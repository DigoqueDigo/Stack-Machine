#ifndef GUIAO4_H
#define GUIAO4_H
#pragma once

/**
\file guiao4.h
\brief Funções relativas ao guião 4
*/


/**
 * @brief Esta função dá o tamanho de um array ou string, caso contrario faz range de um elemento
 * 
 * @param stack stack principal
 * @param var_list stack auxiliar que guarda variaveis
 * @param sp_list array que contem varios stack pointers
 * @param N elemento que indica o valor do stack pointer
 */
void operador_virgula(STACK *stack, VAR_LIST *var_list, int sp_lista[], int *N);


/**
 * @brief Coloca uma string dada pelo terminal na stack (apontador para char)
 * 
 * @param stack stack principal
 * @param palavra string que será dada pelo terminal 
 */
void inicializa_string(STACK *stack, char *palavra);


/**
 * @brief Esta função permite tirar o caracter '"' de uma string
 * 
 * @param frase string com o caractere '"'
 * @param string string já sem o caractere '"'
 */
void constroi_string(char *frase, char *string);


/**
 * @brief Faz push dos elementos desde uma determinada possição da stack para um ELEMENT de tipo ARRAY
 * 
 * @param stack
 * @param sp_list array que contem varios stack pointers
 * @param N elemento que indica o valor do stack pointer
 */
void push_to_array(STACK *stack, int sp_lista[], int *N);


/**
 * @brief Replicação de uma string
 * 
 * @param string string que será replicada
 * @param N quantidade de replicas que serão feitas
 * @return string já replicada
 */
char* replica_string(char *string, int N);


/**
 * @brief Converte o coneudo de um ELEMENT para uma string
 * 
 * @param x ELEMENT que contem uma string 
 * @return retorna sempre 0
 */
int passa_string(ELEMENT* x);


/**
 * @brief Concatena dois elementos, sendo que um deles é uma string
 * 
 * @param x elemento para o qual será passada a string concatenada 
 * @param y elemento que contem a outra string que será concatenada
 */
void concat_string(ELEMENT* x, ELEMENT* y);


/**
 * @brief Devolve o caracter de uma string num certo indice
 * 
 * @param x ELEMNT que contem um string 
 * @param N indice que será utilizado para obter o caractere 
 */
void string_indice(ELEMENT *x, int N);


/**
 * @brief Operador para string, remove primeiro
 * 
 * @param stack stack principal
 * @param x ELEMENT que contem um string e cujo primeiro caractere será removido
 */
void remove_primeiro_string(STACK *stack, ELEMENT *x);


/**
 * @brief Operador para string, remove ultimo
 * 
 * @param stack stack principal
 * @param x ELEMENT que contem um string e cujo ultimo caractere será removido
 */
void remove_ultimo_string(STACK *stack, ELEMENT *x);


/**
 * @brief Operador < para string, captuda N char do inicio
 * 
 * @param stack stack principal
 * @param x ELEMENT que contem uma string
 * @param N numero de caracteres iniciais que a string passará a ter 
 */
void captuda_incio(STACK *stack, ELEMENT *x, int N);


/**
 * @brief Operador > para string, captura N char do fim
 * 
 * @param stack stack principal
 * @param x ELEMENT que contem uma string
 * @param N numero de caracteres finais que a string passará a ter 
 */
void captuda_fim(STACK *stack, ELEMENT *x, int N);


/**
 * @brief Procura substring na string e devolve o indice onde ela começa, caso contrário devolve -1
 * 
 * @param frase string principal
 * @param substring substring que será utilizada para ver se verifica à string principal
 * @return retorna -1 se a substring não pertence à string, caso contrário retorna o indice onde esta se inicia 
 */
int substring_indice(char *frase, char *substring);


/**
 * @brief Coloca um dado pelo terminal na stack
 * 
 * @param stack stack principal
 * @param sp_list array que contem varios stack pointers
 * @param N elemento que indica o valor do stack pointer
 */
