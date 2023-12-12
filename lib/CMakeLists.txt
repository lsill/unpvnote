project(lib)

add_library(${PROJECT_NAME}
        sock_ntop.c)# SHARED

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/)