#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int MAX_SIZE = (int) 256;

void swap(char *a, char *b) {
    char copy = *a;
    *a = *b;
    *b = copy;
}

void reverse(char *string, int i, int j) {
    for (int k1 = i, k2 = j - 1; k1 <= k2; k1++, k2--)
        swap(&string[k1], &string[k2]);
}

int main() {
    char string[MAX_SIZE];
    fgets(string, MAX_SIZE, stdin);

    int string_length = 0;

    while (string[string_length] != '\n')
        string_length++;

    for (int i = 0, j = string_length - 1; i < string_length / 2; i++, j--)
        swap(&string[i], &string[j]);

    puts(string);

    for (int i = 0; i < string_length; i++) {
        int j = i + 1;

        while (string[j] != '\n' && string[j] != ' ')
            j++;

        reverse(string, i, j);
        i = j;
    }

    puts(string);
}
