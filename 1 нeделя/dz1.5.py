a=int(str(N), b)
otvet = ""
while a > 0:
    otvet = str(a % c) + otvet
    A //= c
print(otvet)
