import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
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
            [self.book, self.messages] = pickle.load(PKfile)

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

            self.messages.time = self.messages.time.map(lambda t: utility.parseNanosecondsToDateTime(self.date,t))
            self.book.time = self.book.time.map(lambda t: utility.parseNanosecondsToDateTime(self.date,t))

            with open(pk_folderPath+self.PKfileName, 'wb') as file:
                print("pickling...")
                pickle.dump([self.book, self.messages], file)

    def plot_liquidity_heatmap(self):
        plt.figure()
        mid = (self.book['1_bid_price']+self.book['1_ask_price'])/2
        plt.plot(self.book.time, mid, c='black')
        plt.scatter([d.to_pydatetime() for d in self.book.time], self.book['1_bid_price'], c=self.book['1_bid_vol'])
        plt.show()

