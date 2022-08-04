#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"
#include "guiao1.h"
#include "guiao2.h"
#include "guiao3.h"
#include "guiao4.h"
#include "guiao5.h"

// GUIAO 3

ELEMENT passa_double (ELEMENT x) {
    ELEMENT y;
    y.type = DOUBLE;
    if (x.type == INT) y.bytes.DOUBLE = x.bytes.INT;
    else if (x.type == CHAR) y.bytes.DOUBLE = x.bytes.CHAR;
    else y.bytes.DOUBLE = x.bytes.DOUBLE;
    return y;
}

// operador ?

void if_then_else(STACK *stack) {
    ELEMENT x, y, z;
    x = pop(stack);
    y = pop(stack);
    z = pop(stack);
    if (z.type == ARRAY && z.bytes.ARRAY->stack_pointer == 0){
        push(stack, x.bytes, x.type);
    }
    else{
        z = passa_double(z);
        if (z.bytes.DOUBLE != 0) push(stack, y.bytes, y.type);
        else push(stack, x.bytes, x.type);
    }
}

// operador = (caso o tipo seja irrelevante é só apagar o primeiro if)

void igualdade(STACK *stack) {
    ELEMENT x = pop(stack);
    ELEMENT y = pop(stack);
    int valor = 0;
    if (y.type == ARRAY) array_indice(stack,&y,x.bytes.INT);
    else if (y.type == STRING && x.type == INT){
        string_indice(&y,x.bytes.INT);
        push(stack, y.bytes, CHAR);
    }
    else{
        if (y.type == DOUBLE || x.type == DOUBLE){
            x = passa_double(x);
            y = passa_double(y);
            if (y.bytes.DOUBLE == x.bytes.DOUBLE) valor = 1;
        }
        else if (y.type == STRING && x.type == STRING){
            valor = !strcmp(y.bytes.STRING,x.bytes.STRING);
        }
        else if (y.bytes.INT == x.bytes.INT) valor = 1;
        push(stack, (BYTES){valor}, INT);
    }
}

// Operador >

void maior(STACK *stack) {
    ELEMENT x = pop(stack);
    ELEMENT y = pop(stack);
    int valor = 0;
    if (y.type == ARRAY){
        ELEMENT *p = malloc(sizeof(ELEMENT));
        clone_array(&y,p);
        captura_fim_array(stack,p,x.bytes.INT);
    }
    else if (y.type == STRING && x.type == INT) captuda_fim(stack,&y,x.bytes.INT);
    else {
        if (y.type == DOUBLE || x.type == DOUBLE){
            x = passa_double(x);
            y = passa_double(y);
            if (y.bytes.DOUBLE > x.bytes.DOUBLE) valor = 1;
        }
        else if (y.type == STRING && x.type == STRING){
            valor = maior_string(y.bytes.STRING,x.bytes.STRING);
        }
        else if (y.bytes.INT > x.bytes.INT) valor = 1;
        push(stack, (BYTES){valor}, INT);
    }
}

// Operador <

void menor(STACK *stack) {
    ELEMENT x = pop(stack);
    ELEMENT y = pop(stack);
    int valor = 0;
    if (y.type == ARRAY) captura_inicio_array(stack,&y,x.bytes.INT);
    else if (y.type == STRING && x.type == INT) captuda_incio(stack,&y,x.bytes.INT);
    else{
        if (y.type == DOUBLE || x.type == DOUBLE){
            x = passa_double(x);
            y = passa_double(y);
            if (y.bytes.DOUBLE < x.bytes.DOUBLE) valor = 1;
        }
        else if (y.type == STRING && x.type == STRING){
            valor = menor_string(y.bytes.STRING,x.bytes.STRING);
        }
        else if (y.bytes.INT < x.bytes.INT) valor = 1;
        push(stack, (BYTES){valor}, INT);
    }
}

// Operador !

void negacao_operador(STACK *stack) {
    ELEMENT x = pop(stack);
    if (x.type == INT && x.bytes.INT == 0) push(stack, (BYTES){1}, INT);
    else if (x.type == DOUBLE && x.bytes.DOUBLE == 0) push(stack, (BYTES){1}, INT);
    else if (x.type == CHAR && x.bytes.CHAR == 0) push(stack, (BYTES){1}, INT);
    else push(stack, (BYTES){0}, INT);
}

// Operador &&

void operador_and_shortcut(STACK *stack) {
    ELEMENT x1, y2;
    ELEMENT x = pop(stack);
    ELEMENT y = pop(stack);
    x1 = passa_double(x);
    y2 = passa_double(y);
    if (x1.bytes.DOUBLE == 0 || y2.bytes.DOUBLE == 0) push(stack, (BYTES){0}, INT);
    else push(stack, x.bytes, x.type);
}

