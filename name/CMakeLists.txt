cmake_minimum_required(VERSION 3.24.1)
project(name)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(../lib lib)

target_include_directories(lib PUBLIC ../lib)

add_executable(${PROJECT_NAME} hostent.c)

target_link_libraries(${PROJECT_NAME}
        lib)
