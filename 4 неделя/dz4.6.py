import datetime
import matplotlib.dates as mdates
df = pd.read_csv('/Users/rootadmin/Downloads/BTC_data.csv')
z=[datetime.datetime.strptime(i.split('T')[0], '%Y-%m-%d') for i in df['time']]
z1=list(df['close'])
fig=plt.figure(figsize=(10,6))
ax=fig.add_subplot(111)
ax.xaxis.set_major_formatter(mdates.DateFormatter('%d-%m-%Y'))
ax.plot(z,z1)
plt.show()

a=[i for i in range(1457)]
b=(list(df['close']))

v = np.polyfit(a,df['close'],1)
p = np.poly1d(v)


x=[1,1457]
y=[p(1),p(1457)]

plt.plot(x,y )