#!/usr/bin/env python3

import argparse
import os
from os.path import join
from shutil import copyfile, copyfileobj

"""Create skeleton solution script for given day.
   Credit: code taken from https://github.com/amrit110/aoc
"""

def parse_args():
  parser = argparse.ArgumentParser(description='Bootstrap')
  parser.add_argument('-d', '--day', required=True, type=int, help='day')
  return parser.parse_args()

def bootstrap_solution(day):
  target_dir = f'day{day}'
  # Try to make directories
  try:
    os.makedirs(target_dir+'/python', exist_ok=False)
    os.makedirs(target_dir+'/data', exist_ok=False)
  
    # day and test_day paths
    day_path = join(target_dir, f'python/day{day}.py')
    test_day_path = join(target_dir, f'python/test_day{day}.py')

    # template and test_template paths
    template_day_path = join('.', 'templates/template_day.py')
    template_test_path = join('.', 'templates/template_test_day.py')

    # Copy template_day and remove first row in the file
    source_day = open(template_day_path, 'r').readlines()[1:]  
    with open(day_path, 'w') as sp:
      [sp.write(line) for line in source_day]

    # Copy template_test_day and append row
    source_test = open(template_test_path, 'r').readlines()
    with open(test_day_path, 'w') as sp:
      sp.write(f'from day{day} import *\n')
      [sp.write(line) for line in source_test]

    # Create empty input file
    with open(join(target_dir, 'data/input.txt'), 'w') as f: pass
    with open(join(target_dir, 'data/test_input0.txt'), 'w') as f: pass

    # Done
    print(f'Created skeleton for day{day}')

  except OSError as error: 
    print(f'Directory day{day} already exists') 
    

def main():
    args = parse_args()
    day = args.day
    bootstrap_solution(day)


if __name__ == '__main__':
    main()