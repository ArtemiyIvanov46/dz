M = int(input())

G = {}

for i in range(M):
    v1,v2 = input().split()
    if v1 in G:
        G[v1].add(v2)
    else:
        G[v1] = {v2}
    if v2 in G:
        G[v2].add(v1)
    else:
        G[v2] = {v1}


def dfs(G,visited,matching,start):
    if start in visited:
        return False
    visited.add(start)
    for i in G[start]:
        if matching[i]==None or dfs(G,visited,matching,matching[i]):
            matching[i] = start
            matching[start] = i
            return True
    return False

def Kuhn(G):
    matching = {i:None for i in G}
    for i in G:
        visited = set()
        if not matching[i]:
            dfs(G,visited,matching,i)
    return matching
kung=Kuhn(G)
for i in G:
    if kung[i]==None:
        for j in G[i]:
            if kung[j]!=None:
                kung[j]=set(kung[j])
                kung[i]={j}
                kung[j].add(i)
                break
print(kung)