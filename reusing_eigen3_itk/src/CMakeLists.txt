cmake_minimum_required(VERSION 3.10)
project(itk_minimal)
find_package(ITK REQUIRED COMPONENTS
  ITKEigen3
  # This calls find_package(Eigen3) if ITK_USE_SYSTEM_EIGEN
  # Or find_package(ITKInternalEigen3) otherwise
  # ITKInternalEigen3 does NOT allow to #include <Eigen/Core> but to #include <itkeigen/Eigen/Core>
  # But ITK also creates a Eigen3Config.cmake for external consumers that are already using Eigen3
  # (i.e. in ExternalModules) that points to ITKInternal, so #include <Eigen/Core> can be used.
  # that's why we need the extra logic to find Eigen in the case of non using the system eigen.
  #if(DEFINED ITKInternalEigen3_DIR)
  #  set(Eigen3_DIR ${ITKInternalEigen3_DIR})
  #  find_package(Eigen3 REQUIRED CONFIG)
  #endif()
  ITKCommon
  )
include(${ITK_USE_FILE})

# set(_internal_cmake_eigen3)
# FOR ITK BUILD TREE:
# list(GET ITKEigen3_INCLUDE_DIRS 0 _internal_cmake_eigen3)
# set(Eigen3_DIR "${_internal_cmake_eigen3}/itkeigen")
# message(STATUS "Internal set Eigen3_DIR: ${Eigen3_DIR}")
# FOR ITK BUILD/INSTALL TREE
set(ITK_EIGEN_LIBRARIES "")
if(DEFINED ITKInternalEigen3_DIR)
  set(Eigen3_DIR ${ITKInternalEigen3_DIR})
  find_package(Eigen3 REQUIRED CONFIG)
  list(APPEND ITK_EIGEN_LIBRARIES Eigen3::Eigen)
endif()
message(STATUS "After Eigen3_DIR: ${Eigen3_DIR}")

message(STATUS "ITK_LIBRARIES:\n ${ITK_LIBRARIES}")
add_executable(main main.cpp)
target_link_libraries(main PUBLIC ${ITK_LIBRARIES} )
target_link_libraries(main PUBLIC ${ITK_EIGEN_LIBRARIES} )

# if (TARGET Eigen3::Eigen)
#   message(STATUS "TARGET Eigen3::Eigen FOUND")
#   target_link_libraries(main PUBLIC Eigen3::Eigen )
# endif()

# if (TARGET ITKInternalEigen3::Eigen)
#   message(STATUS "TARGET ITKInternalEigen3::Eigen FOUND")
#   target_link_libraries(main PUBLIC ITKInternalEigen3::Eigen )
# endif()
