M = int(input())

G = {}

for i in range(M):
    v1, v2, w = input().split()
    w = float(w)
    if v1 in G:
        G[v1][v2] = w
    else:
        G[v1] = {v2: w}


# Алгоритм Беллмана-Форда

def bellman_ford(G, start, a):
    d = {i: float('-inf') for i in G}
    d[start] = 1
    for i in range(len(G) + a):
        for node1 in d:
            for node2 in G[node1]:
                if d[node2] < d[node1] * G[node1][node2]:
                    d[node2] = d[node1] * G[node1][node2]
    return (d)


if (bellman_ford(G, '1', 0)) != (bellman_ford(G, '1', 1)):
    print('Можно')
else:
    print('Нельзя')