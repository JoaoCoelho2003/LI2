/**
 * Ficheiro logica.c:
 * 
 * Ficheiro onde se encontram definidas as funções responsáveis pelo guião 3 do projeto.
 */


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"


/**
 * Função typeCheck:
 * 
 * Função que, consoante o tipo recebido, retorna o valor do union desejado.
 * 
 * Retorna sempre double porque na transição de qualquer outra variável para double não há qualquer perda de conteúdo.
 * 
 * O mesmo não se verificaria caso o tipo retornado fosse outro dos disponíveis.  
 */


double typeCheck(stack_Elem x,type l){
    if(l == LNG) return x.saved_Value.l;
    if(l == DBL) return x.saved_Value.d;
    if(l == CHAR) return x.saved_Value.c;
    return 1.0;
}


/**
 * Função igualAux:
 * 
 * Verifica se dois valores são iguais.
 * 
 * Esta igualdade é verificada para todos os casos possiveis (para todos os tipos).
 * 
 * Função auxiliar de "igual".
 */


int igualAux(type l,stack_Elem x, stack_Elem y){
    if(x.t == l && y.t == LNG){
        if(y.saved_Value.l == typeCheck(x,l)) return 1;
    }
    else if(x.t == l && y.t == CHAR){
        if(y.saved_Value.c == typeCheck(x,l)) return 1;
    }
    else if(x.t == l && y.t == DBL){
        if(y.saved_Value.d == typeCheck(x,l)) return 1;
    }
    return 0;
}


/**
 * Função igualStrings:
 * 
 * Função auxiliar da função "igual" quando ambos os 2 elementos do topo da stack sejam strings. 
 * 
 * Caso as duas strings sejam iguais é feito push de 1. Caso contrário faz push de 0.
 */


int igualStrings(stack_Elem x,stack_Elem y){
    if(strlen(x.saved_Value.str) != strlen(y.saved_Value.str)) return 0;
    for(size_t i = 0; i < strlen(x.saved_Value.str);i++){
        if(x.saved_Value.str[i] != y.saved_Value.str[i]) return 0;
    }
    return 1;
}


/**
 * Função igual:
 * 
 * Função que faz push de 1 caso os dois últimos valores a serem inseridos na stack serem iguais. Caso contrário faz push de 0.
 */


int igual(STACK *s,char *token){
    if(token[0] == '='){
    stack_Elem x = pop(s);
    stack_Elem y = pop(s);
    stack_Elem j;
    if(x.t == STR && y.t == STR){
        j.t = LNG;
        j.saved_Value.l = igualStrings(x,y);
        push(s,j);
        return 1;
    }
    if(y.t == STR || y.t == ARRAY){
        procuraIndice(s,x,y);
        return 1;
    }
    j.t = LNG;
    j.saved_Value.l = igualAux(x.t,x,y);
    push(s,j);
    return 1;
    }
    return 0;
}


/**
 * Função menorAux:
 * 
 * Verifica se o último valor a ser inserido na stack é maior que o que veio antes dele.
 * 
 * Verifica esta comparação para todos os casos possiveis (para todos os tipos).
 * 
 * Função auxiliar de "menor".
 */


int menorAux(type l,stack_Elem x, stack_Elem y){
    if(x.t == l && y.t == LNG){
        if(y.saved_Value.l < typeCheck(x,l)) return 1;
    }
    if(x.t == l && y.t == CHAR){
        if(y.saved_Value.c < typeCheck(x,l)) return 1;
    }
    if(x.t == l && y.t == DBL){
        if(y.saved_Value.d < typeCheck(x,l)) return 1;
    }
    return 0;
}


/**
 * Função menorStrings:
 * 
 * Função responsável pela execução da função "menor" para caso ambos os 2 elementos do topo da stack sejam strings.
 *   
 * Esta faz push de 1 caso o valor da última string a ser inserida na stack seja maior que o valor da string anterior. Caso contrário, isto é se for menor,
 * faz push de 0.
 */


