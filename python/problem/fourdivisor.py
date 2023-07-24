# coding=utf-8
"""
我们可以遍历数组 nums 中的每个元素，依次判断这些元素是否恰好有四个因数。
对于任一元素 x，我们可以用类似质数判定的方法得到它的因数个数，
其本质为：如果整数 x 有因数 y，那么也必有因数 x/y，并且 y 和 x/y 中至少有一个不大于 sqrt(x)。
这样我们只需要在 [1, sqrt(x)] 的区间内枚举可能为整数 x 的因数 y，
并通过 x/y 得到整数 x 的其它因数。

如果 x 恰好有四个因数，我们就将其素数因数作为因数，累积到最终的乘积中去。

下面的题目中，找出sums中所有的四因字数，求出所有素数因数的乘积，素数因数不能有重复。
"""

import pytest


class Solution:
    def multiFourDivisors(self, nums: list[int]) -> int:

        def _isFourDivisor(num: int) -> tuple[int, int] | None:
            if num in (1, 2, 3, 4):
                return None
            min = 2
            max = int(num**0.5)
            divisors = []
            for i in range(min, max+1):
                if num % i == 0:
                    divisors.append((i, int(num/i)))
            if len(divisors) == 1:
                return divisors[0]
            else:
                return None
        # 找出所有素数
        divisors_all = []
        for num in nums:
            divisor = _isFourDivisor(num)
            if divisor != None:
                divisors_all.append(divisor[0])
                divisors_all.append(divisor[1])
        print(divisors_all)
        # 长度<=2，特殊处理
        len_divisors_all = len(divisors_all)
        if len_divisors_all < 2:
            return 0
        if len_divisors_all == 2:
            return divisors_all[0] * divisors_all[1]
        # 排序
        divisors_all.sort()
        # uniq
        divisors_all_uniq = set(divisors_all)
        multi = 1
        for i in divisors_all_uniq:
            multi *= i
        return multi


def test_Solution():
    nums = [1, 2, 4, 21, 33]
    # 21=3*7, 33=3*11, output [3,7,11]=>231
    solu = Solution()
    assert solu.multiFourDivisors(nums) == 231
    nums = [1, 2, 4]
    assert solu.multiFourDivisors(nums) == 0


if __name__ == '__main__':
    pytest.main(["-s", "fourdivisor.py"])
