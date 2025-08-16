import sys


sys.setrecursionlimit(10 ** 7)

QUADS = ((1, 1), (1, -1), (-1, 1), (-1, -1))

def main() -> None:
    x0, y0, r = map(int, input().split())
    sector = []
    x = 0; y = r
    p = 3 - 2 * r


    while x < y:
        sector.append((x, y))
        x += 1

        if p < 0:
            p = p + 4 * x + 6
        else:
            y -= 1
            p = p + 4 * (x - y) + 10

    sector = sector + sector[len(sector) - 2::-1]

    for q in QUADS:
        for point in sector:
            print(point[0] * q[0], point[1] * q[1])

    

if __name__ == "__main__":
    main()  