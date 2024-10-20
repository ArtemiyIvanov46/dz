from random import *
from tkinter import *
from tkinter import ttk
import numpy as np


def selection(*args):
    try:
        value = list(color.get())
        first = list(hex(255 - eval("0x" + ''.join(value[1:3]))))

        second = list(hex(255 - eval("0x" + ''.join(value[3:5]))))

        third = list(hex(255 - eval("0x" + ''.join(value[5:]))))

        complementary.set('#' + ''.join(first[2:]) + ''.join(second[2:]) + ''.join(third[2:]))

    except ValueError:
        pass


root = Tk()
root.title("Selection of colors")

mainframe = ttk.Frame(root, padding="3 3 12 12")
mainframe.grid(column=0, row=0, sticky=(N, W, E, S))
root.columnconfigure(0, weight=1)
root.rowconfigure(0, weight=1)

color = StringVar()
feet_entry = ttk.Entry(mainframe, width=7, textvariable=color)
feet_entry.grid(column=2, row=1, sticky=(W, E))

complementary = StringVar()
ttk.Label(mainframe, textvariable=complementary).grid(column=2, row=2, sticky=(W, E))

ttk.Button(mainframe, text="Подобрать цвет", command=selection).grid(column=2, row=3, sticky=W)

ttk.Label(mainframe, text="Введите Ваш цвет (c #):").grid(column=1, row=1, sticky=W)
ttk.Label(mainframe, text="Комплементарный цвет:").grid(column=1, row=2, sticky=(W, E))

for child in mainframe.winfo_children():
    child.grid_configure(padx=5, pady=5)

feet_entry.focus()

root.bind("<Return>", selection)

root.mainloop()