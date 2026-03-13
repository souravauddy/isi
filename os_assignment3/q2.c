#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct sequence_information {
    int start, size;
};

typedef struct sequence_information sequence_information;

int *numbers, N;

int int_comparator(const void *a, const void *b) {
    return *((int *) a) - *((int *) b);
}

void * sort_subarray(void *arguments) {
    sequence_information *sequence_informationd_arguments = (sequence_information *) arguments;
    qsort(numbers + sequence_informationd_arguments->start, sequence_informationd_arguments->size, sizeof(int), int_comparator);
    return NULL;
}

void merge_and_copy(int *numbers1, int size1, int *numbers2, int size2) {
    int *another_numbers = (int *) malloc((size1 + size2) * sizeof(int));
    int pointer1 = 0, pointer2 = 0, pointer3 = 0;

    while (pointer1 < size1 && pointer2 < size2)
        another_numbers[pointer3++] = numbers1[pointer1] < numbers2[pointer2] ? numbers1[pointer1++] : numbers2[pointer2++];

    while (pointer1 < size1)
        another_numbers[pointer3++] = numbers1[pointer1++];
    
    while (pointer2 < size2)
        another_numbers[pointer3++] = numbers2[pointer2++];

    for (int i = 0; i < size1 + size2; i++)
        numbers[i] = another_numbers[i];
}

int main() {
    scanf("%d", &N);
    numbers = (int *) malloc(N * sizeof(int));

    for (int i = 0; i < N; i++)
        scanf("%d", &numbers[i]);

    sequence_information sequence_information1, sequence_information2;
    sequence_information1.start = 0, sequence_information1.size = N / 2;
    sequence_information2.start = sequence_information1.size, sequence_information2.size = N - sequence_information1.size;

    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, sort_subarray, &sequence_information1);
    pthread_create(&thread2, NULL, sort_subarray, &sequence_information2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    merge_and_copy(numbers + sequence_information1.start, sequence_information1.size, numbers + sequence_information2.start, sequence_information2.size);

    for (int i = 0; i < N; i++)
        printf("%d ", numbers[i]);
    puts("");
}
