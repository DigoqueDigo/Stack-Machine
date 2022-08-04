#ifndef STACK_H
#define STACK_H
#pragma once

/** \mainpage Máquina de Stack
 * 
 * Este projeto consiste, tal como o nome indica, numa máquina de stack, máquina essa que teria 
 * de ser capaz de realizar várias operações e correr diversos programas impostos pelo utilizador.\n
 *
 * A nossa máquina de stack aceita todos os operador impostos nos 5 guiões, tal como diversos tipos
 * de dados e interpretações diferentes dos operadores conforme o elemento que está em determinada
 * posição da stack.\n
 *
 * Apenas não fomos capazes de resolver o guião 5 por completo, contudo temos muito orgulho no trabalho
 * que realizamos ao longo deste último mês.\n\n
 * 
 * Projeto realizado por:\n 
 * :: Diogo Marques\n
 * :: Francisco Afonso\n
 * :: João Moura\n
 * :: João Rodrigues\n\n
 *
 * Universidade do Minho
 */

/**
\file stack.h
\brief Definição de uma stack
*/


/*! \def STACK_SIZE
    \brief Indica a capacidade inicial de uma stack.

    Quando a capacidade da stack já não é suficiente o STACK_SIZE passa para o dobro e assim sucessivamente.
*/
#define STACK_SIZE 1000

/*! \def ARRAY_SIZE
    \brief Indica a capacidade de um array.

    O tamanho de um array é constante, daí a sua capacidade ser tão elevada
*/
#define ARRAY_SIZE 1000000


/*!
 * @brief Enum dos tipos de dados
 * 
 * Indicador do tipo de dado de cada elemento
 */
typedef enum types {
    CHAR, ///< identificador do tipo caractere
    INT, ///< identificador do tipo inteiro
    DOUBLE, ///< identificador do tipo double
    STRING, ///< identificador do tipo string
    ARRAY, ///< identificador do tipo array
    BLOCO ///< identificador do tipo bloco
} TYPE;


/*!
 * @brief Estrutura de um elemento
 * 
 * Forward declaration
 */
struct elemento;


/*!
 * @brief Estrutura de uma stack
 * 
 * Forward declaration
 */
struct stack;


/*!
 * @brief Estrutura que armazena o conteudo de uma variavel
 * 
 * Uma variavel pode ser varios tipos de dados, mas nunca mais de um ao mesmo tempo
 */
typedef union variavel{
    int INT; ///< variável inteira de um union
    double DOUBLE; ///< variável double de um union
    char CHAR; ///< variável char de um union
    char *STRING; ///< variável char* de um union
    char *BLOCO; ///< variavel que idica um bloco no union
    struct stack *ARRAY; ///< variável apontador par stack de um union
}VAR_TIPO;


/*!
 * @brief Estrutura de uma variavel
 * 
 * uma variavel é constituida por um caracter, definida por um tipo e contem um tipo de dado definido pelo tipo
 */
typedef struct var_check{
    char letra; ///< identificador do caracter de uma variável
    VAR_TIPO variavel; ///< elemento correpondente á variável
    TYPE tipo; ///< identificador do tipo de variável
}VAR;


/*!
 * @brief Estrutura de uma lista de variaveis
 * 
 * uma lista de variaveis contem um array de variaveis e um stack pointer que indica o tamanho util do array
 */
typedef struct array_var{
    VAR vetor[40*sizeof(VAR)]; ///< array de variaveis
    int var_sp; ///< stack pointer do array de variáveis
}VAR_LIST;



/*!
 * @brief Estrutura de um elemento do array
 * 
 * um elemento do array é composta por um tipo e o seu respetivo conteudo
 */
typedef struct array_element{
    TYPE type; ///< identificador do tipo de um elemento
    VAR_TIPO bytes; ///< conteudo do elemento em causa
}ARRAY_ELEMENT;


/*!
 * @brief Estrutura de uma list
 * 
 * uma lista é composta por um inteiro que inidica o tamanho util de um array que contem elemento próprios
 */
typedef struct{
    int size; ///< identificador do tamanho
    ARRAY_ELEMENT array[100*sizeof(VAR_TIPO)]; ///< array de elementos
} LIST;


/*!
 * @brief Estrutura do conteudo de um ELEMENT
 * 
 * um ELEMENT pode assumir varios tipos
 */
typedef union elementos {
    long INT; ///< elemento inteiro de um union
    char CHAR; ///< elemento char de um union
    double DOUBLE; ///< elemento double de um union
    char* STRING; ///< elemento char* de um union
    struct stack* ARRAY; ///< elemento apontador de stack de um union
    char *BLOCO; ///< elemento bloco de um union
}BYTES;


/*!
 * @brief Estrutura de um ELEMENT
 * 
 * um ELEMENT é composto por um tipo e o seu respetivo conteudo
 */
typedef struct elemento{
    BYTES bytes; ///< conteudo de um elemento
    TYPE type; ///< tipo de um elemento
} ELEMENT;


