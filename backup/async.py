from __future__ import annotations
import functools
import asyncio
from typing import (
    Coroutine,
    Any,
)

from numpy import isin


async def function(text: str = "sourav") -> None:
    print(text)
    task = asyncio.create_task(print_text(text="sourav auddy"))
    await asyncio.sleep(5)
    print("done")
    await task


async def print_text(text: str) -> None:
    print(text)
    await asyncio.sleep(8)
    print("This is done here")


@functools.total_ordering
class Check(object):
    def __init__(self, x: int = 0, y: int = 0, z: int = 0) -> None:
        self.x, self.y, self.z = x, y, z

    def __lt__(self, other: object) -> bool:
        if isinstance(other, Check):
            return self.x < other.x
        return NotImplemented

    def __repr__(self) -> str:
        return f"<{self.__class__} ({self.x=}, {self.y=}, {self.z=}) at {id(self)}>"

    def __str__(self) -> str:
        return f"{self!r}"

    def __int__(self) -> int:
        return self.sum

    @property
    def sum(self) -> int:
        return self.x + self.y + self.z


def main() -> int:
    asyncio.run(print_text("sourav auddy"))

    return 0


if __name__ == '__main__':
    raise SystemExit(main())
