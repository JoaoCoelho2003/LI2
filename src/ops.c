/**
 * Ficheiro ops.c:
 * 
 * Ficheiro onde se encontram definidas as funções responsáveis pelos primeiros guiões do projeto.
 * 
 * Neste ficheiro também se encontra a função "handle" --> uma das principais funções do programa.
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"


/**
 * Função lerToken:
 * 
 * Função que verifica se existe algum ponto nos tokens verificados, caso existir devolve 1, caso contrário devolve 0.
 * 
 * É usada como função auxiliar da função "pushToken".
 */


int lerToken(char *token){
    int pontos = 0,r;
    for(int i = 0; token[i] != '\0';i++){
        if(token[i] == '.') pontos++;
    }
    if(pontos != 0){
        r = 1;
    }
    else{
        r = 0;
    }
    return r;
}


/**
 * Função pushToken:
 * 
 * Função que, caso exista um ponto nos tokens avaliados, conclui que o valor é um double e faz push do mesmo, caso contrário o valor será um long e também será
 * feito o push do valor. 
 * 
 * É esta função que permite que seja reconhecido o valor que é inserido no terminal, logo acaba por ser uma das principais "peças" do programa já que sem ela nenhum
 * resultado apareceria no terminal.
 */


int pushToken(STACK *s,char *token){
    stack_Elem j;
    if(lerToken(token)){
        double resultado;
        sscanf(token,"%lg",&resultado);
        push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = resultado});
    }
    else{
        long resultado;
        sscanf(token,"%ld",&resultado);
        push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = resultado});
    }
    return 1;
}


/**
 * Função somarLong:
 * 
 * Função que avalia os casos onde o primeiro valor retirado, um dos membros da operação, é um long.
 * 
 * Faz push do resultado da operação somar para todos os tipos possiveis do outro membro.
 * 
 * É usada como função auxiliar da função "somar".
 */


void somarLong(STACK *s,stack_Elem x,stack_Elem y){
    stack_Elem j;
    if(y.t == LNG){
        push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = x.saved_Value.l + y.saved_Value.l});
    }
    if(y.t == CHAR){
        push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = x.saved_Value.l + y.saved_Value.c});
    }
    if(y.t == DBL){
        push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = x.saved_Value.l + y.saved_Value.d});
    }
}


/**
 * Função somarDouble:
 * 
 * Função que avalia os casos onde o primeiro valor retirado, um dos membros da operação, é um double.
 * 
 * Faz push do resultado da operação somar para todos os tipos possiveis do outro membro.
 * 
 * É usada como função auxiliar da função "somar".
 */


void somarDouble(STACK *s,stack_Elem x,stack_Elem y){
    stack_Elem j;
    if(y.t == LNG){
        push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = x.saved_Value.d + y.saved_Value.l});
    }
    if(y.t == CHAR){
        push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = x.saved_Value.d + y.saved_Value.c});
    }
    if(y.t == DBL){
        push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = x.saved_Value.d + y.saved_Value.d});
    }
}


/**
 * Função somarChar:
 * 
 * Função que avalia os casos onde o primeiro valor retirado, um dos membros da operação, é um char.
 * 
 * Faz push do resultado da operação somar para todos os tipos possiveis do outro membro.
 * 
 * É usada como função auxiliar da função "somar".
 */


void somarChar(STACK *s,stack_Elem x,stack_Elem y){
    stack_Elem j;
    if(y.t == LNG){
        push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = x.saved_Value.c + y.saved_Value.l});
    }
    if(y.t == CHAR){
        push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = x.saved_Value.c + y.saved_Value.c});
    }
    if(y.t == DBL){
        push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = x.saved_Value.c + y.saved_Value.d});
    }
}


/**
 * Função somar:
 * 
 * Função que retira os dois elementos do topo da stack, soma-os e adiciona o resultado no topo da stack.
 * 
 * Utiliza as três funções auxiliares apresentadas anteriormente de forma a realizar a operação somar para todos os casos possíveis.
 * 
 * Exemplo: 12 7 + = 12 + 7 = 19.
 */


int somar(STACK *s,char *token){
    if(token[0] == '+'){
    stack_Elem x = pop(s);
    stack_Elem y = pop(s);
    if(x.t == STR || y.t == STR || y.t == ARRAY || x.t == ARRAY){
        concatenar(s,x,y);
        return 1;
    }
    if(x.t == LNG) somarLong(s,x,y);
    if(x.t == DBL) somarDouble(s,x,y);
    if(x.t == CHAR) somarChar(s,x,y);
    return 1;
    }
    return 0;                                 
}


/**
 * Função subtrairLong:
 * 
 * Função que avalia os casos onde o primeiro valor retirado, um dos membros da operação, é um long.
 * 
 * Faz push do resultado da operação subtrair para todos os tipos possiveis do outro membro.
 * 
 * É usada como função auxiliar da função "subtrair".
 */


void subtrairLong(STACK *s,stack_Elem x,stack_Elem y){
    stack_Elem j;
    if(y.t == LNG){
        push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l =  y.saved_Value.l - x.saved_Value.l});
    }
    if(y.t == CHAR){
        push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = y.saved_Value.c - x.saved_Value.l});
    }
    if(y.t == DBL){
        push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = y.saved_Value.d - x.saved_Value.l});
    }
}


