import numpy as np
from utils import IO
from collections import defaultdict
import collections

def compute_vision(x):
  """ Loop through each asteroid and check its surroundings. Bin each detection
  in a dictionary where the key is the angle to each asteroid. """

  ids = np.where(x=='#')
  max_asteroids, index = [],[]
  for i in range(len(ids[0])):
    x,y = ids[0][i],ids[1][i]
    monitor = defaultdict(lambda:10000)
    for j in range(len(ids[0])):
      if i == j:
        continue

      x1,y1 = ids[0][j],ids[1][j]
      angle = np.arctan2(y1-y,x1-x)
      monitor[angle] = 1

    max_asteroids.append(len(monitor))
    index.append(i)

  return np.max(max_asteroids),index[np.argmax(max_asteroids)]


def blast(x,i,n_asteriods):
  """ Loop through the measured angles, and delete the closest asteroid in for
  each angle key until n:th asteroid is destroyed. """

  ids = np.where(x=='#')
  x0, y0 = ids[0][i], ids[1][i]
  ids = np.delete(ids,i,1)

  monitor = defaultdict(lambda: np.ndarray(0))
  for j in range(len(ids[0])):

    dx,dy = ids[0][j]-x0,-(ids[1][j]-y0)
    distance = np.sqrt(dx*dx+dy*dy)
    angle = np.arctan2(-dy,dx)-np.pi/2

    if len(monitor[angle])==0:
      monitor[angle] = np.reshape([distance,ids[0][j],ids[1][j]],(1,3))
    else:
      monitor[angle] = np.vstack((monitor[angle],[distance,ids[0][j],ids[1][j]]))


  ord_monitor = collections.OrderedDict(sorted(monitor.items()))
  angles = ord_monitor.keys()

  idx = ord_monitor.keys().index(np.pi/2)
  n_removed = 0

  while n_removed < n_asteriods:
    if len(ord_monitor[angles[idx]])>0:
      id = np.argmin(ord_monitor[angles[idx]][:,0])
      x,y = ord_monitor[angles[idx]][id,1:]
      ord_monitor[angles[idx]] = np.delete(ord_monitor[angles[idx]],id,0)
      n_removed += 1
    idx = idx-1 if idx >-len(ord_monitor) else -1

  return int(y*100+x)


def main():
  x = IO.read_image('../input.txt')

  max_asteroids,spot_index = compute_vision(x)
  print("Solution to part one: " + str(max_asteroids))
  print("Solution to part two: " + str(blast(x,spot_index,n_asteriods=200)))


if __name__== "__main__":
  main()
