cmake_minimum_required(VERSION 2.8)

project(binzip)

include_directories("${PROJECT_SOURCE_DIR}/include")
link_directories("${PROJECT_SOURCE_DIR}/lib")

add_subdirectory(src)
