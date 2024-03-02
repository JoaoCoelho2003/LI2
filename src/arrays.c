/**
 * Ficheiro arrays.c:
 * 
 * Ficheiro onde se encontram definidas as funções responsáveis pelo guião 4 do projeto.
 */


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"


/**
 * Função concatenarArray:
 * 
 * Função auxiliar da função "concatenar".
 * 
 * Responsável pelos casos em que se quer concatenar algum tipo a um array.
 * 
 * Utiliza-se a função push para mandar os valores para a array.
 * 
 * Exemplo: [ 1 2 3 ] [ 4 5 ] + -> 12345
 *          [ 3 4 7 ] 2 +       -> 3472
 *          2 [ 3 1 ] +         -> 231
 */


void concatenarArray(STACK *s,stack_Elem x, stack_Elem y){
    if(y.t == ARRAY && x.t != ARRAY){
        push(y.saved_Value.array,x);
        push(s,y);
    }
    else if(y.t != ARRAY && x.t == ARRAY){
        push(x.saved_Value.array,x.saved_Value.array->stack[x.saved_Value.array->sp - 1]);
        for(int i = x.saved_Value.array->sp - 2; i >= 0;i--){
            x.saved_Value.array->stack[i + 1] = x.saved_Value.array->stack[i];
        }
        x.saved_Value.array->stack[0] = y;
        push(s,x);
        }
    else{
        for(int i = 0; i < x.saved_Value.array->sp;i++){
            push(y.saved_Value.array,x.saved_Value.array->stack[i]);
        }
        push(s,y);
    }
}


/**
 * Função concatenar: 
 * 
 * Função é aplicada quando receber '+' e caso um dos elementos seja array ou string. 
 * 
 * Se um dos elementos no topo da stack for array é chamada a função "concatenarArray".
 * 
 * A função devolve os dois elementos concatenados.
 * 
 * Exemplo: "ola" 99 c + = "olac"
 *          "ola" "adeus" + = "olaadeus"
 *          3 "21" + = "321"
 * 
 */


void concatenar(STACK *s,stack_Elem x, stack_Elem y){
    if(x.t == ARRAY || y.t == ARRAY){
        concatenarArray(s,x,y);
    }
    else{
    if(y.t == STR){
        long tamanho = strlen(y.saved_Value.str);
        char guardado[tamanho];
        if(x.t == STR){
            strcat(y.saved_Value.str,x.saved_Value.str);
        }
        else if(x.t == LNG){
            sprintf(guardado,"%ld",x.saved_Value.l);
            strcat(y.saved_Value.str,guardado);
        }
        else if(x.t == DBL){
            sprintf(guardado,"%g",x.saved_Value.d);
            strcat(y.saved_Value.str,guardado);
        }
        else if(x.t == CHAR){
            strcat(y.saved_Value.str,&x.saved_Value.c);
        }
        push(s,y);
        }
    else if(x.t == STR){
        char *guardado = malloc(strlen(x.saved_Value.str));
        if(y.t == LNG){
            sprintf(guardado,"%ld",y.saved_Value.l);
            strcat(guardado,x.saved_Value.str);
        }
        else if(y.t == DBL){
            sprintf(guardado,"%g",y.saved_Value.d);
            strcat(guardado,x.saved_Value.str);
        }
        else if(y.t == CHAR){
            sprintf(guardado,"%c",y.saved_Value.c);
            strcat(guardado,x.saved_Value.str);
        }
    push(s,x = (stack_Elem) {.t = STR, .saved_Value.str = guardado});
    }
    }
}


/**
 * Função concatenarNvezesArrays:
 * 
 * Função que verifica os casos da função "concatenarNvezes" em que queremos aplicar a função a um array.
 * 
 * Concatena o array n vezes(sendo este n o valor do elemento que se encontra no topo da stack).
 */


void concatenarNvezesArrays(STACK *s,stack_Elem x,stack_Elem y){
    int tamanho = y.saved_Value.array->sp;
    for(int i = 1; i < x.saved_Value.l;i++){
        for(int j = 0; j < tamanho;j++){
            push(y.saved_Value.array,y.saved_Value.array->stack[j]);
        }
    }
    push(s,y);
}


