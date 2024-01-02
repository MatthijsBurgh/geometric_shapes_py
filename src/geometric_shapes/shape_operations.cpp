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

#include <geometric_shapes/shape_operations.h>

#include <container_typecasters.hpp>
#include <pystreambuf.hpp>
#include <ros_msg_typecasters.hpp>
#include "shape_operations.hpp"

#include <sstream>

namespace geometric_shapes_py
{

using namespace shapes;

struct Visitor : boost::static_visitor<std::string>
{
  template <typename T>
  auto operator()(const T& /*msg*/)
  {
    return std::string(rosidl_generator_traits::name<T>());
  }
};

void define_shape_operations(py::module& m)
{
  m.def(
      "construct_shape_from_msg",
      [](const ShapeMsg& msg) {
        Shape* shape = constructShapeFromMsg(msg);
        if (!shape)
        {
          Visitor visitor;
          throw std::runtime_error("Could not construct a shape from message of type: " + msg.apply_visitor(visitor));
        }
        return shape;
      },
      py::arg("msg"), R"(Construct the shape that corresponds to the message.)");

  m.def(
      "construct_msg_from_shape",
      [](const Shape& shape) {
        ShapeMsg msg;
        bool ret = constructMsgFromShape(&shape, msg);
        if (!ret)
        {
          std::ostringstream ss;
          ss << "Could not construct a shape msg from shape of type: " << shape.type;
          throw std::runtime_error(ss.str());
        }
        return msg;
      },
      py::arg("shape"), R"(Construct the message that corresponds to the shape.)");

  m.def(
      "construct_marker_from_shape",
      [](const Shape& shape, bool use_mesh_traingle_list = false) {
        visualization_msgs::msg::Marker msg;
        bool ret = constructMarkerFromShape(&shape, msg, use_mesh_traingle_list);
        if (!ret)
        {
          std::ostringstream ss;
          ss << "Could not construct a marker msg from shape of type: " << shape.type;
          throw std::runtime_error(ss.str());
        }
        return msg;
      },
      py::arg("shape"), py::arg("use_mesh_triangle_list") = false,
      R"(Construct the marker that corresponds to the shape.)");

  m.def("shape_string_name", &shapeStringName, py::arg("shape"), R"(Get the string name of the shape.)");

  m.def("shape_to_text", &saveAsText, py::arg("shape"), py::arg("binary_stream"),
        R"(Write all the information about this shape to a binary stream.)");

  m.def(
      "text_to_shape",
      [](std::istream& stream) {
        Shape* shape = constructShapeFromText(stream);
        if (!shape)
          throw std::runtime_error("Could not construct a shape");

        return shape;
      },
      py::arg("binary_stream"), R"(Construct a shape from a binary text stream.)");
}

}  // namespace geometric_shapes_py
