#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct list {
    int *numbers;
    size_t number_of_elements;
};

typedef struct list list;

void init_list(list *list_, int *elements, int number_of_elements) {
    list_->numbers = elements;
    list_->number_of_elements = number_of_elements;
}

static inline int max(int a, int b) {
    return a > b ? a : b;
}

static inline int min(int a, int b) {
    return a < b ? a : b;
}

void * mean(void *arguments) {
    double *result = (double *) malloc(sizeof(double));
    list *list_ = (list *) arguments;
    *result = 0;

    for (int i = 0; i < list_->number_of_elements; i++)
        *result += list_->numbers[i];
    
    *result /= list_->number_of_elements;
    pthread_exit((void *) result);
}

void * minimum(void *arguments) {
    list *list_ = (list *) arguments;
    int *result = (int *) malloc(sizeof(int));
    *result = list_->numbers[0];

    for (int i = 1; i < list_->number_of_elements; i++)
        *result = min(*result, list_->numbers[i]);

    pthread_exit((void *) result);
}

void * maximum(void *arguments) {
    list *list_ = (list *) arguments;
    int *result = (int *) malloc(sizeof(int));
    *result = list_->numbers[0];

    for (int i = 1; i < list_->number_of_elements; i++)
        *result = max(*result, list_->numbers[i]);

    pthread_exit((void *) result);
}

int main() {
    int N;
    scanf("%d", &N);
    int *numbers = (int *) malloc(N * sizeof(int));

    for (int i = 0; i < N; i++)
        scanf("%d", &numbers[i]);
    
    list element_numbers;
    init_list(&element_numbers, numbers, N);
    
    pthread_t thread1, thread2, thread3;

    pthread_create(&thread1, NULL, mean, &element_numbers);
    pthread_create(&thread2, NULL, minimum, &element_numbers);
    pthread_create(&thread3, NULL, maximum, &element_numbers);

    double *mean_result;
    int *max_result, *min_result;
    
    pthread_join(thread1, (void **) &mean_result);
    pthread_join(thread2, (void **) &max_result);
    pthread_join(thread3, (void **) &min_result);

    printf("mean = %lf, max = %d, min = %d\n", *mean_result, *max_result, *min_result);

    free(mean_result);
    free(max_result);
    free(min_result);
    free(numbers);
}
