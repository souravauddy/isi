from __future__ import annotations
import random
import time


def main() -> int:
    random.seed(time.time())
    p, q = random.randint(2, 2000000), random.randint(2, 2000000)
    print(p, q)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
