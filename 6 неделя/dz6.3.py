import pandas as pd

films = pd.read_csv('/Users/rootadmin/Downloads/imdb_top_250.csv')
film_genres_list = list(films['Genre'])
films = list(films['Title'])
# попробуйте посмотреть промежуточный результат в film_list
# print(film_list)

complex_genres = []  # будем хранить составные жанры, чтобы потом их удалить
for film_genre in film_genres_list:
    genres = film_genre.split(' | ')  # разберем каждый составной жанр на составляющие
    if len(genres) > 1:  # если попался составной жанр
        for genre in genres:  # то пройдемся по всем элементарным жанрам фильма
            film_genres_list.append(genre)  # и добавим их
        complex_genres.append(film_genre)
    # обратите внимание, что мы не можем в процессе итерации через for удалять элементы, поскольку это собьет итератор. Можете посмотреть, к чему это приведет, написав вместо complex_genres.append(film_genre) сразу film_genres_list.remove(film_genre)

for genre in complex_genres:
    film_genres_list.remove(genre)  # удалим все составные жанры из списка жанров

genres_set = set(film_genres_list)  # чтобы сделать из этого set! теперь здесь лежат все уникальные элементарные жанры
print(genres_set)

films2 = pd.read_csv('/Users/rootadmin/Downloads/imdb_top_250.csv')
film_genres_list2 = list(films2['Genre'])

goodfilms = []
import random
from tkinter import *
from tkinter import ttk


def film(*argc):
    for i in range(250):
        global films2
        global film_genres_list2
        if (command.get()) in ((film_genres_list2[int(i)]).split('|')):
            print(film_genres_list2[int(i)])
            goodfilms.append(films[int(i)])
    randomfilm = random.choice(goodfilms)
    result.set('you should watch ' + randomfilm)


root = Tk()
root.title('Фильмы')
mainframe = Frame(root)
mainframe.grid(column=0, row=0, sticky=(N, S, W, E))
root.columnconfigure(0, weight=1)
root.rowconfigure(0, weight=1)

command = StringVar()
result = StringVar()
entry = Entry(mainframe, width=10, textvariable=command)
entry.grid(column=1, row=1, sticky=(W))

Label(mainframe, textvariable=result).grid(column=2, row=1, sticky=(W))

Button(mainframe, text='жанр', command=film).grid(column=1, row=2)
root.bind('<Return>', film)
entry.focus()
root.mainloop()