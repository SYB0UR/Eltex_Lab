#include <stdio.h>

#define N 5

int main(){
    int mas[N];
    for (int i = 0; i != N; i++){
        mas[i]=i+1;
        
    }
    printf("Массив до:\n");
    for (int i; i != N; i++){
        printf("%d ",mas[i]);
    }
    printf("\nМассив после:\n");
    
    int n = N - 1 , m = 0, k;
    while (n - m >= 1)
    {
        k = mas[n];
        mas[n] = mas[m];
        mas[m] = k;
        m++;
        n--;
    }
    for (int i; i != N; i++){
        printf("%d ",mas[i]);
    }
    return 0;
}