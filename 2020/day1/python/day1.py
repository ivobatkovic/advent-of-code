#!/usr/bin/env python3
from os.path import dirname, realpath, join
import time, pytest

def transform_input(input_):
  # custom transform for the day
  return int(input_)


def read_input(file_name = '../data/input.txt'):
  dir_path = dirname(realpath(__file__))
  with open(file_name, 'r') as f:
    input_ = [transform_input(x.strip()) for x in f.readlines()]

  return input_

def solve_part1(input_):
  for i, v1 in enumerate(input_[:-1]):
    for j, v2 in enumerate(input_[i:]):
      if v1 + v2 == 2020:
        return v1*v2

def solve_part2(input_):
  for i, v1 in enumerate(input_[:-2]):
    for j, v2 in enumerate(input_[i:-1]):
      for k, v3 in enumerate(input_[j:]):
        if v1 + v2 + v3== 2020:
          return v1*v2*v3


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
  ('../data/test_input0.txt', 514579)
])

def test1(input1,output1):
  assert solve_part1(read_input(input1)) == output1

@pytest.mark.parametrize("input2,output2", [
  ('../data/test_input0.txt', 241861950)
])

def test2(input2,output2):
  assert solve_part2(read_input(input2)) == output2