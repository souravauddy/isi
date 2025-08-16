from __future__ import annotations
from random import randrange
from typing import Generator, Any, Iterator, Generic, TypeVar, final
import dataclasses
import sys


def check_reference(numbers: list[int]) -> None:
    numbers.clear()
    numbers.extend([2, 4, 5])


T = TypeVar("T")

@final
class ListNode(Generic[T]):
    def __init__(self, data: T, next: ListNode | None = None) -> None:
        self.data = data
        self.next = next

    def __repr__(self) -> str:
        return f"<ListNode object at {id(self)} with value {self.data} and next {id(self.next)}>"


class List(object):
    def __init__(self) -> None:
        self.node = None
        self.head = None
        self.length = 0

    def add_node(self, value: int) -> None:
        new_node = ListNode(value, None)
        self.length += 1

        if self.node is None:
            self.node = new_node
            self.head = new_node
        else:
            self.node.next = new_node
            self.node = self.node.next

    def __len__(self) -> int:
        return self.length

    def __iter__(self) -> Iterator:
        iterator = self.head

        while iterator is not None:
            yield iterator
            iterator = iterator.next

    def __repr__(self) -> str:
        return f"{super().__class__} object"


@dataclasses.dataclass
class First(object):
    x: int = 0
    y: int = 0
    z: int = 0


class Second(First):
    pass


class Third(Second, First):
    pass


class Fourth(Third, Second, First):
    pass


def keyword_arguments(**kwargs: dict[str, Any]) -> None:
    print(type(kwargs))
    print(kwargs.keys())


def main() -> int:

    return 0


if __name__ == '__main__':
    main()
