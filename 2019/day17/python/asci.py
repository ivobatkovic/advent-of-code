from os.path import dirname
from os.path import realpath
from os.path import join
from collections import defaultdict

import curses
import numpy as np

import sys

sys.path.append(join(dirname(realpath(__file__)), *["..", ".."]))
from day5.python.intcode import Intcode


class Asci:
    """ Class that controls the scaffolding bot. """

    def __init__(self, fileName):
        """ Initialize class and intcode computer. """
        self.fileName = fileName
        self.ic = Intcode(fileName, verbose=False, reset=False)
        self.mp = self.get_map()

    def get_map(self):
        """ Call the intcode computer to generate the map """

        self.mp = defaultdict(lambda: ord("x"))
        y, x = 0, 0
        while True:
            cond, output = self.ic()

            if cond:
                break
            # New row of the print out
            if output == 10:
                y += 1
                x = 0
            # Assign the value to the map
            else:
                self.mp[y, x] = output
                x += 1

        return self.mp

    def compute_intersections(self):
        """ Go through map and find if any section intersects """

        # Make list of elements where v ==35 (chr(v) = '#')
        list = [k for k, v in self.mp.items() if v == 35]
        sum = 0
        for y, x in list:
            x1, x2 = self.mp[y, x + 1], self.mp[y, x - 1]
            y1, y2 = self.mp[y - 1, x], self.mp[y + 1, x]
            if x1 == 35 and x2 == 35 and y1 == 35 and y2 == 35:
                self.mp[y, x] = ord("O")
                sum += y * x
        return sum

    def find_start_pose(self):
        """ Find where (<,>,^,v) is in the map """

        # Find start position
        y, x = [
            k
            for k, v in self.mp.items()
            if v == 94 or v == 60 or v == 62 or v == 118
        ][0]

        # Assign orientation
        theta = 0
        if self.mp[y, x] == ord("^"):
            theta = np.pi / 2
        elif self.mp[y, x] == ord("<"):
            theta = -np.pi
        elif self.mp[y, x] == ord(">"):
            theta = 0
        else:
            theta = -np.pi / 2

        return y, x, theta

    def traverse_scaffold(self):
        """ Compute which actions are needed to go through scaffold """

        y, x, theta = self.find_start_pose()
        dy, dx = -np.sin(theta), np.cos(theta)
        straight, instruction_string = 0, ""

        while True:
            # Either scaffold infront of us
            if self.mp[y + dy, x + dx] == ord("#") or self.mp[
                y + dy, x + dx
            ] == ord("O"):
                self.mp[y, x] = ord("O")
                straight += 1
                y, x = y + dy, x + dx
            # Otherwise, it is to our left or right
            else:
                if self.mp[y - 1, x] == ord("#"):
                    theta_ = np.pi / 2
                elif self.mp[y + 1, x] == ord("#"):
                    theta_ = -np.pi / 2
                elif self.mp[y, x - 1] == ord("#"):
                    theta_ = -np.pi
                elif self.mp[y, x + 1] == ord("#"):
                    theta_ = 0

                # Reached the end
                else:
                    self.mp[y, x] = ord("x")
                    if straight > 0:
                        instruction_string = instruction_string + str(straight)

                    return instruction_string

                if straight > 0:
                    instruction_string = (
                        instruction_string + str(straight) + ","
                    )
                    straight = 0

                # Find angle between directions
                d = np.arccos(
                    np.dot(
                        [np.sin(theta + np.pi / 2), np.cos(theta + np.pi / 2)],
                        [np.sin(theta_), np.cos(theta_)],
                    )
                )

                if d == 0:
                    instruction_string += "L,"
                    theta = theta + np.pi / 2
                else:
                    instruction_string += "R,"
                    theta = theta - np.pi / 2
                # Update orientation

                dy, dx = np.int(-np.sin(theta)), np.int(np.cos(theta))

    def find_movement_routine(self):
        """ Find three repeating patterns in the movement string """

        str0 = self.traverse_scaffold() + ","

        for an in range(min(20, len(str0)), 0, -1):
            if str0[:an][-1] == ",":
                continue
            else:
                str1 = str0.replace(str0[0 : an + 1], "")
                for bn in range(min(20, len(str1)), 0, -1):
                    if str1[:bn][-1] == ",":
                        continue
                    else:
                        str2 = str1.replace(str1[0 : bn + 1], "")
                        for cn in range(min(20, len(str2)), 0, -1):
                            if str2[:cn][-1] == ",":
                                continue
                            else:
                                str3 = str2.replace(str2[0 : cn + 1], "")
                                if not str3:
                                    A, B, C = (
                                        str0[0:an],
                                        str1[0:bn],
                                        str2[0:cn],
                                    )
                                    routine = (
                                        str0.replace(A, "A")
                                        .replace(B, "B")
                                        .replace(C, "C")[:-1]
                                    )
                                    return routine, A, B, C

    def construct_input(self, print_iterations=False):
        """Get the routine and movement functions and
        translate into the desired input format"""
        routine, A, B, C = self.find_movement_routine()

        def toOrd(A):
            return [ord(x) for x in A]

        output = toOrd(routine) + [10] + toOrd(A) + [10] + toOrd(B) + [10]
        output += toOrd(C) + [10] + [ord("y" if print_iterations else "n"), 10]

        return output

    def print_video_feed(self):
        """ Print the progress of the scaffolding robot """

        screen = curses.initscr()
        height, width = screen.getmaxyx()

        # String template used to remove unecessary plotting
        valid = "#.<^v>\n"

        y_max, x_max = map(max, zip(*self.mp.keys()))
        mp = defaultdict(lambda: ord(" "))
        try:
            # Keep going until we reach the terminating condition
            while True:
                # Initial conditions for each map
                y, x, skip = 0, 0, False
                while True:
                    cond, output = self.ic()
                    if cond:
                        return output

                    # Check if output belongs to the valid string and
                    # filter new lines
                    if (chr(output % 256) not in valid) or (
                        x == 0 and output == 10
                    ):
                        skip = True

                    # If output =
                    if output == 10:
                        if not skip:
                            y += 1
                        x, skip = 0, False
                        if y > y_max - 1:
                            break
                    elif not skip:
                        mp[y, x] = output
                        x += 1

                # Print using screen
                self.print_map(screen, width, height, y_max, x_max, mp)

        finally:
            curses.endwin()

    def print_map(self, screen, width, height, y_max, x_max, mp):
        for row in range(0, y_max):
            msg = []
            for k in range(0, x_max):
                if k > width - 3:
                    break
                msg.append(chr(mp[row, k]))
                if row > height - 3:
                    break
            screen.addstr(row, 0, "".join(msg))
        screen.refresh()

    def collect_dust(self, print_iterations=False):
        """ Let the robot traverse using the compted input """

        input = self.construct_input(print_iterations)

        self.ic = Intcode(
            self.fileName, input=input, verbose=False, reset=False
        )
        self.ic.memory[0] = 2

        if not print_iterations:
            while True:
                cond, output = self.ic()
                if cond:
                    return output
        else:
            return self.print_video_feed()
