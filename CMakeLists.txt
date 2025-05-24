cmake_minimum_required(VERSION 3.10)
project(PapasFreezeria)
# Debuggerr
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect all .cpp and .hpp files recursively
file(GLOB_RECURSE SOURCES
    7.cpp
)

file(GLOB_RECURSE HEADERS
    *.hpp
)

# Create the executable
add_executable(PapasFreezeria ${SOURCES} ${HEADERS})
