import sys,glob,os
sys.path.append(glob.glob(os.getcwd())[0] + "/../../day-5/python")
from collections import defaultdict
from intcode import Intcode
import curses
import numpy as np

class Asci:
  """ Class that controls the scaffolding bot. """

  def __init__(aladeen,fileName):
    """ Initialize class and intcode computer. """
    aladeen.fileName = fileName
    aladeen.ic = Intcode(fileName,verbose = False, reset = False)
    aladeen.mp = aladeen.get_map()


  def get_map(aladeen):
    """ Call the intcode computer to generate the map """

    aladeen.mp = defaultdict(lambda : ord('x'))
    y, x = 0, 0
    while True:
      cond, output = aladeen.ic()

      if cond: break
      # New row of the print out
      if output == 10:
        y += 1
        x = 0
      # Assign the value to the map
      else:
        aladeen.mp[y,x] = output
        x += 1

    return aladeen.mp

  def print_map(aladeen):
    """ Print the obtained map """
    y_max,x_max = map(max, zip(*aladeen.mp.keys()))
    for row in range(0,y_max+1):
      msg = []
      for k in range(0,x_max+1):
        msg.append(chr(aladeen.mp[row,k]))
      print("".join(msg))

  def compute_intersections(aladeen,print_map = True):
    """ Go through map and find if any section intersects """

    if print_map : aladeen.print_map()

    # Make list of elements where v ==35 (chr(v) = '#')
    list = [k for k,v in aladeen.mp.items() if v == 35]
    sum = 0
    for y,x in list:
      if aladeen.mp[y,x+1] == 35 and aladeen.mp[y,x-1] == 35 \
          and aladeen.mp[y-1,x] == 35 and aladeen.mp[y+1,x] == 35:
        aladeen.mp[y,x] = ord('O')
        sum += y*x
    return sum

  def find_start_pose(aladeen):
    """ Find where (<,>,^,v) is in the map """

    # Find start position
    y,x = [k for k,v in aladeen.mp.items() if v == 94 or v == 60 \
            or v == 62 or v == 118][0]


    # Assign orientation
    dy,dx, theta = 0,0, 0
    if aladeen.mp[y,x] == ord('^'): theta = np.pi/2
    elif mp[y,x] == ord('<'): theta = -np.pi
    elif mp[y,x] == ord('>'): theta = 0
    else: theta = -np.pi/2

    return y, x, theta

  def traverse_scaffold(aladeen):
    """ Compute which actions are needed to go through scaffold """

    y, x, theta = aladeen.find_start_pose()
    dy, dx = -np.sin(theta), np.cos(theta)
    straight, instruction_string = 0, ''

    while True:
      # Either scaffold infront of us
      if aladeen.mp[y+dy,x+dx] == ord('#') or aladeen.mp[y+dy,x+dx] == ord('O'):
        aladeen.mp[y,x] = ord('O')
        straight += 1
        y, x = y+dy, x+dx
      # Otherwise, it is to our left or right
      else:
        if   aladeen.mp[y-1,x] == ord('#'): theta_ = np.pi/2
        elif aladeen.mp[y+1,x] == ord('#'): theta_ = -np.pi/2
        elif aladeen.mp[y,x-1] == ord('#'): theta_ = -np.pi
        elif aladeen.mp[y,x+1] == ord('#'): theta_ = 0

        # Reached the end
        else:
          aladeen.mp[y,x] = ord('x')
          if straight > 0:
            instruction_string = instruction_string + str(straight)
          return instruction_string

        if straight > 0:
          instruction_string = instruction_string + str(straight) + ','
          straight = 0

        # Find angle between directions
        if np.arccos(np.dot([np.sin(theta+np.pi/2),np.cos(theta+np.pi/2)],\
                            [np.sin(theta_),np.cos(theta_)])) == 0:
          instruction_string += 'L,'
          theta = theta+np.pi/2
        else:
          instruction_string += 'R,'
          theta = theta-np.pi/2
        # Update orientation
        dy,dx = np.int(-np.sin(theta)),np.int(np.cos(theta))


  def find_movement_routine(aladeen):
    """ Find three repeating patterns in the movement string """

    str0 = aladeen.traverse_scaffold()+','
    for an in range(min(20,len(str0)),0,-1):
      if str0[:an][-1] == ',':
        continue
      else:
        str1 = str0.replace(str0[0:an+1],'')
        for bn in range(min(20,len(str1)),0,-1):
          if str1[:bn][-1] == ',':
            continue
          else:
            str2 =str1.replace(str1[0:bn+1],'')
            for cn in range(min(20,len(str2)),0,-1):
              if str2[:cn][-1] == ',':
                continue
              else:
                str3 = str2.replace(str2[0:cn+1],'')
                if not str3:
                  A, B, C = str0[0:an], str1[0:bn], str2[0:cn]
                  routine = str0.replace(A,'A').replace(B,'B').replace(C,'C')[:-1]
                  return routine, A, B, C

  def construct_input(aladeen, print_iterations = False):
    """ Get the routine and movement functions and
        translate into the desired input format """
    routine, A, B, C = aladeen.find_movement_routine()

    def toOrd(A): return [ord(x) for x in A]
    return toOrd(routine) + [10] + toOrd(A) + [10] + toOrd(B) + [10] \
            + toOrd(C) + [10] + [ord('y' if print_iterations else 'n'),10]


  def print_video_feed(aladeen):
    """ Print the progress of the scaffolding robot """

    use_screen = True
    # Initialize screen for plotting
    if use_screen:
      screen = curses.initscr()
      height,width = screen.getmaxyx()

    # String template used to remove unecessary plotting
    valid = '#.<^v>\n'

    y_max,x_max = map(max, zip(*aladeen.mp.keys()))
    mp = defaultdict(lambda : ord(' '))
    try:
      # Keep going until we reach the terminating condition
      while True:
        # Initial conditions for each map
        y, x, skip = 0, 0, False
        while True:
          cond, output = aladeen.ic()
          if cond: return output

          # Check if output belongs to the valid string + filter new lines
          if (chr(output%256) not in valid) or (x==0 and output==10):
            skip = True

          # If output =
          if output == 10:
            if not skip: y += 1
            x, skip = 0, False
            if y > y_max-1: break
          elif not skip:
            mp[y,x] = output
            x += 1

        # Print using screen
        if use_screen:
          for row in range(0,y_max):
            msg = []
            for k in range(0,x_max):
              if k > width - 3:
                break
              msg.append(chr(mp[row,k]))
            if row > height - 3:
              break
            screen.addstr(row,0,"".join(msg))
          screen.refresh()
        # Normal print
        else:
          aladeen.mp = mp
          aladeen.print_map()

    finally:
      if use_screen:
        curses.endwin()



  def collect_dust(aladeen,print_iterations = False):
    """ Let the robot traverse using the compted input """
    
    input = aladeen.construct_input(print_iterations)
    aladeen.ic = Intcode(aladeen.fileName,input=input,verbose = False, reset = False)
    aladeen.ic.memory[0] = 2

    if not print_iterations:
        while True:
          cond, output = aladeen.ic()
          if cond : return output
    else:
      return aladeen.print_video_feed()
