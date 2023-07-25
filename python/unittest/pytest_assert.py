# pytest是使用python自带的断言
import pytest


def func(x):
    return x + 1


def test_a():
    print("____test_a____")
    assert func(2) == 5


def test_b():
    print("____test_b____")
    assert not func(2) == 3


def test_c():
    print("____test_b____")
    assert func(2) in ["a", "b", "c"]


def test_d():
    print("____test_b____")
    assert func(2) not in ["a", "b", "c"]


if __name__ == '__main__':
    pytest.main(["-s", "-v", "pytest_assert.py"])
