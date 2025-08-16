import random
import functools
import os


def generate_fibbonacci():
    a, b = 0, 1

    yield 0
    yield 1

    while True:
        yield a + b
        b = a + b
        a = b - a


def main() -> None:
    N = int(input())
    fibbonacci = generate_fibbonacci()
    square = lambda number : number * number

    List = [square(next(fibbonacci)) for _ in range(N)]

    print(List)


if __name__ == "__main__":
    main()