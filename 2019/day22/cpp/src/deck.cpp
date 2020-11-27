#include "deck.hpp"
#include <cassert>
#include "utils.hpp"

Deck::Deck(std::string file_name, int64_t num_cards) : 
    m_file_name(file_name), m_num_cards(num_cards), m_a(), m_b()
{
  parse(read_shuffle(),m_a,m_b);
}

void Deck::parse(std::vector<std::pair<char, int>> 
    instructions,int64_t &a, int64_t &b)
{
  a = 1; b = 0;
  
  for (auto &x : instructions) {
    int db(0), da(0);
    if (x.first == 'I') {
      da = x.second; db = 0;
    } else if ( x.first == 'D') {
      da = -1; db = -1;
    } else if ( x.first == 'C') {
      da = 1; db = -x.second;
    }

    a = mod(da * a,m_num_cards);
    b = mod(da * b + db, m_num_cards);
  }
}

std::vector<std::pair<char, int>> Deck::read_shuffle()
{
  std::vector<std::string> input;
  std::vector<std::pair<char, int>> instructions;
  utils::readFile(m_file_name, input);

  for (auto &line : input) {
    size_t len = line.size();
    if (line.find("deal with increment") != std::string::npos) {
      instructions.push_back(
        std::make_pair('I',std::stoi(line.substr(20,len-20))));
    }
    else if (line.find("deal into new stack") != std::string::npos) {
      instructions.push_back(
        std::make_pair('D', 0));
    }
    else if (line.find("cut") != std::string::npos) {
      instructions.push_back(
        std::make_pair('C', std::stoi(line.substr(4, len - 4))));
    }
  }
  
  return instructions;
}

// Apply the linear transformation to see where <card> ends up
int Deck::part_one(int card)
{
  return (m_a * card + m_b) % m_num_cards;
}

/**
 * @brief Part two: apply the linear transformation y = a*x+b, m times.
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
      x % n  <=> ( ((y-B) % n) * (A^(n-2) % n) ) % n
 * 
 * @param card 
 * @param n_shuffles 
 * @return int64_t 
 */
int64_t Deck::part_two(int card, int64_t n_shuffles) {

  auto A = modular_power(m_a, n_shuffles, m_num_cards);
  auto an = modular_power(m_a, n_shuffles, m_num_cards);

  int128 B = mod(m_b * modular_divide(an-1, m_a-1, m_num_cards), m_num_cards);
  auto moddiv = modular_divide(mod(card - B, m_num_cards), A, m_num_cards);
  
  return int64_t(mod(moddiv, m_num_cards));
}

int128 Deck::mod(int128 a, int128 b)
{
  return (a >= 0) ? (a % b) : (b + a % b);
}

int128 Deck::gcd_extended(int128 a, int128 b, int128 &x, int128 &y)
{
  if (a == 0)
  {
    x = 0;
    y = 1;
    return b;
  }

  int128 x1, y1;
  int128 gcd = gcd_extended(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
  return gcd;
}

int128 Deck::modular_inverse(int128 b, int128 n)
{
  int128 x, y;
  int128 g = gcd_extended(b, n, x, y);
  return (g != 1) ? -1 : mod(x, n);
}

int128 Deck::modular_divide(int128 a, int128 b, int128 n)
{
  a = mod(a, n);
  int128 inv = modular_inverse(b, n);
  return (inv == -1) ? -1 : (a * inv) % n;
}

int128 Deck::modular_power(int128 base, int128 exponent, int128 n)
{
  assert(exponent >= 0);
  if (exponent == 0)
  {
    return (base == 0) ? 0 : 1;
  }

  int128 bit = 1;
  int128 power = mod(base, n);
  int128 out = 1;
  while (bit <= exponent)
  {
    if (exponent & bit)
    {
      out = mod(out * power, n);
    }
    power = mod(power * power, n);
    bit <<= 1;
  }

  return out;
}