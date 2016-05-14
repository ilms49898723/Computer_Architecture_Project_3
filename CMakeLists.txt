cmake_minimum_required(VERSION 3.5)

project(Computer_Architecture_Project_3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Os")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 -Wall -Wextra")

set(SOURCE_FILES
        InstDataBin.cpp
        InstDataBin.hpp
        InstDataStr.cpp
        InstDataStr.hpp
        InstDecoder.cpp
        InstDecoder.hpp
        InstErrorDetector.cpp
        InstErrorDetector.hpp
        InstImageReader.cpp
        InstImageReader.hpp
        InstLookUp.cpp
        InstLookUp.hpp
        InstMemory.cpp
        InstMemory.hpp
        InstPipelineData.cpp
        InstPipelineData.hpp
        InstSimulator.cpp
        InstSimulator.hpp
        InstType.hpp
        InstUtility.cpp
        InstUtility.hpp
        main.cpp)

add_executable(CMP ${SOURCE_FILES})
