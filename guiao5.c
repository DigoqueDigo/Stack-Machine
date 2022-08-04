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



void inicializa_bloco(STACK *stack, char *bloco){
    ELEMENT x;
    x.type = BLOCO;
    x.bytes.BLOCO = strdup(bloco);
    push(stack, x.bytes, x.type);
}


void operacoes(STACK *stack, ELEMENT *x, VAR_LIST *var_list, int sp_lista[], int *N){
    ELEMENT principal = pop(stack);
    ELEMENT y;
    int iter = 0, size = strlen(x->bytes.BLOCO), auxs = 0;
    if (principal.type != BLOCO){
        STACK *new = new_stack();
        push(new, principal.bytes, principal.type);
        while (iter < size){
            if (x->bytes.BLOCO[iter] == '\"') iter = found(x->bytes.BLOCO,iter);
            iter = put_zero(x->bytes.BLOCO, iter);
        }   
        while (auxs < size){
            handle(new,x->bytes.BLOCO,var_list,sp_lista,N);
            iter = strlen(x->bytes.BLOCO);
            iter++;
            x->bytes.BLOCO = &(x->bytes.BLOCO[iter]);
            auxs += iter;
        }
        for (int k = 0; k < new->stack_pointer; k++){
            y = new->stack[k];
            stack->stack[stack->stack_pointer++] = y;
        }
        free(new);
    }
}


void operacoes_array(STACK *stack, ELEMENT *bloco, ELEMENT *x, VAR_LIST *var_list, int sp_lista[], int *N){
    ELEMENT auxiliar;
    auxiliar.type = ARRAY;
    auxiliar.bytes.ARRAY = malloc(sizeof(STACK));
    auxiliar.bytes.ARRAY->stack = malloc(ARRAY_SIZE*sizeof(ELEMENT));
    auxiliar.bytes.ARRAY->stack_pointer = 0;
    ELEMENT aux, y;
    int iter = 0, size = strlen(bloco->bytes.BLOCO), auxs = 0;
    char *auxbloco = strdup(bloco->bytes.BLOCO);
    for (int p = 0; p < x->bytes.ARRAY->stack_pointer; p++, auxs = 0, iter = 0, bloco->bytes.BLOCO = strdup(auxbloco)){
        STACK *new = new_stack();
        aux = x->bytes.ARRAY->stack[p];
        push(new, aux.bytes, aux.type);
        while (iter < size){
            if (bloco->bytes.BLOCO[iter] == '\"') iter = found(bloco->bytes.BLOCO,iter);
            iter = put_zero(bloco->bytes.BLOCO, iter);
        }
        while (auxs < size){
            handle(new,bloco->bytes.BLOCO,var_list,sp_lista,N);
            iter = strlen(bloco->bytes.BLOCO);
            iter++;
            bloco->bytes.BLOCO = &(bloco->bytes.BLOCO[iter]);
            auxs += iter;
        }
        for (int k = 0; k < new->stack_pointer; k++){
            y = new->stack[k];
            auxiliar.bytes.ARRAY->stack[auxiliar.bytes.ARRAY->stack_pointer++] = y;
        }
        free(new->stack);
        free(new);
    }
    push(stack, auxiliar.bytes, auxiliar.type);
}


void operacoes_string(STACK *stack, ELEMENT *bloco, ELEMENT *x, VAR_LIST *var_list, int sp_lista[], int *N){
    ELEMENT aux, y;
    int iter = 0, size = strlen(bloco->bytes.BLOCO), auxs = 0, tamanho = strlen(x->bytes.STRING), i = 0;
    char *auxbloco = strdup(bloco->bytes.BLOCO), final, *string = malloc(1000);
    for (int p = 0; p < tamanho; p++, auxs = 0, iter = 0, bloco->bytes.BLOCO = strdup(auxbloco)){
        STACK *new = new_stack();
        aux.bytes.CHAR = x->bytes.STRING[p];
        push(new, aux.bytes, CHAR);
        while (iter < size){
            if (bloco->bytes.BLOCO[iter] == '\"') iter = found(bloco->bytes.BLOCO,iter);
            iter = put_zero(bloco->bytes.BLOCO, iter);
        }
        while (auxs < size){
            handle(new,bloco->bytes.BLOCO,var_list,sp_lista,N);
            iter = strlen(bloco->bytes.BLOCO);
            iter++;
            bloco->bytes.BLOCO = &(bloco->bytes.BLOCO[iter]);
            auxs += iter;
        }
        for (int indice = 0; indice < new->stack_pointer; indice++, i++){
            y = new->stack[indice];
            final = y.bytes.CHAR;
            string[i] = final;
        }
        free(new);
    }
    x->bytes.STRING = strdup(string);
    push(stack, x->bytes, x->type);
}


