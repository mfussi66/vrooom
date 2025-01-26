cmake_minimum_required(VERSION 3.21)

project(rover)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(USE_LGPIO "Use LGpio instead of mocking" OFF)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        src/main.cpp
        src/Rover.cpp
        src/Motor.cpp
        src/control.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

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

else()
    target_sources(${PROJECT_NAME}
    PRIVATE
    src/mockHardware.cpp)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE ${LGPIO_LIBRARY})
