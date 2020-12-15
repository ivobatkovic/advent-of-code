import numpy as np


class IO:
    @staticmethod
    def read_image(file_location):
        """ Read data and shape it into and array [layers x width x height]."""
        try:
            with open(file_location) as f:
                x = []
                for line in f:
                    x.append(list(line.strip()))
            return np.reshape(x, (-1, len(x)))

        except IOError:
            print("Cannot find file at: " + file_location)
            return None