/**
 * Função subtrairDouble:
 * 
 * Função que avalia os casos onde o primeiro valor retirado, um dos membros da operação, é um double.
 * 
 * Faz push do resultado da operação subtrair para todos os tipos possiveis do outro membro.
 * 
 * É usada como função auxiliar da função "subtrair".
 */


void subtrairDouble(STACK *s,stack_Elem x,stack_Elem y){
    stack_Elem j;
    if(y.t == LNG){
        push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = y.saved_Value.l - x.saved_Value.d});
    }
    if(y.t == CHAR){
        push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = y.saved_Value.c - x.saved_Value.d});
    }
    if(y.t == DBL){
        push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = y.saved_Value.d - x.saved_Value.d});
    }
}


/**
 * Função subtrairChar:
 * 
 * Função que avalia os casos onde o primeiro valor retirado, um dos membros da operação, é um char.
 * 
 * Faz push do resultado da operação subtrair para todos os tipos possiveis do outro membro.
 * 
 * É usada como função auxiliar da função "subtrair".
 */


void subtrairChar(STACK *s,stack_Elem x,stack_Elem y){
    stack_Elem j;
    if(y.t == LNG){
        push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = y.saved_Value.l - x.saved_Value.c});
    }
    if(y.t == CHAR){
        push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = y.saved_Value.c - x.saved_Value.c});
    }
    if(y.t == DBL){
        push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = y.saved_Value.d - x.saved_Value.c});
    }
}


/**
 * Função subtrair:
 * 
 * Função que retira os dois elementos do topo da stack, subtrai-os e adiciona o resultado no topo da stack.
 * 
 * Utiliza as três funções auxiliares apresentadas anteriormente de forma a realizar a operação subtrair para todos os casos possíveis.
 * 
 * Exemplo: 12 7 - = 12 - 7 = 5.
 */


int subtrair(STACK *s,char *token){
    if(token[0] == '-' && token[1] == '\0'){
    stack_Elem x = pop(s);
    stack_Elem y = pop(s);
    if(x.t == LNG) subtrairLong(s,x,y);
    if(x.t == DBL) subtrairDouble(s,x,y);
    if(x.t == CHAR) subtrairChar(s,x,y);
    return 1;
    }
    return 0;
}


/**
 * Função dividirLong:
 * 
 * Função que avalia os casos onde o primeiro valor retirado, um dos membros da operação, é um long.
 * 
 * Faz push do resultado da operação dividir para todos os tipos possiveis do outro membro.
 * 
 * É usada como função auxiliar da função "dividir".
 */


void dividirLong(STACK *s,stack_Elem x,stack_Elem y){
    stack_Elem j;
    if(y.t == LNG){
        push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = y.saved_Value.l / x.saved_Value.l});
    }
    if(y.t == CHAR){
        push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = y.saved_Value.c / x.saved_Value.l});
    }
    if(y.t == DBL){
        push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = y.saved_Value.d / x.saved_Value.l});
    }
}


/**
 * Função dividirDouble:
 * 
 * Função que avalia os casos onde o primeiro valor retirado, um dos membros da operação, é um double.
 * 
 * Faz push do resultado da operação dividir para todos os tipos possiveis do outro membro.
 * 
 * É usada como função auxiliar da função "dividir".
 */


void dividirDouble(STACK *s,stack_Elem x,stack_Elem y){
    stack_Elem j;
    if(y.t == LNG){
        push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = y.saved_Value.l / x.saved_Value.d});
    }
    if(y.t == CHAR){
        push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = y.saved_Value.c / x.saved_Value.d});
    }
    if(y.t == DBL){
        push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = y.saved_Value.d / x.saved_Value.d});
    }
}


/**
 * Função dividirChar:
 * 
 * Função que avalia os casos onde o primeiro valor retirado, um dos membros da operação, é um char.
 * 
 * Faz push do resultado da operação dividir para todos os tipos possiveis do outro membro.
 * 
 * É usada como função auxiliar da função "dividir".
 */


void dividirChar(STACK *s,stack_Elem x,stack_Elem y){
    stack_Elem j;
    if(y.t == LNG){
        push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = y.saved_Value.l / x.saved_Value.c});
    }
    if(y.t == CHAR){
        push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = y.saved_Value.c / x.saved_Value.c});
    }
    if(y.t == DBL){
        push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = y.saved_Value.d / x.saved_Value.c});
    }
}


/**
 * Função dividir:
 * 
 * Função que retira os dois elementos do topo da stack, dividi-os e adiciona o resultado no topo da stack.
 * 
 * Utiliza as três funções auxiliares apresentadas anteriormente de forma a realizar a operação dividir para todos os casos possíveis.
 * 
 * Exemplo: 20 2 / = 20 / 2 = 10.
 */


int dividir(STACK *s,char *token){
    if(token[0] == '/'){
    stack_Elem x = pop(s);
    stack_Elem y = pop(s);
    if(y.t == STR){
        separarString(s,x,y);
        return 1;
    }
    if(x.t == LNG) dividirLong(s,x,y);
    if(x.t == DBL) dividirDouble(s,x,y);
    if(x.t == CHAR) dividirChar(s,x,y);
    return 1;
    } 
    return 0;
}

