import pytest
from itertools import combinations


def ksum(nums: list[int], k: int, target: int) -> list[tuple[int]]:
    if len(nums) < k:
        return []
    nums_set = set(nums)  # 去掉重复元素
    result = [combs for combs in combinations(nums_set, k)
              if sum(combs) == target]
    return result


def combinationSum(nums: list[int], target: int) -> list[tuple[int]]:
    if not nums:
        return []
    result = []
    for k in range(2, len(nums)+1):
        tmp = ksum(nums, k, target)
        if tmp:
            result.append(tmp)
    return result


def test_ksum():
    nums = [1, 0, -1, 0, -2, 2]
    target = 0
    k = 3
    result = ksum(nums, k, target)
    print(result)


def test_combinationSum():
    nums = [1, 0, -1, 0, -2, 2]
    target = 0
    print(combinationSum(nums, target))


if __name__ == '__main__':
    pytest.main(["-v", "-s", "ksum.py"])
