#include <stdio.h>
#include <stdbool.h>

const int MAX_SIZE = (int) 64;

int string_length(const char *string) {
    int length = 0;

    while (string[length] != '\0')
        length++;

    return length;
}

bool property(const char *string1, const char *string2) {
    int length1 = string_length(string1);
    int length2 = string_length(string2);

    if (length1 != length2)
        return false;

    int count = 0;

    for (int i = 0; i < length1; i++)
        if (string1[i] != string2[i])
            count++;

    return count <= 2;
}

int main() {
    int M;
    scanf("%d", &M);
    char strings[M][MAX_SIZE];

    for (int i = 0; i < M; i++)
        scanf(" %s", strings[i]);

    for (int i = 0; i < M - 1; i++)
        if (!property(strings[i], strings[i + 1])) {
            puts("NO");
            return 0;
        }

    puts("YES");
}
