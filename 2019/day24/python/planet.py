import collections
import copy
import time
import math

class Planet:
  """ Planet class that scans the bugs """
  def __init__(self,file, recursive = False):
    """ Intialize Planet class """
    self.grid = self.read_map(file)
    self.h, self.w = len(self.grid[0]), len(self.grid[0][0])
    self.recursive = recursive
    self.neighbors = self.get_neighbors()
    self.map_config = dict()
    

  def get_neighbors(self):
    """ Go through every grid position and compute its neighbors """

    # Dictionary to keep track of neighbors
    neighbor_dict = collections.defaultdict(list)

    # Search directions
    directions = [[-1,0], [1,0], [0,1], [0,-1]]

    # Middle of the grid
    mid_y, mid_x = self.h // 2, self.w // 2
    
    for row in range(self.h):
      for col in range(self.w):
        for dx,dy in directions:
          row_, col_ = row + dy, col + dx

          # By default set the neighbors in this direction to empty
          neighbors = []

          # Outer neighbors above
          if row_ < 0 and self.recursive:
            neighbors = [[-1, mid_y-1, mid_x]]
          # Outer neighbors below
          elif row_ >= self.h and self.recursive:
            neighbors = [[-1, mid_y+1, mid_x]]
          # Outer neighbors to the left
          elif col_ < 0 and self.recursive:
            neighbors = [[-1, mid_y, mid_x-1]]
          # Outer neighbors to the right
          elif col_ >= self.w and self.recursive:
            neighbors = [[-1, mid_y, mid_x+1]]
          # Handle center of maze when it is recursive
          elif col_ == self.w // 2 and row_ == self.h // 2 and self.recursive:
            # Left inside
            if dx == 1: neighbors = [ [1, y, 0] for y in range(self.h)]
            # Right inside
            if dx == -1: neighbors = [ [1, y, self.w-1] for y in range(self.h)]
            # Top inside
            if dy == 1: neighbors = [[1, 0, x] for x in range(self.w)]
            # Bottom inside
            if dy == -1: neighbors = [[1, self.h-1, x] for x in range(self.w)]
          # Otherwise, we are inside the boundaries  
          elif col_ >= 0 and col_ < self.w and row_ >= 0 and row_ < self.h:
            neighbors = [[0, row_, col_]]

          # Go through the list of found neighbors and append them:
          # [level_difference, y_pos, x_pos]
          for neighbor in neighbors: neighbor_dict[row, col].append(neighbor)

    return neighbor_dict

  def update(self, n_updates = 1):
    """ Apply the bug update step """

    # If grid is recursive, figure out how many levels are needed
    if self.recursive:
      # Min and max levels
      min_level = int(math.floor(-n_updates / 2))
      max_level =  int(math.ceil(n_updates / 2) + 1)
      
      # Expand the dictionary to include levels : [min_level, max_level]
      [self.grid[level] for level in range(min_level,max_level)]

    
    # Run the number of updates
    for update in range(n_updates):

      # Temporary grid used in between updates
      temp_level = collections.defaultdict(lambda: self.empty_grids)
      
      # We do not need to go through the recursion for all levels
      depth = update // 2
      for level in range(-depth - 1, depth + 2):
      

        # Temporary grid for a given level
        temp_grid = []

        for row in range(self.h):
          new_row = ""
          for col in range(self.w):
            # See how many bugs are as neighbors
            neighbor_str = ""
            for level_dir, y, x in self.neighbors[row, col]:
              neighbor_str += self.grid[level+level_dir][y][x]
            n_neighbors = neighbor_str.count('#')
            
            # Update bug tile
            if self.grid[level][row][col] == '#':
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
      self.grid = temp_level

      # Check this for part one
      if not self.recursive:
        # Check if the key has been listed before
        if "".join(self.grid[0]) in self.map_config:
          return True
        # Otherwise keep going with iterations
        else:
          self.map_config["".join(self.grid[0])] = 1
          return False

  def part_one(self):
    """ Solve part one by updating the grid until finding same configuration """
    
    while True:
      # If configuration found
      if self.update():
        self.print_map()
        
        # Flatten the string
        strng = "".join([row for row in self.grid[0]])
        # Compute formula
        return sum([2 ** i if val == '#' else 0 for i,val in enumerate(strng)])
      
      
  def part_two(self):
    """ Solve part two by updating the grid 200 times and counts the bugs """
    
    # Update
    self.update(200)

    # Count bugs
    bugs = 0
    for level in self.grid:
      for row in self.grid[level]:
        bugs +=row.count('#')
      # Remove center of the maze as we can't count it
      if self.grid[level][self.h // 2][ self.w // 2] == '#':
        bugs -= 1

    return bugs

  def read_map(self, fileName):
    """ Read the map """
    self.empty_grids = ['.'*5 for x in range(5)]
    grid = collections.defaultdict(lambda:self.empty_grids)
    
    with open(fileName) as f:
      grid[0] = f.read().splitlines()

    return grid

  def print_map(self):
    """ Print the map """
    for row in range(1,len(self.grid[0])-1):
      print("".join(self.grid[0][row][1:-1]))
    



