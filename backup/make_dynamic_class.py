from __future__ import annotations
import sys
from typing import Final


def main() -> int:
    classname, superclasses, class_attributes_names = sys.stdin.readlines()

    if isinstance(classname, list):
        classname = classname[-1]

    superclasses = tuple([eval(f"{name}().__class__") for name in superclasses.split()])

    class_attributes_names = class_attributes_names.split()

    """
    creating class using type.
    """

    new_class = type(
        classname,
        superclasses,
        {
            name: type(name) for name in class_attributes_names
        }
    )

    print(new_class)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
