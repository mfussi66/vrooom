cmake_minimum_required(VERSION 3.30)

project(rover)

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
)

lcm_add_library(my_lcmtypes C STATIC ${c_sources} ${c_headers})
target_include_directories(my_lcmtypes INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)

lcm_add_library(my_lcmtypes-cpp CPP ${cpp_headers})
target_include_directories(my_lcmtypes-cpp INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)

lcm_install_headers(DESTINATION include
  ${CMAKE_CURRENT_BINARY_DIR}/my_lcmtypes_export.h
  ${cpp_headers}
)

add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
         ${CMAKE_CURRENT_BINARY_DIR}/include
)

target_sources(${PROJECT_NAME}
    PRIVATE
        src/main.cpp
        src/Rover.cpp
        src/Motor.cpp
        src/Comms.cpp
        src/mockHardware.cpp
        src/control.cpp
)


option(USE_LGPIO "Use LGpio instead of mocking" OFF)

# Find and link the lgpio library
if(USE_LGPIO)
    find_library(LGPIO_LIBRARY lgpio)
    if(NOT LGPIO_LIBRARY)
        message(FATAL_ERROR "lgpio library not found")
    endif()

    target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/hw
    )
    taget_sources(${PROJECT_NAME} PRIVATE src/hw/Hardware.cpp)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE  ${LGPIO_LIBRARY} my_lcmtypes-cpp ${LCM_NAMESPACE}lcm)
