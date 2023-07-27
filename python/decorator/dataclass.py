from dataclasses import dataclass, field, asdict, astuple
from typing import List, Any
import copy
import pytest
from dataclasses import dataclass


class Student:
    def __init__(self, name, age, score):
        self.name = name
        self.age = age
        self.score = score

    def __repr__(self) -> str:
        return f"Student({self.name},{self.age},{self.score})"

    def __lt__(self, other) -> bool:
        return self.score < other.score


@dataclass
class Book:
    name: str
    author: str
    # extend: Any = 'hello world'   # 扩展字段 仅做记录
    publication: str = field(metadata={"description": "出版日期"})
    num: int = field(default=1, metadata={"description": "数量"})
    price: float = field(default=0.0, metadata={'currency': 'RMB'})
    category: List[str] = field(default_factory=list, repr=False, metadata={
                                "description": "图书类别"})

    def __post_init__(self):
        # 方法来确保书名的每个单词的首字母都是大写的
        self.name = self.name.title()
        self.title = self.name.upper()

    def is_expensive(self):
        # 检查一本书是否价格高于100
        return self.price > 30.0

    def __lt__(self, other):
        return self.price < other.price


def test_Student():
    s1 = Student("alice", 20, 98)
    s2 = Student("bob", 21, 92)
    s3 = Student("nike", 21, 95)
    students = [s1, s2, s3]
    # print
    print("\n")
    print(students)
    students.sort()
    print(students)


def test_Book():
    book1 = Book(name="Under the sky", author="sanxian", price=47.82,
                 publication="2022-11-07", category=['武侠', '古风'])
    book2 = Book(**{"name": "the three body problem", "author": "刘慈欣",
                 "price": 37.82, "publication": "2022-12-23", "category": ['科幻', '悬疑']})
    books = [book1, book2]
    print(book1, book2)
    print(books)
    print(sorted(books))


if __name__ == '__main__':
    pytest.main(["-s", "-v", "dataclass.py"])
