#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

const int MAX_SIZE = (int) 1e3 + 5;
const int MIN_CAPACITY = (int) 27;
const char INVALID_CHARACTER = '!';

static inline bool sign(const char character) {
    return character == '+' || character == '-';
}

static inline char flip_sign(const char sign) {
    return '+' ^ '-' ^ sign;
}

size_t string_length(const char *string) {
    size_t length = 0;

    while (string[length] != '\n' && string[length] != '\0')
        length++;

    return length;
}

struct term {
    char sign, variable;
};

typedef struct term term;

struct expression {
    term *terms;
    size_t number_of_terms, _capacity;
};

typedef struct expression expression;

void _increase_capacity(expression *_expression) {
    _expression->terms = (term *) realloc(_expression->terms, 2 * _expression->_capacity * sizeof(term));
    _expression->_capacity = 2 * _expression->_capacity;
    assert(_expression->terms);
}

void add_term(expression *_expression, char sign, char variable) {
    if (_expression->number_of_terms == _expression->_capacity)
        _increase_capacity(_expression);

    _expression->terms[_expression->number_of_terms].sign = sign;
    _expression->terms[_expression->number_of_terms].variable = variable;
    _expression->number_of_terms++;
}

int term_comparator(const void *a, const void *b) {
    return ((term *) a)->variable - ((term *) b)->variable;
}

void init_expression(expression *_expression) {
    _expression->_capacity = MIN_CAPACITY;
    _expression->number_of_terms = 0;
    _expression->terms = (term *) malloc(_expression->_capacity * sizeof(term));
    assert(_expression->terms);
}

void free_expression(expression *_expression) {
    free(_expression->terms);
    free(_expression);
}

static inline char get_sign(const char *string, const int index) {
    if (index == 0)
        return '+';

    return sign(string[index - 1]) ? string[index - 1] : '+';
}

void print_expression(const expression *_expression) {
    for (int i = 0; i < _expression->number_of_terms; i++)
        printf("%c%c", _expression->terms[i].sign, _expression->terms[i].variable);
    puts("");
}

expression * parse_and_simplify_expression(char *string_expression) {
    const size_t N = string_length(string_expression);
    expression *parsed_expression = (expression *) malloc(sizeof(expression));
    init_expression(parsed_expression);

    for (int i = 0; i < N; i++)
        if (isalpha(string_expression[i]))
            add_term(parsed_expression, get_sign(string_expression, i), string_expression[i]);

    // valid O(N ^ 2) algorithm, and constant extra space.

    int term_index = parsed_expression->number_of_terms;

    for (int i = N - 1; i >= 0; i--) {
        if (isalpha(string_expression[i])) {
            term_index--;
            continue;
        }

        if (string_expression[i] == '(') {
            if (i - 1 >= 0 && string_expression[i - 1] == '-') {
                int previous_term_index = term_index, j = i + 1;
                int open_count = 0;

                for (j = i + 1; string_expression[j] != ')' || open_count > 0; j++) {
                    if (isalpha(string_expression[j])) {
                        parsed_expression->terms[term_index].sign = flip_sign(parsed_expression->terms[term_index].sign);
                        term_index++;
                    }

                    if (string_expression[j] == '(')
                        open_count++;

                    if (string_expression[j] == ')')
                        open_count--;
                }

                assert(string_expression[j] == ')');
                string_expression[i] = string_expression[j] = INVALID_CHARACTER;
                term_index = previous_term_index;
            }
        }
    }

    return parsed_expression;
}

static inline bool equal_term(const term *term1, const term *term2) {
    return term1->sign == term2->sign && term1->variable == term2->variable;
}

bool equal(const expression *expression1, const expression *expression2) {
    if (expression1->number_of_terms != expression2->number_of_terms)
        return false;

    qsort(expression1->terms, expression1->number_of_terms, sizeof(term), term_comparator);
    qsort(expression2->terms, expression2->number_of_terms, sizeof(term), term_comparator);

    for (int i = 0; i < expression1->number_of_terms; i++)
        if (!equal_term(&expression1->terms[i], &expression2->terms[i]))
            return false;
        
    return true;
}

int main() {
    char string_expression1[MAX_SIZE], string_expression2[MAX_SIZE];
    scanf("%s%s", string_expression1, string_expression2);

    expression *expression1 = parse_and_simplify_expression(string_expression1);
    expression *expression2 = parse_and_simplify_expression(string_expression2);

    puts(equal(expression1, expression2) ? "Same" : "Different");

    free_expression(expression1);
    free_expression(expression2);
}
