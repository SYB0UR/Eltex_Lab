#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

#define TABLE_SIZE 10

unsigned int hash(char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % TABLE_SIZE;
}

char* my_strdup(const char* str) {
    char* copy = (char*)malloc(strlen(str) + 1);
    if (copy) {
        strcpy(copy, str);
    }
    return copy;
}

HashTable* create_table() {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (table == NULL) {
        fprintf(stderr, "Ошибка: недостаточно памяти для создания таблицы.\n");
        exit(1);
    }
    table->items = (HashItem**)calloc(TABLE_SIZE, sizeof(HashItem*));
    if (table->items == NULL) {
        fprintf(stderr, "Ошибка: недостаточно памяти для инициализации элементов таблицы.\n");
        free(table);
        exit(1);
    }
    return table;
}

void insert(HashTable* table, char* key, char* value) {
    unsigned int index = hash(key);
    HashItem* newItem = (HashItem*)malloc(sizeof(HashItem));
    if (newItem == NULL) {
        fprintf(stderr, "Ошибка: недостаточно памяти для создания нового элемента.\n");
        exit(1);
    }
    newItem->key = my_strdup(key);
    newItem->value = my_strdup(value);
    newItem->next = NULL;

    if (newItem->key == NULL || newItem->value == NULL) {
        fprintf(stderr, "Ошибка: недостаточно памяти для дублирования ключа или значения.\n");
        free(newItem);
        exit(1);
    }

    HashItem* current = table->items[index];
    if (current == NULL) {
        table->items[index] = newItem;
    } else {
        newItem->next = current;
        table->items[index] = newItem;
    }
}

char* get(HashTable* table, char* key) {
    unsigned int index = hash(key);
    HashItem* current = table->items[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void delete(HashTable* table, char* key) {
    unsigned int index = hash(key);
    HashItem* current = table->items[index];
    HashItem* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                table->items[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->key);
            free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void free_table(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        HashItem* current = table->items[i];
        while (current != NULL) {
            HashItem* temp = current;
            current = current->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free(table->items);
    free(table);
}

void print_table(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        printf("Ячейка %d: ", i);
        HashItem* current = table->items[i];
        while (current != NULL) {
            printf("-> [ключ: %s, значение: %s] ", current->key, current->value);
            current = current->next;
        }
        printf("\n");
    }
}