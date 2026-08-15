cmake_minimum_required(VERSION 3.16)

project(student_portal
    VERSION 1.0.0
    DESCRIPTION "CLI student portal for students, courses, and enrollments"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Keep build artifacts out of the source tree (use: cmake -S . -B build)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(student_portal
    main.cpp
    src/Student.cpp
    src/Course.cpp
)

target_include_directories(student_portal
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(student_portal PRIVATE /W4)
else()
    target_compile_options(student_portal PRIVATE -Wall -Wextra -Wpedantic)
endif()
