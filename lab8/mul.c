#include "libcalc.h"
int mul(int a, int b) {
    int result = 0;
    int sign = 1;
    if (a < 0) {
        a = -a;
        sign = -sign;
    }
    if (b < 0) {
        b = -b;
        sign = -sign;
    }
    for (int i = 0; i < b; i++) {
        result = add(result, a);
    }
    return result * sign;
}
