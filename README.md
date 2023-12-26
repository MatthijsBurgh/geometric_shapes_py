# geometric_shapes_py

This package contains generic definitions of geometric shapes and bodies, as well as tools for operating on shape messages.
Shapes represent only the form of an object.
Bodies are shapes at a particular pose. Routines such as point containment and ray intersections are provided.

Supported shapes:

- sphere
- box
- cone
- cylinder
- mesh

Note: Bodies for meshes compute the convex hull of those meshes in order to provide the point containment / ray intersection routines.

## Build Status

[![Formatting (pre-commit)](https://github.com/MatthijsBurgh/geometric_shapes_py/actions/workflows/format.yaml/badge.svg)](https://github.com/MatthijsBurgh/geometric_shapes_py/actions/workflows/format.yaml)
[![Build and Test](https://github.com/MatthijsBurgh/geometric_shapes_py/actions/workflows/build_and_test.yaml/badge.svg)](https://github.com/MatthijsBurgh/geometric_shapes_py/actions/workflows/build_and_test.yaml)
[![codecov](https://codecov.io/gh/MatthijsBurgh/geometric_shapes_py/graph/badge.svg?token=87L37CL0I6)](https://codecov.io/gh/MatthijsBurgh/geometric_shapes_py)

Code Coverage Grid:

[![Code Coverage Grid](https://codecov.io/gh/MatthijsBurgh/geometric_shapes_py/graphs/tree.svg?token=87L37CL0I6)](https://codecov.io/gh/MatthijsBurgh/geometric_shapes_py/graphs/tree.svg?token=87L37CL0I6)

Devel Job: [![Build Status](http://build.ros2.org/buildStatus/icon?job=Fsrc_uF__geometric_shapes_py__ubuntu_focal__source)](http://build.ros2.org/view/Fsrc_uF/job/Fsrc_uF__geometric_shapes_py__ubuntu_focal__source)

Debian Job: [![Build Status](http://build.ros2.org/buildStatus/icon?job=Fbin_uF64__geometric_shapes_py__ubuntu_focal_amd64__binary)](http://build.ros2.org/view/Fbin_uF64/job/Fbin_uF64__geometric_shapes_py__ubuntu_focal_amd64__binary)
