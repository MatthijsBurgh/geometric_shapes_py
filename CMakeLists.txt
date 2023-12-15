cmake_minimum_required(VERSION 3.5)
project(geometric_shapes_py)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()
# Default to C11
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 11)
endif()
# Set compile options
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(PROJECT_COMPILE_OPTIONS
    -Wall
    -Wextra
    -Wwrite-strings
    -Wunreachable-code
    -Wpointer-arith
    -Wredundant-decls
    -Wno-unused-parameter
  )
endif()

# Figure out Python3 debug/release before anything else can find_package it
if(WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  find_package(python_cmake_module REQUIRED)
  find_package(PythonExtra REQUIRED)

  # Force FindPython3 to use the debug interpreter where ROS 2 expects it
  set(Python3_EXECUTABLE "${PYTHON_EXECUTABLE_DEBUG}")
endif()

find_package(ament_cmake REQUIRED)
find_package(geometric_shapes REQUIRED)

# Find python before pybind11
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

find_package(pybind11_vendor REQUIRED)
find_package(pybind11 REQUIRED)

# enables using the Python extensions from the build space for testing
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/test_geometric_shapes/__init__.py" "")

ament_python_install_package(geometric_shapes)

# Set the build location and install location for a CPython extension
function(configure_build_install_location _library_name)
    # Install into test_moveit folder in build space for unit tests to import
    set_target_properties(${_library_name} PROPERTIES
        # Use generator expression to avoid prepending a build type specific directory on Windows
        LIBRARY_OUTPUT_DIRECTORY $<1:${CMAKE_CURRENT_BINARY_DIR}/test_geometric_shapes>
        RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_CURRENT_BINARY_DIR}/test_geometric_shapes>)

    install(TARGETS ${_library_name}
    DESTINATION "${PYTHON_INSTALL_DIR}/geometric_shapes"
  )
endfunction()

pybind11_add_module(_geometric_shapes_pybind11 SHARED
  src/geometric_shapes/_geometric_shapes_pybind11.cpp
)
target_link_libraries(_geometric_shapes_pybind11 PRIVATE
  geometric_shapes::geometric_shapes
)
configure_build_install_location(_geometric_shapes_pybind11)
# target_link_libraries(_geometric_shapes_pybind11 PRIVATE moveit_ros_planning::moveit_cpp
				   # rclcpp::rclcpp
				   # moveit_core::moveit_transforms
				   # moveit_core::moveit_kinematic_constraints
				   # moveit_core::moveit_planning_interface
				   # moveit_core::moveit_planning_scene
				   # moveit_core::moveit_utils
				   # moveit_core::moveit_robot_model
				   # moveit_core::moveit_robot_state
				   # moveit_py_utils)
# configure_build_install_location(core)
#
# pybind11_add_module(planning
    # src/moveit/planning.cpp
    # src/moveit/moveit_ros/moveit_cpp/moveit_cpp.cpp
    # src/moveit/moveit_ros/moveit_cpp/planning_component.cpp
    # src/moveit/moveit_ros/planning_scene_monitor/planning_scene_monitor.cpp
    # src/moveit/moveit_ros/trajectory_execution_manager/trajectory_execution_manager.cpp
# )
# target_link_libraries(planning PRIVATE moveit_ros_planning::moveit_cpp
    # moveit_ros_planning::moveit_planning_scene_monitor
    # moveit_ros_planning::moveit_trajectory_execution_manager
    # moveit_core::moveit_utils
    # rclcpp::rclcpp
    # moveit_py_utils
# )
# configure_build_install_location(planning)
#
#
# if(BUILD_TESTING)
  # find_package(ament_cmake_pytest REQUIRED)
  # set(_pytest_tests
    # test/unit/test_robot_model.py
    # test/unit/test_robot_state.py
  # )
  # foreach(_test_path ${_pytest_tests})
	  # get_filename_component(_test_name ${_test_path} NAME_WE)
	  # ament_add_pytest_test(${_test_name} ${_test_path}
	  # APPEND_ENV AMENT_PREFIX_INDEX=${ament_index_build_path} PYTHONPATH=${CMAKE_CURRENT_BINARY_DIR}
	  # TIMEOUT 60
	  # WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
   	  # )
  # endforeach()
