from Algo import Algo
import environment
import utility

class fixed_spread(Algo):

    def __init__(self,spread_ticks):
        """ Algo specific parameters here.
        """
        super(fixed_spread, self).__init__()
        self.spread_ticks = spread_ticks

    def init_run(self,env_p0):
        """ Called before run method. Use to initialize persistent variables.
        """
        super(fixed_spread, self).init_run()
        self.tick = env_p0['ticksize']
        self.spread = self.spread_ticks*self.tick
        self.last_price = env_p0['p0']
        self.width = 1
        self.a_sell = 9999999
        self.a_buy = 0

    def step(self,last_message):
        """ Get startegy for next tick.
        """
        t = last_message[0].time

        if last_message[1].type=='E':

            pt = last_message[1].price

            self.orders.delete_all_buy_order()
            self.orders.delete_all_sell_order()

            if pt>self.a_sell or pt<self.a_sell:
                self.a_sell = pt if pt > self.a_sell else pt+self.spread
                self.a_buy = pt if pt < self.a_buy else pt-self.spread

            self.width = max(self.width, int(abs(pt - self.last_price)/self.tick))

            self.last_price = pt

            for i in range(1,self.width+1):
                self.orders.set_buy_order(self.a_buy-i*self.tick,1)
                self.orders.set_sell_order(self.a_sell+i*self.tick,1)

if __name__=='__main__':
    s = fixed_spread(5);
    a = environment.ts('01302019','NASDAQ','INTC')
    s.run(a)
    s.plot()
