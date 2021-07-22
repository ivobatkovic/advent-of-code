from utils import Digits
import time
import numpy as np


def secure_container(input):
    """Solves problem one and two by iterating over monotonic numbers and
    checking the double digits, with no adjacency, condition."""

    start = Digits.make_monotonic(
        np.array([int(char) for char in str(input[0])])
    )
    stop = np.array([int(char) for char in str(input[1])])

    sol1, sol2 = 0, 0
    while np.sum(start < stop) > 0:
        sol1 += 1 if Digits.double_digit(start) else 0
        sol2 += 1 if Digits.double_digit_no_adjacent(start) else 0
        start = Digits.next_monotonic(start)

    return sol1, sol2


def main():
    """Print out the problem solutions."""

    # Timing reference
    t0 = time.time()

    # Puzzle input
    input = [108457, 562041]

    # Print solutions
    t0 = time.time()
    solution1, solution2 = secure_container(input)
    time_end = round((time.time() - t0) * 1e3)

    print(
        "Solution to part two: %s (time taken %s[ms])" % (solution1, time_end)
    )
    print(
        "Solution to part two: %s (time taken %s[ms])" % (solution2, time_end)
    )


if __name__ == "__main__":
    main()
