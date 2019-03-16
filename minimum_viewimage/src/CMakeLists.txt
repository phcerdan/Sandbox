cmake_minimum_required(VERSION 3.4)
project(viewimage_MWE)

find_package(ITK REQUIRED COMPONENTS
  ITKCommon
  ITKImageIO
  ITKVtkGlue
  )
include(${ITK_USE_FILE})
add_executable(minimum_viewimage minimum_viewimage.cpp)
target_link_libraries(minimum_viewimage ${ITK_LIBRARIES})
