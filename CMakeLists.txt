cmake_minimum_required(VERSION 3.10)

project(rover C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        src/main.c
        src/rover.c
        src/motor.c
        src/control.c
        src/hardware.c
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Find and link the lgpio library
find_library(LGPIO_LIBRARY lgpio)
if(NOT LGPIO_LIBRARY)
    message(FATAL_ERROR "lgpio library not found")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE ${LGPIO_LIBRARY})
