file(GLOB_RECURSE SRC
    "./*.cpp"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gtest)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

add_definitions(-std=c++11)
add_definitions(-O0)

add_subdirectory (gtest)
add_executable(UT main.cpp ${SRC})
target_link_libraries (UT -pthread gtest)