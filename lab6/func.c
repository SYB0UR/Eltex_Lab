#include "func.h"
void print_abonent(struct abonent ab, int i) {
    printf("\nId: %d", i);
    printf("\nИмя:     ");
    for (int j = 0; j != M; j++) {
        printf("%c", ab.name[j]);
    }
    printf("\nФамилия: ");
    for (int j = 0; j != M; j++) {
        printf("%c", ab.second_name[j]);
    }
    printf("\nТелефон: ");
    for (int j = 0; j != M; j++) {
        printf("%c", ab.tel[j]);
    }
    printf("\n");
}


void initialize_abonent(struct abonent* ab) {
    for (int j = 0; j != M; j++) {
        ab->name[j] = '0';
        ab->second_name[j] = '0';
        ab->tel[j] = '0';
    }
}

void fill_field(struct abonent* ab, char* mas, char* field) {
    printf("Введите %s: ", field);
    for (int l = 0; l != M; l++) {
        mas[l] = '0';
    }
    scanf("%s", mas);
    if (strcmp(field, "Имя") == 0) {
        for (int l = 0; l != M; l++) {
            ab->name[l] = mas[l];
        }
    } else if (strcmp(field, "Фамилию") == 0) {
        for (int l = 0; l != M; l++) {
            ab->second_name[l] = mas[l];
        }
    } else if (strcmp(field, "телефон") == 0) {
        for (int l = 0; l != M; l++) {
            ab->tel[l] = mas[l];
        }
    }
}



void delete_abonent(struct abonent** ab, int* counter_ab, int id) {
    if (id < 0 || id >= *counter_ab) {
        printf("Вы ввели недопустимый id\n");
        return;
    }
    for (int i = id; i < (*counter_ab - 1); i++) {
        (*ab)[i] = (*ab)[i + 1];
    }
    (*counter_ab)--;
    *ab = (struct abonent*)realloc(*ab, (*counter_ab) * sizeof(struct abonent));
    if (*ab == NULL && *counter_ab > 0) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
}

