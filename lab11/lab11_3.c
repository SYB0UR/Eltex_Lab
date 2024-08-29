
#include"lab11_3.h"



    Shop shops[NUM_SHOPS];
    pthread_t customers[NUM_CUSTOMERS];
    pthread_t loader;
    int customer_needs[NUM_CUSTOMERS];
    int customers_satisfied = 0;
    pthread_mutex_t customers_satisfied_mutex;


int main() {
    srand(time(NULL));

    for (int i = 0; i < NUM_SHOPS; i++) {
        shops[i].capacity = rand() % SHOP_CAPACITY;
        pthread_mutex_init(&shops[i].mutex, NULL);
    }

    pthread_mutex_init(&customers_satisfied_mutex, NULL);

    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        customer_needs[i] = rand() % 100000;
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&customers[i], NULL, customer_thread, id);
    }

    pthread_create(&loader, NULL, loader_thread, NULL);

    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        pthread_join(customers[i], NULL);
    }

    pthread_cancel(loader);
    pthread_join(loader, NULL);

    for (int i = 0; i < NUM_SHOPS; i++) {
        pthread_mutex_destroy(&shops[i].mutex);
    }

    pthread_mutex_destroy(&customers_satisfied_mutex);

    printf("Программа завершена.\n");
    return 0;
}
