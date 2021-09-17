from collections import defaultdict
import re


class IO:
    @staticmethod
    def readFile(input_):

        formula = defaultdict(list)
        for line in input_.splitlines():

            # Separate the left hand side and right hand sides
            # Example: l = "3 A, 4 B => 1 AB"
            # data = ["3 A, 4 B", "1 AB"]
            # LHS = ["3 A", "4 B"]
            # RHS = ["1",  "AB"]
            data = re.findall("([^=>]+)", line)

            LHS = data[0].split(",")
            rhs = data[1].split()

            # Example
            # formula['A'] = (3, 1, 'AB' )
            # 3 A needed to produce 1 AB.
            for lhs in LHS:
                t = lhs.split()
                formula[t[1]].append((int(t[0]), int(rhs[0]), rhs[1]))

        return formula
