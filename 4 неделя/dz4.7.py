import string
a = str(input())
for i in a:
    if i in string.punctuation:
        a = a.replace(i, " ")
kolvo = {}
words = [str(i).lower() for i in a.split()]
print(words)
for w in words:
    if w in kolvo:
        kolvo[w] += 1
    else:
        kolvo[w] = 1
print(kolvo)