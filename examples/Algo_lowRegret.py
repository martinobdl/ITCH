from Algo import Algo
from Algo_fixedSpread import fixed_spread
import environment
import collections
import utility
import numpy as np

class low_regret(Algo):

    def __init__(self,B):
        """ Algo specific parameters here.
        """
        super(low_regret, self).__init__()
        self.B = B
        self.experts = [fixed_spread(b) for b in B]
        self.Expert_distribution = utility.normalize(np.ones(len(B)))

    def init_run(self,env_p0):
        """ Called before run method. Use to initialize persistent variables.
        """
        super(low_regret, self).init_run()
        for e in self.experts:
            e.init_run(env_p0)

    def step(self,last_message):
        """ Get startegy for next tick.
        """
        self.orders.delete_all_buy_order()
        self.orders.delete_all_sell_order()
        t = last_message[1].time
        p = last_message[1].price

        for i,e in enumerate(self.experts):

            e.collect_from_orders(last_message)
            e.step(last_message)
            e.update_history(t,p)
            e.orders.timestamp = t

            c1 = collections.Counter({x: y*self.Expert_distribution[i] for x, y in e.orders.get_buy_orders().items()})

            c2 = collections.Counter({x: y*self.Expert_distribution[i] for x, y in e.orders.get_sell_orders().items()})

            self.orders.add_buy_orders_from_dict(c1)
            self.orders.add_sell_orders_from_dict(c2)

        self.update_expert_distribution()

    def update_expert_distribution(self):
        k = 0.0001
        inventory = np.array([e.inventory for e in self.experts])
        Loss = np.exp(-k*np.abs(inventory))
        self.Expert_distribution = utility.normalize(Loss)


if __name__=='__main__':
    s = low_regret([1,2,3,4,5]);
    a = environment.ts('01302019','NASDAQ','ACAD')
    s.run(a)
    s.plot()
