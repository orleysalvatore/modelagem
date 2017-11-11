#include <stdio.h> //Para usar funções de entrada e saida do teclado e tela
#include <stddef.h> // para usar constante NULL
#include <stdlib.h> // usar a função malloc e free
/*Os valores criados abaixo são numeros aleatórios baseados no algoritmo da congruência

os nós serao chamados de folhas durante a descricao
*/


typedef struct element{     // struct que define cada folha da lista
    int value;                  //variavel q slta o numero aleatório inteiro
    struct element *neighbor;   //aponta para a proxima folha
} number;                   //renomeia a struct para number


void createHead (number **head, int FirstValue)   // função que cria o primeiro nó da lista
{

    if((*head) == NULL){                               //verifica se é nullo, se for nulo ele cria o primeiro nó com
        (*head) = (number *)malloc(sizeof(number));        //o valor da semente inicial
        (*head)->value=FirstValue;                          //salva o valor da semente no no cabeça
        (*head)->neighbor = NULL;
    }
}

void createLeaf(number **lastLeaf, int value)                    // função que aloca um novo no da lista e salva o valor recebido dentro desse nó
{
    number *newLeaf = (number *)malloc(sizeof(number));         //aloca e cria a nova folha
    newLeaf->value = value;                                     //salva valor dentro da folha
    newLeaf->neighbor=NULL;                                     //atrinui valor nulo para proximo
    (*lastLeaf)->neighbor = newLeaf;                            //Aponta o proximo como sendo a nova folha
    (*lastLeaf)=newLeaf;                                        // atualiza a posicao da ultima folha

}

void generating (int a, int M, int control, int seed, int c, number *lastLeaf) // função recursiva que gera a cada recursão um novo valor aleatório
{                                                                              // e e chama a funcao createleaf para alocar em uma lista dinamica, os
                                                                                //parametros desta funcao sao: (a, M, c) valores necessarios para o calculo
                                                                                // da cogruencia, control o valor restante de numeros a serem gerados,
                                                                                //seed a semente ou valor atual, *lastLeaf -> ultima folha.
    if(control<=1){                         //condição de parada da recursao, caso a variavel de
        printf("ACABOU !!!\n\n");             //printa para avisar que acabou
        printf("Procure na raiz de onde esta rodando o codigo, um txt 'numeros' que \nQue contem os valores gerados\n\n");
    }
    else
    {
        seed= (a*seed+c)%M;                             //gera um novo numero baseado no calculo da congruencia
        createLeaf(&lastLeaf, seed);                    //chama funcao para alocar o valor na lista
        generating(a,M,control-1,seed,c,lastLeaf);      //chama recursivamente e decrementa o parametro "control" em menos 1, que
    }                                                   //eh a quantidade de numeros restantes a serem gerados
}

void gravNOtxt (number *lista) // função que pega a lista e grava dentro de um txt
{

    FILE *arq;                          //cria ponterio do tipo arquivo
    arq = fopen("numeros.txt", "wt");   // abre ou cria um arquivo "numeros.txt" para escrever os valores dentro deste txt

    while (lista != NULL)                   // enquanto nao lista nao estiver no fim ela vai entrar para imprimir
    {
        fprintf(arq,"%d\n",lista->value);   //Escreve dentro do arquivo
        lista=lista->neighbor;              //Aponta para a proxima folha.
    }
}

int main(){                                                         //função principal que chama as outras
number *head = NULL, *lastLeaf=NULL;                                //variaveis globais de inicialização, ponterios que controlam a lista
int M,a=5, seed=8, c=3, op;                                         //variaveis para uso da funcao de congruencia e "op" para uso de um switch

printf("Informe a quantidade de numeros aleatorios desejado\n");    //pergunta a quantidade de numeros que deseja gerar
scanf("%d",&M);                                                     // lê a quantidade

createHead(&head,seed);                                             //criar a lista com a cabeça
lastLeaf = head;                                                    //ponteiro que vai salvar uma copia para percorrer a lista



voltar:                                                              //ponto de retorno do "GO TO" na linha 92
printf("Deseja informar uma semente nova?\nAperte\n");                       //pergunta se deseja informar uma semente nova
printf("(1) -> sim\n");                                              //informa as opcoes
printf("(2) -> nao\n");                                              //aperta 1 para sim ou aperta 2 para nao
scanf("%d",&op);                                                      //le a opcao escolhida

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

    default:                                                            //se ele escolher uma opção invalida, ele sera redireciondo pelo GO TO para alinha 71
        printf("Valor invalido\n");
        goto voltar;                                                    //faz voltar o processo de escolha
        break;
}

gravNOtxt(head);                                                        //funcao que salva todos os valores da lista em um arquivo


free(head);                                                             //libera a memoria alocada pela lista
return 0;
}
