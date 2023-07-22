#!/usr/bin/env python
# encoding: utf-8
# Author: xnliu
# Date: 2023-07
# Desc: 举例说明class类中的三类不同类型的方法
#


import abc


class DemoClass:
    def __init__(self):
        print("这里测试说明class类中的四个不同类型的方法\n")

    def normal_method(self, *args, **kwargs):
        print("这个是普通实例方法，需要初始化实例之后调用")

    @staticmethod
    def static_method(a, b):
        print("这是类的静态方法(@staticmethod): ", a + b)

    @classmethod
    def class_method(cls, *args, **kwargs):
        print("这是类的类方法(@classmethod): ", args, kwargs)


def TestDemoClass():
    demo = DemoClass()
    print("通过实例调用类的实例方法: ")
    a = demo.normal_method()
    print("通过实例调用类的静态方法:  ")
    b = demo.static_method(3, 4)
    print("通过实例调用类的类方法: ")
    c = demo.class_method()

    print("------" * 10)
    print("通过类调用的实例方法: DemoClass.normal_method() 会报错")
    print("Error: TypeError: normal_method() missing 1 required positional argument: 'self'")
    # DemoClass.normal_method()
    print("通过类调用类的静态方法:  ")
    DemoClass.static_method(3, 4)
    print("通过类调用类的类方法: ")
    DemoClass.class_method()

# ------------------------------


class Abstract(abc.ABC):
    @abc.abstractmethod
    def fun(self):
        pass


class SubClass(Abstract):
    def fun(self):
        print("From SubClass")

    def f(self):
        print('This is SubClass!')


def TestAbstract():
    try:
        a = Abstract()
    except Exception as e:
        print(e)
        # 实例化报错
        # TypeError: Can't instantiate abstract class Foo with abstract methods fun
    c = SubClass()
    c.fun()
    c.f()


if __name__ == "__main__":
    TestDemoClass()
    TestAbstract()
