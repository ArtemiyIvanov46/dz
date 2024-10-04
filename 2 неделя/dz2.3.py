list=input()
lista=['4','7','9','6','B','C','D','F','G','K','N','P','R',]
for i in lista:
  if i in list:
    a=0
    break
  else: a=1
listb={"E":"3","3":"E","J":"L","L":"J","S":"2","2":"S","Z":"5","5":"Z"}
listc=[listb.get(x,x) for x in list]
listd=listc[::-1]
liste="".join(listd)
if liste==list:
    b=1
else:
    b=0


if list==str(list[::-1]):
    c=1
else:
    c=0

if(a+b+c)==3:
    print(f"{list} is a mirrored palindrome.")
elif (c==1 and a+b+c!=3):
    print(f"{list} is a normal palindrome.")
elif (c==0 and a+b+c==2):
    print(f"{list} is a mirrored string.")
else:
    print(f"{list} is not a palindrome.")