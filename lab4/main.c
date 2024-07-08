/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct abonent {
    char name[10];
    char second_name[10];
    char tel[10];
};

int main()
{
    int key;
    struct abonent ab[100];
    for (int i = 0; i != 100; i++) {
        for (int j = 0; j != 10; j++) {
            ab[i].name[j] = 'a';
            ab[i].second_name[j] = 'b';
            ab[i].tel[j] = '9';
        }

    }
    for (int i = 0; i != 100; i++) {
        printf(" %c", ab[i].name[1]);
        printf("\n");

    }

    while (1) {
        scanf("%d", &key);
        switch (key) {





        case 5:
            exit(1);

        }
    }

    return 0;
}
