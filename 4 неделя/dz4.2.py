pos = 0
scale = 10
values1 = np.random.normal(pos, 10, 2000)
values2 = np.random.normal(pos, 10, 6000)
values3 = np.random.normal(pos, 10, 10000)
values4 = np.random.normal(pos, 10, 22000)

fig=plt.figure(figsize=(10,6))
ax1=fig.add_subplot(221)
ax2=fig.add_subplot(222)
ax3=fig.add_subplot(223)
ax4=fig.add_subplot(224)

ax1.hist(values1, 100)
ax2.hist(values2, 100)
ax3.hist(values3, 100)
ax4.hist(values4, 100)

plt.show()
