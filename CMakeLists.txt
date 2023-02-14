cmake_minimum_required(VERSION 3.24)
project(Psps)

set(CMAKE_CXX_STANDARD 17)

add_executable(enronMailProject main.cpp Sender.cpp Worker.cpp unableToOpenFileException.cpp unableToOpenFileException.h)