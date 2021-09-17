from os.path import dirname
from os.path import realpath
from os.path import join
import sys
import time

if sys.version_info.major == 3:
    from queue import Queue
else:
    from Queue import Queue

sys.path.append(join(dirname(realpath(__file__)), *[".."]))
from day6.utils import get_parents_and_neighbors


class Orbit:
    """Orbit computer class using Queues, as implemented in
    https://github.com/hoxovic/adventofcode2019."""

    def __init__(self, input_):
        """Initialize with a file location."""
        self.parents, self.neighbors = get_parents_and_neighbors(input_)

    def get_n_orbits(self):
        """Function that goes through the object connections and computes all
        direct  and indirect connections."""

        # Queue that iterates through all children from 'COM'
        q = Queue()
        for child in self.parents["COM"]:
            q.put((child, 1))

        # Go through children queue
        n_orbits = 0
        while not q.empty():
            node, n_parents = q.get()
            n_orbits += n_parents - 1

            # Add children to the current node
            for child in self.parents[node]:
                q.put((child, n_parents + 1))
        return n_orbits + len(self.parents) - 1

    def get_orbitals(self, start, stop):

        # Go through parent start node and search through children for end node
        q = Queue()
        for neighbor in self.neighbors[start]:
            q.put((neighbor, start, 1))

        # Go through queue by traversing neighbors
        while not q.empty():
            node, previous_node, dist = q.get()
            if node == stop:
                return dist - 2

            # Add new neighbors - disregard the node it came from
            neighbors = self.neighbors[node]
            neighbors.remove(previous_node)
            for neighbor in neighbors:
                q.put((neighbor, node, dist + 1))

        # No connection
        return None


def part1(input_):
    o = Orbit(input_)
    return o.get_n_orbits()


def part2(input_):
    o = Orbit(input_)
    return o.get_orbitals("YOU", "SAN")


def main():

    # Open data file and read through all lines
    file_location = "data/input.txt"
    try:
        dir_path = dirname(realpath(__file__))
        with open(join(dir_path, file_location), "r") as f:
            input_ = f.read()

        t0 = time.time()
        sol_part1 = part1(input_)
        time_end = round((time.time() - t0) * 1e3)

        print(
            "Solution to part one: %s (time taken %s[ms])"
            % (sol_part1, time_end)
        )

        t0 = time.time()
        sol_part2 = part2(input_)
        time_end = round((time.time() - t0) * 1e3)
        print(
            "Solution to part two: %s (time taken %s[ms])"
            % (sol_part2, time_end)
        )
    except IOError:
        print("Cannot find file at: " + file_location)


if __name__ == "__main__":
    main()
