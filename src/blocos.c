/**
 * Ficheiro blocos.c:
 * 
 * Ficheiro onde se encontram definidas as funções responsáveis pelo guião 5 do projeto.
 */


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"


/**
 * Função executaBloco:
 * 
 * A função aplica o que está dentro do bloco ao elemento da stack que se encontra antes do mesmo.
 * 
 * Exemplo: [ 1 2 3 ] { 2 * } ~ = 123123
 *          2 { 3 * } ~ = 6
 */


void executaBloco(STACK *s,stack_Elem *l, char *str){
    char *aux = strdup(str);
    aux += 2;
    int fechados = 0,abertos = 0,delimita = 1,posicao = 0;
    for(posicao = 0; delimita;posicao++){
        if(aux[posicao] == '{') abertos++;
        else if(aux[posicao] == '}'){
            if(abertos == fechados){
                aux[posicao] = '\0';
                delimita = 0;
            }
            else fechados++;
        }
    }
    operacoes(s,l,aux);
}


/**
 * Função copiaParaStrings:
 * 
 * Copia todos os elementos de um array para uma string.
 * 
 */


void copiaParaString(stack_Elem x,char *str){
    for(int i = 0; i < x.saved_Value.array->sp;i++){
        if(x.saved_Value.array->stack[i].t == CHAR) str[i] = x.saved_Value.array->stack[i].saved_Value.c;
        if(x.saved_Value.array->stack[i].t == DBL) str[i] = x.saved_Value.array->stack[i].saved_Value.d;
        if(x.saved_Value.array->stack[i].t == LNG) str[i] = x.saved_Value.array->stack[i].saved_Value.l;
        if(x.saved_Value.array->stack[i].t == STR){
            int j = 0;
            int l = i;
            while(x.saved_Value.array->stack[i].saved_Value.str[j] != '\0'){
                str[l] = x.saved_Value.array->stack[i].saved_Value.str[j];
                j++;
                l++;
            }
            i = l;
        }
    }
}


/**
 * Função aplicarBloco:
 * 
 * Função que aplica o conteúdo do bloco a cada membro do array/string e depois faz push para a stack de um array/string com os novos valores obtidos.
 * 
 * Exemplo: [ 1 2 3 ] { 2 * } % = 246;
 *          "ola" { _ } % = oollaa
 */


void aplicarBloco (STACK *s,stack_Elem *l, stack_Elem x,stack_Elem y){
    char *str = x.saved_Value.bloco;
    stack_Elem arr;
    arr.t = ARRAY;
    arr.saved_Value.array = new_stack();
    if(y.t == ARRAY){
        for(int i = 0; i < y.saved_Value.array->sp;i++){
            char *aux = strdup(str);
            push(arr.saved_Value.array,y.saved_Value.array->stack[i]);
            executaBloco(arr.saved_Value.array,l,aux);
        }
        push(s,arr);
    }
    if(y.t == STR){
        for(int i = 0; y.saved_Value.str[i] != '\0';i++){
            char *aux = strdup(str);
            stack_Elem letra;
            letra.t = CHAR;
            letra.saved_Value.c = y.saved_Value.str[i];
            push(arr.saved_Value.array,letra);
            executaBloco(arr.saved_Value.array,l,aux);
        }
        char *lista = malloc(arr.saved_Value.array->sp * sizeof(char) * 2);
        copiaParaString(arr,lista);
        stack_Elem result;
        result.t = STR;
        result.saved_Value.str = lista;
        push(s,result);
    }
}


/**
 * Função fold:
 * 
 * Adaptação da função fold de Haskell para C.
 * 
 * Esta função só pode ser aplicada a arrays.
 * 
 * Combina os elementos do array a partir do conteúdo do bloco de uma maneira sistemática.
 * 
 * Exemplo: [ 1 2 3 4 5 ] { * } * = (1 * ( 2 * ( 3 * ( 4 * ( 5))))) = 120
 *          [ 2 4 6 8 10 ] { + } * = (2 + ( 4 + ( 6 + ( 8 + ( 10))))) = 30
 */


void fold(STACK *s,stack_Elem *l,stack_Elem x,stack_Elem y){
    char *str = x.saved_Value.bloco;
    stack_Elem arr;
    arr.t = ARRAY;
    arr.saved_Value.array = new_stack();
    for(int i = 0;i < y.saved_Value.array->sp;i++){
        char *aux = strdup(str);
        push(arr.saved_Value.array,y.saved_Value.array->stack[i]);
        if(arr.saved_Value.array->sp > 1) executaBloco(arr.saved_Value.array,l,aux);
    }
    push(s,arr);
}


/**
 * Função verificaVerdadeiro:
 * 
 * Função auxiliar de "filtrar" e "whileTruthy".
 * 
 * Função que verifica se o valor do stack_Elem é verdadeiro ou não.
 * 
 * Retorna 0 caso seja falso e 1 caso seja verdadeiro.
 * 
 */


int verificaVerdadeiro(stack_Elem y){
    int r = 1;
    if(y.t == LNG){
        if(y.saved_Value.l == 0) r = 0;
    }
    else if(y.t == DBL){
        if(y.saved_Value.d == 0) r = 0;
    }
    else if(y.t == STR){
        for(int i = 0; y.saved_Value.str[i] != '\0';i++){
            if(y.saved_Value.str[i] == 0) r = 0;
        }
    }
    else if(y.t == CHAR){
        if(y.saved_Value.c == 0) r = 0;
    }
    return r;
}


