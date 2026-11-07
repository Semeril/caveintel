cmake_minimum_required(VERSION 3.16)
project(CaveIntel VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(fmt)

add_library(caveintel
	src/logger.cpp
	src/network.cpp
	src/backprop.cpp
	src/qnetwork.cpp
)

add_library(caveintel::caveintel ALIAS caveintel)

target_include_directories(caveintel PUBLIC ./include)

target_link_libraries(caveintel PRIVATE fmt::fmt)

target_compile_options(caveintel PRIVATE -Wall -Wextra -Wpedantic)

add_executable(example examples/main.cpp)

target_link_libraries(example PRIVATE caveintel::caveintel)