cmake_minimum_required(VERSION 3.14)
project(BlockChain VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Define your main executable target
add_executable(BlockChain 
    main.cpp
    src/block.cpp
    src/blockchain.cpp
)

target_include_directories(BlockChain PRIVATE
    include
    external
)

# ==========================================
# 2. GoogleTest Integration via FetchContent
# ==========================================
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE  # <--- Fixes the warning
)

# For Windows: Prevent override of compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest) # <--- MUST come BEFORE target_link_libraries uses it

# Enable testing support in CMake
enable_testing()

# 3. Define your Unit Test executable target AFTER googletest is available
add_executable(BlockChainTests
    tests/blockchain_tests.cpp
    src/block.cpp
    src/blockchain.cpp
)

target_include_directories(BlockChainTests PRIVATE
    include
    external
)

# Link GoogleTest libraries to your test target
target_link_libraries(BlockChainTests PRIVATE gtest_main)

# Register the test with CMake
include(GoogleTest)
gtest_discover_tests(BlockChainTests)