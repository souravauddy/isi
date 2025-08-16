from __future__ import annotations
import concurrent.futures
import concurrent.futures._base
import time
import gc


def work() -> None:
    sum_ = sum(range(20000000000))
    print("This is finished")
    return sum_

def main() -> int:
    with concurrent.futures.ThreadPoolExecutor() as executor:
        thread1 = executor.submit(work)
        thread2 = executor.submit(work)

        print(thread1.result())
        print(thread2.result())

    return 0


if __name__ == '__main__':
    raise SystemExit(main())
