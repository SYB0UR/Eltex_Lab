#include "abonent.h"

int main() {
    Abonent* head = NULL;
    Abonent* tail = NULL;
    int key, id;

    while (1) {
        printf("�������� ������� (1-5):\n1) �������� ��������\n2) ������� ��������\n3) ����� ��������� �� �����\n4) ����� ���� �������\n5) �����\n��������� �������: ");
        if (scanf("%d", &key) != 1) {
            printf("������������ ����. ���������� ��� ���.\n");
            while (getchar() != '\n'); 
            continue;
        }
        while (getchar() != '\n'); 

        switch (key) {
        case 1:
            add_abonent(&head, &tail);
            break;
        case 2:
            printf("������� id ��������: ");
            if (scanf("%d", &id) != 1) {
                printf("������������ id. ���������� ��� ���.\n");
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
            printf("������������ �������. ���������� ��� ���.\n");
            break;
        }
    }

    return 0;
}