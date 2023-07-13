import time
from functools import wraps


def task_retry(retry_count: int = 5, timeout: int = 2, errcode: int = 0):
    """
    任务重试装饰器 Args:
    retry_count: 最大重试次数 默认5次
    timeout: 每次重试间隔 默认2s
    errcode: 碰到该错误码则重试
    """
    def _task_retry(task_func):
        @ wraps(task_func)
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


@task_retry(retry_count=3, timeout=1, errcode=1)
def gpu_api():
    return 0


ret = gpu_api()