int verifica_valor(ELEMENT *x){
    int valor = 0;
    if (x->type == INT && x->bytes.INT != 0) valor = 1;
    else if ((x->type == CHAR && x->bytes.CHAR != '\0') || (x->type == ARRAY && x->bytes.ARRAY->stack_pointer != 0)) valor = 1;
    else if (x->type == STRING && strlen(x->bytes.STRING) != 0) valor = 1;
    return valor;
}

void filter_array(STACK *stack, ELEMENT *bloco, ELEMENT *x, VAR_LIST *var_list, int sp_lista[], int *N){
    ELEMENT aux, y;
    int iter = 0, size = strlen(bloco->bytes.BLOCO), auxs = 0, acc = 0;
    char *auxbloco = strdup(bloco->bytes.BLOCO);
    STACK *new = new_stack();
    for (int p = 0; p < x->bytes.ARRAY->stack_pointer; p++, auxs = 0, iter = 0, bloco->bytes.BLOCO = strdup(auxbloco)){
        aux = x->bytes.ARRAY->stack[p];
        push(new, aux.bytes, aux.type);
        while (iter < size){
            if (bloco->bytes.BLOCO[iter] == '\"') iter = found(bloco->bytes.BLOCO,iter);
            iter = put_zero(bloco->bytes.BLOCO, iter);
        }
        while (auxs < size){
            handle(new,bloco->bytes.BLOCO,var_list,sp_lista,N);
            iter = strlen(bloco->bytes.BLOCO);
            iter++;
            bloco->bytes.BLOCO = &(bloco->bytes.BLOCO[iter]);
            auxs += iter;
        }
        y = new->stack[0];
        int valor = verifica_valor(&y);
        if (valor != 0){
            x->bytes.ARRAY->stack[acc] = aux;
            acc++;
        }
        solta_stack(new);
    }
    x->bytes.ARRAY->stack_pointer = acc;
    push(stack, x->bytes, x->type);
}


// E sabido que o x é um bloco

void aux_operador_virgula(STACK *stack, ELEMENT *bloco, VAR_LIST *var_list, int sp_lista[], int *N){
    ELEMENT y = pop(stack);
    if (y.type == ARRAY){
        filter_array(stack,bloco,&y,var_list,sp_lista,N);
    }
}

void converte_string_to_int(ELEMENT *x){
    int y = atoi(x->bytes.STRING);
    x->bytes.INT = y;
    x->type = INT;
}

void converte_string_to_double(ELEMENT *x){
    char *resto;
    double y = strtod(x->bytes.STRING,&resto);
    x->bytes.DOUBLE = y;
    x->type = DOUBLE;
}


void flodl(STACK *stack, ELEMENT *bloco, ELEMENT *x, VAR_LIST *var_list, int sp_lista[], int *N){
    ELEMENT aux, y = x->bytes.ARRAY->stack[0], *t = malloc(sizeof(ELEMENT));
    int iter = 0, size = strlen(bloco->bytes.BLOCO), auxs = 0, j;
    char *auxbloco = strdup(bloco->bytes.BLOCO);
    STACK *new = new_stack();
    push(new, y.bytes, y.type);
    t->type = ARRAY;
    t->bytes.ARRAY = malloc(sizeof(STACK));
    t->bytes.ARRAY->stack = malloc(1000000);
    t->bytes.ARRAY->stack_size = ARRAY_SIZE;
    if (x->bytes.ARRAY->stack_pointer >= 1){
        for (int p = 1; p < x->bytes.ARRAY->stack_pointer; p++, auxs = 0, iter = 0, bloco->bytes.BLOCO = strdup(auxbloco)){
            aux = x->bytes.ARRAY->stack[p];
            push(new, aux.bytes, aux.type);
            while (iter < size){
                if (bloco->bytes.BLOCO[iter] == '\"') iter = found(bloco->bytes.BLOCO,iter);
                iter = put_zero(bloco->bytes.BLOCO, iter);
            }
            while (auxs < size){
                handle(new,bloco->bytes.BLOCO,var_list,sp_lista,N);
                iter = strlen(bloco->bytes.BLOCO);
                iter++;
                bloco->bytes.BLOCO = &(bloco->bytes.BLOCO[iter]);
                auxs += iter;
            }
        }
    }
    for (j = 0; j < new->stack_pointer; j++){
            t->bytes.ARRAY->stack[j] = new->stack[j];
        }
    t->bytes.ARRAY->stack_pointer = j;
    push(stack, t->bytes, t->type);
}


// Função que calcula o maior valor de um array de valores

int max_valor(VALOR_LISTA *vetor, int N){
    int max = vetor->lista[0].valor, r = 0;
    for (int p = 1; p < N; p++){
        if (vetor->lista[p].valor > max){
            max = vetor->lista[p].valor;
            r = p;
        }
    }
    return r;
}

// Função que troca dois elementos de uma array de valores

void swap(VALOR_LISTA *vetor, int x, int N){
    VALOR temp = vetor->lista[x];
    vetor->lista[x] = vetor->lista[N-1];
    vetor->lista[N-1] = temp;
}

