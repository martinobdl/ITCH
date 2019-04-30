import utility
import pandas as pd
import numpy as np
from matplotlib import pyplot as plt
from tqdm import tqdm
from fixed_spread import fixed_spread

fileName = "~/Documents/ITCH/20180830.PSX_ITCH_50_AAPL_out_message.csv"

df = pd.read_csv(fileName);
df.time = df.time.map(lambda t: utility.parseNanosecondsToDateTime(fileName,t))
df_Executions = df[(df.type == "P") | (df.type == "E")]
ts_AAPL = pd.Series(index=df_Executions.time,data=df_Executions.price.values)

fileName = "~/Documents/ITCH/20180830.PSX_ITCH_50_SPY_out_message.csv"

df = pd.read_csv(fileName);
df.time = df.time.map(lambda t: utility.parseNanosecondsToDateTime(fileName,t))
df_Executions = df[(df.type == "P") | (df.type == "E")]
ts_SPY = pd.Series(index=df_Executions.time,data=df_Executions.price.values)

S0 = 100
tt = np.array(map(lambda x: x.value ,df_Executions.time-df_Executions.time.iloc[0]))/float((df_Executions.time.iloc[-1]-df_Executions.time.iloc[0]).value)
dt = np.hstack([0,np.diff(tt)])
S = S0*np.cumprod(np.exp(-0.2**2*0.5*dt+dt**0.5*0.2*np.random.normal(size=len(df_Executions.time))))
ts_s = pd.Series(index = df_Executions.time, data = S)

tick = 0.005

B = [1, 2, 3, 4, 5, 10, 20, 40, 80, 100]
res = []

for b in B:
    s = fixed_spread(tick=0.005,spread_ticks=b,width=10)
    s.run(ts_AAPL)
    res.append(s.get_total_value())

plt.figure()
plt.plot(B,res)
plt.show(0)
