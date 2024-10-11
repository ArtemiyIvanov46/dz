a=[1,2,3,4,5,5,6,88]
b=[5,6,7,8,8,9,10]
a1=[i for i in a if a.count(i)==1 #уникальные для 1 списка
print(a1)
b1=[i for i in b if b.count(i)==1] #уникальные для 2 списка
print(b1)
print((set(a)&set(b))^set(b))
print(set(a)^set(b)) #уникальные для объединения
print(set(a)&set(b)) #содержатся в обоих