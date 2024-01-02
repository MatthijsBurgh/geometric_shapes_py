from pathlib import Path

import geometric_shapes as gs

TRIANGLE_MESH_FILES = [
    "triangle.stl",
    "triangle_1m.dae",
    "triangle_10m.dae",
    "triangle_no_unit.dae",
    "triangle_no_up.dae",
    "triangle_x_up.dae",
    "triangle_y_up.dae",
    "triangle_z_up.dae",
]


MESH_FILES = ["box.dae", "cube.stl", "forearm_roll.stl"].extend(TRIANGLE_MESH_FILES)


def load_mesh(mesh: str) -> gs.Mesh:
    path = Path(__file__).resolve().parent / "resources" / mesh
    print(f"Loading mesh from file://{path}")
    return gs.create_mesh_from_resource(f"file://{path}")
