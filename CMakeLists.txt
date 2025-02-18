cmake_minimum_required(VERSION 3.30)

project(vrooom)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(lcm REQUIRED)

include(${LCM_USE_FILE})
include(GenerateExportHeader)

# Set the path to your LCM types
set(LCM_TYPES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/types)

lcm_wrap_types(
  C_EXPORT my_lcmtypes
  C_HEADERS c_headers
  C_SOURCES c_sources
  CPP_HEADERS cpp_headers
  ${LCM_TYPES_DIR}/twist.lcm
  ${LCM_TYPES_DIR}/motor_commands.lcm
)

lcm_add_library(my_lcmtypes C STATIC ${c_sources} ${c_headers})
generate_export_header(my_lcmtypes)
target_include_directories(my_lcmtypes INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)

lcm_add_library(my_lcmtypes-cpp CPP ${cpp_headers})
target_include_directories(my_lcmtypes-cpp INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)

lcm_install_headers(DESTINATION include
  ${CMAKE_CURRENT_BINARY_DIR}/my_lcmtypes_export.h
  ${cpp_headers}
)

add_subdirectory(Rover)
add_subdirectory(JoypadControl)
add_subdirectory(Simulator)