/**
 * Função multiplicarLong:
 * 
 * Função que avalia os casos onde o primeiro valor retirado, um dos membros da operação, é um long.
 * 
 * Faz push do resultado da operação multiplicar para todos os tipos possiveis do outro membro.
 * 
 * É usada como função auxiliar da função "multiplicar".
 */


void multiplicarLong(STACK *s,stack_Elem x,stack_Elem y){
    stack_Elem j;
    if(y.t == LNG){
        push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = y.saved_Value.l * x.saved_Value.l});
    }
    if(y.t == CHAR){
        push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = y.saved_Value.c * x.saved_Value.l});
    }
    if(y.t == DBL){
        push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = y.saved_Value.d * x.saved_Value.l});
    }
}


/**
 * Função multiplicarDouble:
 * 
 * Função que avalia os casos onde o primeiro valor retirado, um dos membros da operação, é um double.
 * 
 * Faz push do resultado da operação multiplicar para todos os tipos possiveis do outro membro.
 * 
 * É usada como função auxiliar da função "multiplicar".
 */


void multiplicarDouble(STACK *s,stack_Elem x,stack_Elem y){
    stack_Elem j;
    if(y.t == LNG){
        push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = y.saved_Value.l * x.saved_Value.d});
    }
    if(y.t == CHAR){
        push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = y.saved_Value.c * x.saved_Value.d});
    }
    if(y.t == DBL){
        push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = y.saved_Value.d * x.saved_Value.d});
    }
}


/**
 * Função multiplicarChar:
 * 
 * Função que avalia os casos onde o primeiro valor retirado, um dos membros da operação, é um char.
 * 
 * Faz push do resultado da operação multiplicar para todos os tipos possiveis do outro membro.
 * 
 * É usada como função auxiliar da função "multiplicar".
 */


void multiplicarChar(STACK *s,stack_Elem x,stack_Elem y){
    stack_Elem j;
    if(y.t == LNG){
        push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = y.saved_Value.l * x.saved_Value.c});
    }
    if(y.t == CHAR){
        push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = y.saved_Value.c * x.saved_Value.c});
    }
    if(y.t == DBL){
        push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = y.saved_Value.d * x.saved_Value.c});
    }
}


/**
 * Função multiplicar:
 * 
 * Função que retira os dois elementos do topo da stack, multiplica-os e adiciona o resultado no topo da stack.
 * 
 * Utiliza as três funções auxiliares apresentadas anteriormente de forma a realizar a operação multiplicar para todos os casos possíveis.
 * 
 * Exemplo: 5 4 * = 5 * 4 = 20.
 */


int multiplicar(STACK *s,stack_Elem *l, char *token){
    if(token[0] == '*'){
    stack_Elem x = pop(s);
    stack_Elem y = pop(s);
    if(y.t == ARRAY && x.t == BLOCO){
        fold(s,l,x,y);
        return 1;
    }
    if(y.t == STR || y.t == ARRAY){
        concatenarNvezes(s,x,y);
        return 1;
    }
    if(x.t == LNG) multiplicarLong(s,x,y);
    if(x.t == DBL) multiplicarDouble(s,x,y);
    if(x.t == CHAR) multiplicarChar(s,x,y);
    return 1;
    } 
    return 0;
}


/**
 * Função decrementarAux:
 * 
 * Função que apresenta a operação a ser realizada consoante o tipo do valor a ser considerado.
 */


void decrementarAux(STACK *s,stack_Elem x){
    stack_Elem j;
    if(x.t == LNG) push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = x.saved_Value.l - 1});
    if(x.t == DBL) push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = x.saved_Value.d - 1});
    if(x.t == CHAR) push(s,j = (stack_Elem) {.t = CHAR,.saved_Value.c = x.saved_Value.c - 1});
}


/**
 * Função decrementar:
 * 
 * Função que retira o elemento do topo da stack e retira 1 ao seu valor e depois coloca o valor resultante no topo da stack.
 * 
 * Exemplo: 5 ( = 5 - 1 = 4.
 */


int decrementar(STACK *s,char *token){
    if(token[0] == '('){
    stack_Elem x = pop(s);
    if(x.t == STR || x.t == ARRAY){
        retiraPrimeiro(s,x);
        return 1;
    }
    decrementarAux(s,x);
    return 1;
    }
    return 0;
}


/**
 * Função incrementarAux:
 * 
 * Função que apresenta a operação a ser realizada consoante o tipo do valor a ser considerado.
 */


void incrementarAux(STACK *s,stack_Elem x){
    stack_Elem j;
    if(x.t == LNG) push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = x.saved_Value.l + 1});
    if(x.t == DBL) push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = x.saved_Value.d + 1});
    if(x.t == CHAR) push(s,j = (stack_Elem) {.t = CHAR,.saved_Value.c = x.saved_Value.c + 1});
}


/**
 * Função incrementar:
 * 
 * Função que retira o elemento do topo da stack e adiciona 1 ao seu valor e depois coloca o valor resultante no topo da stack.
 * 
 * Exemplo: 5 ) = 5 + 1 = 6.
 */


