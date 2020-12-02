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


def parse_args():
  parser = argparse.ArgumentParser(description='Bootstrap')
  parser.add_argument('-d', '--day', required=True, type=int, help='day')
  return parser.parse_args()

def bootstrap_solution(day):
  target_dir = f'day{day}'
  # Try to make directories
  try:
    # Copy templates folder
    copytree("templates",f'day{day}',dirs_exist_ok=False)

    # Rename template.py and remove top line
    src = os.path.join(*[f'day{day}','python','template_day.py'])
    dst = os.path.join(*[f'day{day}','python',f'day{day}.py'])
    os.rename(src,dst)

    # Remove top line from template_day.py
    with open(dst, 'r+') as f:
      data = f.readlines()[1:]; f.truncate(0); f.seek(0); f.writelines(data)
        
    # Done
    print(f'Created skeleton for day{day}')

  except OSError as error: 
    print(f'Directory day{day} already exists') 

  # Download latest data
  data_dst = os.path.join(*[f'day{day}','data','input.txt'])
  download_data(2020,day,data_dst)
    
def main():
    args = parse_args()
    day = args.day
    bootstrap_solution(day)


if __name__ == '__main__':
    main()