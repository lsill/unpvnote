project(libfree)
add_library(${PROJECT_NAME} SHARED
        inet_nton_ipv4.c
        inet_pton_ipv4.c
        getaddrinfo.c
        getnameinfo.c
        in_cksum.c
        inet_aton.c
        inet_ntop.c
        inet_pton.c)# SHARED

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/)