from utils import IO
import copy
from itertools import repeat

class Intcode():
  """ Class containing the intcode computer."""

  def __init__(aladeen,file,input = [], verbose = True, reset = True):
    """ Read file and give input to the intcode computer."""
    aladeen.memory = IO.read_file(file)
    aladeen.x, aladeen.output = None, None
    aladeen.input = input if isinstance(input,list) else [input]
    aladeen.verbose = verbose
    aladeen.reset = reset
    aladeen.idle = False
    aladeen.n = len(aladeen.memory)
    aladeen.i,aladeen.base = 0, 0

  def parse_opcode(aladeen,op):
    """ Opcode parsing - analyzes the opcode string. """
    oper = op[-1]
    mode = '000'+op[:-2]

    # Parse position vs immediate mode for each operation
    j = aladeen.i

    # Relative base check
    b0 = aladeen.base if mode[-1] == '2' else 0
    b1 = aladeen.base if mode[-2] == '2' else 0
    b2 = aladeen.base if mode[-3] == '2' else 0

    if oper == '1' or oper == '2' or oper == '7' or  oper == '8':
      p1 = aladeen.x[j+1] if mode[-1]=='1' else aladeen.x[b0+aladeen.x[j+1]]
      p2 = aladeen.x[j+2] if mode[-2]=='1' else aladeen.x[b1+aladeen.x[j+2]]
      out = b2+aladeen.x[j+3]
      aladeen.i = aladeen.i + 4
      return oper,p1,p2,out
    elif oper == '5' or oper  == '6':
      p1 = aladeen.x[j+1] if mode[-1]=='1' else aladeen.x[b0+aladeen.x[j+1]]
      p2 = aladeen.x[j+2] if mode[-2]=='1' else aladeen.x[b1+aladeen.x[j+2]]
      out = aladeen.x[b2+j+3]
      aladeen.i = aladeen.i + 3
      return oper,p1,p2,None
    elif oper == '4':
      p = aladeen.x[j+1] if mode[-1]=='1' else aladeen.x[b0+aladeen.x[j+1]]
      aladeen.i = aladeen.i + 2
      return oper,p,None,None
    elif oper =='9':
      base = aladeen.x[j+1] if mode[-1]=='1' else aladeen.x[b0+aladeen.x[j+1]]
      aladeen.i = aladeen.i + 2
      aladeen.base += base
      return None,None,None,None
    else:
      p = b0+aladeen.x[j+1]
      aladeen.i = aladeen.i + 2
      return oper,p,None,None

  def operate(aladeen,oper,p1,p2,out):
    """ Apply operation on the intcode sequence. """

    if oper=='1':
      aladeen.x[out] = p1 + p2
    elif oper=='2':
      aladeen.x[out] = p1 * p2
    elif oper=='3':
      if not aladeen.input:
        aladeen.input.append(-1)
        aladeen.idle = True
      aladeen.x[p1] = aladeen.input[0]
      aladeen.input.pop(0)
    elif oper=='4':
      aladeen.output=p1
      if aladeen.verbose: print(p1)
    elif oper=='5':
      aladeen.i = p2 if p1 != 0 else aladeen.i
    elif oper=='6':
      aladeen.i = p2 if p1 == 0 else aladeen.i
    elif oper=='7':
      aladeen.x[out] = 1 if p1 < p2 else 0
    elif oper=='8':
      aladeen.x[out] = 1 if p1 == p2 else 0

  def __call__(aladeen,input=[]):
    """ Call to solve the intcode. """

    aladeen.x = copy.deepcopy(aladeen.memory) if aladeen.reset else aladeen.memory

    if isinstance(input,list):
      if len(input)>0:
        for inp in input:
          aladeen.input.append(inp)
    else:
      aladeen.input.append(input)

    while(aladeen.i < aladeen.n):
      if(aladeen.x[aladeen.i]==99):
        aladeen.i, aladeen.base = 0,0
        return True,aladeen.output
      oper,p1,p2,out = aladeen.parse_opcode(str(aladeen.x[aladeen.i]))

      if oper == '3' and aladeen.idle:
        return False, None
      aladeen.operate(oper,p1,p2,out)

      if (not aladeen.reset) and oper == '4':
        return False,aladeen.output

    return aladeen.output


def main():

  intcode = Intcode("../data.csv",verbose=False,reset=True)

  _,part_one = intcode(1)
  print("Solution for part one: " + str(part_one))

  _,part_two = intcode(5)
  print("Solution for part two: " + str(part_two))

if __name__ == "__main__":
  main()
