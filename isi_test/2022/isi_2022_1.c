#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

const int MAX_DIGITS = (int) 1e2 + 5;
const int DIGIT = (int) '0';
const int BASE = (int) 10;
const char NULL_TERMINATOR = (char) '\0';

int ascii_to_integer(int ascii_value) {
    return ascii_value - DIGIT;
}

int string_length(const char *string) {
    int length = 0;

    while (string[length] != '\0' && string[length] != '\n' && string[length] != NULL_TERMINATOR)
        length++;

    return length;
}

void swap(char *a, char *b) {
    char copy = *a;
    *a = *b;
    *b = copy;
}

int min(int a, int b) {
    return a < b ? a : b;
}

void reverse(char *string) {
    int length = string_length(string);

    for (int i = 0, j = length - 1; i < length / 2; i++, j--)
        swap(&string[i], &string[j]);
}

void add(const char *number1, const char *number2, char *result) {
    int number_of_digits1 = string_length(number1), number_of_digits2 = string_length(number2);
    int sum = 0, carry = 0;
    int min_digits = min(number_of_digits1, number_of_digits2);

    for (int digit = 0; digit < min_digits; digit++) {
        sum = (ascii_to_integer(number1[digit]) + ascii_to_integer(number2[digit]) + carry);
        carry = sum / BASE;
        result[digit] = (char) sum % BASE + DIGIT;
    }

    int digit = min_digits;

    while (digit < number_of_digits1) {
        sum = (ascii_to_integer(number1[digit]) + carry);
        carry = sum / BASE;
        result[digit] = (char) sum % BASE + DIGIT;
        digit++;
    }

    while (digit < number_of_digits2) {
        sum = (ascii_to_integer(number2[digit]) + carry);
        carry = sum / BASE;
        result[digit] = (char) sum % BASE + DIGIT;
        digit++;
    }

    result[digit] = (char) carry + DIGIT;
    result[digit + (carry > 0)] = NULL_TERMINATOR;
}

void subtract(char *number1, char *number2, char *result) {
    int number_of_digits1 = string_length(number1), number_of_digits2 = string_length(number2);
    int min_digits = min(number_of_digits1, number_of_digits2);
    int carry = 0;

    for (int digit = 0; digit < min_digits; digit++) {
        int number1_digit = ascii_to_integer(number1[digit]), number2_digit = ascii_to_integer(number2[digit]);
        int difference = number1_digit - carry - number2_digit;
        carry = difference < 0 ? 1 : 0;
        difference = difference < 0 ? BASE + difference : difference;
        result[digit] = (char) difference + DIGIT;
    }

    int digit = min_digits;

    while (digit < number_of_digits1) {
        int difference = ascii_to_integer(number1[digit]) - carry;
        carry = difference < 0 ? 1 : 0;
        difference = difference < 0 ? BASE + difference : difference;
        result[digit] = (char) difference + DIGIT;
        digit++;
    }

    result[digit] = NULL_TERMINATOR;
}

void remove_prefix_zeros(char *string) {
    int length = string_length(string);
    int left = 0, right = 0;

    while (string[right] == '0')
        right++;

    while (string[right] != NULL_TERMINATOR) {
        string[left] = string[right];
        left++, right++;
    }

    string[left] = NULL_TERMINATOR;
}

int main() {
    char number1[MAX_DIGITS], number2[MAX_DIGITS];
    char result[MAX_DIGITS];

    for (int digit = 0; digit < MAX_DIGITS; digit++)
        result[digit] = number1[digit] = number2[digit] = '0';

    fgets(number1, MAX_DIGITS, stdin);
    fgets(number2, MAX_DIGITS, stdin);

    reverse(number1);
    reverse(number2);

    char operator = getchar();

    switch (operator) {
        case '+':
            add(number1, number2, result);
            break;
        
        case '-':
            subtract(number1, number2, result);
            break;

        default:
            assert(false);
    }

    reverse(result);
    remove_prefix_zeros(result);

    puts(string_length(result) ? result : "0");
}
