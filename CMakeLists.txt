cmake_minimum_required(VERSION 3.5)

project(Computer_Architecture_Project_3)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "-Os")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Os -g")

set(SOURCE_FILES
    InstCache.cpp
    InstCache.hpp
    InstDataBin.cpp
    InstDataBin.hpp
    InstDataStr.cpp
    InstDataStr.hpp
    InstDecoder.cpp
    InstDecoder.hpp
    InstDisk.cpp
    InstDisk.hpp
    InstImageReader.cpp
    InstImageReader.hpp
    InstLookUp.cpp
    InstLookUp.hpp
    InstMemory.cpp
    InstMemory.hpp
    InstPageTable.cpp
    InstPageTable.hpp
    InstRegister.cpp
    InstRegister.hpp
    InstSimulator.cpp
    InstSimulator.hpp
    InstTLB.cpp
    InstTLB.hpp
    InstType.hpp
    InstUtility.cpp
    InstUtility.hpp
    main.cpp)

set(TEST_GEN_SOURCE_FILES
    testGenerator.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/release")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

add_executable(CMP ${SOURCE_FILES})
add_executable(testGen ${TEST_GEN_SOURCE_FILES})
