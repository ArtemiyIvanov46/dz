class Node:
    def __init__(self,val = None):
        self.val = val
        self.left = None
        self.right = None

class Deque:
    def __init__(self):
        self.head = None
        self.tail = None
    def add(self,val):
        node = Node(val)
        if not self.head:
            self.head = node
            self.tail = node
        else:
            self.tail.right = node
            self.tail = node
    def remove(self):
        if not self.head:
            print('Empty')
            return None
        res = self.head.val
        self.head = self.head.right
        return res

M=int(input())
queue = Deque()
G={}

for i in range(M):
    v1,v2,w=input().split()
    w=int(w)
    if v1 in G:
        G[v1][v2]=w
    else:
        G[v1]={v2:w}
    if v2 in G:
        G[v2][v1]=0
    else:
        G[v2]={v1:0}
def dfs(G,start,finish,visited,f_min):
    if start==finish:
        return f_min
    visited.add(start)
    for v in G[start]:
        if (v not in visited and G[start][v]>0):
            flow=dfs(G,v,finish,visited,min(f_min,G[start][v]))
            G[start][v]-=flow
            G[v][start]+=flow
            if flow>0:
                return flow
    return 0

def bfs(G,queue,start,finish,visited,f_min):
    parents={i:None for i in G}
    flow=0
    queue.add(start)
    visited.append(start)
    while queue.head:
        current = queue.remove()
        for i in G[current]:
            if (i not in visited and G[current][i]>0):
                parents[i]=current
                if i==finish:
                    while parents[i]:
                        f_min=min(f_min,G[parents[i]][i])
                        G[parents[i]][i]-=f_min
                        G[i][parents[i]]+=f_min
                        i=parents[i]
                    flow+=f_min
                queue.add(i)
                visited.append(i)
    return flow


def ford_fulkerson(G,start,finish):
    visited=[]
    res=0
    while (flow:=bfs(G,queue,start,finish,visited,float('inf')))!=0:
        res+=flow
        visited=[]
    return res
print(ford_fulkerson(G,'1','3'))
