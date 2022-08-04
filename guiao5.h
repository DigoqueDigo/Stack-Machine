#ifndef GUIAO5_H
#define GUIAO5_H
#pragma once

/**
\file guiao5.h
\brief Funções relativas ao guião 5
*/


/*!
 * @brief Estrutura que armazena o conteudo de um VALOR
 * 
 * Um VALOR é constituido por um ELEMENT e um inteiro que indica a importancia de ELEMENT
 */
typedef struct valor{
    ELEMENT elemento; ///< ELEMENT no qual se prentede armazenar informação
    int valor; ///< parâmetro que indica a importancia do ELEMENT  
} VALOR;


/*!
 * @brief Estrutura que armazena varios VALORES
 * 
 * Esta estrutura é composta por um array de VALORES e um inteiro que indica o tamanho útil do array
 */
typedef struct valor_array{
    VALOR lista[1000]; ///< array que contem a informação de varios VALORES
    int tamanho; ///< inteiro que indica o tamanho util que array de VALORES
} VALOR_LISTA;


/**
 * @brief Esta função tem como objetivo inicializar um bloco
 * 
 * @param stack stack na qual será colocado o bloco já inicializado
 * @param bloco um bloco é um string que apenas é tratada de forma diferente
 */
void inicializa_bloco(STACK *stack, char *bloco);


/**
 * @brief Esta função tem como objetivo aplicar um bloco à stack
 * 
 * @param stack stack na qual será aplicado o bloco
 * @param var_list stack auxiliar que guarda variaveis
 * @param sp_lista array que contem varios stack pointers
 * @param N elemento que indica o valor do stack pointer
 */
void operacoes(STACK *stack, ELEMENT *x, VAR_LIST *var_list, int sp_lista[], int *N);


/**
 * @brief Esta função tem como objetivo aplicar um bloco a um array
 * 
 * @param stack stack que contem um bloco e um array no seu topo
 * @param bloco bloco que será aplicado no array contido no ELEMENTO x
 * @param x ELEMENT que contem um array e no qual será aplicado o bloco
 * @param var_list stack auxiliar que guarda variaveis
 * @param sp_lista array que contem varios stack pointers
 * @param N elemento que indica o valor do stack pointer
 */
void operacoes_array(STACK *stack, ELEMENT *bloco, ELEMENT *x, VAR_LIST *var_list, int sp_lista[], int *N);


/**
 * @brief Esta função tem como objetivo aplicar um bloco a uma string
 * 
 * @param stack stack que contem um bloco e uma string no seu topo
 * @param bloco bloco que será aplicado à string contido no ELEMENTO x
 * @param x ELEMENT que contem uma string na qual será aplicado o bloco
 * @param var_list stack auxiliar que guarda variaveis
 * @param sp_lista array que contem varios stack pointers
 * @param N elemento que indica o valor do stack pointer
 */
void operacoes_string(STACK *stack, ELEMENT *bloco, ELEMENT *x, VAR_LIST *var_list, int sp_lista[], int *N);


/**
 * @brief Esta função analisa o valor logico que um ELEMENT
 * 
 * @param x ELEMENT que será analisado e do qual se pretende extrair o valor logico
 * @return retorna o valor logico do ELEMENT x
 */
int verifica_valor(ELEMENT *x);


/**
 * @brief Esta função tem como objetivo filtar um array/string a partir de uma certa condição
 * 
 * @param stack stack que contem um bloco e uma string/array no seu topo
 * @param bloco bloco que será aplicado a um array ou string
 * @param x ELEMENT que contem uma string/array em que será aplicado o bloco
 * @param var_list stack auxiliar que guarda variaveis
 * @param sp_lista array que contem varios stack pointers
 * @param N elemento que indica o valor do stack pointer
 */
void filter_array(STACK *stack, ELEMENT *bloco, ELEMENT *x, VAR_LIST *var_list, int sp_lista[], int *N);


/**
 * @brief Esta função serve como uma auxiliar à função operador virgula definida no guiao 4
 * 
 * @param stack stack que contem um bloco e uma string/array no seu topo
 * @param bloco bloco que será aplicado a um array ou string
 * @param var_list stack auxiliar que guarda variaveis
 * @param sp_lista array que contem varios stack pointers
 * @param N elemento que indica o valor do stack pointer
 */
