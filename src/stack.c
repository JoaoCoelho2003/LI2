/**
 * Ficheiro stack.c:
 * 
 * Ficheiro onde se encontram definidas as principais funções da stack utilizada no projeto.
 */


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stack.h"

/**
 * Função new_stack:
 * 
 * Função que cria e aloca espaço para a stack que será utilizada pelo programa.
 */


STACK *new_stack(){                                 
    STACK *s = malloc(sizeof(STACK));
    s-> sp = 0;
    s-> capacidade = 0;
    return s;
}


/**
 * Função push:
 * 
 * Função que coloca o stack_Elem dado como argumento no topo da stack.
 */


void push(STACK *s,stack_Elem elem){
    if(s-> sp == s-> capacidade){
        if(s->capacidade == 0) s->stack = (stack_Elem*)realloc(NULL,(++s->capacidade) * sizeof(stack_Elem));
        else{
            s->stack = (stack_Elem*)realloc(s->stack,2 * s->capacidade * sizeof(stack_Elem));
            s->capacidade *= 2;
        }
    }
    s->stack[s->sp++] = elem;   
}


/**
 * Função pop:
 * 
 * Função que retira o stack_Elem que se encontra no topo da stack.
 */


stack_Elem pop(STACK *s){
    assert(s->sp > 0);
    return s->stack[--s->sp];
}