int incrementar(STACK *s,char *token){
    if(token[0] == ')'){
    stack_Elem x = pop(s);
    if(x.t == STR || x.t == ARRAY){
        retiraUltimo(s,x);
        return 1;
    }
    incrementarAux(s,x);
    return 1;
    }
    return 0;
}


/**
 * Função modulo:
 * 
 * Função que retira os dois elementos do topo da stack, dividi-os, e adiciona o resto da divisão no topo  da stack.
 * 
 * Exemplo: 12 5 % = 12 - (2*5) = 12 - 10 = 2.
 */


int modulo(STACK *s,stack_Elem *l,char *token){
    if(token[0] == '%'){
    stack_Elem x = pop(s);
    stack_Elem y = pop(s);
    stack_Elem j;
    if((y.t == STR || y.t == ARRAY) && x.t == BLOCO){
        aplicarBloco(s,l,x,y);
    }
    else{
    if(x.t == LNG && y.t == LNG) push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = y.saved_Value.l % x.saved_Value.l});
    }
    return 1;
    }
    return 0;
}


/**
 * Função exponenciacaoLong:
 * 
 * Função que avalia os casos onde o primeiro valor retirado, um dos membros da operação, é um long.
 * 
 * Faz push do resultado da operação exponenciação para todos os tipos possiveis do outro membro.
 * 
 * É usada como função auxiliar da função "exponenciacao".
 */


void exponenciacaoLong(STACK *s,stack_Elem x,stack_Elem y){
    stack_Elem j;
    if(y.t == LNG){
        push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = pow(y.saved_Value.l,x.saved_Value.l)});
    }
    if(y.t == CHAR){
        push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = pow(y.saved_Value.c,x.saved_Value.l)});
    }
    if(y.t == DBL){
        push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = pow(y.saved_Value.d,x.saved_Value.l)});
    }
}


/**
 * Função exponenciacaoDouble:
 * 
 * Função que avalia os casos onde o primeiro valor retirado, um dos membros da operação, é um double.
 * 
 * Faz push do resultado da operação exponenciação para todos os tipos possiveis do outro membro.
 * 
 * É usada como função auxiliar da função "exponenciacao".
 */


void exponenciacaoDouble(STACK *s,stack_Elem x,stack_Elem y){
    stack_Elem j;
    if(y.t == LNG){
        push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = pow(y.saved_Value.l,x.saved_Value.d)});
    }
    if(y.t == CHAR){
        push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = pow(y.saved_Value.c,x.saved_Value.d)});
    }
    if(y.t == DBL){
        push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = pow(y.saved_Value.d,x.saved_Value.d)});
    }
}


/**
 * Função exponenciacaoChar:
 * 
 * Função que avalia os casos onde o primeiro valor retirado, um dos membros da operação, é um char.
 * 
 * Faz push do resultado da operação exponenciação para todos os tipos possiveis do outro membro.
 * 
 * É usada como função auxiliar da função "exponenciacao".
 */


void exponenciacaoChar(STACK *s,stack_Elem x,stack_Elem y){
    stack_Elem j;
    if(y.t == LNG){
        push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = pow(y.saved_Value.l,x.saved_Value.c)});
    }
    if(y.t == CHAR){
        push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = pow(y.saved_Value.c,x.saved_Value.c)});
    }
    if(y.t == DBL){
        push(s,j = (stack_Elem) {.t = DBL,.saved_Value.d = pow(y.saved_Value.d,x.saved_Value.c)});
    }
}


/**
 * Função exponenciacao:
 * 
 * Função que retira os dois elementos do topo da stack, coloca o primeito valor retirado como expoente do segundo valor retirado e insere o resultado no topo
 * da stack.
 * 
 * Exemplo: 2 5 # = 2^5 = 2*2*2*2*2.
 */


int exponenciacao(STACK *s,char *token){
    if(token[0] == '#'){
    stack_Elem x = pop(s);
    stack_Elem y = pop(s);
    if(y.t == STR){
        searchSubstring(s,x,y);
        return 1;
    }
    if(x.t == LNG) exponenciacaoLong(s,x,y);
    if(x.t == DBL) exponenciacaoDouble(s,x,y);
    if(x.t == CHAR) exponenciacaoChar(s,x,y);
    return 1;
    }
    return 0;
}


/**
 * Função eBitwise:
 * 
 * Função que retira os dois elementos do topo da stack e, a partir dos mesmos na forma binária, caso ambos tenham o valor 1 na mesma posicao, o valor do binário
 * resultante na tal posição será 1, caso contrário o valor é 0.
 * 
 * Exemplo: 5 3 &        0101 --------> 5  
 *                     & 0011 --------> 3
 *                       0001 --------> Resultado = 1
 */

      
int eBitwise(STACK *s,char *token){
    if(token[0] == '&'){
    stack_Elem x = pop(s);
    stack_Elem y = pop(s);
    stack_Elem j;
    if(x.t == LNG && y.t == LNG) push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = y.saved_Value.l & x.saved_Value.l});
    return 1;
    }
    return 0;
}                    


/**
 * Função ouBitwise:
 * 
 * Função que retira os dois elementos do topo da stack e, a partir dos mesmos na forma binária, se pelo menos um deles tenha o valor 1 numa certa posição, o 
 * valor do binário resultante na tal posição será 1, caso contrário o valor é 0.
 * 
 * Exemplo: 5 3 |        0101 --------> 5  
 *                     | 0011 --------> 3
 *                       0111 --------> Resultado = 7                     
 */


