import csv
from collections import defaultdict
class IO:
  @staticmethod
  def read_file(file_location):
    try:
      with open(file_location) as csvfile:
        row = list(csv.reader(csvfile,delimiter=','))[0]
        data = defaultdict(int,{i:int(x) for i,x in enumerate(row)})
        
      return data

    except IOError:
      print("Cannot find file at: " + file_location)
      return None
