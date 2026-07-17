cmake_minimum_required(VERSION 4.2)
project(Wet2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Wet2
    main26b2.cpp
    Racenion26b2.cpp
    Racenion26b2.h
    wet2util.h
        AVLTree.h
        RankTree.h
        MyTable.h)
