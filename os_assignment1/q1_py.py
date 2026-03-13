from __future__ import annotations
import concurrent.futures
from concurrent.futures import Future
from typing import (
    Final,
    Sequence,
)


def task(row: str) -> int:
    return sum((ord(value) - ord('0') for value in row))


def main() -> int:
    N, _ = list(map(int, input().split()))
    matrix = []

    for _ in range(N):
        matrix.append(input())

    with concurrent.futures.ProcessPoolExecutor(max_workers=N) as executor:
        futures: list[Future[int]] = []
        results = []

        for i in range(N):
            futures.append(executor.submit(task, matrix[i]))

        for future in futures:
            results.append(future.result())

        print(1 + results.index(max(results)))

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