void inicializa_array(STACK* stack, int sp_lista[], int *N);


/**
 * @brief Função que serve para concatenar arrays com array ou um elemento com um array
 * 
 * @param stack stack principal
 * @param x ELEMENT para o qual passará o resultado da concatencação 
 * @param y ELEMENT que será concatenda ao x
 */
void concat_array(STACK *stack, ELEMENT *x, ELEMENT *y);


/**
 * @brief Função que dcrementa as posições de um array
 * 
 * @param x ELEMENT cujo conteudo será alterado 
 */
void puxa_frente(ELEMENT *x);


/**
 * @brief Função que incrementa as posições de um array
 * 
 * @param x ELEMENT cujo conteudo será alterado
 */
void puxa_atras(ELEMENT *x);


/**
 * @brief Função que aumenta o tamanho do array
 * 
 * @param stack stack principal
 * @param x ELEMENT que será replicado 
 * @param N número de vezes que o array será replicado
 */
void replica_array(STACK *stack, ELEMENT *x, int N);


/**
 * @brief Dado um array esta função remove o primeiro elemento do array e coloca os dois na stack
 * 
 * @param stack stack principal 
 * @param x ELEMENT cujo primeiro elemento será removido
 */
void remove_primeiro_array(STACK *stack, ELEMENT *x);


/**
 * @brief Dado um array esta função remove o ultimo elemento do array e coloca os dois na stack
 * 
 * @param stack stack principal 
 * @param x ELEMENT cujo ultimo elemento será removido 
 */
void remove_ultimo_array(STACK *stack, ELEMENT *x);


/**
 * @brief Dado um array e um interiro esta função devolve o elemento que está no indice do inteiro
 * 
 * @param stack stack principal 
 * @param x ELEMENT no qual será pesquisado um indice
 * @param N indice que será utilizado na procura
 */
void array_indice(STACK *stack, ELEMENT *x, int N);


/**
 * @brief Esta função remove todos os elementos do array e coloca-os na stack
 * 
 * @param stack stack principal
 * @param x ELEMENT que do qual serão extraidos os elementos e colocados na stack principal
 */
void push_array_to_stack(STACK *stack, ELEMENT *x);


/**
 * @brief Dado um inteiro e um array esta função remove todos os elementos a partir do indice do inteiro
 * 
 * @param stack stack principal 
 * @param x ELEMENT cujo conteudo será alterado 
 * @param N nmero de elementos iniciais que serão mantidos no array  
 */
void captura_inicio_array(STACK *stack, ELEMENT *x, int N);


/**
 * @brief Dado um inteiro e um array esta função remove todos os elementos a partir do indice do inteiro do numero de elementos do array menos o indice
 * 
 * @param stack stack principal 
 * @param x ELEMENT cujo conteudo será alterado 
 * @param N nmero de elementos finais que serão mantidos no array  
 */
void captura_fim_array(STACK *stack, ELEMENT *x, int N);


/**
 * @brief Operador t (lê todo o input)
 * 
 * @param stack stack principal e na qual será colocado o conteudo na leitura
 */
void read_all_input(STACK *stack);


/**
 * @brief Operador que separa string por withespace (é sabido que o elemento ao qual é dado pop é uma string)
 * 
 * @param stack stack principal e na qual será colocado o conteudo na leitura
 */
void whitespace(STACK *stack);


/**
 * @brief Operador que separa uma string por substring (é sabido que os dois elementos aos quais é dado pop são string's)
 * 
 * @param stack stack principal e na qual será colocado o array que contem as varias sunstrings
 * @param x stirng completa e que será dividida em substrings
 * @param y elemento que contem a substring utilizada na divisao da string do elemento x
 */
void separa_substring(STACK *stack, ELEMENT *x, ELEMENT *y);


/**
 * @brief Operador que separa uma string por newlines (é sabido que o elemento ao qual é dado pop é uma string)
 * 
 * @param stack stack principal e na qual será colocado o conteudo na leitura
 */
void new_lines(STACK *stack);

#endif