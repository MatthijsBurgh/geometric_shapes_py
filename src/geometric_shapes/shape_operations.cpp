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