// Operador ||

void operador_or_shortcut(STACK *stack) {
    ELEMENT x1, y2;
    ELEMENT y = pop(stack);
    ELEMENT x = pop(stack);
    x1 = passa_double(x);
    y2 = passa_double(y);
    if (x1.bytes.DOUBLE == 0 && y2.bytes.DOUBLE == 0) push(stack, (BYTES){0}, INT);
    else if (x1.bytes.DOUBLE == 0) push(stack, y.bytes, y.type);
    else push(stack, x.bytes, x.type);
}

// Operador e<

void push_menor(STACK *stack) {
    ELEMENT x = pop(stack);
    ELEMENT y = pop(stack);
    ELEMENT x1, y2;
    if (x.type == STRING && y.type == STRING){
        if (menor_string(y.bytes.STRING,x.bytes.STRING) == 0) y = x;
        push(stack, y.bytes, y.type);
    }
    else{    
        x1 = passa_double(x);
        y2 = passa_double(y);
        if (x1.bytes.DOUBLE < y2.bytes.DOUBLE) push(stack, x.bytes, x.type);
        else push(stack, y.bytes, y.type);
    }
}



// Operador e>

void push_maior(STACK *stack) {
    ELEMENT x1, y2;
    ELEMENT x = pop(stack);
    ELEMENT y = pop(stack);
    if (x.type == STRING && y.type == STRING){
        if (maior_string(y.bytes.STRING,x.bytes.STRING) == 0) y = x;
        push(stack, y.bytes, y.type);
    }
    else{
        x1 = passa_double(x);
        y2 = passa_double(y);
        if (x1.bytes.DOUBLE > y2.bytes.DOUBLE) push(stack, x.bytes, x.type);
        else push(stack, y.bytes, y.type);
    }
}


//---------------------------------------------------------------------

// função que verifica se uma string apenas tem letras do alfabeto: 0 falso 1 verdade

int avalia_string(char *string){
    int valor = 1;
    for (int p = 0; string[p] != '\0'; p++){
        if (isalpha(string[p]) == 0) valor = 0;
    }
    return valor;
}

// verifica se o caracter ponto pertence a uma string

int avalia_ponto(char *string){
    int valor = 0;
    for (int p = 0; string[p] != '\0'; p++){
        if (string[p] == '.') valor = 1;
    }
    return valor;
}

// devolve o tipo do elemnto

TYPE found_type(char *string){
    TYPE tipo;
    int x = strlen(string), valor_s = avalia_string(string), valor_p = avalia_ponto(string);
    if (valor_s == 1){
        if (x == 1) tipo = CHAR;
        else tipo = STRING;
    }
    else if (valor_p == 1) tipo = DOUBLE;
    else tipo = INT;
    return tipo;
}

//----------------------------------------------------------------------------

// VARIÁVEIS

// operador :<letra> atribui um valor à variavel

// verifica se uma variavel pertence ao VAR_LIST

int elem(VAR_LIST *lista, char x){
    int valor = 0;
    for (int p = 0; p < lista->var_sp && valor != 1; p++){
        if (lista->vetor[p].letra == x) valor = 1;
    }
    return valor;
}

// Coloca o valor na stack das variaveis
// Operador :

void aux_atribui_var(STACK *stack, VAR_LIST *lista, char caracter){
    ELEMENT x = pop(stack);
    VAR y;
    y.letra = caracter;
    if (x.type == INT){
        y.variavel.INT = x.bytes.INT;  
        y.tipo = INT;
        lista->vetor[lista->var_sp++] = y; 
    }
    else if (x.type == DOUBLE){
        y.variavel.DOUBLE = x.bytes.DOUBLE;  
        y.tipo = DOUBLE;
        lista->vetor[lista->var_sp++] = y; 

    }
    else if (x.type == CHAR){
        y.variavel.CHAR = x.bytes.CHAR;
        y.tipo = CHAR;
        lista->vetor[lista->var_sp++] = y;
    }
    else if (x.type == ARRAY){
        ELEMENT copia = clone(x);
        y.variavel.ARRAY = copia.bytes.ARRAY;
        y.tipo = ARRAY;
        lista->vetor[lista->var_sp++] = y;
    }
    else if (x.type == BLOCO){
        y.variavel.BLOCO = strdup(x.bytes.BLOCO);
        y.tipo = BLOCO;
        lista->vetor[lista->var_sp++] = y;
    }
    else{
        y.variavel.STRING = x.bytes.STRING; 
        y.tipo = STRING; 
        lista->vetor[lista->var_sp++] = y;
    }
    push(stack, x.bytes, x.type);
}


