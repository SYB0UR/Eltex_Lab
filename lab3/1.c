#include <stdio.h>

int main()
{
    int number, newByte, i = 0;
    char* ptr;
    while (number <= 0) {
        if (i > 0) {
            printf("Вы ввели не положительное число \n");
        }
        printf("Введите целое положительное число: ");
        scanf("%d", &number);
        i++;
    }
    i = 0;
    ptr = (char*)&number;

    while (newByte <= 0 || newByte > 255) {
        if (i > 0) {
            printf("Вы ввели число не из допустимой области\n");
        }
        printf("Введите число из данной области чтобы заменить им 3 байт(0-255): ");
        scanf("%d", &newByte);
        i++;
    }

    ptr = ptr + 2;
    *ptr = newByte;
    printf("Измененное число: %d\n", number);
    return 0;
}