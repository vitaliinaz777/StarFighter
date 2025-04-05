add_executable(${STAR_FIGHTER_GAME_TARGET_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/EnemySpaceship.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/EnemySpaceship.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/TwinBlade.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/TwinBlade.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/Vanguard.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/Vanguard.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/enemy/VanguardStage.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/enemy/VanguardStage.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/gameFramework/GameApplication.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/gameFramework/GameApplication.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/gameplay/HealthComponent.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/gameplay/HealthComponent.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/level/GameLevelOne.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/level/GameLevelOne.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/spaceship/Spaceship.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/spaceship/Spaceship.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/player/PlayerSpaceship.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/player/PlayerSpaceship.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/VFX/Explosion.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/VFX/Explosion.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/Bullet.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/Bullet.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/BulletShooter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/BulletShooter.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/weapon/Shooter.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/weapon/Shooter.cpp
)

target_include_directories(${STAR_FIGHTER_GAME_TARGET_NAME} PUBLIC 
 	${CMAKE_CURRENT_SOURCE_DIR}/include
 )

target_link_libraries(${STAR_FIGHTER_GAME_TARGET_NAME} PUBLIC ${STAR_FIGHTER_ENGINE_TARGET_NAME})

# Function name is CopyLibDirToTarget. Parameters names of function are LIB_NAME and TARGET_NAME
function(CopyLibDirToTarget LIB_NAME TARGET_NAME)
	add_custom_command(TARGET ${TARGET_NAME}
	POST_BUILD
	COMMAND
	${CMAKE_COMMAND} -E copy_directory
	$<TARGET_FILE_DIR:${LIB_NAME}>
	$<TARGET_FILE_DIR:${TARGET_NAME}>
	)
endfunction()

CopyLibDirToTarget(${STAR_FIGHTER_ENGINE_TARGET_NAME} ${STAR_FIGHTER_GAME_TARGET_NAME})

set(RESOURCE_FOLDER_NAME "assets")
set(RESOURCE_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${RESOURCE_FOLDER_NAME}")

add_custom_command(
 	TARGET ${STAR_FIGHTER_GAME_TARGET_NAME}
 	POST_BUILD
 	COMMAND
 	${CMAKE_COMMAND} -E copy_directory
 	${RESOURCE_SRC_DIR}
 	$<TARGET_FILE_DIR:${STAR_FIGHTER_GAME_TARGET_NAME}>/${RESOURCE_FOLDER_NAME}
 )
 
 configure_file(
 	"config.h.in"
 	"${CMAKE_CURRENT_SOURCE_DIR}/include/config.h" ESCAPE_QUOTES
 )
