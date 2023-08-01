# Имопрт всех необходимых модулей
import pygame  # Модуль рандома для расположения яблока
import random  # Модуль pygame для формирования и вывода изображения
from os import path  # Модуль path из os для расположения изображений

img_dir = path.join(path.dirname(__file__), 'img')  # Расположение библиотеки с изображениями

WIDTH = 512  # Высота окна
HEIGHT = 640  # Ширина окна
FPS = 30  # Частота обновления окна
tile_time = 200  # Время между созданием фрагментов
TURNS = ((0, -32), (-32, 0), (0, 32), (32, 0))  # Картеж расстояний при перемещении
grid_X = WIDTH // 32 - 1  # Количество столбцов
grid_Y = HEIGHT // 32 - 1  # Количество строчек
maxScore = (grid_X * grid_Y - 2) * 10  # Максимально возможный счёт - для выигрыша
score = 0  # Счёт игрока
tiles = []  # Список расположения клеток
lastTileDel = True  # Флаг перемещения хвоста - удаление последнего тайла
running = True  # Флаг работы цикла программы
gameOver = True  # Флаг окончания игры и меню запуска
winning = False  # Флаг выигрыша

# Инициализация модуля pygame
pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Snake on pygame")
clock = pygame.time.Clock()
font_name = pygame.font.match_font('arial')  # Шрифт для текста


# Функции
def draw_text(text, size, x, y):  # Функция отрисовки текста
    font = pygame.font.Font(font_name, size)
    text_surface = font.render(text, True, (0, 0, 0))
    text_rect = text_surface.get_rect()
    text_rect.center = (x, y)
    screen.blit(text_surface, text_rect)


