from os.path import dirname
from os.path import realpath
from os.path import join
import time


def solve_part_one(input_string):
    """Function that applies the filter along the digits."""

    # Make a list of the integers
    d = [int(x) for x in input_string]

    # Find out length of the list of integers
    N = len(d)

    # Loop through 100 FFTs
    for _ in range(100):
        # Use filter (0,1,0,-1) across each digit i and then multiply the
        # phase with k
        d = [
            abs(
                sum(
                    (0, 1, 0, -1)[(i + 1) // (k + 1) % 4] * d[i]
                    for i in range(N)
                )
            )
            % 10
            for k in range(N)
        ]

    return "".join(str(x) for x in d[:8])


def solve_part_two(input_string):
    """We realize that the last digit in the FFT is always the same, since the
    filter will be [0,0,...,1]. For the second last element, the filter looks
    like [0,0,...,1,1], all the way until the middle digit in the number.
    Hence, we can compute the number backwards if the offset is more than
    half the digit
    """

    # Make a list of the integers
    d = [int(x) for x in input_string]

    # Digits to skip
    d_skip = int(input_string[:7])

    # Check if the elements we want to skip are on the second half of the digit
    if len(d) * 10000 < 2 * d_skip:
        # Repeat the number 10000 times and, since we are in right half,
        # chop the number up to the digits with the offset
        v = (10000 * d)[d_skip:]

        # Loop through 100 FFTs
        for _ in range(100):
            # Go from the end of the list to the first number and compute
            # the new values using the old ones
            for i in range(len(v) - 1, 0, -1):
                v[i - 1] = (v[i - 1] + v[i]) % 10

        return "".join(str(x) for x in v[:8])
    else:
        return "Algorithm does not work"


def main():

    dir_path = dirname(realpath(__file__))
    file_location = join(dir_path, "../data/input.txt")

    # Part one
    t0 = time.time()
    # Open the file and read the input into a string s
    with open(file_location) as f:
        input_string = f.read().strip()

    part_one = solve_part_one(input_string)
    time_part_one = round((time.time() - t0) * 1e3)
    print(
        "Solution to part one: %s (time taken %s[ms])"
        % (part_one, time_part_one)
    )

    t0 = time.time()
    part_two = solve_part_two(input_string)
    time_part_two = round((time.time() - t0) * 1e3)
    print(
        "Solution to part two: %s (time taken %s[ms])"
        % (part_two, time_part_two)
    )


if __name__ == "__main__":
    main()
