from __future__ import annotations
import re


def main() -> int:
    compiled_regex = re.compile(r"\d{1,3}")
    string = "sourav 245, 294"
    # print(re.sub(r"(\t| |\n)", '-', "sourav\n "))
    
    for match in compiled_regex.finditer(string):
        print(match.group())

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
