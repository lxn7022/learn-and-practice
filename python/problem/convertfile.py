# coding=utf-8

"""
说明
1. 有 1000 个 20M ⼤⼩的⽂本⽂件，⽂件中每⾏数据的格式固定为: 
{"name": "xx","timestamp": xx, "content": "xx"}
name: 字符串， ⻓度为 32 个字节以内
timestamp: 毫秒级时间戳
content: 字符串，⻓度为 1024 个字节以内 
⽂件地址: https://mc-public-resource-cn.s3.cn-north-1.amazonaws.com.cn/records.zip

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


def time2fname(timestamp: int) -> str:
    """时间戳转为文件名"""
    dt = datetime.datetime.fromtimestamp(timestamp//1000)
    timestr = dt.strftime("%Y-%m-%d")
    filename = f"record_{timestr}.txt"
    return filename


def readfile(filename: str) -> list[dict]:
    f = open(filename)
    buf = f.read()
    f.close()
    lines = buf.split("\n")
    lines = [eval(line) for line in lines if line]
    return lines


def writefile(lines: list[dict], filename: str):
    buf = "\n".join([str(line) for line in lines])
    f = open(filename, "a+")
    f.write(buf)  # 作为一个整体，一次性写入，提高性能
    f.write("\n")
    f.close()


def split_lines_to_filedict(lines: list[dict], files: dict[str, list]):
    def getfname(line): return time2fname(line["timestamp"])
    for line in lines:
        fname = getfname(line)
        if fname in files:
            files[fname].append(line)
        else:
            files[fname] = [line]


def write_filedict_to_output(files: dict[str, list], filepath: str):
    for filename in files:
        fname = filepath+filename
        writefile(files[filename], fname)


def mapfiles():
    path = "/data/records/"
    files = [f"record_{i}.txt" for i in range(0, 1000)]
    out_path = "/data/records2/"
    lines_of_outfile = {}
    savepoint = [100, 200, 300, 400, 500, 600, 700, 800, 999]
    savepoint_fname = set([f"record_{i}.txt" for i in savepoint])
    for filename in files:
        fname = path+filename
        lines = readfile(fname)
        split_lines_to_filedict(lines, lines_of_outfile)
        if filename in savepoint_fname:
            print("savepoint:", filename, " @", datetime.datetime.now())
            write_filedict_to_output(lines_of_outfile, out_path)
            lines_of_outfile = {}  # clean after output


@memory_profiler.profile
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


def sortfiles():
    path = "/data/records2/"
    files = getfiles(path)
    print(files)
    for fname in files:
        print("sortfile:", fname, " @", datetime.datetime.now())
        sortfile(fname)


def test_time2fname():
    tms = [1649622588005, 1649738014676, 1649481357214]
    print()
    for t in tms:
        fname = time2fname(t)
        print(fname)


def test_readfile():
    path = "/data/records/"
    fname = path + "record_0.txt"
    lines = readfile(fname)
    print("\n", fname, ":", len(lines))
    print("\n", lines[:5])


def test_writefile():
    path = "/data/records/"
    fname = path + "record_0.txt"
    output = "test_record_0.txt"
    lines = readfile(fname)
    writefile(lines, output)


@clock.clock
def test_mapfiles():
    mapfiles()


@clock.clock
def test_sortfiles():
    sortfiles()


if __name__ == '__main__':
    pytest.main(["-v", "-s", "convertfile.py"])
