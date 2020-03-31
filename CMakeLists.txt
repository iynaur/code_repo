cmake_minimum_required(VERSION 3.5)

project(codeRepo LANGUAGES CXX)

include_directories(${CMAKE_SOURCE_DIR})
file(GLOB HEAD_FILES "*.h")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(codeRepo main.cpp ${HEAD_FILES})
