cmake_minimum_required(VERSION 3.30)

project(rover-simulator)

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
)

target_link_libraries(${PROJECT_NAME} PRIVATE my_lcmtypes-cpp ${LCM_NAMESPACE}lcm)

