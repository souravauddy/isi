from __future__ import annotations
from ast import Call
import multiprocessing
import inspect
import functools
import random
import contextlib
import sys
import numpy as np
from types import FrameType, TracebackType
from typing import (
    Any, 
    Generator, 
    Callable,
    Iterable,
    NoReturn, 
    ParamSpec, 
    Self,
    TypeVar,
    Union,
    assert_never, 
    overload,
    Type,
    final,
    Final,
    assert_type,
)


CPU_CORES_COUNT: Final[int] = multiprocessing.cpu_count()


@functools.total_ordering
class Edge(object):
    def __init__(self, source: int = random.randint(20, 30), destination=random.randint(20, 30), weight=sys.maxsize) -> None:
        self.source = source
        self.destination = destination
        self.weight = weight
        self.array = [-1 for _ in range(30)]

    def __eq__(self, other: object) -> bool:
        if isinstance(other, Edge):
            return self.weight == other.weight
        return NotImplemented

    def __lt__(self, other: object) -> bool:
        if isinstance(other, Edge):
            return self.weight < other.weight
        return NotImplemented

    def __str__(self) -> str:
        return f"source = {self.source}, destination = {self.destination}, weight = {self.weight}"

    def __repr__(self) -> str:
        return f"{self!s}"

    def __add__(self, other: object) -> Any:
        if isinstance(other, Edge):
            result = Edge()
            result.source = self.source
            result.destination = self.destination
            result.weight = self.weight + other.weight
            return result
        return NotImplemented

    def __radd__(self: object, other: Edge) -> Any:
        if isinstance(self, Edge):
            return other + self
        return NotImplemented

    def __len__(self) -> int:
        return self.weight

    def __getitem__(self, index: int) -> Any:
        return self.array[index]

    def __setitem__(self, index: int, value: Any) -> Any:
        self.array[index] = value

    def __delitem__(self, index: int) -> None | NoReturn:
        if isinstance(self, Array):
            del self.numbers[index]
        raise NotImplementedError()


class Array(object):
    @overload
    def __init__(self, size: int) -> None: ...
    @overload
    def __init__(self, numbers: list) -> None: ...

    def __init__(self, argument: int | list) -> None:
        if isinstance(argument, int):
            self.numbers = [0 for _ in range(argument)]
        elif isinstance(argument, list):
            self.numbers = argument.copy()
        else:
            raise ValueError("Pass either int or list")
        return None
        # self.numbers = [0 for _ in range(args)] if isinstance(args, int) else args.copy()

    def __repr__(self) -> str:
        return f"{self.numbers!r}"

    def __len__(self) -> int:
        return len(self.numbers)

    @overload
    def __add__(self, other: Array) -> Array: ...

    @overload
    def __add__(self, other: int) -> Array: ...

    def __add__(self, other: object) -> Array:  # implemented some degree of broadcasting
        if isinstance(other, Array):
            assert (len(self) == len(other))
            result = Array(len(other))

            for index, _ in enumerate(self.numbers):
                result[index] = self[index] + other[index]

            return result
        elif isinstance(other, int):
            result = Array(self.numbers)

            for index, _ in enumerate(self.numbers):
                result[index] = self[index] + other

            return result
        return NotImplemented

    def __getitem__(self, index: int) -> int:
        return self.numbers[index]

    def __setitem__(self, index: int, value: int) -> int:
        self.numbers[index] = value
        return self.numbers[index]

    def __enter__(self) -> Self:
        return self

    def __exit__(self, exception_type: type | None, exception_value: Exception | None, exception_traceback: TracebackType | None) -> None:
        print(f"{exception_type}, {exception_traceback}, {exception_value}")


@functools.lru_cache(maxsize=None)
def fibonacci(number: int) -> int:
    return number if number < 2 else fibonacci(number - 1) + fibonacci(number - 2)


@contextlib.contextmanager
def context_generator_function() -> Generator[Any, None, None]:
    print("This is the entry code")
    yield fibonacci
    print("This is the exit code")


class decorator:
    def __init__(self, function: Callable) -> None:
        self.function = function
        functools.update_wrapper(self, function)

    def __call__(self, *args: Any, **kwargs: Any) -> Any:
        print("called from here")
        return self.function(*args, **kwargs)


class UseProperty(object):
    def __init__(self, length: int, breadth: int) -> None:
        self.length = length
        self.breadth = breadth

    @property
    def area(self) -> int:
        return self.length * self.breadth


@final
class Descriptor(object):
    def __set_name__(self, owner: object, name: str) -> None:
        self.attribute_name = name

    def __get__(self, object: object, object_type: type | None = None) -> Union[Any, NoReturn]:
        if object is None:
            raise AttributeError("You should not access the class version of the variables.")
        if self.attribute_name.startswith('_'):
            raise NotImplementedError("This has not been Implented")
        return getattr(object, self.attribute_name)

    def __set__(self, object: Any, value: Any) -> None:
        setattr(object, self.attribute_name, value)


