from __future__ import annotations
import functools
import inspect
import copy
import random
import sys
from typing import NoReturn


sys.setrecursionlimit(10**7)


@functools.total_ordering
class Check(object):
    def __init__(self: Check, name: str, number: int) -> None:
        self.name = name
        self.number = number

    
    def __hash__(self: Check) -> int:
        return hash(hash(self.name) + hash(self.number))

    
    def __str__(self: Check) -> str:
        return f"{{name = {self.name}, number = {self.number}}}"


    def __repr__(self: Check) -> str:
        return str(self)


    def __gt__(self: Check, other: Check) -> bool:
        return self.number > other.number


    def __eq__(self: Check, other: Check) -> bool:
        return self.number == other.number  

    @property
    def get_name(self: Check) -> str:
        return self.name


    @property
    def set_name(self: Check) -> Check:
        return self


    @set_name.setter    
    def set_name(self: Check, **kwargs) -> None:
        self.name = kwargs[self.name]
        self.number = kwargs[str(self.number)]


    def __add__(self: Check, other: Check) -> Check:
        result = Check("sourav", 20)
        result.name = f"{self.name} {other.name}"
        result.number = self.number + other.number
        return result


    def __iadd__(self: Check, other: Check) -> Check:
        self = self + other
        return self


def palindrome(number: int) -> bool:
    another = number
    reverse = 0

    while number > 0:
        reverse = reverse * 10 + (number % 10)
        number //= 10

    return another == reverse


def main() -> None:
    factorial = lambda number : number * factorial(number - 1) if number > 1 else 1

    N = int(input())
    print(tuple(range(N)))
    exit()

    N = int(input())
    a = 0; b = 1

    @functools.lru_cache(maxsize=None)
    def fibonacci(N: int) -> None:
        if N < 2:
            return N
        
        fibonacci(N - 1) + fibonacci(N - 2)

    fibonacci(N)
    print(fibonacci.cache_info())


if __name__ == "__main__":
    main()