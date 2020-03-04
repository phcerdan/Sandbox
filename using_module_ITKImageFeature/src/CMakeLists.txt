cmake_minimum_required(VERSION 3.10)
project(itk_minimal)
find_package(ITK)
include(${ITK_USE_FILE})
message(STATUS "ITK_LIBRARIES:\n ${ITK_LIBRARIES}")

add_executable(main main.cpp)
target_link_libraries(main PUBLIC ${ITK_LIBRARIES} )
