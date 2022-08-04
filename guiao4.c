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



void operador_virgula(STACK *stack, VAR_LIST *var_list, int sp_lista[], int *N){
    ELEMENT x = pop(stack);
    ELEMENT y, aux;
    y.type = ARRAY;
    if (x.type == INT){
        y.bytes.ARRAY = malloc(sizeof(STACK));
        y.bytes.ARRAY->stack = malloc(ARRAY_SIZE*sizeof(ELEMENT));
        y.bytes.ARRAY->stack_size = ARRAY_SIZE;
        for (int p = 0; p < x.bytes.INT; p++){
            aux.type = INT;
            aux.bytes.INT = p;
            y.bytes.ARRAY->stack[p] = aux;
            y.bytes.ARRAY->stack_pointer++;
        }
        push(stack, y.bytes, y.type);
    }
    else if (x.type == DOUBLE){
        y.bytes.ARRAY = malloc(sizeof(STACK));
        y.bytes.ARRAY->stack = malloc(ARRAY_SIZE*sizeof(STACK));
        y.bytes.ARRAY->stack_size = ARRAY_SIZE;
        for (int p = 0; p < x.bytes.DOUBLE; p++){
            aux.type = INT;
            aux.bytes.INT = p;
            y.bytes.ARRAY->stack[p] = aux;
            y.bytes.ARRAY->stack_pointer++;

        }
        push(stack, y.bytes, y.type);
    }
    else if (x.type == CHAR){
        int i = 0;
        y.bytes.ARRAY = malloc(sizeof(STACK));
        y.bytes.ARRAY->stack = malloc(ARRAY_SIZE*sizeof(STACK));
        y.bytes.ARRAY->stack_size = ARRAY_SIZE;
        for (char p = 'a'; p < x.bytes.CHAR; p++, i++){
            aux.type = CHAR;
            aux.bytes.CHAR = p;
            y.bytes.ARRAY->stack[i] = aux;
            y.bytes.ARRAY->stack_pointer++;
        }
        push(stack, y.bytes, y.type);
    }
    else if (x.type == STRING){
        y.type = INT;
        y.bytes.INT = strlen(x.bytes.STRING);
        push(stack, y.bytes, y.type);
    }
    else if (x.type == BLOCO) aux_operador_virgula(stack,&x,var_list,sp_lista,N);
    else{
        y.type = INT;
        y.bytes.INT = x.bytes.ARRAY->stack_pointer;
        push(stack, y.bytes, y.type);
    }
}


void inicializa_string(STACK *stack, char *palavra){
    ELEMENT x;
    x.type = STRING;
    x.bytes.STRING = strdup(palavra);
    push(stack, x.bytes, x.type);
}



void inicializa_array(STACK *stack, int sp_lista[], int *N){
    sp_lista[*N] = stack->stack_pointer;
    *N = *N+1;
}


void push_to_array(STACK *stack, int sp_lista[], int *N){
    ELEMENT x;
    x.type = ARRAY;
    x.bytes.ARRAY = malloc(sizeof(STACK));
    x.bytes.ARRAY->stack = malloc(ARRAY_SIZE*sizeof(ELEMENT));
    int sp = sp_lista[*N-1];
    int tamanho = stack->stack_pointer - sp;
    if (tamanho == 0){
        x.bytes.ARRAY->stack_pointer = 0;
        push(stack, x.bytes, x.type);
    }
    else{
        for (int p = 0; p < tamanho; p++, sp++){
            x.bytes.ARRAY->stack[p] = stack->stack[sp];
            x.bytes.ARRAY->stack_pointer++;
        }
        for (int p = 0; p < tamanho; p++){
            pop(stack);
        }
        push(stack, x.bytes, x.type);
        *N = *N-1;
    }
}


char* replica_string(char *string, int N){
    char *aux = strdup(string);
    int tamanho = strlen(string);
    string = malloc(tamanho*N);
    for (int p = 0; p < N; p++){
        strcat(string,aux);
    }
    return string;
}


int passa_string(ELEMENT* x){
    char palavra[100];
    if (x->type == STRING) return 0;
    else if (x->type == INT) sprintf(palavra, "%ld", x->bytes.INT);
    else if (x->type == DOUBLE) sprintf(palavra, "%lf", x->bytes.DOUBLE);
    else if (x->type == CHAR) sprintf(palavra, "%c", x->bytes.CHAR);
    x->type = STRING;
    x->bytes.STRING = strdup(palavra); 
    return 0;
}


