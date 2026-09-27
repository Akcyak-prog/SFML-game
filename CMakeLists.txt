cmake_minimum_required(VERSION 3.20)
project(SFML_Learning LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main
     main.cpp
     Game.cpp
     Game.hpp
)

find_package(SFML 2 REQUIRED COMPONENTS graphics window system)
target_link_libraries(main PRIVATE sfml-graphics sfml-window sfml-system)
