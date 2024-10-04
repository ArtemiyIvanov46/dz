a = input()
b = list(map(int, a.split()))
sum = 0
for i in b:
    sum += i ** 2
print((sum/len(b)) ** (1 / 2))
