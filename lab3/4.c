#include <stdio.h>
#define MAX 500
#include <string.h>
int main()
{
    char mas1[MAX], mas2[MAX];
    char* ptr;
    printf("Введите строку: ");
    fgets(mas1, MAX, stdin);
    printf("Введите подстроку: ");
    fgets(mas2, MAX, stdin);
    ptr = mas1;
    int n = 0, count2 = 0, flag = 0;
    while (*ptr != NULL) {
        if (*ptr == mas2[count2]) {
            count2++;
            n++;
            ptr++;
            if (mas2[n] == NULL) {
                break;
            }
        }
        else {
            ptr = ptr - n + 1;
            n = 0;
            count2 = 0;
        }
        if (count2 + 1 == strlen(mas2)) {
            ptr = ptr - count2;
            flag = 1;
            break;
        }
    }
    if (flag == 1) {
        printf("Подстрока есть такая вод ее ячейка в памяти: %p\n ", ptr);
    }
    else {
        printf("Подстрока не нашлась в строке(значение указателя) : %s\n ", *ptr);
        printf("Подстрока не нашлась в строке(ячейка в памяти) : %p\n ", ptr);
    }

    return 0;
}