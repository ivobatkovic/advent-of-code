import numpy as np


class IO:
    @staticmethod
    def read_image(input_):
        """Read data and shape it into and array [layers x width x height]."""
        x = []
        for line in input_.splitlines():
            x.append(list(line.strip()))
        return np.reshape(x, (-1, len(x)))
