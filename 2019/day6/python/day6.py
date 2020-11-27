import sys, time
if sys.version_info.major == 3:
    from queue import Queue
else:
  from Queue import Queue
from utils import get_parents_and_neighbors

class Orbit:
  """ Orbit computer class using Queues, as implemented in
  https://github.com/hoxovic/adventofcode2019."""

  def __init__(self,file_location):
    """ Initialize with a file location. """
    self.parents,self.neighbors = get_parents_and_neighbors(file_location)

  def get_n_orbits(self):
    """ Function that goes through the object connections and computes all
    direct  and indirect connections. """

    # Queue that iterates through all children from 'COM'
    q = Queue()
    for child in self.parents['COM']:
      q.put((child,1))

    # Go through children queue
    n_orbits = 0
    while not q.empty():
      node, n_parents = q.get()
      n_orbits += n_parents - 1

      # Add children to the current node
      for child in self.parents[node]:
        q.put((child,n_parents + 1))
    return n_orbits + len(self.parents)-1

  def get_orbitals(self,start,stop):

    # Go through parent start node and search through children for end node
    q = Queue()
    for neighbor in self.neighbors[start]:
      q.put((neighbor,start,1))

    # Go through queue by traversing neighbors
    while not q.empty():
      node, previous_node, dist = q.get()
      if node == stop:
        return dist -1

      # Add new neighbors - disregard the node it came from
      neighbors = self.neighbors[node]
      neighbors.remove(previous_node)
      for neighbor in neighbors:
        q.put((neighbor,node, dist + 1))

    # No connection
    return None

def main():

  # Initialize puzzle
  o = Orbit("../data/input.txt")

  # Solve puzzle
  t0 = time.time()
  part_one = o.get_n_orbits()
  time_part_one = round((time.time()-t0)*1e3)
  print("Solution to part one: %s (time taken %s[ms])" % (
      part_one, time_part_one))

  t0 = time.time()
  part_two = o.get_orbitals('YOU', 'SAN')
  time_part_two = round((time.time()-t0)*1e3)
  print("Solution to part two: %s (time taken %s[ms])" % (
      part_two, time_part_two))


if __name__ == "__main__":
  main()
