from __future__ import annotations

import multiprocessing
import concurrent.futures


def work(limit: int = 0, step: int = 0) -> int:
    return sum(range(0, limit, step))


def main() -> None:
    with concurrent.futures.ProcessPoolExecutor() as executor:
        task = executor.submit(work, 20, 2)
        print(task.result())

if __name__ == '__main__':
    main()
