
#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#define M 10
struct abonent {
    char name[M];
    char second_name[M];
    char tel[M];
};

void print_abonent(struct abonent ab, int i);
void initialize_abonent(struct abonent* ab);
void fill_field(struct abonent* ab, char* mas, char* field);
void delete_abonent(struct abonent** ab, int* counter_ab, int id);

#endif

