#include <stdio.h> //Para usar funções de entrada e saida do teclado e tela
#include <stddef.h> // para usar constante NULL
#include <math.h> // para usar a função ceil
#include <stdlib.h> // usar a função malloc
/*Os valores criados abaixo são numeros aleatórios baseados no algoritmo da congruência*/

typedef struct element{     // struct que define cada nó da lista
    int value;                  //variavel q slta o numero aleatório inteiro
    struct element *neighbor;   //aponta para o proximo nó
} number;                   //renomeia a struct


void createHead (number **head, int FirstValue)   // função que cria o primeiro nó da lista
{
    printf("%d\n", *head);
    if((*head) == NULL){                               //verifica se é nullo, se for nulo ele cria o primeiro nó com
        (*head) = (number *)malloc(sizeof(number));        //o valor da semente inicial
        (*head)->value=FirstValue;                          //salva o valor da semente no nó cabeça
        (*head)->neighbor = NULL;
        printf("%d\n",*head);
    }
}

void createLeaf(number **lastLeaf, int value)    // função que aloca um novo nó da lista e salva o valor recebido dentro desse nó
{
    number *newLeaf = (number *)malloc(sizeof(number));         //aloca e cria o novo nó
    newLeaf->value = value;
    newLeaf->neighbor=NULL;                             //salva valor dentro do nó
    (*lastLeaf)->neighbor = newLeaf;
    *lastLeaf=newLeaf;
                           // atualiza a posicao do ultimo nó
}

void generating (int a, int M, int control, int seed, int c, number *lastLeaf) // função recursiva que gera a cada recursão um novo valor aleatório
{

    if(control<=1){                         //condição de parada da recursão
        printf("%d\n",M);
        printf("ACABOU !!!\n");
    }
    else
    {
        seed= (a*seed+c)%M;
        printf("%d\n",seed);                          //cria o novo numero
        createLeaf(lastLeaf, seed);                     //chama função para alocar o novo nó e salvar o valor na lista
        generating(a,M,control-1,seed,c,&lastLeaf);      //chama recursivamente e decrementa a quantidade de valores restates para gerar

    }
}

void gravNOtxt (number *lista) // função que pega a lista e grava dentro de um txt
{
    printf("teste2\n");
    printf("%d\n", lista);
    FILE *arq;
    arq = fopen("numeros.txt", "wt");

    while (lista != NULL)
    {
        fprintf(arq,"%d\n",lista->value);
        lista=lista->neighbor;
    }

}

int main(){                                                         //função principal que chama as outras
number *head = NULL, *lastLeaf=NULL;                                //variaveis globais de inicialização
int M,a=5, seed=8, c=3, op;

number *last = NULL;
/*
createHead(&head, 1); last = head;
createLeaf(&last, 2);
createLeaf(&last, 3);
createLeaf(&last, 4);
createLeaf(&last, 5);
createLeaf(&last, 6);

gravNOtxt(head);

exit(1);
*/

printf("Informe a quantidade de numeros aleatorios desejado\n");    //pergunta a quantidade de numeros que deseja gerar
scanf("%d",&M);                                                     // lê a quantidade

createHead(&head,seed);

printf("oficial %d\n",head);                                              //criar a lista com a cabeça
lastLeaf = head;
                                                //nós que vai ser passado para correr na lista



voltar:                                                              //ponto de retorno do "GO TO" na linha 92
printf("Deseja informar uma semente nova?\n");                       //pergunta se deseja informar uma semente nova
printf("(1) -> sim\n");                                              //informa as opções
printf("(2) -> nao\n");
scanf("%d",&op);

switch (op)                                                          //switch para avaliar a escolha e executar de acordo com a escolha
{
    case 1:                                                          // caso 1, ele atualiza o novo valor da semente e começa a gerar
        printf("Iforme o valor da semente\n");
        scanf("%d",&seed);
        head->value=seed;
        generating(a, M,M, seed, c, &lastLeaf);
        break;

    case 2:                                                             //caso 2 ele mantem o valor da semente estipulado pelo programa e começa gerar
        generating(a, M,M, seed, c, &lastLeaf);
        break;

    default:                                                            //se ele escolher uma opção invalida, ele ser redireciondo pelo GO TO para alinha 71
        printf("Valor invalido\n");
        goto voltar;                                                    //faz voltar o processo de escolha
        break;
}

printf("\teste1\n");
printf("%d\n", head);
gravNOtxt(head);
printf("\n\n\n\n");

while(head!= NULL)
{
    printf("%d\n",head->value);
    head=head->neighbor;
}//pega lista criada e salta dentro de um arquivo nomeado "numeros.txt"


free(head);                                                                        //esse arquivo está na raiz do diretório do codigo fonte e o compilado
return 0;                                                               //txt criado em tempo de execução
}


