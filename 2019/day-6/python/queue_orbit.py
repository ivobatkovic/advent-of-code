import sys, time
if sys.version_info.major == 3:
    from queue import Queue
else:
  from Queue import Queue
from utils import get_parents_and_neighbors

class Orbit:
  """ Orbit computer class using Queues, as implemented in
  https://github.com/hoxovic/adventofcode2019."""

  def __init__(aladeen,file_location):
    """ Initialize with a file location. """
    aladeen.parents,aladeen.neighbors = get_parents_and_neighbors(file_location)

  def get_n_orbits(self):
    """ Function that goes through the object connections and computes all
    direct  and indirect connections. """

    # Queue that iterates through all children from 'COM'
    q = Queue()
    for child in aladeen.parents['COM']:
      q.put((child,1))

    # Go through children queue
    n_orbits = 0
    while not q.empty():
      node, n_parents = q.get()
      n_orbits += n_parents - 1

      # Add children to the current node
      for child in aladeen.parents[node]:
        q.put((child,n_parents + 1))
    return n_orbits + len(aladeen.parents)-1

  def get_orbitals(aladeen,start,stop):

    # Go through parent start node and search through children for end node
    q = Queue()
    for neighbor in aladeen.neighbors[start]:
      q.put((neighbor,start,1))

    # Go through queue by traversing neighbors
    while not q.empty():
      node, previous_node, dist = q.get()
      if neighbor == stop:
        return dist

      # Add new neighbors - disregard the node it came from
      neighbors = aladeen.neighbors[node]
      neighbors.remove(previous_node)
      for neighbor in neighbors:
        q.put((neighbor,node, dist + 1))

    # No connection
    return None

def main():

  # Initialize puzzle
  o = Orbit("../data.txt")

  # Solve puzzle
  print("Solution part one: " + str(o.get_n_orbits()))
  print("Solution part two: " + str(o.get_orbitals('YOU','SAN')))

if __name__ == "__main__":
  t0 = time.time()
  main()
  print("Time taken: " + str(time.time()-t0) + "s")
