project(intro)
include_directories(../lib)

add_library(${PROJECT_NAME} SHARED
        byteorder.c)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/)