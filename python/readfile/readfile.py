"""
readline:
基于FileSystem.read() 实现 MyFileSystem.readline() 
"""


class FileSystem:
    def __init__(self, filename: str):
        self.filename = filename
        self.file = open(filename)

    def close(self):
        self.file.close()

    def read(self, length):
        return self.file.read(length)


class MyFileSystem:
    def __init__(self, filename):
        self.FileObject = FileSystem(filename)
        self.readlen = 100
        self.harfline = ''
        self.index = 0
        self.lines = []
        self.EOF = False

    def _read(self):
        # 文件结束，直接返回
        if self.EOF:
            return
        # 不空的话，直接返回
        if len(self.lines) != 0:
            return
        # 开始读取，至少读取一行
        buffer = self.harfline
        while True:
            if buf := self.FileObject.read(self.readlen):
                if len(buf) != self.readlen:
                    self.EOF = True
                buffer += buf
            # 至少读到一行
            if buffer.find('\n'):
                break
        # 分割成多行
        self.lines = buffer.split("\n")
        if buffer[-1] != '\n':
            self.harfline = self.lines[-1]
            self.lines = self.lines[:-1]

    def readline(self):
        # 每次进来都触发读取
        self._read()
        # 读完则返回None
        if len(self.lines) == 0:
            return None
        # 生成每一行
        line = self.lines[0]
        self.lines = self.lines[1:]
        return line

    def eof(self):
        return self.EOF


if __name__ == "__main__":
    myfile = MyFileSystem("./readfile.py")
    line = ''
    while not myfile.eof():
        line = myfile.readline()
        print(line)
