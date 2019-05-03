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

PATH = os.path.dirname(os.path.realpath(__file__))
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
    def __init__(self, date, venue, stock, levels=5):
        self.date = date
        self.venue = venue
        self.stock = stock
        self.levels = levels
        self.PKfileName = date+"."+venue+"_"+stock+"_"+str(levels)+".pk"
        pk_folderPath = os.path.dirname(PATH)+'/data/pk/'

        try:

            PKfile = open(pk_folderPath+self.PKfileName,'rb')
            [self.time, self.book, self.messages] = pickle.load(PKfile)

        except:

            print
            print("Executing BookConstructor...")

            shellScriptPath = os.path.dirname(PATH)+"/BookConstructor.sh"

            subprocess.run([shellScriptPath, os.path.dirname(PATH)+"/data/", self.date, self.venue, self.stock, "-n", str(self.levels)])

            bookDir = os.path.dirname(PATH)+"/data/book/"
            messDir = os.path.dirname(PATH)+"/data/messages/"
            nameFile = self.date+"."+self.venue+PROTOCOL_NAME+self.stock

            self.book = pd.read_csv(bookDir+nameFile+"_book_"+str(levels)+".csv");
            self.messages = pd.read_csv(messDir+nameFile+"_message.csv");

            print("parsing time into datetime objects...")
            print

            self.time = self.messages.time
            self.messages.time = self.messages.time.map(lambda t: utility.parseNanosecondsToDateTime(self.date,t).to_pydatetime())
            self.book.time = self.book.time.map(lambda t: utility.parseNanosecondsToDateTime(self.date,t).to_pydatetime())

            with open(pk_folderPath+self.PKfileName, 'wb') as file:
                print("pickling...")
                pickle.dump([self.time, self.book, self.messages], file)

    def plot_liquidity_heatmap(self,t_min=34200000000000,t_max=57600000000000,p_min=0,p_max=999999,n_t=400,n_p=500,levels=100):

        mask = (self.time > t_min) & (self.time <= t_max)

        if(p_min==0): p_min = self.book['1_bid_price'].loc[mask].min()-0.1
        if(p_max==999999): p_max = self.book['1_bid_price'].loc[mask].max()+0.1

        tgrid = np.linspace(t_min,t_max,n_t)
        pgrid = np.linspace(p_min,p_max,n_p)
        pgrid.sort()
        tgrid2, pgrid2 = np.meshgrid(tgrid, pgrid)
        heat = np.zeros(tgrid2.shape)

        max_levels = min(self.levels+1,levels)

        for t,ti in tqdm.tqdm(zip(tgrid,range(len(tgrid)))):
            cut = self.book.iloc[np.abs(self.time-t).idxmin()].iloc[1:]
            for k in range(1,max_levels):
                price = cut[str(k)+'_bid_price']
                if not np.isnan(price):
                    p = np.abs(pgrid-price).argmin()
                    vol = cut[str(k)+'_ask_vol']
                    if not np.isnan(vol): heat[p][ti] += vol
                price = cut[str(k)+'_ask_price']
                if not np.isnan(price):
                    p = np.abs(pgrid-price).argmin()
                    vol = cut[str(k)+'_ask_vol']
                    if not np.isnan(vol): heat[p][ti] += vol

        heat[heat==0] = np.nan

        fig = plt.figure()
        ax = fig.add_subplot(111)
        ax.plot(self.time.loc[mask], self.book['1_bid_price'].loc[mask], c='crimson',linewidth=0.7)
        ax.plot(self.time.loc[mask], self.book['1_ask_price'].loc[mask], c='teal',linewidth=0.7)
        cs = ax.pcolormesh(tgrid2, pgrid2, heat, cmap='plasma', norm=matplotlib.colors.LogNorm(vmin=np.nanmin(heat), vmax=np.nanmax(heat)))
        fig.colorbar(cs, ax=ax,
                        orientation='vertical',
                        fraction=.1,
                        extend='both',
                        extendfrac='auto')
        plt.show()

# importlib.reload(environment)
# a = environment.ts('08302018','PSX','FF', 6)
# a.plot_liquidity_heatmap()
