cmake_minimum_required(VERSION 3.27.7)

project(StarFighter
	VERSION 1.0.0
	LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD          14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS       OFF)

# Fetch SFML
include(FetchContent)
# variable
set(SFML_LIB_NAME SFML)

FetchContent_Declare(
	${SFML_LIB_NAME}
	GIT_REPOSITORY https://github.com/SFML/SFML
	GIT_TAG 2.5.1
	GIT_SHALLOW FALSE
)

FetchContent_MakeAvailable(${SFML_LIB_NAME})

# variables
set(STAR_FIGHTER_ENGINE_TARGET_NAME StarFighterEngine)
set(STAR_FIGHTER_GAME_TARGET_NAME StarFighterGame)

add_subdirectory(StarFighterEngine)
add_subdirectory(StarFighterGame)
