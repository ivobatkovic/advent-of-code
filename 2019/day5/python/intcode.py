from utils import IO
import copy
from itertools import repeat

class Intcode():
  """ Class containing the intcode computer."""

  def __init__(self,file,input = [], verbose = True, reset = True):
    """ Read file and give input to the intcode computer."""
    self.memory = IO.read_file(file)
    self.x, self.output = None, None
    self.input = input if isinstance(input,list) else [input]
    self.verbose = verbose
    self.reset = reset
    self.idle = False
    self.n = len(self.memory)
    self.i,self.base = 0, 0

  def parse_opcode(self,op):
    """ Opcode parsing - analyzes the opcode string. """
    oper = op[-1]
    mode = '000'+op[:-2]
    # Parse position vs immediate mode for each operation
    j = self.i

    # Relative base check
    b0 = self.base if mode[-1] == '2' else 0
    b1 = self.base if mode[-2] == '2' else 0
    b2 = self.base if mode[-3] == '2' else 0

    xb0 = self.x[b0+self.x[j+1]]
    xb1 = self.x[b1+self.x[j+2]]
    
    if oper == '1' or oper == '2' or oper == '7' or  oper == '8':
      p1 = self.x[j+1] if mode[-1]=='1' else xb0
      p2 = self.x[j+2] if mode[-2]=='1' else xb1
      out = b2+self.x[j+3]
      self.i = self.i + 4
      return oper,p1,p2,out
    elif oper == '5' or oper  == '6':
      p1 = self.x[j+1] if mode[-1]=='1' else xb0
      p2 = self.x[j+2] if mode[-2]=='1' else xb1
      out = self.x[b2+j+3]
      self.i = self.i + 3
      return oper,p1,p2,None
    elif oper == '4':
      p = self.x[j+1] if mode[-1]=='1' else xb0
      self.i = self.i + 2
      return oper,p,None,None
    elif oper =='9':
      base = self.x[j+1] if mode[-1]=='1' else xb0
      self.i = self.i + 2
      self.base += base
      return None,None,None,None
    else:
      p = b0+self.x[j+1]
      self.i = self.i + 2
      return oper,p,None,None

  def operate(self,oper,p1,p2,out):
    """ Apply operation on the intcode sequence. """

    if oper=='1':
      self.x[out] = p1 + p2
    elif oper=='2':
      self.x[out] = p1 * p2
    elif oper=='3':
      if not self.input:
        self.input.append(-1)
        self.idle = True

      self.x[p1] = self.input[0]
      self.input.pop(0)
    elif oper=='4':
      self.output=p1
      if self.verbose: print(p1)
    elif oper=='5':
      self.i = p2 if p1 != 0 else self.i
    elif oper=='6':
      self.i = p2 if p1 == 0 else self.i
    elif oper=='7':
      self.x[out] = 1 if p1 < p2 else 0
    elif oper=='8':
      self.x[out] = 1 if p1 == p2 else 0

  def __call__(self,input=[]):
    """ Call to solve the intcode. """

    self.x = copy.deepcopy(self.memory) if self.reset else self.memory

    if isinstance(input,list):
      if len(input)>0:
        for inp in input:
          self.input.append(inp)
    else:
      self.input.append(input)

    while(self.i < self.n):
      
      if(self.x[self.i]==99):
        self.i, self.base = 0,0
        return True,self.output
      oper,p1,p2,out = self.parse_opcode(str(self.x[self.i]))
      
      if oper == '3' and self.idle:
        return False, None
      self.operate(oper,p1,p2,out)

      if (not self.reset) and oper == '4':
        return False,self.output

    return self.output
