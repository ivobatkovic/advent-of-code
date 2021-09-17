from os.path import dirname
from os.path import realpath
from os.path import join
import numpy as np
import time


def transform_input(input_):
    return [row.split(",") for row in input_.splitlines()]


def compute_wire_segments(wires):
    """Given the instructions in wires, the function returns an (N+1)x4 array
    of wire positions. First two elements are the x,y positions, the third
    element is the cummulated wire length, and the fourth element indicates if
    the line is vertical or horizontal."""

    # Wire segments container
    wire_segments = []

    # Go through each wire
    for wire in wires:

        # Start position
        pos = np.zeros((1, 4))

        # Initialize array
        wire_segment = np.zeros((len(wire) + 1, 4))

        # Move 'along' wire
        for i, w in enumerate(wire):

            # Initialize direction steps and orientation
            dx, dy, step, orientation = 0, 0, int(w[1:]), 0

            # Wire moves left or right
            if w[0] == "L" or w[0] == "R":
                dx = step if (w[0] == "R") else -step
            # Wire move up or down
            if w[0] == "U" or w[0] == "D":
                dy = step if (w[0] == "U") else -step
                orientation = 1

            # Update position
            pos += [dx, dy, step, orientation - pos[0, 3]]

            # Add position to wire_segment
            wire_segment[i + 1, :] = pos

        # Add wire segment to container
        wire_segments.append(wire_segment)

    # Return segments
    return wire_segments


def intersect(line1, line2):
    """Checks if line1: [A,B] intersects with line2: [C,D]. Assumes only
    horizontal and vertical lines."""

    # Check if lines are perpendicular
    if line1[1, -1] == line2[1, -1]:
        return None, None

    # Compute min and max bounds for line 1
    x1m, x1M = min(line1[:, 0]), max(line1[:, 0])
    y1m, y1M = min(line1[:, 1]), max(line1[:, 1])

    # Compute min and max bounds for line 2
    x2min, x2max = min(line2[:, 0]), max(line2[:, 0])
    y2min, y2max = min(line2[:, 1]), max(line2[:, 1])

    # Intersection condition
    if (x1M >= x2min) and (x1m <= x2max) and (y1M >= y2min) and (y1m <= y2max):

        # Compute intersection point
        p = [x2min, y1m] if (x1M - x1m) != 0 else [x1m, y2min]

        # Total wire steps
        wire_steps = line1[0, 2] + line2[0, 2]

        # Added wire steps to intersection point
        steps_to_point = sum(abs(line1[0, :2] - p)) + sum(
            abs(line2[0, :2] - p)
        )

        return p, (wire_steps + steps_to_point)

    return None, None


def intersect_wires(wire1, wire2):
    """Loop through the wire segments wire1 and wire2 and looks for possible
    intersections."""

    intersection, steps = [], []
    for i in range(len(wire1) - 1):
        for j in range(len(wire2) - 1):
            point, s = intersect(wire1[i : i + 2], wire2[j : j + 2])
            if point is not None:
                intersection.append(point)
                steps.append(s)
    return intersection, steps


def crossed_wires(wires):
    """This function assumes that the wires aren't routed along eachother,
    they will only cross perpendicularly, hence it is enough only to check
    vertical wire segments vs horizontal wire segments."""

    # Compute the wire positions for each wire
    wire_segments = compute_wire_segments(wires)

    # Try to intersect the two wire segments with eachother
    points, steps = intersect_wires(wire_segments[0], wire_segments[1])

    return points, steps


def part1(input_):
    input_ = transform_input(input_)
    points, steps = crossed_wires(input_)
    return int(min(np.sum(np.abs(points), axis=1)))


def part2(input_):
    input_ = transform_input(input_)
    points, steps = crossed_wires(input_)
    return int(min(steps))


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
