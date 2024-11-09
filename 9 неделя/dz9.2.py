def calc(s):
    a=s.split()
    stopka=[]
    for i in a:
        if i.isdigit():
            stopka.append(i)
        else:
            try:
                second=stack.pop()
                first=stack.pop()
            except:
                print('Некорректное выражение')
                return(-1)
            stopka.append(str(eval(first+i+second)))
    return(stack[0])