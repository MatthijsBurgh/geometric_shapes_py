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

import io
from _typeshed import Incomplete
from typing import ClassVar, overload

class Box(Shape):
    size: Incomplete
    x: Incomplete
    y: Incomplete
    z: Incomplete
    @overload
    def __init__(self) -> None: ...
    @overload
    def __init__(self, x: float, y: float, z: float) -> None: ...
    @overload
    def padd(self, padd: float) -> None: ...
    @overload
    def padd(self, padd_x: float, padd_y: float, padd_z: float) -> None: ...
    @overload
    def scale(self, scale: float) -> None: ...
    @overload
    def scale(self, scale_x: float, scale_y: float, scale_z: float) -> None: ...
    @overload
    def scale_and_padd(self, scale: float, padd: float) -> None: ...
    @overload
    def scale_and_padd(
        self,
        scale_x: float,
        scale_y: float,
        scale_z: float,
        padd_x: float,
        padd_y: float,
        padd_z: float,
    ) -> None: ...

class Cone(Shape):
    length: Incomplete
    radius: Incomplete
    @overload
    def __init__(self) -> None: ...
    @overload
    def __init__(self, r: float, l: float) -> None: ...
    @overload
    def padd(self, padd: float) -> None: ...
    @overload
    def padd(self, padd_radius: float, padd_length: float) -> None: ...
    @overload
    def scale(self, scale: float) -> None: ...
    @overload
    def scale(self, scale_radius: float, scale_length: float) -> None: ...
    @overload
    def scale_and_padd(self, scale: float, padd: float) -> None: ...
    @overload
    def scale_and_padd(
        self,
        scale_radius: float,
        scale_length: float,
        padd_radius: float,
        padd_length: float,
    ) -> None: ...

class Cylinder(Shape):
    length: Incomplete
    radius: Incomplete
    @overload
    def __init__(self) -> None: ...
    @overload
    def __init__(self, r: float, l: float) -> None: ...
    @overload
    def padd(self, padd: float) -> None: ...
    @overload
    def padd(self, padd_radius: float, padd_length: float) -> None: ...
    @overload
    def scale(self, scale: float) -> None: ...
    @overload
    def scale(self, scale_radius: float, scale_length: float) -> None: ...
    @overload
    def scale_and_padd(self, scale: float, padd: float) -> None: ...
    @overload
    def scale_and_padd(
        self,
        scale_radius: float,
        scale_length: float,
        padd_radius: float,
        padd_length: float,
    ) -> None: ...

class Mesh(Shape):
    @overload
    def __init__(self) -> None: ...
    @overload
    def __init__(self, vertex_count: int, triangle_count: int) -> None: ...
    @overload
    def padd(self, padd: float) -> None: ...
    @overload
    def padd(self, padd_x: float, padd_y: float, padd_z: float) -> None: ...
    @overload
    def scale(self, scale: float) -> None: ...
    @overload
    def scale(self, scale_x: float, scale_y: float, scale_z: float) -> None: ...
    @overload
    def scale_and_padd(self, scale: float, padd: float) -> None: ...
    @overload
    def scale_and_padd(
        self,
        scale_x: float,
        scale_y: float,
        scale_z: float,
        padd_x: float,
        padd_y: float,
        padd_z: float,
    ) -> None: ...
    @property
    def triangle_count(self) -> int: ...
    @property
    def vertex_count(self) -> int: ...

class OcTree(Shape):
    def __init__(self) -> None: ...

class Plane(Shape):
    a: float
    b: float
    c: float
    d: float
    @overload
    def __init__(self) -> None: ...
    @overload
    def __init__(self, pa: float, pb: float, pc: float, pd: float) -> None: ...

class Shape:
    def __init__(self) -> None: ...
    def padd(self, padd: float) -> None: ...
    def scale(self, scale: float) -> None: ...
    def scale_and_padd(self, scale: float, padd: float) -> None: ...
    def __copy__(self) -> Shape: ...
    def __deepcopy__(self, memo: dict) -> Shape: ...
    @property
    def is_fixed(self): ...
    @property
    def shape_type(self): ...

class ShapeType:
    __members__: ClassVar[dict] = ...  # read-only
    __entries: ClassVar[dict] = ...
    box: ClassVar[ShapeType] = ...
    cone: ClassVar[ShapeType] = ...
    cylinder: ClassVar[ShapeType] = ...
    mesh: ClassVar[ShapeType] = ...
    octree: ClassVar[ShapeType] = ...
    plane: ClassVar[ShapeType] = ...
    sphere: ClassVar[ShapeType] = ...
    unknown_shape: ClassVar[ShapeType] = ...
    def __init__(self, value: int) -> None: ...
    def __eq__(self, other: object) -> bool: ...
    def __hash__(self) -> int: ...
    def __index__(self) -> int: ...
    def __int__(self) -> int: ...
    def __ne__(self, other: object) -> bool: ...
    @property
    def name(self) -> str: ...
    @property
    def value(self) -> int: ...

class Sphere(Shape):
    radius: Incomplete
    @overload
    def __init__(self) -> None: ...
    @overload
    def __init__(self, r: float) -> None: ...

def construct_marker_from_shape(*args, **kwargs): ...
def construct_msg_from_shape(*args, **kwargs): ...
def construct_shape_from_msg(msg) -> Shape: ...
def create_mesh_from_binary(*args, **kwargs): ...
def create_mesh_from_resource(*args, **kwargs): ...
def create_mesh_from_shape(*args, **kwargs): ...
def mesh_to_stl_binary(mesh, binary_stream: io.BytesIO) -> None: ...
def shape_string_name(shape: Shape) -> str: ...
def shape_to_text(shape: Shape, binary_stream: io.BytesIO) -> None: ...
def text_to_shape(binary_stream: io.BytesIO) -> Shape: ...
