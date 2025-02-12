#include "abonent.h"

int main() {
    Abonent* head = NULL;
    Abonent* tail = NULL;
    int key, id;

    while (1) {
        printf("Выберите команду (1-5):\n1) Добавить абонента\n2) Удалить абонента\n3) Поиск абонентов по имени\n4) Вывод всех записей\n5) Выход\nВыбранная команда: ");
        if (scanf("%d", &key) != 1) {
            printf("Некорректный ввод. Попробуйте еще раз.\n");
            while (getchar() != '\n'); 
            continue;
        }
        while (getchar() != '\n'); 

        switch (key) {
        case 1:
            add_abonent(&head, &tail);
            break;
        case 2:
            printf("Введите id абонента: ");
            if (scanf("%d", &id) != 1) {
                printf("Некорректный id. Попробуйте еще раз.\n");
                while (getchar() != '\n'); 
                continue;
            }
            while (getchar() != '\n'); 
            delete_abonent(&head, &tail, id);
            break;
        case 3:
            search_abonent(head);
            break;
        case 4:
            print_all_abonents(head);
            break;
        case 5:
            return 0;
        default:
            printf("Неправильная команда. Попробуйте еще раз.\n");
            break;
        }
    }

    return 0;
}