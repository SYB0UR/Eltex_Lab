#include"lab11_1.h"

int main() {
    pthread_t threads[NUM_THREADS];
    int indix[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        indix[i] = i;
        pthread_create(&threads[i], NULL, print_index, &indix[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
