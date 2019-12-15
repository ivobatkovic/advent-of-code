import re, copy

class Gravity:
  """ Class simulating the N-body problem. """

  def __init__(s,fileName):
    """ Initialize position and velocity of the n bodies. """
    s.pos = s.readFile(fileName)
    s.vel = [[0]*4 for pos in s.pos]

  def readFile(s,fileName):
    """ Read file using regexp - extract the each number with possible minus
    sign."""
    try:
      with open(fileName,'r') as f:
        r = f.read().strip()
      # Array dimension [[x1,y1,z1],[...],[xN,yN,zN]]
      pos = [list(map(int,re.findall('-?\d+',s))) for s in r.split('\n')]
      # Array dimenison [[x1,x2,...,xN],[y1,y2,...,yN],[z1,z2,....,zN]]
      return map(list,list(zip(*pos)))

    except IOError:
      print("Cannot find file at: " + fileName)
      quit()

  def tick(s,d=0):
    """ Update step for a dimension. """
    for i,ego in enumerate(s.pos[d]):
      for other in s.pos[d]:
        s.vel[d][i] += 1 if ego<other else 0 if ego==other else -1
    for i in range(4):
      s.pos[d][i] += s.vel[d][i]

  def update(s,t = 1):
    """ Forward simulate the dynamics for all dimensions for t timesteps. """
    for i in range(t):
      for k in range(3):
        s.tick(k)

  def energy(s):
    """ Compute the potential and kinematic energy. """
    energy = 0

    # Transform to array of nBodies  * [x,y,z]
    posFinal, velFinal = zip(*s.pos), zip(*s.vel)
    for m,v in zip(posFinal,velFinal):
      energy += sum(map(abs,m))*sum(map(abs,v))
    return int(energy)

  def cycles(s):
    """ Go through each dimension until a cycle has been repeated. When all
    cycles have been found, compute the LCM to find when in time the same
    configuration appears. """

    periods = []
    for i in range(len(s.pos)):
      pos = copy.deepcopy(s.pos[i])
      n_steps = 0
      while True:
        s.tick(i)
        n_steps += 1
        if (not any(s.vel[i])) and (pos == s.pos[i]):
          break
      periods.append(n_steps)
    return periods
