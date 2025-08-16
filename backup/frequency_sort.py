from __future__ import annotations
import collections


def main() -> int:
    numbers = list(map(int, input().split()))
    frequency = collections.defaultdict(int)

    for number in numbers:
        frequency[number] += 1

    numbers.sort(
        key=type(
            '_',
            (int,),
            {
                "__lt__": lambda x, y: frequency.get(x) < frequency.get(y)
            }
        ), 
        reverse=True
    )
    
    print(numbers)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
