cmake_minimum_required (VERSION 3.0)

project (Calculator)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories (
    ${PROJECT_SOURCE_DIR}/src
)

set (
    calculator_SOURCES
    ${PROJECT_SOURCE_DIR}/src/calculator.cpp
)

add_library (
    calculator SHARED
    ${calculator_SOURCES}
)

# Enable ExternalProject_Add directive.
include (ExternalProject)

add_subdirectory (test)
