a,b,n=map(int,input().split())
G={'S':{},'F':{}}
for i in range(1,n+1):
    for j in range(n+1,2*n+1):
        v1,v2,w=i,j,min(a*i,b*(j-n))
        if v1 in G:
            G[v1][v2]=w
        else:
            G[v1]={v2:w}
        if v2 in G:
            G[v2][v1]=0
        else:
            G[v2]={v1:0}

for i in range(1,n+1):
    G['S'][i]=a*i
    G[i]['S']=0
for i in range(n+1,2*n+1):
    G[i]['F']=b*(i-n)
    G['F'][i]=0


def dfs(G,start,finish,visited,f_min):
    if start == finish:
        return f_min
    visited.add(start)
    for v in G[start]:
        if (v not in visited and G[start][v] > 0):
            flow = dfs(G,v,finish,visited,min(f_min,G[start][v]))
            G[start][v] -= flow
            G[v][start] += flow
            if flow > 0:
                return flow
    return 0
def ford_fulkerson(G,start,finish):
    visited = set()
    res = 0
    while (flow:=dfs(G,start,finish,visited,float('inf'))) != 0:
        res += flow
        visited = set()
    return res
(ford_fulkerson(G,'S','F'))
#не совсем понял вразу "Могут ли предприятия взять кредиты так, чтобы все условия выполнились", поэтому проверил, взяли ли все
#предприятия столько кредитов, сколько им надо
sum=0
for i in range(1,n+1):
    if G[i]['S']!=a*i:
        sum+=1
#этот код для проверки, все ли банки дали все кредиты
#for i in range(n+1,2*n+1):
#    if G[i]['F']!=0:
#        sum+=1
if sum==0:
    print('YES')
else:
    print('NO')