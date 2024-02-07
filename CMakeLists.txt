cmake_minimum_required(VERSION 3.27)
project(project14Real C)

set(CMAKE_C_STANDARD 11)

include_directories(Headers)

add_executable(project14_1
        Headers/nodes.h
        Headers/PreAsse.h
        Sourcefiles/nodes.c
        Sourcefiles/PreAssembler.c
        Headers/general.h
        Sourcefiles/general.c
        Sourcefiles/main.c)