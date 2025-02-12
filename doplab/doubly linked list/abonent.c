#include "abonent.h"

// ������� ��� ������ ���������� �� ��������
void print_abonent(Abonent* ab, int id) {
    printf("\nId: %d", id);
    printf("\n���:     %s", ab->name);
    printf("\n�������: %s", ab->second_name);
    printf("\n�������: %s\n", ab->tel);
}

// ������� ��� �������� ������ ��������
Abonent* create_abonent() {
    Abonent* new_ab = (Abonent*)malloc(sizeof(Abonent));
    memset(new_ab->name, '\0', M);
    memset(new_ab->second_name, '\0', M);
    memset(new_ab->tel, '\0', M);
    new_ab->prev = NULL;
    new_ab->next = NULL;
    return new_ab;
}

// ������� ��� ���������� ����� ��������
void fill_field(Abonent* ab, const char* field_name) {
    printf("������� %s (�������� %d ��������): ", field_name, M - 1);
    char input[M + 100] = { 0 };
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = '\0';
    if (strlen(input) >= M) {
        printf("��������� ������ ��������� ���������� ����� � ����� �������� �� %d ��������.\n", M - 1);
    }

    if (strcmp(field_name, "���") == 0) {
        strncpy(ab->name, input, M - 1);
        ab->name[M - 1] = '\0';
    }
    else if (strcmp(field_name, "�������") == 0) {
        strncpy(ab->second_name, input, M - 1);
        ab->second_name[M - 1] = '\0';
    }
    else if (strcmp(field_name, "�������") == 0) {
        strncpy(ab->tel, input, M - 1);
        ab->tel[M - 1] = '\0';
    }
}

// ������� ��� ���������� ������ �������� � ������
void add_abonent(Abonent** head, Abonent** tail) {
    Abonent* new_ab = create_abonent();
    fill_field(new_ab, "���");
    fill_field(new_ab, "�������");
    fill_field(new_ab, "�������");

    if (*head == NULL) {
        *head = new_ab;
        *tail = new_ab;
    }
    else {
        new_ab->prev = *tail;
        (*tail)->next = new_ab;
        *tail = new_ab;
    }
}

// ������� ��� �������� �������� �� id
void delete_abonent(Abonent** head, Abonent** tail, int id) {
    Abonent* current = *head;
    int count = 0;

    while (current != NULL) {
        if (count == id) {
            if (current->prev) {
                current->prev->next = current->next;
            }
            else {
                *head = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            }
            else {
                *tail = current->prev;
            }
            free(current);
            return;
        }
        current = current->next;
        count++;
    }
    printf("�������� id\n");
}

// ������� ��� ������ ��������� �� �����
void search_abonent(Abonent* head) {
    char name[M];
    printf("������� ��� ��� ������: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    Abonent* current = head;
    int id = 0, found = 0;
    while (current != NULL) {
        if (strncmp(current->name, name, M) == 0) {
            print_abonent(current, id);
            found = 1;
        }
        current = current->next;
        id++;
    }

    if (!found) {
        printf("�������� � ������ '%s' �� �������.\n", name);
    }
}

// ������� ��� ������ ���� ���������
void print_all_abonents(Abonent* head) {
    Abonent* current = head;
    int id = 0;

    while (current != NULL) {
        print_abonent(current, id);
        current = current->next;
        id++;
    }
}