int ouBitwise(STACK *s,char *token){
    if(token[0] == '|'){
    stack_Elem x = pop(s);
    stack_Elem y = pop(s);
    stack_Elem j;
    if(x.t == LNG && y.t == LNG) push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = y.saved_Value.l | x.saved_Value.l});
    return 1;
    }
    return 0;
}


/**
 * Função xorBitwise:
 * 
 * Função que retira os dois elementos do topo da stack e, a partir dos mesmos na forma binária, se o bit da mesma posição tiver um valor diferente, o valor do
 * binário resultante na tal posição será 1, caso contrário o valor é 0.
 * 
 * Exemplo: 5 3 ^        0101 --------> 5  
 *                     ^ 0011 --------> 3
 *                       0110 --------> Resultado = 6                    
 */


int xorBitwise(STACK *s,char *token){
    if(token[0] == '^'){
    stack_Elem x = pop(s);
    stack_Elem y = pop(s);
    stack_Elem j;
    if(x.t == LNG && y.t == LNG) push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = y.saved_Value.l ^ x.saved_Value.l});
    return 1;
    }
    return 0;
}


/**
 * Função notBitwise:
 * 
 * Função que retira o elemento do topo da stack e, a partir do mesmo na forma binária, inverte o valor do bit em todas as posições, ou seja, os 1s passam para
 * 0s e vice-versa.
 * 
 * Exemplo: 5 ~       ~ 00000101  
 *                      11111010 --------> Resultado = -6                
 */
    

int notBitwise(STACK *s,stack_Elem *l,char *token){
    if(token[0] == '~'){
    stack_Elem x = pop(s);
    stack_Elem j;
    if(x.t == BLOCO){
        executaBloco(s,l,x.saved_Value.bloco);
    }
    else{
    if(x.t == ARRAY){
        colocarArrayStack(s,x);
    }
    if(x.t == LNG) push(s,j = (stack_Elem) {.t = LNG,.saved_Value.l = ~x.saved_Value.l});
    }
    return 1;
    }
    return 0;
}


/**
 * Função rodar:
 * 
 * Função que roda os 3 últimos valores a serem inseridos na stack, independentemente do tipo dos mesmos.
 * 
 * Exemplo: 1 2 3 @ = 231.
 *                                    
 */


int rodar(STACK *s,char *token){
    if(token[0] == '@'){
    stack_Elem x = pop(s);
    stack_Elem y = pop(s);
    stack_Elem z = pop(s);
    push(s,y);
    push(s,x);
    push(s,z);
    return 1;
    }
    return 0;
}


/**
 * Função duplicar:
 * 
 * Função que duplica o último valor a ser inserido na stack, ou seja, realiza duas vezes push do valor.
 * 
 * Exemplo: 1 2 3 _ = 1233.
 *                                    
 */


int duplicar(STACK *s,char *token){
    if(token[0] == '_'){
    stack_Elem x = pop(s);
    stack_Elem y = x;
    push(s,x);
    push(s,y);
    return 1;
    }
    return 0;
}


/**
 * Função realizarPop:
 * 
 * Função que chama a função pop e acaba por ter a mesma funcionalidade que a mesma, sendo essa retirar o último elemento inserido na stack.
 * 
 * Exemplo: 1 2 3 ; = 12.
 *                                    
 */


int realizarPop(STACK *s,char *token){
    if(token[0] == ';'){
        pop(s);
        return 1;
    }
    return 0;
}


/**
 * Função trocar:
 * 
 * Função que troca a ordem dos últimos dois valores inseridos na stack.
 * 
 * Exemplo: 1 2 3 \ = 132.
 *                                    
 */


int trocar(STACK *s,char *token){
    if(token[0] == '\\'){
    stack_Elem x = pop(s);
    stack_Elem y = pop(s);
    push(s,x);
    push(s,y);
    return 1;
    }  
    return 0;
}


/**
 * Função copiaNesimo:
 * 
 * Função que retira o último elemento inserido na stack e realiza push do valor que se encontra na posição do que foi retirado(a contagem começa no zero).
 * 
 * Exemplo: 1 2 3 2 $ = 1231.
 *                                    
 */


int copiaNesimo(STACK *s,stack_Elem *l,char *token){
    if(token[0] == '$'){
    stack_Elem x = pop(s);
    if(x.t == BLOCO){
        stack_Elem z = pop(s);
        ordenaViaBloco(s,l,x,z);
    }
    else{
        stack_Elem y = s -> stack[s->sp-x.saved_Value.l-1];
        push(s,y);
    }
    return 1;
    }
    return 0;
}


/**
 * Função converteChar:
 * 
 * Função que converte qualquer valor de qualquer tipo para um char.
 * 
 * Exemplo: 98 c = b.
 *                                    
 */


int converteChar(STACK *s,char *token){
    if(token[0] == 'c'){
    stack_Elem x = pop(s);
    stack_Elem j;
    if(x.t == CHAR)
        push(s,x);
    if(x.t == LNG)
        push(s,j = (stack_Elem) {.t = CHAR,.saved_Value.c = x.saved_Value.l});
    if(x.t == DBL)
        push(s,j = (stack_Elem) {.t = CHAR,.saved_Value.c = x.saved_Value.d});
    return 1;
    }
    return 0;
}


