#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char *str = "String from file";
    char ch;
    int len;

    file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Ошибка при открытии файла!\n");
        return 1;
    }
    fprintf(file, "%s", str);
    fclose(file);
    file = fopen("output.txt", "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла!\n");
        return 1;
    }
    fseek(file, 0, SEEK_END);
    len = ftell(file);
    for (int i = 1; i <= len; i++) {
        fseek(file, -i, SEEK_END);
        ch = fgetc(file);
        putchar(ch);
    }
    putchar('\n');

    fclose(file);
    return 0;
}
