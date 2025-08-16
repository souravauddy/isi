import functools

def print_args(*args) -> None:
    for arg in args:
        print(arg, end = ' ')
    print(end = '\n')


def main() -> None:
    A = input()
    B = input()
    N, M = len(A), len(B)
    dp = [[0 for _ in range(M + 1)] for _ in range(N + 1)]

    for i in range(1, N + 1):
        for j in range(1, M + 1):
            if A[i - 1] == B[j - 1]:
                dp[i][j] = 1 + dp[i - 1][j - 1]
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])

    for row in dp:
        print(row)

    length = dp[N][M]
    Aindex, Bindex = N, M
    subsequence = ""

    while length > 0 and Aindex != 0 and Bindex != 0:
        if A[Aindex - 1] == B[Bindex - 1]:
            subsequence = A[Aindex - 1] + subsequence

        if dp[Aindex - 1][Bindex] > dp[Aindex][Bindex - 1]:
            Aindex -= 1
        else:
            Bindex -= 1

    print("The length of the subsequence is ", length)
    print(subsequence if subsequence != "" else "There is no common subsequence present")
    

if __name__ == "__main__":
    main()