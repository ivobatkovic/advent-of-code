import queue

import copy


class Jiggsaw:
    def __init__(self, images):
        self.images = copy.deepcopy(images)
        self.image_sides = self.compute_image_sides()
        self.complete_image = dict()
        self.combined_image = None

    def compute_image_sides(self):
        # Go through each image and compute the right, top, left, bottom sides
        sides = dict()
        for key, val in self.images.items():
            sides[key] = []
            for dir in range(4):
                sides[key].append([dir, self.get_side(key, dir)])
        return sides

    def get_side(self, tile, dir=0):
        row = 0 if dir == 1 else -1
        col = 0 if dir == 2 else -1
        # Return top or bottom side
        if dir % 2 == 1:
            return self.images[tile][row]
        # Return left or right side
        else:
            return "".join(
                [
                    self.images[tile][i][col]
                    for i in range(len(self.images[tile]))
                ]
            )

    def rotate(self, tile, n_times):
        # Rotate an image 90 degrees counter-clockwise n_times
        for k in range(4 - n_times):
            self.images[tile] = [
                "".join(rows) for rows in list(zip(*self.images[tile][::-1]))
            ]

    def organize_tile(self, tile, dir_to, dir_from):

        # Transform the neighboring map
        if dir_to == dir_from:
            if dir_to == 1 or dir_to == 3:
                self.images[tile].reverse()
            else:
                self.images[tile] = [m[::-1] for m in self.images[tile]]
        elif (dir_to + dir_from) == 3 and (dir_from == 3 or dir_from == 1):
            self.rotate(tile, 3)
        elif (dir_to + dir_from) == 3 and (dir_from == 0 or dir_from == 2):
            self.rotate(tile, 1)
        elif (dir_to + dir_from) == 5 or (dir_to + dir_from) == 1:
            self.rotate(tile, 1)
            self.images[tile].reverse()

        # Update new image sides
        for dir in range(4):
            self.image_sides[tile][dir][1] = self.get_side(tile, dir)

    def find_matching_tile(self, current, tile, dir_to):
        # Find a tile that matches the current side
        current_side = self.image_sides[current][dir_to][1]

        # Go through all four sides of the tile
        for dir_from, tile_side in self.image_sides[tile]:
            forward_match = current_side == tile_side
            if current_side == tile_side[::-1]:
                forward_match = True
                # Apply transformation to fix the tile
                if dir_from % 2 == 0:
                    self.images[tile].reverse()
                else:
                    self.images[tile] = [m[::-1] for m in self.images[tile]]

            # If we found a matchign tile, organize it properly to fit the map
            if forward_match:
                self.organize_tile(tile, dir_to, dir_from)
                return True

        return False

    def solve(self):

        # Start from any (first) key in the input
        current = list(self.image_sides.keys())[0]
        visited = set()
        decided = set(current)

        # Store the output map
        complete_images = dict()
        complete_images[0, 0] = [current, self.images[current]]

        # Queue to go through all tiles
        q = queue.Queue()
        q.put([current, 0, 0])

        while not q.empty():
            # Get next in queue
            current, y, x = q.get()
            if current in visited:
                continue
            visited.add(current)

            # Check the tiles
            for tile in self.image_sides.keys():
                if tile in visited or current == tile or tile in decided:
                    continue

                # Check all our "directions" with the other ones
                for dir, current_side in self.image_sides[current]:

                    found = self.find_matching_tile(current, tile, dir)
                    if found:
                        # Set direction to assign the tile
                        dx = 1 if dir == 0 else -1 if dir == 2 else 0
                        dy = 1 if dir == 1 else -1 if dir == 3 else 0

                        # Update the complete image
                        complete_images[y + dy, x + dx] = [
                            tile,
                            self.images[tile],
                        ]
                        # Add tile to queue
                        q.put([tile, y + dy, x + dx])
                        decided.add(tile)
                        break
        # Flip the image upside down to match the directions
        for keys in complete_images:
            complete_images[keys][-1] = complete_images[keys][-1][::-1]
        self.complete_images = complete_images

        # Combine the complete images into a big image
        self.combine_images()

    def combine_images(self):
        # Combine all tiles into a big image
        combined_image = []
        n_rows = len(self.complete_images[0, 0][-1])
        ymin, xmin = min(self.complete_images, key=tuple)
        ymax, xmax = max(self.complete_images, key=tuple)

        # Go through each connected of tiles
        for y in range(ymin, ymax + 1):
            # For each tile, go through its rows
            for row in range(1, n_rows - 1):
                row_ = ""
                # Go through each row-tile
                for x in range(xmin, xmax + 1):
                    row_ += self.complete_images[y, x][-1][row][1:-1]
                combined_image.append(row_)

        self.combined_image = combined_image

    def get_corners(self):
        # Return corner tiles
        ymin, xmin = min(self.complete_images, key=tuple)
        ymax, xmax = max(self.complete_images, key=tuple)

        corners = [(ymin, xmin), (ymin, xmax), (ymax, xmin), (ymax, xmax)]
        return [int(self.complete_images[corner][0]) for corner in corners]

    def find_monster(self, monster, h_monster, w_monster, row, col):
        for i in range(h_monster):
            for j in range(w_monster):
                # If monster and image don't overlap: break
                if (
                    monster[i][j] == "#"
                    and self.combined_image[row + i][col + j] != "#"
                ):
                    return False
        return True

    def find_monsters(self, monster):

        h, w = len(self.combined_image), len(self.combined_image[0])
        h_monster, w_monster = len(monster), len(monster[0])

        op = 1
        for _ in range(8):
            nMonsters = 0
            # Go through a mask of monster height and width size
            for row in range(0, h - h_monster):
                for col in range(0, w - w_monster):
                    # Go through the monster sub-mask
                    if self.find_monster(
                        monster, h_monster, w_monster, row, col
                    ):
                        nMonsters += 1
            if nMonsters > 0:
                return nMonsters

            # Reverse image
            if op == 1:
                self.combined_image.reverse()
            # If no match, reverse back and rotate
            else:
                self.combined_image.reverse()
                self.combined_image = [
                    "".join(rows)
                    for rows in list(zip(*self.combined_image[::-1]))
                ]
            op *= -1
        return 0

    def get_rough_waters(self, monster):
        # Get number of monsters
        nr_monsters = self.find_monsters(monster)

        # Check how many '#' the monster has
        size_monster = sum(
            [1 for row in monster for elem in row if elem == "#"]
        )
        # Check how many '#' the image has
        water = self.combined_image
        rough_waters = sum([1 for row in water for wtr in row if wtr == "#"])
        return rough_waters - nr_monsters * size_monster
