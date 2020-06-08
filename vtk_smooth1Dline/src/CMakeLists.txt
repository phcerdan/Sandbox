cmake_minimum_required(VERSION 3.6)
project(vtk_smooth1Dline)
find_package(VTK REQUIRED)

include(${VTK_USE_FILE})
add_executable(main main.cpp)
target_link_libraries(main PUBLIC ${VTK_LIBRARIES} )
