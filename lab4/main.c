#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#define N 100
#define M 10

struct abonent {
    char name[M];
    char second_name[M];
    char tel[M];
};

int main()
{
    int key  = 0;
    struct abonent ab[N];
    for (int i = 0; i != N; i++) {
        for (int j = 0; j != M; j++) {
            ab[i].name[j] = '0';
            ab[i].second_name[j] = '0';
            ab[i].tel[j] = '0';
        }

    }
    char mas[M];
    int n1,n2,n3,k;
    while (1) {
        printf("Выберите комманду(1-5):\n1) Добавить абонента\n2) Удалить абонента\n3) Поиск абонентов по имени\n4) Вывод всех записей\n5) Выход\nВыбранная комаанда: ");
        if (scanf("%d", &key) != 1){
            printf("error input");
            key = 5;
        }
        switch (key) {
            case 1:
                for (int i = 0; i != N; i++){
                    n1 = 0; n2 = 0; n3 = 0;
                    for(int j = 0; j != M; j++){
                        if (ab[i].name[j] == '0'){
                            n1++;
                        }
                        if (ab[i].second_name[j] == '0'){
                            n2++;
                        }
                        if (ab[i].tel[j] == '0'){
                            n3++;
                        }
                    }
                    if ( n1+n2+n3 == M*3){
                        k = i;
                        break;
                    }
                }
                printf("Введите Имя:     ");
                for(int l = 0; l != M; l++){
                    mas[l] = '0';
                }
                scanf("%s",&mas);
                for (int l = 0; l != M ; l++){
                    ab[k].name[l] = mas[l];
                }
                for(int l = 0; l != M; l++){
                    mas[l] = '0';
                }     
                printf("\nВведите Фамилию: ");
                scanf("%s",&mas);
                for (int l = 0; l != M ; l++){
                    ab[k].second_name[l] = mas[l];
                }
                for(int l = 0; l != M; l++){
                    mas[l] = '0';
                }    
                printf("\nВведите телефон: ");
                scanf("%s",&mas);
                for (int l = 0; l != M ; l++){
                    ab[k].tel[l] = mas[l];
                }    
                break;
            case 2:
                printf("Введите id абонента: ");
                scanf("%d",&k);
                if ((k >= 0) && (k < N) ){
                    for (int i = 0; i != M; i++){
                        ab[k].name[i] = '0';
                        ab[k].second_name[i] = '0';
                        ab[k].tel[i] = '0';
                    }
                }else{
                    printf("Вы ввели недопустимый id");
                }
                break;
            case 3:
                for(int l = 0; l != M; l++){
                    mas[l] = '0';
                }
                printf("\nВведите имя, по которому вести поиск: ");
                scanf("%s",&mas);
                
                for(int i = 0; i != N; i++){
                    n1 = 0;
                    n2 = 0;
                    for (int j = 0; j != M; j++){
                        if (ab[i].name[j] == mas[j]){
                            n1++;
                        }
                        if (n1 == M){
                            n2 = 1;
                        }
                    }
                    if (n2 == 1){
                        printf("\nId: %d",i);
                        printf("\nИмя:     ");
                        for (int j = 0; j != M; j++){
                            printf("%c",ab[i].name[j]);
                        }
                        printf("\nФамилия: ");
                        for (int j = 0; j != M; j++){
                            printf("%c",ab[i].second_name[j]);
                        }
                        printf("\nТелефон: ");
                        for (int j = 0; j != M; j++){
                            printf("%c",ab[i].tel[j]);
                        }
                        printf("\n");
                    }                        
        
                }
                break;
            case 4:    
                printf("Список абонентов: \n");
                for (int i = 0; i != N; i++){
                    printf("\nId: %d",i);
                    printf("\nИмя:     ");
                    for (int j = 0; j != M; j++){
                        printf("%c",ab[i].name[j]);
                    }
                    printf("\nФамилия: ");
                    for (int j = 0; j != M; j++){
                        printf("%c",ab[i].second_name[j]);
                    }
                    printf("\nТелефон: ");
                    for (int j = 0; j != M; j++){
                        printf("%c",ab[i].tel[j]);
                    }
                    printf("\n");
                }
                break;
            case 5:
                exit(1);

            }
    
    }

    return 0;
}
