cmake_minimum_required(VERSION 3.15)
project(flight_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(flight_project
        client.cpp
        client.h
        command.h
        controlFly.cpp
        controlFly.h
        Expression.cpp
        Expression.h
        ifWhileCommandFromFileToMap.cpp
        ifWhileCommandFromFileToMap.h
        lexer.cpp
        lexer.h
        main.cpp
        server.cpp
        server.h
        simpleCommandFromFileToMap.cpp
        simpleCommandFromFileToMap.h
        stringsplit.cpp
        xmlChunksIndices.cpp
        xmlChunksIndices.h)
