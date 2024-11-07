from random import randint
from math import *

gravitational_constant = 6.67408E-11
"""Гравитационная постоянная Ньютона G"""


class Star():
    """Тип данных, описывающий звезду.
    Содержит массу, координаты, скорость звезды,
    а также визуальный радиус звезды в пикселах и её цвет.
    """
    type = "star"
    """Признак объекта звезды"""
    m = 0
    """Масса звезды"""
    x = 0
    """Координата по оси **x**"""
    y = 0
    """Координата по оси **y**"""
    Vx = 0
    """Скорость по оси **x**"""
    Vy = 0
    """Скорость по оси **y**"""
    Fx = 0
    """Сила по оси **x**"""
    Fy = 0
    """Сила по оси **y**"""
    R = 5
    """Радиус звезды"""
    color = "red"
    """Цвет звезды"""
    image = None
    """Изображение звезды"""


class Planet():
    """Тип данных, описывающий планету.
    Содержит массу, координаты, скорость планеты,
    а также визуальный радиус планеты в пикселах и её цвет
    """
    type = "planet"
    """Признак объекта планеты"""
    m = 0
    """Масса планеты"""
    x = 0
    """Координата по оси **x**"""
    y = 0
    """Координата по оси **y**"""
    Vx = 0
    """Скорость по оси **x**"""
    Vy = 0
    """Скорость по оси **y**"""
    Fx = 0
    """Сила по оси **x**"""
    Fy = 0
    """Сила по оси **y**"""
    R = 5
    """Радиус планеты"""
    color = "green"
    """Цвет планеты"""
    image = None
    """Изображение планеты"""


w = alpha = 0


def calculate_force(body, space_objects):
    """Вычисляет силу, действующую на тело.
    Параметры:
    **body** — тело, для которого нужно вычислить дейстующую силу.
    **space_objects** — список объектов, которые воздействуют на тело.
    """
    global w
    global alpha
    body.Fx = body.Fy = 0
    for obj in space_objects:
        if body != obj:
            body.Fx += (gravitational_constant * body.m * obj.m * (obj.x - body.x) / (
                        ((obj.x - body.x) ** 2 + (obj.y - body.y) ** 2) ** 0.5)) / (
                                   (obj.x - body.x) ** 2 + (obj.y - body.y) ** 2)
            body.Fy += (gravitational_constant * body.m * obj.m * (obj.y - body.y) / (
                        ((obj.x - body.x) ** 2 + (obj.y - body.y) ** 2) ** 0.5)) / (
                                   (obj.x - body.x) ** 2 + (obj.y - body.y) ** 2)
            if (body.x ** 2 + body.y ** 2) == 0:
                w = 0
            else:
                w = (((body.Vx ** 2 + body.Vy ** 2)) / ((body.x ** 2 + body.y ** 2))) ** 0.5


tiiime = 1


def move_space_object(body, dt):
    """Перемещает тело в соответствии с действующей на него силой.
    Параметры:
    **body** — тело, которое нужно переместить.
    """
    ax = body.Fx / body.m
    body.Vx += ax * dt
    body.x += body.Vx * dt
    ay = body.Fy / body.m
    body.y += body.Vy * dt
    body.Vy += ay * dt
    '''zhitь ( ͡ಥ ͜ʖ ͡ಥ)'''


def recalculate_space_objects_positions(space_objects, dt):
    """Пересчитывает координаты объектов.
    Параметры:
    **space_objects** — список оьъектов, для которых нужно пересчитать координаты.
    **dt** — шаг по времени
    """
    for body in space_objects:
        calculate_force(body, space_objects)
    for body in space_objects:
        move_space_object(body, dt)


if __name__ == "__main__":
    print("This module is not for direct call!")
header_font = "Arial-16"
"""Шрифт в заголовке"""
window_width = 800
"""Ширина окна"""
window_height = 600
"""Высота окна"""
scale_factor = None
"""Масштабирование экранных координат по отношению к физическим.
Тип: float
Мера: количество пикселей на один метр."""


def calculate_scale_factor(max_distance):
    """Вычисляет значение глобальной переменной **scale_factor** по данной характерной длине"""
    global scale_factor
    scale_factor = 0.4 * min(window_height, window_width) / max_distance
    print('Scale factor:', scale_factor)


def scale_x(x):
    """Возвращает экранную **x** координату по **x** координате модели.
    Принимает вещественное число, возвращает целое число.
    В случае выхода **x** координаты за пределы экрана возвращает
    координату, лежащую за пределами холста.
    Параметры:
    **x** — x-координата модели.
    """
    return int(x * scale_factor) + window_width // 2


def scale_y(y):
    """Возвращает экранную **y** координату по **y** координате модели.
    Принимает вещественное число, возвращает целое число.
    В случае выхода **y** координаты за пределы экрана возвращает
    координату, лежащую за пределами холста.
    Направление оси развёрнуто, чтобы у модели ось **y** смотрела вверх.
    Параметры:
    **y** — y-координата модели.
    """
    return int(-y * scale_factor) + window_height // 2


