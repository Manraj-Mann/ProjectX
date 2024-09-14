# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(main VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the ConfigReader library
add_subdirectory(ConfigReader)

# Add the executable target
add_executable(main_exec main.cpp)

# Link the executable with the ConfigReader library
target_link_libraries(main_exec PRIVATE ConfigReader)