int menorStrings(stack_Elem x, stack_Elem y){
    int tamanho;
    int sumx = 0,sumy = 0;
    if(strlen(x.saved_Value.str) > strlen(y.saved_Value.str)) tamanho = strlen(x.saved_Value.str);
    else tamanho = strlen(y.saved_Value.str);
    for(int i = 0; i < tamanho;i++){
        sumx += x.saved_Value.str[i];
        sumy += y.saved_Value.str[i];
    }
    if(sumy < sumx) return 1;
    else return 0;
}


/**
 * Função menor:
 * 
 * Função que faz push de 1 caso o último valor a ser inserido na stack fôr maior que o que veio antes dele. Caso contrário faz push de 0.
 */


int menor(STACK *s,char *token){
    if(token[0] == '<'){
    stack_Elem x = pop(s);
    stack_Elem y = pop(s);
    stack_Elem j;
    if(x.t == STR && y.t == STR){
        j.t = LNG;
        j.saved_Value.l = menorStrings(x,y);
        push(s,j);
        return 1;
    }
    else if(y.t == STR || y.t == ARRAY){
        buscarInicio(s,x,y);
        return 1;
    }
    else{
        j.t = LNG;
        j.saved_Value.l = menorAux(x.t,x,y);
        push(s,j);
        return 1;
        }
    }
    return 0;
}


/**
 * Função maiorAux:
 * 
 * Verifica se o último valor a ser inserido na stack é menor que o que veio antes dele.
 * 
 * Verifica esta comparação para todos os casos possiveis (para todos os tipos).
 * 
 * Função auxiliar de "maior".
 */


int maiorAux(type l,stack_Elem x, stack_Elem y){
    if(x.t == l && y.t == LNG){
        if(y.saved_Value.l > typeCheck(x,l)) return 1;
    }
    if(x.t == l && y.t == CHAR){
        if(y.saved_Value.c > typeCheck(x,l)) return 1;
    }
    if(x.t == l && y.t == DBL){
        if(y.saved_Value.d > typeCheck(x,l)) return 1;
    }
    return 0;
}


/**
 * Função maiorStrings:
 * 
 * Função auxiliar da função "maior" para caso ambos os 2 elementos do topo da stack sejam strings.
 * 
 * Esta faz push de 1 caso a última string tenha um valor menor que a string anterior. Caso contrário, isto é se for maior, faz push de 0.
 */


int maiorStrings(stack_Elem x, stack_Elem y){
    int tamanho;
    int sumx = 0,sumy = 0;
    if(strlen(x.saved_Value.str) > 
    strlen(y.saved_Value.str)) tamanho = 
    strlen(x.saved_Value.str);
    else tamanho = strlen(y.saved_Value.str);
    for(int i = 0; i < tamanho;i++){
        sumx += x.saved_Value.str[i];
        sumy += y.saved_Value.str[i];
    }
    if(sumy > sumx) return 1;
    else return 0;
}



/**
 * Função maior:
 * 
 * Função que faz push de 1 caso o último valor a ser inserido na stack fôr menor que o que veio antes dele. Caso contrário faz push de 0.
 */


int maior(STACK *s,char *token){
    if(token[0] == '>'){
    stack_Elem x = pop(s);
    stack_Elem y = pop(s);
    stack_Elem j;
    if(x.t == STR && y.t == STR){
        j.t = LNG;
        j.saved_Value.l = maiorStrings(x,y);
        push(s,j);
        return 1;
    }
    else if(y.t == STR || y.t == ARRAY){
        buscarFim(s,x,y);
        return 1;
    }
    else{
        j.t = LNG;
        j.saved_Value.l = maiorAux(x.t,x,y);
        push(s,j);
        return 1;
        }
    }
    return 0;
}


