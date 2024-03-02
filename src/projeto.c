/**
 * Ficheiro projeto.c:
 * 
 * Ficheiro onde se encontram definidas as funções responsáveis pela verificação do token.
 * 
 * Ficheiro que contém a função "main" ---> principal função do programa.
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define alfabeto 26
#include "stack.h"
#define MAX_STACK 1000


/**
 * Função printArray:
 * 
 * Função responsável pelos prints dos valores num array.
 * 
 * Como o nosso array está definido como sendo uma STACK então é necessário criar outra função quase idêntica à que faz os prints da stack só que aplicada aos arrays.
 * 
 * Pode ser chamada recursivamente para fazer prints de arrays dentro de arrays.
 */


void printArray(STACK *s){
    for(int i = 0;i < s->sp;i++)
        {
        if(s->stack[i].t == CHAR) printf("%c",s->stack[i].saved_Value.c);
        if(s->stack[i].t == STR) printf("%s",s->stack[i].saved_Value.str);
        if(s->stack[i].t == BLOCO) printf("%s",s->stack[i].saved_Value.bloco);
        if(s->stack[i].t == DBL) printf("%g",s->stack[i].saved_Value.d);
        if(s->stack[i].t == LNG) printf("%ld",s->stack[i].saved_Value.l);
        if(s->stack[i].t == ARRAY) printArray(s->stack[i].saved_Value.array);
        }
}


/**
 * Função print:
 * 
 * Função responsável pelos prints dos valores numa stack.
 */


void print(STACK *s){
    for(int i = 0;i < s->sp;i++)
        {
        if(s->stack[i].t == CHAR) printf("%c",s->stack[i].saved_Value.c);
        if(s->stack[i].t == STR) printf("%s",s->stack[i].saved_Value.str);
        if(s->stack[i].t == BLOCO) printf("%s",s->stack[i].saved_Value.bloco);
        if(s->stack[i].t == DBL) printf("%g",s->stack[i].saved_Value.d);
        if(s->stack[i].t == LNG) printf("%ld",s->stack[i].saved_Value.l);
        if(s->stack[i].t == ARRAY) printArray(s->stack[i].saved_Value.array);
        }
        printf("\n");
}


/**
 * Função verificarString:
 * 
 * Função responsável por verificar se o token recebido possui uma string no mesmo.
 * 
 * A função recebe um token e "corta" as aspas das extremidades.
 * 
 * No fim retorna esse token atualizado para a função operações.
 */


char* verificarString(char** str){
    if(*str[0] == '\"'){
        char *copiado = strdup(*str);
        copiado++;
        char *limite = "\"";
        char *ocorre = strstr(copiado,limite);
        int index = ocorre - copiado;
        copiado[index] = '\0';
        return copiado;
    }
    return NULL;
}


/**
 * Função verificarBloco:
 * 
 * Função responsável por verificar se o token recebido possui um bloco no mesmo.
 * 
 * Se tiver um bloco então vai ver onde se encontra o último "}" e vai cortar o token logo após a posição desse parênteses final. 
 * 
 * No fim retorna esse token para a função operações.
 */


char* verificarBloco(char **str){
    if(*str[0] == '{'){
        char *aux = strdup(*str);
        int fechados = 0,abertos = 0,delimita = 1,posicao = 0;
        for(posicao = 1; delimita;posicao++){
            if(aux[posicao] == '{') abertos++;
            else if(aux[posicao] == '}'){
                if(abertos == fechados){
                    aux[posicao + 1] = '\0';
                    delimita = 0;
                }
                else fechados++;
            }
        }
        return aux;
    }
    return NULL;
}


/**
 * Função verificarToken:
 *
 * Recebe um token e devolve o mesmo até à posição onde se encontra o primeiro espaço.
 */


char* verificarToken(char** str){
    char* delimita = " ";
    char *token = strtok_r(*str,delimita,str);
    return token;
}


/**
 * Função verificarArray:
 * 
 * Função responsável por verificar se o token recebido possui um array no mesmo.
 * 
 * Se tiver um array então vai "cortar" os parênteses retos das extremidades e retornar esse token para a função "operacoes".
 */


char* verificarArray(char** str){
    if(*str[0] == '['){
        char *aux = strdup(*str);
        aux += 2;
        int fechados = 0,abertos = 0,delimita = 1,posicao = 0;
        for(posicao = 0; delimita;posicao++){
            if(aux[posicao] == '[') abertos++;
            else if(aux[posicao] == ']'){
                if(abertos == fechados){
                    aux[posicao] = '\0';
                    delimita = 0;
                }
                else fechados++;
            }
        }
        return aux;
    }
    return NULL;
}


/**
 * Função operacoes:
 * 
 * Função responsável por ler a linha com os valores e operações e dividir a mesma por vários tokens que depois serão avaliados pela função "handle".
 * 
 * Nesta função ainda é feita uma verificação do token dado e dividimos o mesmo em vários casos: token, string, array ou bloco.
 */



void operacoes(STACK *s,stack_Elem *lista,char *linha)
{
    stack_Elem j;
    char* str = linha;
    while(*str != '\0'){
        char* token;
        if((token = verificarString(&str)) != NULL){
            j.t = STR;
            j.saved_Value.str = verificarString(&str);
            push(s,j);
            str += strlen(token) + 3;
        }
        else if((token = verificarBloco(&str)) != NULL){
            j.t = BLOCO;
            j.saved_Value.bloco = token;
            push(s,j);
            str += strlen(token) + 1;
        }
        else if((token = verificarArray(&str)) != NULL){
            STACK *array = new_stack();
            str += strlen(token) + 4;
            operacoes(array,lista,token);
            stack_Elem arr = (stack_Elem) {.t = ARRAY, .saved_Value.array = array};
            push(s,arr);
        }
        else if((token = verificarToken(&str)) != NULL){
            handle(s,lista,token);
        }
    }
}
    


/**
 * Função main:
 * 
 * Principal função do projeto responsável por ler o input e rodar o programa para a linha(s) lidas.
 */


int main(){
    STACK *s = new_stack();
    stack_Elem lista[alfabeto];
    criarVariaveis(lista); 
    char linha[BUFSIZ]; 
     if(fgets(linha,BUFSIZ,stdin) != NULL){
        int tamanho = strlen(linha);
        linha[tamanho-1] = '\0';
        operacoes(s,lista,linha);
     }
    print(s);
    free(s);
    return 0;
}