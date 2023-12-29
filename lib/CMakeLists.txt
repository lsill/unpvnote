project(lib)

add_library(${PROJECT_NAME} SHARED
        sock_ntop.c writen.c readn.c readline.c
        wrapsock.c error.c
        sockfd_to_family.c
        wrapunix.c
        str_echo.c
        wraplib.c
        str_cli.c
        wrapstdio.c
        #connect_nonb.c
        #connect_timeo.c
        #daemon_inetd.c
        #daemon_init.c
        dg_cli.c
        dg_echo.c
        signal.c
        )

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/)