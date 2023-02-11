cmake_minimum_required(VERSION 3.24)
project(newEnronMail)

set(CMAKE_CXX_STANDARD 17)

add_executable(newEnronMail main.cpp Worker.cpp Worker.h Sender.cpp Sender.h)
