add_library(
	lib-stream
	STATIC
)

target_sources(
	lib-stream
	PRIVATE
		BoardBuilder.cpp
		BoardBuilder.h
		Conversion.cpp
		Conversion.h
		StreamSupport.cpp
		StreamSupport.h
	PUBLIC
		StreamLib.h
)

target_link_libraries(
	lib-stream
	PRIVATE
		lib-board
)