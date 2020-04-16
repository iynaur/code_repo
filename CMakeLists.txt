cmake_minimum_required(VERSION 3.5)

project(codeRepo LANGUAGES CXX)

include_directories(${CMAKE_SOURCE_DIR})
file(GLOB HEAD_FILES "*.h")
file(GLOB SRC_FILES "*.cpp")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(codeRepo ${HEAD_FILES} ${SRC_FILES})
