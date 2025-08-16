from __future__ import annotations
import copy
import sys
from typing import (
    Final,
    final,
)


INF: Final[int] = int(1e9 + 5)


@final
class NoInheritance(object): ...


def main() -> int:
    lines = sys.stdin.readlines()
    N, M = map(int, lines[0].split())
    fortress = [list(map(int, row.split())) for row in lines[1:]]
    
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
