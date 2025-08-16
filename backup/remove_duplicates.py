import functools


def binary_search(List, target):
    low, high = 0, len(List) - 1

    while low <= high:
        mid = low + (high - low) // 2

        if List[mid] == target:
            return True
        elif List[mid] < target:
            low = mid + 1
        else:
            high = mid - 1

    return False


def unique(List):
    size = len(List)
    List = sorted(List)
    numbers = []
    index = 0

    while index < size:
        numbers.append(List[index])
        while index + 1 < size and List[index] == List[index + 1]:
            index += 1

        index += 1
        
    if List[-1] not in numbers:
        numbers.append(List[-1])

    return numbers


def main() -> None:
    List1 = sorted([int(number) for number in input().split()])
    List2 = sorted([int(number) for number in input().split()])
    List3 = []

    for number in List1: 
        if not binary_search(List2, number):
            List3.append(number)

    for number in List2:
        if not binary_search(List1, number):
            List3.append(number)

    print(unique(List3))


if __name__ == "__main__":
    main()


'''
i> whether two lists are circularly identical

1 2 3 4 5

3 4 5 1 2

ii> whether a list  contains a sublist

iii> remove duplicates from dictionary

iv> combine two dictionaries by adding values common keys: using third one

v> check if a set is a subset of another set (using set)

vi> check if two given sets have no elements in common

vii> compute the square of first n fibonacci numbers and generate a list of the numbers

viii> convert a given list of strings into a list of lists using map function

information:

check frozen set

'''