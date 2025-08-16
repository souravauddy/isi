import numpy
import random


def main() -> None:
    set1 = set([random.randint(20, 30) for _ in range(30)])
    set2 = set([random.randint(20, 30) for _ in range(30)])

    print(set1.isdisjoint(set2))    # built in function

    for value in set1:
        if value in set2:
            print(f"There is a common element {value}")
            return

    print("There is no common element between the two sets")


if __name__ == "__main__":
    main()