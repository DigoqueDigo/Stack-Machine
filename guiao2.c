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


// OPERADORES DA STACK


void roda_3(STACK *stack){
    ELEMENT x = stack->stack[--stack->stack_pointer];
    ELEMENT y = stack->stack[--stack->stack_pointer];
    ELEMENT z = stack->stack[--stack->stack_pointer];
    push(stack, y.bytes, y.type);
    push(stack, x.bytes, x.type);
    push(stack, z.bytes, z.type);
}

 
//Função que duplica o elemento do topo da stack


void duplica(STACK *stack){
    ELEMENT x = stack->stack[--stack->stack_pointer];
    stack->stack_pointer++;
    push(stack, x.bytes, x.type);
}


void pop_operador(STACK *stack){
    pop(stack);
}


void troca(STACK *stack){
    ELEMENT x = stack->stack[--stack->stack_pointer];
    ELEMENT y = stack->stack[--stack->stack_pointer];
    push(stack, x.bytes, x.type);
    push(stack, y.bytes, y.type);
}

void copia_nesimo(STACK *stack, VAR_LIST *var_list, int sp_lista[], int *N){
    ELEMENT a = pop(stack);
    if (a.type == BLOCO){
        ELEMENT y = pop(stack);
        ordena(stack,&a,&y,var_list,sp_lista,N);
    }
    else{
        int n = a.bytes.INT; 
        ELEMENT x = stack->stack[stack->stack_pointer-n-1];
       push(stack, x.bytes, x.type);
    }
}

void converte_int(STACK *stack) {
    ELEMENT x = pop(stack);
    if (x.type == DOUBLE){
        int y;
        y = x.bytes.DOUBLE;
        x.bytes.INT = y; 
    }
    else if (x.type == CHAR){
        int d = x.bytes.CHAR;
        x.bytes.INT = d;
    }
    else if (x.type == STRING) converte_string_to_int(&x);
    push(stack, x.bytes, INT);
}


void converte_char(STACK *stack) {
    ELEMENT x = pop(stack);
    if (x.type == DOUBLE){
        char y;
        y = x.bytes.DOUBLE;
        x.bytes.CHAR = y; 
    }
    push(stack, x.bytes, CHAR);
}


void converte_double(STACK *stack) {
    ELEMENT x = pop(stack);
    ELEMENT y = x;
    if (x.type == INT) y.bytes.DOUBLE = x.bytes.INT;
    else if (x.type == CHAR) y.bytes.DOUBLE = x.bytes.CHAR;
    else if (x.type == STRING) converte_string_to_double(&y);
    else y.bytes.DOUBLE = x.bytes.DOUBLE;
    push(stack, y.bytes, DOUBLE);
}


void converte_string(STACK *stack) {
    char palavra[100];
    ELEMENT x = pop(stack);
    if (x.type == INT) sprintf(palavra, "%ld", x.bytes.INT);
    else if (x.type == DOUBLE) sprintf(palavra, "%lf", x.bytes.DOUBLE);
    else  sprintf(palavra, "%c", x.bytes.CHAR);
    x.type = STRING;
    x.bytes.STRING = strdup(palavra);
    push(stack, x.bytes, STRING);
}


void print_element(ELEMENT* e) {
    if(e->type == INT) {
        printf("%ld", e->bytes.INT);
    }
    else if(e->type == DOUBLE) {
            printf("%g", e->bytes.DOUBLE);
        }
    else if(e->type == CHAR) {
        printf("%c", e->bytes.CHAR);
    }
    else if (e->type == STRING){
        printf("%s", e->bytes.STRING);
    }
    else if (e->type == ARRAY){
        putchar('\n');
        for (int p = 0; p < e->bytes.ARRAY->stack_pointer; p++){
            if (e->bytes.ARRAY->stack[p].type == INT) printf("array: ->%ld<-\n", e->bytes.ARRAY->stack[p].bytes.INT);
            else if (e->bytes.ARRAY->stack[p].type == DOUBLE) printf("array: ->%g<-\n", e->bytes.ARRAY->stack[p].bytes.DOUBLE);
            else if (e->bytes.ARRAY->stack[p].type == CHAR) printf("array: ->%c<-\n", e->bytes.ARRAY->stack[p].bytes.CHAR);
            else if (e->bytes.ARRAY->stack[p].type == STRING) printf("array: ->%s<-\n", e->bytes.ARRAY->stack[p].bytes.STRING);
            else if (e->bytes.ARRAY->stack[p].type == ARRAY) print_element(&(e->bytes.ARRAY->stack[p]));
        }
    }
}


void pede_linha(STACK *stack){
    ELEMENT x;
    char *linha = malloc(ARRAY_SIZE*sizeof(char));
    if (fgets(linha, ARRAY_SIZE, stdin) != NULL){
        int tamanho = strlen(linha);
        linha[tamanho-1] = '\0';
        x.type = STRING;
        x.bytes.STRING = strdup(linha);
        push(stack, x.bytes, x.type);
    }
}

void print_stack(STACK *stack){
    for (int p = 0; p < stack->stack_pointer; p++){
        if (stack->stack[p].type == INT) printf("%ld", stack->stack[p].bytes.INT);
        else if (stack->stack[p].type == DOUBLE) printf("%g", stack->stack[p].bytes.DOUBLE);
        else if (stack->stack[p].type == CHAR) printf("%c", stack->stack[p].bytes.CHAR);
        else if (stack->stack[p].type == STRING) printf("%s", stack->stack[p].bytes.STRING);
        else if (stack->stack[p].type == BLOCO) printf("{%s}", stack->stack[p].bytes.BLOCO);
        else print_stack(stack->stack[p].bytes.ARRAY);
    }
}