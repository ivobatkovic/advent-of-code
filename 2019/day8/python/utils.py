import numpy as np


class IO:
    @staticmethod
    def read_image(file_location, width, height):
        """Read data and shape it into and array [layers x width x height]."""
        try:
            with open(file_location) as f:
                x = list(map(int, f.readline().strip()))
                return np.reshape(x, (-1, height, width))

        except IOError:
            print("Cannot find file at: " + file_location)
            return None
