from collections import defaultdict
import collections
import heapq
import time
class Donut:
  """ Donut maze class """

  def __init__(aladeen,fileName):
    """ Initialize Donut with the map and find all portals """
    aladeen.fileName = fileName
    aladeen.grid = aladeen.read_map(fileName)
    aladeen.portals, aladeen.reach = aladeen.find_portals()

  def shortest_path(aladeen,level_check=False):
    """ Find the shortest path from AA to ZZ """

    # Start and goal positions
    pos = aladeen.portals['AA'][0]
    goal = aladeen.portals['ZZ'][0]

    # Search directions
    d = [[-1,0],[1,0],[0,1],[0,-1]]

    # Visited nodes
    visited = set()

    # Start the queue at the current position
    q = collections.deque([(0, pos, 0)])
    while q:

      # Obtain information from queue
      depth, pos, level = q.popleft()

      # Check if we reached the goal
      if pos == goal:
        # Part two: check if level is 0
        if level_check:
          if level == 0:
            return depth
        # Part one
        else:
          return depth

      # Keep track of the visited nodes
      yp,xp = pos
      if (yp, xp, level) in visited:
        continue
      visited.add((yp, xp, level))


      # If the node is outside a portal entrance, teleport. Trick here is to
      # understand that the level must be >= 0 to use outer teleports
      if aladeen.reach[yp,xp] and level >=0:
        pos_,level_,_ = aladeen.reach[yp,xp]
        q.append((depth+1, pos_, level + level_))

      # Go in all other search directions and see if we can move
      for dy,dx in d:
        if aladeen.grid[yp+dy][xp+dx] == '.':
          q.append((depth+1, (yp+dy,xp+dx),level))

    # If we empty the queue, return no solution
    return 'No solution'

  def find_portals(aladeen):
    """ Go through the grid and find the portals """

    # Figure out height and width of the maze
    h, w = len(aladeen.grid), len(aladeen.grid[0])

    # Use a dict to keep track of the portals
    portals = defaultdict(list)

    for y in range(h):
      for x in range(w):

        # Check if the key is an upper case letter
        key, key_pair = aladeen.grid[y][x], ""
        if key.isupper():
          # Look up
          if y - 2 > 0 and aladeen.grid[y-1][x].isupper() == key.isupper() \
                       and aladeen.grid[y-2][x] == '.':
            yp, xp = y-2, x
            key_pair = aladeen.grid[y-1][x]+key
          # Look down
          elif y + 2 < h and aladeen.grid[y+1][x].isupper() == key.isupper() \
                         and aladeen.grid[y+2][x] == '.':
            yp, xp = y+2, x
            key_pair = key+aladeen.grid[y+1][x]
          # Look left
          elif x - 2 > 0 and aladeen.grid[y][x-1].isupper() == key.isupper() \
                         and aladeen.grid[y][x-2] == '.':
            yp, xp = y, x-2
            key_pair = aladeen.grid[y][x-1]+key
          # Look right
          elif x + 2 < w and aladeen.grid[y][x+1].isupper() == key.isupper() \
                       and aladeen.grid[y][x+2] == '.':
            yp, xp = y, x+2
            key_pair = key+aladeen.grid[y][x+1]

        # If a portal is found: append its position
        if key_pair:
          portals[key_pair].append((yp,xp))



    # Go through the portals and connect the teleport positions
    reach = defaultdict(list)
    for key,val in portals.items():
      # Multiple positions are connected, so direct them to eachother
      if len(val) > 1:

        v1, v2, dir = val[0], val[1], [1, -1]
        # Outer portals have either x or y on the outer edge of the map
        if (v1[0] == 2 or v1[0] == len(aladeen.grid)-3) or \
           (v1[1] == 2 or v1[1] == w-3):
          dir = [-1,1]
        reach[v1], reach[v2] = [v2,dir[0],key], [v1,dir[1],key]
    return portals, reach



  def read_map(aladeen,fileName):
    """ Read the map """
    with open(fileName) as f: return f.read().splitlines()
  def print_map(aladeen):
    """ Print the map """
    for row in aladeen.grid: print("".join(row))


donut = Donut('../input.txt')
print("Solution to part one: %s" % donut.shortest_path())
print("Solution to part two: %s" % donut.shortest_path(True))
