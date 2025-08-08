from __future__ import annotations
import random
import itertools
import io
from typing import (
    Final,
)


CHARACTERS: Final[tuple[str]] = tuple([chr(value) for value in itertools.chain(range(ord('A'), ord('Z') + 1), range(ord('a'), ord('z') + 1))])


def main() -> int:
    number_of_characters = random.randint(2, 20)
    character_string = io.StringIO()

    for _ in range(number_of_characters):
        character_string.write(random.choice(CHARACTERS))

    print(character_string.getvalue())

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
