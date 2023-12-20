cmake_minimum_required(VERSION 3.24.1)
project(unpvnote)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)
add_subdirectory(libfree)
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
        lib
        libfree)
