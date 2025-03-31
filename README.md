# Diploma thesis
### Star Fighter. Project "Armada"
Final project of the OTUS C++ 2024 course

**Project description:**
A game in the "Space Invaders genre"


**Rules of the game:**
- Kill enemies (get points)
- Dodge oncoming fire and obstacles
- Collect resources
- Kill the boss
- Go to the next level
- Reach the maximum number of points and finish the game :smiley:

**Game elements:**
- Spaceship
- Enemy
- Boss
- Life/Damage
- Weapons (3 types)
- Resources (weapons, lives)
- UI (buttons, text, life bar, lives, points)

**Tech stack:**
- C++ Core
- SFML library
- Box2D
- Cmake
- Git

**Game Engine modules:**
- The game application
- Level (World)
- Actor (Object)
- Assets and resources
- Delegate
- Timer
- Collisions detection

**Subjects implemented in the project:**
- OOP, Encapsulation, Composition, Inheritance, Polymorphism
- Design Patterns and Ideoms: 
  	Singleton: AssetManager, PhysicsSystem
 	Delegation: Delegate
 	Callbacks: Spaceship::OnHealthChanged() and else...
- Templates
- Data Structure
- Smart Pointers
- Exceptions

**Resources:**
- Space Shooter (Redux, plus fonts and sounds) by Kenney Vleugels (www.kenney.nl). License (CC0)

## Controls
- Movement: WASD or Up, Down, Left, Right arrows
- Shooting: Space


## Run on Linux (Ubuntu)
First install some required packeges (if not installed):

**Git**
```bash
sudo add-apt-repository ppa:git-core/ppa
sudo apt update
sudo apt install git
```

**Cmake 3.27.7 or higher**
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
cmake -S . -B build/
cmake --build build/
```

Run the Game:
```bash
./build/StarFighterGame/StarFighterGame 
```

**Have a fan!** :smiley:

## Run on Windows
// TODO
