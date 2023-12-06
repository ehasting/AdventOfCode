cmake_minimum_required(VERSION 3.26)
project(Day3)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        Day3 main.cpp
        task1.cpp
        task1.hpp
        task2.cpp
        task2.hpp
        gamesets.cpp
        gamesets.hpp
)
add_custom_target(copy_asset
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/payload.txt $<TARGET_FILE_DIR:Day3>)
add_dependencies(Day3 copy_asset)
