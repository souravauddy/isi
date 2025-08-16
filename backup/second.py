import random


def main() -> None:
	size = random.randint(20, 30)

	for _ in range(size):
		print(random.randint(20, 30), end = ' ')

	print(end = '\n')



if __name__ == "__main__":
	main()