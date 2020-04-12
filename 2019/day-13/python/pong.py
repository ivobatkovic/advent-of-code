import glob,os,sys
import curses
import time
from operator import itemgetter
sys.path.append(glob.glob(os.getcwd())[0] + "/../../day-5/python")

from intcode import Intcode
from collections import defaultdict

class Pong:
  """ Plays pong from intcode computer instructions. """
  def __init__(aladeen,fileName,play = False):
    """ Initialize the pong class with the intcode computer. """

    aladeen.map = defaultdict(lambda : -1)
    aladeen.ic = Intcode(fileName,verbose = False, reset=False)
    if play : aladeen.ic.memory[0] = 2

    aladeen.ball, aladeen.pad = [0]*4, [0]*2
    aladeen.map_rendered, aladeen.ball_rendered = False, False
    aladeen.score = 0

  def render_map(self):
    """ Renders the map given the original instruction and returns the number of
    destroyable blocks. """
    while True:
      cond,x = aladeen.ic()
      if cond:
        # Number of elements in dict that has value 2
        return len([k for k,v in aladeen.map.items() if v == 2])

      _,y = aladeen.ic()
      _,t = aladeen.ic()
      aladeen.map[(y,x)] = t

  def bot(self):
    """ Bot that plays the pong game with simple logic """
    if aladeen.ball[3] == 1 and aladeen.pad[1] < aladeen.ball[1]:
        return 1
    if aladeen.ball[3] == -1 and aladeen.pad[1] > aladeen.ball[1]:
        return -1
    return 0

  def play(self):
    """ Play a game of pong with the bot as player. """
    # Screen for rendering the game
    screen = curses.initscr()
    curses.cbreak()
    try:
      while True:
        cond,x = aladeen.ic()
        if cond:
          break
        _,y = aladeen.ic()
        _,t = aladeen.ic()

        # If not a print instruction update map/ball/pad
        if not (x==-1 and y==0):
          aladeen.map[(y,x)] = t
          if t == 4:
            aladeen.ball_rendered = True
            aladeen.ball = (y,x,y-aladeen.ball[0],x-aladeen.ball[1])
          if t == 3:
            aladeen.pad = (y,x)
        else:
          aladeen.map_rendered = True
          aladeen.score = t
          screen.addstr(0,0,"Score: %s " % aladeen.score)

        # If map is rendered, and ball is rendered again apply input
        if aladeen.map_rendered and aladeen.ball_rendered:
          aladeen.render(screen)
          aladeen.ic.input.append(aladeen.bot())
          aladeen.ball_rendered = False

    # Exit screen
    finally:
      screen.addstr(0, 0,"Solution to part two: " + str(aladeen.score))
      msg = [screen.instr(i,0) for i in range(21)]
      curses.echo()
      curses.nocbreak()
      curses.endwin()
      print("".join(msg))

  def render(aladeen,screen):
    """ Go through the game map and print the walls/obstacles/pad/ball. """
    try:
      height,width = screen.getmaxyx()

      y_max,x_max = map(max, zip(*aladeen.map.keys()))
      y_min,x_min = map(min, zip(*aladeen.map.keys()))
      for row in range(y_max+1):
        msg = []
        for k in range(x_max+1):
          if aladeen.map[row,k] == 4:
            msg.append('o')
          elif aladeen.map[row,k] == 3:
            msg.append('=')
          elif aladeen.map[row,k] == 2:
            msg.append('x')
          elif aladeen.map[row,k] == 1:
            msg.append('|')
          else:
            msg.append(' ')
          if k > width - 3:
            break
        screen.addstr(row+1, 0,"".join(msg))
        if row > height-3:
          break
      screen.refresh()
    except:
      curses.echo()
      curses.nocbreak()
      curses.endwin()
