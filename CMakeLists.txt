cmake_minimum_required(VERSION 3.16)

project(student_portal VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(student_portal
    main.cpp
)

target_include_directories(student_portal PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
