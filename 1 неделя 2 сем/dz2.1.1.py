visited = []

def dfs(G,visited,start):
    visited.append(start)
    for i in G[start]:
        if i not in visited:
            dfs(G,visited,i)

eiler=0
rebra=[]
rebra2=[]
G={}
degree={}
M=int(input())
for i in range(M):
    a=input()
    rebra.append(list(map(int,a.split(','))))
    rebra2.append(a)
stroka=','.join(rebra2)
rebra2=list(map(int,stroka.split(',')))
for i in range(int(max(rebra2))+1):
    if rebra2.count(i)%2!=0:
        global eiler
        eiler+=1
for i in rebra:
    if i[0] in G:
        G[i[0]].append(i[1])
        degree[i[0]]+=1
    else:
        G[i[0]]=[i[1]]
        degree[i[0]]=1
    if i[1] in G:
        G[i[1]].append(i[0])
        degree[i[1]]+=1
    else:
        G[i[1]]=[i[0]]
        degree[i[1]]=1
dfs(G,visited,rebra2[0])
if len(G)-len(visited)!=0:
    eiler+=100

if eiler>2:
    print('False')
else:
    print('True')