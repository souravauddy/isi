from __future__ import annotations
import collections
import numpy as np
import sys
from typing import Final


OPTIONS: tuple[str, str] = ("one", "one's")


def main() -> int:
    string = sys.stdin.readlines()[0]
    frequency = collections.defaultdict(int)

    for character in string:
        frequency[character] += 1

    for key, value in frequency.items():
        print(f"{key}: {value} {OPTIONS[bool(value - 1)]}")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
