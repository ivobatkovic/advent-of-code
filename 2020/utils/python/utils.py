import csv

''' Read .txt input that is integer format '''
def readFileInt(file_name):
  try:
    with open(file_name) as f:
      # Remove whitespace characters at end of each line
      return [int(x.strip()) for x in f.readlines()]
  except IOError:
    print("Cannot find file at: " + file_name)

''' Read .txt input that is string format '''
def readFileString(file_name):
  try:
    with open(file_name) as f:
      # Remove whitespace characters at end of each line
      return [x.strip() for x in f.readlines()]
  except IOError:
    print("Cannot find file at: " + file_name)

''' Read .csv input that is integer format '''
def readFileCSVInt(file_name):
    try:    
      with open(file_name) as csvfile:
        row = csv.reader(csvfile,delimiter=',')
        output = []
        for r in row:
          output.append([int(x) for x in r])
      return output

    except IOError:
      print("Cannot find file at: " + file_name)
      return None

''' Read .csv input that is integer format '''
def readFileCSVString(file_name):
    try:    
      with open(file_name) as csvfile:
        row = csv.reader(csvfile,delimiter=',')
        output = []
        for r in row:
          output.append([x for x in r])
      return output

    except IOError:
      print("Cannot find file at: " + file_name)
      return None