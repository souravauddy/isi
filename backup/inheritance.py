from __future__ import annotations
from collections import Counter
from random import randint as rand
from abc import ABC


class Base(object): 
    pass


class Derived(Base): # DB
    pass


class Third(Derived, Base): # T + (DB + B)
    pass



def main(*args, **kwargs) -> None:
    list_ = ["sourav", (20, 40), 20]
    print(sorted(list_))

    print(*list_)
    exit()

    print((Third.__mro__))
    numbers = [(20, number) for number in input().split()]
    numbers.sort(key=type("_", (tuple, object), {"__lt__": lambda x, y: x[1] < y[1]}))
    print(numbers)


if __name__ == "__main__":         
    main()