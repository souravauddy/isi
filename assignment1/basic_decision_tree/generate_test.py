from __future__ import annotations
import random
import time
import os


def main() -> int:
    random.seed(time.time())
    digits = "0123456789"
    print(''.join(random.sample(digits, 9)))

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