/**
 * Função converteInt:
 * 
 * Função que converte qualquer valor de qualquer tipo para um int.
 * 
 * Exemplo: 2.2 i = 2.
 *                                    
 */


int converteInt(STACK *s,char *token){
    if(token[0] == 'i')
    {
        stack_Elem x = pop(s);
        stack_Elem j;
        if(x.t == LNG)
            j.saved_Value.l = (long)x.saved_Value.l;  
        if(x.t == CHAR) 
            j.saved_Value.l = (long)x.saved_Value.c;
        if(x.t == DBL) 
            j.saved_Value.l = (long)x.saved_Value.d;
        if(x.t == STR)
        {
            j.saved_Value.l = atoi(x.saved_Value.str);
        }
        j.t = LNG;
        push(s,j);
        return 1;
    }
    return 0;
}


/**
 * Função converteDouble:
 * 
 * Função que converte qualquer valor de qualquer tipo para um double.
 * 
 * Exemplo: 2 f = 2.0.
 *                                    
 */



int converteDouble(STACK *s,char *token){
    if(token[0] == 'f')
    {
        stack_Elem x = pop(s);
        stack_Elem j;
        if(x.t == DBL) 
            j.saved_Value.d = x.saved_Value.d;
        if(x.t == CHAR)
            j.saved_Value.d = x.saved_Value.c;
        if(x.t == LNG)
            j.saved_Value.d = x.saved_Value.l;
        if(x.t == STR)
            j.saved_Value.d = atof(x.saved_Value.str);
        j.t = DBL;
        push(s,j);
        return 1;
    }
    return 0;
}


/**
 * Função converteString:
 * 
 * Função que converte qualquer valor de qualquer tipo para uma string.
 * 
 * Exemplo: 2 s = "2"
 *                                    
 */


int converteString(STACK *s,char *token){
    if(token[0] == 's')
    {
        stack_Elem x = pop(s);
        stack_Elem j;
        j.saved_Value.str = malloc(sizeof(char) * 22);
        if(x.t == STR)
            j.saved_Value.str = x.saved_Value.str;
        if(x.t == CHAR){
            sprintf(j.saved_Value.str,"%c",x.saved_Value.c);
        }
        if(x.t == LNG){
            sprintf(j.saved_Value.str,"%ld",x.saved_Value.l);
        }
        if(x.t == DBL){
            sprintf(j.saved_Value.str,"%g",x.saved_Value.d);
        }
        j.t = STR;
        push(s,j);
        return 1;
    }
    return 0;
}


/**
 * Função lerLinha:
 * 
 * Função que lê uma linha e dá push da mesma na forma de uma string.
 * 
 * Permite a criação de várias linhas com operações, que podem ser todas realizadas apesar dos valores estarem inseridos em linhas diferentes.
 * 
 * Exemplo: l i :A l i :B > A B ?
 *          7                      ----------> Resultado: 7
 *          4      
 *                     
 */


int lerLinha(STACK *s,char *token){
    if(token[0] == 'l'){
    char linha [10001];
    stack_Elem j;
    if (fgets(linha,10001,stdin)!= NULL)
    {
        int tamanho = strlen(linha);
        if(linha[tamanho-1] == '\n') linha[tamanho-1] = '\0';
        j.t = STR;
        j.saved_Value.str = strdup(linha);
        push(s,j);
    }
    return 1;
    }
    return 0;
}


/**
 * Função criarVariaveis:
 * 
 * Função que atribui os valores desejados a certas "letras" (posicao na lista que corresponde à posição das letras no alfabeto).
 * 
 * Os valores atribuidos são os que estão identificados na página do enunciado referente às variáveis.     
 *              
 * Exemplo: A = 10, B = 11, N = '\n', etc...
 *            
 */


void criarVariaveis(stack_Elem *l){
    for(int i = 0;i < 26;i++){
        if(i < 6){
            l[i] = (stack_Elem) {.t = LNG,.saved_Value.l = 10 + i};
        }
        if(i == 13) l[i] = (stack_Elem) {.t = CHAR,.saved_Value.c = '\n'};
        if(i == 18) l[i] = (stack_Elem) {.t = CHAR,.saved_Value.c = ' '};
        if(i > 22 && i < 26){
            l[i] = (stack_Elem) {.t = LNG,.saved_Value.l = 0 + (i - 23)};
        }
    }
}


/**
 * Função colocarVariavel:
 * 
 * Função que permite dar push do valor que foi dado às variáveis na função "criarVariaveis" em vez das próprias letras, ou seja, quando se insere a letra 'A'
 * no terminal e faz-se enter, o valor devolvido é o que está associado à letra em vez da letra em si, neste caso o terminal devolveria 10.
 *            
 */


int colocarVariavel(STACK *s,stack_Elem *l,char *token){
    if(token[0] >= 65 && token[0] <= 91){
        int posicao = token[0] - 65;
        stack_Elem j = l[posicao];
        push(s,j);
        return 1;
    }
    return 0;
}