def create_star_image(space, star):
    """Создаёт отображаемый объект звезды.
    Параметры:
    **space** — холст для рисования.
    **star** — объект звезды.
    """
    x = scale_x(star.x)
    y = scale_y(star.y)
    r = star.R
    star.image = space.create_oval([x - r, y - r], [x + r, y + r], fill=star.color)


def create_planet_image(space, planet):
    """Создаёт отображаемый объект планеты.
    Параметры:
    **space** — холст для рисования.
    **planet** — объект планеты.
    """
    x = scale_x(planet.x)
    y = scale_y(planet.y)
    r = planet.R
    planet.image = space.create_oval([x - r, y - r], [x + r, y + r], fill=planet.color)


def update_system_name(space, system_name):
    """Создаёт на холсте текст с названием системы небесных тел.
    Если текст уже был, обновляет его содержание.
    Параметры:
    **space** — холст для рисования.
    **system_name** — название системы тел.
    """
    space.create_text(30, 80, tag="header", text=system_name, font=header_font)


def update_object_position(space, body):
    """Перемещает отображаемый объект на холсте.
    Параметры:
    **space** — холст для рисования.
    **body** — тело, которое нужно переместить.
    """
    x = scale_x(body.x)
    y = scale_y(body.y)
    r = body.R
    if x + r < 0 or x - r > window_width or y + r < 0 or y - r > window_height:
        space.coords(body.image, window_width + r, window_height + r,
                     window_width + 2 * r, window_height + 2 * r)  # положить за пределы окна
    space.coords(body.image, x - r, y - r, x + r, y + r)


if __name__ == "__main__":
    print("This module is not for direct call!")


# раскомментируйте строку ниже
# from solar_physics import *
def read_space_objects_data_from_file(input_filename):
    """Cчитывает данные о космических объектах из файла, создаёт сами объекты
    и вызывает создание их графических образов
    Параметры:
    **input_filename** — имя входного файла
    """
    objects = []
    with open(input_filename) as input_file:
        for line in input_file:
            if len(line.strip()) == 0 or line[0] == '#':
                continue  # пустые строки и строки-комментарии пропускаем
            object_type = line.split()[0].lower()
            if object_type == "star":
                star = Star()
                parse_star_parameters(line, star)
                objects.append(star)
            elif object_type == "planet":
                planet = Planet()
                parse_planet_parameters(line, planet)
                objects.append(planet)
            else:
                print("Unknown space object")
    return objects


def parse_star_parameters(line, star):
    """Считывает данные о звезде из строки.
    Входная строка должна иметь слеюущий формат:
    Star <радиус в пикселах> <цвет> <масса> <x> <y> <Vx> <Vy>
    Здесь (x, y) — координаты зведы, (Vx, Vy) — скорость.
    Пример строки:
    Star 10 red 1000 1 2 3 4
    Параметры:
    **line** — строка с описание звезды.
    **star** — объект звезды.
    """
    tokens = line.split()
    assert (tokens[0].lower() == 'star')
    assert (len(tokens) == 8)
    star.R = int(tokens[1])
    star.color = tokens[2]
    star.m = float(tokens[3])
    star.x = float(tokens[4])
    star.y = float(tokens[5])
    star.Vx = float(tokens[6])
    star.Vy = float(tokens[7])


def parse_planet_parameters(line, planet):
    """Считывает данные о планете из строки.
    Входная строка должна иметь следующий формат:
    Planet <радиус в пикселах> <цвет> <масса> <x> <y> <Vx> <Vy>
    Здесь (x, y) — координаты планеты, (Vx, Vy) — скорость.
    Пример строки:
    Planet 10 red 1000 1 2 3 4
    Параметры:
    **line** — строка с описание планеты.
    **planet** — объект планеты.
    """
    tokens = line.split()
    assert (tokens[0].lower() == 'planet')
    assert (len(tokens) == 8)
    planet.R = int(tokens[1])
    planet.color = tokens[2]
    planet.m = float(tokens[3])
    planet.x = float(tokens[4])
    planet.y = float(tokens[5])
    planet.Vx = float(tokens[6])
    planet.Vy = float(tokens[7])


def write_space_objects_data_to_file(output_filename, space_objects):
    """Сохраняет данные о космических объектах в файл.
    Строки должны иметь следующий формат:
    Star <радиус в пикселах> <цвет> <масса> <x> <y> <Vx> <Vy>
    Planet <радиус в пикселах> <цвет> <масса> <x> <y> <Vx> <Vy>
    Параметры:
    **output_filename** — имя входного файла
    **space_objects** — список объектов планет и звёзд
    """
    with open(output_filename, 'w') as out_file:
        for obj in space_objects:
            print(out_file, "%s %d %s %f" % ('1', 2, '3', 4.5))


