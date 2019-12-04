import csv
import numpy as np

def compute_wire_segments(wires):
    """ Given the instructions in wires, the function returns an (N+1)x4 array
    of wire positions. First two elements are the x,y positions, the third
    element is the cummulated wire length, and the fourth element indicates if
    the line is vertical or horizontal."""

    # Wire segments container
    wire_segments = []

    # Go through each wire
    for wire in wires:

        # Start position
        pos = np.zeros((1,4))

        # Initialize array
        wire_segment = np.zeros((len(wire)+1,4))

        # Move 'along' wire
        for i, w in enumerate(wire):

            # Initialize direction steps and orientation
            dx,dy,step,orientation = 0,0,int(w[1:]),0

            # Wire moves left or right
            if w[0] == 'L' or w[0] == 'R':
                dx = step if (w[0] == 'R') else -step
            # Wire move up or down
            if w[0] == 'U' or w[0] == 'D':
                dy = step if (w[0] == 'U') else -step
                orientation = 1

            # Update position
            pos += [dx,dy,step,orientation]

            # Add position to wire_segment
            wire_segment[i+1,:] = pos

        # Add wire segment to container
        wire_segments.append(wire_segment)

    # Return segments
    return wire_segments

def intersect(line1,line2):
    """ Checks if line1: [A,B] intersects with line2: [C,D]. Assumes only
    horizontal and vertical lines."""

    # Check if lines are perpendicular
    if line1[1,-1] == line2[1,-1]:
        return None,None

    # Compute min and max bounds for line 1
    x1min,x1max = min(line1[:,0]),max(line1[:,0])
    y1min,y1max = min(line1[:,1]),max(line1[:,1])

    # Compute min and max bounds for line 2
    x2min,x2max = min(line2[:,0]),max(line2[:,0])
    y2min,y2max = min(line2[:,1]),max(line2[:,1])

    # Intersection condition
    if (x1max >= x2min) and (x1min <= x2max) and \
        (y1max >= y2min) and (y1min <= y2max):

        # Compute intersection point
        p = [x2min,y1min] if (x1max-x1min) != 0 else [x1min,y2min]

        # Total wire steps
        wire_steps = line1[0,2] + line2[0,2]

        # Added wire steps to intersection point
        steps_to_point = sum(abs(line1[0,:2] - p)) + sum(abs(line2[0,:2]-p))

        return p,(wire_steps+steps_to_point)

    return None,None

def intersect_wires(wire1,wire2):
    """ Loop through the wire segments wire1 and wire2 and looks for possible
    intersections."""

    intersection, steps = [], []
    for i in range(len(wire1)-1):
        for j in range(len(wire2)-1):
            point,s = intersect(wire1[i:i+2],wire2[j:j+2])
            if point is not None:
                intersection.append(point)
                steps.append(s)
    return intersection,steps

def crossed_wires(wires):
    """ This function assumes that the wires aren't routed along eachother, i.e.,
	they will only cross perpendicularly, hence it is enough only to check
    vertical wire segments vs horizontal wire segments."""

    # Compute the wire positions for each wire
    wire_segments = compute_wire_segments(wires)

    # Try to intersect the two wire segments with eachother
    points,steps = intersect_wires(wire_segments[0],wire_segments[1])

    # Compute Manhattan distance
    minimum_manhattan_distance = int(min(np.sum(np.abs(points),axis=1)))

    # Compute fewest steps
    fewest_steps  = int(min(steps))

    return minimum_manhattan_distance,fewest_steps

def main():
  # Open data file and read through all lines
  file_location = "../data.csv"
  try:
    wires = []
    with open(file_location) as csvfile:
      reader = csv.reader(csvfile,delimiter=',')
      # Go through each row of the csv
      for row in reader:
          wires.append(row)

    manhattan_distance,fewest_steps = crossed_wires(wires)
    print("Solution to part one: " + str(manhattan_distance))
    print("Solution to part two: " + str(fewest_steps))

  except IOError:
    print("Cannot find file at: " + file_location)

if __name__ == "__main__":
  main()