/**
 * Função copiaParaVariavel:
 * 
 * Função que copia o valor que se encontra antes do simbolo ":" para a variável que se encontra após o mesmo.
 * 
 * O valor desejado é inserido na lista, na posição em que a letra se encontra no alfabeto.
 * 
 * Exemplo: A B * :T T = 110110.          
 */


int copiaParaVariavel(STACK *s,stack_Elem *l,char *token){
    if(token[0] == ':' && token[1] >= 65 && token[1] <= 91){
        int posicao = token[1] - 65;
        stack_Elem x = s->stack[s->sp-1];
        if(x.t == BLOCO){
            stack_Elem j;
            j.t = BLOCO;
            char *aux = strdup(x.saved_Value.bloco);
            j.saved_Value.str = aux;
            l[posicao] = j;
        }
        if(x.t == ARRAY){
            stack_Elem j;
            j.t = ARRAY;
            j.saved_Value.array = new_stack();
            for(int i = 0; i < x.saved_Value.array->sp;i++){
                push(j.saved_Value.array,x.saved_Value.array->stack[i]);
            }
            l[posicao] = j;
        }
        else l[posicao] = x;
        return 1;
    }
    return 0;
}


/**
 * Função printStackElem:
 * 
 * Função auxiliar de "imprimeTopo".
 * 
 * Função responsável por imprimir o valor presente no stack_Elem.        
 */


void printStackElem(stack_Elem x){
    if(x.t == CHAR) printf("%c",x.saved_Value.c);
    if(x.t == STR) printf("%s",x.saved_Value.str);
    if(x.t == BLOCO) printf("%s",x.saved_Value.bloco);
    if(x.t == DBL) printf("%g",x.saved_Value.d);
    if(x.t == LNG) printf("%ld",x.saved_Value.l);
    if(x.t == ARRAY) printArray(x.saved_Value.array);
}


/**
 * Função imprimeTopo:
 * 
 * Função responsável por imprimir o stack_Elem que se encontra no topo da stack.        
 */


int imprimeTopo(STACK *s,char *token){
    if(token[0] == 'p'){
        stack_Elem x = s->stack[s->sp-1];
        printStackElem(x);
        putchar('\n');
        return 1;
    }
    return 0;
}



/**
 * Função operacaoAritmetica:
 * 
 * Função que vê se algum dos tokens corresponde a um dos simbolos utilizados para identificar uma das operações. 
 * 
 * Os tokens verificados nesta função são os que correpondem às seguintes funções: somar,subtrair,multiplicar,dividir,decrementar,incrementar,modulo e exponenciacao.
 *            
 */


int operacaoAritmetica(char *token){
    char lista[] = "+-*/()%#";
    for(int i = 0; i != '\0';i++){
        if(token[0] == lista[i]) return 1;
    }
    return 0;
}


/**
 * Função operacaoBitwise:
 * 
 * Função que vê se algum dos tokens corresponde a um dos simbolos utilizados para identificar uma das operações. 
 * 
 * Os tokens verificados nesta função são os que correpondem às seguintes funções: eBitwise,ouBitwise,xorBitwise e notBitwise.
 *          
 */


int operacaoBitwise(char *token){
    char lista[] = "&|^~";
    for(int i = 0; i != '\0';i++){
        if(token[0] == lista[i]) return 1;
    }
    return 0;
}


/**
 * Função operacaoAlteraStack:
 * 
 * Função que vê se algum dos tokens corresponde a um dos simbolos utilizados para identificar uma das operações. 
 * 
 * Os tokens verificados nesta função são os que correpondem às seguintes funções: rodar,duplicar,realizarPop,trocar,copiaNesimo,converteChar,converteInt,
 * converteDouble, lerLinha e converteString. 
 *           
 */


int operacaoAlteraStack(char *token){
    char lista[] = "@_;\\$cifls";
    for(int i = 0; i != '\0';i++){
        if(token[0] == lista[i]) return 1;
    }
    return 0;
}


/**
 * Função operacaoLogica:
 * 
 * Função que vê se algum dos tokens corresponde a um dos simbolos utilizados para identificar uma das operações. 
 * 
 * Os tokens verificados nesta função são os que correpondem às seguintes funções: igual,menor,maior,negacao,ifThenElse. 
 *           
 */


int operacaoLogica(char *token){
    char lista[] = "=<>!?";
    for(int i = 0; i != '\0';i++){
        if(token[0] == lista[i]) return 1;
    }
    return 0;
}


/**
 * Função operacaoDif:
 * 
 * Função que vê se algum dos tokens corresponde a um dos simbolos utilizados para identificar uma das operações. 
 * 
 * Os tokens verificados nesta função são os que correpondem às seguintes funções: eShortcut,ouShortcut,menorDoTopo e maiorDoTopo.
 *           
 */


int operacaoDif(char *token){
    int resultado = 0;
    if(token[0] == 'e' && token[1] == '&') resultado = 1;
    if(token[0] == 'e' && token[1] =='|') resultado = 1;
    if(token[0] == 'e' && token[1] == '<') resultado = 1;
    if(token[0] == 'e' && token[1] == '>') resultado = 1;
    if(token[0] == 'S' && token[1] == '/') resultado = 1;
    if(token[0] == 'N' && token[1] == '/') resultado = 1;
    return resultado;
}


