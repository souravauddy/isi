import functools

# This algorithm assumes that the values in the queue are unique


def get_index(target, numbers):
    for index, number in enumerate(numbers):
        if number == target:
            return index

    return -1


def main() -> None:
    queue = [int(number) for number in input().split()]
    numbers = [int(number) for number in input().split()]
    queue_size, numbers_size = len(queue), len(numbers)

    assert queue_size == numbers_size, print("The two lists are not valid")

    start = int(get_index(queue[0], numbers))

    if start == -1:
        print("The lists are not in the form a circular queue")
        return

    index = 0

    for i in range(start, numbers_size):
        if numbers[i] != queue[index]:
            print("The two lists are not equivalent")
            return

        index += 1

    for i in range(0, start):
        if numbers[i] != queue[index]:
            print("The two lists are not in the form of a circular queue")
            return

        index += 1

    print("The two lists are equivalent in circular way")


if __name__ == "__main__":
    main()