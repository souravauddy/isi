import random
from typing import Any, Tuple


class Pair:
    def __init__(self, first: int = 0, second: int = 0) -> None:
        self.first = first
        self.second = second


    def __add__(self, other) -> Any:
        self.first += other.first
        self.second += other.second
        return self


    def __iter__(self) -> int:
        yield self.first
        yield self.second


    def __repr__(self) -> str:
        return self.__str__()


    def __pow__(self, other) -> int:
        return self.first ** other.first + self.second ** other.second


    def __str__(self) -> str:
        return f"{{{self.first}, {self.second}}}"


    def __lt__(self, other) -> bool:
        return self.first < other.first


    def __gt__(self, other) -> bool:
        return self.first > other.first


    def __mul__(self, other) -> Any:
        return Pair(self.first * other.first, self.second * other.second)


def make_list(string):
    List = []

    for character in string:
        List.append(character)

    return List


def main() -> None:
    # strings = ["sourav", "auddy", "name", "India"]
    # List = list(map(make_list, strings))

    one = Pair(20, 30)
    another = Pair(40, 50)
    Tuple = (one, another, one + another)

    print(Tuple)


if __name__ == "__main__":
    main()