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

//int base = 0;

// Serve para saber numero de celulas ocupadas da stack 

// o stack pointer inicializa automaticamente a zero, sendo que essa possição estará sempre vazia

STACK *new_stack(){
    STACK *stack = malloc(sizeof(STACK));
    stack->stack = malloc(1000*sizeof(ELEMENT));
    stack->stack_pointer = 0;
    stack->stack_size = 1000;
    return stack;
}


void push(STACK *pointer, BYTES element, TYPE type){
    if (pointer->stack_pointer >= pointer->stack_size) {
        pointer->stack_size *= 2;
        pointer->stack = realloc(pointer->stack, pointer->stack_size*sizeof(ELEMENT));
    }
    ELEMENT e;
    e.bytes = element;
    e.type = type;
    pointer->stack[pointer->stack_pointer++] = e;
}

ELEMENT pop(STACK *pointer){
    ELEMENT x = pointer->stack[--pointer->stack_pointer];
    return x;
}


int put_zero(char *token, int iter){
    for(; token[iter] != ' ' && token[iter] != '\n'; iter++);
    token[iter] = '\0';
    return ++iter;
}

int found(char *token, int iter){
    for (++iter; token[iter] != '\"'; iter++);
    return ++iter;
}

int found_bloco(char *palavra, int iter){
	for(++iter; palavra[iter] != '}'; iter++);
	return ++iter; 
}

void cria_string(char *token, char *new){
    int size = strlen(token), p, k;
    for(p = 1, k = 0; p < size-1; p++, k++){
        new[k] = token[p];
    }
}


int fornece_numero(char *token){
    char lista_strings1[20] [3] = { "+", "-", "*", "/", ")", "(", "#", "%", "&", "|", "^", "~", "_", ";", "\\", "@", "$", "i", "c", "f"};
    char lista_strings2[20] [3] = { "s", "l", "?", "=", ">", "<", "!", "e&", "e|", "e<", "e>", "A", "B", "C", "D", "E", "F", "G", "H", "I"};
    char lista_strings3[20] [3] = { "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", ":A", ":B", ":C"};
    char lista_strings4[20] [3] = { ":D", ":E", ":F", ":G", ":H", ":I", ":J", ":K", ":L", ":M", ":N", ":O", ":P", ":Q", ":R", ":S", ":T", ":U", ":V", ":W"};
    char lista_strings5[13] [3] = { ":X", ":Y", ":Z", ",", "\0", "\"", "[", "]", "t", "S/", "N/", "{", "w"};
    int conta = 1;
    if (token[0] == '\"') return 86;
    else if (token[0] == '{') return 92;
    for (int p = 0; p < 20; p++, conta++){
        if (strcmp(lista_strings1[p],token) == 0) return conta;
    }
    for (int p = 0; p < 20; p++, conta++){
        if (strcmp(lista_strings2[p],token) == 0) return conta;
    }
    for (int p = 0; p < 20; p++, conta++){
        if (strcmp(lista_strings3[p],token) == 0) return conta;
    }
    for (int p = 0; p < 20; p++, conta++){
        if (strcmp(lista_strings4[p],token) == 0) return conta;
    }
    for (int p = 0; p < 13; p++, conta++){
        if (strcmp(lista_strings5[p],token) == 0) return conta;
    }
    return 0;
}


int aux_handle_first(STACK *pointer, VAR_LIST *var_list, int sp_lista[], int indice, int *N){
    switch (indice){
        case 1: soma(pointer); return 0;
        case 2: sub(pointer); return 0;
        case 3: mult(pointer,var_list,sp_lista,N); return 0;
        case 4: divsao(pointer); return 0;
        case 5: incrementa(pointer); return 0;
        case 6: decrementa(pointer); return 0;
        case 7: exponencial(pointer); return 0;
        case 8:
            restdiv(pointer,var_list,sp_lista,N);
            return 0;
        case 9: conjuncao(pointer); return 0;
        case 10: disjuncao(pointer); return 0;
        case 11: xor(pointer); return 0;
        case 12: negacao(pointer,var_list,sp_lista,N); return 0;
        case 13: duplica(pointer); return 0;
        case 14: pop_operador(pointer); return 0;
        case 15: troca(pointer); return 0;
        case 16: roda_3(pointer); return 0;
        case 17: copia_nesimo(pointer,var_list,sp_lista,N); return 0;
        case 18: converte_int(pointer); return 0;
        case 19: converte_char(pointer); return 0;
        case 20: converte_double(pointer); return 0;
        case 21: converte_string(pointer); return 0;
        case 22: pede_linha(pointer); return 0;
        case 23: if_then_else(pointer); return 0;
        case 24: igualdade(pointer); return 0;
    }
    return 0;
}

