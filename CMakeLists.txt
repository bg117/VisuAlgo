cmake_minimum_required(VERSION 3.10)
project(VisuAlgo)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
# GTK3
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

add_executable(VisuAlgo main.cpp App.hpp App.cpp AlgoVisualizer.hpp AlgoVisualizer.cpp Algorithm.hpp Algorithm.cpp)

target_link_libraries(VisuAlgo ${GTKMM_LIBRARIES})