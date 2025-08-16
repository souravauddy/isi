from __future__ import annotations
import sys
from typing import (
    Final,
    Sequence,
    NamedTuple
)


INF: Final[int] = int(sys.maxsize)
RAND_MAX: Final[int] = int(sys.maxsize)


class Edge(NamedTuple):
    edge: int = 0
    weight: int = INF


def bellman_ford(adjacency_list: list[list[Edge]], source: int) -> list[int]:
    vertices = int(len(adjacency_list))
    distance = [INF for _ in range(vertices)]
    distance[source] = 0

    for _ in range(vertices - 1):
        for vertex in range(vertices):
            for edge, weight in adjacency_list[vertex]:
                distance[edge] = min(distance[edge], distance[vertex] + weight)

    for vertex in range(vertices):
        for edge, weight in adjacency_list[vertex]:
            if distance[edge] > distance[vertex] + weight:
                print("The graph contains a negative edge cycle")
                return [INF for vertex in range(vertices)]

    return distance


def negative_cost_cycle(container: Sequence[int], value: int) -> bool:
    return len(container) == 1 and next(iter(set(container))) == value


def main() -> int:
    print("Enter the number of vertices and the number of edges")
    vertices, edges = map(int, input().split())

    print("Enter the adjacency list")
    adjacency_list = [list() for _ in range(vertices)]    # type: ignore

    for _ in range(edges):      
        u, v, weight = map(int, input().split())
        adjacency_list[u].append(Edge(v, weight))

    print("Enter the source")
    source = int(input())
    
    distance = bellman_ford(adjacency_list, source)

    if not negative_cost_cycle(distance, INF):
        print(dict(enumerate(distance)))
        print(tuple(enumerate(distance)))
    else:
        print("There exists a negative weight cycle in the graph.")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())


''' 

Sample Inputs:

3 3
0 1 1
1 2 3
2 0 -5

5 8
0 1 -1
0 2 4
1 2 3 
1 3 2 
1 4 2 
3 2 5
3 1 1 
4 3 -3
0

5 6
0 1 2
1 3 3
0 2 1
2 1 -2 
2 4 1
3 4 1
0

0 1 2 3 4

5
0 2 1 0 0
0 0 0 3 0
0 -2 0 0 1
0 0 0 0 1
0 0 0 0 0
0

'''
