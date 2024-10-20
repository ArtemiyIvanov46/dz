from tkinter import *
from random import randint

WIDTH = 1600
HEIGHT = 900


class Ball:
    def __init__(self):
        self.R = randint(10, 50)
        self.x = randint(self.R, WIDTH - self.R)
        self.y = randint(self.R, HEIGHT - self.R)
        self.dx, self.dy = (10, 10)
        self.ball_id = canvas.create_oval(self.x - self.R,
                                     self.y - self.R,
                                     self.x + self.R,
                                     self.y + self.R, fill="green")

    def move(self):
        self.x += self.dx
        self.y += self.dy
        if self.x + self.R > WIDTH or self.x - self.R <= 0:
            self.dx = -self.dx
        if self.y + self.R > HEIGHT or self.y - self.R <= 0:
            self.dy = -self.dy

    def show(self):
        canvas.move(self.ball_id, self.dx, self.dy)


def click_handler(event):
    global balls
    balls.append(Ball())
def tick():
    for ball in balls:
        ball.move()
        ball.show()
    root.after(50, tick)


root = Tk()
root.geometry(f'{WIDTH}x{HEIGHT}')
canvas = Canvas(root)
canvas.grid(column=0, row=0, sticky=(N,S,W,E))
root.columnconfigure(0, weight=1)
root.rowconfigure(0,weight=1)
canvas.bind('<Button-1>', click_handler)
balls = [Ball() for i in range(5)]
tick()
root.mainloop()