/**
 * Função negacaoAux:
 * 
 * Verifica se o valor avaliado é igual a zero ou não.
 * 
 * Função auxiliar de "negacao".
 */


int negacaoAux(stack_Elem x){
    if(x.t == LNG){
        if(x.saved_Value.l == 0) return 1;
    }
    if(x.t == CHAR){
        if(x.saved_Value.c == 0) return 1;
    }
    if(x.t == DBL){
        if(x.saved_Value.d == 0) return 1;
    }
    return 0;
}


/**
 * Função negacao:
 * 
 * Faz push do valor obtido na função "negacaoAux".
 * 
 * O valor retornado é sempre 0 ou 1.
 */


int negacao(STACK *s,char *token){
    if(token[0] == '!'){
    stack_Elem x = pop(s);
    stack_Elem j;
    j.t = LNG;
    j.saved_Value.l = negacaoAux(x);
    push(s,j);
    return 1;
    }
    return 0;
}


/**
 * Função equalZero:
 * 
 * Retorna sempre o stack_Elem que tem valor igual a 0.
 * 
 * Função auxiliar de "eShortcut".
 */


stack_Elem equalZero(stack_Elem x, stack_Elem y){
    if(y.t == LNG){
        if(x.saved_Value.l == 0 && y.saved_Value.l != 0) return x;
    }
    if(y.t == CHAR){
        if(x.saved_Value.l == 0 && y.saved_Value.c != 0) return x;
    }
    if(y.t == DBL){
        if(x.saved_Value.l == 0 && y.saved_Value.d != 0) return x;
    }
    return y;
}


/**
 * Função ambosDifZero:
 * 
 * Verifica se ambos os valores são diferentes de 0 ou não.
 * 
 * Função auxiliar de "eShortcut".
 */


int ambosDifZero(stack_Elem x, stack_Elem y){
    if(y.t == LNG){
        if(x.saved_Value.l != 0 && y.saved_Value.l != 0) return 1;
    }
    if(y.t == CHAR){
        if(x.saved_Value.l != 0 && y.saved_Value.c != 0) return 1;
    }
    if(y.t == DBL){
        if(x.saved_Value.l != 0 && y.saved_Value.d != 0) return 1;
    }
    return 0;
}



/**
 * Função eShortcut:
 * 
 * Utiliza as duas funções apresentadas anteriormente como funções auxiliares.
 * 
 * Caso ambos os valores sejam diferentes de 0 retorna o stack_Elem que representa o último valor a ser inserido na stack( e o primeiro que foi retirado da mesma
 * através do pop).
 * 
 * Se um dos valores avaliados fôr igual a zero esse é o valor que será sempre alvo do push.
 */



int eShortcut(STACK *s,char *token){
    if(token[0] == 'e' && token[1] == '&'){
    stack_Elem x = pop(s);
    stack_Elem y = pop(s);
    stack_Elem j = equalZero(x,y);
    if(ambosDifZero(x,y) == 1) j = x;
        push(s,j);
        return 1;
    }
    return 0;
}


/**
 * Função valorDifZero:
 * 
 * Verifica se o valor é diferente de zero ou não.
 * 
 * Retorna sempre um stack_Elem.
 * 
 * Função auxiliar de "eShortcut".
 */


stack_Elem valorDifZero(stack_Elem x,stack_Elem y){
    if(x.t == LNG){
        if(y.saved_Value.l != 0) return y;
    }
    if(x.t == CHAR){
        if(y.saved_Value.c != 0) return y;
    }
    if(x.t == DBL){
        if(y.saved_Value.d != 0) return y;
    }
    return x;
}


/**
 * Função ouShortcut:
 * 
 * Utiliza as duas funções apresentadas anteriormente como funções auxiliares.
 * 
 * Caso ambos os valores sejam diferentes de 0 retorna o stack_Elem que representa o segundo valor a ser retirado da stack, ou seja, o stack_Elem y.
 * 
 * Se um dos valores avaliados fôr igual a zero, então o membro que será alvo do push é o outro valor da operação.
 */


