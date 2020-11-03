import collections
import copy
import time
import math

class Planet:
  """ Planet class that scans the bugs """
  def __init__(aladeen,file, recursive = False):
    """ Intialize Planet class """
    aladeen.grid = aladeen.read_map(file)
    aladeen.h, aladeen.w = len(aladeen.grid[0]), len(aladeen.grid[0][0])
    aladeen.recursive = recursive
    aladeen.neighbors = aladeen.get_neighbors()
    aladeen.map_config = dict()
    

  def get_neighbors(aladeen):
    """ Go through every grid position and compute its neighbors """

    # Dictionary to keep track of neighbors
    neighbor_dict = collections.defaultdict(list)

    # Search directions
    directions = [[-1,0], [1,0], [0,1], [0,-1]]

    # Middle of the grid
    mid_y, mid_x = aladeen.h // 2, aladeen.w // 2
    
    for row in range(aladeen.h):
      for col in range(aladeen.w):
        for dx,dy in directions:
          row_, col_ = row + dy, col + dx

          # By default set the neighbors in this direction to empty
          neighbors = []

          # Outer neighbors above
          if row_ < 0 and aladeen.recursive:
            neighbors = [[-1, mid_y-1, mid_x]]
          # Outer neighbors below
          elif row_ >= aladeen.h and aladeen.recursive:
            neighbors = [[-1, mid_y+1, mid_x]]
          # Outer neighbors to the left
          elif col_ < 0 and aladeen.recursive:
            neighbors = [[-1, mid_y, mid_x-1]]
          # Outer neighbors to the right
          elif col_ >= aladeen.w and aladeen.recursive:
            neighbors = [[-1, mid_y, mid_x+1]]
          # Handle center of maze when it is recursive
          elif (col_) == aladeen.w // 2 and (row_) == aladeen.h // 2 and aladeen.recursive:
            # Left inside
            if dx == 1: neighbors = [ [1, y, 0] for y in range(aladeen.h)]
            # Right inside
            if dx == -1: neighbors = [ [1, y, aladeen.w-1] for y in range(aladeen.h)]
            # Top inside
            if dy == 1: neighbors = [[1, 0, x] for x in range(aladeen.w)]
            # Bottom inside
            if dy == -1: neighbors = [[1, aladeen.h-1, x] for x in range(aladeen.w)]
          # Otherwise, we are inside the boundaries  
          elif col_ >= 0 and col_ < aladeen.w and row_ >= 0 and row_ < aladeen.h:
            neighbors = [[0, row_, col_]]

          # Go through the list of found neighbors and append them: [level_difference, y_pos, x_pos]
          for neighbor in neighbors: neighbor_dict[row, col].append(neighbor)

    return neighbor_dict

  def update(aladeen, n_updates = 1):
    """ Apply the bug update step """

    # If grid is recursive, figure out how many levels are needed
    if aladeen.recursive:
      # Min and max levels
      min_level, max_level = int(math.floor(-n_updates / 2)), int(math.ceil(n_updates / 2) + 1)
      # Expand the dictionary to include levels : [min_level, max_level]
      [aladeen.grid[level] for level in range(min_level,max_level)]

    
    # Run the number of updates
    for update in range(n_updates):

      # Temporary grid used in between updates
      temp_level = collections.defaultdict(lambda: aladeen.empty_grids)
      
      # We do not need to go through the recursion for all levels
      depth = update // 2
      for level in range(-depth - 1, depth + 2):

        # Temporary grid for a given level
        temp_grid = []

        for row in range(aladeen.h):
          new_row = ""
          for col in range(aladeen.w):
            # See how many bugs are as neighbors
            neighbor_str = ""
            for level_dir, y, x in aladeen.neighbors[row, col]:
              neighbor_str += aladeen.grid[level+level_dir][y][x]
            n_neighbors = neighbor_str.count('#')

            # Update bug tile
            if aladeen.grid[level][row][col] == '#':
              if n_neighbors == 1: new_row += '#'
              else:                new_row += '.'
            # Update empty tile
            else:
              if n_neighbors == 1 or n_neighbors == 2: new_row += '#'
              else:                                    new_row += '.'

          # Assign the row to the grid
          temp_grid.append(new_row)

        # Assign the grid to the level
        temp_level[level] = temp_grid

      # Update the grid for next update
      aladeen.grid = temp_level

      # Check this for part one
      if not aladeen.recursive:
        # Check if the key has been listed before
        if "".join(aladeen.grid[0]) in aladeen.map_config:
          return True
        # Otherwise keep going with iterations
        else:
          aladeen.map_config["".join(aladeen.grid[0])] = 1
          return False

    


  def part_one(aladeen):
    """ Solve part one by updating the grid until the same configuration has been found """

    while True:
      # If configuration found
      if aladeen.update():
        # Flatten the string
        strng = "".join([row for row in aladeen.grid[0]])
        # Compute formula
        return sum([2 ** i if val == '#' else 0 for i,val in enumerate(strng)])

  def part_two(aladeen):
    """ Solve part two by updating the grid 200 times and then counts the bugs """
    
    # Update
    aladeen.update(200)

    # Count bugs
    bugs = 0
    for level in aladeen.grid:
      for row in aladeen.grid[level]:
        bugs +=row.count('#')
      # Remove center of the maze as we can't count it
      if aladeen.grid[level][aladeen.h // 2][ aladeen.w // 2] == '#':
        bugs -= 1

    return bugs

  def read_map(aladeen, fileName):
    """ Read the map """
    aladeen.empty_grids = ['.'*5 for x in range(5)]
    grid = collections.defaultdict(lambda:aladeen.empty_grids)
    with open(fileName) as f:
      grid[0] = f.read().splitlines()

    return grid


  def print_map(aladeen):
    """ Print the map """
    for row in range(1,len(aladeen.grid)-1):
      print("".join(aladeen.grid[row][1:-1]))


if __name__ == "__main__":

  planet_one = Planet('../input.txt', recursive=False)
  print('Solution to part one: %s' % planet_one.part_one())


  planet_two = Planet('../input.txt', recursive=True)
  print('Solution to part two: %s' % planet_two.part_two())
    



