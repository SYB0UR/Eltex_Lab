#include"lab11_3.h"


/**
 * Функция потока покупателя.
 * @param arg Указатель на идентификатор покупателя.
 * @return NULL
 *
 * Покупатель выбирает случайный магазин, уменьшает свою потребность на количество товаров в магазине,
 * засыпает на 2 секунды и повторяет процесс, пока его потребность не станет <= 0.
 */
void* customer_thread(void* arg) {
    int id = *((int*)arg);
    while (customer_needs[id] > 0) {
        int shop_index = rand() % NUM_SHOPS;
        if (pthread_mutex_trylock(&shops[shop_index].mutex) == 0) {
            int purchase_amount = (customer_needs[id] < shops[shop_index].capacity) ? customer_needs[id] : shops[shop_index].capacity;
            printf("Я покупатель %d, зашел в магазин %d, там было %d, мне надо %d. Заснул\n", id, shop_index, shops[shop_index].capacity, customer_needs[id]);
            customer_needs[id] -= purchase_amount;
            shops[shop_index].capacity -= purchase_amount;
            pthread_mutex_unlock(&shops[shop_index].mutex);
            sleep(2);
        }
    }
    pthread_mutex_lock(&customers_satisfied_mutex);
    customers_satisfied++;
    pthread_mutex_unlock(&customers_satisfied_mutex);
    printf("Покупатель %d завершил свою работу.\n", id);
    return NULL;
}
/**
 * Функция потока грузчика.
 * @return NULL
 *
 * Грузчик проверяет магазины и добавляет товары, если их количество меньше максимальной вместимости.
 * Засыпает на 1 секунду после каждой загрузки.
 */
void* loader_thread() {
    while (1) {
        pthread_mutex_lock(&customers_satisfied_mutex);
        if (customers_satisfied == NUM_CUSTOMERS) {
            pthread_mutex_unlock(&customers_satisfied_mutex);
            break;
        }
        pthread_mutex_unlock(&customers_satisfied_mutex);

        for (int i = 0; i < NUM_SHOPS; i++) {
            if (pthread_mutex_trylock(&shops[i].mutex) == 0) {
                if (shops[i].capacity < SHOP_CAPACITY) {
                    int load_amount = (shops[i].capacity + LOADER_CAPACITY > SHOP_CAPACITY) ? (SHOP_CAPACITY - shops[i].capacity) : LOADER_CAPACITY;
                    printf("Я грузчик, зашел в магазин %d, там было %d, я положил %d. Заснул\n", i, shops[i].capacity, load_amount);
                    shops[i].capacity += load_amount;
                    pthread_mutex_unlock(&shops[i].mutex);
                    sleep(1);
                } else {
                    pthread_mutex_unlock(&shops[i].mutex);
                }
            }
        }
    }
    return NULL;
}