/**
 * Função concatenarNvezes:
 * 
 * Concatena o penúltimo elemento da stack n vezes( n = valor que se encontra no topo da stack) caso este seja array ou string e quando encontrar "*".
 * 
 * Exemplo: "abc" 3 *     ->  abcabcabc
 *          [ 1 2 3 ] 2 * ->  123123
 */


void concatenarNvezes(STACK *s,stack_Elem x, stack_Elem y){
    if(y.t == ARRAY){
        concatenarNvezesArrays(s,x,y);
    }
    else{
    stack_Elem j;
    j.t = STR;
    char copiada[BUFSIZ];
    strcpy(copiada,y.saved_Value.str);
    for(int i = 0; i < x.saved_Value.l - 1;i++){
        strcat(copiada,y.saved_Value.str);
    }
    j.saved_Value.str = copiada;
    push(s,j);
    }
}


/**
 * Função range: 
 * 
 * Função auxiliar da função "rangeTamanho".
 * 
 * Ao receber o caracter ',', a função recebe o último elemento da stack quando este é LNG e devolve um array que vai desde 0 até ao valor do (LNG - 1).
 * 
 * Exemplo: 5 , -> 01234
 */


void range(STACK *s,stack_Elem x,stack_Elem j){
    int i;
    j.saved_Value.array = new_stack();
    for( i = 0; i < x.saved_Value.l;i++){
        stack_Elem y;
        y.t = LNG;
        y.saved_Value.l = i;
        push(j.saved_Value.array,y);
    }
    push(s,j);
}


/**
 * Função rangeTamanho:
 * 
 * Ao receber o caracter ',', a função faz pop do elemento do topo da stack e devolve:
 * 
 * - O n º de elementos caso este seja Array ou String;
 * 
 * Exemplo: [ 1 2 a 4 ] , -> 4 
            "231ola53" , -> 8
 *
 * - Todos os números de 0 ao (elemento-1) caso seja Long, chamando a função range;
 *
 * Exemplo: 2 ,  -> 01
 *          11 , -> 012345678910
 * 
 * - Filtra um array ou string através de um bloco: retira mais um dos valores da stack e chama a função filtrar;
 *                  (exemplos estão na função filtrar)
 */


int rangeTamanho(STACK *s,stack_Elem *l,char *token){
    if(token[0] == ','){
        stack_Elem j;
        stack_Elem x = pop(s);
        j.t = LNG;
        if(x.t == BLOCO){
            stack_Elem y = pop(s);
            filtrar(s,l,x,y);
            return 1;
        }
        if(x.t == LNG){
            j.t = ARRAY;
            range(s,x,j);
            return 1;
        }
        if(x.t == ARRAY){
            j.saved_Value.l = x.saved_Value.array->sp;
        }
        if(x.t == STR){
            j.saved_Value.l = strlen(x.saved_Value.str);;
        }
        push(s,j);
        return 1;
    }
    return 0;
}


/** 
 * Função procuraIndice:
 * 
 * Quando recebe o simbolo "=" e sendo o penúltimo elemento da stack um array ou uma string.
 * 
 * É devolvido o valor que se encontra na posição do indice dado pelo elemento que se encontra no topo da stack(neste caso o stack_Elem x).
 * 
 * Exemplo: [ 2 7 5 ] 0 = -> 2
         
            "abcd" 2 =    -> c
 */


void procuraIndice(STACK *s,stack_Elem x,stack_Elem y){
    stack_Elem j;
    if(y.t == ARRAY){
        push(s,y.saved_Value.array->stack[x.saved_Value.l]);
    }
    else{
        if(y.t == STR){
        j.t = CHAR;
        j.saved_Value.c = y.saved_Value.str[x.saved_Value.l]; 
        push(s,j);
        }
    }
}

/**
 * Função buscarInicioArray:
 * 
 * Função auxiliar de "buscarInicio".
 * 
 * Função que verifica os casos de "buscarInicio" em que o penúltimo elemento da stack é um array.
 */


