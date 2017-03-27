file(GLOB_RECURSE SRC
    "./*.cpp"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gtest)

add_definitions(-std=c++11)
add_definitions(-O3)
add_library(interpreter_tests ${SRC})

add_subdirectory (gtest)
add_executable(UT test.cpp)
target_link_libraries (UT -pthread gtest interpreter_tests )