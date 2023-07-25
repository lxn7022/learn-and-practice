import pytest
import random
from tenacity import wait_fixed, stop_after_attempt, retry_if_result
import tenacity
import time
import timeit
import wrapt
from functools import wraps


def clock(func):
    def clocked(*args, **kwargs):
        start = timeit.default_timer()
        res = func(*args, **kwargs)
        run_time = timeit.default_timer() - start
        func_name = func.__name__
        arg_str = ', '.join(repr(arg) for arg in args)
        print('调用>>>%s(%s)   \t返回值>>>%r   \t耗时>>>%0.8fs\n' %
              (func_name, arg_str, res, run_time))
        return res
    return clocked


def logging(level):
    @wrapt.decorator
    def wrapper(wrapped, instance, args, kwargs):
        print("[{}]: enter {}()".format(level, wrapped.__name__))
        return wrapped(*args, **kwargs)
    return wrapper


def task_retry(retry_count: int = 5, timeout: int = 2, errcode: int = 0):
    """
    任务重试装饰器 Args:
    retry_count: 最大重试次数 默认5次
    timeout: 每次重试间隔 默认2s
    errcode: 碰到该错误码则重试
    """
    def _task_retry(task_func):
        @wraps(task_func)
        def wrapper(*args, **kwargs):
            # 函数循环重试
            for retry_cnt in range(retry_count):
                print(f"execute count {retry_cnt + 1}")
                try:
                    task_result = task_func(*args, **kwargs)
                    if task_result == errcode:  # 碰到指定错误码则重试
                        time.sleep(timeout)
                        task_result = task_func(*args, **kwargs)
                        return task_result
                except Exception as e:  # 发生异常则重试
                    time.sleep(timeout)
        return wrapper
    return _task_retry


@clock
@logging(level="INFO")
@task_retry(retry_count=3, timeout=2, errcode=-1)
def dotask():
    return 0

# --------------------------


def singleton(cls):
    """设计模式: singleton"""
    instances = {}

    def wrapper(*args, **kwargs):
        if cls not in instances:
            instances[cls] = cls(*args, **kwargs)
        return instances[cls]
    return wrapper


@singleton
class cls:
    """通过装饰器将一个类变为单例"""

    def func(self):
        pass


def test_singleton():
    a = cls()
    b = cls()
    assert a is b

# -------------------------


def return_last_value(retry_state):
    print("执行回调函数")
    return retry_state.outcome.result()  # 表示返回原函数的返回值


def err_code(value):
    return value in (-1, -2, -3)


@tenacity.retry(wait=wait_fixed(2),  # 重试前等待2秒
                stop=stop_after_attempt(3),  # 总共重拾3次
                retry_error_callback=return_last_value,  # 最后一次重试失败后的回调函数
                retry=retry_if_result(err_code))  # 碰到指定错误码时回调
def dotask2():
    rets = [0, -1]
    ret = rets[random.randrange(0, 2)]
    print(f"dotask2: ret={ret} retry... ")
    return ret


if __name__ == "__main__":
    ret = dotask()
    dotask2()
    pytest.main(["-v", "-s", "decorator.py"])
