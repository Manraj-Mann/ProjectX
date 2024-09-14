# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Define the library
add_library(ConfigReader STATIC
    ConfigReader.cpp
)

# Set C++ standard
set_target_properties(ConfigReader PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED True
)
