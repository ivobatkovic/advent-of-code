from report import Report
import pytest

@pytest.mark.parametrize("input1,output1", [
    ('../data/test_input0.txt', 514579)
])

def test_step1(input1,output1):
    report = Report(input1)
    assert report.part_one() == output2


@pytest.mark.parametrize("input2,output2", [
    ('../data/test_input0.txt', 241861950)
])

def test_step1(input2,output2):
    report = Report(input2)
    assert report.part_two() == output2
