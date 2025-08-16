from __future__ import annotations
import numpy as np
import timeit


MAX_SIZE = int(18)
factorial = np.array([1 for _ in range(MAX_SIZE + 1)], dtype=np.int64)


def preprocess() -> None:
    for i in range(1, MAX_SIZE + 1):
        factorial[i] = i * factorial[i - 1]


def catalan_number(N: int) -> int:
    return factorial[2 * N] / (factorial[N + 1] * factorial[N])


def build_list(n: int = 10**4) -> list[str]:
    return ['\t'] * n


def build_list_using_comprehension(n: int = 10**4) -> list[str]:
    return ['\n' for _ in range(n)]


def main() -> int:

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
