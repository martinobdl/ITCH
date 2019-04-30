from Algo import Algo

class fixed_spread(Algo):

    def __init__(self,tick,spread_ticks,width):
        super(fixed_spread, self).__init__()
        self.spread_ticks = spread_ticks
        self.spread = spread_ticks*tick
        self.width = width
        self.tick = tick

    def init_run(self):
        super(fixed_spread, self).init_run()
        self.width = 1
        self.a_sell = 9999999
        self.a_buy = 0

    def step(self,pt,past_ts):
        self.a_sell = pt if pt > self.a_sell else pt+self.spread
        self.a_buy = pt if pt < self.a_buy else pt-self.spread
        self.orders = self.init_orders()
        if not past_ts.empty:
            self.width = max(self.width,int(abs(pt-past_ts.iloc[-1])/self.tick))
        for i in range(1,self.width+1):
            self.orders[0][self.a_buy-i*self.tick] = 1
            self.orders[1][self.a_sell+i*self.tick] = 1

