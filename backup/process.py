from __future__ import annotations
from signal import SIGINT, SIGTERM
from types import FrameType
from time import sleep
from typing import (
    Callable,
    ParamSpec,
    Any,
    TypeVar,
    NoReturn,
    Protocol,
    Self,
    overload,
)
import multiprocessing
import functools
import concurrent.futures
import signal
import sys
import os
import asyncio


CPU_CORES_COUNT = multiprocessing.cpu_count()


# class _ReturnType(Protocol):
#     @overload
#     def __mul__(self: ReturnType, other: int) -> ReturnType: ...
#     @overload
#     def __mul__(self: ReturnType, other: float) -> ReturnType: ...


# Parameter = ParamSpec("Parameter")
# ReturnType = TypeVar("ReturnType", bound=_ReturnType)


# def synchronize(function: Callable[Parameter, ReturnType]) -> Callable[Parameter, ReturnType]:
#     semaphore = multiprocessing.Semaphore(3)
#     @functools.wraps(function)
#     def inner(*args: Parameter.args, **kwargs: Parameter.kwargs) -> ReturnType:
#         semaphore.acquire()
#         result = function(*args, **kwargs)
#         semaphore.release()
#         return result

#     return inner


# @synchronize
# def work(start: int, end: int) -> int:
#     sum_ = 0
#     for number in range(start, end):
#         print(number)
#         sum_ += number
#     return sum_


# class Descriptor(object):
#     def __set_name__(self, owner: object, name: str) -> None:
#         self.private_name = f"_{name}"
#         self.class_ = owner

#     def __get__(self, object: object, object_type: type | None = None) -> object:
#         return getattr(object, self.private_name)

#     def __set__(self, object: object, value: Any) -> None:
#         setattr(object, self.private_name, value)


# class specialdict(dict):
#     def __getitem__(self, key: str) -> Any | NoReturn:
#         if not isinstance(key, str):
#             raise NotImplementedError
#         return super().__getitem__(key)

#     def __setitem__(self, key: str, value: Any) -> None:
#         if not isinstance(key, str):
#             raise NotImplementedError
#         return super().__setitem__(key, value)


# def class_decorator(cls):
#     @functools.wraps(cls, updated=())
#     class Wrapper(cls):
#         def print(self) -> None:
#             print(**self.__dict__)
#             print(self.__dict__.keys())

#     return Wrapper


class decorator(object):
    def __init__(self, function: Callable) -> None:
        function = functools.update_wrapper(self, function)
        self.function = function

    def __call__(self, *args: tuple[Any, ...], **kwargs: dict[str, Any]) -> Any:
        return self.function(*args, **kwargs) ** 2


# class decorator_arguments(object):
#     def __init__(self, iterations: int = 0) -> None:
#         print("comes here in the init function")
#         self.iterations = iterations

#     def __call__(self, function: Callable[..., ReturnType]) -> Callable[..., ReturnType]:
#         print("comes here in the call function")
#         @functools.wraps(function)
#         def wrapper(*args: tuple[Any, ...], **kwargs: dict[Any, Any]) -> Any:
#             return function(*args, **kwargs) * self.iterations

#         return wrapper


# def function_decorator(iterations: int) -> Callable:
#     def wrapper(function: Callable[Parameter, Any]) -> Callable[Parameter, ReturnType]:
#         @functools.wraps(function)
#         def inner(*args: Parameter.args, **kwargs: Parameter.kwargs) -> Any:
#             return iterations * function(*args, **kwargs)

#         return inner
#     return wrapper


# @decorator_arguments(iterations=4)
# def function_for_decorator() -> int:
#     print("sourav")
#     return 20


# @function_decorator(iterations=20)
# def check_function_decorator() -> int:
#     return 20


# def function(argument: ReturnType) -> ReturnType:
#     return argument * 2


# class MetaClass(type):
#     def __new__(cls, *args, **kwargs) -> Self:
#         print("comes here in the __new__ method")
#         return super().__new__(cls, *args, **kwargs)


# class Check(metaclass=MetaClass):
#     def __init__(self) -> None:
#         self.name = "sourav"


# def signal_handler(signal: int, frame: FrameType) -> None:
#     print("This is how we handle signals in python")
#     raise SystemExit(0)


@decorator
def something() -> None: ...


def main() -> int:
    print(something)

    return 0
    raise SystemExit(0)

    with concurrent.futures.ProcessPoolExecutor(CPU_CORES_COUNT) as executor:
        process1 = executor.submit(work, 2000, 2200)
        process2 = executor.submit(work, 500, 800)
        process3 = executor.submit(work, 900, 1300)
        print(process3.result())
        print(process1.result())
        print(process2.result())

    return 0


if __name__ == '__main__':
    raise SystemExit(main())
