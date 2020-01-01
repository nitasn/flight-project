cmake_minimum_required(VERSION 3.15)
project(flight_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(flight_project
        Command.h
        Expression.cpp
        Expression.h
        ifWhileCommandFromFileToMap.cpp
        ifWhileCommandFromFileToMap.h
        lexer.cpp
        lexer.h
        main.cpp
        simpleCommandFromFileToMap.cpp
        simpleCommandFromFileToMap.h
        controlFly.cpp controlFly.h parser.cpp parser.h test.cpp singlton.h singltonGlobals.h lexerFile.cpp lexerFile.h)
