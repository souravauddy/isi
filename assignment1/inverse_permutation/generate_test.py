from __future__ import annotations
import random
import time
from typing import (
    Final,
)

MIN_SIZE: Final[int] = int(5)
MAX_SIZE: Final[int] = int(1e2 + 2)

def main() -> int:
    random.seed(time.time())
    permutation_size = int(MIN_SIZE + random.randint(0, int(1e2))) % MAX_SIZE
    permutation = list(range(0, permutation_size))
    random.shuffle(permutation)

    print(permutation_size)
    print(*permutation)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
