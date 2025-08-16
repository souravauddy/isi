from __future__ import annotations
import concurrent.futures
import os
import collections
import sys
import functools
import datetime
from threading import Lock, Semaphore
from typing import (
    Self,
    Final,
    Type,
    TypedDict,
    Unpack,
    final,
    reveal_type,
)


MAXIMUM_WORKERS: Final[int] = max(os.cpu_count(), 4)


# class AnnotateKwargs(TypedDict):
#     first: int
#     second: str


# def func(**kwargs: Unpack[AnnotateKwargs]):
#     pass


# class Generic[Type]:
#     def __init__(self, value: Type) -> None:
#         self.value = value

#     def __call__(self) -> Type:
#         return self.value
    
#     def return_something[T](self, something: T) -> tuple[T, Type]:
#         return something, self.value
    

# def print_something[T](something: int) -> None:
#     print(something)


class SomeType(object):
    def __repr__(self) -> str:
        return "something"


def singleton(cls: type) -> type:
    class Inner(cls):
        _instance = None

        def __new__(cls, *args, **kwargs) -> Inner:
            if cls._instance is None:
                cls._instance = super().__new__(cls, *args, **kwargs)
            return cls._instance
    
    return Inner


@singleton
class Check(object):
    def __init__(self) -> None:
        pass


def main() -> int:
    for value in range(1, 200):
        print(f"{value}")

    import dis
    print(dis.dis(dis.dis))

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
