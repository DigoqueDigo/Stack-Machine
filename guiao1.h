#ifndef GUIAO1_H
#define GUIAO1_H
#pragma once

/**
\file guiao1.h
\brief Funções relativas ao guião 1
*/


/**
 * @brief Soma de dois elementos da stack
 * 
 * @param pointer stack na qual será colocado o resultado da soma de dois elementos 
 */
void soma(STACK *pointer);


/**
 * @brief Subtração de dois elementos da stack
 * 
 * @param pointer stack na qual será colocado o resultado da subtração de dois elementos 
 */
void sub(STACK *pointer);


/**
 * @brief Multiplicação de dois elementos da stack
 * 
 * @param pointer stack na qual será colocado o resultado da multiplicação de dois elementos
 * @param var_list stack auxiliar que guarda variaveis
 * @param sp_lista array que contem varios stack pointers
 * @param N elemento que indica o valor do stack pointer
 */
void mult(STACK *pointer, VAR_LIST *var_list, int sp_lista[], int *N);


/**
 * @brief Divisão de dois elementos da stack
 * 
 * @param pointer stack na qual será colocado o resultado da divisão de dois elementos
 */
void divsao(STACK *pointer);


/**
 * @brief Incrementa um valor da stack
 * 
 * @param pointer stack na qual será colocado o elemento já incrementado 
 */
void incrementa(STACK *pointer);


/**
 * @brief Decrementa um valor da stack
 * 
 * @param pointer stack na qual será colocado o elemento já decrementado 
 */
void decrementa(STACK *pointer);


/**
 * @brief Exponencial
 * 
 * @param pointer stack na qual será colocado o elemento resultante da exponenciação de um elemento por outro 
 */
void exponencial(STACK *pointer);


/**
 * @brief Resto da divisão
 * 
 * @param pointer stack na qual será colocado o resultado do resto da divisão de dois elementos
 * @param var_list stack auxiliar que guarda variaveis
 * @param sp_lista array que contem varios stack pointers
 * @param N elemento que indica o valor do stack pointer
 */
void restdiv(STACK *pointer, VAR_LIST *var_list, int sp_lista[], int *N);


/**
 * @brief Operador de conjunção (bitwise)
 * 
 * @param stack stack na qual será será colocado o elemento resultado da conjunção de dois elementos
 */
void conjuncao(STACK *stack);


/**
 * @brief Operador de disjunção (bitwise)
 * 
 * @param stack na qual será será colocado o elemento resultado da disjunção de dois elementos
 */
void disjuncao(STACK *stack);


/**
 * @brief Operador xor (bitwise)
 * 
 * @param stack na qual será será colocado o elemento resultado do xor de dois elementos 
 */
void xor(STACK *stack);


/**
 * @brief Negação
 * 
 * @param stack stack na qual será colocado a negação de um elemento
 * @param var_list stack auxiliar que guarda variaveis
 * @param sp_lista array que contem varios stack pointers
 * @param N elemento que indica o valor do stack pointer
 */
void negacao(STACK *stack, VAR_LIST *var_list, int sp_lista[], int *N);

#endif