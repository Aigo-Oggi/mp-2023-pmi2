cmake_minimum_required(VERSION 3.0)


project(matrix)

set(MP2_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")

include_directories("${MP2_INCLUDE}" gtest)

add_subdirectory(samples)
add_subdirectory(gtest)
add_subdirectory(test)

