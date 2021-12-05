cmake_minimum_required (VERSION 3.13)

project ("Labyrinth Board")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_TESTING "Specifies whether to building the tests" TRUE)

include_directories("${PROJECT_SOURCE_DIR}/src")

add_subdirectory(src/board)
add_subdirectory(src/stream)
add_subdirectory(src/solver)
add_subdirectory(src/app)

if(ENABLE_TESTING)
	enable_testing()
	add_subdirectory(test)
endif()
