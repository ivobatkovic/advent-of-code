from os.path import dirname
from os.path import realpath
from os.path import join
from cryo import Cryo

if __name__ == "__main__":
    """Play the final game of advent of code 2019
    Solution to this input is to pick up:
    - klein bottle
    - mutex
    - hyper cube
    - mug"""

    dir_path = dirname(realpath(__file__))
    file_location = join(dir_path, "../data/input.txt")

    # Solve the final day by enjoying playing the game!
    cryo = Cryo(file_location)
    cryo.play()
