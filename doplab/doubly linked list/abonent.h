#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 10

typedef struct Abonent {
    char name[M];
    char second_name[M];
    char tel[M];
    struct Abonent* prev;
    struct Abonent* next;
} Abonent;

void print_abonent(Abonent* ab, int id);
Abonent* create_abonent();
void fill_field(Abonent* ab, const char* field_name);
void add_abonent(Abonent** head, Abonent** tail);
void delete_abonent(Abonent** head, Abonent** tail, int id);
void search_abonent(Abonent* head);
void print_all_abonents(Abonent* head);