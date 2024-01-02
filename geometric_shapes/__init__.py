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
