import numpy as np
def spiral(N,M):
    A= np.zeros((N,M))
    a,i,j=1,0,0
    while(a<M*N):
        while(j+1 <M and A[i][j+1]==0):
            A[i][j]=a
            a+=1
            j+=1
        while(i+1<N and A[i+1][j]==0):
            A[i][j]=a
            a+=1
            i+=1
        while(j>0 and A[i][j-1]==0):
            A[i][j]=a
            a+=1
            j-=1
        while(i>0 and A[i-1][j]==0):
            A[i][j]=a
            a+=1
            i-=1
    A[i][j]=a
    return A
a=int(input())
b=int(input())
print(spiral(6,7))