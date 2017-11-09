#include <stdio.h> //Para usar fun��es de entrada e saida do teclado e tela
#include <stddef.h> // para usar constante NULL
#include <math.h> // para usar a fun��o ceil
#include <stdlib.h> // usar a fun��o malloc
/*Os valores criados abaixo s�o numeros aleat�rios baseados no algoritmo da congru�ncia*/

typedef struct element{     // struct que define cada n� da lista
    int value;                  //variavel q slta o numero aleat�rio inteiro
    struct element *neighbor;   //aponta para o proximo n�
} number;                   //renomeia a struct




void createHead (number *(*head), int FirstValue)   // fun��o que cria o primeiro n� da lista
{
    if((*head) == NULL){                               //verifica se � nullo, se for nulo ele cria o primeiro n� com
        (*head) = (number *)malloc(sizeof(number));        //o valor da semente inicial
        (*head)->value=FirstValue;                         //salva o valor da semente no n� cabe�a
        printf("%d\n",head);
    }
}

void createLeaf(number *lastLeaf, int value)    // fun��o que aloca um novo n� da lista e salva o valor recebido dentro desse n�
{
    number *newLeaf;                                    //cria ponteiro ara alocar o novo n�
    newLeaf = (number *)malloc(sizeof(number));         //aloca e cria o novo n�
    newLeaf->value = value;                             //salva valor dentro do n�
    lastLeaf->neighbor = newLeaf;                       // atualiza a posicao do ultimo n�
}

void generating (int a, int M, int control, int seed, int c, number *lastLeaf) // fun��o recursiva que gera a cada recurs�o um novo valor aleat�rio
{
    if(control<=1){                         //condi��o de parada da recurs�o
        printf("%d",M);
        printf("ACABOU !!!\n");
    }
    else
    {
        seed= (a*seed+c)%M;                             //cria o novo numero
        createLeaf(lastLeaf, seed);                     //chama fun��o para alocar o novo n� e salvar o valor na lista
        generating(a,M,control-1,seed,c,lastLeaf);      //chama recursivamente e decrementa a quantidade de valores restates para gerar

    }
}

void gravNOtxt (number *lista) // fun��o que pega a lista e grava dentro de um txt
{
    FILE *arq;
    arq = fopen("numeros.txt", "wt");

    while (lista->neighbor != NULL)
    {
        fprintf(arq," %d\n",lista->value);
        lista=lista->neighbor;
    }

}

int main(){                                                         //fun��o principal que chama as outras
number *head = NULL, *lastLeaf=NULL;                                //variaveis globais de inicializa��o
int M,a=5, seed=8, c=1, op;

printf("Informe a quantidade de numeros aleatorios desejado\n");    //pergunta a quantidade de numeros que deseja gerar
scanf("%d",&M);                                                     // l� a quantidade


createHead(head,seed);                                              //criar a lista com a cabe�a
lastLeaf = head;                                                    //n�s que vai ser passado para correr na lista
printf("%d\n",head);
printf("%d\n",lastLeaf);
/*
voltar:                                                              //ponto de retorno do "GO TO" na linha 92
printf("Deseja informar uma semente nova?\n");                       //pergunta se deseja informar uma semente nova
printf("(1) -> sim\n");                                              //informa as op��es
printf("(2) -> nao\n");

switch (op)                                                          //switch para avaliar a escolha e executar de acordo com a escolha
{
    case 1:                                                          // caso 1, ele atualiza o novo valor da semente e come�a a gerar
        printf("Iforme o valor da semente\n");
        scanf("%d",&seed);
        head->value=seed;
        generating(a, M,M+1, seed, c, lastLeaf);
        break;

    case 2:                                                             //caso 2 ele mantem o valor da semente estipulado pelo programa e come�a gerar
        head->value=seed;
        generating(a, M,M+1, seed, c, lastLeaf);
        break;

    default:                                                            //se ele escolher uma op��o invalida, ele ser redireciondo pelo GO TO para alinha 71
        printf("Valor invalido\n");
        goto voltar;                                                    //faz voltar o processo de escolha
        break;
}

gravNOtxt(head);                                                        //pega lista criada e salta dentro de um arquivo nomeado "numeros.txt"
*/                                                                      //esse arquivo est� na raiz do diret�rio do codigo fonte e o compilado
return 0;                                                               //txt criado em tempo de execu��o
}