/**
 * Função filtrar:
 * 
 * Função que aplica a "executaBloco" a cada elemento da string/array e caso o valor seja verdadeiro ( ou seja != 0) o mesmo será adicionado a uma nova 
 * string/array que conterá apenas os valores com valor lógico verdadeiro, caso contrário o valor não é adicionado a essa nova estrutura e a função começa
 * a inspecionar o próximo elemento.
 * 
 * A função faz push para a stack da nova string/array que contém os elementos com valor lógico verdadeiro.
 * 
 * Exemplo: [ 2 3 4 5 ] { 2 % } , = 35
 *          "2345" { i 2 % } , = 35
 */


void filtrar(STACK *s,stack_Elem *l,stack_Elem x,stack_Elem y){
    char *str = x.saved_Value.bloco;
    stack_Elem arr;
    arr.t = ARRAY;
    arr.saved_Value.array = new_stack();
    if(y.t == ARRAY){
        stack_Elem result;
        result.t = ARRAY;
        result.saved_Value.array = new_stack();
        for(int i = 0; i < y.saved_Value.array->sp;i++){
            char *aux = strdup(str);
            push(arr.saved_Value.array,y.saved_Value.array->stack[i]);
            executaBloco(arr.saved_Value.array,l,aux);
        }
        for(int i = 0; i < arr.saved_Value.array->sp;i++){
            if(verificaVerdadeiro(arr.saved_Value.array->stack[i])) push(result.saved_Value.array,y.saved_Value.array->stack[i]);
        }
        push(s,result);
    }
    if(y.t == STR){
        for(int i = 0; y.saved_Value.str[i] != '\0';i++){
            char *aux = strdup(str);
            stack_Elem letra;
            letra.t = CHAR;
            letra.saved_Value.c = y.saved_Value.str[i];
            push(arr.saved_Value.array,letra);
            executaBloco(arr.saved_Value.array,l,aux);
        }
        stack_Elem lista;
        lista.t = STR;
        lista.saved_Value.str = malloc(strlen(y.saved_Value.str) * sizeof(char));
        int pos = 0;
        for(int i = 0; y.saved_Value.str[i] != '\0';i++){
            if(verificaVerdadeiro(arr.saved_Value.array->stack[i])){
                lista.saved_Value.str[pos] = y.saved_Value.str[i];
                pos++;
            }
        }
        push(s,lista);
    }
}


/**
 * Função swap:
 * 
 * Função auxiliar de "ssort".
 * 
 * Função que troca o conteúdo de 2 stack_Elem que se encontram na posição i e j.
 * 
 */


void swap(stack_Elem x, int i, int j){
    stack_Elem aux = x.saved_Value.array->stack[i];
    x.saved_Value.array->stack[i] = x.saved_Value.array->stack[j];
    x.saved_Value.array->stack[j] = aux;
}


/**
 * Função ssort:
 * 
 * Função auxiliar de "ordenaViaBloco".
 * 
 * Função responsável por ordenar um array(stack).
 * 
 * Adaptação do método de ordenação "selection sort" para a nossa definição de stack.
 */


void ssort(stack_Elem x,stack_Elem y,int n) {
    int i, j, m;
    for (i = n; i > 0; i--) {
        m = 0;
    for (j = 0; j < i; j++)
        if(maiorAux(x.saved_Value.array->stack[m].t,x.saved_Value.array->stack[m],x.saved_Value.array->stack[j])) m = j;
    swap(x, i-1, m);
    swap(y, i-1, m);
    }
}


/**
 * Função ordenaViaBloco:
 * 
 * Utiliza o método de ordenação apresentado anteriormente para ordenar o array recebido como argumento (stack_Elem y) a partir dos resultados obtidos através
 * da "executaBloco" aplicada a cada elemento do array "arr"(cópia exata do stack_Elem y).
 * 
 * Exemplo:  [ "ola" "adeus" "bomdia" "a" ] { , } $ = aolaadeusbomdia;
 *           [ 5 3 2 4 1 ] { } $ = 12345;
 * 
 */


void ordenaViaBloco(STACK *s,stack_Elem *l,stack_Elem x,stack_Elem y){
    char *str = x.saved_Value.bloco;
    stack_Elem arr;
    arr.t = ARRAY;
    arr.saved_Value.array = new_stack();
    for(int i = 0; i < y.saved_Value.array->sp;i++){
        char *aux = strdup(str);
        push(arr.saved_Value.array,y.saved_Value.array->stack[i]);
        executaBloco(arr.saved_Value.array,l,aux);
    }
    ssort(arr,y,arr.saved_Value.array->sp);
    push(s,y);
}


/**
 * Função whileTruthy:
 * 
 * A função vai aplicando de maneira cíclica a função "executaBloco" ao stack_Elem y e no fim faz sempre pop do valor obtido através da aplicação dessa função.
 * Enquanto o valor retirado(y = pop) seja verdadeiro(!= 0) o ciclo vai proceder.
 * 
 * Exemplo: 1 { C *C ( :C } w = 479001600
 */


int whileTruthy(STACK *s,stack_Elem *l,char *token){
    if(token[0] == 'w'){
        stack_Elem x = pop(s);
        char *str = x.saved_Value.bloco;
        char *copiado = strdup(str);
        executaBloco(s,l,str);
        stack_Elem y = pop(s);
        if(!verificaVerdadeiro(y)){
            push(s,y);
        }
        else{
            while(verificaVerdadeiro(y)){
                char *aux = strdup(copiado);
                executaBloco(s,l,aux);
                y = pop(s);
            }
        }
        return 1;
    }
    return 0;
}