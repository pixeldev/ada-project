cmake_minimum_required(VERSION 3.29)
project(proyecto)

set(CMAKE_CXX_STANDARD 26)

add_executable(proyecto
        main.cpp
        Board.cpp
        Board.h
        Game.cpp
        Game.h
        Solution.cpp
        Solution.h
        SolutionCell.cpp
        SolutionCell.h
)
