lists = [1, 0]
listt = [0, 1]
def evclid(a, b):
    r=1
    listr = [a, b]
    while r>0:
        q = listr[-2] // listr[-1]
        r = listr[-2] - listr[-1] * q
        listr.append(r)
        s = lists[-2] - q * lists[-1]
        lists.append(s)
        t = listt[-2] - q * listt[-1]
        listt.append(t)
        if r==0:
            break
    print(f'{(a*lists[-2])+(b*listt[-2])} {lists[-2]} {listt[-2]}')
    return
c=int(input())
d=int(input())
evclid(c,d)