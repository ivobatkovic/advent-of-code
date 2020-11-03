import time

class Orbit:
  """ Class containing the orbit computer."""

  def __init__(aladeen,file_location):
    """ Initialize with a file location. """

    aladeen.val,aladeen.con = {},{}
    aladeen.init_connections(file_location)

  def init_connections(aladeen,file_location):
    """ Reads each line in the file and connects the objects through a
    dictionary."""

    try:
      with open(file_location) as f:
        for line in f:
          a,b= line.strip().split(')')
          aladeen.val[a],aladeen.val[b] = 0,0
          aladeen.con[b] = a
    except IOError:
      print("Cannot find file at: " + file_location)

  def __call__(aladeen):
    """ Function that goes through the object connections and computes all
    direct  and indirect connections. """

    # Reset values
    aladeen.val = dict.fromkeys(aladeen.val.keys(), 0)

    for k in aladeen.con:
      key = k
      while True:
        if key == 'COM':
          break
        else:
          key = aladeen.con[key]
          aladeen.val[key] +=1

    return sum(aladeen.val.values())

  def orbits(aladeen,key):
    """ Computes the distance and sequence from key to COM """
    if aladeen.con.get(key):
      out = {}
      i = 0
      while True:
        if key == 'COM':
          break
        else:
          key = aladeen.con[key]
          out[key] = i
          i+=1
      return out
    return {}


  def minimum(aladeen,x,y):
    """ Finds shortest orbit distance between x and y. """

    x_dict,y_dict = aladeen.orbits(x),aladeen.orbits(y)
    for key_x, val_x in sorted(x_dict.items(), key=lambda x: x[1]):
      for key_y, val_y in sorted(y_dict.items(), key=lambda x: x[1]):
        if key_x==key_y:
          return val_x+val_y

    return -1

def main():

  # Initialize puzzle
  o = Orbit("../data.txt")

  # Solve puzzle
  print("Solution part one: " + str(o()))
  print("Solution part two: " + str(o.minimum('YOU','SAN')))

if __name__ == "__main__":
  t0 = time.time()
  main()
  print("Time taken: " + str(time.time()-t0) + "s")
