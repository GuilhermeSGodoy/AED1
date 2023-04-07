// Nome: Guilherme Santos de Godoy
// RA: 758710
// Curso: Ciência da Computação
// Algoritmos e Estruturas de Dados 1 - 2019/2

#include <stdio.h>
#include <stdlib.h>

typedef struct Pessoa {
    int posicao;
    struct Pessoa *prox;
} Pessoa;

Pessoa *inicio = NULL; // Lista vazia

void insereLista (int x);
void removeLista (Pessoa *p);
void imprimeLista ();
int resolveJosephus (int n, int m);

int main()
{
    int nroexecs;

    scanf("%d", &nroexecs);

    int *n = malloc(nroexecs * sizeof(int));
    int *p = malloc(nroexecs * sizeof(int));

    for (int i = 0; i < nroexecs; i++) {
        scanf("%d", &n[i]);
        scanf("%d", &p[i]);
    }

    for (int i = 0; i < nroexecs; i++)
        printf("Usando n=%d, m=%d, resultado=%d\n", n[i], p[i], resolveJosephus(n[i], p[i]));

    return 0;
}

/*
    A funcao insereLista recebe um inteiro x, correspondente a um valor que sera inserido na
    lista ligada circular. Caso seja a primeira insercao, a funcao cria uma cabeca para a lista,
    como forma de inicializa-la, para assim comecar a inserir os elementos, de fato.
*/
void insereLista (int x)
{
    // Condicao para criar o no cabeca da lista
    if (inicio == NULL)
    {
        inicio = (Pessoa*) malloc(sizeof(Pessoa));
        inicio->prox = inicio;
    }

    // Execucao da insercao do elemento
    Pessoa *nova = (Pessoa*) malloc(sizeof(Pessoa));
    nova->posicao = x;
    nova->prox = inicio->prox;
    inicio->prox = nova;
}

/*
    A função imprimeLista nao recebe nenhum parametro, dado que a referida lista esta declarada
    em escopo global. Portanto, seu objetivo e imprimir a lista completa.
*/
void imprimeLista ()
{
    Pessoa *p = inicio->prox;

    while (p != inicio)
    {
        printf("%d ", p->posicao);
        p = p->prox;
    }
    printf("\n");
}

/*
    A funcao remove lista recebe um ponteiro do tipo Pessoa, correspondente a uma celula cuja
    celula seguinte sera removida da lista.
*/
void removeLista (Pessoa *p)
{
    Pessoa *morta;

    morta = p->prox;

    // Verifica se a celula prestes a ser excluida e a cabeça da lista.
    // Caso seja, pula para a proxima posicao, evitando a perda da lista.
    if (morta == inicio)
    {
        p = p->prox;
        morta = p->prox;
    }

    p->prox = morta->prox;

    free(morta);
}

/*
    A funcao resolveJosephus e a responsavel por criar a lista a cada iteracao do
    programa principal, assim como remover os determinados elementos, de acordo com
    a logica de remocao do problema de Josephus. Recebe como parametro um numero inteiro
    n, equivalente a quantidade de pessoas/elementos da lista, um outro numero inteiro
    m, equivalente ao passo que sera dado dentro do circulo/lista circular. Retorna a
    posicao da ultima pessoa viva.
*/
int resolveJosephus (int n, int m)
{
    // Cria e preenche a lista
    for (int i = 0; i < n; i++)
        insereLista(i);

    // Atribuicao do valor -1 a cabeca da lista, com o intuito de
    // facilitar futuras verificacoes.
    inicio->posicao = -1;

    Pessoa *p = inicio; // Ponteiro auxiliar para a cabeça da lista
    int qtdePessoas = n; // Variavel usada para decrementar a quantidade de pessoas
    int aux; // Variavel criada com o intuito de armazenar o valor da posicao do "assassino"
    int contP; // Variavel que conta a quantidade de passos dados ao andar na lista
    int resultado;

    while (qtdePessoas > 1)
    {
        contP = 0;

        while (contP < m)
        {
            p = p->prox;
            contP++;

            // Condicao necessaria para "ignorar" a cabeca da lista
            if (p == inicio)
                p = p->prox;

            // Na primeira iteracao, a variavel aux recebe a posicao do "assassino"
            if (contP == 1)
                aux = p->posicao;
        }

        // Condicao que verifica se o proximo no e a cabeça, evitando que ela seja
        // removida, de modo que nao existe o risco de perder-se a lista.
        if (p->prox == inicio)
        {
            p = p->prox;

            // Condicao que verifica se a posicao do "assassino" e igual a do próximo no.
            // Essa condicao e necessaria pois, sem ela, poderia ocorrer o caso de o
            // "assassino" acabar se matando e, de acordo com as especificacoes do problema,
            // isso não e valido.
            // Essa verificacao e necessaria pois a funcao removeLista() remove o no seguinte
            // ao que esta sendo enviado como parametro.
            if (aux == p->prox->posicao)
            {
                p = p->prox;
                removeLista(p);
            }
            else
                removeLista(p);
        }
        // Condicao que verifica a situacao em que o "assassino" pode acabar se matando,
        // impedindo que isso ocorra.
        // Essa verificacao e necessaria pois a funcao removeLista() remove o no seguinte
        // ao que esta sendo enviado como parametro.
        else if (aux == p->prox->posicao)
        {
            p = p->prox;
            removeLista(p);
        }
        // Condicao que verifica se o no seguinte e a cabeça da lista, impedindo que ela
        // seja removida.
        else if (p->prox == inicio)
        {
            p = p->prox->prox;
            removeLista(p);
        }
        else
            removeLista(p);

        qtdePessoas--;
    }

    // Caso o ponteiro p termine apontando para a cabeça da lista, essa condicao
    // faz com que ele aponte para o proximo elemento da lista, que e o último
    // sobrevivente.
    if (p->posicao == -1)
        p = p->prox;

    // n - p->posicao é uma operacao que se faz necessaria, dado que a lista e percorrida
    // de traz para frente
    resultado = n - p->posicao;

    removeLista(p); // Remove o ultimo elemento da lista

    return resultado;
}
