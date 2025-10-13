from __future__ import annotations
import random
import time
import sys
from typing import (
    Final,
)

MIN_SIZE: Final[int] = int(1e1)
MAX_SIZE: Final[int] = int(2e1)
OPERATIONS: Final[tuple[str, str]] = ("Union", "Connected")

def main() -> int:
    random.seed(time.time())
    filename = sys.argv[1]
    capacity = random.randint(MIN_SIZE, MAX_SIZE)
    number_of_operations = 4 * capacity

    with open(filename, "w") as output_file:
        print(capacity, file=output_file)

        for _ in range(number_of_operations):
            chonsen_operation = OPERATIONS[random.randint(0, 1)]
            first = random.randint(1, capacity)
            second = random.randint(1, capacity)

            print(chonsen_operation, first, second, file=output_file)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
