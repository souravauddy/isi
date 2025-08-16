import functools
import sys


sys.setrecursionlimit(10**7)


@functools.lru_cache(maxsize=None)
def fibonacci(number):
    return number if number < 2 else fibonacci(number - 1) + fibonacci(number - 2)


def main() -> None:
    term = int(input())
    print(fibonacci(term))


if __name__ == "__main__":
    main()