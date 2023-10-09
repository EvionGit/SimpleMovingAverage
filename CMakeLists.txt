cmake_minimum_required(VERSION 3.21)
project(SimpleMovingAverage)

set(CMAKE_CXX_STANDARD 20)

add_executable(SMA
        src/main.cpp
        include/sma.h
        include/random_generator.h
)

