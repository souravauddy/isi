from __future__ import annotations
import io
import string
from typing import (
	Any,
	NoReturn,
	TypeVar,
	Protocol,
	Self,
	Sequence,
)
from collections.abc import Sequence

from matplotlib import streamplot


class SupportsMultiplicationWithInt(Protocol):
	def __mul__(self, n: int) -> Self: ...


class SupportsIndex(Protocol):
	def __index__(self) -> int: ...


T = TypeVar("T", bound=SupportsMultiplicationWithInt)
TIndex = TypeVar("TIndex", bound=SupportsIndex)
T1 = TypeVar("T1")


class Check(object):
	def __call_me__(self) -> None:
		print("This can be called with just an outed method")

	
def call_me(instance: Any) -> None | NoReturn:
	try:
		return instance.__call_me__()
	except AttributeError as exeception:
		print("don't send a non-valid instance")
		raise


def multiply(x: T, n: int) -> T:
	return x * n


def return_value(sequence: Sequence[T1], index: int) -> T1:
	return sequence[index]


def check(*args: int) -> int:
	return args[0]


def main() -> int:
	stringstream = io.StringIO()
	items = [20, 40, 50, 100]

	for item in items:
		print(item, file=stringstream)

	print(stringstream.getvalue())

	return 0


if __name__ == "__main__":
	raise SystemExit(main())
