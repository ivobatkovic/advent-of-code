import time


class Orbit:
    """Class containing the orbit computer."""

    def __init__(self, file_location):
        """Initialize with a file location."""

        self.val, self.con = {}, {}
        self.init_connections(file_location)

    def init_connections(self, file_location):
        """Reads each line in the file and connects the objects through a
        dictionary."""

        try:
            with open(file_location) as f:
                for line in f:
                    a, b = line.strip().split(")")
                    self.val[a], self.val[b] = 0, 0
                    self.con[b] = a
        except IOError:
            print("Cannot find file at: " + file_location)

    def __call__(self):
        """Function that goes through the object connections and computes all
        direct  and indirect connections."""

        # Reset values
        self.val = dict.fromkeys(self.val.keys(), 0)

        for k in self.con:
            key = k
            while True:
                if key == "COM":
                    break
                else:
                    key = self.con[key]
                    self.val[key] += 1

        return sum(self.val.values())

    def orbits(self, key):
        """Computes the distance and sequence from key to COM"""
        if self.con.get(key):
            out = {}
            i = 0
            while True:
                if key == "COM":
                    break
                else:
                    key = self.con[key]
                    out[key] = i
                    i += 1
            return out
        return {}

    def minimum(self, x, y):
        """Finds shortest orbit distance between x and y."""

        x_dict, y_dict = self.orbits(x), self.orbits(y)
        for key_x, val_x in sorted(x_dict.items(), key=lambda x: x[1]):
            for key_y, val_y in sorted(y_dict.items(), key=lambda x: x[1]):
                if key_x == key_y:
                    return val_x + val_y

        return -1


def main():

    # Initialize puzzle
    o = Orbit("../data/input.txt")

    t0 = time.time()
    part_one = o()
    time_part_one = round((time.time() - t0) * 1e3)
    print(
        "Solution to part one: %s (time taken %s[ms])"
        % (part_one, time_part_one)
    )

    t0 = time.time()
    part_two = o.minimum("YOU", "SAN")
    time_part_two = round((time.time() - t0) * 1e3)
    print(
        "Solution to part one: %s (time taken %s[ms])"
        % (part_two, time_part_two)
    )


if __name__ == "__main__":
    main()
