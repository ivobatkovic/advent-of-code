from donut import Donut
import pytest

@pytest.mark.parametrize("input1,steps1", [
    ('../input0.txt',23),
    ('../input1.txt',58),
])

def test_step1(input1,steps1):
    donut = Donut(input1)
    assert donut.shortest_path() == steps1


@pytest.mark.parametrize("input2,steps2", [
    ('../input0.txt',26),
    ('../input2.txt',396),
])

def test_step2(input2,steps2):
    donut = Donut(input2)
    assert donut.shortest_path(True) == steps2
