df = pd.read_csv('/Users/rootadmin/Downloads/iris_data.csv')
fig=plt.figure(figsize=(10,6))
ax1=fig.add_subplot(321)
ax2=fig.add_subplot(322)
ax3=fig.add_subplot(323)
ax4=fig.add_subplot(324)
ax5=fig.add_subplot(325)
ax6=fig.add_subplot(326)
a=(list(df['SepalLengthCm']))
a1=sorted(a)
b=list(df['SepalWidthCm'])
b1=sorted(b)
c=list(df['PetalLengthCm'])
c1=sorted(c)
d=list(df['PetalWidthCm'])
d1=sorted(d)


print(np.polyfit(a1,b1,1))
z=np.polyfit(a1,b1,1)
p = np.poly1d(z)
x=[a1[0],a1[149]]
y=[p(a1[0]),p(a1[149])]


ax1.scatter(a1, b1, marker="2", color='b')

ax6.scatter(c1,d1, marker="2", color='b')

ax1.plot(x,y)
ax2.plot(a1,c1)
ax3.plot(a1,d1)
ax4.plot(b1,c1)
ax5.plot(b1,d1)


print(np.polyfit(c1,d1,1))
z=np.polyfit(c1,d1,1)
p = np.poly1d(z)
x=[c1[0],c1[149]]
y=[p(c1[0]),p(c1[149])]
ax6.plot(x,y)
plt.show()