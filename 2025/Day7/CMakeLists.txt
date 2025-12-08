cmake_minimum_required(VERSION 3.31)
project(Day7)

set(CMAKE_CXX_STANDARD 23)



add_executable(Day7 main.cpp
        task1.cpp
        task1.hpp
        task2.cpp
        task2.hpp
        dataclass.hpp)
add_custom_target(copy_asset
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/payload.txt
        ${CMAKE_SOURCE_DIR}/testpayload.txt $<TARGET_FILE_DIR:Day7>)
add_dependencies(Day7 copy_asset)