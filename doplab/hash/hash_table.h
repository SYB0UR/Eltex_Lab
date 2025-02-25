#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef struct HashItem {
    char* key;
    char* value;
    struct HashItem* next;
} HashItem;

typedef struct {
    HashItem** items;
} HashTable;

HashTable* create_table();
void insert(HashTable* table, char* key, char* value);
char* get(HashTable* table, char* key);
void delete(HashTable* table, char* key);
void free_table(HashTable* table);
void print_table(HashTable* table);

#endif 