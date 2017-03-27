file(GLOB_RECURSE SRC
    "./*.cc"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_definitions(-pthread)
add_definitions(-std=c++11)
add_definitions(-O0)

add_library(gtest ${SRC})