/*!
 * @brief Estrutura de uma stack
 * 
 * é na stack que serão guardados, utilizados e removidos os mais diversos elementos
 */
typedef struct stack{
    ELEMENT *stack; ///< apontador para um array de elementos
    int stack_pointer; ///< stack pointer do array de elementos
    int stack_size; ///< capacidade do array de elementos
} STACK;


/**
 * @brief Esta função inicializa uma stack com o stack pointer a zero e uma capacidade maxima de 100 elementos
 * 
 * @return retorna uma stack já inicializada
 */
STACK *new_stack();


/**
 * @brief Esta função coloca um elemento na posição indicada pelo stack pointer
 * 
 * @param pointer stack principal
 * @param element conteudo do elemento que se pretende colocar na stack 
 * @param pointer tipo do elemento que se pretende colocar na stack
 */
void push(STACK *pointer, BYTES element, TYPE type);

/**
 * @brief Esta função devolve o elemento que se encontra no topo da stack
 * 
 * @param s stack principal
 * @return retorna o elemento que estava no topo da stack
 */
ELEMENT pop(STACK *s);


/**
 * @brief Esta função permite manipular a stack
 * 
 * @param pointer stack principal
 * @param token string que contem conteudo aplicavel à stack principal
 * @param var_list stack auxiliar que guarda variaveis
 * @param sp_list array que contem varios stack pointers
 * @param N elemento que indica o valor do stack pointer
 * @return retorna sempre zero
 */
int handle(STACK *pointer, char *token, VAR_LIST *var_list, int sp_lista[], int *N);


/**
 * @brief Esta função permite tirar o caracter '"' de uma string
 * 
 * @param palavra string que contem o caractere '"'
 * @param new string igual à anterior mas sem o caractere '"'
 */
void cria_string(char *palavra, char *new);


/**
 * @brief Dada uma string cujo primeiro caracter é '"' esta função calcula o indice do próximo '"'
 * 
 * @param palavra string que é liga no terminal
 * @param iter indice que será considerado como o inicio da string
 * @return retorna o indice (incrementado) da posição do próximo caractere ' '
 */
int found(char *palavra, int iter);


/**
 * @brief Dada uma string cujo primeiro caracter é '{' esta função calcula o indice do próximo '}'
 * 
 * @param palavra string que é liga no terminal
 * @param iter indice que será considerado como o inicio da string
 * @return retorna o indice (incrementado) da posição do próximo caractere '}'
 */
int found_bloco(char *palavra, int iter);


/**
 * @brief Esta função coloca '\0' no primeiro whitespace de uma string e devolve o seu indice
 * 
 * @param palavra string que é liga no terminal
 * @param iter indice que será considerado como o inicio da string
 * @return retorna o indice (incrementado) da posição do próximo caractere ' ' 
 */
int put_zero(char *palavra, int iter);


/**
 * @brief Esta função identifica um token
 * 
 * @param token string que contem informação acerca de uma operação na stack  
 * @return retorna um inteiro que será utilizado num switch case
 */
int fornece_numero(char *token);


/**
 * @brief Primeira função auxiliar da handle
 * 
 * @param pointer stack principal
 * @param var_list stack auxiliar que guarda variaveis
 * @param sp_list array que contem varios stack pointers
 * @param indice inteiro que indica qual a operação exata a realizar na stack
 * @param N elemento que indica o valor do stack pointer
 * @return retorna sempre zero
 */
int aux_handle_first(STACK *pointer, VAR_LIST *var_list, int sp_lista[], int indice, int *N);


/**
 * @brief Segunda função auxiliar da handle
 * 
 * @param pointer stack principal
 * @param var_list stack auxiliar que guarda variaveis
 * @param indice inteiro que indica qual a operação exata a realizar na stack
 * @return retorna sempre zero
 */
int aux_handle_second(STACK *pointer, VAR_LIST *var_list, int indice);


/**
 * @brief Terceira função auxiliar da handle
 * 
 * @param pointer stack principal
 * @param var_list stack auxiliar que guarda variaveis
 * @param indice inteiro que indica qual a operação exata a realizar na stack
 * @return retorna sempre zero
 */
int aux_handle_third(STACK *pointer, VAR_LIST *var_list, int indice);


/**
 * @brief Quarta função auxiliar da handle
 * 
 * @param pointer stack principal
 * @param token string que contem conteudo aplicavel à stack principal
 * @param var_list stack auxiliar que guarda variaveis
 * @param sp_lista array que contem varios stack pointers
 * @param N elemento que indica o valor do stack pointer
 * @param indice inteiro que indica qual a operação exata a realizar na stack
 * @return retorna sempre zero
 */
int aux_handle_fourth(STACK *pointer, char *token, VAR_LIST *var_list, int sp_lista[], int *N, int indice);


/**
 * @brief Função que dá clone a um array
 * 
 * @param x elemento que será clonado
 * @return retorna uma copia do ELEMENT x
 */
ELEMENT clone(ELEMENT x);

/**
 * @brief função main (serve de entrada para as restantes funções) 
 *
 * @return retorna sempre zero
 */
int main();

#endif