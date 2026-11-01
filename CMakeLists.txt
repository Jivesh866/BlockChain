cmake_minimum_required(VERSION 3.12)
project(BlockChain VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(BlockChain 
    main.cpp
    src/block.cpp
    src/blockchain.cpp
    
)

target_include_directories(BlockChain PRIVATE
    include
    external
)