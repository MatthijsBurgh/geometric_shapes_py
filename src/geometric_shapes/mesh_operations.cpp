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
#include <pybind11/iostream.h>
#include <pybind11/eigen.h>

#include <geometric_shapes/mesh_operations.h>

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
