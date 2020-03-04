cmake_minimum_required(VERSION 3.5)
project(dijkstra-example)

find_package(Boost COMPONENTS
        graph
        REQUIRED)
add_executable(dijkstra_example_bgl dijkstra_example_bgl.cpp)
target_link_libraries(dijkstra_example_bgl ${Boost_LIBRARIES})
