
add_executable(
	labyrinth
)

target_sources(
	labyrinth
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(
	labyrinth
	PRIVATE
		lib-board
		lib-stream
		lib-solver
)
