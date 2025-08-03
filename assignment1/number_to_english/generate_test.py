from __future__ import annotations
import random
import time

def main() -> int:
    random.seed(time.time())
    numbers = list(range(0, int(1e6)))
    print(random.choice(numbers))

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
