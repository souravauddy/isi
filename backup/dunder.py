from __future__ import annotations
import copy
from typing import (
    Any,
    Self,
)


class Matrix(object):
    def __init__(self, size: int = 0) -> None:
        self.matrix = [[0 for _ in range(size)] for _ in range(size)]
        self.size = size

    def __len__(self) -> int:
        return self.size

    def __str__(self) -> str:
        return f"{self.size}"

    def __repr__(self) -> str:
        return f"{self!s}"

    def __call__(self, other: object) -> Self:
        if isinstance(other, list):
            self.matrix = copy.deepcopy(other)
            self.size = len(other)
            return self
        return NotImplemented

    def __mul__(self, other: object) -> Matrix:
        if isinstance(other, Matrix):
            assert self.size == other.size

            result = Matrix(other.size)(
                [[0 for _ in range(self.size)] for _ in range(self.size)]
            )

            for i in range(self.size):
                for j in range(self.size):
                    for k in range(self.size):
                        result.matrix[i][j] += self.matrix[i][k] * other.matrix[k][j]

            return result
        return NotImplemented

    def __eq__(self, other: object) -> bool:
        if isinstance(other, Matrix):
            return True if self.matrix == other.matrix else False
        return NotImplemented

    def __add__(self, other: object) -> Matrix:
        if isinstance(other, Matrix):
            result = Matrix(other.size)(
                [[0 for _ in range(other.size)] for _ in range(other.size)]
            )

            for i in range(other.size):
                for j in range(other.size):
                    result.matrix[i][j] = self.matrix[i][j] + other.matrix[i][j]

            return result
        return NotImplemented
    
    def __sub__(self, other: object) -> Matrix:
        if isinstance(other, Matrix):
            result = Matrix(other.size())(
                [[0 for _ in range(other.size)] for _ in range(other.size)]
            )

            for i in range(other.size):
                for j in range(other.size):
                    result.matrix[i][j] = self.matrix[i][j] - other.matrix[i][j]

            return result
        return NotImplemented
    
    def transpose(self) -> Matrix:
        result = Matrix(self.matrix.size())(
            [[0 for _ in range(self.matrix.size())] for _ in range(self.matrix.size())]
        )

        for row_index, row in enumerate(self.matrix):
            for column_index, value in enumerate(row):
                result.matrix[column_index][row_index] = value

        return result


def main() -> int:


    return 0


if __name__ == "__main__":
    raise SystemExit(main())
