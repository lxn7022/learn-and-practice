# 用 Taichi 加速 Python：提速 100+ 倍！
# https://zhuanlan.zhihu.com/p/547123604

import pytest
import clock

import taichi as ti
import taichi.math as tm

ti.init()


def is_prime(n: int):
    result = True
    max = n**0.5
    for k in range(2, int(max) + 1):
        if n % k == 0:
            result = False
            break
    return result


def count_primes(n: int) -> int:
    count = 0
    for k in range(2, n):
        if is_prime(k):
            count += 1
    return count


@ti.func
def is_prime_taichi(n: int):
    result = True
    max = n ** 0.5
    for k in range(2, int(max) + 1):
        if n % k == 0:
            result = False
            break
    return result


@ti.kernel
def count_primes_taichi(n: int) -> int:
    count = 0
    for k in range(2, n):
        if is_prime(k):
            count += 1
    return count


N = 1000000


@clock.clock
def test_count_primes():
    count_primes(N)


@clock.clock
def test_count_primes_taichi():
    count_primes_taichi(N)

# -----------------------------------------


n = 320
pixels = ti.field(dtype=float, shape=(n * 2, n))


@ti.func
def complex_sqr_taichi(z):  # complex square of a 2D vector
    return tm.vec2(z[0] * z[0] - z[1] * z[1], 2 * z[0] * z[1])


@ti.kernel
def paint_taichi(t: float):
    for i, j in pixels:  # Parallelized over all pixels
        c = tm.vec2(-0.8, tm.cos(t) * 0.2)
        z = tm.vec2(i / n - 1, j / n - 0.5) * 2
        iterations = 0
        while z.norm() < 20 and iterations < 50:
            z = complex_sqr_taichi(z) + c
            iterations += 1
        pixels[i, j] = 1 - iterations * 0.02


@clock.clock
def test_paint_taichi():
    for i in range(100):
        paint_taichi(i * 0.03)


if __name__ == "__main__":
    # Test_count_primes()
    # Test_count_primes_taichi()
    # 运行报错，系统提示：
    # Taichi requires glibc >= 2.27 to run, please try upgrading your OS to a recent on
    # TypeError: int() argument must be a string, a bytes-like object or a real number, not 'Expr'
    # test_paint_taichi()
    pytest.main(["-s", "-v", "hp-taichi.py"])
