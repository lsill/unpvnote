project(lib)

add_library(${PROJECT_NAME}
        sock_ntop.c writen.c readn.c readline.c)# SHARED

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/)