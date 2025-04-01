add_library(${STAR_FIGHTER_ENGINE_TARGET_NAME} STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/include/main.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Actor.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Actor.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Application.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Application.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/AssetManager.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/AssetManager.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Core.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Core.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Delegate.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Delegate.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/MathUtility.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/MathUtility.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Object.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Object.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/PhysicsSystem.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/PhysicsSystem.cpp
	
	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/TimerManager.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/TimerManager.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/World.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/World.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/gameplay/GameStage.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/gameplay/GameStage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/VFX/Particle.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/VFX/Particle.cpp
)

target_include_directories(${STAR_FIGHTER_ENGINE_TARGET_NAME} PUBLIC 
 	${CMAKE_CURRENT_SOURCE_DIR}/include
 )

include(FetchContent)

# Fetch SFML
# set variable
set(SFML_LIB_NAME SFML)
FetchContent_Declare(
	${SFML_LIB_NAME}
	GIT_REPOSITORY https://github.com/SFML/SFML
	GIT_TAG 2.5.1
	GIT_SHALLOW FALSE
)
FetchContent_MakeAvailable(${SFML_LIB_NAME})

target_link_libraries(${STAR_FIGHTER_ENGINE_TARGET_NAME} PUBLIC sfml-audio)
target_link_libraries(${STAR_FIGHTER_ENGINE_TARGET_NAME} PUBLIC sfml-graphics)
target_link_libraries(${STAR_FIGHTER_ENGINE_TARGET_NAME} PUBLIC sfml-network)
target_link_libraries(${STAR_FIGHTER_ENGINE_TARGET_NAME} PUBLIC sfml-system)
target_link_libraries(${STAR_FIGHTER_ENGINE_TARGET_NAME} PUBLIC sfml-window)



# Fetch BOX2D_LIB_NAME
# set variable
set(BOX2D_LIB_NAME Box2D)
# disable UnitTests
option(BOX2D_BUILD_UNIT_TESTS "Build the Box2D unit tests" OFF)
FetchContent_Declare(
	${BOX2D_LIB_NAME}
	GIT_REPOSITORY https://github.com/erincatto/box2d
	GIT_TAG v2.4.1
	GIT_SHALLOW FALSE
)
FetchContent_MakeAvailable(${BOX2D_LIB_NAME})

target_link_libraries(${STAR_FIGHTER_ENGINE_TARGET_NAME} PUBLIC box2d)


# Function name is CopyLibToTarget. Parameters names of function are LIB_NAME and TARGET_NAME
function(CopyLibToTarget LIB_NAME TARGET_NAME)
	add_custom_command(TARGET ${TARGET_NAME}
	POST_BUILD
	COMMAND
	${CMAKE_COMMAND} -E copy_if_different
	$<TARGET_FILE:${LIB_NAME}>
	$<TARGET_FILE_DIR:${TARGET_NAME}>
	)
endfunction()

CopyLibToTarget(sfml-audio ${STAR_FIGHTER_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-graphics ${STAR_FIGHTER_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-network ${STAR_FIGHTER_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-system ${STAR_FIGHTER_ENGINE_TARGET_NAME})
CopyLibToTarget(sfml-window ${STAR_FIGHTER_ENGINE_TARGET_NAME})

CopyLibToTarget(box2d ${STAR_FIGHTER_ENGINE_TARGET_NAME})
