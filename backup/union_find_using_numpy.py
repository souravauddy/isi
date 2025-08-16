import numpy as np
import copy


class UnionFind:
    def __init__(self, size: int) -> None:
        self.size = size
        self.parent = np.arange(0, size + 1)
        self.rank = np.zeros(size + 1)
        self.connected_components = size


    def find(self, vertex: int) -> int:
        if self.parent[vertex] == vertex:
            return vertex

        self.parent[vertex] = self.find(self.parent[vertex])
        return self.parent[vertex]


    def unite(self, x: int, y: int) -> bool:
        x = self.find(x)
        y = self.find(y)

        if x == y:
            return False

        if self.rank[x] > self.rank[y]:
            x, y = y, x     # swap the two parents
        
        self.parent[x] = self.parent[y]
        self.rank[y] += self.rank[x]
        self.connected_components -= 1

        return True


    def components(self) -> int:
        return self.connected_components


class Edge:
    def __init__(self, source: int = 0, destination: int = 0) -> None:
        self.source = source
        self.destination = destination


def main() -> None:
    N, edges = map(int, input().split())
    UF = UnionFind(N)

    for _ in np.arange(edges):
        u, v = map(int, input().split())
        UF.unite(u, v)

    print(UF.components())


if __name__ == "__main__":
    main()