@final
class PrivateAttribute(object):
    def __set_name__(self, owner: object, name: str) -> None:
        self.attribute_name = name
        self._class = owner

    def __get__(self, object: object, object_type: type | None = None) -> Any | NoReturn:
        if object is None:
            raise AttributeError()

        current_frame = inspect.currentframe()

        if isinstance(current_frame, FrameType):
            callers_frame = current_frame.f_back
            assert_never(callers_frame, None)
            local_variables = callers_frame.f_locals

        if self.attribute_name.startswith('_'):
            if 'self' not in local_variables:
                raise NotImplementedError("This has not been implemented")
            if self._class != type(local_variables.get('self')):
                raise AttributeError("The attribute cannot be accessed outside the class")

        return getattr(object, self.attribute_name)

    def __set__(self, object: Any, value: Any) -> None | NoReturn:
        current_frame = inspect.currentframe()
        
        if isinstance(current_frame, FrameType):
            callers_frame = current_frame.f_back
            local_varibles = callers_frame.f_locals

        if self.attribute_name.startswith('_'):
            if 'self' in local_varibles:
                if self._class == type(local_varibles.get('self')):
                    setattr(object, self.attribute_name, value)
                    return

            raise AttributeError()
        
        setattr(object, self.attribute_name, value)


@final
class NonDataDescriptor(object):
    def __set_name__(self, owner: object, name: str) -> None:
        self.attribute_name = name
        self.attribute_owner = owner

    def __get__(self, object: Any, object_type: type | None = None) -> Any:
        object.__dict__.get(self.attribute_name, None)


class CheckDescriptors(object):
    name = PrivateAttribute()
    income = Descriptor()
    status = NonDataDescriptor()

    def __init__(self, name: str, income: int) -> None:
        self.name = name
        self.income = income


class CheckPrivateAttributeAccess(object):
    _name = PrivateAttribute()
    name = PrivateAttribute()

    def __init__(self, name: str) -> None:
        self._name = name
        self.name = name

    def cannot_call_me(self) -> None:
        print("I am still called")

    def __you_can_call_me(self) -> None:
        print("I can be called")


class CheckPrivateAttributeAccess2(CheckPrivateAttributeAccess):
    def __init__(self, name: str) -> None:
        self._name = name
        print("comes here")


class Node(object):
    _name = PrivateAttribute()

    def __init__(self, name: str) -> None:
        self._name = name
        self.account = 0

    def __repr__(self) -> str:
        return f"name = {self._name}, account = {self.account}"

    @property
    def name(self) -> str:
        return self._name


ParameterType = ParamSpec("ParameterType")
TReturnValue = TypeVar("TReturnValue")


def private(function: Callable[ParameterType, TReturnValue | NoReturn]) -> Callable[ParameterType, TReturnValue | NoReturn]:
    @functools.wraps(function)
    def wrapper(*args: ParameterType.args, **kwargs: ParameterType.kwargs) -> TReturnValue | NoReturn:
        callers_frame = inspect.currentframe().f_back
        callers_local_variables = callers_frame.f_locals
        
        if 'self' not in callers_local_variables and function.__name__.startswith('_'):
            raise AttributeError()
        return function(*args, **kwargs)

    return wrapper


class Check(object):
    _name = PrivateAttribute()
    _account = PrivateAttribute()

    def __init__(self, name: str = "", amount: int = 0) -> None:
        self._name = name
        self._amount = amount

    def get_name(self) -> str:
        return self._name


class Enumerate(object):
    def __init__(self, iterable: Iterable[object]) -> None:
        self.iterable = iterable

    def __iter__(self) -> Generator[tuple[int, object], None, None]:
        index = 0

        for item in self.iterable:
            yield (index, item)
            index += 1


# def cached_static_method(function: Callable[ParameterType, TReturnValue | NoReturn]) -> Callable[ParameterType, TReturnValue | NoReturn]:
#     @functools.wraps(function)
#     def wrapper(*args: ParameterType.args, **kwargs: ParameterType.kwargs) -> TReturnValue:
#         return function(*args)

#     wrapper = functools.cache(wrapper)
#     wrapper = staticmethod(wrapper)

#     return wrapper


class cached_static_method(object):
    def __init__(self, function: Callable[ParameterType, TReturnValue | NoReturn]) -> Callable[ParameterType, TReturnValue | NoReturn]:
        self.function = function
        functools.update_wrapper(self, self.function)

    def __call__(self, *args: ParameterType.args, **kwargs: ParameterType.kwargs) -> TReturnValue:
        self.function = functools.cache(self.function)
        self.function = staticmethod(self.function)
        return self.function(*args, **kwargs)
    
    def __repr__(self) -> str:
        return f"{self.function!r}"


class Check(object):
    @cached_static_method
    def method(value: int) -> int:
        print(f"{value=}")
        return value


def main() -> int:
    check = Check()
    check.method(2)
    check.method(1)
    check.method(2)

    check2 = Check()
    check2.method(2)
    check2.method(3)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
