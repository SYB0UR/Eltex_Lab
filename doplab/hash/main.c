#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

int main() {
    HashTable* table = create_table();

    insert(table, "ключ1", "значение1");
    insert(table, "ключ2", "значение2");

    insert(table, "key1", "value1");
    insert(table, "key2", "value2");
    insert(table, "key3", "value3");

    print_table(table);

    char* value1 = get(table, "ключ1");
    if (value1 != NULL) {
        printf("%s\n", value1); 
    } else {
        printf("Ключ ключ1 не найден\n");
    }

    char* value2 = get(table, "ключ2");
    if (value2 != NULL) {
        printf("%s\n", value2);
    } else {
        printf("Ключ ключ2 не найден\n");
    }

    delete(table, "ключ1");

    value1 = get(table, "ключ1");
    if (value1 != NULL) {
        printf("%s\n", value1);
    } else {
        printf("Ключ ключ1 не найден\n");
    }

    print_table(table);

    free_table(table);

    return 0;
}