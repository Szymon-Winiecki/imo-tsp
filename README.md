# IMO-TSP

Modified traveling salesman problem solver.

## Requirements

 - Visual Studio 2022 (with MSVC 143 and up)
 - CMake 3.15 and up
 - NetworkX python package (https://networkx.org/documentation/stable/index.html#)
 - matplotlib python package (https://matplotlib.org/)

## How to run

 - open root project directory in VS22
 - run project (with main.exe as a startup item)

It is also possible to use another c++ compiler that supports at least c++20 standard, but it requires some changes in CMake configuration and adjusting relativeProjectRootDir in `src/main.cpp`