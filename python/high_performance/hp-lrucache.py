
import clock
import functools
import pytest

# 普通版本


def factorial(n):
    return n * factorial(n-1) if n else 1

# 加速版本


@functools.lru_cache
def factorial_lru(n):
    return n * factorial(n-1) if n else 1


N = 400


@clock.clock
def test_factorial():
    factorial(N)


@clock.clock
def test_factorial_lru():
    factorial_lru(N)


if __name__ == "__main__":
    pytest.main(["-s", "-v", "hp-lrucache.py"])
