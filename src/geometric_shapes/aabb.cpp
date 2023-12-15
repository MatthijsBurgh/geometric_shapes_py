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
#include <pybind11/eigen.h>

#include <geometric_shapes/aabb.h>

namespace geometric_shapes_py
{

void define_aabb(py::object& module)
{
  py::class_<bodies::AABB>(m, "AABB", R"(
      Represents an axis-aligned bounding box.
      )")
      .def("extend_with_transformed_box", &bodies::AABB::extendWithTransformedBox);
}
}  // namespace geometric_shapes_py
