alphabet = 'abcdefghijklmnopqrstuvwxyz'
word=input()
otvet=[]
def z_function(S):
    zf = [0]*len(S)
    left,right = 0,0
    for i in range(1, len(S)):
        zf[i] = max(0, min(zf[i - left], right - i))
        while i + zf[i] < len(S) and S[zf[i]] == S[i + zf[i]]:
            zf[i] += 1
        if i + zf[i] > right:
            left, right = i, i + zf[i]
    return zf
ZZZ=z_function(word)
n=0
w=0
for i in ZZZ:
    if i==0 and w!=0:
        w-=1
    if i==0 and w==0:
        otvet.append(alphabet[n])
        n+=1
    elif ((i==1)and(w==0)):
        otvet.append(otvet[0])
        w+=1
    elif (i>1 and w==0):
        for j in range(i):
            otvet.append(otvet[j])
        w+=i
print(''.join(otvet))
