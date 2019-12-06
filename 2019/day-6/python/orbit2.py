file_location = "../data.txt"
try:

  val, con = {}, {}
  with open(file_location) as f:
    for line in f:

      l = line.strip()
      a,b= l.split(')')

      val[a],val[b] = 0,0
      con[b] = a

  t = 'SAN'
  orbS = {}
  i = 0
  while True:
    if t == 'COM':
      break
    else:
      t = con[t]
      print(t,i)
      orbS[t] = i
      i+=1
  print(orbS['COM'])
  t = 'YOU'
  orbY = {}
  i = 0
  while True:
    if t == 'COM':
      break
    else:
      t = con[t]
      print(t,i)
      orbY[t] = i
      i+=1


  br = False
  for k1, v1 in sorted(orbS.items(), key=lambda x: x[1]):
    for k2, v2 in sorted(orbY.items(), key=lambda x: x[1]):
      if k1==k2:
        print(v1+v2)
        br = True
        break
    if br:
      break


except IOError:
  print("Cannot find file at: " + file_location)
