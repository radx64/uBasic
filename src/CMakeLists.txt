file(GLOB_RECURSE SRC
    "./*.cpp"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_definitions(-std=c++11)
add_definitions(-O3)
add_library(interpreter ${SRC})

add_executable(uBasic main.cpp)
target_link_libraries (uBasic interpreter)