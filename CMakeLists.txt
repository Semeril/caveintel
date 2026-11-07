cmake_minimum_required(VERSION 3.16)
project(CaveIntel VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(cereal GIT_REPOSITORY https://github.com/USCiLab/cereal.git GIT_TAG v1.3.2)
set(SKIP_PERFORMANCE_COMPARISON ON)
FetchContent_MakeAvailable(cereal)

FetchContent_Declare(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt.git GIT_TAG 12.2.1)
FetchContent_MakeAvailable(fmt)

add_library(caveintel
	src/logger.cpp
	src/network.cpp
	src/backprop.cpp
	src/qnetwork.cpp
)

add_library(caveintel::caveintel ALIAS caveintel)

target_include_directories(caveintel PUBLIC ./include)

target_link_libraries(caveintel PRIVATE fmt::fmt cereal::cereal)

target_compile_options(caveintel PRIVATE -Wall -Wextra -Wpedantic)

add_executable(example examples/main.cpp)

target_link_libraries(example PRIVATE caveintel::caveintel)