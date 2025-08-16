from __future__ import annotations
import itertools
import sys


def main() -> int:
    R, N = int(input()), int(input())
    characters = [chr(i + 97) for i in range(26)]

    for permutation in itertools.permutations(characters, N):
        if R == 1:
            print("".join(permutation))
            break
            
        R -= 1

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
