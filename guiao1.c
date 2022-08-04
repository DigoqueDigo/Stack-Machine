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


// GUIÃO I


// Se a soma não é de int's então é de double's
// A soma de double dá sempre 0.000000

void soma(STACK *pointer) {
    ELEMENT x = pop(pointer);
    ELEMENT y = pop(pointer);
    if (x.type == ARRAY || y.type == ARRAY) concat_array(pointer,&x,&y);
    else{
        if (x.type == STRING || y.type == STRING) concat_string(&x,&y);
        else if (y.type == DOUBLE || x.type == DOUBLE){
                x = passa_double(x);
                y = passa_double(y);
                y.bytes.DOUBLE += x.bytes.DOUBLE;
            }
        else if (x.type == INT || y.type == INT){
                y.bytes.INT += x.bytes.INT;
                y.type = INT;
            }
        else y.bytes.INT += x.bytes.INT;
        push(pointer, y.bytes, y.type);
    }
}

void sub(STACK *pointer) {
    ELEMENT x = pop(pointer);
    ELEMENT y = pop(pointer);
    if (y.type == DOUBLE || x.type == DOUBLE){
            x = passa_double(x);
            y = passa_double(y);
            y.bytes.DOUBLE -= x.bytes.DOUBLE;
        }
    else if (x.type == INT || y.type == INT){
            y.bytes.INT -= x.bytes.INT;
            y.type = INT;
        }
    else y.bytes.INT -= x.bytes.INT;
    push(pointer, y.bytes, y.type);
}

void mult(STACK *pointer, VAR_LIST *var_list, int sp_lista[], int *N){
    ELEMENT x = pop(pointer);
    ELEMENT y = pop(pointer);
    if (x.type == BLOCO) flodl(pointer,&x,&y,var_list,sp_lista,N);
    else if (y.type == ARRAY) replica_array(pointer, &y, x.bytes.INT);
    else {
        if (y.type == STRING){
            y.bytes.STRING = replica_string(y.bytes.STRING, x.bytes.INT);
        }
        else if (y.type == DOUBLE || x.type == DOUBLE){
                x = passa_double(x);
                y = passa_double(y);
                y.bytes.DOUBLE *= x.bytes.DOUBLE;
            }
        else if (x.type == INT || y.type == INT){
                y.bytes.INT *= x.bytes.INT;
                y.type = INT;
            }
        else y.bytes.INT *= x.bytes.INT;
        push(pointer, y.bytes, y.type);
    }
}


void divsao(STACK *pointer){
    ELEMENT x = pop(pointer);
    ELEMENT y = pop(pointer);
    if (x.type == STRING && y.type == STRING) separa_substring(pointer,&x,&y);
    else{
        if (y.type == DOUBLE || x.type == DOUBLE){
                x = passa_double(x);
                y = passa_double(y);
                y.bytes.DOUBLE /= x.bytes.DOUBLE;
            }
        else if (x.type == INT || y.type == INT){
                y.bytes.INT /= x.bytes.INT;
                y.type = INT;
            }
        else y.bytes.INT /= x.bytes.INT;
        push(pointer, y.bytes, y.type);
    }
}


void incrementa(STACK *pointer){
    ELEMENT x = pop(pointer);
    if (x.type == ARRAY) remove_ultimo_array(pointer,&x);
    else if (x.type == STRING) remove_ultimo_string(pointer,&x);
    else{
        if (x.type == INT) ++x.bytes.INT;
        else if (x.type == CHAR) ++x.bytes.CHAR;
        else ++x.bytes.DOUBLE;
        push(pointer, x.bytes, x.type);
    }
}


void decrementa(STACK *pointer){
    ELEMENT x = pop(pointer);
    if (x.type == ARRAY) remove_primeiro_array(pointer,&x);
    else if (x.type == STRING) remove_primeiro_string(pointer,&x);
    else{
        if (x.type == INT) --x.bytes.INT;
        else if (x.type == CHAR) --x.bytes.CHAR;
        else --x.bytes.DOUBLE;
        push(pointer, x.bytes, x.type);
    }
}



void exponencial(STACK *pointer){
    ELEMENT x = pop(pointer);
    ELEMENT y = pop(pointer);
    if (y.type == STRING && x.type == STRING){
        int a = substring_indice(y.bytes.STRING,x.bytes.STRING);
        x.type = INT;
        x.bytes.INT = a;
        push(pointer, x.bytes, x.type);
    }
    else{
        if (y.type == DOUBLE || x.type == DOUBLE){
                x = passa_double(x);
                y = passa_double(y);
                y.bytes.DOUBLE = pow(y.bytes.DOUBLE, x.bytes.DOUBLE);
            }
        else if (x.type == INT || y.type == INT){
                y.bytes.INT = pow(y.bytes.INT, x.bytes.INT);
                y.type = INT;
            }
        else pow(y.bytes.INT, x.bytes.INT);
        push(pointer, y.bytes, y.type);
    }
}

void restdiv(STACK *pointer, VAR_LIST *var_list, int sp_lista[], int *N){
    ELEMENT a = pop(pointer);
    ELEMENT b = pop(pointer);
    if (a.type == BLOCO && b.type == ARRAY) operacoes_array(pointer,&a,&b,var_list,sp_lista,N); 
    else if (a.type == BLOCO && b.type == STRING) operacoes_string(pointer,&a,&b,var_list,sp_lista,N);
    else{
        int x = a.bytes.INT;
        int y = b.bytes.INT;
        push(pointer, (BYTES){y%x}, INT);
    }
}



void conjuncao(STACK *stack){
    int x = pop(stack).bytes.INT;
    int y = pop(stack).bytes.INT;
    push(stack, (BYTES){x & y}, INT);
}



void disjuncao(STACK *stack){
    int x = pop(stack).bytes.INT;
    int y = pop(stack).bytes.INT;
    push(stack, (BYTES){x | y}, INT);
}



void xor(STACK *stack){
    int x = pop(stack).bytes.INT;
    int y = pop(stack).bytes.INT;
    push(stack, (BYTES){x ^ y}, INT);
}



void negacao(STACK *stack, VAR_LIST *var_list, int sp_lista[], int *N){
    ELEMENT x = pop(stack);
    if (x.type == ARRAY) push_array_to_stack(stack,&x); 
    else if (x.type == BLOCO) operacoes(stack,&x,var_list,sp_lista,N);
    else{
        int a = x.bytes.INT;
        push(stack, (BYTES){~a}, INT);
    }
}
