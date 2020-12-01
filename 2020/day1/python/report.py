import sys,glob,os
sys.path.append(glob.glob(os.getcwd())[0] + "/../../utils/python")
from utils import readFileInt

''' Day one solution '''
class Report:

  ''' Read input '''
  def __init__(self,file_name):
    self.x = readFileInt(file_name)

  ''' Loop through the list to find a pair that sums to 2020 '''
  def part_one(self):
    x = self.x
    for i in range(len(x)):
      for j in range(len(x)):
        if x[i] + x[j] == 2020:
          return x[i]*x[j]
          
  ''' Loop through the list to find a triplet that sums to 2020 '''
  def part_two(self):
    x = self.x
    for i in range(len(x)):
      for j in range(len(x)):
        for z in range(len(x)):
          if x[i] + x[j] + x[z] == 2020:
            return x[i]*x[j]*x[z]  