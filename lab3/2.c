#include <stdio.h>
int main(void)
{
    float x = 5.0;
    printf("x = %f, ", x);
    float y = 6.0;
    printf("y = %f\n", y);
    float* xp = &x + 1; // TODO: �������������� ��� ������, � ������ ������ ��������������
    float* yp = &y;
    printf("���������: %f\n", *xp + *yp);
}