void buscarInicioArray(STACK *s,stack_Elem x,stack_Elem y){
    y.saved_Value.array->sp = x.saved_Value.l;
    push(s,y);
}


/**
 * Função buscarInicio:
 * 
 * Caso o valor do stack_Elem y seja um array então é chamada a função auxiliar "buscarInicioArray".
 * 
 * Devolve os primeiros n elementos da string\array ( sendo n o valor do elemento que se encontra no topo da stack --> stack_Elem x).
 * 
 * Exemplo: "abcdef" 3 <  -> abc
 *          [ 1 2 3 4 ] 2 <  -> 12
 */


void buscarInicio(STACK *s,stack_Elem x,stack_Elem y){
    if(y.t == ARRAY){
        buscarInicioArray(s,x,y);
    }
    if(y.t == STR){
        y.saved_Value.str[x.saved_Value.l] = '\0';
        push(s,y);
    }
    return;
}


/**
 * Função buscarFimArray:
 * 
 * Função auxiliar de "buscarFim".
 * 
 * Função que verifica os casos de "buscarFim" em que o penúltimo elemento da stack é um array.
 */


void buscarFimArray(STACK *s,stack_Elem x,stack_Elem y){
    stack_Elem j;
    j.t = ARRAY;
    j.saved_Value.array = new_stack();
    int limite = y.saved_Value.array->sp - x.saved_Value.l;
    for(int i = limite; i < y.saved_Value.array->sp;i++){
        push(j.saved_Value.array,y.saved_Value.array->stack[i]);
    }
    push(s,j);
}


/**
 * Função buscarFim:
 * 
 * Caso o valor do stack_Elem y seja um array então é chamada a função auxiliar "buscarFimArray".
 * 
 * Devolve os últimos n elementos da string\array ( sendo n o valor do elemento que se encontra no topo da stack --> stack_Elem x).
 * 
 * Exemplo: "abcdef" 3 >  -> def
 *          [ 1 2 3 4 ] 2 >  -> 34
 */


void buscarFim(STACK *s,stack_Elem x,stack_Elem y){
    if(y.t == ARRAY){
        buscarFimArray(s,x,y);
    }
    else if(y.t == STR){
        stack_Elem j;
        int tamanho = strlen(y.saved_Value.str);
        int delimita = tamanho - x.saved_Value.l;
        j.saved_Value.str = y.saved_Value.str += delimita;
        j.t = STR;
        push(s,j);
    }
    return;
}


/**
 * Função deleteArrays: 
 * 
 * Função auxiliar de 'retiraPrimeiro' e 'retiraUltimo'.
 * 
 * Adaptação da função "delete" para arrays.
 * 
 * Função responsável por apagar do array o stack_Elem que se encontra na posição N.
 */


void deleteArrays(stack_Elem *x,int N){
    for(int i = N; i != x->saved_Value.array->sp - 1;i++){
        x->saved_Value.array->stack[i] = x->saved_Value.array->stack[i+1];
    }
    x->saved_Value.array->sp--;
}


/**
 * Função delete: 
 * 
 * Função auxiliar de 'retiraPrimeiro' e 'retiraUltimo'.
 * 
 * Função responsável por apagar o elemento que se encontra na posição N.
 */


void delete(stack_Elem *x,int N){
    for(int i = N; x->saved_Value.str[i] != '\0';i++){
        x->saved_Value.str[i] = x->saved_Value.str[i+1];
    }
}


/** 
 * Função retiraPrimeiro:
 * 
 * Se o elemento do topo da stack fôr Array ou String,ao receber "(" a função retira o seu primeiro elemento e coloca-o depois do array ou da string, sendo que o
 * valor deixa da fazer parte do stack_Elem do qual foi retirado.
 *
 * Caso o elemento do topo da stack seja um array, é chamada a função "deleteArrays",para retirar o 1º elemento, após este ser guardado.
 * 
 * Caso o elemento do topo da stack seja uma string é chamada a função "delete", para retirar o 1º elemento, após este ser guardado.
 * 
 * Exemplo: "abcs" (     -> bcsa
 *          [ 3 4 5 ] (  -> 453
 */


