import sys
import numpy as np
import pandas as pd
import itertools
import logging
import inspect
import copy
import matplotlib.pyplot as plt
import tqdm
import collections
import environment
import utility


class Algo(object):
    """ Base class for algorithm calculating cash inventory for a market making strategy.
    You have to subclass step method to submit new orders.
    """

    COMMISSIONS = 0.003 # fix commission
    LATENCY = 100*1e-3*1e9 # 100 ms: LON to NY is ~60ms
    ONLY_EXEC = True # the algo only takes a decision at times of executions, and not at each timestamp

    def __init__(self):
        """ Subclass to define algo specific parameters here.
        :param latency: algorith latency in execution
        """
        pass

    def init_run(self):
        """ Called before run method. Use to initialize persistent variables.
        """
        self.orders = orders()
        self.cash = 0
        self.inventory = 0
        self.value = 0
        self.history = np.empty((0,4), float)


    def run(self, env):
        """ Run algorithm and get inventory,cash and total value.
        :params env: environment object used to test the
        """
        self.init_run(env.initial_param)
        if self.ONLY_EXEC:
            time = env.time[env.messages.type=='E']
        else:
            time = env.time
        time = time[time < 57600000000000][time > 34200000000000]

        for i in tqdm.tqdm(time.index):

            t = time.at[i]
            tmp_row = env.get_data_at_time(i)
            self.collect_from_orders(tmp_row)
            if tmp_row[1].type == 'E':
                self.update_history(t,tmp_row[1].price)
            self.step(tmp_row)
            self.orders.timestamp = t

    def step(self, data_up_to_now):
        """ Get startegy for next tick.
        Should update orders.
        """
        raise NotImplementedError('Subclass must implement this!')

    def collect_from_orders(self,last_message):
        """ Method to update inventory and cash after observing next tick given limit orders submitted.
        :params pt: last execution price.
        """
        t = last_message[0].time

        if self.orders.timestamp < t - 2*self.LATENCY and last_message[1].type=='E':
            pt = last_message[1].price
            # buy
            for price in self.orders.get_buy_orders().keys():
                size = self.orders.get_buy_orders()[price]
                if price > pt:
                    self.inventory += size
                    self.orders.delete_buy_order(price)
                    self.cash -= size*(price + self.COMMISSIONS)

            # sell
            for price in self.orders.get_sell_orders().keys():
                size = self.orders.get_sell_orders()[price]
                if price < pt:
                    self.inventory -= size
                    self.orders.delete_sell_order(price)
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
        fig = plt.figure()
        gs = fig.add_gridspec(2,2)

        ax1 = fig.add_subplot(gs[0, 0])
        ax2 = fig.add_subplot(gs[0, 1])
        ax3 = fig.add_subplot(gs[1, :])

        fig.suptitle('performance')
        ax1.plot(self.history[:,0],self.history[:,1])
        ax2.plot(self.history[:,0],self.history[:,2])
        ax3.plot(self.history[:,0],self.history[:,3])
        ax1.set_title('inventory')
        ax1.grid(1)
        ax2.set_title('cash')
        ax2.grid(1)
        ax3.set_title('value')
        ax3.grid(1)
        fig.autofmt_xdate
        plt.show()

    def get_total_value(self):
        """ total final value of the strategy
        """
        return self.value


class orders(object):
    def __init__(self, orders = [collections.defaultdict(int), collections.defaultdict(int)]):
        self.orders = orders
        self.timestamp = 0

    def get_sell_orders(self):
        return self.orders[1]

    def get_buy_orders(self):
        return self.orders[0]

    def add_sell_order(self, price, size):
        self.orders[0][price] += size

    def add_buy_order(self, price, size):
        self.orders[1][price] += size

    def set_buy_order(self, price, size):
        self.orders[0][price] = size

    def set_sell_order(self, price, size):
        self.orders[1][price] = size

    def delete_buy_order(self, price):
        self.orders[0][price] = 0

    def delete_sell_order(self, price):
        self.orders[1][price] = 0
