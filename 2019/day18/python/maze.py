import collections
import itertools
import heapq


class Maze:
    """Class finding its way through the maze."""

    def __init__(self, fileName, multi_robots=False):
        self.grid = self.read_map(fileName)
        self.y, self.x, self.total_keys = self.find_start_and_keys()
        self.pos = self.initialize_position(multi_robots)

    def compute_shortest_path(self):
        """Traverse the grid by first looking for the reachable keys and select
        nodes with shortest distance while traversing."""

        # Initial node - depth, position, collection of keys
        q = [(0, self.pos, frozenset())]

        # Visited nodes
        visited = set()

        while q:

            # Obtain shortest the node
            depth, current_pos, keys = heapq.heappop(q)

            # We are done if all keys are found
            if keys == self.total_keys:
                return depth

            # Skip node if visited before
            if (current_pos, keys) in visited:
                continue

            # Update visited node
            visited.add((current_pos, keys))

            # Go through positions
            for i, (current_y, current_x) in enumerate(current_pos):
                # Go through the reachable keys for each position
                for d, y, x, key in self.reachable_keys(
                    current_y, current_x, keys
                ):
                    # Update positions list
                    new_pos = (
                        current_pos[0:i] + ((y, x),) + current_pos[i + 1 :]
                    )
                    # Push to heap new depth, new position, and collected keys
                    heapq.heappush(
                        q, (depth + d, new_pos, keys | frozenset([key]))
                    )

    def reachable_keys(self, y_, x_, keys):
        """Given start position y_,x_, and keys find other reachable keys"""

        # Initialize node to go through
        q = collections.deque([(y_, x_, 0)])

        # Initialize visited nodes
        visited = set()

        # Search directions
        directions = ((1, 0), (-1, 0), (0, 1), (0, -1))

        while q:

            # Get the node
            y, x, depth = q.popleft()

            # If we reach a key which we do not have, yield it
            if self.grid[y][x].islower() and self.grid[y][x] not in keys:
                yield depth, y, x, self.grid[y][x]
                continue

            # Search neighbors
            for dy, dx in directions:
                y_new, x_new = y + dy, x + dx

                # Skip if we have visited the node
                if ((y_new, x_new)) in visited:
                    continue

                # Add to visited node
                visited.add((y_new, x_new))

                value = self.grid[y_new][x_new]

                if value != "#" and (
                    not value.isupper() or value.lower() in keys
                ):
                    q.append((y_new, x_new, depth + 1))

    def initialize_position(self, multi_robots):
        """Set the initial position depending on part one or part two"""
        if multi_robots:
            y, x = self.y, self.x
            self.grid[y - 1] = (
                self.grid[y - 1][:x] + "#" + self.grid[y - 1][x + 1 :]
            )
            self.grid[y] = (
                self.grid[y][: x - 1] + "###" + self.grid[y][x + 2 :]
            )
            self.grid[y + 1] = (
                self.grid[y + 1][:x] + "#" + self.grid[y + 1][x + 1 :]
            )
            return (
                (self.y - 1, self.x - 1),
                (self.y - 1, self.x + 1),
                (self.y + 1, self.x - 1),
                (self.y + 1, self.x + 1),
            )
        else:
            return ((self.y, self.x),)

    def find_start_and_keys(self):
        """Figure out middle of the map and how many keys are present"""
        # Flatten grid
        linear_grid = list(itertools.chain.from_iterable(self.grid))

        # Width and height of grid
        width = len(self.grid[0])
        start_index = linear_grid.index("@")

        # Divide index with length and width
        y, x = start_index // width, start_index % width

        # If the key is a lower case letter then include
        total_keys = set(key for key in linear_grid if key.islower())

        return y, x, total_keys

    def read_map(self, fileName):
        """Read the map"""
        with open(fileName) as f:
            return f.read().splitlines()

    def print_map(self):
        """Print the map"""
        for row in self.grid:
            print("".join(row))