// Função que ordena um 

void max_sort(VALOR_LISTA *vetor){
    int aux, N = vetor->tamanho;
    for (; N > 0; N--){
        aux = max_valor(vetor,N);
        swap(vetor,aux,N);
    }
}

// Função que ordena um array conforme um parametro


void ordena(STACK *stack, ELEMENT *bloco, ELEMENT *x, VAR_LIST *var_list, int sp_lista[], int *N){
    ELEMENT aux;
    int iter = 0, size = strlen(bloco->bytes.BLOCO), auxs = 0;
    char *auxbloco = strdup(bloco->bytes.BLOCO);
    VALOR_LISTA *vetor = malloc(sizeof(struct valor_array)); 
    vetor->tamanho = 0;
    for (int p = 0; p < x->bytes.ARRAY->stack_pointer; p++, auxs = 0, iter = 0, bloco->bytes.BLOCO = strdup(auxbloco)){
        VALOR temp;
        STACK *new = new_stack();
        aux = x->bytes.ARRAY->stack[p];
        push(new, aux.bytes, aux.type);
        while (iter < size){
            if (bloco->bytes.BLOCO[iter] == '\"') iter = found(bloco->bytes.BLOCO,iter);
            iter = put_zero(bloco->bytes.BLOCO, iter);
        }
        while (auxs < size){
            handle(new,bloco->bytes.BLOCO,var_list,sp_lista,N);
            iter = strlen(bloco->bytes.BLOCO);
            iter++;
            bloco->bytes.BLOCO = &(bloco->bytes.BLOCO[iter]);
            auxs += iter;
        }
        temp.elemento = x->bytes.ARRAY->stack[p];
        temp.valor = new->stack[0].bytes.INT;
        vetor->lista[vetor->tamanho++] = temp;
        free(new);
    }
    max_sort(vetor);
    for (int a = 0; a < vetor->tamanho; a++){
        x->bytes.ARRAY->stack[a] = vetor->lista[a].elemento;
    }
    push(stack, x->bytes, x->type);
}


void print_valores(VALOR_LISTA *vetor){
    for (int p = 0; p < vetor->tamanho; p++){
        printf("elemento: ");
        print_element(&(vetor->lista[p].elemento));
        putchar('\n');
        printf("valor: %d\n", vetor->lista[p].valor);
    }
}

// função que executa um bloco enquanto a condição no topo da stack auxiliar é verdadeira


void whiler(STACK *stack, ELEMENT *bloco, VAR_LIST *var_list, int sp_lista[], int *N){
    ELEMENT aux, y, thrutly;
    thrutly.type = INT;
    thrutly.bytes.INT = 1;
    int iter = 0, size = strlen(bloco->bytes.BLOCO), auxs = 0, h = 0;
    char *auxbloco = strdup(bloco->bytes.BLOCO);
    while(verifica_valor(&thrutly)){
        for (int p = 0; p < stack->stack_pointer; p++, auxs = 0, iter = 0, bloco->bytes.BLOCO = strdup(auxbloco), var_list = clone_var_list(var_list)){
            STACK *new = new_stack();
            aux = stack->stack[p];
            push(new, aux.bytes, aux.type);
            while (iter < size){
                if (bloco->bytes.BLOCO[iter] == '\"') iter = found(bloco->bytes.BLOCO,iter);
                iter = put_zero(bloco->bytes.BLOCO, iter);
            }
            while (auxs < size){
                handle(new,bloco->bytes.BLOCO,var_list,sp_lista,N);
                iter = strlen(bloco->bytes.BLOCO);
                iter++;
                bloco->bytes.BLOCO = &(bloco->bytes.BLOCO[iter]);
                auxs += iter;
            }
            y = new->stack[0];
            stack->stack[p] = y;
            thrutly = new->stack[new->stack_pointer-1];
            free(new);
            h++;
        }
    }
}

void aux_whiler(STACK *stack, VAR_LIST *var_list, int sp_lista[], int *N){
    ELEMENT bloco = pop(stack);
 //   printf("sp ->%d<-\n", stack->stack_pointer);
    whiler(stack,&bloco,var_list,sp_lista,N);
}


void print_var_list(VAR_LIST *var_list){
    for (int p = 0; p < var_list->var_sp; p++){
        printf("letra: %c\n", var_list->vetor[p].letra);
        printf("conteudo: %d\n", var_list->vetor[p].variavel.INT);
    }
}


VAR_LIST* clone_var_list(VAR_LIST *lista){
    VAR_LIST *new = malloc(sizeof(struct array_var));
    new->var_sp = lista->var_sp;
    for (int p = 0; p < lista->var_sp; p++){
        new->vetor[p] = lista->vetor[p];
    }
    return new;
}

void solta_stack(STACK *stack){
    int N = stack->stack_pointer;
    for (int p = 0; p < N; p++, pop(stack));
}