#include <stdio.h>
#include "bigint.h"

void print_bigint(const char *label, BigInt a) {
    printf("%s: ", label);
    for (int i = NUM_BITS / 8 - 1; i >= 0; i--) {
        printf("%02X", a[i]);
    }
    printf("\n");
}

int main() {
    BigInt a, b, res;

    // Testando big_val
    big_val(a, 1234);
    print_bigint("Valor A (1234)", a);

    big_val(b, -5678);
    print_bigint("Valor B (-5678)", b);

    // Testando big_comp2
    big_comp2(res, a);
    print_bigint("Complemento de dois de A", res);

    big_comp2(res, b);
    print_bigint("Complemento de dois de B", res);

    // Testando big_sum
    big_sum(res, a, b);
    print_bigint("A + B", res);

    // Testando big_sub
    big_sub(res, a, b);
    print_bigint("A - B", res);

    // Testando big_mul
    big_mul(res, a, b);
    print_bigint("A * B", res);

    // Testando big_shl
    big_shl(res, a, 5);
    print_bigint("A << 5", res);

    // Testando big_shr
    big_shr(res, a, 5);
    print_bigint("A >> 5 (lógico)", res);

    // Testando big_sar
    big_sar(res, b, 5);
    print_bigint("B >> 5 (aritmético)", res);

    return 0;
}
