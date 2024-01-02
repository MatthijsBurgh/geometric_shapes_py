from copy import deepcopy
import sys

import pytest

import geometric_shapes as gs

from common import load_mesh


@pytest.fixture()
def plane() -> gs.Plane:
    return gs.Plane(1.0, 1.0, 1.0, 1.0)


@pytest.fixture()
def octree() -> gs.OcTree:
    return gs.OcTree()


@pytest.fixture()
def sphere() -> gs.Sphere:
    return gs.Sphere(1.0)


@pytest.fixture()
def cylinder() -> gs.Cylinder:
    return gs.Cylinder(1.0, 2.0)


@pytest.fixture()
def cone() -> gs.Cone:
    return gs.Cone(1.0, 2.0)


@pytest.fixture()
def box() -> gs.Box:
    return gs.Box(1.0, 2.0, 3.0)


@pytest.fixture()
def mesh() -> gs.Mesh:
    return load_mesh("box.dae")


def test_plane_scale_and_padd(plane: gs.Plane) -> None:
    plane2 = deepcopy(plane)
    assert plane2.a == plane.a
    assert plane2.b == plane.b
    assert plane2.c == plane.c
    assert plane2.d == plane.d

    plane2.scale(2.0)
    assert plane2.a == plane.a
    assert plane2.b == plane.b
    assert plane2.c == plane.c
    assert plane2.d == plane.d

    plane2.padd(1.0)
    assert plane2.a == plane.a
    assert plane2.b == plane.b
    assert plane2.c == plane.c
    assert plane2.d == plane.d

    plane2.scale_and_padd(2.0, 1.0)
    assert plane2.a == plane.a
    assert plane2.b == plane.b
    assert plane2.c == plane.c
    assert plane2.d == plane.d


def test_octree_scale_and_padd_empty(octree: gs.OcTree) -> None:
    octree.scale(2.0)
    octree.padd(1.0)
    octree.scale_and_padd(2.0, 1.0)


def test_sphere_scale_and_padd(sphere: gs.Sphere) -> None:
    sphere2 = deepcopy(sphere)
    assert sphere2.radius == sphere.radius
    radius = sphere2.radius

    sphere2.scale(2.0)
    assert sphere2.radius == 2.0 * radius
    radius = sphere2.radius

    sphere2.padd(1.0)
    assert sphere2.radius == radius + 1.0
    radius = sphere2.radius

    sphere2.scale_and_padd(2.0, 1.0)
    assert sphere2.radius == 2.0 * radius + 1.0


def test_cylinder_scale_and_padd(cylinder: gs.Cylinder) -> None:
    cylinder2 = deepcopy(cylinder)
    assert cylinder2.radius == cylinder.radius
    assert cylinder2.length == cylinder.length
    radius = cylinder2.radius
    length = cylinder2.length

    cylinder2.scale(2.0)
    assert cylinder2.radius == 2.0 * radius
    assert cylinder2.length == 2.0 * length
    radius = cylinder2.radius
    length = cylinder2.length

    cylinder2.padd(1.0)
    assert cylinder2.radius == radius + 1.0
    assert cylinder2.length == length + 2 * 1.0
    radius = cylinder2.radius
    length = cylinder2.length

    cylinder2.scale_and_padd(2.0, 1.0)
    assert cylinder2.radius == 2.0 * radius + 1.0
    assert cylinder2.length == 2.0 * length + 2 * 1.0
    radius = cylinder2.radius
    length = cylinder2.length

    cylinder2.scale_and_padd(1.0, 3.0, 1.0, 3.0)
    assert cylinder2.radius == 1.0 * radius + 1.0
    assert cylinder2.length == 3.0 * length + 2 * 3.0
    radius = cylinder2.radius
    length = cylinder2.length

    cylinder2.scale(2.0, 1.5)
    assert cylinder2.radius == 2.0 * radius
    assert cylinder2.length == 1.5 * length
    radius = cylinder2.radius
    length = cylinder2.length

    cylinder2.padd(2.0, 3.0)
    assert cylinder2.radius == radius + 2.0
    assert cylinder2.length == length + 2 * 3.0


def test_cone_scale_and_padd(cone: gs.Cone) -> None:
    cone2 = deepcopy(cone)
    assert cone2.radius == cone.radius
    assert cone2.length == cone.length
    radius = cone2.radius
    length = cone2.length

    cone2.scale(2.0)
    assert cone2.radius == 2.0 * radius
    assert cone2.length == 2.0 * length
    radius = cone2.radius
    length = cone2.length

    cone2.padd(1.0)
    assert cone2.radius == radius + 1.0
    assert cone2.length == length + 2 * 1.0
    radius = cone2.radius
    length = cone2.length

    cone2.scale_and_padd(2.0, 1.0)
    assert cone2.radius == 2.0 * radius + 1.0
    assert cone2.length == 2.0 * length + 2 * 1.0
    radius = cone2.radius
    length = cone2.length

    cone2.scale_and_padd(1.0, 3.0, 1.0, 3.0)
    assert cone2.radius == 1.0 * radius + 1.0
    assert cone2.length == 3.0 * length + 2 * 3.0
    radius = cone2.radius
    length = cone2.length

    cone2.scale(2.0, 1.5)
    assert cone2.radius == 2.0 * radius
    assert cone2.length == 1.5 * length
    radius = cone2.radius
    length = cone2.length

    cone2.padd(2.0, 3.0)
    assert cone2.radius == radius + 2.0
    assert cone2.length == length + 2 * 3.0


def test_box_scale_and_padd(box: gs.Box) -> None:
    box2 = deepcopy(box)
    assert box2.x == box.x
    assert box2.y == box.y
    assert box2.z == box.z
    x = box2.x
    y = box2.y
    z = box2.z

    box2.scale(2.0)
    assert box2.x == 2.0 * x
    assert box2.y == 2.0 * y
    assert box2.z == 2.0 * z
    x = box2.x
    y = box2.y
    z = box2.z

    box2.padd(1.0)
    assert box2.x == x + 2 * 1.0
    assert box2.y == y + 2 * 1.0
    assert box2.z == z + 2 * 1.0
    x = box2.x
    y = box2.y
    z = box2.z

    box2.scale_and_padd(2.0, 1.0)
    assert box2.x == 2.0 * x + 2 * 1.0
    assert box2.y == 2.0 * y + 2 * 1.0
    assert box2.z == 2.0 * z + 2 * 1.0
    x = box2.x
    y = box2.y
    z = box2.z

    box2.scale_and_padd(1.0, 2.0, 3.0, 1.0, 2.0, 3.0)
    assert box2.x == 1.0 * x + 2 * 1.0
    assert box2.y == 2.0 * y + 2 * 2.0
    assert box2.z == 3.0 * z + 2 * 3.0
    x = box2.x
    y = box2.y
    z = box2.z

    box2.scale(1.0, 2.0, 3.0)
    assert box2.x == 1.0 * x
    assert box2.y == 2.0 * y
    assert box2.z == 3.0 * z
    x = box2.x
    y = box2.y
    z = box2.z

    box2.padd(1.0, 2.0, 3.0)
    assert box2.x == x + 2 * 1.0
    assert box2.y == y + 2 * 2.0
    assert box2.z == z + 2 * 3.0


def test_mesh_scale_and_padd(mesh: gs.Mesh) -> None:
    assert mesh.vertex_count == 8
    assert mesh.triangle_count == 12

    mesh2 = deepcopy(mesh)
    assert mesh2.vertex_count == mesh.vertex_count
    assert mesh2.triangle_count == mesh.triangle_count


if __name__ == "__main__":
    sys.exit(pytest.main())
