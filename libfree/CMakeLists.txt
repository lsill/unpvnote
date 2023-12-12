project(libfree)
include_directories(../lib)
add_library(${PROJECT_NAME}
        inet_nton_ipv4.c
        inet_pton_ipv4.c)# SHARED

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/)