void aux_operador_virgula(STACK *stack, ELEMENT *bloco, VAR_LIST *var_list, int sp_lista[], int *N);


/**
 * @brief Esta função converte o conteudo de um ELEMENT que possua uma string para um double
 * 
 * @param x ELEMENT cujo conteudo será alterado de uma string para um double
 */
void converte_string_to_double(ELEMENT *x);


/**
 * @brief Esta função converte o conteudo de um ELEMENT que possua uma string para um int
 * 
 * @param x ELEMENT cujo conteudo será alterado de uma string para um int
 */
void converte_string_to_int(ELEMENT *x);


/**
 * @brief Esta função faz fold a um ELEMENT que contem um array
 * 
 * @param stack stack que contem um bloco e um array no seu topo
 * @param bloco bloco que será aplicado ao array contido no elemento x
 * @param x ELEMENT que contem um array no qual será aplicado o bloco
 * @param var_list stack auxiliar que guarda variaveis
 * @param sp_lista array que contem varios stack pointers
 * @param N elemento que indica o valor do stack pointer
 */
void flodl(STACK *stack, ELEMENT *bloco, ELEMENT *x, VAR_LIST *var_list, int sp_lista[], int *N);


/**
 * @brief Esta função calcula a posição do VALOR com maior importancia
 * 
 * @param vetor array que contem varios VALORES e do qual se pretende extrair a informação da poscição do de maior importancia
 * @return retorna o indice do VALOR de maior importancia
 */
int max_valor(VALOR_LISTA *vetor, int N);


/**
 * @brief Esta função troca dois VALORES de posição
 * 
 * @param vetor array no qual será troca a posição de dois VALORES
 * @param x o VALOR nesta posição irá passar para o posição N-1 
 * @param N o VALOR nesta posição irá passar para o posição x
 */
void swap(VALOR_LISTA *vetor, int x, int N);


/**
 * @brief Esta função ordena um array de VALORES conforme a importancia de cada valor
 * 
 * @param vetor array no qual os VALORES de maior importancia ficarão nas ultimas posições
 */
void max_sort(VALOR_LISTA *vetor);


/**
 * @brief Esta função ordena um array conforme um bloco
 * 
 * @param stack stack que contem o array que será ordenado
 * @param bloco bloco que será aplicado ao array
 * @param x ELEMENT que contem um array no qual será aplicado o bloco
 * @param var_list stack auxiliar que guarda variaveis
 * @param sp_lista array que contem varios stack pointers
 * @param N elemento que indica o valor do stack pointer
 */
void ordena(STACK *stack, ELEMENT *bloco, ELEMENT *x, VAR_LIST *var_list, int sp_lista[], int *N);


/**
 * @brief Esta função representa no terminal o conteudo de array de VALORES
 * 
 * @param vetor array de VALORES que será representado no terminal
 */
void print_valores(VALOR_LISTA *vetor);


/**
 * @brief Esta função executa um bloco enquanto este tiver valor logico igual a 1
 * 
 * @param stack stack na qual será aplicado o bloco
 * @param bloco bloco que será aplicado à stack
 * @param var_list stack auxiliar que guarda variaveis
 * @param sp_lista array que contem varios stack pointers
 * @param N elemento que indica o valor do stack pointer
 */
void whiler(STACK *stack, ELEMENT *bloco, VAR_LIST *var_list, int sp_lista[], int *N);


/**
 * @brief Esta função é apenas um auxilixar para awhiler
 * 
 * @param stack stack na qual será aplicado o bloco
 * @param var_list stack auxiliar que guarda variaveis
 * @param sp_lista array que contem varios stack pointers
 * @param N elemento que indica o valor do stack pointer
 */
void aux_whiler(STACK *stack, VAR_LIST *var_list, int sp_lista[], int *N);


/**
 * @brief Esta função representa no terminal um array de variaveis
 * 
 * @param var_list array de variaveis que será representado no terminal
 */
void print_var_list(VAR_LIST *var_list);


/**
 * @brief Esta função faz um clone de um array de variaveis
 * 
 * @param var_list array de variaveis que será clonado
 * @return array de variaveis clonado
 */
VAR_LIST* clone_var_list(VAR_LIST *lista);


/**
 * @brief Esta função retira todo o conteudo que uma stack possui
 * 
 * @param stack stack à qual será removido todo o seu conteudo
 */
void solta_stack(STACK *stack);

#endif