# Make Catch2 available for this project
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.0-preview3
)

FetchContent_MakeAvailable(Catch2)

# The line below is necessary when obtaining Catch2 via FetchContent.
# For more info check https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md 
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

add_executable(test-labyrinth)

target_sources(
	test-labyrinth
	PRIVATE
		board/BoardTest.cpp
		board/CellTest.cpp
		board/DirectionTest.cpp
		stream/BoardBuilderTest.cpp
		stream/StreamSupportTest.cpp
		stream/ConversionTest.cpp
		solver/SolverFactoryTest.cpp
		solver/SimpleSolverTest.cpp
 )

target_link_libraries(
	test-labyrinth
	PRIVATE
		Catch2::Catch2WithMain
		lib-board
		lib-stream
		lib-solver
)

add_test(test-all test-labyrinth)

include(CTest)
include(Catch)
catch_discover_tests(test-labyrinth)
