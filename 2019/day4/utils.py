class Digits:
    @staticmethod
    def double_digit(num):
        """Checks if there exist two adjacent matching digits."""

        for i in range(0, len(num) - 1):
            if num[i] == num[i + 1]:
                return True
        return False

    @staticmethod
    def double_digit_no_adjacent(num):
        """Checks if there exist two adjacent matching digits that are not part of as
        larger group of matching digits."""

        for i in range(0, len(num) - 1):
            if num[i] == num[i + 1]:
                # Special case in the beginning of the number
                if i == 0 and num[i + 1] != num[i + 2]:
                    return True
                # Special case in the end of the number
                if i == len(num) - 2 and num[i - 1] != num[i]:
                    return True
                # Somwhere in the middle of the number
                elif num[i - 1] != num[i] and num[i + 1] != num[i + 2]:
                    return True
        return False

    @staticmethod
    def make_monotonic(num):
        """Given an array of digits, returns the closest (rounded up) number that is
        monotonic."""

        for i in range(0, len(num) - 1):
            if num[i] > num[i + 1]:
                for j in range(i + 1, len(num)):
                    num[j] = num[i]
                return num
        return num

    @staticmethod
    def next_monotonic(num):
        """Returns the next monotonic number."""
        for i in range(len(num) - 1, -1, -1):
            if num[i] < 9:
                num[i] += 1
                for j in range(i, len(num)):
                    num[j] = num[i]
                return num
        return num

    @staticmethod
    def monotonic(num):
        """Checks if the string changes after sorting it. If it does, the number
        is not monotonic."""

        return num == "".join(sorted(num))
