from __future__ import annotations
import inspect
import random
import collections
import functools
from typing import (
    MutableMapping,
    Sequence,
    MutableSequence,
    Generic,
    TypeVar,
    Mapping,
    NoReturn,
    ParamSpec,
    Iterable,
    Callable,
)
from types import FrameType


TKey = TypeVar("TKey")
TValue = TypeVar("TValue")
TReturn = TypeVar("TReturn")
Parameters = ParamSpec("Parameters")


def decorator(callable: Callable[Parameters, TReturn]) -> Callable[Parameters, TReturn]:
    @functools.wraps(callable)
    def inner(*args: Parameters.args, **kwargs: Parameters.kwargs) -> TReturn:
        return_value = callable(*args, **kwargs)
        return return_value
    
    return inner



class FrozenDictionary(Generic[TKey, TValue]):
    def __init__(self, dictionary: Mapping[TKey, TValue]) -> None:
        self._dictionary = dictionary
        
    def __getitem__(self, key: TKey) -> TValue:
        return self._dictionary[key]
    
    def keys(self) -> Iterable[TKey]:
        return self._dictionary.keys()
    
    def values(self) -> Iterable[TValue]:
        return self._dictionary.values()
    
    def __contains__(self, key: TKey) -> bool:
        return key in self._dictionary
    
    def get(self, key: TKey, default: TValue | None = None) -> TValue | None:
        return self._dictionary.get(key, default)


def check_variance(iterable: MutableSequence[int]) -> None:    
    frame = inspect.currentframe()

    if isinstance(frame, FrameType):
        print(frame.f_back)
    else:
        assert frame is None, "NoneType returned cannot get the current frame"


def main() -> int:
    items = random.sample(population=range(20, 500000), k=50000)
    items.extend(random.sample(population=range(20, 500), k=100))

    builtin_dictionary_order = {}

    for item in items:
        if item not in builtin_dictionary_order:
            builtin_dictionary_order[item] = 1
        else:
            builtin_dictionary_order[item] += 1

    collections_defaultdict_order: collections.defaultdict = collections.defaultdict(int)

    for item in items:
        collections_defaultdict_order[item] += 1

    same_order = True

    for item1, item2 in zip(builtin_dictionary_order, collections_defaultdict_order):
        if item1 != item2:
            same_order = False
            break
    
    if same_order:
        "no break, this code only runs if the for loop completely completes it's iteration"
        print("All same order")

    return 0


if __name__ == '__main__':
    raise SystemExit(main())
