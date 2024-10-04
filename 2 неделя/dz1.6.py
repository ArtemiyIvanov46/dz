f=open('input.txt','r')
lines=f.readlines()
a=list(map(int,lines[0].split()))
op=lines[1]
om=lines[2]
on=om[:1]
od=op[:1]
b=[]
for i in a:
    i = int(str(i), int(on))
    b+=str(i)
g=od.join(str(i) for i in b)
res=eval(g)
otvet = ""
while res > 0:
    otvet = str(res % int(on)) + otvet
    res //= int(on)
f.close()
f=open('output.txt','w')
f.write(str(res))
f.close()