int aux_handle_second(STACK *pointer, VAR_LIST *var_list, int indice){
    switch (indice){  
        case 25: maior(pointer); return 0;
        case 26: menor(pointer); return 0;
        case 27: negacao_operador(pointer); return 0;
        case 28: operador_and_shortcut(pointer); return 0;
        case 29: operador_or_shortcut(pointer); return 0;
        case 30: push_menor(pointer); return 0;
        case 31: push_maior(pointer); return 0; 
        case 32: push_var(pointer, var_list, 'A'); return 0;
        case 33: push_var(pointer, var_list, 'B'); return 0;
        case 34: push_var(pointer, var_list, 'C'); return 0;
        case 35: push_var(pointer, var_list, 'D'); return 0;
        case 36: push_var(pointer, var_list, 'E'); return 0;
        case 37: push_var(pointer, var_list, 'F'); return 0;
        case 38: push_var(pointer, var_list, 'G'); return 0;
        case 39: push_var(pointer, var_list, 'H'); return 0;
        case 40: push_var(pointer, var_list, 'I'); return 0;
        case 41: push_var(pointer, var_list, 'J'); return 0;
        case 42: push_var(pointer, var_list, 'K'); return 0;
        case 43: push_var(pointer, var_list, 'L'); return 0;
        case 44: push_var(pointer, var_list, 'M'); return 0;
        case 45: push_var(pointer, var_list, 'N'); return 0;
        case 46: push_var(pointer, var_list, 'O'); return 0;
        case 47: push_var(pointer, var_list, 'P'); return 0;
        case 48: push_var(pointer, var_list, 'Q'); return 0;
    }
    return 0;
}

int aux_handle_third(STACK *pointer, VAR_LIST *var_list, int indice){
    switch (indice){
        case 49: push_var(pointer, var_list, 'R'); return 0;
        case 50: push_var(pointer, var_list, 'S'); return 0;
        case 51: push_var(pointer, var_list, 'T'); return 0;
        case 52: push_var(pointer, var_list, 'U'); return 0;
        case 53: push_var(pointer, var_list, 'V'); return 0;
        case 54: push_var(pointer, var_list, 'W'); return 0;
        case 55: push_var(pointer, var_list, 'X'); return 0;
        case 56: push_var(pointer, var_list, 'Y'); return 0;
        case 57: push_var(pointer, var_list, 'Z'); return 0;
        case 58: atribui_var(pointer, var_list, 'A'); return 0;
        case 59: atribui_var(pointer, var_list, 'B'); return 0;
        case 60: atribui_var(pointer, var_list, 'C'); return 0;
        case 61: atribui_var(pointer, var_list, 'D'); return 0;
        case 62: atribui_var(pointer, var_list, 'E'); return 0;
        case 63: atribui_var(pointer, var_list, 'F'); return 0;
        case 64: atribui_var(pointer, var_list, 'G'); return 0;
        case 65: atribui_var(pointer, var_list, 'H'); return 0;
        case 66: atribui_var(pointer, var_list, 'I'); return 0;
        case 67: atribui_var(pointer, var_list, 'J'); return 0;
        case 68: atribui_var(pointer, var_list, 'K'); return 0;
        case 69: atribui_var(pointer, var_list, 'L'); return 0;
        case 70: atribui_var(pointer, var_list, 'M'); return 0;
        case 71: atribui_var(pointer, var_list, 'N'); return 0;
        case 72: atribui_var(pointer, var_list, 'O'); return 0;
    }
    return 0;
}

int aux_handle_fourth(STACK *pointer, char *token, VAR_LIST *var_list, int sp_lista[], int *N, int indice){
    char *aux;
    switch (indice){
        case 73: atribui_var(pointer, var_list, 'P'); return 0;
        case 74: atribui_var(pointer, var_list, 'Q'); return 0;
        case 75: atribui_var(pointer, var_list, 'R'); return 0;
        case 76: atribui_var(pointer, var_list, 'S'); return 0;
        case 77: atribui_var(pointer, var_list, 'T'); return 0;
        case 78: atribui_var(pointer, var_list, 'U'); return 0;
        case 79: atribui_var(pointer, var_list, 'V'); return 0;
        case 80: atribui_var(pointer, var_list, 'W'); return 0;
        case 81: atribui_var(pointer, var_list, 'X'); return 0;
        case 82: atribui_var(pointer, var_list, 'Y'); return 0;
        case 83: atribui_var(pointer, var_list, 'Z'); return 0;
        case 84: operador_virgula(pointer,var_list,sp_lista,N); return 0;
        case 85: return 0;
        case 86:
            aux = malloc(strlen(token));
            cria_string(token,aux);
            inicializa_string(pointer,aux);
            return 0;
        case 87: inicializa_array(pointer,sp_lista,N); return 0;
        case 88: push_to_array(pointer,sp_lista,N); return 0;
        case 89: read_all_input(pointer); return 0;
        case 90: whitespace(pointer); return 0;
        case 91: new_lines(pointer); return 0;
        case 92: 
            aux = malloc(strlen(token));
            cria_string(token,aux);
            inicializa_bloco(pointer,aux);
            return 0;
        case 93: aux_whiler(pointer,var_list,sp_lista,N);
    }
    return 0;
}


int handle(STACK *pointer, char *token, VAR_LIST *var_list, int sp_lista[], int *N){
    int indice = fornece_numero(token);
    if (indice != 0){
        if (indice < 25) aux_handle_first(pointer,var_list,sp_lista,indice,N);
        else if (indice < 49) aux_handle_second(pointer,var_list,indice);
        else if (indice < 73) aux_handle_third(pointer,var_list,indice);
        else aux_handle_fourth(pointer,token,var_list,sp_lista,N,indice);
    }
    else{
        char *palavra = malloc(1000*sizeof(char)), *auxpalavra = malloc(1000*sizeof(char));
        BYTES aux;
        sscanf(token, "%s", palavra); 
        TYPE tipo = found_type(palavra);
        if (tipo == INT) aux.INT = atoi(palavra);
        else if (tipo == DOUBLE) aux.DOUBLE = strtod(palavra, &auxpalavra);
        else if (tipo == CHAR) aux.CHAR = palavra[0];
        else aux.STRING = palavra;
        push(pointer, aux, tipo);
    }
    return 0;
}