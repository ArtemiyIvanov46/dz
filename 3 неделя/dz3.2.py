def factor(n, i = 2):
    while(i+1<=n):
        if n%i != 0:
            i+=1
        else:
            return [i] + factor(n//i,i)
    return [n]
print(factor(int(input())))