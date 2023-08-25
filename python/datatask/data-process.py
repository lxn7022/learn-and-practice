#!/usr/bin/env python3

"""
data-process.py is the CLI utility to process unzipped records files to get specific user posts
./data-process.py -o output -u 'zhangsan' -p parrallel inputDirectory

doc:【金山文档】 https://kdocs.cn/l/cmGIakxCDEh7
"""

import argparse
import os
import sys
import time
from datetime import datetime
from pytz import utc
from concurrent import futures
import json
import time
import pprint

pp = pprint.PrettyPrinter(indent=2)


class DataTask:
    def __init__(self, **kwargs):
        self.verbose = kwargs['verbose']
        self.input = kwargs['input']
        self.output = kwargs['output']
        self.user = kwargs['user']
        self.mapperCount = kwargs['mappers']
        self.reducerCount = kwargs['reducers']

        self.partitions = {}
        self.reduceBuf = []

    def get_input_files(self):
        inputFiles = []
        for f in os.listdir(self.input):
            if 'record_' in f:
                inputFiles.append(f)
        return sorted(inputFiles)

    def run_each_mapper(self, f):
        outs = []
        with open(self.input + '/' + f, 'r') as fd:
            for line in fd.readlines():
                r = json.loads(line)
                if r['name'] == self.user:
                    outs.append((int(r['timestamp']), line))
        return outs

    def getPartitionKey(self, milli):
        return datetime.fromtimestamp(milli//1000, tz=utc).strftime('%Y-%m-%d')

    def getPartitionBuf(self, key):
        if key in self.partitions:
            return self.reduceBuf[self.partitions[key]]
        else:
            self.partitions[key] = len(self.reduceBuf)
            self.reduceBuf.append([])
            return self.reduceBuf[-1]

    def run_mappers(self):
        # 1. run mapper
        startMapperTS = time.time()

        files = self.get_input_files()
        with futures.ProcessPoolExecutor(max_workers=self.mapperCount) as executor:
            filtered = executor.map(self.run_each_mapper, files)

        endMapperTS = time.time()
        if self.verbose:
            sys.stderr.write("mapper[%d] consumes [%d]ms\n" %
                             (self.mapperCount, int((endMapperTS-startMapperTS)*1000)))

        # 2. partition mapper
        for outs in filtered:
            for record in outs:
                key = self.getPartitionKey(record[0])
                buf = self.getPartitionBuf(key)
                buf.append(record)

        endPartitionTS = time.time()
        if self.verbose:
            sys.stderr.write("partition consumes [%d]ms\n" %
                             int((endPartitionTS-endMapperTS)*1000))

    def run_each_reducer(self, key):
        buf = self.getPartitionBuf(key)
        # 1. sort by sortKey
        ordered = map(lambda r: r[1], sorted(buf, key=lambda r: r[0]))
        # 2. dump results
        with open(self.output + '/' + key + '.txt', 'w') as fd:
            fd.writelines(ordered)

    def run_reducers(self):
        startReducerTS = time.time()

        keys = sorted(self.partitions.keys())
        with futures.ThreadPoolExecutor(max_workers=self.reducerCount) as executor:
            executor.map(self.run_each_reducer, keys)

        endReducerTS = time.time()
        if self.verbose:
            sys.stderr.write("reducer[%d] consumes [%d]ms\n" %
                             (self.reducerCount, int((endReducerTS-startReducerTS)*1000)))

    def run(self):
        startTS = time.time()

        self.run_mappers()

        self.run_reducers()

        endTS = time.time()
        if self.verbose:
            sys.stderr.write("mapper[%d] reducer[%d] total [%d]ms\n" %
                             (self.mapperCount, self.reducerCount, int((endTS-startTS)*1000)))


class CustomArgParseFormatter(
        argparse.ArgumentDefaultsHelpFormatter,
        argparse.RawDescriptionHelpFormatter):
    pass


def main():
    description = __doc__.format()
    parser = argparse.ArgumentParser(description=description,
                                     formatter_class=CustomArgParseFormatter)

    parser.add_argument('input',
                        help='The path of input folder')

    parser.add_argument('-u', '--user', default='张三', help='张三|李四')

    parser.add_argument('-m', '--mappers', default=0, type=int,
                        help='the parallel processors of mappers')

    parser.add_argument('-r', '--reducers', default=0, type=int,
                        help='the parallel processors of reducers')

    parser.add_argument('-o', '--output', default='output', required=False,
                        help='The path of output')

    parser.add_argument('-v', '--verbose', required=False, default=False,
                        action='store_true', help='print info')

    args = parser.parse_args()
    inputFolder = args.input

    if not os.path.exists(args.input):
        sys.stderr.write('%s is not existed.\n' % args.input)
        return 1

    if os.path.exists(args.output):
        sys.stderr.write('[%s] is existed. please remove the output directory first\n'
                         % args.output)
        return 1

    os.mkdir(args.output)
    mappers = os.cpu_count() if args.mappers < 1 else args.mappers
    reducers = 1 if args.reducers < 1 else args.reducers
    task = DataTask(input=args.input, output=args.output,
                    mappers=mappers, reducers=reducers, user=args.user, verbose=args.verbose)
    task.run()
    return 0


if __name__ == '__main__':
    sys.exit(main())
