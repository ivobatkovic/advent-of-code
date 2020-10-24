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
        if 'deal with increment ' in line:
          instructions.append(('I',int(line[20:])))
        elif 'deal into new stack' in line:
          instructions.append(('D',0))
        elif 'cut ' in line:
          instructions.append(('C',int(line[4:])))
    return instructions

  def parse(self,instructions):
    """ The shuffle process for card x can be written as y = a * x + b. """

    # x = a*x + b = x
    a, b = 1, 0

    # Go through instructions list
    for instruction, number in instructions:
      if instruction == 'I':
        da, db = number, 0
      elif instruction == 'D':
        da, db = -1,-1
      elif instruction == 'C':
        da, db = 1, -number

      a, b = (da * a) % self.num_cards, (da * b + db) % self.num_cards

    return a, b


def part_one(file):
  """ Part one: apply the linear transformation y = a*x + b to get which
  position card x ends up in after one shuffle """

  n, card = 10007, 2019
  deck = Deck(file,num_cards = 10007)

  return ( deck.a * card + deck.b ) % n

def part_two(file):
  """ Part two: apply the linear transformation y = a*x+b, m times.
  The solution consists of two parts.
  First: we can write the m:th shuffle as:
      y = a^m * x + b * (a^(m-1) +a^2 + a + 1 = a^m * x + b * (a^m-1)/(a-1)

  Next, we want to apply y % n, to keep the size of the number small. Here, we
  use the relations for y = a*x + b:
      y % n == ( (a*x % n) + b % n) % n and (a*b) % n == ((a%n)*(b%n)) % n
  Since n in this problem is a prime, we can use Fermat's little theorem which
  says that  x^(n-1) % n == 1 % n, hence x^(n-2) % n == x^(-1) % n. We apply
  this relation to x = (a-1) -> (a-1)^-1 % n == a^(n-2) % n to obtain
      A = a^m
      B = ( b * (a^m-1) % n ) * ( a^(n-2) % n ) % n
      y % n = ( A%n * x + (B % n) ) % n

  Second: We want to know what card is at position x, hence we need to invert
      y = A * x + B -> x = (y-B) * A^(-1)
      x % n  <=> ( ((y-B) % n) * (A^(n-2) % n) ) % n """

  n, card = 119315717514047, 2020
  deck = Deck(file,num_cards = n)

  m_times = 101741582076661
  A = pow(deck.a,m_times,n)
  B = ( deck.b * (pow(deck.a,m_times,n)-1) * pow(deck.a-1, n-2, n) ) % n

  return ( (card-B) % n ) * pow(A,n-2,n) % n


if __name__ == "__main__":

  file = '../input.txt'
  print('Solution to part one: %s' % part_one(file))
  print('Solution to part one: %s' % part_two(file))
