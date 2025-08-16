from __future__ import annotations
import sys


def main() -> int:
    N = int(input())
    
    print(1 if N == 0 else 2 ** (bin(N)[2:].count('0')))

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
