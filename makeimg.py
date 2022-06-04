from pandas.core.arrays import datetimes
from datetime import date
from pandas.io.formats import style
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

data  = pd.read_csv('data.csv',index_col=0,parse_dates=True)

#data.head(3).append(data.tail(3))

spx = data.loc['2022-04-01':'2022-04-20']
#['2022-04-19']

#spx.head(3).append(data.tail(3))

fig = plt.figure(figsize=(16,6))
ax1 = fig.add_subplot(1,1,1)

x = spx.index
y1 = spx.kcal
y2 = spx.weight
#y1 = data.weight
#y2 = data.kcal

ax1.bar(x,y1,label='kcal',alpha=0.7)
ax1.legend(loc='upper left',frameon=True)

ax2 = ax1.twinx()
ax2.plot(y2,color='#204556',label='weight',linestyle='-')
ax2.legend(loc='upper right',frameon=True)

plt.savefig('outputimg.png')
#plt.xticks(np.linspace(1,20,20))