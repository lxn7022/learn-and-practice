import time
import timeit
import wrapt
from functools import wraps


def logging(level):
    @wrapt.decorator
    def wrapper(wrapped, instance, args, kwargs):
        print("[{}]: enter {}()".format(level, wrapped.__name__))
        return wrapped(*args, **kwargs)
    return wrapper


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
@task_retry(retry_count=3, timeout=1, errcode=1)
def dotask():
    return 0


ret = dotask()
