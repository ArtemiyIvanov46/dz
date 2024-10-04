with open ('input.txt', 'r') as f1:
    L1=f1.readlines()
count=0
for i in L1:
    if i==("?" or "!"):
        if a==("?" or "!"):
            count+=0
            a=i
        else:
            count+=1
            a=i
    elif i==("."):
        if a==("."):
            count+=0
            a=i
        else:
            count+=1
            a=i
    else:
        count+=0
        a=i
print(count)
