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

#include <geometric_shapes/shapes.h>

#include "shapes.hpp"

#include <sstream>

namespace geometric_shapes_py
{

using namespace shapes;

template <class ShapeBase = Shape>
class PyShape : public ShapeBase
{
  using ShapeBase::ShapeBase;  // Inherit constructors
  ShapeBase* clone() const override
  {
    PYBIND11_OVERRIDE_PURE_NAME(ShapeBase*, ShapeBase, "__copy__", clone);
  };
  void scaleAndPadd(double scale, double padd) override
  {
    PYBIND11_OVERRIDE_PURE_NAME(void, ShapeBase, "scale_and_padd", scaleAndPadd, scale, padd);
  };
};

template <class InheritedShapeBase>
class PyInheritedShape : public PyShape<InheritedShapeBase>
{
public:
  using PyShape<InheritedShapeBase>::PyShape;  // Inherit constructors
  InheritedShapeBase* clone() const override
  {
    PYBIND11_OVERRIDE_NAME(InheritedShapeBase*, InheritedShapeBase, "__copy__", clone);
  }
  void scaleAndPadd(double scale, double padd) override
  {
    PYBIND11_OVERRIDE_NAME(void, InheritedShapeBase, "scale_and_padd", scaleAndPadd, scale, padd);
  };
};

void define_shapes(py::module& m)
{
  py::enum_<ShapeType>(m, "ShapeType")
      .value("unknown_shape", ShapeType::UNKNOWN_SHAPE)
      .value("sphere", ShapeType::SPHERE)
      .value("cylinder", ShapeType::CYLINDER)
      .value("cone", ShapeType::CONE)
      .value("box", ShapeType::BOX)
      .value("plane", ShapeType::PLANE)
      .value("mesh", ShapeType::MESH)
      .value("octree", ShapeType::OCTREE)
      .export_values();

  py::class_<Shape, PyShape<>>(m, "Shape", R"(
    A basic definition of a shape. Shapes are considered centered at origin
    )")
      .def(py::init<>())
      .def("__copy__", &Shape::clone)
      .def(
          "__deepcopy__", [](const Shape& self, py::dict&) { return self.clone(); }, py::arg("memo"))
      .def("__repr__",
           [](const Shape& s) {
             std::ostringstream oss;
             s.print(oss);
             return oss.str();
           })
      .def("scale", &Shape::scale)
      .def("padd", &Shape::padd)
      .def_property_readonly("is_fixed", &Shape::isFixed)
      .def_readonly("shape_type", &Shape::type);

  py::class_<Sphere, Shape, PyInheritedShape<Sphere>>(m, "Sphere")
      .def(py::init<>())
      .def(py::init<double>(), py::arg("r"))
      .def_readwrite("radius", &Sphere::radius);

  py::class_<Cylinder, Shape, PyInheritedShape<Cylinder>>(m, "Cylinder")
      .def(py::init<>())
      .def(py::init<double, double>(), py::arg("r"), py::arg("l"))
      .def("scale", (void(Cylinder::*)(double, double)) & Cylinder::scale, py::arg("scale_radius"),
           py::arg("scale_length"))
      .def("padd", (void(Cylinder::*)(double, double)) & Cylinder::padd, py::arg("padd_radius"), py::arg("padd_length"))
      .def("scale_and_padd", (void(Cylinder::*)(double, double, double, double)) & Cylinder::scaleAndPadd,
           py::arg("scale_radius"), py::arg("scale_length"), py::arg("padd_radius"), py::arg("padd_length"))
      .def_readwrite("length", &Cylinder::length)
      .def_readwrite("radius", &Cylinder::radius);

  py::class_<Cone, Shape, PyInheritedShape<Cone>>(m, "Cone")
      .def(py::init<>())
      .def(py::init<double, double>(), py::arg("r"), py::arg("l"))
      .def("scale", (void(Cone::*)(double, double)) & Cone::scale, py::arg("scale_radius"), py::arg("scale_length"))
      .def("padd", (void(Cone::*)(double, double)) & Cone::padd, py::arg("padd_radius"), py::arg("padd_length"))
      .def("scale_and_padd", (void(Cone::*)(double, double, double, double)) & Cone::scaleAndPadd,
           py::arg("scale_radius"), py::arg("scale_length"), py::arg("padd_radius"), py::arg("padd_length"))
      .def_readwrite("length", &Cone::length)
      .def_readwrite("radius", &Cone::radius);

  py::class_<Box, Shape, PyInheritedShape<Box>>(m, "Box")
      .def(py::init<>())
      .def(py::init<double, double, double>(), py::arg("x"), py::arg("y"), py::arg("z"))
      .def("scale", (void(Box::*)(double, double, double)) & Box::scale, py::arg("scale_x"), py::arg("scale_y"),
           py::arg("scale_z"))
      .def("padd", (void(Box::*)(double, double, double)) & Box::padd, py::arg("padd_x"), py::arg("padd_y"),
           py::arg("padd_z"))
      .def("scale_and_padd", (void(Box::*)(double, double, double, double, double, double)) & Box::scaleAndPadd,
           py::arg("scale_x"), py::arg("scale_y"), py::arg("scale_z"), py::arg("padd_x"), py::arg("padd_y"),
           py::arg("padd_z"))
      .def_readwrite("size", &Box::size);
}

}  // namespace geometric_shapes_py