void concat_string(ELEMENT* x, ELEMENT* y){
    passa_string(x);
    passa_string(y);
    int Nx = strlen(x->bytes.STRING);
    int Ny = strlen(y->bytes.STRING);
    char *aux = strdup(y->bytes.STRING);
    y->bytes.STRING = malloc(Nx + Ny);
    strcpy(y->bytes.STRING,aux);
    strcat(y->bytes.STRING,x->bytes.STRING);
}


void string_indice(ELEMENT *x, int N){
    char aux = x->bytes.STRING[N];
    x->type = CHAR;
    x->bytes.CHAR = aux;
}


void remove_primeiro_string(STACK *stack, ELEMENT *x){
    ELEMENT aux;
    aux.type = CHAR;
    aux.bytes.CHAR = x->bytes.STRING[0];
    for (int p = 0; x->bytes.STRING[p] != '\0'; p++){
        x->bytes.STRING[p] = x->bytes.STRING[p+1];
    }
    push(stack, x->bytes, x->type);
    push(stack, aux.bytes, aux.type);
}


void remove_ultimo_string(STACK *stack, ELEMENT *x){
    int tamanho = strlen(x->bytes.STRING);
    ELEMENT aux;
    aux.type = CHAR;
    aux.bytes.CHAR = x->bytes.STRING[tamanho-1];
    x->bytes.STRING[tamanho-1] = '\0';
    push(stack, x->bytes, x->type);
    push(stack, aux.bytes, aux.type);
}


void captuda_incio(STACK *stack, ELEMENT *x, int N){
    x->bytes.STRING[N] = '\0';
    push(stack, x->bytes, x->type);
}


void captuda_fim(STACK *stack, ELEMENT *x, int N){
    int inicio = strlen(x->bytes.STRING)-N;
    x->bytes.STRING = &(x->bytes.STRING[inicio]);
    push(stack, x->bytes, x->type);
}


int substring_indice(char *frase, char *substring){
    int tamanho = strlen(frase), p = -1;
    char *aux = strdup(frase);
    aux = strstr(frase,substring);
    if (aux != NULL){
        int lenght = strlen(aux);
        p = tamanho - lenght;
    }
    return p;
}




void puxa_frente(ELEMENT *x){
    int tamanho = x->bytes.ARRAY->stack_pointer;
    for (; tamanho > 0; tamanho--){
        x->bytes.ARRAY->stack[tamanho] = x->bytes.ARRAY->stack[tamanho-1];
    }
    x->bytes.ARRAY->stack_pointer++;

}

void puxa_atras(ELEMENT *x){
    int tamanho = x->bytes.ARRAY->stack_pointer;
    for (int p = 0; p < tamanho-1; p++){
        x->bytes.ARRAY->stack[p] = x->bytes.ARRAY->stack[p+1];
    }
    x->bytes.ARRAY->stack_pointer--;
}


void concat_array(STACK *stack, ELEMENT *x, ELEMENT *y){
    if (x->type == ARRAY && y->type == ARRAY){
        for (int p = 0; p < x->bytes.ARRAY->stack_pointer; p++){
            y->bytes.ARRAY->stack[y->bytes.ARRAY->stack_pointer++] = x->bytes.ARRAY->stack[p];
        }
        push(stack, y->bytes, y->type);
    }
    else if (x->type == ARRAY){
        puxa_frente(x);
        x->bytes.ARRAY->stack[0] = *y;
        push(stack, x->bytes, x->type);
    }
    else{
        y->bytes.ARRAY->stack[y->bytes.ARRAY->stack_pointer++] = *x;
        push(stack, y->bytes, y->type);
    }
}

void replica_array(STACK *stack, ELEMENT *x, int N){
    int max = x->bytes.ARRAY->stack_pointer;
    for (int i = 0; i < N-1; i++){
        for (int p = 0; p < max; p++){
            x->bytes.ARRAY->stack[x->bytes.ARRAY->stack_pointer++] = x->bytes.ARRAY->stack[p];
        }
    }
    push(stack, x->bytes, x->type);
}

void remove_primeiro_array(STACK *stack, ELEMENT *x){
    ELEMENT aux = x->bytes.ARRAY->stack[0];
    puxa_atras(x);
    push(stack, x->bytes, x->type);
    push(stack, aux.bytes, aux.type);
}

