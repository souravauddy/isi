import random
import functools


def unique(dictionary):
    values = {}

    for key in dictionary:
        value = dictionary[key]

        if value not in values:
            values[value] = key

    dictionary.clear()

    for value in values:
        key = values[value]
        dictionary[key] = value

    return dictionary


def main() -> None:
    List = [random.randint(20, 60) for _ in range(random.randint(30, 50))]
    dictionary = {}

    for number in List:
        if number not in dictionary:
            dictionary[number] = 1
        else:
            dictionary[number] += 1

    print(unique(dictionary))


if __name__ == "__main__":
    main()