/**
 * Função operacaoArrays:
 * 
 * Função que vê se algum dos tokens corresponde a um dos simbolos utilizados para identificar uma das operações. 
 * 
 * Os tokens verificados nesta função são os que correpondem às seguintes funções: rangeTamanho, lerInput, whileTruthy e imprimeTopo.
 *           
 */


int operacaoArrays(char *token){
    char lista[] = ",twp";
    for(int i = 0; lista[i] != '\0';i++){
        if(token[0] == lista[i]) return 1;
    }
    return 0;
}



/**
 * Função handleAritmetica:     
 * 
 * Verifica se alguma das funções representadas pelos simbolos da função "operacaoAritmetica" dão valor 1, ou seja, a operação foi realizada.
 *    
 */


int handleAritmetica(STACK *s,stack_Elem *l,char *token){
    if(somar(s,token) || subtrair(s,token) || dividir(s,token) || multiplicar(s,l,token) || decrementar(s,token) || incrementar(s,token) || modulo(s,l,token)
    || exponenciacao(s,token)) return 1;
    return 0;
}


/**
 * Função handleBitwise:     
 * 
 * Verifica se alguma das funções representadas pelos simbolos da função "operacaoBitwise" dão valor 1, ou seja, a operação foi realizada.
 *    
 */


int handleBitwise(STACK *s,stack_Elem *l,char *token){
    if(eBitwise(s,token) || ouBitwise(s,token) || xorBitwise(s,token) || notBitwise(s,l,token)) return 1;
    return 0;
}


/**
 * Função handleAlteraStack:     
 * 
 * Verifica se alguma das funções representadas pelos simbolos da função "operacaoAlteraStack" dão valor 1, ou seja, a operação foi realizada.
 *    
 */


int handleAlteraStack(STACK *s,stack_Elem *l,char *token){
    if(rodar(s,token) || duplicar(s,token) || realizarPop(s,token) || trocar(s,token) || copiaNesimo(s,l,token) || converteChar(s,token) || converteInt(s,token) 
    || converteDouble(s,token) || converteString(s,token) || lerLinha(s,token)) return 1;
    return 0;
}


/**
 * Função handleLogica:     
 * 
 * Verifica se alguma das funções representadas pelos simbolos da função "operacaoLogica" dão valor 1, ou seja, a operação foi realizada.
 *    
 */


int handleLogica(STACK *s,char *token){
    if(igual(s,token) || menor(s,token) || maior(s,token) || negacao(s,token) || ifThenElse(s,token)) return 1;
    return 0;
}


/**
 * Função handleDif:     
 * 
 * Verifica se alguma das funções representadas pelos simbolos da função "operacaoDif" dão valor 1, ou seja, a operação foi realizada.
 *    
 */


int handleDif(STACK *s,char *token){
    if(eShortcut(s,token) || ouShortcut(s,token) || maiorDoTopo(s,token) || menorDoTopo(s,token) || separarWhiteSpace(s,token) || separarEnter(s,token)) return 1;
    return 0;
}


/**
 * Função handleArray:     
 * 
 * Verifica se alguma das funções representadas pelos simbolos da função "operacaoArrays" dão valor 1, ou seja, a operação foi realizada.
 *    
 */

int handleArray(STACK *s,stack_Elem *l,char *token){
    if(rangeTamanho(s,l,token) || lerInput(s,token) || whileTruthy(s,l,token) || imprimeTopo(s,token)) return 1;
    return 0;
}


/**
 * Função operacaoHandle:     
 * 
 * Verifica se algum dos handles referidos anteriormente retorna valor 1. Se tal acontecer é porque uma das operações foi realizada, caso contrário podemos
 * concluir que nenhuma das operações incluidas nos handles anteriores foi verificada.
 *    
 */


int operacaoHandle(STACK *s,stack_Elem *l,char *token){
    if(handleBitwise(s,l,token) || handleAritmetica(s,l,token) || handleAlteraStack(s,l,token) || handleLogica(s,token)
    || handleDif(s,token) || handleArray(s,l,token)) return 1;
    return 0;
}


/**
 * Função handleTheRest:     
 * 
 * Verifica as funções que sobram depois de verificar todas as outras operações.
 *    
 */


int handleTheRest(STACK *s,stack_Elem *l,char *token){
    if(colocarVariavel(s,l,token) || copiaParaVariavel(s,l,token) || pushToken(s,token)) return 1;
    return 0;
}


/**
 * Função handle:
 * 
 * Verifica se alguma das operações devolve valor 1, se tal acontecer então foi encontrado um token que coincide com o simbolo de uma das operações e a função
 * vai chamar o handle ("operacaoHandle") responsável por verificar quase todas as funções existentes, com exceção de 4 (que se encontram no "handleTheRest").
 * 
 * Caso o handle chamado retorne valor 0 então podemos concluir que a operação por realizar é uma das 4 presentes no "handleTheRest" e então essa mesma função
 * é chamada.         
 */


void handle(STACK *s,stack_Elem *l,char *token) 
{   
    if(operacaoAritmetica(token) || operacaoAlteraStack(token) || operacaoBitwise(token) || operacaoLogica(token) || operacaoDif(token)) operacaoHandle(s,l,token);
    else if(operacaoHandle(s,l,token) == 0) handleTheRest(s,l,token);           
}