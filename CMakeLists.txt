cmake_minimum_required(VERSION 3.15)

project(imo-tsp VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(main ${SOURCES} "src/RegretSolver.cpp" "include/RegretSolver.h" "include/Experiment.h" "src/experiment.cpp" "src/RandomSolver.cpp" "include/RandomSolver.h" "include/GreedyLocalSearch.h" "src/GreedyLocalSearch.cpp" "include/SteepestLocalSearch.h" "src/SteepestLocalSearch.cpp")
