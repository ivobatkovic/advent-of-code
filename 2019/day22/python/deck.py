class Deck:
    """ Class sorting the cards in the deck """

    def __init__(self, file, num_cards):
        """ Initialize number of cards and parse instructions """
        self.file = file
        self.num_cards = num_cards
        self.a, self.b = self.parse(self.read_shuffle())

    def read_shuffle(self):
        """ Go through instructions list to shuffle """
        instructions = []
        with open(self.file) as f:
            for line in f.readlines():
                if "deal with increment " in line:
                    instructions.append(("I", int(line[20:])))
                elif "deal into new stack" in line:
                    instructions.append(("D", 0))
                elif "cut " in line:
                    instructions.append(("C", int(line[4:])))

        return instructions

    def parse(self, instructions):
        """ The shuffle process for card x can be written as y = a * x + b. """

        # x = a*x + b = x
        a, b = 1, 0

        # Go through instructions list
        for instruction, number in instructions:
            if instruction == "I":
                da, db = number, 0
            elif instruction == "D":
                da, db = -1, -1
            elif instruction == "C":
                da, db = 1, -number

            a, b = (da * a) % self.num_cards, (da * b + db) % self.num_cards

        return a, b
