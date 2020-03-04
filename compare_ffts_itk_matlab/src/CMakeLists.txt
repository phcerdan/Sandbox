cmake_minimum_required(VERSION 3.6)
project(compare_ffts)

find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(main testFFT.cpp)
target_link_libraries(main PUBLIC ${ITK_LIBRARIES})
