#ifndef GUIAO2_H
#define GUIAO2_H
#pragma once

/**
\file guiao2.h
\brief Funções relativas ao guião 2
*/


/**
 * @brief Função que roda os três elementos do topo da stack
 * 
 * @param stack stack na qual as posições de três elementos serão alteradas
 */
void roda_3(STACK *stack);


/**
 * @brief Função que duplica o elemento do topo da stack
 * 
 * @param stack stack na qual será colocado um elemento exatamente igual ao anterior
 */
void duplica(STACK *stack);


/**
 * @brief Esta função faz simplesmento pop
 * 
 * @param stack stack a partir da qual será extraido um elemento
 */
void pop_operador(STACK *stack);


/**
 * @brief Função que troca os dois elementos do topo da stack
 * 
 * @param stack stack na qual os dois ultimo elementos irão trocar de posição
 */
void troca(STACK *stack);


/**
 * @brief Esta função copia n-ésimo elemento para o topo da stack
 * 
 * @param stack stack a partir da qual será copiado um elemento de uma certa posição para o topo da mesma stack
 * @param var_list stack auxiliar que guarda variaveis
 * @param sp_lista array que contem varios stack pointers
 * @param N elemento que indica o valor do stack pointer
 */
void copia_nesimo(STACK *stack, VAR_LIST *var_list, int sp_lista[], int *N);


/**
 * @brief Converte o elemento do topo da stack em int
 * 
 * @param stack stack em que o seu elemento do topo será convertido para int
 */
void converte_int(STACK *stack);


/**
 * @brief Converte o elemento do topo da stack em char
 * 
 * @param stack stack em que o seu elemento do topo será convertido para char
 */
void converte_char(STACK *stack);


/**
 * @brief Converte o elemento do topo da stack em double
 * 
 * @param stack stack em que o seu elemento do topo será convertido para double
 */
void converte_double(STACK *stack);


/**
 * @brief Converte o elemento do topo da stack em string
 * 
 * @param stack stack em que o seu elemento do topo será convertido para char*
 */
void converte_string(STACK *stack);


/**
 * @brief Esta função é utilizada na main para dar print de um ELEMENT
 * 
 * @param e apontador para o elemento que se pretende representar no terminal 
 */
void print_element(ELEMENT* e);


/**
 * @brief Este função permite ler mais do que uma linha no termina
 * 
 * @param stack stack na qual será colocada a string resultante da leitura feita no terminal 
 */
void pede_linha(STACK *stack);


/**
 * @brief Esta função faz print de uma stack
 * 
 * @param stack stack que será totalmente representado no terminal 
 */
void print_stack(STACK *stack);

#endif