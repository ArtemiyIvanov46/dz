def fib(n, c={0:0,1:1}):
    if n in c:
        return c[n]
    c[n]= fib(n-2,c)+fib(n-1,c)
    return c[n]

a=int(input())
print(fib(a))