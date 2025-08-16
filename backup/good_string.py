from __future__ import annotations
import sys
import io


def main() -> int:
    lines = sys.stdin.readlines()
    good_string, name = lines
    good_string_set = frozenset(good_string)
    builder = io.StringIO("")

    for character in name:
        if character not in good_string_set:
            builder.write(character)

    modified_name = builder.getvalue()
    previous = good_string[0]
    answer = 0

    for character in modified_name:
        minimum = sys.maxsize
        good_characters_set = set()

        for good_character in good_string:
            if abs(ord(character) - ord(good_character)) < minimum:
                minimum = abs(ord(character) - ord(good_character))

        for good_character in good_string:
            if abs(ord(character) - ord(good_character)) == minimum:
                good_characters_set.add(good_character)

        assert len(good_characters_set) > 0, "There is something wrong with the logic in this code."

        good_characters = list(good_characters_set)
    
        if len(good_characters) == 1:
            answer += minimum
            previous = good_characters[0]
            continue

        assert len(good_characters) == 2

        if abs(ord(previous) - ord(good_characters[0])) < abs(ord(previous) - ord(good_characters[1])):
            answer += abs(ord(previous) - ord(good_characters[0]))
            previous = good_characters[0]
        else:
            answer += abs(ord(previous) - ord(good_characters[1]))
            previous = good_characters[1]
        
    print(answer)

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
