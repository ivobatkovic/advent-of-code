#!/usr/bin/env python3
""" Credit: code taken and modified from https://github.com/amrit110/aoc """
import argparse
import os
from os.path import join
from shutil import copytree
from aocd import get_data

def download_data(year, day, dst ):
  try:
    data = get_data(year=year,day=day)
    print(f'Fetched input year {year}, day {day}')
  except:
    data = ''
    print(f'Failed fetching input year {year}, day {day}')
  with open(dst, 'r+') as f: f.write(data)

""" Initialize python source file. """
def setup_python_source(day):
  # Rename template_day.py
  src = os.path.join(*[f'day{day}','python','day.py_tmp'])
  dst = os.path.join(*[f'day{day}','python',f'day{day}.py'])
  os.rename(src,dst)

  # Remove top line from template_day.py
  with open(dst, 'r+') as f:
    data = f.readlines()[1:]; f.truncate(0); f.seek(0); f.writelines(data)

""" Initialize c++ build and source files """
def setup_cpp_source(day):
  # Rename files
  src_files = [os.path.join(f'day{day}','CMakeLists.txt_tmp'),
           os.path.join(*[f'day{day}','cpp','include',f'day.hpp_tmp']),
           os.path.join(*[f'day{day}','cpp','src',f'day.cpp_tmp']),
           os.path.join(*[f'day{day}','cpp','src','main.cpp_tmp'])]
  dst_files = [os.path.join(f'day{day}','CMakeLists.txt'),
               os.path.join(*[f'day{day}','cpp','include',f'day{day}.hpp']),
               os.path.join(*[f'day{day}','cpp','src',f'day{day}.cpp']),
               os.path.join(*[f'day{day}','cpp','src','main.cpp'])]
  for src,dst in zip(src_files,dst_files): os.rename(src,dst)

  # Update files with the corresponding day
  for dst in dst_files: 
    with open(dst,'r+') as f: 
      lines = f.read().splitlines()
      # Reset file cursor
      f.seek(0); f.truncate(0)
      for line in lines:
        f.write(eval("f'{}'".format(line))+'\n')


def parse_args():
  parser = argparse.ArgumentParser(description='Bootstrap')
  parser.add_argument('-d', '--day', required=True, type=int, help='day')
  return parser.parse_args()

def bootstrap_solution(day):
  target_dir = f'day{day}'
  # Try to make directories
  try:
    # Copy templates folder
    copytree("templates",f'day{day}')

    # Copy python source
    setup_python_source(day)
    
    setup_cpp_source(day)

    # Done
    print(f'Created skeleton for day{day}')

  except OSError as error: 
    print(f'Failed to create directory day{day}') 

  # Download latest data
  # data_dst = os.path.join(*[f'day{day}','data','input.txt'])
  # download_data(2020,day,data_dst)
    
def main():
    args = parse_args()
    day = args.day
    bootstrap_solution(day)


if __name__ == '__main__':
    main()