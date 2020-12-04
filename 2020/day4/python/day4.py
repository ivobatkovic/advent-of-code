#!/usr/bin/env python3
from os.path import dirname, realpath, join
import time, pytest



def transform_input(input_):
  # custom transform for the day
  if not input_:
    return None
  else:
    # Split into spaces and then into key, value pairs
    return [parts.split(':') for parts in input_.split()]
      

def read_input(file_name = '../data/input.txt'):
  
  dir_path = dirname(realpath(__file__))
  with open(join(dir_path,file_name), 'r') as f:
    # Transform input
    input_ = [transform_input(x.strip()) for x in f.readlines()]

    # Assing input into passports
    passports, n_passports = [dict()], 0
    for ip in input_:
      if ip == None:
        passports.append(dict())
        n_passports += 1
      else:
        for key,val in ip:
          passports[n_passports][key] = val

  return passports

def solve_part1(input_):
  # Required fields
  req = ['byr', 'iyr', 'eyr', 'hgt','hcl','ecl','pid','cid']

  n_valid = 0
  for ip in input_:
    # Since cid is not necessary, just pop it in
    if not 'cid' in ip: ip['cid'] = None

    # Check if we have as many matches as required keys
    if sum([key in req for key in ip.keys()])==len(req): n_valid +=1
        
  return n_valid


def solve_part2(input_):

  # Matching strings
  colors = ['amb','blu','brn','gry','grn','hzl','oth']
  hair_color = '0123456789abcdef'
  
  n_valid = 0
  for ip in input_:
    # Continue if passport is OK
    if solve_part1([ip]):
      nOk = 0
      for key in ip.keys():
        if key == 'byr' and 1920<=int(ip[key])<=2002: nOk +=1  
        if key == 'iyr' and 2010<=int(ip[key])<=2020: nOk +=1
        if key == 'eyr' and 2020<=int(ip[key])<=2030: nOk +=1
        if key == 'hgt':
          if ip[key][-2:] == 'cm' and 150<=int(ip[key][:-2])<=193: nOk +=1
          elif ip[key][-2:] == 'in' and 59<=int(ip[key][:-2])<=76: nOk +=1
        if key == 'hcl' and ip[key][0] == '#' \
          and sum(k in hair_color for k in ip[key][1:])==6: nOk +=1
        if key == 'ecl' and len(ip[key]) == 3 and ip[key] in colors: nOk +=1
        if key == 'pid' and len(ip[key])==9 and ip[key].isdigit(): nOk += 1
        if key == 'cid': nOk += 1
      if nOk == len(ip.keys()):
        n_valid +=1
        
  return n_valid
  


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
  ('../data/test_input1.txt', 0),
  ('../data/test_input2.txt', 4),
])

def test2(input2,output2):
  assert solve_part2(read_input(input2)) == output2