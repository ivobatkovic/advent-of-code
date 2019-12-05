from utils import IO

class Intcode():
  """ Class containing the intcode computer."""

  def __init__(self,file_location,input):
    """ Read file and give input to the intcode computer."""
    self.x = IO.read_file(file_location)
    self.n = len(self.x)
    self.i = 0
    self.input = input

  def parse_opcode(self,op):
    """ Opcode parsing - analyzes the opcode string. """
    oper = op[-1]
    mode = '00'+op[:-2]

    # Parse position vs immediate mode for each operation
    j = self.i
    if oper == '1' or oper == '2' or oper == '7' or  oper == '8':
      p1 = self.x[self.x[j+1]] if mode[-1]=='0' else self.x[j+1]
      p2 = self.x[self.x[j+2]] if mode[-2]=='0' else self.x[j+2]
      out = self.x[j+3]
      self.i = self.i + 4
      return oper,p1,p2,out
    elif oper == '5' or oper  == '6':
      p1 = self.x[self.x[j+1]] if mode[-1]=='0' else self.x[j+1]
      p2 = self.x[self.x[j+2]] if mode[-2]=='0' else self.x[j+2]
      out = self.x[j+3]
      self.i = self.i + 3
      return oper,p1,p2,None
    elif oper == '4':
      p = self.x[self.x[j+1]] if mode[-1]=='0' else self.x[j+1]
      self.i = self.i + 2
      return oper,p,None,None
    else:
      p = self.x[j+1]
      self.i = self.i + 2
      return oper,p,None,None


  def operate(self,oper,p1,p2,out):
    """ Apply operation on the intcode sequence. """

    if oper=='1':
      self.x[out] = p1 + p2
    elif oper=='2':
      self.x[out] = p1 * p2
    elif oper=='3':
      self.x[p1] = self.input
    elif oper=='4':
      print(p1)
    elif oper=='5':
      self.i = p2 if p1 != 0 else self.i
    elif oper=='6':
      self.i = p2 if p1 == 0 else self.i
    elif oper=='7':
      self.x[out] = 1 if p1 < p2 else 0
    elif oper=='8':
      self.x[out] = 1 if p1 == p2 else 0

  def __call__(self):
    """ Call to solve the intcode. """

    while(self.i < self.n):
      if(self.x[self.i]==99):
        break
      oper,p1,p2,out = self.parse_opcode(str(self.x[self.i]))
      self.operate(oper,p1,p2,out)

def main():

  part_one = Intcode("../data.csv",1)
  print("Solution for part one:")
  part_one()
  
  part_two = Intcode("../data.csv",5)
  print("Solution for part two:")
  part_two()

if __name__ == "__main__":
  main()