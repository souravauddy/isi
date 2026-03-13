from __future__ import annotations
from typing import (
    Final,
)


NULL_CHAR: Final[str] = str('\0')
MIN_CHAR: Final[str] = str('a')
INT_NULL: Final[int] = int(-1)
ALPHABET: Final[int] = int(26)


class Node(object):
    __slots__ = ("next_index", "end_of_word")

    @staticmethod
    def _get_index(character: str) -> int:
        return ord(character) - ord(MIN_CHAR)

    def __init__(self) -> None:
        self.next_index = [INT_NULL for _ in range(ALPHABET)]
        self.end_of_word = NULL_CHAR

    def contains(self, character: str) -> bool:
        return self.next_index[Node._get_index(character)] != INT_NULL
    
    def next(self, character: str) -> int:
        return self.next_index[Node._get_index(character)]
    
    def add(self, character: str, index: int) -> int:
        self.next_index[Node._get_index(character)] = index
        return index

    def leaf(self) -> bool:
        return all(index == INT_NULL for index in self.next_index)


class Trie(object):
    __slots__ = ("_nodes")

    ROOT_INDEX: Final[int] = int(0)

    def __init__(self) -> None:
        """
            Initializes the Trie Object, with the root node.
        """

        self._nodes: list[Node] = []
        self._nodes.append(Node())

    def add(self, string: str) -> None:
        """
            takes in a string and add's it to the trie structure, if the string is already present in the trie, no operation occurs.
        """

        node_index = Trie.ROOT_INDEX

        for character in string:
            if self._nodes[node_index].contains(character):
                node_index = self._nodes[node_index].next(character)
                continue
            
            self._nodes.append(Node())
            node_index = self._nodes[node_index].add(character, len(self._nodes) - 1)

        self._nodes[node_index].end_of_word = string[-1]

    def __getitem__(self, index: int) -> Node:
        return self._nodes[index]
    
    def search(self, string: str) -> bool:
        node_index = Trie.ROOT_INDEX

        for character in string:
            if not self._nodes[node_index].contains(character):
                return False
            
            node_index = self._nodes[node_index].next(character)
            
        return True


def main() -> int:
    number_of_dictionary_items = int(input())
    dictionary = Trie()

    for _ in range(number_of_dictionary_items):
        dictionary.add(input())

    node_index = Trie.ROOT_INDEX

    print(dictionary[node_index].next_index)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
