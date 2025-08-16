from __future__ import annotations
from math import lcm, sqrt
from typing import Final


LIMIT: Final[int] = int(10 ** 10)


def prime(number: int) -> bool:
    for factor in range(2, int(sqrt(number) + 1)):
        if number % factor == 0:
            return False
        
    return number >= 2


def main() -> int:
    numbers = [int(number) for number in input().split()]
    numbers.sort()
    numbers_lcm = lcm(*numbers[1:])
    goal = numbers_lcm + numbers[0]

    try:
        if not prime(goal) or (goal % numbers[0] == numbers[0]) or goal >= LIMIT:
            print("None")
            return 0
    except Exception as exception:
        print(f"Something is wrong in the input, and the exception is {exception}")

    print(goal)
        
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
