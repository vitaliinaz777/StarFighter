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

**Технологии, которые планируется использовать**
- Библиотека SFML
- Cmake
- Git

**А также самописный игровой движок, который будет состоят из следующих частей:**
- Само приложение игры
- Уровни
- Акторы
- Ассеты и ресурсы
- Делегаты
- Таймер
- Коллизии

**Install on Linux**
Git install:
sudo add-apt-repository ppa:git-core/ppa
sudo apt update
sudo apt install git

Cmake install:
sudo snap install cmake --classic
sudo apt install make

C++ install:
sudo apt install build-essential

Create run  bash script installDeps.sh:

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

Clone repo and build
git clone https://github.com/vitaliinaz777/StarFighter.git
cd StarFighter/
mkdir build
cd build/
cmake -S .. -B .
cmake --build .

Run Game:
./StarFighterGame/StarFighterGame

**Have a fan =)**

