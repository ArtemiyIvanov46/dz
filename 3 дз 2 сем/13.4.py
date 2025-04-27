def prefix(s):
    p = [0] * len(s)
    for i in range(1, len(s)):
        k = p[i - 1]
        while k > 0 and s[k] != s[i]:
            k = p[k - 1]
        if s[k] == s[i]:
            k += 1
        p[i] = k
    return p

alphabet = 'abcdefghijklmnopqrstuvwxyz'
word=input()
otvet=[]
perfecto=prefix(word)
print(perfecto)
boombl4=0
bit=0
for simple in perfecto:
    if simple==0 and bit==0:
        otvet.append(alphabet[boombl4])
        boombl4+=1
    if simple==0 and bit!=0:
        for electronic in range(bit):
            otvet.append(otvet[electronic])
        bit=0
        otvet.append(alphabet[boombl4])
        boombl4+=1
    if simple!=0:
        bit=simple
if bit!=0:
    for electronic in range(bit):
            otvet.append(otvet[electronic])
print(''.join(otvet))