cmake_minimum_required(VERSION 4.4.5)
project(CaveIntel VERSION 1 LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
	cereal
	GIT_REPOSITORY
	https://github.com/USCiLab/cereal.git
	GIT_TAG
	v1.3.2
	SYSTEM
)
set(SKIP_PERFORMANCE_COMPARISON ON)
FetchContent_MakeAvailable(cereal)

FetchContent_Declare(
	fmt
	GIT_REPOSITORY
	https://github.com/fmtlib/fmt.git
	GIT_TAG
	12.2.1
	SYSTEM
)
FetchContent_MakeAvailable(fmt)

add_library(caveintel)
add_library(caveintel::caveintel ALIAS caveintel)

target_sources(caveintel
	PRIVATE
	FILE_SET SOURCES
	BASE_DIRS ./src
	FILES
		src/logger.cpp
		src/network.cpp
		src/backprop.cpp
		src/qnetwork.cpp
	PUBLIC
	FILE_SET HEADERS
	BASE_DIRS ./include
	FILES
		./include/caveintel/backprop.hpp
		./include/caveintel/logger.hpp
		./include/caveintel/network.hpp
		./include/caveintel/qnetwork.hpp
)

target_link_libraries(caveintel PRIVATE fmt::fmt cereal::cereal)
target_compile_features(caveintel PRIVATE cxx_std_23)

# example
add_executable(example examples/main.cpp)
target_link_libraries(example PRIVATE caveintel::caveintel)