void remove_ultimo_array(STACK *stack, ELEMENT *x){
    ELEMENT aux = x->bytes.ARRAY->stack[--x->bytes.ARRAY->stack_pointer];
    push(stack, x->bytes, x->type);
    push(stack, aux.bytes, aux.type);
}

void array_indice(STACK *stack, ELEMENT *x, int N){
    ELEMENT aux = x->bytes.ARRAY->stack[N];
    push(stack, aux.bytes, aux.type);
}

void push_array_to_stack(STACK *stack, ELEMENT *x){
    for (int p = 0; p < x->bytes.ARRAY->stack_pointer; p++){
        ELEMENT aux = x->bytes.ARRAY->stack[p];
        push(stack, aux.bytes, aux.type);
    }
}

void captura_inicio_array(STACK *stack, ELEMENT *x, int N){
    x->bytes.ARRAY->stack_pointer = N;
    push(stack, x->bytes, x->type);
}

void captura_fim_array(STACK *stack, ELEMENT *x, int N){
    int indice = x->bytes.ARRAY->stack_pointer - N;
    for (int p = 0; indice < x->bytes.ARRAY->stack_pointer; p++, indice++){
        x->bytes.ARRAY->stack[p] = x->bytes.ARRAY->stack[indice];
    }
    x->bytes.ARRAY->stack_pointer = N;
    push(stack, x->bytes, x->type);
}



void read_all_input(STACK *stack){
    ELEMENT x;
    char linha[1000], *frase = malloc(100);
    while (fgets (linha, 1000, stdin) != NULL){
        int N = strlen(linha);
        int M = strlen(frase);
        frase = realloc(frase, N + M);
        strcat(frase,linha);
    }
    x.type = STRING;
    x.bytes.STRING = strdup(frase);
    push(stack, x.bytes, x.type);
}



void whitespace(STACK *stack){
    ELEMENT x, y = pop(stack);
    x.type = ARRAY;
    x.bytes.ARRAY = malloc(sizeof(STACK));
    x.bytes.ARRAY->stack = malloc(ARRAY_SIZE*sizeof(ELEMENT));
    char *string = strdup(y.bytes.STRING), *token;
    char *resto = string;
	while ((token = strtok_r(resto, " " "\n", &resto))){
        ELEMENT aux;
        aux.type = STRING;
        aux.bytes.STRING = strdup(token);
        x.bytes.ARRAY->stack[x.bytes.ARRAY->stack_pointer++] = aux;
	}
	push(stack, x.bytes, x.type);
}


void separa_substring(STACK *stack, ELEMENT *x, ELEMENT *y){
    ELEMENT z;
    z.type = ARRAY;
    z.bytes.ARRAY = malloc(sizeof(STACK));
    z.bytes.ARRAY->stack = malloc(ARRAY_SIZE*sizeof(ELEMENT));
    char *string = strdup(y->bytes.STRING), *limite = strdup(x->bytes.STRING), *token;
	token = strtok(string,limite);
    while (token != NULL){
        ELEMENT aux;
        aux.type = STRING;
        aux.bytes.STRING = strdup(token);
        z.bytes.ARRAY->stack[z.bytes.ARRAY->stack_pointer++] = aux;
		token = strtok(NULL,limite);
	}
	push(stack, z.bytes, z.type);
}


void new_lines(STACK *stack){
    ELEMENT x, y = pop(stack);
    x.type = ARRAY;
    x.bytes.ARRAY = malloc(sizeof(STACK));
    x.bytes.ARRAY->stack = malloc(ARRAY_SIZE*sizeof(ELEMENT));
    char *string = strdup(y.bytes.STRING), limite[2] = "\n", *token;
	token = strtok(string,limite);
	while (token != NULL){
        ELEMENT aux;
        aux.type = STRING;
        aux.bytes.STRING = strdup(token);
        x.bytes.ARRAY->stack[x.bytes.ARRAY->stack_pointer++] = aux;
		token = strtok(NULL,limite);
	}
	push(stack, x.bytes, x.type);
}


ELEMENT clone(ELEMENT x){
    ELEMENT new;
    new.bytes.ARRAY = malloc(sizeof(STACK));
    new.bytes.ARRAY->stack = malloc(ARRAY_SIZE*sizeof(STACK));
    new.bytes.ARRAY->stack_size = ARRAY_SIZE;
    for (int p = 0; p < x.bytes.ARRAY->stack_pointer; p++){
        new.bytes.ARRAY->stack[new.bytes.ARRAY->stack_pointer++] = x.bytes.ARRAY->stack[p];
    }
    return new;
}