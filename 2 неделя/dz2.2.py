sum = 0
list = input()
lista = list[2:]
a = int(list[0])
result = []
while sum < len(lista):
    listv = lista[sum:sum + a]
    listw = listv[::-1]
    result += listw
    sum += a
print(''.join(result))