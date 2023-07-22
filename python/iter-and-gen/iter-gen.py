from collections.abc import Iterator, Iterable


class A(object):
    def __init__(self):
        self.index = -1
        self.a = [1, 2, 3]

    # 必须要返回一个实现了 __next__ 方法的对象，否则后面无法 for 遍历
    # 因为本类自身实现了 __next__，所以通常都是返回 self 对象即可
    def __iter__(self):
        return self

    def __next__(self):
        self.index += 1
        if self.index < len(self.a):
            return self.a[self.index]
        else:
            # 抛异常，for 内部会自动捕获，表示迭代完成
            raise StopIteration("遍历完了")


def TestA():
    cls_a = A()
    print(isinstance(cls_a, Iterable))  # True
    # True  从这里可以看出来同时具有__iter__和__next__的类，是Iterator
    print(isinstance(cls_a, Iterator))
    # True 这里加不加iter()都一样，因为这个类里面的iter也是直接返回自身(self)
    print(isinstance(iter(cls_a), Iterator))

    # 另外补充一点这个a和上面类里面的a是不一样的；这里的用i(任意字母都可以)也能
    for a in cls_a:
        print(a)


def gensquares(N):
    for i in range(N):
        yield i ** 2


def TestGenerator():
    gen = gensquares(10)
    for x in gen:
        print(x)


if __name__ == "__main__":
    TestA()
    TestGenerator()
