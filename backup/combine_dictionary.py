import random
import functools

def get_dictionary():
    List = [random.randint(20, 60) for _ in range(random.randint(30, 50))]
    dictionary = {}

    for number in List:
        if number not in dictionary:
            dictionary[number] = 1
        else:
            dictionary[number] += 1

    return dictionary


def main() -> None:
    dictionary1 = get_dictionary()
    dictionary2 = get_dictionary()
    dictionary3 = {}

    for key in dictionary1:
        if key in dictionary2:
            dictionary3[key] = dictionary1[key] + dictionary2[key]

    print(dictionary3)


if __name__ == "__main__":
    main()