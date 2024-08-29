#include"lab11_2.h"

/**
 * Функция потока инкрементации.
 * @return NULL
 *
 * Поток выполняет NUM_ITERATIONS итераций, в каждой из которых инкрементирует общий счетчик.
 * Для синхронизации используется мьютекс.
 */
void* increment() {
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
