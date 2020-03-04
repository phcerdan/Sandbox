cmake_minimum_required(VERSION 3.6)
project(dgtal_ctopo3d)
find_package(DGtal REQUIRED COMPONENTS)

add_executable(main dgtal_ctopo3d.cpp)
target_link_libraries(main PUBLIC ${DGTAL_LIBRARIES} )
target_include_directories(main PRIVATE ${DGTAL_INCLUDE_DIRS})
