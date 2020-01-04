cmake_minimum_required(VERSION 3.15)
project(flight_project)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

include_directories(.)

add_executable(
        flight_project
        Command.cpp
        Command.h
        CommandFactory.cpp
        CommandFactory.h
        ExpressionInterpreter.cpp
        ExpressionInterpreter.h
        FromAeroplaneServer.cpp
        FromAeroplaneServer.h
        TelnetClient.cpp
        TelnetClient.h
        TelnetServer.cpp
        TelnetServer.h
        ToAeroplaneClient.cpp
        ToAeroplaneClient.h
        globals_singleton.h
        lexer.cpp
        lexer.h
        lexerFile.cpp
        lexerFile.h
        main.cpp
        parser.cpp
        parser.h
        var.h
)
