# Add the executable target
add_executable(configTest main.cpp)

# Link the executable with the ConfigReader library
target_link_libraries(configTest PRIVATE ConfigReader)
