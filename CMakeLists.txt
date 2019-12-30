cmake_minimum_required(VERSION 3.15)
project(flight_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(flight_project
        command.h
        Expression.cpp
        Expression.h
        ifWhileCommandFromFileToMap.cpp
        ifWhileCommandFromFileToMap.h
        lexer.cpp
        lexer.h
        main.cpp
        simpleCommandFromFileToMap.cpp
        simpleCommandFromFileToMap.h
        stringsplit.cpp
        controlFly.cpp controlFly.h parser.cpp parser.h test.cpp singlton.h singltonGlobals.h lexerFile.cpp lexerFile.h)
