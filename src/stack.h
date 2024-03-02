/**
 * Ficheiro stack.h:
 * 
 * Ficheiro onde se encontram as structs necessárias para o bom funcionamento do programa.
 * 
 * Támbem estão presentes as declarações de todas as funções principais do programa, ou seja, nenhuma das funções auxiliares usadas nas funções aqui presentes
 * necessitam de estar declaradas.
 */


/**
 * enum --> type:
 * 
 * Enum que contêm os tipos que os valores da stack poderão assumir.
 */


typedef enum {
  CHAR,
  INT,
  STR,
  LNG,
  DBL,
  BLOCO,
  ARRAY
}type;

/**
 * Declaração da struct STACK para a poder utilizar na struct stack_Elem antes dela estar definida.
 */


struct STACK;


/**
 * struct --> stack_Elem:
 * 
 * Struct constituida por um union e um type.
 * 
 * O type é usado como indicador do tipo que queremos ir buscar ao union.
 * 
 * O union(saved_Value) contêm valores de todos os tipos que estão presente no type.
 */


typedef struct stack_Elem{
  type t;
  union{
    char c;
    int i;
    char *str;
    char *bloco;
    long l;
    double d;
    struct STACK* array;
  }saved_Value;
}stack_Elem;


/**
 * struct ---> STACK,
 * 
 * Struct que é usada como base de todo o programa.
 * 
 * É constituida por uma lista de stack_Elem e um stack pointer que tem o valor da posição do stack_Elem que se encontra no topo da stack.
 */


typedef struct STACK{
  stack_Elem *stack;
  int sp;
  int capacidade;
}STACK;

/**
 * Indicação da função somar.
 */

int somar(STACK *s,char *token); 

/**
 * Indicação da função subtrair.
 */

int subtrair(STACK *s,char *token);

/**
 * Indicação da função dividir.
 */

int dividir(STACK *s,char *token);

/**
 * Indicação da função multiplicar.
 */

int multiplicar(STACK *s,stack_Elem *l,char *token);

/**
 * Indicação da função incrementar.
 */

int incrementar(STACK *s,char *token);

/**
 * Indicação da função decrementar.
 */

int decrementar(STACK *s,char *token);

/**
 * Indicação da função modulo.
 */

int modulo(STACK *s,stack_Elem *l,char *token);

/**
 * Indicação da função exponenciacao.
 */

int exponenciacao(STACK *s,char *token);

/**
 * Indicação da função eBitwise.
 */

int eBitwise(STACK *s,char *token);

/**
 * Indicação da função ouBitwise.
 */

int ouBitwise(STACK *s,char *token);

/**
 * Indicação da função xorBitwise.
 */

int xorBitwise(STACK *s,char *token);

/**
 * Indicação da função notBitwise.
 */

int notBitwise(STACK *s,stack_Elem *l,char *token);

/**
 * Indicação da função rodar.
 */

int rodar(STACK *s,char *token);

/**
 * Indicação da função duplicar.
 */

int duplicar(STACK *s,char *token);

/**
 * Indicação da função realizarPop.
 */

int realizarPop(STACK *s,char *token);

/**
 * Indicação da função trocar.
 */

int trocar(STACK *s,char *token);

/**
 * Indicação da função copiaNesimo.
 */

int copiaNesimo(STACK *s,stack_Elem *l,char *token);

/**
 * Indicação da função converteChar.
 */

int converteChar(STACK *s,char *token);

/**
 * Indicação da função converteInt.
 */

int converteInt(STACK *s,char *token);

/**
 * Indicação da função converteDouble.
 */

int converteDouble(STACK *s,char *token);

/**
 * Indicação da função converteString.
 */

int converteString(STACK *s,char *token);

/**
 * Indicação da função lerLinha.
 */

int lerLinha(STACK *s,char *token);

/**
 * Indicação da função igual.
 */

int igual(STACK *s,char *token);

/**
 * Indicação da função menor.
 */

int menor(STACK *s,char *token);

/**
 * Indicação da função maior.
 */

int maior(STACK *s,char *token);

/**
 * Indicação da função maiorAux.
 */

int maiorAux(type l,stack_Elem x, stack_Elem y);

/**
 * Indicação da função negacao.
 */

int negacao(STACK *s,char *token);

/**
 * Indicação da função eShortcut.
 */

int eShortcut(STACK *s,char *token);

/**
 * Indicação da função ouShortcut.
 */

