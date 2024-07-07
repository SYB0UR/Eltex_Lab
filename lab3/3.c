#include <stdio.h>

int main()
{
    int mas[10];
    int* ptr;
    for (int i = 0; i != 10; i++) {
        mas[i] = i + 1;
    }
    ptr = mas;
    for (int i = 0; i != 10; i++) {
        printf("mas[%d] = %d\n", i, *ptr);
        ptr++;
    }
    return 0;
}