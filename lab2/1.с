#include <stdio.h>
#define M 10000
#define N 15

void printmatrix(int mas[]) {
    int j = 0;
    for (int i =0; i < N*N ;i++){
    if (j == N){
            break;
        }
        printf("%d ",mas[i]);

        if( (i+1) % N == 0 ){
            printf("\n");
            j++;
        } 
    }
    
}
int main(){
    int mas[M];
    for (int i =0; i < M;i++){
        mas[i]=i+1;        
    }
    printmatrix(mas);

    
    return 0;
}