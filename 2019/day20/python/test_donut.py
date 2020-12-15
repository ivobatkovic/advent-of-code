from os.path import dirname
from os.path import realpath
from os.path import join
from donut import Donut
import pytest


@pytest.mark.parametrize(
    "input1,steps1",
    [
        ("../data/test_input0.txt", 23),
        ("../data/test_input1.txt", 58),
    ],
)
def test_step1(input1, steps1):
    donut = Donut(join(dirname(realpath(__file__)), input1))
    assert donut.shortest_path() == steps1


@pytest.mark.parametrize(
    "input2,steps2",
    [
        ("../data/test_input0.txt", 26),
        ("../data/test_input2.txt", 396),
    ],
)
def test_step2(input2, steps2):
    donut = Donut(join(dirname(realpath(__file__)), input2))
    assert donut.shortest_path(True) == steps2
