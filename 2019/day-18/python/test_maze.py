from maze import Maze
import pytest

@pytest.mark.parametrize("input1,steps1", [
    ('../input0.txt', 8),
    ('../input1.txt',86),
    ('../input2.txt',132),
    ('../input3.txt',136),
    ('../input4.txt',81),
])

def test_step1(input1,steps1):
    maze = Maze(input1)
    assert maze.compute_shortest_path() == steps1


@pytest.mark.parametrize("input2,steps2", [
    ('../input0_2.txt', 8),
    ('../input1_2.txt',24),
    ('../input2_2.txt',32),
    ('../input3_2.txt',72),
])
def test_steps(input2,steps2):
    maze = Maze(input2,True)
    assert maze.compute_shortest_path() == steps2
