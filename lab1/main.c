#include <stdio.h>


void printBinary(int num) {
    int size = sizeof(int) * 8;


    for (int i = size - 1; i >= 0; i--) {
        if (num & (1 << i)) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
}

int countOnes(int num) {
    int count = 0;
    while (num) {
        count += num & 1;
        num >>= 1;
    }
    return count;
}
int changeThirdByte(int num, int newValue) {

    int mask = 0xFF << 16; 

    num &= ~mask;
    
    num |= (newValue << 16);
    
    return num;
}

int main() {
    int number;
    int i = 0;
    //1
    printf("1\n");
    while(number <= 0){
        if (i>0){
            printf("Вы ввели не положительное число\n");
        }
        printf("Введите целое положительное число: ");
        scanf("%d", &number);
        i++;
    }
    
    printf("Двоичное представление числа %d: ", number);
    printBinary(number);
    i = 0;
    number = 0;
    
    //2
    printf("2\n");
    while (number >= 0){
        if (i>0){
            printf("Вы ввели не отрицательное число\n"); 
        }
        printf("Введите целое отрицательное число: ");
        scanf("%d", &number);
        i++;
    }
    
    printf("Двоичное представление числа %d: ", number);
    printBinary(number);
    number = 0;
    i = 0;
    
    //3
    printf("3\n");
    while (number <= 0){ 
        if (i > 0) {
            printf("Вы ввели не положительное число\n");
        } 
        printf("Введите целое положительное число: ");
        scanf("%d", &number);
       
        i++;
    }
    
    int ones = countOnes(number);
    printf("Количество единиц в двоичном представлении числа %d: %d\n", number, ones);
    number = 0;
    i=0;
    
    //4
    int newByte;
    printf("4\n");
    while (number <= 0){
        if (i > 0){
            printf("Вы ввели не положительное число\n");
        } 
        printf("Введите целое положительное число: ");
        scanf("%d", &number);
        i++;
    }
    
    i = 0;
    
    while (newByte <= 0 || newByte > 255 ){
        if (i > 0){
            printf("Вы ввели число не из нужного диапозона\n");
        } 
        printf("Введите новое значение для третьего байта (0-255): ");
        scanf("%d", &newByte);
        i++;
    }
    
    int result = changeThirdByte(number, newByte);
    printf("Измененное число: %d\n", result);
    
    return 0;
}
