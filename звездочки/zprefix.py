alphabet = 'abcdefghijklmnopqrstuvwxyz'


def prefix(s):
    p = [0] * len(s)
    for i in range(1, len(s)):
        k = p[i - 1]
        while k > 0 and s[k] != s[i]:
            k = p[k - 1]
        if s[k] == s[i]:
            k += 1
        p[i] = k
    return p


def z_function(S):
    zf = [0] * len(S)
    left, right = 0, 0
    for i in range(1, len(S)):
        zf[i] = max(0, min(zf[i - left], right - i))
        while i + zf[i] < len(S) and S[zf[i]] == S[i + zf[i]]:
            zf[i] += 1
        if i + zf[i] > right:
            left, right = i, i + zf[i]
    return zf


alphabet = 'abcdefghijklmnopqrstuvwxyz'
variant = input()
word = list(map(int, input().split()))
# если на ввод подается префикс функция
if variant == 'prefix':
    otvet = []
    perfecto = word
    boombl4 = 0
    bit = 0
    for simple in perfecto:
        if simple == 0 and bit == 0:
            otvet.append(alphabet[boombl4])
            boombl4 += 1
        if simple == 0 and bit != 0:
            for electronic in range(bit):
                otvet.append(otvet[electronic])
            bit = 0
            otvet.append(alphabet[boombl4])
            boombl4 += 1
        if simple != 0:
            bit = simple
    if bit != 0:
        for electronic in range(bit):
            otvet.append(otvet[electronic])
    print(z_function(''.join(otvet)))
# если подается z функция
elif variant == 'z':
    alphabet = 'abcdefghijklmnopqrstuvwxyz'
    otvet = []
    ZZZ = word
    n = 0
    w = 0
    for i in ZZZ:
        if i == 0 and w != 0:
            w -= 1
        if i == 0 and w == 0:
            otvet.append(alphabet[n])
            n += 1
        elif ((i == 1) and (w == 0)):
            otvet.append(otvet[0])
            w += 1
        elif (i > 1 and w == 0):
            for j in range(i):
                otvet.append(otvet[j])
            w += i
    print(prefix(''.join(otvet)))
else:
    print(':(')