def load_screen():  # Функция загрузочного экрана
    waiting = True  # Флаг работы экрана ожидания начала
    global score
    global winning
    if winning:  # Отрисовка текста экрана победы
        draw_text("You win!", 22, int(WIDTH / 2), int(HEIGHT / 2))
    else:  # Отрисовка текста обычного экрана
        draw_text("Snake on pygame", 22, int(WIDTH / 2), int(HEIGHT / 2))
    draw_text("Press any key to begin", 18, int(WIDTH / 2), int(HEIGHT * 3 / 4))
    pygame.display.flip()  # Отрисовка текста на экран
    tiles.clear()  # Очистка списка тайлов для коллизий
    last = pygame.time.get_ticks()
    while waiting:
        # Держим цикл на правильной скорости
        clock.tick(FPS)
        # Ввод процесса (события)
        for qur_event in pygame.event.get():
            # Проверка для закрытия окна
            if qur_event.type == pygame.QUIT:
                global running
                running = False  # Остановка окна игры
                waiting = False  # Остановка экрана ожидания
                break

            if ((qur_event.type == pygame.KEYUP) and
                    (pygame.time.get_ticks() - last > 200)):
                waiting = False  # Остановка экрана ожидания 
                global gameOver
                gameOver = False  # Запуск хода игры
                break

    # Очищаем списки объектов
    snake.clear()
    all_sprites.empty()
    # Добавление игровых объектов
    all_sprites.add(player)
    all_sprites.add(apple)

    # Обнуляем координаты головы
    player.rect.center = (WIDTH // 2 - 16, HEIGHT // 2 - 48)  # (X, Y)
    player.turn = 0  # Поворот головы
    player.rot = 0  # Направление следующего поворота
    player.last_update = pygame.time.get_ticks()  # Время последнего обновления

    # Создание изначальной змейки
    for i in range(3):
        player.move()  # Перемещение головы для создания начальной змеи
    # Преобразование последнего тайла в хвост
    snake[0].image = pygame.transform.scale(IMG_end, (32, 32))
    snake[0].image = pygame.transform.rotate(snake[0].image, 90 * snake[0].ang)

    apple.eat()  # Размещение яблока
    score = 0  # Обнуление игрового счёта
    winning = False


# Класс управляемой головы
class Head(pygame.sprite.Sprite):
    def __init__(self):
        pygame.sprite.Sprite.__init__(self)
        # Загрузка вариантов спрайтов головы
        # Основное изображение головы - Прямое
        self.image1 = pygame.transform.scale(IMG_head_straight, (32, 32))
        # Второе изображение головы - Поворот налево
        self.image2 = pygame.transform.scale(IMG_head_left, (32, 32))
        # Третье изображение головы - Поворот направо
        self.image3 = pygame.transform.scale(IMG_head_right, (32, 32))

        self.image = self.image1  # Выбор 1 изображения головы
        self.rect = self.image.get_rect()
        self.turn = 0  # Изменение движение по x
        # 0 - Вверх, 1 - вправо, 2 - вниз, 3 - влево
        self.last_update = 0  # Время последнего обновления
        self.rot = 0  # Изначальный поворот
        self.fat = False  # Состояние расширенного тайла

    def update(self):  # Обновление 
        # Обработка поворотов от нажатия клавиш
        key_press = pygame.key.get_pressed()
        if self.rot % 2 == 0:
            if key_press[pygame.K_a] or key_press[pygame.K_LEFT]:
                self.turn = 1
            if key_press[pygame.K_d] or key_press[pygame.K_RIGHT]:
                self.turn = 3
        else:
            if key_press[pygame.K_w] or key_press[pygame.K_UP]:
                self.turn = 0
            if key_press[pygame.K_s] or key_press[pygame.K_DOWN]:
                self.turn = 2
        # Поворот головы в зависимости от нажатия
        if self.rot == self.turn:
            self.image = pygame.transform.rotate(self.image1, 90 * self.turn)
        elif (self.rot - self.turn == -1) or (self.rot - self.turn == 3):
            self.image = pygame.transform.rotate(self.image2, 90 * self.turn)
        else:
            self.image = pygame.transform.rotate(self.image3, 90 * self.turn)

    def move(self):
        # Перемещение головы в зависимости от поворота
        next_pos = ((self.rect.centerx + TURNS[self.turn][0]), (self.rect.centery + TURNS[self.turn][1]))
        # Проверка коллизий
        if ((next_pos in tiles)
                or (next_pos[0] < 0) or (next_pos[0] > WIDTH)
                or (next_pos[1] < 0) or (next_pos[1] > HEIGHT)):
            global gameOver
            gameOver = True  # Меню загрузки
            global lastTileDel
            lastTileDel = False  # Не перемещаем хвост, если врезались

        else:  # Изменяем координату только если не врезались
            # Создание нового фрагмента змеи
            # тип фрагмента 1 - поворот на лево, 0 - прямо, -1 - право
            tile = Tile(self.turn, self.rect.centerx, self.rect.centery,
                        self.turn - self.rot, self.fat)
            all_sprites.add(tile)
            snake.append(tile)
            tiles.append(self.rect.center)

            self.rect.center = next_pos  # Изменение координаты головы
            self.rot = self.turn  # Изменение поворота головы

            if next_pos == apple.rect.center:  # Проверка съедания яблока
                apple.eat()  # Перемещение яблока на новое место
                self.fat = True
                # Проверка выигрыша
                if score >= maxScore:
                    # global gameOver
                    gameOver = True  # Меню загрузки
                    # global lastTileDel
                    lastTileDel = False  # Не перемещаем хвост, если врезались
                    global winning
                    winning = True  # флаг надписи о выигрыше
            else:
                self.fat = False


class Tile(pygame.sprite.Sprite):  # Класс элемента змейки
    def __init__(self, ang, x, y, typ, fat):
        pygame.sprite.Sprite.__init__(self)
        # Выбор необходимой картинки
        if typ == 1 or typ == -3:  # Поворот налево
            self.image = pygame.transform.scale(IMG_turn_left, (32, 32))
        elif typ == 0:  # Поворот направо
            if fat:
                self.image = pygame.transform.scale(IMG_tors_fat, (32, 32))
            else:
                self.image = pygame.transform.scale(IMG_tors_straight, (32, 32))

        else:  # Прямой фрагмент
            self.image = pygame.transform.scale(IMG_turn_right, (32, 32))

        # Отрисовка выбранного изображения
        self.image.set_colorkey((255, 255, 255))
        self.image = pygame.transform.rotate(self.image, 90 * ang)
        self.rect = self.image.get_rect()
        self.rect.center = [x, y]  # Установка необходимых координат
        self.ang = ang  # Установка необходимого угла поворота


class Item(pygame.sprite.Sprite):  # Класс предмета на поле
    def __init__(self):
        pygame.sprite.Sprite.__init__(self)
        self.image = pygame.transform.scale(IMG_apple, (32, 32))
        self.image.set_colorkey((255, 255, 255))
        self.rect = self.image.get_rect()

    def eat(self):  # Съедание яблока
        # Перемещение яблока на новое случайное место
        x = random.randint(0, grid_X) * 32 + 16
        y = random.randint(0, grid_Y) * 32 + 16
        while ((x, y) in tiles) or ((x, y) in player.rect.center):
            x = random.randint(0, grid_X) * 32 + 16
            y = random.randint(0, grid_Y) * 32 + 16
        self.rect.center = (x, y)
        global lastTileDel
        lastTileDel = False  # Не перемещаем хвост
        global score
        score += 10  # Прибавление счёта


# Загрузка графики
IMG_head_straight = pygame.image.load(path.join(img_dir, "Snake_head1.png")).convert_alpha()  # Голова
IMG_head_left = pygame.image.load(path.join(img_dir, "Snake_head_turnL.png")).convert_alpha()  # Голова, налево
IMG_head_right = pygame.image.load(path.join(img_dir, "Snake_head_turnR.png")).convert_alpha()  # Голова, напрво
IMG_tors_straight = pygame.image.load(path.join(img_dir, "Snake_Torso.png")).convert_alpha()  # Прямой фрагмент
IMG_tors_fat = pygame.image.load(path.join(img_dir, "Snake_Torso_fat.png")).convert_alpha()  # Прямой с яблоком
IMG_turn_left = pygame.image.load(path.join(img_dir, "Snake_TurningLeft.png")).convert_alpha()  # Поворот налево
IMG_turn_right = pygame.image.load(path.join(img_dir, "Snake_TurningRight.png")).convert_alpha()  # Поворот направо
IMG_end = pygame.image.load(path.join(img_dir, "Snake_End.png")).convert_alpha()  # Конечный элемент
IMG_apple = pygame.image.load(path.join(img_dir, "Apple.png")).convert_alpha()  # Яблоко
IMG_background = pygame.image.load(path.join(img_dir, "Background.png")).convert_alpha()  # Фон

# Создание объектов на экране
all_sprites = pygame.sprite.Group()  # Создание массива спрайтов
snake = []  # Массив элементов тела змеи
background_rect = IMG_background.get_rect()  # Создание прямоугольника заднего фона
player = Head()  # Создание объекта игрок
apple = Item()  # Создание объекта яблоко

last_update = pygame.time.get_ticks()  # Задаём последний момент времени обновления тайлов

# Цикл игры
while running:
    # Держим цикл на правильной скорости
    clock.tick(FPS)
    # Ввод процесса (события)
    for event in pygame.event.get():
        # проверка для закрытия окна
        if event.type == pygame.QUIT:
            running = False
        # Рестарт на кнопку r
        keyPress = pygame.key.get_pressed()
        if keyPress[pygame.K_r]:
            gameOver = True
            break

    all_sprites.update()  # Обновление спрайтов

    # Проверка необходимости перемещения
    now = pygame.time.get_ticks()
    if now - last_update > tile_time:
        last_update = now  # Устанавливаем последний момент обновления на сейчас
        tiles.pop(0)  # Убираем тайл из списка для коллизий
        player.move()  # Перемещение головы

        if lastTileDel:  # Если нужно перемещать хвост (кроме случаев коллизии или съедания яблока)
            # Убираем последний тайл
            all_sprites.remove(snake[0])  # Убираем из списка спрайтов для отрисовки
            snake[0].kill()  # Уничтожаем элемент как спрайт
            snake.pop(0)  # Убираем из списка классов

            # Преобразуем последний тайл в конец змейки
            snake[0].image = pygame.transform.scale(IMG_end, (32, 32))
            snake[0].image = pygame.transform.rotate(snake[0].image, 90 * snake[0].ang)

        else:  # Иначе восстанавливаем значения
            lastTileDel = True  # Восстанавливаем удаление тайла для следующего хода
            tiles.insert(0, snake[0].rect.center)  # Возращаем тайл коллизий

    # Рендеринг
    screen.blit(IMG_background, background_rect)  # Отрисовка заднего фона
    all_sprites.draw(screen)  # Отрисовываем спрайты на экране
    draw_text(str(score), 18, int(WIDTH / 2), 10)  # Написание счёта на экране
    pygame.display.flip()  # После отрисовки всего, переворачиваем экран

    if gameOver:
        load_screen()  # Экран рестарта

pygame.quit()
