"""
Always run in iteractive mode.
This contains functions for quick solutions
"""

from __future__ import annotations
from typing import NoReturn
import numpy as np
from math import (
    lcm,
    gcd,
)


def largest_number_leaving_same_remainder(*numbers: int) -> int:
    maximum = max(numbers)
    numbers = np.array(numbers)
    answer = None

    def all_same(*numbers: int) -> bool:
        first = numbers[0]

        for number in numbers:
            if number != first:
                return False
        return True

    for divisor in range(1, maximum + 1):
        if all_same(*list(numbers % divisor)):
            answer = divisor

    assert answer is not None
    return answer


def sum_of_digits(number: int) -> int:
    sum = 0

    while number > 0:
        number, digit = divmod(number, 10)
        sum += digit

    return sum


def greatest_number_of_k_digits(*numbers, k: int) -> int | NoReturn:
    numbers = np.array(numbers)
    start = 10 ** (k - 1)
    end = 10 ** k
    answer = None

    print(start, end)

    def all_zeros(*numbers: int) -> int:
        for number in numbers:
            if number:
                return False
        return True if numbers else False
    
    for number in range(start, end):
        remainders = []

        for x in numbers:
            remainders.append(number % x)

        if all_zeros(*remainders):
            answer = number

    assert answer is not None
    return answer
