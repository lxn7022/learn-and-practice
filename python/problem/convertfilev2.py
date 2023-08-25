# coding=utf-8

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
"""

import sys
import memory_profiler
import clock
import pytest
import datetime
import time
import os


def getfiles(dir: str) -> list[str]:
    """获取某个目录下的所有普通文件"""
    res = []
    # Iterate directory
    for path in os.listdir(dir):
        # check if current path is a file
        fname = os.path.join(dir, path)
        if os.path.isfile(fname):
            res.append(fname)
    return res


class ConvertFile:
    def __init__(self) -> None:
        self.path1 = "/data/records/"  # 存放源数据
        self.path2 = "/data/records4/"  # 存放处理后的数据
        self.filter_key = "张三"

    @staticmethod
    def time2fname(timestamp: int) -> str:
        """时间戳转为文件名"""
        dt = datetime.datetime.fromtimestamp(timestamp//1000)
        timestr = dt.strftime("%Y-%m-%d")
        filename = f"record_{timestr}.txt"
        return filename

    @staticmethod
    def readfile(filename: str, filter_key) -> list[dict]:
        f = open(filename)
        buf = f.read()
        f.close()
        lines = buf.split("\n")
        ret = []
        for line in lines:
            if not line:
                continue
            record = eval(line)
            if record["name"] == filter_key:
                ret.append(record)
        return ret

    @staticmethod
    def writefile(lines: list[dict], filename: str):
        buf = "\n".join([str(line) for line in lines])
        f = open(filename, "a+")
        f.write(buf)  # 作为一个整体，一次性写入，提高性能
        f.write("\n")
        f.close()

    @staticmethod
    def _split_lines_to_filedict(lines: list[dict], files: dict[str, list]):
        def getfname(line): return ConvertFile.time2fname(line["timestamp"])
        for line in lines:
            fname = getfname(line)
            if fname in files:
                files[fname].append(line)
            else:
                files[fname] = [line]

    @staticmethod
    def _write_filedict_to_output(files: dict[str, list], filepath: str):
        for filename in files:
            fname = filepath+filename
            ConvertFile.writefile(files[filename], fname)

    @clock.clock
    def map_files(self):
        files = [f"{self.path1}record_{i}.txt" for i in range(0, 1000)]
        lines_of_outfile = {}
        savepoint = [100, 200, 300, 400, 500, 600, 700, 800, 999]
        savepoint_fname = set(
            [f"{self.path1}record_{i}.txt" for i in savepoint])
        for fname in files:
            lines = self.readfile(fname, self.filter_key)
            self._split_lines_to_filedict(lines, lines_of_outfile)
            if fname in savepoint_fname:
                print("savepoint:", fname, " @", datetime.datetime.now())
                self._write_filedict_to_output(lines_of_outfile, self.path2)
                lines_of_outfile = {}  # clean after output

    @staticmethod
    def sortfile(filename):
        lines = []
        with open(filename) as f:
            for line in f:
                if not line:
                    continue
                lines.append(eval(line.strip()))
        # sort
        lines = sorted(lines, key=lambda line: line["timestamp"])
        # write
        f = open(filename, "w+")
        f.writelines([str(line) for line in lines])
        f.close()

    @clock.clock
    def sort_files(self):
        files = getfiles(self.path2)
        print(files)
        for fname in files:
            print("sortfile:", fname, " @", datetime.datetime.now())
            self.sortfile(fname)


def main():
    convfile = ConvertFile()
    convfile.map_files()
    convfile.sort_files()


if __name__ == '__main__':
    sys.exit(main())