# endif()
#
# ament_export_targets(moveit_py_utilsTargets HAS_LIBRARY_TARGET)
# ament_export_dependencies(moveit_ros_planning_interface)
# ament_package()


# if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
  # message("${PROJECT_NAME}: You did not request a specific build type: Choosing 'Release' for maximum performance")
  # set(CMAKE_BUILD_TYPE Release)
# endif()
#
#
# # find *absolute* paths to ASSIMP_LIBRARIES
# # Both, pkg-config and assimp's cmake-config don't provide an absolute library path.
# # For, pkg-config the path is in ASSIMP_PC_LIBRARY_DIRS, for cmake in ASSIMP_LIBRARY_DIRS.
# find_library(assimp_ABS_LIBRARIES NAMES ${assimp_LIBRARIES} assimp HINTS ${assimp_LIBRARY_DIRS} ${assimp_PC_LIBRARY_DIRS})
# set(assimp_LIBRARIES "${assimp_ABS_LIBRARIES}")
#
# # These need to be in this order to find header files
# find_package(eigen3_cmake_module REQUIRED)
# find_package(Eigen3 REQUIRED)
#
# find_package(ament_cmake REQUIRED)
# find_package(assimp REQUIRED)
# find_package(console_bridge REQUIRED)
# find_package(console_bridge_vendor REQUIRED)
# find_package(eigen_stl_containers REQUIRED)
# find_package(geometry_msgs REQUIRED)
# find_package(OCTOMAP REQUIRED)
# find_package(QHULL REQUIRED)
# find_package(random_numbers REQUIRED)
# find_package(rclcpp REQUIRED)
# find_package(resource_retriever REQUIRED)
# find_package(shape_msgs REQUIRED)
# find_package(visualization_msgs REQUIRED)
# include(ConfigExtras)
#
# set(THIS_PACKAGE_EXPORT_DEPENDS
  # eigen3_cmake_module
  # Eigen3
  # Boost
  # console_bridge
  # console_bridge_vendor
  # eigen_stl_containers
  # geometry_msgs
  # OCTOMAP
  # random_numbers
  # rclcpp
  # resource_retriever
  # shape_msgs
  # visualization_msgs
# )
#
# # Set VERSION from package.xml
# ament_package_xml()
#
# include_directories(include)
#
# add_library(${PROJECT_NAME} SHARED
  # src/aabb.cpp
  # src/bodies.cpp
  # src/body_operations.cpp
  # src/mesh_operations.cpp
  # src/shape_extents.cpp
  # src/shape_operations.cpp
  # src/shape_to_marker.cpp
  # src/shapes.cpp
# )
# set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${${PROJECT_NAME}_VERSION} WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
# target_compile_options(${PROJECT_NAME} PRIVATE ${PROJECT_COMPILE_OPTIONS})
# ament_target_dependencies(${PROJECT_NAME}
  # ${THIS_PACKAGE_EXPORT_DEPENDS}
# )
# ament_target_dependencies(${PROJECT_NAME} SYSTEM
  # # We don't export these dependencies because their cmake is broken
  # assimp
  # QHULL
# )
#
# if(BUILD_TESTING)
  # find_package(ament_cmake_gtest REQUIRED)
  # # Unit tests
  # add_subdirectory(test)
#
  # # ament_lint
  # find_package(ament_lint_auto REQUIRED)
  # ament_lint_auto_find_test_dependencies()
# endif()
#
# install(
  # TARGETS ${PROJECT_NAME}
  # EXPORT export_${PROJECT_NAME}
  # LIBRARY DESTINATION lib
  # ARCHIVE DESTINATION lib
  # RUNTIME DESTINATION bin
  # INCLUDES DESTINATION include
# )
# install(DIRECTORY include/ DESTINATION include)
#
# ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
# ament_export_dependencies(${THIS_PACKAGE_EXPORT_DEPENDS})
#
# ament_package(CONFIG_EXTRAS "cmake/ConfigExtras.cmake")
