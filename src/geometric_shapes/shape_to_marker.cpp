// Copyright 2021 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <pybind11/pybind11.h>

#include <geometric_shapes/shape_to_marker.h>

#include <ros_msg_typecasters.hpp>
#include "shape_to_marker.hpp"

#include <sstream>

namespace geometric_shapes_py
{

using namespace geometric_shapes;

void define_shape_to_marker(py::module& m)
{
  m.def(
      "construct_marker_from_shape",
      [](const shape_msgs::msg::Mesh& msg, bool use_mesh_traingle_list = true) {
        visualization_msgs::msg::Marker marker;
        constructMarkerFromShape(msg, marker, use_mesh_traingle_list);
        return marker;
      },
      py::arg("msg"), py::arg("use_mesh_triangle_list") = false,
      R"(Convert a shape_msgs::msg::Mesh \e shape_msg to a visualization_msgs::msg::Marker \e marker.

The corresponding marker will be constructed as a LINE_LIST (if \e use_mesh_triangle_list
is false) or as a TRIANGLE_LIST (if \e use_mesh_triangle_list is true).
On incorrect input, this function throws a RuntimeError.)");

  m.def(
      "construct_marker_from_shape",
      [](const shape_msgs::msg::SolidPrimitive& msg) {
        visualization_msgs::msg::Marker marker;
        constructMarkerFromShape(msg, marker);
        return marker;
      },
      py::arg("msg"),
      R"(Convert a shape_msgs::msg::SolidPrimitive \e shape_msg to a visualization_msgs::msg::Marker \e marker.

On incorrect input, this function throws a RuntimeError.)");
}

}  // namespace geometric_shapes_py
