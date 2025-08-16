from __future__ import annotations
import contextlib
from types import TracebackType
from typing import (
    Any,
    Generator,
    Sequence,
    Type,
    Self,
)


class First(object):
    def __init__(self) -> None:
        print("done")

    def __enter__(self) -> Self:
        print("We have entered into the context manager")
        return self

    def __exit__(self, exception_type: Type[Exception] | None, exception_value: Exception | None, exception_traceback: TracebackType | None) -> None:
        print(type(exception_type))
        print(type(exception_traceback))
        print(type(exception_value))
        print("done")


def function_generator() -> Generator[int, None, None]:
    print("comes here")
    yield 20
    yield 49
    yield 50
    yield 100
    print("done")


@contextlib.contextmanager
def context_manager() -> Generator[Sequence[int], None, None]:
    print("enter")
    yield range(20)
    print("exit")


def main() -> int:
    with context_manager() as series:
        print(type(series))

        for item in series:
            print(item)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
