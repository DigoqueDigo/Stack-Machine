#ifndef GUIAO3_H
#define GUIAO3_H
#pragma once

/**
\file guiao3.h
\brief Funções relativas ao guião 3
*/


/**
 * @brief Esta função altera o conteudo de um ELEMENT para um double
 * 
 * @param x elemento que se predente alterar o conteudo para um double
 * @return elemento já com o conteudo convertido para double
 */
ELEMENT passa_double (ELEMENT x);

/**
 * @brief Esta função corresponte ao operador ?
 * 
 * @param stack stack em que são retirados os elementos correspondentes a cada parte do operador "if then else"
 */
void if_then_else(STACK *stack);


/**
 * @brief Esta função verifica se dois ELEMENT's são iguais
 * 
 * @param stack stack na qual é feito o teste se dois elementos são igual (o tipo é irrelevante)
 */
void igualdade(STACK *stack);


/**
 * @brief Esta função verifica se um elemento é maior que o outro
 * 
 * @param stack stack na qual é feita a analise de qual dos elementos é maior
 */
void maior(STACK *stack);


/**
 * @brief Esta função verifica se um elemento é menor que o outro
 * 
 * @param stack stack na qual é feita a analise de qual dos elementos é menor
 */
void menor(STACK *stack);


/**
 * @brief Esta função permite negar qualquer ELEMENT (tudo o que é diferente de zero é verdade)
 * 
 * @param stack stack stack na qual é feita a negação de um dois seu elementos
 */
void negacao_operador(STACK *stack);


/**
 * @brief Esta função parecida ao operador && na linguagem C
 * 
 * @param stack stack em que são extraidos dois elementos com o objetivo de aplicar o operador & (shortcut)
 */
void operador_and_shortcut(STACK *stack);


/**
 * @brief Esta função é parecida ao operador || na linguagem C
 * 
 * @param stack stack em que são extraidos dois elementos com o objetivo de aplicar o operador | (shortcut)
 */
void operador_or_shortcut(STACK *stack);


/**
 * @brief Esta função faz pop de dois ELEMENT's e dá push do menor
 * 
 * @param stack stack na qual é colocada o menor dos dois elementos 
 */
 void push_menor(STACK *stack);


/**
 * @brief Esta função faz pop de dois ELEMENT's e dá pop do maior
 * 
 * @param stack stack na qual é colocada o maior dos dois elementos
 */
void push_maior(STACK *stack);


/**
 * @brief Esta função verifica se uma string apenas contem letras do alfabeto
 * 
 * @param string string na qual serão testados cada um dos caracteres 
 * @return retorn 1 se a string apenas possuir letras do alfabeto, caso contrário retorna 0
 */
int avalia_string(char *string);


/**
 * @brief Esta função verifica se uma string possui o caractere '.'
 * 
 * @param string string da qual serão testados todos os seus caracteres 
 * @return retorn 1 se a string apenas possuir o caractere '.', caso contrário retorna 0
 */
int avalia_ponto(char *string);


/**
 * @brief Dada uma string, esta função identifica se a string corresponde a um INT, DOUBLE, CHAR ou então uma STRING
 * 
 * @param string stirng a partir da qual se predente extrair a informação do tipo do elemento  
 * @return retorna o tipo que a string pretende transmitir
 */
TYPE found_type(char *string);


/**
 * @brief Esta função verifica se um dado caractere pertence ou não à VAR_LIST
 * 
 * @param lista lista de variaveis que será analisada
 * @param c caracter que se pretende verificar se pretence à lista
 * @return retorna 1 se uma dada variavel pertence à lista, caso contrário devolve zero
 */
int elem(VAR_LIST *lista, char x);


/**
 * @brief operador = (caso o tipo seja irrelevante é só apagar o primeiro if)
 * 
 * @param stack stack na qual está contida a lista de variaveis
 * @param lista array que contem varias variaveis
 * @param caractere caractere que será colocado na lista de variaveis, juntamente com o seu respetivo conteudo
 */
void aux_atribui_var(STACK *stack, VAR_LIST *lista, char caractere);


/**
 * @brief Esta função faz push de um determinado caractere na VAR_LIST
 * 
 * @param stack stack na qual está contida a lista de variaveis
 * @param lista array que contem varias variaveis
 * @param caractere caractere cujo conteudo se pretende extrair da lista de variaveis para a stack
 */
void push_var_list(STACK *stack, VAR_LIST *lista, char caractere);


/**
 * @brief Esta função faz push de um caracter para a stack, que este esteja na VAR_LIST ou não
 * 
 * @param stack stack na qual está contida a lista de variaveis
 * @param lista array que contem varias variaveis
 * @param caractere caractere cujo conteudo será colocado na stack
 */
void push_var(STACK *stack, VAR_LIST *lista, char caractere);


/**
 * @brief Vê se a string A é maior que a string B. Se sim devolve 1 se não devolve 0
 * 
 * @param string_A string que se preteinde comparar com string_B
 * @param string_B string que se preteinde comparar com string_A
 * @return retorna 1 se string_A for maior que string_B, caso contrário retorna zero
 */
int maior_string(char *string_A, char *string_B);


/**
 * @brief Vê se a string A é menor que a string B. Se sim devolve 1 se não devolve 0
 * 
 * @param string_A string que se preteinde comparar com string_B
 * @param string_B string que se preteinde comparar com string_A
 * @return retorna 1 se string_A for menor que string_B, caso contrário retorna zero
 */
int menor_string(char *string_A, char *string_B);


/**
 * @brief Esta função altera o conteudo de um elemento pertencente a uma VAR_LIST
 * 
 * @param stack stack na qual está contida a lista de variaveis
 * @param var_list lista de variaveis à qual se pretende alterar o conteudo
 * @param y caractere que corresponde ao conteudo que se pretende substituir na lista de variaveis
 */
void torca_variavel(STACK *stack, VAR_LIST *var_list, char y);


/**
 * @brief Esta função coloca na VAR_LIST uma nova variável e o seu respetivo conteudo
 * 
 * @param stack stack na qual está contida a lista de variaveis
 * @param lista lista de variaveis na qual será colocada uma nova variavel
 * @param caractere novo caractere que será colocado na lista de variaveis
 */
void atribui_var(STACK *stack, VAR_LIST *lista, char caractere);


/**
 * @brief Esta função copia todo o conteudo do elemento x para y
 * 
 * @param x apontador de um elemento cujo conteudo será copiado para y
 * @param y apontador de um elemento que vai receber o conteudo de x
 */
void clone_array(ELEMENT *x, ELEMENT *t);

#endif