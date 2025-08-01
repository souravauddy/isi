#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const int MAX_SIZE = (int) 2e5;

int string_length(const char *string) {
    int length = 0;

    while (string[length] != '\0')
        length++;

    return length;
}

bool check(const char *string, int index, int string_length, const char *target, int length) {
    int target_index = 0;

    while (index < string_length && target_index < length) {
        if (string[index] != target[target_index])
            return false;

        index++, target_index++;
    }

    return target_index == length;
}

int main(const int argc, const char **argv) {
    FILE *file = fopen(argv[1], "r+");
    char sentence[MAX_SIZE] = {0}, replaced[MAX_SIZE] = {0};
    fgets(sentence, MAX_SIZE, file);

    const char *target = argv[2], *prefix = argv[3];

    int target_length = string_length(target), prefix_length = string_length(prefix), sentence_length = string_length(sentence);
    int index = 0, replaced_index = 0;

    while (sentence[index] != '\n' && sentence[index]) {
        if (sentence[index] == target[0]) {
            if (check(sentence, index, sentence_length, target, target_length)) {
                for (int i = 0; i < prefix_length; i++)
                    replaced[replaced_index++] = prefix[i];

                for (int i = 0; i < target_length; i++)
                    replaced[replaced_index++] = target[i];

                index += target_length;
            } else {
                replaced[replaced_index] = sentence[index];
                replaced_index++, index++;
            }
        } else {
            replaced[replaced_index] = sentence[index];
            replaced_index++, index++;
        }
        printf("%c", replaced[replaced_index]);
    }

    replaced[replaced_index] = '\0';

    puts(replaced);
    fputs(replaced, file);
}
