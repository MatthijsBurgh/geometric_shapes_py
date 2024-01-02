import sys

import pytest

from common import TRIANGLE_MESH_FILES, load_mesh


@pytest.mark.parametrize("mesh_file", TRIANGLE_MESH_FILES)
def test_assert_mesh(mesh_file: str):
    mesh = load_mesh(mesh_file)
    assert mesh is not None
    assert isinstance(mesh.vertex_count, int)
    assert mesh.vertex_count == 3
    assert isinstance(mesh.triangle_count, int)
    assert mesh.triangle_count == 1


if __name__ == "__main__":
    sys.exit(pytest.main())
