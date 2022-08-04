#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "guiao1.h"
#include "guiao2.h"
#include "guiao3.h"
#include "guiao4.h"
#include "guiao5.h"


int main(){
    STACK *pointer = new_stack();
    VAR_LIST *var_list = (VAR_LIST*) malloc(sizeof(VAR_LIST));
    int aux = 0, iter = 0, size, sp_lista[100], *N, aux_N = 0;
    N = &aux_N;
    char *line = malloc(ARRAY_SIZE*sizeof(char));
    char *token = malloc(ARRAY_SIZE*sizeof(char));
    if (fgets(line, ARRAY_SIZE, stdin) != NULL){
        strcpy(token, line);
        size = strlen(token);
        while (iter < size){
            if (token[iter] == '\"'){
                iter = found(token,iter);
            }
            else if (token[iter] == '{'){
                iter = found_bloco(token,iter);
            }
            iter = put_zero(token, iter);
        }
        while (aux < size){
          //  printf("token ->%s<-\n", token);
            handle(pointer,token,var_list,sp_lista,N);
            iter = strlen(token);
            iter++;
            token = &(token[iter]);
            aux += iter;
        }
      //  printf("sp:%d\n", pointer->stack_pointer);
        print_stack(pointer);
        putchar('\n');
    }
//    printf("stack pointer: ->%d<-\n", pointer->stack_pointer);
    return 0;
}