cmake_minimum_required(VERSION 3.16)
project(Tetris)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)

# Set SFML_DIR to the extracted location
set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML-3.0.0/lib/cmake/SFML")

# Find SFML
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

# Create the executable
add_executable(Tetris main.cpp)

# Set output directory AFTER the target is created
set_target_properties(Tetris PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

# Link SFML libraries
target_link_libraries(Tetris PRIVATE SFML::Graphics SFML::Window SFML::System)