int ouShortcut(STACK *s,char *token);

/**
 * Indicação da função maiorDoTopo.
 */

int maiorDoTopo(STACK *s,char *token);

/**
 * Indicação da função menorDoTopo.
 */

int menorDoTopo(STACK *s,char *token);

/**
 * Indicação da função ifThenElse.
 */

int ifThenElse(STACK *s,char *token);

/**
 * Indicação da função criarVariaveis.
 */

void criarVariaveis(stack_Elem *l);

/**
 * Indicação da função colocarVariavel.
 */

int colocarVariavel(STACK *s,stack_Elem *l,char *token);

/**
 * Indicação da função copiarParaVariavel.
 */

int copiaParaVariavel(STACK *s,stack_Elem *l,char *token);

/**
 * Indicação da função concatenar.
 */

void concatenar(STACK *s,stack_Elem x, stack_Elem y);

/**
 * Indicação da função concatenarNvezes.
 */

void concatenarNvezes(STACK *s,stack_Elem x, stack_Elem y);

/**
 * Indicação da função rangeTamanho.
 */

int rangeTamanho(STACK *s,stack_Elem *l,char *token);

/**
 * Indicação da função procuraIndice.
 */

void procuraIndice(STACK *s,stack_Elem x,stack_Elem y);

/**
 * Indicação da função buscarInicio.
 */

void buscarInicio(STACK *s,stack_Elem x,stack_Elem y);

/**
 * Indicação da função buscarFim.
 */

void buscarFim(STACK *s,stack_Elem x,stack_Elem y);

/**
 * Indicação da função retiraPrimeiro.
 */

void retiraPrimeiro(STACK *s,stack_Elem x);

/**
 * Indicação da função retiraUltimo.
 */

void retiraUltimo(STACK *s,stack_Elem x);

/**
 * Indicação da função searchSubstring.
 */

void searchSubstring(STACK *s,stack_Elem x,stack_Elem y);

/**
 * Indicação da função lerInput.
 */

int lerInput(STACK *s,char *token);

/**
 * Indicação da função separarString.
 */

void separarString(STACK *s,stack_Elem x,stack_Elem y);

/**
 * Indicação da função handle.
 */

void handle(STACK *s,stack_Elem *l,char *token);


/**
 * Indicação da função operacoes.
 */

void operacoes(STACK *s,stack_Elem *lista,char *linha);

/**
 * Indicação da função colocarArrayStack.
 */

void colocarArrayStack(STACK *s,stack_Elem x);

/**
 * Indicação da função verificarArray.
 */

char *verificarArray(char **str);

/**
 * Indicação da função separarWhiteSpace.
 */

int separarWhiteSpace(STACK *s,char *token);

/**
 * Indicação da função separarEnter.
 */

int separarEnter(STACK *s,char *token);

/**
 * Indicação da função executaBloco.
 */

void executaBloco(STACK *s,stack_Elem *l,char *str);

/**
 * Indicação da função aplicarBloco.
 */

void aplicarBloco (STACK *s,stack_Elem *l,stack_Elem x,stack_Elem y);

/**
 * Indicação da função fold.
 */

void fold(STACK *s,stack_Elem *l,stack_Elem x,stack_Elem y);

/**
 * Indicação da função delete.
 */

void delete(stack_Elem *x,int N);

/**
 * Indicação da função filtrar.
 */

void filtrar(STACK *s,stack_Elem *l,stack_Elem x,stack_Elem y);

/**
 * Indicação da função deleteArrays.
 */

void deleteArrays(stack_Elem *x,int N);

/**
 * Indicação da função ordenaViaBloco.
 */

void ordenaViaBloco(STACK *s,stack_Elem *l,stack_Elem x,stack_Elem y);

/**
 * Indicação da função whileTruthy.
 */

int whileTruthy(STACK *s,stack_Elem *l,char *token);

/**
 * Indicação da função imprimeTopo.
 */

int imprimeTopo(STACK *s,char *token);

/**
 * Indicação da função printArray.
 */

void printArray(STACK *s);

/**
 * Indicação da função new_stack.
 */

STACK *new_stack();

/**
 * Indicação da função push.
 */

void push(STACK *s,stack_Elem elem);

/**
 * Indicação da função pop.
 */

stack_Elem pop(STACK *s);

/**
 * Indicação da função pushToken.
 */

int pushToken(STACK *s,char *token);