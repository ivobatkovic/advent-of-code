#!/usr/bin/env python3
from os.path import dirname, realpath, join
import time, pytest

def transform_input(input_):
  # custom transform for the day
  count, letter, pw = input_.replace(':','').split()
  low, high = count.split('-')
  return int(low), int(high), letter, pw


def read_input(file_name = '../data/input.txt'):
  dir_path = dirname(realpath(__file__))
  with open(file_name, 'r') as f:
    input_ = [transform_input(x.strip()) for x in f.readlines()]

  return input_

def solve_part1(input_):
  n_pws = 0
  for low, high, letter, pw in input_:
    n_pws += 1 if low <= pw.count(letter) <= high else 0
  return n_pws
    

def solve_part2(input_):
  n_pws = 0
  for low, high, letter, pw in input_:
    n_pws += 1 if (pw[low-1] == letter) ^ (pw[high-1] == letter) else 0
  return n_pws


def main():
  
  input_ = read_input()

  t0 = time.time()
  part1 = solve_part1(input_)
  time_part1 = round((time.time()-t0)*1e3)
  print(f'Solution to part one: {part1} (time taken {time_part1}[ms])')

  t0 = time.time()
  part2 = solve_part2(input_)
  time_part2 = round((time.time()-t0)*1e3)
  print(f'Solution to part one: {part2} (time taken {time_part2}[ms])')


if __name__ == '__main__':
  main()

@pytest.mark.parametrize("input1,output1", [
  ('../data/test_input0.txt', 2)
])

def test1(input1,output1):
  assert solve_part1(read_input(input1)) == output1

@pytest.mark.parametrize("input2,output2", [
  ('../data/test_input0.txt', 1)
])

def test1(input2,output2):
  assert solve_part2(read_input(input2)) == output2
