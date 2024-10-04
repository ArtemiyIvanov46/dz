with open ('input.txt', 'r') as f1:
    L1=f1.readlines()+[" "]
answer=[]
a = 0
countt = 0
b=1
m=["у", "ю", "э", "я", "а", "о", "ы", "и", "е", "ё"]
for i in L1:
    if m.count(a)==0 and m.count(i)==1 and b==0:
            answer += [i] + ["с"] + [i]
            a=i
            countt+=1
            b=0
    elif i == " ":
        a = i
        answer += [i]
        countt=0
        b=1
    elif m.count(i)!=1:
        a = i
        answer += [i]
        countt=0
        b=0
    else:
        a = i
        answer += [i]
        countt+=1
print("".join(answer))