void retiraPrimeiro(STACK *s,stack_Elem x){
    if(x.t == ARRAY){
        stack_Elem retirado = x.saved_Value.array->stack[0];
        deleteArrays(&x,0);
        push(s,x);
        push(s,retirado);
    }
    else{
        stack_Elem j;
        char retirado = x.saved_Value.str[0];
        delete(&x,0);
        push(s,x);
        j.saved_Value.c = retirado;
        j.t = CHAR;
        push(s,j);
    }
}


/** 
 * Função retiraUltimo:
 * 
 * Se o elemento do topo da stack fôr Array ou String,ao receber ")" a função retira o seu último elemento e coloca-o depois do array ou da string, sendo que o
 * valor deixa da fazer parte do stack_Elem do qual foi retirado.
 *
 * Caso o elemento do topo da stack seja um array, é chamada a função "deleteArrays",para retirar o último elemento, após este ser guardado.
 * 
 * Caso o elemento do topo da stack seja uma string é chamada a função "delete", para retirar o último elemento, após este ser guardado.
 * 
 * Exemplo: "abcs" )   -> abcs -----> não esquecer que apesar de não se poder reparar nisso sem testar, os valores retirados não se encontram mais na string/array
 *          [ 3 4 5 ] )  -> 453
 */


void retiraUltimo(STACK *s,stack_Elem x){
    if(x.t == ARRAY){
        stack_Elem retirado = x.saved_Value.array->stack[x.saved_Value.array->sp-1];
        deleteArrays(&x,x.saved_Value.array->sp-1);
        push(s,x);
        push(s,retirado);
    }
    else{
        stack_Elem j;
        int indice = strlen(x.saved_Value.str) - 1;
        char retirado = x.saved_Value.str[indice];
        delete(&x,indice);
        push(s,x);
        j.saved_Value.c = retirado;
        j.t = CHAR;
        push(s,j);
    }
}


/** 
 * Função searchSubstring:
 * 
 * Procura uma substring/char, x, na string, y, e devolve o índice onde esta se inicia na string onde se procura.
 * 
 * Caso a substring/char não esteja contida na string então é devolvido -1.
 * 
 * Exemplo: "abcd" "bc" #  -> 1
 *          "abcde" "fc" # -> -1
 */


void searchSubstring(STACK *s,stack_Elem x,stack_Elem y){
    stack_Elem j;
    if(x.t == STR){
        char *ocorre = strstr(y.saved_Value.str,x.saved_Value.str);
        if(ocorre != NULL){
            j.t = LNG;
            j.saved_Value.l = ocorre - y.saved_Value.str;
        }
        else{
            j.t = LNG;
            j.saved_Value.l = -1;
        }
    }
    else if(x.t == CHAR){
        char limite = x.saved_Value.c;
        char *ocorre = strchr(y.saved_Value.str,limite);
        if(ocorre != NULL){
            j.t = LNG;
            j.saved_Value.l = ocorre - y.saved_Value.str;
        }
        else{
            j.t = LNG;
            j.saved_Value.l = -1;
        }
    }
    push(s,j);
}


/** 
 * Função lerInput:
 * 
 * Função responsável por ler um input mesmo que este possua várias linhas.
 * 
 * Só acaba de guardar as linhas lidas numa string quando o valor do fgets atinge o NULL.
 * 
 * Faz push para a stack da string usada como acumulador das linhas que estavam a ser lidas pelo fgets ao longo do ciclo.
 */


int lerInput(STACK *s,char *token){
    if(token[0] == 't'){
    char linha [10100];
    char copiada[10100];
    stack_Elem j;
    while((fgets(linha,10100,stdin)!= NULL))
    {   
        j.t = STR;
        j.saved_Value.str = strdup(linha);
        strcat(copiada,j.saved_Value.str);
    }
    copiada[strlen(copiada)] = '\0';
    j.saved_Value.str = copiada;
    push(s,j);
    return 1;
    }
    return 0;
}


