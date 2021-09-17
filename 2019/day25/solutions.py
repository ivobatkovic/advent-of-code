from os.path import dirname
from os.path import realpath
from os.path import join
import sys

sys.path.append(join(dirname(realpath(__file__)), *[".."]))
from day25.cryo import Cryo

if __name__ == "__main__":
    """Play the final game of advent of code 2019
    Solution to this input is to pick up:
    - klein bottle
    - mutex
    - hyper cube
    - mug"""

    dir_path = dirname(realpath(__file__))
    file_location = join(dir_path, "data/input.txt")
    with open(join(dir_path, file_location), "r") as f:
        input_ = f.read()

    # Solve the final day by enjoying playing the game!
    cryo = Cryo(input_)
    cryo.play()
