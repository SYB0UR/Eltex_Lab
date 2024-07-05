
#include <stdio.h>
#define N 5
int main()
{
    int mas[N][N];
    int k = 1;
    for (int i = 0; i != N; i++) {
        for (int j = 0; j != N; j++) {
            mas[i][j] = 0;
            printf("%d ", mas[i][j]);

        }
        printf("\n");
    }
    int i = 0, j = 0, key = 0;
    while (k < ((N * N) + 1)) {
        if (key == 0) {
            if ((j + 1 != N) && (mas[i][j + 1] == 0) || (k == N * N)) {
                mas[i][j] = k;
                j++;
                k++;
            }
            else {
                key++;
            }
        }

        if (key == 1) {
            if ((i + 1 != N) && (mas[i + 1][j] == 0) || (k == N * N)) {
                mas[i][j] = k;
                i++;
                k++;
            }
            else {
                key++;
            }
        }
        if (key == 2) {
            if ((j - 1 != -1) && (mas[i][j - 1] == 0) || (k == N * N)) {
                mas[i][j] = k;
                j--;
                k++;
            }
            else {
                key++;
            }
        }
        if (key == 3) {
            if ((i - 1 != -1) && (mas[i - 1][j] == 0) || (k == N * N)) {
                mas[i][j] = k;
                i--;
                k++;
            }
            else {
                printf("\n\n\n\n");
                key = 0;
            }
        }

        for (int n1 = 0; n1 != N; n1++) {
            for (int n2 = 0; n2 != N; n2++) {
                printf("%-3d", mas[n1][n2]);
            }
            printf("\n");
        }
        printf("\n");

    }
    return 0;
}
