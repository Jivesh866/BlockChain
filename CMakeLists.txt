cmake_minimum_required(VERSION 3.12)
project(BlockChain VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Define your executable target using your main source file
add_executable(BlockChain 
    main.cpp
    src/block.cpp
)

# 2. Specify where the compiler should look for header files (.h)
target_include_directories(BlockChain PRIVATE
    include
    external
)