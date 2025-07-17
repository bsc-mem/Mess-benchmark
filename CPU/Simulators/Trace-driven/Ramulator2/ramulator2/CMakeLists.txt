cmake_minimum_required(VERSION 3.14)

project(
  Ramulator
  VERSION 2.0
  LANGUAGES CXX
)

#### Prompt the build type ####
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()
message("Configuring ${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_Version}...")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DRAMULATOR_DEBUG")
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
###############################

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

#### External libraries ####
message("Configuring yaml-cpp...")
option(YAML_CPP_BUILD_CONTRIB "Enable yaml-cpp contrib in library" OFF)
option(YAML_CPP_BUILD_TOOLS "Enable parse tools" OFF)
option(YAML_BUILD_SHARED_LIBS "Build yaml-cpp as a shared library" OFF)
add_subdirectory(vendor/yaml-cpp)
include_directories(vendor/yaml-cpp/include)
message("Done configuring yaml-cpp.")

message("Configuring spdlog...")
add_subdirectory(vendor/spdlog)
include_directories(vendor/spdlog/include)
message("Done configuring spdlog.")

message("Configuring argparse...")
add_subdirectory(vendor/argparse)
include_directories(vendor/argparse/include)
message("Done configuring argparse.")
##################################

include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(ramulator SHARED)
set_target_properties(ramulator PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}
)
target_link_libraries(
  ramulator 
  PUBLIC yaml-cpp
  PUBLIC spdlog
  PUBLIC stdc++fs
)

add_executable(ramulator-exe)
target_link_libraries(
  ramulator-exe 
  # PRIVATE -Wl,--whole-archive ramulator -Wl,--no-whole-archive 
  PRIVATE ramulator
  PRIVATE argparse
  PUBLIC stdc++fs
)

set_target_properties(
  ramulator-exe
  PROPERTIES 
  OUTPUT_NAME ramulator2
)

add_subdirectory(src)