void torca_variavel(STACK *stack, VAR_LIST *var_list, char y){
    ELEMENT x = pop(stack);
    int p;
    VAR aux;
    aux.letra = y;
    aux.tipo = x.type;
    for (p = 0; p < var_list->var_sp && var_list->vetor[p].letra != y; p++);
    if (x.type == INT) aux.variavel.INT = x.bytes.INT;
    else if (x.type == DOUBLE) aux.variavel.DOUBLE = x.bytes.DOUBLE;
    else if (x.type == CHAR) aux.variavel.CHAR = x.bytes.CHAR;
    else if (x.type == STRING) aux.variavel.STRING = x.bytes.STRING;
    else if (x.type == ARRAY) aux.variavel.ARRAY = x.bytes.ARRAY;
    else if (x.type == BLOCO) aux.variavel.BLOCO = x.bytes.BLOCO;
    var_list->vetor[p] = aux;
    push(stack, x.bytes, x.type);
}


void atribui_var(STACK *stack, VAR_LIST *var_list, char caracter){
    int valor = elem(var_list, caracter);
    if (valor == 1) torca_variavel(stack,var_list,caracter);
    else aux_atribui_var(stack,var_list,caracter);
}


// faz push de um variavel que está na stack das VAR_LIST

void push_var_list(STACK *stack, VAR_LIST *lista, char caracter){
    ELEMENT x;
    VAR y = lista->vetor[0];
    for (int p = 0; p < lista->var_sp && y.letra != caracter; p++){
        y = lista->vetor[p];
    }
    if (y.tipo == INT){
        x.bytes.INT = y.variavel.INT;
        push(stack, x.bytes, INT);
    }
    else if (y.tipo == DOUBLE){
        x.bytes.DOUBLE = y.variavel.DOUBLE;
        push(stack, x.bytes, DOUBLE);
    }
    else if (y.tipo == CHAR){
        x.bytes.CHAR = y.variavel.CHAR;
        push(stack, x.bytes, CHAR);
    }
    else if (y.tipo == ARRAY){
        x.bytes.ARRAY = y.variavel.ARRAY;
        push(stack, x.bytes, ARRAY);
    }
    else if (y.tipo == BLOCO){
        x.bytes.BLOCO = strdup(y.variavel.BLOCO);
        push(stack, x.bytes, BLOCO);
    }
    else{
        x.bytes.STRING = y.variavel.STRING;
        push(stack, x.bytes, STRING);
    }
}

// Dá push de um caracter especial (faz tudo sozinho)

void push_var(STACK *stack, VAR_LIST *lista, char caracter){
    int valor = elem(lista, caracter);
    if (valor == 1) push_var_list(stack, lista, caracter);
    else if (caracter == 'A') push(stack, (BYTES){10}, INT);
    else if (caracter == 'B') push(stack, (BYTES){11}, INT);
    else if (caracter == 'C') push(stack, (BYTES){12}, INT);
    else if (caracter == 'D') push(stack, (BYTES){13}, INT);
    else if (caracter == 'E') push(stack, (BYTES){14}, INT);
    else if (caracter == 'F') push(stack, (BYTES){15}, INT);
    else if (caracter == 'X') push(stack, (BYTES){0}, INT);
    else if (caracter == 'Y') push(stack, (BYTES){1}, INT);
    else if (caracter == 'Z') push(stack, (BYTES){2}, INT);
    else if (caracter == 'N') push(stack, (BYTES){'\n'}, CHAR);
    else if (caracter == 'S') push(stack, (BYTES){' '}, CHAR);
}

// devolve 1 se a string A for maior que a B

int maior_string(char *string_A, char *string_B){
    int valor = strcmp(string_A,string_B);
    if (valor > 0) return 1;
    else return 0;
}

int menor_string(char *string_A, char *string_B){
    int valor = strcmp(string_A,string_B);
    if (valor < 0) return 1;
    else return 0;
}

void clone_array(ELEMENT *x, ELEMENT *y){
    int p;
    y->type = ARRAY;
    y->bytes.ARRAY = malloc(sizeof(STACK));
    y->bytes.ARRAY->stack = malloc(1000000);
    y->bytes.ARRAY->stack_size = ARRAY_SIZE;
    for (p = 0; p < x->bytes.ARRAY->stack_pointer; p++){
        y->bytes.ARRAY->stack[p] = x->bytes.ARRAY->stack[p];
    }
    y->bytes.ARRAY->stack_pointer = p;
}