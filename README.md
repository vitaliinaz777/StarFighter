# Дипломная работа
### Star Fighter. Project "Armada"
Финальный проект курса OTUS C++ 2024

**Описание проекта:**
Игра в жанре Space Invaders.

**Правила игры:**
- Убивать противников (зарабатывая при этом очки) 
- Уворачиваться от встречного огня и препятствий
- Собирать ресурсы
- Убить босса
- Перейти на следующий уровень
- Достичь максимального кол-ва очков и закончить игру =)

**Элементы приложения:**
- Космический корабль
- Враг
- Босс
- Жизнь/Урон
- Оружие (3 вида)
- Ресурсы (оружие, жизни)
- UI (кнопки, текст, полоска жизни, жизни, очки)

**Технологии:**
- Библиотека SFML
- Box2D
- Cmake
- Git

**Модули игрового движка:**
- Само приложение игры
- Уровни
- Акторы
- Ассеты и ресурсы
- Делегаты
- Таймер
- Коллизии

**Темы реализованные в проекте:**
- ООП, Инкапслуляция, Полиморфизм
- Паттерны проектирования
- Шаблоны
- Cтруктуры данных
- Умные указатели
- Исключения
- Векторы, Матрицы

## Install on Linux (Ubuntu)
First install some required packeges (if not installed):

**Git**
```bash
sudo add-apt-repository ppa:git-core/ppa
sudo apt update
sudo apt install git
```

**Cmake**
```bash
sudo snap install cmake --classic
sudo apt install make
```

**C++**
```bash
sudo apt install build-essential
```


------------


Then create bash script with dependencies:
*installDependencies.sh*
```bash
sudo apt install -y \
libx11-dev \
libxi-dev \
libxrandr-dev \
libglu1-mesa-dev freeglut3-dev mesa-common-dev \
libudev-dev \
libfreetype6-dev \
libopenal-dev \
libvorbis-dev \
libflac++-dev \
libxinerama-dev \
libxcursor-dev
```
Give it rights and run:
```bash
sudo chmod +x installDependencies.sh:
./installDependencies.sh
```


Clone a repo and build it:
```bash
git clone https://github.com/vitaliinaz777/StarFighter.git
cd StarFighter/
mkdir build
cd build/
cmake -S .. -B .
cmake --build .
```

Run the Game:
```bash
./StarFighterGame/StarFighterGame
```

**Have a fan!** :smiley:
