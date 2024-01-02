/*********************************************************************
 * Software License Agreement (BSD 3-Clause License)
 *
 *  Copyright (c) 2024, VBTI
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice, this
 *  list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *  this list of conditions and the following disclaimer in the documentation
 *  and/or other materials provided with the distribution.
 *
 *  3. Neither the name of the copyright holder nor the names of its
 *  contributors may be used to endorse or promote products derived from
 *  this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

/* Author: Matthijs van der Burgh */

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
