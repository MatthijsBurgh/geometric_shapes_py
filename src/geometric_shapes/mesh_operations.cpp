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
#include <pybind11/iostream.h>
#include <pybind11/eigen.h>
//#include <pybind11/stl.h>

#include <geometric_shapes/mesh_operations.h>

#include <container_typecasters.hpp>
#include <pystreambuf.hpp>
#include <ros_msg_typecasters.hpp>
#include "mesh_operations.hpp"

#include <iostream>
#include <sstream>
#include <vector>

namespace geometric_shapes_py
{

using namespace shapes;

void define_mesh_operations(py::module& m)
{
  m.def("create_mesh_from_resource",
        py::overload_cast<const std::string&, const Eigen::Vector3d&>(&createMeshFromResource), py::arg("resource"),
        py::arg("scale") = Eigen::Vector3d(1., 1., 1.),
        R"(Load a mesh from a resource that contains a mesh that can be loaded by assimp.)");

  m.def(
      "create_mesh_from_binary",
      [](std::istream& stream, const Eigen::Vector3d scale = { 1., 1., 1. },
         const std::string& assimp_hint = std::string()) {
        size_t buffer_size = stream.gcount();
        char buffer[buffer_size];
        stream >> buffer;
        return createMeshFromBinary(buffer, buffer_size, scale, assimp_hint);
      },
      py::arg("binary_stream"), py::arg("scale"), py::arg("assimp_hint"),
      R"( Load a mesh from a binary stream that contains a mesh that can be loaded by assimp.)");

  m.def("create_mesh_from_shape", py::overload_cast<const Shape*>(&createMeshFromShape), py::arg("shape"),
        R"(Construct a mesh from a primitive shape that is NOT already a mesh. This call allocates a new object.)");

  m.def("create_mesh_from_shape", py::overload_cast<const Box&>(&createMeshFromShape), py::arg("shape"),
        R"(Construct a mesh from a box.)");

  m.def("create_mesh_from_shape", py::overload_cast<const Sphere&>(&createMeshFromShape), py::arg("shape"),
        R"(Construct a mesh from a sphere.)");

  m.def("create_mesh_from_shape", py::overload_cast<const Cylinder&>(&createMeshFromShape), py::arg("shape"),
        R"(Construct a mesh from a cylinder.)");

  m.def("create_mesh_from_shape", py::overload_cast<const Cone&>(&createMeshFromShape), py::arg("shape"),
        R"(Construct a mesh from a cone.)");

  m.def(
      "mesh_to_stl_binary",
      [](const Mesh* mesh, std::ostream& stream) {
        std::vector<char> buffer;
        writeSTLBinary(mesh, buffer);
        stream.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
      },
      py::arg("mesh"), py::arg("binary_stream"), R"(Write the mesh to a buffer in STL format.)");
}

}  // namespace geometric_shapes_py
