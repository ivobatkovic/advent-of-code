import numpy as np


class IO:
    @staticmethod
    def read_image(input_, width, height):
        """Read data and shape it into and array [layers x width x height]."""
        x = list(map(int, input_.strip()))
        return np.reshape(x, (-1, height, width))
