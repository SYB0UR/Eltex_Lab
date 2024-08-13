#include "libcalc.h"
int div(int dividend, int divisor) {
    if (divisor == 0) {
        printf("Ошибка: деление на ноль!\n");
        return -1;
    }

    int sign = 1;
    if ((dividend < 0) ^ (divisor < 0)) {
        sign = -1;
    }

    dividend = dividend < 0 ? -dividend : dividend;
    divisor = divisor < 0 ? -divisor : divisor;

    int quotient = 0;
    while (dividend >= divisor) {
        dividend = sub(dividend, divisor);
        quotient = add(quotient, 1);
    }

    return sign * quotient;
}
