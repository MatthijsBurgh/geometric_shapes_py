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
find_package(rclcpp REQUIRED)

# Find python before pybind11
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

find_package(pybind11_vendor REQUIRED)
find_package(pybind11 REQUIRED)

# enables using the Python extensions from the build space for testing
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/test_geometric_shapes/__init__.py" "")

ament_python_install_package(geometric_shapes)

# Set the build location and install location for a CPython extension
function(configure_build_install_location _library_name)
  # Install into test_moveit test_geometric_shapes in build space for unit tests to import
  set_target_properties(${_library_name} PROPERTIES
    # Use generator expression to avoid prepending a build type specific directory on Windows
    LIBRARY_OUTPUT_DIRECTORY $<1:${CMAKE_CURRENT_BINARY_DIR}/test_geometric_shapes>
    RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_CURRENT_BINARY_DIR}/test_geometric_shapes>
  )

  install(TARGETS ${_library_name}
    DESTINATION "${PYTHON_INSTALL_DIR}/geometric_shapes"
  )
endfunction()

pybind11_add_module(_geometric_shapes_py SHARED
  src/geometric_shapes/_geometric_shapes_py.cpp
#  src/geometric_shapes/aabb.cpp
  src/geometric_shapes/mesh_operations.cpp
  src/geometric_shapes/ros_msg_typecasters.cpp
  src/geometric_shapes/shape_operations.cpp
  src/geometric_shapes/shape_to_marker.cpp
  src/geometric_shapes/shapes.cpp
)
if(CMAKE_C_COMPILER_ID MATCHES "Clang" AND NOT APPLE)
  target_link_libraries(_geometric_shapes_py PRIVATE atomic)
endif()
target_include_directories(_geometric_shapes_py PRIVATE
  src/geometric_shapes/
)

target_link_libraries(_geometric_shapes_py PRIVATE
  geometric_shapes::geometric_shapes
  rclcpp::rclcpp
)
configure_build_install_location(_geometric_shapes_py)

if(NOT WIN32)
  ament_environment_hooks(
    "${ament_cmake_package_templates_ENVIRONMENT_HOOK_LIBRARY_PATH}"
  )
endif()

if(BUILD_TESTING)
  # ament_lint
  set(ament_cmake_clang_format_CONFIG_FILE ".clang-format")
#  set(ament_cmake_clang_tidy_CONFIG_FILE ".clang-tidy")
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()

  # pytest
  find_package(ament_cmake_pytest REQUIRED)

  file(GLOB _geometric_shapes_py_pytest_tests RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
      "test/test*.py"
  )

  message(DEBUG "Detected pytest files: ${_geometric_shapes_py_pytest_tests}")

  foreach(_test_path ${_geometric_shapes_py_pytest_tests})
    get_filename_component(_test_name ${_test_path} NAME_WE)
    ament_add_pytest_test(${_test_name} ${_test_path}
      APPEND_ENV
        AMENT_PREFIX_PATH=${ament_index_build_path}
        PYTHONPATH=${CMAKE_CURRENT_BINARY_DIR}
      TIMEOUT 120
      WERROR ON
    )
  endforeach()
endif()

ament_package()
