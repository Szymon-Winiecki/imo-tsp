cmake_minimum_required(VERSION 3.15)

project(imo-tsp VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Matplot++ REQUIRED)

add_executable(main src/main.cpp )

target_link_libraries(main PUBLIC Matplot++::matplot)