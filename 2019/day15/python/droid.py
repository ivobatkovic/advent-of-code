from os.path import dirname
from os.path import realpath
from os.path import join
from collections import defaultdict
from queue import Queue
import sys
import copy
import curses

sys.path.append(join(dirname(realpath(__file__)), *["..", ".."]))

from day5.python.intcode import Intcode


class Droid:
    """Class that controls the droid."""

    def __init__(self, fileName):
        """Initialize class and intcode computer."""
        self.ic = Intcode(fileName, verbose=False, reset=False)

    def one_step(self, y, x, inp):
        """Returns next (y,x) pair given input."""
        y -= 1 if inp == 1 else -1 if inp == 2 else 0
        x += 1 if inp == 3 else -1 if inp == 4 else 0
        return y, x

    def repair_oxygen(self, y=0, x=0):
        """Starts from (y,x) and searches for the oxygen (output 2 from intcode).
        Program continues to map entire area after finding the oxygen."""

        # Keep track of parent nodes
        parents = defaultdict(list)
        parents[y, x] = (-1, -1)

        # Create a map of the environment
        map = defaultdict(lambda: 0)
        map[y, x] = 1

        # Queue - first come first serve
        q = Queue()
        q.put((y, x, copy.deepcopy(self.ic), 0))

        output = None

        # Initialize screen
        screen = curses.initscr()
        curses.cbreak()

        try:
            while not q.empty():
                y, x, ic_, depth = q.get()
                for input in range(1, 5):
                    y_new, x_new = self.one_step(y, x, input)

                    if not len(parents[y_new, x_new]) > 0:
                        parents[y_new, x_new] = (y, x)

                        ic_new = copy.deepcopy(ic_)
                        _, out = ic_new(input)
                        if out == 1:
                            map[y_new, x_new] = 1  # Plotting purpose
                            q.put((y_new, x_new, ic_new, depth + 1))
                        elif out == 2:
                            map[y_new, x_new] = 2  # Plotting purpose
                            output = (y_new, x_new, depth + 1)
                        else:
                            map[y_new, x_new] = 0  # Plotting purpose

                self.render(screen, map)  # Plot map
        finally:
            curses.echo()
            curses.nocbreak()
            curses.endwin()
            return map, output

    def render(self, screen, mp):
        """Go through the game map and print the walls/obstacles/pad/ball."""
        try:
            height, width = screen.getmaxyx()

            y_max, x_max = map(max, zip(*mp.keys()))
            y_min, x_min = map(min, zip(*mp.keys()))

            for row, v in enumerate(range(y_min, y_max + 1)):
                msg = []
                for k in range(x_min, x_max + 1):
                    if mp[v, k] == 0:
                        msg.append("X")
                    elif mp[v, k] == 1:
                        msg.append(" ")
                    elif mp[v, k] == 2:
                        msg.append("O")
                    else:
                        msg.append(" ")
                    if k > width - 3:
                        break
                screen.addstr(row, 0, "".join(msg))
                if row > height - 3:
                    break
            screen.refresh()
        except KeyboardInterrupt:
            curses.echo()
            curses.nocbreak()
            curses.endwin()
            exit(0)

    def fill_oxygen(self, map, y=0, x=0):
        """Given a starting position, sees how many time steps (how deep) the
        search goes until entire map is explored."""

        # Keep track of parent nodes
        parents = defaultdict(list)
        parents[y, x] = (-1, -1)

        # Queue - first come first serve
        q = Queue()
        q.put((y, x, 0))

        max_depth = -1
        screen = curses.initscr()
        curses.cbreak()
        try:
            while not q.empty():
                y, x, depth = q.get()
                for input in range(1, 5):

                    y_new, x_new = self.one_step(y, x, input)

                    if not len(parents[y_new, x_new]) > 0:

                        parents[y_new, x_new] = (y, x)
                        if map[y_new, x_new] == 1:
                            map[y_new, x_new] = 2
                            max_depth = depth + 1
                            q.put((y_new, x_new, depth + 1))
                self.render(screen, map)

        finally:
            curses.echo()
            curses.nocbreak()
            curses.endwin()
            return max_depth
