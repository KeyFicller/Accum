
cmake_minimum_required(VERSION 3.15)

project(Accum VERSION 0.0.1 LANGUAGES CXX)

# set the c++ standard of the project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# set the global configurations
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

# set the export directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# set the project directories
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(INCLUDE_DIR ${PROJECT_ROOT}/include)
set(MODULE_DIR ${PROJECT_ROOT}/module)

add_subdirectory(module)
add_subdirectory(test)