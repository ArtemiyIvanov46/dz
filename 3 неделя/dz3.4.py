def triangle(size,symb,a=1):
    if size == 0:
        return
    print(min(a,size)*symb)
    triangle(size-1,symb,a+1)
size = int(input())
symb = input()
print(triangle(size, symb))