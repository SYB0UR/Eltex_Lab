#include"lab11_1.h"
/**
 * Функция потока.
 * @param arg Указатель на индекс потока.
 * @return NULL
 *
 * Поток получает свой индекс и выводит его на экран.
 */
void* print_index(void* arg) {
    int index = *((int*)arg);
    printf("Thread index: %d\n", index);
    return NULL;
}