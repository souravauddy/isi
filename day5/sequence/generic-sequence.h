#include <stdlib.h>

struct SEQUENCE {
    void *elements;
    int type;
    size_t num_elements, capacity, element_size;
};

typedef struct SEQUENCE SEQUENCE;

int init_sequence(SEQUENCE *sequence, int type, int capacity);
int get_element(SEQUENCE *sequence, size_t i, void *element);
size_t length(SEQUENCE *sequence);
int summation(SEQUENCE *sequence);
