from __future__ import annotations
import math
from typing import (
    Final,
)


def sqrt(number: float, EPSILON: float = float(1e-6)) -> float:
    """Returns the square root of the argument using the babilonian method

    Args:
        number (float): number can be a 'int' or a 'float'.
        EPSILON (float, optional): The digits of precision that is requird (by defualt provides 6 digits of precision). Defaults to float(1e-6).

    Returns:
        float: the computed square root
    """

    root = number / 2

    while True:
        previous = root
        root = (root + number / root) / 2

        if math.fabs(root - previous) < EPSILON:
            break

    return root


def main() -> int:
    number = int(input())
    print(sqrt(number))

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
