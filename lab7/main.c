#include "libcalc.h"

void input(int* a, int* b) {
    printf("Введите 2 целых числа\n");
        while (scanf("%d%d", a, b) != 2) {
            printf("Ведите 2 целых числа\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
            }
        }
}


int main() {
    int key = 0;
    int a,b;
    while (key != 5) {
        printf("Выберите комманду(1-5):\n1) Сложение\n2) Вычитание\n3) Умножение\n4) Деление\n5) Выход\nВыбранная комаанда: ");
        if (scanf("%d", &key) != 1) {
            printf("error input");
            key = 5;
        }
        switch (key) {
            case 1:
                input(&a, &b);
                printf("Результат = %d\n", add(a, b));
                break;
            case 2:
                input(&a, &b);
                printf("Результат = %d\n", sub(a, b));
                break;
            case 3:
                input(&a, &b);
                printf("Результат = %d\n", mul(a, b));
                break;
            case 4:
                input(&a, &b);
                printf("Результат = %d\n", div(a, b));
                break;
            case 5:
                break;
        }
    }

    return 0;
}