if __name__ == "__main__":
    print("This module is not for direct call!")
import tkinter
from tkinter.filedialog import *

# раскомментируйте три строки ниже
# from solar_visuals import *
# from solar_physics import *
# from solar_read import *
perform_execution = False
"""Флаг цикличности выполнения расчёта"""
physical_time = 0
"""Физическое время от начала расчёта.
Тип: float"""
displayed_time = None
"""Отображаемое на экране время.
Тип: переменная tkinter"""
time_step = None
"""Шаг по времени при моделировании.
Тип: float"""
space_objects = []
"""Список космических объектов."""


def execution():
    """Функция исполнения -- выполняется циклически, вызывая обработку всех небесных тел,
    а также обновляя их положение на экране.
    Цикличность выполнения зависит от значения глобальной переменной perform_execution.
    При perform_execution == True функция запрашивает вызов самой себя по таймеру через от 1 мс до 100 мс.
    """
    global physical_time
    global displayed_time
    recalculate_space_objects_positions(space_objects, time_step.get())
    for body in space_objects:
        update_object_position(space, body)
    physical_time += time_step.get()
    displayed_time.set("%.1f" % physical_time + " seconds gone")
    if perform_execution:
        space.after(101 - int(time_speed.get()), execution)


def start_execution():
    """Обработчик события нажатия на кнопку Start.
    Запускает циклическое исполнение функции execution.
    """
    global perform_execution
    perform_execution = True
    start_button['text'] = "Pause"
    start_button['command'] = stop_execution
    execution()
    print('Started execution...')


def stop_execution():
    """Обработчик события нажатия на кнопку Start.
    Останавливает циклическое исполнение функции execution.
    """
    global perform_execution
    perform_execution = False
    start_button['text'] = "Start"
    start_button['command'] = start_execution
    print('Paused execution.')


def open_file_dialog():
    """Открывает диалоговое окно выбора имени файла и вызывает
    функцию считывания параметров системы небесных тел из данного файла.
    Считанные объекты сохраняются в глобальный список space_objects
    """
    global space_objects
    global perform_execution
    perform_execution = False
    for obj in space_objects:
        space.delete(obj.image)  # удаление старых изображений планет
    in_filename = askopenfilename(filetypes=(("Text file", ".txt"),))
    space_objects = read_space_objects_data_from_file(in_filename)
    max_distance = max([max(abs(obj.x), abs(obj.y)) for obj in space_objects])
    calculate_scale_factor(max_distance)
    for obj in space_objects:
        if isinstance(obj, Star):
            create_star_image(space, obj)
        elif isinstance(obj, Planet):
            create_planet_image(space, obj)
        else:
            raise AssertionError()


def save_file_dialog():
    """Открывает диалоговое окно выбора имени файла и вызывает
    функцию считывания параметров системы небесных тел из данного файла.
    Считанные объекты сохраняются в глобальный список space_objects
    """
    out_filename = asksaveasfilename(filetypes=(("Text file", ".txt"),))
    write_space_objects_data_to_file(out_filename, space_objects)


def main():
    """Главная функция главного модуля.
    Создаёт объекты графического дизайна библиотеки tkinter: окно, холст, фрейм с кнопками, кнопки.
    """
    global physical_time
    global displayed_time
    global time_step
    global time_speed
    global space
    global start_button
    print('Modelling started!')
    physical_time = 0
    root = tkinter.Tk()
    # космическое пространство отображается на холсте типа Canvas
    space = tkinter.Canvas(root, width=window_width, height=window_height, bg="black")
    space.pack(side=tkinter.TOP)
    # нижняя панель с кнопками
    frame = tkinter.Frame(root)
    frame.pack(side=tkinter.BOTTOM)
    start_button = tkinter.Button(frame, text="Start", command=start_execution, width=6)
    start_button.pack(side=tkinter.LEFT)
    time_step = tkinter.DoubleVar()
    time_step.set(1)
    time_step_entry = tkinter.Entry(frame, textvariable=time_step)
    time_step_entry.pack(side=tkinter.LEFT)
    time_speed = tkinter.DoubleVar()
    scale = tkinter.Scale(frame, variable=time_speed, orient=tkinter.HORIZONTAL)
    scale.pack(side=tkinter.LEFT)
    load_file_button = tkinter.Button(frame, text="Open file...", command=open_file_dialog)
    load_file_button.pack(side=tkinter.LEFT)
    save_file_button = tkinter.Button(frame, text="Save to file...", command=save_file_dialog)
    save_file_button.pack(side=tkinter.LEFT)
    displayed_time = tkinter.StringVar()
    displayed_time.set(str(physical_time) + " seconds gone")
    time_label = tkinter.Label(frame, textvariable=displayed_time, width=30)
    time_label.pack(side=tkinter.RIGHT)
    root.mainloop()
    print('Modelling finished!')


if __name__ == "__main__":
    main()