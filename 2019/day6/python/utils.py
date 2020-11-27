from collections import defaultdict

def get_parents_and_neighbors(file_location):
  """ Reads each line in the file and connects the objects through a
  dictionary."""
  try:
    parents, neighbors  = defaultdict(list), defaultdict(list)

    with open(file_location) as f:
      for line in f:
        parent, child = line.strip().split(')')
        parents[parent].append(child)
        neighbors[parent].append(child)
        neighbors[child].append(parent)
    return parents,neighbors
  except IOError:
    print("Cannot find file at: " + file_location)
