def main() -> None:
    numbers = [int(number) for number in input().split()]
    sequence = [int(number) for number in input().split()]
    length = len(sequence)

    for i in range(len(numbers) - length):
        subarray = numbers[i : i + length]

        if (subarray == sequence):
            print("The list is present in the string")
            return

    print("The list is not present in the string")


if __name__ == "__main__":
    main()