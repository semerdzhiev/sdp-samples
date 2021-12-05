add_library(
	lib-solver
	STATIC
)

target_sources(
	lib-solver
	PRIVATE
		Backlog.h
		SimpleSolver.h
		Solver.h
		SolverFactory.cpp
		SolverFactory.h
	PUBLIC
		SolverLib.h
)

target_link_libraries(
	lib-solver
	PRIVATE
		lib-board
		lib-stream
)