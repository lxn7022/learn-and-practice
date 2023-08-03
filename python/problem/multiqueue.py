import pytest
import random
from threading import Timer
import time


class Queue:
    def __init__(self, Q, q, low_threshold, high_threshold) -> None:
        self.Q = Q  # 队列最大Elem个数
        self.q = q  # 队列当前Elem个数
        self.low_threshold = low_threshold
        self.high_threshold = high_threshold
        self.rate_in = 0  # 当前流入速率
        self.rate_out = 0  # 当前流程速率
        self.thread_num = 1  # 当前处理线程数

    def __str__(self):
        return f"Queue(Q={self.Q},q={self.q},low={self.low_threshold},high={self.high_threshold},threadnum={self.thread_num})"

    def load_factor(self) -> float:
        return float(self.q/self.Q)

    def is_low_load(self) -> bool:
        if self.load_factor() < self.low_threshold:
            return True
        else:
            return False

    def is_high_load(self) -> bool:
        if self.load_factor() > self.high_threshold:
            return True
        else:
            return False

    def update_q(self, q) -> None:
        self.q = q

    def updata_thread_num(self, n):
        self.thread_num += n
        if self.thread_num < 1:
            self.thread_num = 1
        if self.thread_num > 20:
            self.thread_num = 20


class MultiQueue:
    def __init__(self) -> None:
        self.queues = []
        self.max_thread_num = 100  # 线程池最大线程数
        for i in range(4):
            _queue = Queue(100, 0, 0.5, 0.8)
            self.add_queue(_queue)
        self.interval = 2  # 2秒间隔
        self.timer = Timer(self.interval, self.adjust)
        self.timer.start()

    def add_queue(self, queue):
        self.queues.append(queue)

    def adjust(self):
        # 实时更新每个队列的负载
        for _queue in self.queues:
            _queue.update_q(random.randint(1, 100))
            print(_queue)
        # 试探性增加每个队列的任务数
        for _queue in self.queues:
            _queue.updata_thread_num(1)
        # 根据队列负载，调整线程数
        for _queue in self.queues:
            if _queue.is_low_load():
                _queue.updata_thread_num(-1)
            if _queue.is_high_load():
                _queue.updata_thread_num(1)
            print(_queue)
        # 启动下次负载调整
        self.timer = Timer(self.interval, self.adjust)
        self.timer.start()


def test_MultiQueue():
    mqueue = MultiQueue()
    while True:
        time.sleep(1)


if __name__ == '__main__':
    pytest.main(["-v", "-s", "multiqueue.py"])
