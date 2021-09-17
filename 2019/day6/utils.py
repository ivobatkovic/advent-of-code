from collections import defaultdict


def get_parents_and_neighbors(input_):
    """Reads each line in the file and connects the objects through a
    dictionary."""
    parents, neighbors = defaultdict(list), defaultdict(list)

    for line in input_.splitlines():

        parent, child = line.strip().split(")")
        parents[parent].append(child)
        neighbors[parent].append(child)
        neighbors[child].append(parent)
    return parents, neighbors
