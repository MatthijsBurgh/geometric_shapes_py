import sys

import pytest

import geometric_shapes as gs

from common import load_mesh


class Meshes:
    def __init__(self):
        self.box = gs.Box(1, 1, 1)
        self.box_mesh = gs.create_mesh_from_shape(self.box)
        self.cube = load_mesh("cube.stl")


@pytest.fixture()
def meshes() -> Meshes:
    return Meshes()


def test_box_vertex_count(meshes: Meshes):
    assert meshes.box_mesh.vertex_count == meshes.cube.vertex_count
    assert meshes.box_mesh.triangle_count == meshes.cube.triangle_count


if __name__ == "__main__":
    sys.exit(pytest.main())