int ouShortcut(STACK *s,char *token){
    if(token[0] == 'e' && token[1] == '|'){
        stack_Elem x = pop(s);
        stack_Elem y = pop(s);
        stack_Elem j = valorDifZero(x,y);
        push(s,j);
        return 1;
    }
    return 0;
}


/**
 * Função maiorDoTopo:
 * 
 * Função que retorna o maior elemento dos dois valores que se encontram antes do simbolo da operação.
 * 
 * Utiliza a função "maiorAux" para verificar qual é o maior valor.
 * 
 * Caso a função auxiliar retorne o valor 1 então sabemos que o maior valor dos dois é o segundo valor retirado(stack_Elem y),caso contrário podemos concluir que 
 * o maior valor é o stack_Elem x.
 * 
 */



int maiorDoTopo(STACK *s,char *token){
    if(token[0] == 'e' && token[1] == '>'){
        stack_Elem x = pop(s);
        stack_Elem y = pop(s);
        stack_Elem j = x;
        if(igualAux(x.t,x,y)) j = y;
        else if(maiorAux(x.t,x,y)) j = y;
        else if(menorAux(x.t,x,y)) j = x;
        else if (maiorStrings(x,y) || igualStrings(x,y)) j = y;
        push(s,j);
        return 1;
    }
    return 0;
}


/**
 * Função menorDoTopo:
 * 
 * Função que retorna o menor elemento dos dois valores que se encontram antes do simbolo da operação.
 * 
 * Utiliza a função "menorAux" para verificar qual é o menor valor.
 * 
 * Caso a função auxiliar retorne o valor 1 então sabemos que o menor valor dos dois é o segundo valor retirado(stack_Elem y),caso contrário podemos concluir que 
 * o menor valor é o stack_Elem x.
 * 
 */


int menorDoTopo(STACK *s,char *token){
    if(token[0] == 'e' && token[1] == '<'){
        stack_Elem x = pop(s);
        stack_Elem y = pop(s);
        stack_Elem j = x;
        if(igualAux(x.t,x,y)) j = y;
        else if(maiorAux(x.t,x,y)) j = x;
        else if(menorAux(x.t,x,y)) j = y;
        else if (menorStrings(x,y) || igualStrings(x,y)) j = y;
        push(s,j);
        return 1;
    }
    return 0;
}


/**
 * Função condicaoDoIf:
 * 
 * Verifica se o valor do z é igual a 0 ou não.
 * 
 * Função auxiliar de "ifThenElse".
 */


int condicaoDoIf(stack_Elem z){
    if(z.t == LNG){
        if(z.saved_Value.l == 0) return 1;
    }
    if(z.t == CHAR){
        if(z.saved_Value.c == 0) return 1;
    }
    if(z.t == DBL){
        if(z.saved_Value.d == 0) return 1;
    }
    if(z.t == STR){
        if(z.saved_Value.str[0] == '\0') return 1;
    }
    if(z.t == ARRAY){
        if(z.saved_Value.array->sp == 0) return 1;
    }
    return 0;
}


/**
 * Função ifThenElse:
 * 
 * Se o valor de z fôr igual a 0 então retorna o stack_Elem x.
 * 
 * Caso contrário retorna o stack_Elem y.
 * 
 * Exemplo1: 1 2 3 ? ---> 1 é diferente de 0 logo retorna o stack_Elem y (2).
 * Exemplo2: 0 5 6 ? ---> z é igual a 0 logo retorna stack_Elem x (6).
 */


int ifThenElse(STACK *s,char *token){
    if(token[0] == '?'){
    stack_Elem x = pop(s);
    stack_Elem y = pop(s);
    stack_Elem z = pop(s);
    stack_Elem j = y;
    if(condicaoDoIf(z)) j = x;
        push(s,j);
        return 1;
    }
    return 0;
}