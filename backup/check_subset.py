from __future__ import annotations
import random


def subset(set1: set[int], set2: set[int]) -> bool:
    for value in set1:
        if value not in set2:
            return False

    return True


def main() -> int:
    set1 = set([random.randint(20, 30) for _ in range(50)])
    set2 = set([random.randint(20, 30) for _ in range(50)])

    print(set1.issubset(set2))
    print(set2.issubset(set1))

    if subset(set1, set2):
        print("set1 is a subset of set2")
    elif subset(set2, set1):
        print("set2 is a subset of set1")
    else:
        print("Not a subset of each other")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
