project(lib)

add_library(${PROJECT_NAME} SHARED
        sock_ntop.c writen.c readn.c readline.c
        wrapsock.c error.c
        sockfd_to_family.c)#

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/)