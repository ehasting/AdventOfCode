cmake_minimum_required(VERSION 3.26)
project(Day1)

set(CMAKE_CXX_STANDARD 20)



add_executable(Day1 main.cpp
        task1.cpp
        task1.hpp
        task2.cpp
        task2.hpp)
add_custom_target(copy_asset
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/payload.txt $<TARGET_FILE_DIR:Day1>)
add_dependencies(Day1 copy_asset)