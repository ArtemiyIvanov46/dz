df = pd.read_csv('iris_data.csv')
fig=plt.figure(figsize=(10,6))
ax1=fig.add_subplot(211)
ax2=fig.add_subplot(212)


a=list(df['Species'])
b=0
c=0
d=0
for i in a:
    if i=="Iris-virginica":
        b+=1
    elif i=="Iris-versicolor":
        c+=1
    else:
        d+=1
b1=b/150
c1=c/150
d1=d/150
ax1.pie([b1, c1, d1], labels = ['Iris-virginica','Iris-versicolor','Iris-setosa'])


df = pd.read_csv('/Users/rootadmin/Downloads/iris_data.csv')
a=list(df['PetalLengthCm'])
b=0
c=0
d=0
for i in a:
    if i<1.2:
        b+=1
    elif i>=1.2 and i<1.5:
        c+=1
    else:
        d+=1
b1=b/150
c1=c/150
d1=d/150
ax2.pie([b1, c1, d1], labels = ['<1,2','1,2=<x<1,5','>1,5'])

plt.title('Ирисы')

plt.show()