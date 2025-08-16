from __future__ import annotations
from typing import overload
import functools
from typing import Any, Generator
from math import pi as PI


# class New(object):
#     def __new__(classname, *args, **kwargs) -> type:
#         print("new called")
#         return super().__new__(classname)

#     def __init__(self) -> None:
#         print("init called")

@functools.total_ordering
class Stack(object):
    __slots__ = ('stack', 'index')

    def __init__(self) -> None:
        self.stack: list[Any] = []
        self.index = 0

    def __len__(self) -> int:
        return len(self.stack)

    def __repr__(self) -> str:
        return f"{self.stack!r}"

    def __iter__(self) -> Generator[Any, None, None]:
        return (item for item in self.stack)

    def __next__(self) -> Any | None:
        if self.index < len(self):
            item = self.stack[self.index]
            self.index += 1
            return item

        raise StopIteration

    def __eq__(self, other: object) -> bool:
        if isinstance(other, Stack):
            return self.stack == other.stack
        return NotImplemented

    def __lt__(self, other: object) -> bool:
        if isinstance(other, Stack):
            return self.stack < other.stack
        return NotImplemented

    def push(self, item: Any) -> None:
        self.stack.append(item)

    def pop(self) -> Any:
        try:
            value = self.stack[-1]
            del self.stack[-1]
            return value
        except Exception as exception:
            print(f"The stack is empty {exception}")

    def top(self) -> Any:
        try:
            return self.stack[-1]
        except IndexError:
            print("Array index is out of bounds, the stack is empty")
        except Exception as exception:
            print(f"The stack is not empty, the issue is {exception}")

    def empty(self) -> bool:
        return self.stack is []


class Sentence(object):
    @overload
    def __init__(self: Sentence) -> None: ...

    @overload
    def __init__(self: Sentence, sentence: str) -> None: ...

    def __init__(self, sentence=None) -> None:
        self.sentence = sentence

    def __iter__(self) -> Generator[str, None, None]:
        for word in self.sentence.split():
            yield word


class Calculator(object):
    @staticmethod
    def add(a: int, b: int) -> int:
        return int(a + b)

    @staticmethod
    def subtract(a: int, b: int) -> int:
        return int(abs(a - b))

    @staticmethod
    def multiply(a: int, b: int) -> int:
        return int(a * b)

    @staticmethod
    def divide(a: int, b: int) -> int:
        return int(a // b)


class Volume(object):
    _shape = "None"

    @classmethod
    def shape(cls):
        return cls._shape

    @staticmethod
    def sphere(radius: int) -> float:
        Volume._shape = "sphere"
        return (4 * PI * radius ** 3) / 3

    @staticmethod
    def cylinder(radius: int, height: int) -> float:
        Volume._shape = "cylinder"
        return PI * radius * radius * height

    @staticmethod
    def cube(side: int) -> int:
        Volume._shape = "cube"
        return side ** 3


def main() -> None:
    stack = Stack()
    stack.push(20)
    stack.push(100)
    print(stack)

    for item in stack:
        print(item)

    print(Volume.sphere(radius=20))
    print(Volume.cylinder(radius=20, height=40))
    print(Volume.cube(side=100))
    print(Volume.shape)

    # for word in sentence:
    #     print(word)

    # for word in sentence:
    #     print(word)

    # list_ = [(20, number) for number in range(200)]

    # def compare(self, other) -> bool:
    #     return self[1] < other[1]

    # list_ = sorted(list_, key=type('Compare', (list,), {
    #     "__lt__": compare,
    # }))

    # print(list_)

    # for item in range(20):
    #     stack.push(item)

    # print(*stack)

    # while not stack.empty():
    #     assert stack.top() is not None, "The stack is empty Assertion error"
    #     print(stack.top())
    #     stack.pop()


if __name__ == "__main__":
    main()
