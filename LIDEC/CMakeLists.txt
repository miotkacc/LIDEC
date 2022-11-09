cmake_minimum_required(VERSION 3.22)
project(LIDEC)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(CLILoader)
add_subdirectory(XMLLoader)

add_executable(main main.cpp)

target_link_libraries(main CLILoader)
