import pytest

@pytest.mark.parametrize("input1,output1", [
  ('../data/test_input0.txt', 1)
])

def test1(input1,output1):
  assert solve_part1(read_input(input1)) == output1

@pytest.mark.parametrize("input2,output2", [
  ('../data/test_input0.txt', 1)
])

def test2(input2,output2):
  assert solve_part2(read_input(input2)) == output2

