def Dijkstra(s):
    a = s.split()
    stopka = [0]
    otvet = []
    queue = []
    vaznost = {'-': 0, '+': 1, '/': 2, '*': 3, 0: -100}
    for i in a:
        if i.isdigit():
            otvet.append(i)
        else:
            for j in range(len(stopka)):
                if vaznost[stopka[-(j + 1)]] > vaznost[i]:
                    otvet.append(stopka[-(j + 1)])
                    queue.pop()
                else:
                    stopka.append(i)
                    queue.append(i)
                    break

    for i in queue[::-1]:
        otvet.append(i)
    return (''.join(otvet))


print(Dijkstra('1 + 2 * 3 - 4'))