cmake_minimum_required(VERSION 3.5)

project(Computer_Architecture_Project_3)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 -Wall -Wextra -g3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Os")


set(SOURCE_FILES
        InstDataBin.cpp
        InstDataBin.hpp
        InstDataStr.cpp
        InstDataStr.hpp
        InstDecoder.cpp
        InstDecoder.hpp
        InstImageReader.cpp
        InstImageReader.hpp
        InstLookUp.cpp
        InstLookUp.hpp
        InstMemory.cpp
        InstMemory.hpp
        InstRegister.cpp
        InstRegister.hpp
        InstSimulator.cpp
        InstSimulator.hpp
        InstType.hpp
        InstUtility.cpp
        InstUtility.hpp
        main.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/release")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

add_executable(CMP ${SOURCE_FILES})
