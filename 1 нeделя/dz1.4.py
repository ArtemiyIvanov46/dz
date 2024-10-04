f=open(‘input.txt','r')
lines=f.readlines()
a=list(map(int,lines[0].split()))
op=lines[1]
od=op[:1]
g=od.join(str(i) for i in a)
res=eval(g)
f.close()
f=open('output.txt','w')
f.write(str(res))
f.close()