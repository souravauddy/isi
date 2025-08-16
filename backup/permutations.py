from __future__ import annotations
import collections
import functools


@functools.cache
def factorial(N: int) -> int:
    """Recursively computes the factorial of the given number, and uses functools.cache to cache the computed factorials.

    Args:
        N (int): given number.

    Returns:
        int: factorial of the given number.
    """

    if N <= 1:
        return 1
    
    return N * factorial(N - 1)


def permutations(word: str) -> int:
    """Returns the number of permutations of the word.

    Args:
        word (str): input word

    Returns:
        int: the number of permutations of the given word.
    """

    frequency = collections.defaultdict(int)

    for character in word:
        frequency[character] += 1

    number_of_permutations = factorial(len(word))

    for value in frequency.values():
        number_of_permutations //= factorial(value)

    return int(number_of_permutations)


def main() -> int:
    print(*[permutations(word) for word in input().split()])

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
