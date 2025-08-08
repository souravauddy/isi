from __future__ import annotations
import itertools
import random
import io
from typing import (
    Final,
    Sequence
)


CHARACTERS: Final[Sequence[str]] = [chr(value) for value in itertools.chain(range(48, 58), range(65, 91), range(97, 123))]


def main() -> int:
    number_of_charactes = random.randint(2, 20)
    string_buffer = io.StringIO()

    for _ in range(number_of_charactes):
        character = random.choice(CHARACTERS)
        frequency = random.randint(2, 20)
        string_buffer.write(f"{character}({frequency})")

    print(string_buffer.getvalue())

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
