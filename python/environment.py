import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.dates as dates
import matplotlib
import subprocess
import os
import pickle
import utility

PATH = os.path.dirname(os.path.realpath(__file__))
PROTOCOL_NAME = "_ITCH50_"

class ts:
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

    def plot_liquidity_heatmap(self):

        tgrid = self.time[4000:4500]
        pgrid = list(set(self.messages.price))
        pgrid.sort()
        tgrid2, pgrid2 = np.meshgrid(tgrid, pgrid)
        heat = np.zeros_like(tgrid2)

        for t in range(len(self.time)):
            for k in range(1,self.levels+1):
                price = self.book.iloc[t][str(k)+'_bid_price']
                if not np.isnan(price):
                    p = pgrid.index(self.book.iloc[t][str(k)+'_bid_price'])
                    heat[p][t] = self.book.iloc[t][str(k)+'_bid_vol']
                price = self.book.iloc[t][str(k)+'_ask_price']
                if not np.isnan(price):
                    p = pgrid.index(self.book.iloc[t][str(k)+'_ask_price'])
                    heat[p][t] = self.book.iloc[t][str(k)+'_ask_vol']


        fig = plt.figure()
        ax = fig.add_subplot(111)
        # ax.plot(self.book.time, self.book['1_bid_price'], c='green')
        # ax.plot(self.book.time, self.book['1_ask_price'], c='red')
        ax.pcolormesh(tgrid, pgrid, heat, cmap='PuRd')
        plt.show()

# importlib.reload(environment)
# a = environment.ts('08302018','PSX','FF', 6)
# a.plot_liquidity_heatmap()
