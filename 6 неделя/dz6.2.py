from tkinter import *
from tkinter import ttk
def calculate(*argc):
    b=command.get()
    a=list(map(float,b.split()))
    if ((list(map(float,b.split()))[0])/(list(map(float,b.split()))[1])**2)>=30:
       result.set('='+str((list(map(float,b.split()))[0])/(list(map(float,b.split()))[1])**2)+'  obesity')
    elif ((list(map(float,b.split()))[0])/(list(map(float,b.split()))[1])**2)<=16:
       result.set('='+str((list(map(float,b.split()))[0])/(list(map(float,b.split()))[1])**2)+'  lack of weight')
    else:
       result.set('='+str((list(map(float,b.split()))[0])/(list(map(float,b.split()))[1])**2)+'  normal weight')
root=Tk()
root.title('Калькулятор ИМТ')
mainframe=Frame(root)
mainframe.grid(column=0,row=0,sticky=(N,S,W,E))
root.columnconfigure(0,weight=1)
root.rowconfigure(0,weight=1)

command=StringVar()
result=StringVar()
entry=Entry(mainframe, width=10, textvariable=command)
entry.grid(column=1,row=1,sticky=(W))

Label(mainframe,textvariable=result).grid(column=2, row=1, sticky=(W))

Button(mainframe, text='mass,kg height,m', command=calculate).grid(column=1,row=2)
root.bind('<Return>',calculate)
entry.focus()
root.mainloop()