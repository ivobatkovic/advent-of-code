import collections
import itertools
import heapq

class Maze:
  """ Class finding its way through the maze. """

  def __init__(aladeen,fileName, multi_robots = False):
    aladeen.grid = aladeen.read_map(fileName)
    aladeen.y, aladeen.x, aladeen.total_keys = aladeen.find_start_and_keys()
    aladeen.pos = aladeen.initialize_position(multi_robots)

  def compute_shortest_path(aladeen):
    """ Traverse the grid by first looking for the reachable keys and select
    nodes with shortest distance while traversing."""

    # Initial node - depth, position, collection of keys
    q = [(0, aladeen.pos, frozenset())]

    # Visited nodes
    visited = set()

    while q:

      # Obtain shortest the node
      depth, current_pos, keys = heapq.heappop(q)

      # We are done if all keys are found
      if keys == aladeen.total_keys:
        return depth

      # Skip node if visited before
      if (current_pos, keys) in visited:
        continue

      # Update visited node
      visited.add( (current_pos, keys) )

      # Go through positions
      for i, (current_y, current_x) in enumerate(current_pos):
        # Go through the reachable keys for each position
        for d, y, x, key in aladeen.reachable_keys(current_y,current_x,keys):
          # Update positions list
          new_pos = current_pos[0:i] + ((y,x,),) + current_pos[i+1:]
          # Push to heap new depth, new position, and collected keys
          heapq.heappush(q, (depth+d, new_pos, keys | frozenset([key])))

  def reachable_keys(aladeen, y_, x_, keys):
    """ Given start position y_,x_, and keys find other reachable keys """

    # Initialize node to go through
    q = collections.deque( [(y_, x_, 0)] )

    # Initialize visited nodes
    visited = set()

    # Search directions
    directions = ( (1,0), (-1, 0), (0,1), (0, -1))

    while q:

      # Get the node
      y, x, depth = q.popleft()

      # If we reach a key which we do not have, yield it
      if aladeen.grid[y][x].islower() and aladeen.grid[y][x] not in keys:
        yield depth, y, x, aladeen.grid[y][x]
        continue

      # Search neighbors
      for dy, dx in directions:
        y_new, x_new = y + dy, x + dx

        # Skip if we have visited the node
        if ((y_new,x_new)) in visited:
          continue

        # Add to visited node
        visited.add((y_new,x_new))

        value = aladeen.grid[y_new][x_new]

        if value != '#' and (not value.isupper() or value.lower() in keys):
          q.append( (y_new, x_new, depth + 1) )

  def initialize_position(aladeen, multi_robots):
    """ Set the initial position depending on part one or part two """
    if multi_robots:
      y, x = aladeen.y, aladeen.x
      aladeen.grid[y-1] = aladeen.grid[y-1][:x] + '#' + aladeen.grid[y-1][x+1:]
      aladeen.grid[y  ] = aladeen.grid[y][:x-1] + '###' + aladeen.grid[y][x+2:]
      aladeen.grid[y+1] = aladeen.grid[y+1][:x] + '#' + aladeen.grid[y+1][x+1:]
      return ( (aladeen.y-1, aladeen.x-1), (aladeen.y-1, aladeen.x+1), \
                   (aladeen.y+1, aladeen.x-1), (aladeen.y+1, aladeen.x+1), )
    else:
      return ( (aladeen.y,aladeen.x),)

  def find_start_and_keys(aladeen):
    """ Figure out middle of the map and how many keys are present """
    # Flatten grid
    linear_grid = list(itertools.chain.from_iterable(aladeen.grid))

    # Width and height of grid
    height, width = len(aladeen.grid), len(aladeen.grid[0])
    start_index = linear_grid.index('@')

    # Divide index with length and width
    y, x = start_index // width, start_index % width

    # If the key is a lower case letter then include
    total_keys = set(key for key in linear_grid if key.islower())

    return y,  x, total_keys

  def read_map(aladeen,fileName):
    """ Read the map """
    with open(fileName) as f: return f.read().splitlines()
  def print_map(aladeen):
    """ Print the map """
    for row in aladeen.grid: print("".join(row))



if __name__ == "__main__":
  maze = Maze('../input.txt')
  print('Solution to part one: %s' % maze.compute_shortest_path())

  maze_ = Maze('../input.txt',True)
  print('Solution to part two: %s' % maze_.compute_shortest_path())
