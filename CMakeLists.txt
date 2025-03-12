cmake_minimum_required(VERSION 3.27.7)

project(StarFighter
	VERSION 1.0.0
	LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD          14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS       OFF)

# variables
set(STAR_FIGHTER_ENGINE_TARGET_NAME StarFighterEngine)
set(STAR_FIGHTER_GAME_TARGET_NAME StarFighterGame)

add_subdirectory(StarFighterEngine)
add_subdirectory(StarFighterGame)
