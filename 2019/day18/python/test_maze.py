from maze import Maze
import pytest

@pytest.mark.parametrize("input1,steps1", [
    ('../data/test_input0.txt', 8),
    ('../data/test_input1.txt', 86),
    ('../data/test_input2.txt', 132),
    ('../data/test_input3.txt', 136),
    ('../data/test_input4.txt', 81),
])

def test_step1(input1,steps1):
    maze = Maze(input1)
    assert maze.compute_shortest_path() == steps1


@pytest.mark.parametrize("input2,steps2", [
    ('../data/test_input5.txt', 8),
    ('../data/test_input6.txt', 24),
    ('../data/test_input7.txt', 32),
    ('../data/test_input8.txt', 72),
])
def test_steps(input2,steps2):
    maze = Maze(input2,True)
    assert maze.compute_shortest_path() == steps2
