import csv
class IO:
  @staticmethod
  def read_file(file_location):
    try:
      with open(file_location) as csvfile:
        reader = csv.reader(csvfile,delimiter=',')

        data = []
        # Go through each row of the csv
        for row in reader:

          # Map to list to int
          intcode_input = [int(x) for x in row]
          data.append(intcode_input)

      return intcode_input

    except IOError:
      print("Cannot find file at: " + file_location)
      return None
