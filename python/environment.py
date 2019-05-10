import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.dates as dates
import matplotlib
import subprocess
import os
import tqdm
import pickle
import utility
from matplotlib.widgets import Button
import sys

PROTOCOL_NAME = "_ITCH50_"

class ts:
    """ Class to handle full depth order book
    and messages data taken from the BookReconstructor
    application. Looks for picked data in ../data/pk
    if the data cannot not found calls the BookConstructor
    application in order to reconstruct the book.

    Parameters
    ----------
    date : string
        date in mmddyyyy format
    venue : string
        NASDAQ venue (PSX,NASDAQ,BX)
    stock : string
        ticker in capital letter traded on the vanue
    levels : int, optional
        specify the maximum depth of the order book

    """
    def __init__(self, date, venue, stock, PATH=os.path.dirname(os.path.realpath(__file__)), levels=5):
        self.date = date
        self.venue = venue
        self.stock = stock
        self.levels = levels
        self.PKfileName = date+"."+venue+"_"+stock+"_"+str(levels)+".pk"
        pk_folderPath = os.path.dirname(PATH)+'/data/pk/'

        try:

            PKfile = open(pk_folderPath+self.PKfileName,'rb')
            [self.book, self.messages] = pickle.load(PKfile)

        except:

            print
            print("Executing BookConstructor...")

            shellScriptPath = os.path.dirname(PATH)+"/BookConstructor.sh"

            try:

                subprocess.run([shellScriptPath, os.path.dirname(PATH)+"/data/", self.date, self.venue, self.stock, "-n", str(self.levels)])

                bookDir = os.path.dirname(PATH)+"/data/book/"
                messDir = os.path.dirname(PATH)+"/data/messages/"
                nameFile = self.date+"."+self.venue+PROTOCOL_NAME+self.stock

                self.book = pd.read_csv(bookDir+nameFile+"_book_"+str(levels)+".csv");
                self.messages = pd.read_csv(messDir+nameFile+"_message.csv");

                print("parsing time into datetime objects...")
                print

                with open(pk_folderPath+self.PKfileName, 'wb') as file:
                    print("pickling...")
                    pickle.dump([self.book, self.messages], file)

            except:

                print("No data found for: ", self. stock, self.venue, self.date)
                print()
                return

        self.time = self.messages.time
        self.ticksize = round(np.diff(np.unique(self.messages.price)).min(),6)

        self.initial_param = {'ticksize':self.ticksize,'p0':self.messages.iloc[0].price}

    def get_heat_map(self,t_boud,p_boud,n_t,n_p,levels):
        """ Get the heat map and the mask parameter
        in order to plot the order heatmap

            Parameters
            ----------
            t_boud : list of int, optional
                time bound, default value is from 9.00 am to 4.30 pm
                in nanoseconds since 00:00
            p_boud : list of int, optional
                price bound, default value is from min to max of the
                time series over the t_bound
            n_t : int, optional
                numbers of data points in the time discretization
            n_p : int, optional
                numbers of data points in the price discretization
            levels : int, optional
                maximum number of levels to dispalay in the book depth

            Returns
            -------
            heat, array
                n_t x n_p matrix with order volumes.

            mask, array
                boolean mask that limits time values
                in order to be in the interval t_bound

            tgrid2, array
                n_t x n_p matrix result of meshgrid

            pgrid2, array
                n_t x n_p matrix result of meshgrid

            """

        t_min, t_max = t_boud
        p_min, p_max = p_boud
        mask = (self.time > t_min) & (self.time <= t_max)
        n_p = min(n_p,(p_max-p_min)/self.ticksize)*2

        if(p_min==0): p_min = self.book['1_bid_price'].loc[mask].min()-0.1
        if(p_max==999999): p_max = self.book['1_bid_price'].loc[mask].max()+0.1

        tgrid = np.linspace(t_min, t_max, n_t)
        bins = np.array(list(set(self.messages.price)))
        bins.sort()
        centers = (bins[1:]+bins[:-1])/2
        pgrid = np.linspace(p_min, p_max, n_p)
        # pgrid = bins[np.digitize(pgrid, centers)]
        tgrid2, pgrid2 = np.meshgrid(tgrid, pgrid)
        heat = np.zeros(tgrid2.shape)

        max_levels = min(self.levels+1,levels)

        for t,ti in tqdm.tqdm(zip(tgrid,range(len(tgrid)))):
            cut = self.book.iloc[np.abs(self.time-t).idxmin()].iloc[1:]
            for k in range(1,max_levels):
                price = cut[str(k)+'_bid_price']
                if not np.isnan(price) and p_boud[0]<=price<=p_boud[1]:
                    p = np.abs(pgrid-price).argmin()
                    vol = cut[str(k)+'_ask_vol']
                    if not np.isnan(vol): heat[p][ti] += vol
                price = cut[str(k)+'_ask_price']
                if not np.isnan(price) and p_boud[0]<=price<=p_boud[1]:
                    p = np.abs(pgrid-price).argmin()
                    vol = cut[str(k)+'_ask_vol']
                    if not np.isnan(vol): heat[p][ti] += vol

        heat[heat==0] = np.nan

        return heat, mask, tgrid2, pgrid2

    def plot_liquidity_heatmap(self,t_boud=[34200000000000,57600000000000],
                                p_boud=[0,999999],
                                n_t=400,n_p=100,
                                levels=100):

        """ Plot the best bid and ask time series together with
        the time series of the sizes of the orders.

            Parameters
            ----------
            t_boud : list of int, optional
                time bound, default value is from 9.00 am to 4.30 pm
                in nanoseconds since 00:00
            p_boud : list of int, optional
                price bound, default value is from min to max of the
                time series over the t_bound
            n_t : int, optional
                numbers of data points in the time discretization
            n_p : int, optional
                numbers of data points in the price discretization
            levels : int, optional
                maximum number of levels to dispalay in the book depth
            """

        def refocus(event):

            global cs, bar
            heat, _, tgrid2, pgrid2 = self.get_heat_map(x_b, y_b, n_t, n_p, levels)
            cs.remove()

            cs = ax.pcolormesh(tgrid2, pgrid2, heat, cmap=cmap,
                        norm=matplotlib.colors.LogNorm(vmin=vmin, vmax=vmax))
            ax.grid()
            plt.draw()

        def on_lims_change(axes):
            global x_b, y_b
            [x_b,y_b] = ax.get_xlim(),ax.get_ylim()
            print(x_b,y_b)

        cmap = plt.cm.jet

        heat, mask, tgrid2, pgrid2 = self.get_heat_map(t_boud,p_boud,n_t,n_p,levels)

        fig, ax = plt.subplots()

        plt.subplots_adjust(bottom=0.2)

        plt.title(self.date + ' @ ' + self.venue + ': ' + self.stock)

        plt.xlabel('ns since 00:00')
        plt.ylabel('price')

        ts_1, = ax.plot(self.time.loc[mask],
                        self.book['1_bid_price'].loc[mask],
                        c='crimson', linewidth=0.9)

        ts_2, = ax.plot(self.time.loc[mask],
                        self.book['1_ask_price'].loc[mask],
                        c='teal', linewidth=0.9)

        plt.legend((ts_1, ts_2), ('bid', 'ask'))

        global cs, bar
        vmin, vmax = [np.nanmin(heat),np.nanmax(heat)]

        cs = ax.pcolormesh(tgrid2, pgrid2, heat,
                            cmap=cmap,
                            norm=matplotlib.colors.LogNorm(vmin=vmin, vmax=vmax))

        bar = fig.colorbar(cs,ax=ax,
                        orientation='vertical',
                        fraction=.1,
                        extend='both',
                        extendfrac='auto')

        bar.set_label('Order size', rotation=270)

        ax.callbacks.connect('xlim_changed', on_lims_change)
        ax.callbacks.connect('ylim_changed', on_lims_change)

        axprev = plt.axes([0.868, 0.90, 0.1, 0.068])
        bprev = Button(axprev, 'Refresh')
        bprev.on_clicked(refocus)
        ax.grid()
        plt.show()

    def get_data_up_to(self,t):
        """ return book df up to time stamp t

            Parameters
            ----------
            t : int
                time of when to truncate the data
            """
        return self.book[self.time<=t], self.messages[self.time<=t]

    def get_data_at_time(self,idx):
        """ return book and message data at index i

            Parameters
            ----------
            idx : int
                query the data at index idx
        """
        return self.book.iloc[idx], self.messages.iloc[idx]

    def get_last_execution(self,t,idx=1):
        """ get the last execution happend before time stamp t

            Parameters
            ----------
            t : int
                time of when to truncate the data
            idx : ind, optional
                get idx-last execution message, defualt is 1

        """
        types = ['E']
        sliced = self.messages[self.time<=t]
        if not sliced.loc[self.messages.type == 'E'].empty:
            return sliced.loc[self.messages.type == 'E'].iloc[-idx]
        else:
            return pd.DataFrame(columns = self.messages.columns)

    def plot_order_book(self,i,index='true',**kwargs):

        """ plot the barplot of the order book at time or index i

            Parameters
            ----------
            i : int
                depending of the boolean index (dault=True) plots
                the order book at index (time) i
            index : boolean, optional
                if True, i is the index
                if False, i is the time
            **kwargs :
                xmin, xmax : float, specify the bounds for the xaxis
                ymax : float, specify the upper bound for the yaxis
                block : bool, wheter to block at the plot or continue the code
        """

        [price, size, t, idx] = self.get_book_for_bar_plot(i,index)

        color = ['red','green']*int(len(size)/2)

        fig, ax = plt.subplots()

        rect = plt.bar(price,size,width=self.ticksize/2,color=color)
        fig.suptitle('time: '+str(t))
        ax.grid(True)
        plt.subplots_adjust(bottom=0.2)

        if 'xmin' and 'xmax' in kwargs.keys():
            plt.xlim((kwargs['xmin'],kwargs['xmax']))

        if 'ymax' in kwargs.keys():
            plt.ylim((0,kwargs['ymax']))

        if 'block' in kwargs.keys():
            plt.show(kwargs['block'])
        else:
            plt.show()
        return fig

    def get_book_for_bar_plot(self,i,index):

        """ get the barplot data of the order book at time or index i

            Parameters
            ----------
            i : int
                depending of the boolean index (dault=True) plots
                the order book at index (time) i
            index : boolean
                if True, i is the index
                if False, i is the time
        """

        if index:
            data = self.book.iloc[i]
            t = self.time[i]
            idx = i
        else:
            data = self.book[self.book.time<i].iloc[-1]
            t = int(data.time)
            idx = data.index
        price = data.iloc[1:-1:2]
        size = data.iloc[2::2]
        return price,size,t,idx

if __name__ == '__main__':
    argc = len(sys.argv)
    if argc == 1:
        date = '01302019'
        venue = 'NASDAQ'
        stock = 'INTC'
    else:
        date = sys.argv[1]
        venue = sys.argv[2]
        stock = sys.argv[3]
    if argc == 5:
        PATH = sys.argv[4]
    else:
        PATH = os.path.dirname(os.path.realpath(__file__))
    a = ts(date,venue,stock,PATH,5)
    a.plot_liquidity_heatmap()

