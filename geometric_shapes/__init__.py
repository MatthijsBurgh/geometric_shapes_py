# Software License Agreement (BSD 3-Clause License)
#
#  Copyright (c) 2024, VBTI
#  All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions are met:
#
#  1. Redistributions of source code must retain the above copyright notice, this
#  list of conditions and the following disclaimer.
#
#  2. Redistributions in binary form must reproduce the above copyright notice,
#  this list of conditions and the following disclaimer in the documentation
#  and/or other materials provided with the distribution.
#
#  3. Neither the name of the copyright holder nor the names of its
#  contributors may be used to endorse or promote products derived from
#  this software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
#  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
#  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
#  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
#  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
#  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

from rpyutils import add_dll_directories_from_env

# Since Python 3.8, on Windows we should ensure DLL directories are explicitly added
# to the search path.
# See https://docs.python.org/3/whatsnew/3.8.html#bpo-36085-whatsnew
# with add_dll_directories_from_env("PATH"):
# from geometric_shapes._geometric_shapes_py import (
#     Box,
#     Cone,
#     Cylinder,
#     Mesh,
#     OcTree,
#     Plane,
#     Shape,
#     ShapeType,
#     Sphere,
#     construct_marker_from_shape,
#     construct_msg_from_shape,
#     construct_shape_from_msg,
#     shape_string_name,
#     shape_to_text,
#     text_to_shape,
# )
# from geometric_shapes._geometric_shapes_py import *
from geometric_shapes._geometric_shapes_py import *

del add_dll_directories_from_env

# __all__ = [
#     "Box",
#     "Cone",
#     "Cylinder",
#     "Mesh",
#     "OcTree",
#     "Plane",
#     "Shape",
#     "ShapeType",
#     "Sphere",
#     "construct_marker_from_shape",
#     "construct_msg_from_shape",
#     "construct_shape_from_msg",
#     "create_mesh_from_binary",
#     "create_mesh_from_resource",
#     "create_mesh_from_shape",
#     "mesh_to_stl_binary",
#     "shape_string_name",
#     "shape_to_text",
#     "text_to_shape",
# ]
