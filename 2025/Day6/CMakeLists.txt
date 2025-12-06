cmake_minimum_required(VERSION 3.31)
project(Day5)

set(CMAKE_CXX_STANDARD 23)



add_executable(Day5 main.cpp
        task1.cpp
        task1.hpp
        task2.cpp
        task2.hpp)
add_custom_target(copy_asset
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/payload.txt
        ${CMAKE_SOURCE_DIR}/testpayload.txt $<TARGET_FILE_DIR:Day5>)
add_dependencies(Day5 copy_asset)