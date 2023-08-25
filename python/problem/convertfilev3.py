"""
说明
1. 有 1000 个 20M ⼤⼩的⽂本⽂件，⽂件中每⾏数据的格式固定为: 
{"name": "xx","timestamp": xx, "content": "xx"}
name: 字符串， ⻓度为 32 个字节以内
timestamp: 毫秒级时间戳
content: 字符串，⻓度为 1024 个字节以内 ⽂件地址: https://mc-public-resource-cn.s3.cn-north-1.amazonaws.com.cn/records.zip

2. 编写程序完成如下要求 
a. 找出所有 name 为 zhangsan 的⾏，并按照 timestamp 从⼩到⼤排序 
b. 将排序好的结果重新写⼊新的⽂件，规则如下： 
i. 按照 timestamp 以天为维度组织⽂件，新⽂件的命名规则为 年-⽉-⽇，例如
(2022-1-12)
ii. 将所有位于同⼀天的数据存放于同⼀个⽂件中 

要求
1. 开发语⾔可以根据⾃⼰的偏好在 python、java、go 中选择，可以⾃由的选择框架、 库 
2. 在硬件性能恒定(内存 16 G)的情况下，尽可能的缩短程序耗时 

输出: 1. 程序耗时 2. 解体思路

doc：https://docs.qq.com/doc/DWkJFa1pFendWc2lX
"""

import sys
import memory_profiler
import clock
import pytest
import datetime
import time
import os
from concurrent import futures


def getfiles(dir: str) -> list[str]:
    """获取某个目录下的所有普通文件"""
    res = []
    # Iterate directory
    for path in os.listdir(dir):
        if "record_" not in path:
            continue
        fname = os.path.join(dir, path)
        if os.path.isfile(fname):
            res.append(fname)
    return res


def workers():
    return os.cpu_count()


class ConvertFile:
    def __init__(self) -> None:
        self.path1 = "/data/records/"  # 存放源数据
        self.path2 = "/data/records5/"  # 存放处理后的数据
        self.filter_key = "张三"

        self.partitions = {}

    @staticmethod
    def time2fname(timestamp: int) -> str:
        """时间戳转为文件名"""
        dt = datetime.datetime.fromtimestamp(timestamp//1000)
        timestr = dt.strftime("%Y-%m-%d")
        filename = f"record_{timestr}.txt"
        return filename

    def map_file(self, filename: str) -> list[dict]:
        ret = []
        with open(filename) as f:
            for line in f:
                record = eval(line)
                if record["name"] == self.filter_key:
                    ret.append(record)
        return ret

    @clock.clock
    def map_files(self):
        files = getfiles(self.path1)
        with futures.ProcessPoolExecutor(max_workers=workers()) as executor:
            rets = executor.map(self.map_file, files)

        for ret in rets:
            for record in ret:
                fname = self.time2fname(record["timestamp"])
                self.partitions.setdefault(fname, [])
                self.partitions[fname].append(record)
        print(self.partitions.keys())

    def sort_file(self, args: tuple[str, list]):
        fname = args[0]
        records = args[1]
        filename = self.path2+fname
        # sort
        records = sorted(records, key=lambda record: record["timestamp"])
        # write
        f = open(filename, "w+")
        f.writelines([str(record) for record in records])
        f.close()

    @clock.clock
    def sort_files(self):
        files = [(k, self.partitions[k]) for k in self.partitions]
        with futures.ThreadPoolExecutor(max_workers=workers()) as executor:
            executor.map(self.sort_file, files)


def main():
    convfile = ConvertFile()
    convfile.map_files()
    convfile.sort_files()


if __name__ == '__main__':
    sys.exit(main())
