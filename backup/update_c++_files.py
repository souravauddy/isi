from __future__ import annotations
from random import randrange
import sys
import os

TARGET_STRING = "#include <bits/stdc++.h>"
REPLACEMENT_STRING = '''\
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <random>
#include <vector>
#include <numeric>
#include <tuple>\
'''


def update_file(filename: str) -> None:
    with open(f"{filename}", "r+") as file:
        file_content = file.read()
        file_content = file_content.replace(TARGET_STRING, REPLACEMENT_STRING)
        file.seek(0)
        file.write(file_content)


def main() -> int:
    os.chdir("/Users/souravauddy/Documents")
    filenames = sys.stdin.readlines()

    for filename in filenames:
        update_file(filename[:-1])

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
