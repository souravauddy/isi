#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "generic-sequence.h"

enum TYPES {
    INT_TYPE, FLOAT_TYPE, STRING_TYPE
};

const int TYPE_SIZE[] = {sizeof(int), sizeof(float), sizeof(char)};
const int MAX_SIZE[] = {1, 1, (int) 1e2 + 5};
const int MAX_CAPACITY = (int) 1e2 + 5;

SEQUENCE * allocate_sequence() {
    return (SEQUENCE *) malloc(sizeof(SEQUENCE));
}

int init_sequence(SEQUENCE *sequence, int type, int capacity) {
    sequence->elements = malloc(capacity * TYPE_SIZE[type] * MAX_SIZE[type]);

    if (sequence->elements == NULL)
        return 0;

    sequence->capacity = capacity;
    sequence->num_elements = 0;
    sequence->type = type;
    sequence->element_size = TYPE_SIZE[type] * MAX_SIZE[type];

    return 1;
}

int insert_element(SEQUENCE *sequence, void *element) {
#ifdef DYNAMIC_SEQUENCE
    if (sequence->num_elements == sequence->capacity) {
        sequence->capacity *= 2;
        sequence->elements = realloc(sequence->elements, sequence->capacity * sequence->element_size);
        
        if (sequence->elements == NULL)
            return 0;
    }
#endif

    memcpy((char *) sequence->elements + sequence->num_elements * sequence->element_size, element, sequence->element_size);
    sequence->num_elements++;

    return 1;
}

int get_element(SEQUENCE *sequence, size_t index, void *element) {
    if (sequence->num_elements == 0) {
        fputs("Sequence is empty cannot return value", stderr);
        return 0;
    }

    if (index >= sequence->num_elements) {
        fprintf(stderr, "index sequence out of bounds (sequence size = %zu, index requested = %zu)\n", sequence->num_elements, index);
        return 0;
    }

    memcpy(element, (char *) sequence->elements + index * sequence->element_size, sequence->element_size);

    return 1;
}

static int round(float number) {
    int integer_part = (int) number;
    float decimal_part = number - integer_part;
    return integer_part + (decimal_part >= 0.5);
}

size_t length(SEQUENCE *sequence) {
    return sequence->num_elements;
}

int element_summation(SEQUENCE *sequence, int index) {
    char *element = (char *) sequence->elements + index * sequence->element_size;

    if (sequence->type == INT_TYPE) // type is "int".
        return *((int *) element);

    if (sequence->type == FLOAT_TYPE) // type is "float".
        return round(*(float *) element);

    // otherwise type is (char *).

    int sum = 0;

    for (int i = 0; element[i]; i++)
        sum += (int) element[i];

    return sum;
}

int summation(SEQUENCE *sequence) {
    int sequence_summation = 0;

    for (int i = 0; i < length(sequence); i++)
        sequence_summation += element_summation(sequence, i);
    
    return sequence_summation;
}

void print_type(SEQUENCE *sequence, int index) {
    char *element = (char *) sequence->elements + index * sequence->element_size;

    if (sequence->type == INT_TYPE) {
        printf("%d", *((int *) element));
        return;
    }

    if (sequence->type == FLOAT_TYPE) {
        printf("%f", *((float *) element));
        return;
    }

    puts(element);
}

void print_sequence(SEQUENCE *sequence) {
    for (int i = 0; i < length(sequence); i++) {
        print_type(sequence, i);
        printf(" ");
    }

    puts("");
}

static inline void free_sequence(SEQUENCE *sequence) {
    free(sequence->elements);
    free(sequence);
}

bool check_exception(int exceptions, char character) {
    return exceptions > 0 && character == ' ' ? false : true;
}

char * next_element(char *sentence) { // iterator to retreive the next element from the sequence using ' ' and the delimeter.
    static int index = 0, exceptions = 2;
    char *element = (char *) malloc(MAX_SIZE[STRING_TYPE]);
    int element_index = 0;

    while (check_exception(exceptions, sentence[index]) && sentence[index] != '\0' && sentence[index] != '\n')
        element[element_index++] = sentence[index++];
    
    element[element_index] = '\0';

    while (sentence[index] == ' ')
        index++;

    if (*sentence == '\n') {
        index = 0;
        exceptions = 2;
    }

    exceptions--;
    return element;
}

int main(const int argc, const char **argv) {
    int N, max_summation = 0;
    scanf("%d", &N);

    SEQUENCE **sequences = (SEQUENCE **) malloc(N * sizeof(SEQUENCE *));
    SEQUENCE *max_sequence = NULL;

    for (int i = 0; i < N; i++) {
        char *sentence = (char *) malloc(MAX_CAPACITY * MAX_SIZE[STRING_TYPE]);
        assert(sentence != NULL);
        fgets(sentence, MAX_CAPACITY * MAX_SIZE[STRING_TYPE] ,stdin);

        char *next = next_element(sentence);
        char type = *next;
        free(next);
        next = next_element(sentence);
        size_t number_of_elements = (size_t) atoi(next);
        free(next);

        switch (type) {
            case 'i':
                sequences[i] = allocate_sequence();
                init_sequence(sequences[i], INT_TYPE, number_of_elements);

                for (int i = 0; i < number_of_elements; i++) {
                    next = next_element(sentence);
                    int element = atoi(next);
                    insert_element(sequences[i], &element);
                    free(next);
                }

                break;

            case 'f':
                sequences[i] = allocate_sequence();
                init_sequence(sequences[i], FLOAT_TYPE, number_of_elements);

                for (int i = 0; i < number_of_elements; i++) {
                    next = next_element(sentence);
                    float element = atof(next);
                    insert_element(sequences[i], &element);
                    free(next);
                }
                
                break;

            case 's':
                sequences[i] = allocate_sequence();
                init_sequence(sequences[i], STRING_TYPE, number_of_elements);

                for (int i = 0; i < number_of_elements; i++) {
                    char *next = next_element(sentence);
                    insert_element(sequences[i], next);
                    free(next);
                }

                break;

            default:
                assert(false);
        }

        free(sentence);
    }

    for (int i = 0; i < N; i++) {
        int current_sequence_summation = summation(sequences[i]);

        if (current_sequence_summation > max_summation) {
            max_summation = current_sequence_summation;
            max_sequence = sequences[i];
        } 
    }

    print_sequence(max_sequence);

    for (int i = 0; i < N; i++)
        free_sequence(sequences[i]);

    free(sequences);
}
