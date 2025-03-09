import heapq

rebra = []
rebra2 = []
G = {}
degree = {}
M = int(input())
for i in range(M):
    n, k, w = input().split()
    w = float(w)
    if n in G:
        G[n][k] = w
    else:
        G[n] = {k: w}

rebra2 = {i: 0 for i in list(G.keys())}
G['S'] = rebra2


def Bellman(G, start):
    slovar = {i: float('inf') for i in G}
    slovar[start] = 0
    for i in range(len(G) - 1):
        for j in slovar:
            for k in G[j]:
                if slovar[k] > slovar[j] + G[j][k]:
                    slovar[k] = slovar[j] + G[j][k]
    return slovar


belman = (Bellman(G, 'S'))
for i in G:
    for j in G[i]:
        G[i][j] = G[i][j] + belman[i] - belman[j]


def dijkstra(G, start):
    distances = {i: float('infinity') for i in G}
    distances[start] = 0
    h = [(0, start)]
    while h:
        cur_dist, cur_node = heapq.heappop(h)
        if cur_dist > distances[cur_node]:
            continue
        for neighbor in G[cur_node]:
            distance = cur_dist + G[cur_node][neighbor]
            if distance < distances[neighbor]:
                distances[neighbor] = distance
                heapq.heappush(h, (distance, neighbor))
    return distances


del G['S']
STARTUEM = input('start')
print(dijkstra(G, STARTUEM))
