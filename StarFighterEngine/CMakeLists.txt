add_library(${STAR_FIGHTER_ENGINE_TARGET_NAME} STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Actor.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Actor.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Application.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Application.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/AssetManager.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/AssetManager.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Core.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Core.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/MathUtility.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/MathUtility.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/main.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/Object.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/Object.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/include/framework/World.h
	${CMAKE_CURRENT_SOURCE_DIR}/src/framework/World.cpp
)

target_include_directories(${STAR_FIGHTER_ENGINE_TARGET_NAME} PUBLIC 
 	${CMAKE_CURRENT_SOURCE_DIR}/include
 )

target_link_libraries(${STAR_FIGHTER_ENGINE_TARGET_NAME} PUBLIC sfml-audio)
target_link_libraries(${STAR_FIGHTER_ENGINE_TARGET_NAME} PUBLIC sfml-graphics)
target_link_libraries(${STAR_FIGHTER_ENGINE_TARGET_NAME} PUBLIC sfml-network)
target_link_libraries(${STAR_FIGHTER_ENGINE_TARGET_NAME} PUBLIC sfml-system)
target_link_libraries(${STAR_FIGHTER_ENGINE_TARGET_NAME} PUBLIC sfml-window)

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
