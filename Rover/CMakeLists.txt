cmake_minimum_required(VERSION 3.21)

project(rover)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PRIVATE
         ${CMAKE_CURRENT_BINARY_DIR}/include
${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
        Rover.cpp
        Motor.cpp
        Comms.cpp
        mockHardware.cpp
        control.cpp
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
        ${CMAKE_CURRENT_SOURCE_DIR}hw
    )
    target_sources(${PROJECT_NAME} PRIVATE hw/Hardware.cpp)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE  ${LGPIO_LIBRARY} my_lcmtypes-cpp ${LCM_NAMESPACE}lcm)

