#include "bigint.h"
#include <string.h>

// Atribuindo o valor de um signed long extendido para big. 
void big_val(BigInt res, long val) {
    memset(res, (val < 0) ? 0xFF : 0, NUM_BITS / 8);
    memcpy(res, &val, sizeof(long));
}
 
// Atribuindo o valor "negado" complemento a 2 de um inteiro de 128 bits "a".
void big_comp2(BigInt res, BigInt a) {
    unsigned char carry = 1;
    for (int i = 0; i < NUM_BITS / 8; i++) {
        res[i] = ~a[i] + carry;
        carry = carry && (res[i] == 0);
    }
}

//Soma de dois inteiros (a e b) de 128 bits.
void big_sum(BigInt res, BigInt a, BigInt b) {
    unsigned short carry = 0;
    for (int i = 0; i < NUM_BITS / 8; i++) {
        unsigned short sum = (unsigned short)a[i] + (unsigned short)b[i] + carry;
        res[i] = (unsigned char)sum;
        carry = sum >> 8;
    }
}

//Subtração entre dois inteiros (a e b) de 128 bits.
void big_sub(BigInt res, BigInt a, BigInt b) {
    BigInt neg_b;
    big_comp2(neg_b, b);
    big_sum(res, a, neg_b);
}

//Multiplicação de dois inteiros (a e b) de 128 bits.
void big_mul(BigInt res, BigInt a, BigInt b) {
    BigInt temp;
    memset(res, 0, NUM_BITS / 8);
    for (int i = 0; i < NUM_BITS; i++) {
        if (b[i / 8] & (1 << (i % 8))) {
            big_shl(temp, a, i);
            big_sum(res, res, temp);
        }
    }
}

// Left shift lógico de n bits no inteiro de 128 bits "a". 
void big_shl(BigInt res, BigInt a, int n) {
    int byte_shift = n / 8;
    int bit_shift = n % 8;

    for (int i = NUM_BITS / 8 - 1; i >= 0; i--) {
        res[i] = 0;
        if (i - byte_shift >= 0) {
            res[i] |= a[i - byte_shift] << bit_shift;
        }
        if (i - byte_shift - 1 >= 0 && bit_shift > 0) {
            res[i] |= a[i - byte_shift - 1] >> (8 - bit_shift);
        }
    }
}

// Right shift lógico de n bits no inteiro de 128 bits "a". 
void big_shr(BigInt res, BigInt a, int n) {
    int byte_shift = n / 8;
    int bit_shift = n % 8;

    for (int i = 0; i < NUM_BITS / 8; i++) {
        res[i] = 0;
        if (i + byte_shift < NUM_BITS / 8) {
            res[i] |= a[i + byte_shift] >> bit_shift;
        }
        if (i + byte_shift + 1 < NUM_BITS / 8 && bit_shift > 0) {
            res[i] |= a[i + byte_shift + 1] << (8 - bit_shift);
        }
    }
}

// Right shift aritmético de n bits no inteiro de 128 bits a. 
void big_sar(BigInt res, BigInt a, int n) {
    int byte_shift = n / 8;
    int bit_shift = n % 8;
    unsigned char sign_bit = a[NUM_BITS / 8 - 1] & 0x80;

    for (int i = 0; i < NUM_BITS / 8; i++) {
        res[i] = (i + byte_shift < NUM_BITS / 8) ? a[i + byte_shift] >> bit_shift : 0;
        if (i + byte_shift + 1 < NUM_BITS / 8 && bit_shift > 0) {
            res[i] |= a[i + byte_shift + 1] << (8 - bit_shift);
        }
    } 

    if (sign_bit) {
        for (int i = NUM_BITS / 8 - 1; i >= NUM_BITS / 8 - byte_shift; i--) {
            res[i] |= 0xFF;
        }
        if (bit_shift > 0) {
            res[NUM_BITS / 8 - byte_shift - 1] |= ((1 << (8 - bit_shift)) - 1) << (8 - bit_shift);
        }
    }
}

