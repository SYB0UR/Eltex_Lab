#ifndef FUNC_H
    #define FUNC_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <pthread.h>
    #include <unistd.h>

    #define NUM_SHOPS 5
    #define NUM_CUSTOMERS 3
    #define SHOP_CAPACITY 10000
    #define LOADER_CAPACITY 5000

    /**
     * Структура, представляющая магазин.
     * @param capacity Вместимость магазина (количество товаров).
     * @param mutex Мьютекс для синхронизации доступа к магазину.
     */
    typedef struct {
        int capacity;
        pthread_mutex_t mutex;
    } Shop;

    extern Shop shops[NUM_SHOPS];
    extern pthread_t customers[NUM_CUSTOMERS];
    extern pthread_t loader;
    extern int customer_needs[NUM_CUSTOMERS];
    extern int customers_satisfied;
    extern pthread_mutex_t customers_satisfied_mutex;

    void* customer_thread(void* arg);
    void* loader_thread();

#endif
