cmake_minimum_required(VERSION 3.27)
project(UnixRemoteShellClient C)

set(CMAKE_C_STANDARD 11)

add_executable(UnixRemoteShellClient main.c
        client_socket_init.c
        client_socket_init.h)
