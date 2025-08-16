import copy
from queue import Queue


def main() -> None:
    vertices, edges = map(int, input().split())
    visited = [False for _ in range(vertices)]
    adjancency_list = [[] for _ in range(vertices)]
    queue = Queue()

    for _ in range(edges):
        u, v = map(int, input().split())
        adjancency_list[u].append(v)

    source = int(input())

    queue.put(source)

    while not queue.empty():
        size = queue.qsize()

        for _ in range(size):
            node = queue.get()
            visited[node] = True
            print(node)

            for vertex in adjancency_list[node]:
                if not visited[vertex]:
                    queue.put(vertex)


if __name__ == "__main__":
    main()


'''
3 5
1 2
1 0
2 0
2 1
0 2
'''