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



int main() {
    int key = 0;
    int counter_ab = 0;
    
    struct abonent* ab = (struct abonent*)malloc(counter_ab * sizeof(struct abonent));
    if (ab == NULL) {
        printf("Ошибка выделения памяти\n");
        return 1;
    }

    char mas[M];
    int n1, n2, k;
    while (1) {
        printf("Выберите комманду(1-5):\n1) Добавить абонента\n2) Удалить абонента\n3) Поиск абонентов по имени\n4) Вывод всех записей\n5) Выход\nВыбранная комаанда: ");
        if (scanf("%d", &key) != 1) {
            printf("error input");
            key = 5;
        }
        switch (key) {
            case 1:
                counter_ab += 1;
                ab = (struct abonent*)realloc(ab, counter_ab * sizeof(struct abonent));
                if (ab == NULL) {
                    printf("Ошибка выделения памяти\n");
                    return 1;
                }
                initialize_abonent(&ab[counter_ab-1]);
                fill_field(&ab[counter_ab-1], mas, "Имя");
                fill_field(&ab[counter_ab-1], mas, "Фамилию");
                fill_field(&ab[counter_ab-1], mas, "телефон");
                
                break;
            case 2:
                printf("Введите id абонента: ");
                scanf("%d", &k);
                delete_abonent(&ab,&counter_ab,k);
                break;
            case 3:
                for (int l = 0; l != M; l++) {
                    mas[l] = '0';
                }
                printf("\nВведите имя, по которому вести поиск: ");
                scanf("%s", mas);
                for (int i = 0; i != counter_ab; i++) {
                    n1 = 0;
                    n2 = 0;
                    for (int j = 0; j != M; j++) {
                        if (ab[i].name[j] == mas[j]) {
                            n1++;
                        }
                        if (n1 == M) {
                            n2 = 1;
                        }
                    }
                    if (n2 == 1) {
                        print_abonent(ab[i], i);
                    }
                }
                break;
            case 4:
                printf("Список абонентов: \n");
                for (int i = 0; i != counter_ab; i++) {
                    print_abonent(ab[i], i);
                }
                break;
            case 5:
                free(ab);
                exit(1);
        }
    }

    return 0;
}
