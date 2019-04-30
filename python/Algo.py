import sys
import numpy as np
import pandas as pd
import itertools
import logging
import inspect
import copy
import matplotlib.pyplot as plt
import tqdm

class Algo(object):
    """ Base class for algorithm calculating cash inventory for a market making strategy.
    You have to subclass step method to submit new orders.
    """

    # fixec commission for execution
    COMMISSIONS = 0.002

    def __init__(self, letency=0):
        """ Subclass to define algo specific parameters here.
        :param latency: algorith latency in execution
        """
        self.letency = letency

    def init_orders(self):
        """ Set initial orders.
        """
        return {0:{},1:{}}

    def init_run(self):
        """ Called before run method. Use to initialize persistent variables.
        """
        self.orders = self.init_orders()
        self.cash = 0
        self.inventory = 0
        self.value = 0
        self.history = np.empty((0,4), float)

    def run(self, data):
        """ Run algorithm and get inventory,cash and total value.
        :params data: time series of the security to analyze
        """
        self.init_run()
        for (i,t,pt) in zip(range(len(data)),data.index,data.values):
            self.collect_from_orders(pt)
            self.update_history(t,pt)
            self.step(pt,data.iloc[:i])

    def step(self, pt):
        """ Get startegy for next tick. """
        raise NotImplementedError('Subclass must implement this!')

    def collect_from_orders(self,pt):
        """ Method to update inventory and cash after observing next tick given limit orders submitted.
        :params pt: last execution price.
        """

        # buy
        for price in self.orders[0].keys():
            size = self.orders[0][price]
            if price > pt:
                self.inventory += size
                self.cash -= size*(price + self.COMMISSIONS)

        # sell
        for price in self.orders[1].keys():
            size = self.orders[1][price]
            if price < pt:
                self.inventory -= size
                self.cash += size*(price - self.COMMISSIONS)

    def update_history(self,t,pt):
        """ Method to update history of the algorithm observing next tick.
        :params pt: last execution price.
        """
        self.value = self.inventory*pt + self.cash
        self.history = np.vstack((self.history,[t,self.inventory,self.cash,self.value]))

    def plot(self):
        """ Plot inventory, cash and total value of the algorithm.
        """
        f, axarr = plt.subplots(3, sharex=True)
        f.suptitle('performance')
        axarr[0].plot(self.history[:,0],self.history[:,1])
        axarr[1].plot(self.history[:,0],self.history[:,2])
        axarr[2].plot(self.history[:,0],self.history[:,3])
        axarr[0].set_title('inventory')
        axarr[1].set_title('cash')
        axarr[2].set_title('value')
        f.autofmt_xdate
        plt.show(0)

    def get_total_value(self):
        return self.value
