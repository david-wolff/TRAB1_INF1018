#ifndef BIGINT_H
#define BIGINT_H

#define NUM_BITS 128

typedef unsigned char BigInt[NUM_BITS / 8];

// Atribuindo o valor de um signed long extendido para big. 
void big_val(BigInt res, long val);

/* Operações Aritméticas */

// Atribuindo o valor "negado" complemento a 2 de um inteiro de 128 bits "a".
void big_comp2(BigInt res, BigInt a);

//Soma de dois inteiros (a e b) de 128 bits.
void big_sum(BigInt res, BigInt a, BigInt b);

//Subtração entre dois inteiros (a e b) de 128 bits.
void big_sub(BigInt res, BigInt a, BigInt b);

//Multiplicação de dois inteiros (a e b) de 128 bits.
void big_mul(BigInt res, BigInt a, BigInt b);

/* Operações de Deslocamento */

// Left shift lógico de n bits no inteiro de 128 bits "a". 
void big_shl(BigInt res, BigInt a, int n);

// Right shift lógico de n bits no inteiro de 128 bits "a". 
void big_shr(BigInt res, BigInt a, int n);

// Right shift aritmético de n bits no inteiro de 128 bits a. 
void big_sar(BigInt res, BigInt a, int n);

#endif
