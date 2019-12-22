cmake_minimum_required(VERSION 3.15)
project(flight-project)

#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)
#set(CMAKE_C_FLAGS -pthread)

add_executable(flight-project lexer.cpp lexer.h main.cpp server.cpp server.h command.h controlFly.cpp controlFly.h commandFromFileToMap.cpp commandFromFileToMap.h client.cpp client.h xmlChunksIndices.cpp xmlChunksIndices.h stringsplit.cpp)