/** 
 * Função separarString:
 * 
 * Função responsável por separar uma string a partir de uma substring da mesma.
 * 
 * A função verifica em que posições ocorrem a substring na string e divide a string nessas mesmas posições, separando-as, e faz push dessas novas substrings
 * criadas para um array.
 * 
 * No fim a função faz push do novo array criado (com as substrings) para a stack principal (s).
 */


void separarString(STACK *s,stack_Elem x,stack_Elem y){
    stack_Elem j;
    stack_Elem l;
    l.t = STR;
    j.t = ARRAY;
    j.saved_Value.array = new_stack();
    int delimita = 1;
    while(delimita){
        if(x.saved_Value.str[0] == '\0'){
            push(s,y);
            return;
        }
        char *copiado = strdup(y.saved_Value.str);
        char *ocorre = strstr(y.saved_Value.str,x.saved_Value.str);
        int index = ocorre - y.saved_Value.str;
        if(ocorre != NULL){
            if(index == 0){
                y.saved_Value.str += strlen(x.saved_Value.str);
            }
            else{
                copiado[index] = '\0';
                l.saved_Value.str = copiado;
                push(j.saved_Value.array,l);
                y.saved_Value.str += index + strlen(x.saved_Value.str);
            }
        }
        else if(ocorre == NULL && strtok(copiado,x.saved_Value.str) != NULL){
            push(j.saved_Value.array,y);
            delimita = 0;
        }
        else if(ocorre == NULL && strtok(copiado,x.saved_Value.str) == NULL){
            delimita = 0;
        }
    }
    push(s,j);
}


/** 
 * Função colocarArrayStack:
 * 
 * Função responsável por fazer push de todos os elementos de um array para a stack.
 */


void colocarArrayStack(STACK *s,stack_Elem x){
    for(int i = 0; i < x.saved_Value.array->sp;i++){
        push(s,x.saved_Value.array->stack[i]);
    }
}


/** 
 * Função separarWhiteSpace:
 * 
 * Função responsável por separar uma string a partir de whitespaces(tab, enter, espaço).
 * 
 * A função verifica em que posições ocorrem os whitespaces na string e divide a string nessas mesmas posições, separando-as, e faz push dessas novas substrings
 * criadas para um array.
 * 
 * No fim a função faz push do novo array criado (com as substrings) para a stack principal (s).
 */


int separarWhiteSpace(STACK *s,char *token){
    if(token[0] == 'S' && token[1] == '/'){
        stack_Elem x = pop(s);
        stack_Elem j;
        stack_Elem l;
        l.t = STR;
        j.t = ARRAY;
        j.saved_Value.array = new_stack();
        char *copia = strdup(x.saved_Value.str);
        char *limite = " \n\t";
        char *ocorre;
        while((ocorre = strtok_r(copia,limite,&copia)) != NULL){
            char *aux = strdup(ocorre);
            l.saved_Value.str = aux;
            push(j.saved_Value.array,l);
        }
        push(s,j);
        return 1;
    }
    return 0;
}


/** 
 * Função separarEnter:
 * 
 * Função responsável por separar uma string a partir de enters.
 * 
 * A função verifica em que posições ocorrem os enters na string e divide a string nessas mesmas posições, separando-as, e faz push dessas novas substrings
 * criadas para um array.
 * 
 * No fim a função faz push do novo array criado (com as substrings) para a stack principal (s).
 */


int separarEnter(STACK *s,char *token){
    if(token[0] == 'N' && token[1] == '/'){
        stack_Elem x = pop(s);
        stack_Elem j;
        stack_Elem l;
        l.t = STR;
        j.t = ARRAY;
        j.saved_Value.array = new_stack();
        char *copia = strdup(x.saved_Value.str);
        char *limite = "\n";
        char *ocorre;
        while((ocorre = strtok_r(copia,limite,&copia)) != NULL){
            char *aux = strdup(ocorre);
            l.saved_Value.str = aux;
            push(j.saved_Value.array,l);
        }
        push(s,j);
        return 1; 
    }
    return 0;
}