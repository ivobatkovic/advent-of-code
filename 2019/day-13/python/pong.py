import glob,os,sys
import curses
import time
from operator import itemgetter
sys.path.append(glob.glob(os.getcwd())[0] + "/../../day-5/python")

from intcode import Intcode
from collections import defaultdict

class Pong:
  """ Plays pong from intcode computer instructions. """
  def __init__(self,fileName,play = False):
    """ Initialize the pong class with the intcode computer. """

    self.map = defaultdict(lambda : -1)
    self.ic = Intcode(fileName,verbose = False, reset=False)
    if play : self.ic.memory[0] = 2

    self.ball, self.pad = [0]*4, [0]*2
    self.map_rendered, self.ball_rendered = False, False
    self.score = 0

  def render_map(self):
    """ Renders the map given the original instruction and returns the number of
    destroyable blocks. """
    while True:
      cond,x = self.ic()
      if cond:
        # Number of elements in dict that has value 2
        return len([k for k,v in self.map.items() if v == 2])

      _,y = self.ic()
      _,t = self.ic()
      self.map[(y,x)] = t

  def bot(self):
    """ Bot that plays the pong game with simple logic """
    if self.ball[3] == 1 and self.pad[1] < self.ball[1]:
        return 1
    if self.ball[3] == -1 and self.pad[1] > self.ball[1]:
        return -1
    return 0

  def play(self):
    """ Play a game of pong with the bot as player. """
    # Screen for rendering the game
    screen = curses.initscr()
    try:
      while True:
        cond,x = self.ic()
        if cond:
          break
        _,y = self.ic()
        _,t = self.ic()

        # If not a print instruction update map/ball/pad
        if not (x==-1 and y==0):
          self.map[(y,x)] = t
          if t == 4:
            self.ball_rendered = True
            self.ball = (y,x,y-self.ball[0],x-self.ball[1])
          if t == 3:
            self.pad = (y,x)
        else:
          self.map_rendered = True
          self.score = t
          screen.addstr(0,0,"Score: %s " % self.score)

        # If map is rendered, and ball is rendered again apply input
        if self.map_rendered and self.ball_rendered:
          self.render(screen)
          self.ic.input.append(self.bot())
          self.ball_rendered = False

    # Exit screen
    finally:
      screen.addstr(0, 0,"Solution to part two: " + str(self.score))
      msg = [screen.instr(i,0) for i in range(21)]
      print
      curses.echo()
      curses.nocbreak()
      curses.endwin()
      print("".join(msg))

  def render(self,screen):
    """ Go through the game map and print the walls/obstacles/pad/ball. """
    for row in range(0,21):
      msg = []
      for k in range(38):
        if self.map[row,k] == 4:
          msg.append('o')
        elif self.map[row,k] == 3:
          msg.append('=')
        elif self.map[row,k] == 2:
          msg.append('x')
        elif self.map[row,k] == 1:
          msg.append('|')
        else:
          msg.append(' ')
      screen.addstr(row+1, 0,"".join(msg))
    screen.refresh()
