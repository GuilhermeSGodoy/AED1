// Nome: Guilherme Santos de Godoy
// RA: 758710
// Curso: Ciência da Computação
// Algoritmos e Estruturas de Dados 1 - 2019/2

#include <stdio.h>
#include <stdlib.h>

// Constantes para definir água e terra na matriz para montar as ilhas
#define WATER 0
#define LAND 1

// Quantidade máxima de colunas
#define MAX_COLS 1024

// Tipo que define a posição [i][j] da matriz, para fins de verificação e para uso da pilha
typedef struct pos
{
    int i;
    int j;
} Posicao;

// Implementação de pilha com nó cabeça
// Tipo que define uma célula da pilha
typedef struct celula
{
    Posicao conteudo;
    struct celula *prox;
} Celula;

// Função que cria uma pilha com nó cabeça
// Não recebe parâmetros de entrada.
// Retorna a pilha inicializada.
Celula *criaPilha()
{
    Celula *pilha;

    pilha = (Celula *) malloc(sizeof(Celula));
    pilha->prox = NULL;

    return pilha;
}

// Função que coloca os elementos na pilha.
// Tem como parâmetros de entrada um ponteiro para a pilha
// e a posição x do tipo Posicao declarado acima.
// Não tem valor de retorno
void empilha(Celula *pilha, Posicao x)
{
    Celula *nova;

    nova = malloc(sizeof(Celula));
    nova->conteudo = x;
    nova->prox = pilha->prox;
    pilha->prox = nova;
}

// Função que remove os elementos da pilha.
// Tem como parâmetro de entrada um ponteiro para a pilha.
// Retorna a posição [i][j] do último elemento inserido na pilha.
Posicao desempilha(Celula *pilha)
{
    Posicao valor;
    Celula *morta;

    morta = pilha->prox;
    valor = morta->conteudo;
    pilha->prox = morta->prox;

    free(morta);
    morta = NULL;

    return valor;
}

// Função que verifica se a pilha está vazia.
// Recebe um ponteiro para a pilha como parâmetro.
// Retorna 0 caso a pilha ainda tenha elementos e 1 caso contrário.
int pilhaVazia(Celula *pilha)
{
    return pilha->prox == NULL;
}

// Função que desaloca a pilha.
// Recebe como parâmetro de entrada um ponteiro para a pilha.
// Retorna o valor NULL para o ponteiro original da pilha.
Celula *liberaPilha(Celula *pilha)
{
    Celula *p, *morta;
    p = pilha;

    while (p != NULL)
    {
        morta = p;
        p = p->prox;
        free(morta);
    }

    return NULL;
}

// Função para alocar um ponteiro que será utilizado na construção da matriz.
// Recebe como parâmetro de entrada o tamanho do tipo alocado.
// Não tem valor de retorno.
void *malloc_safe(unsigned nbytes)
{
    void *p;
    p = malloc(nbytes);

    if (p == NULL)
    {
        printf("Nao foi possível alocar!\n");
        exit(EXIT_FAILURE);
    }

    return p;
}

// Função para criar a matriz.
// Recebe como parâmetros de entrada as quantidades de linhas e colunas da matriz.
// Retorna um ponteiro com a matriz criada.
int** create_matrix(int n_rows, int n_cols)
{
    int** m = NULL;
    m = malloc_safe(n_rows*(sizeof(int*)));

    for (int i = 0; i < n_rows; ++i)
        m[i] = malloc_safe(n_cols*sizeof(int));

    return m;
}

// Desaloca a matriz criada.
// Recebe como parâmetros de entrada o ponteiro para a matriz criada e a
// quantidade de linhas da matriz.
// Não tem valor de retorno.
void destroy_matrix(int **m, int n_rows)
{
    for (int i = 0; i < n_rows; ++i)
        free(m[i]);

    free(m);
}

// Lê os dados da matriz, linha por linha.
// Recebe como valores de entrada um ponteiro para a matriz criada,
// a quantidade de linhas da matriz e a quantidade de colunas.
// Não tem valor de retorno.
void read_input(int* m[], int *n_rows, int *n_cols)
{
    char line[MAX_COLS];

    for (int i = 0; i < *n_rows; ++i)
    {
        fgets(line, MAX_COLS, stdin);
        for (int j = 0; j < *n_cols; ++j)
        {
            if(line[j] == '0')
                m[i][j] = WATER;
            else if(line[j] == '1')
                m[i][j] = LAND;
            else
            {
                printf("Wrong char in buffer\n");
                printf("%s\n", line);
                exit(EXIT_FAILURE);
            }
        }
    }
}

// Imprime a matriz.
// Tem como parâmetros de entrada um ponteiro para a matriz criada
// e a quantidade de linhas e colunas.
// Não tem valor de retorno.
void print_matrix(int** m, int n_rows, int n_cols)
{
    printf("Print %d x %d matrix\n", n_rows, n_cols);

    for (int i = 0; i < n_rows; ++i)
    {
        for (int j = 0; j < n_cols; ++j)
            printf("%d", m[i][j]);

        printf("\n");
    }
    printf("\n");
}

// Função utilizada para zerar os elementos de uma matriz.
// Tem como parâmetros de entrada um ponteiro para a matriz e os
// valores de linha e coluna.
// Não tem valor de retorno.
void zeraMat(int **m, int L, int C)
{
    for (int i = 0; i < L; i++)
        for (int j = 0; j < C; j++)
            m[i][j] = 0;
}

// Função que verifica se existe LAND na célula de cima da matriz.
// Tem como parâmetros de entrada um ponteiro para a matriz, um ponteiro
// para a matriz que indica se as células já foram visitadas e uma variável
// do tipo Posicao definido anteriormente, como parâmetro de comparação.
// Retorna 1 caso a célula esteja livre e 0 caso contrário.
int verificaCima(int** m, int** visitado, Posicao position)
{
    // Verificada se a posição está dentro dos limites da matriz
    if (position.i - 1 >= 0)
    {
        // Verifica se determinada posição da matriz é LAND (tem valor 1)
        // e se ainda não foi visitada
        if (m[position.i - 1][position.j] == LAND && !visitado[position.i - 1][position.j])
        {
            // Marca a posição como visitada
            visitado[position.i - 1][position.j] = 1;
            return 1;
        }
    }

    return 0;
}

// Função que verifica se existe LAND na célula à esquerda da matriz.
// Tem como parâmetros de entrada um ponteiro para a matriz, um ponteiro
// para a matriz que indica se as células já foram visitadas e uma variável
// do tipo Posicao definido anteriormente, como parâmetro de comparação.
// Retorna 1 caso a célula acima livre e 0 caso contrário.
int verificaEsquerda(int** m, int** visitado, Posicao position)
{
    // Verificada se a posição está dentro dos limites da matriz
    if (position.j - 1 >= 0)
    {
        // Verifica se determinada posição da matriz é LAND (tem valor 1)
        // e se ainda não foi visitada
        if (m[position.i][position.j - 1] == LAND && !visitado[position.i][position.j - 1])
        {
            // Marca a posição como visitada
            visitado[position.i][position.j - 1] = 1;
            return 1;
        }
    }

    return 0;
}

// Função que verifica se existe LAND na célula à direita da matriz.
// Tem como parâmetros de entrada um ponteiro para a matriz, um ponteiro
// para a matriz que indica se as células já foram visitadas e uma variável
// do tipo Posicao definido anteriormente, como parâmetro de comparação.
// Retorna 1 caso a célula esteja livre e 0 caso contrário.
int verificaDireita(int** m, int C, int** visitado, Posicao position)
{
    // Verificada se a posição está dentro dos limites da matriz
    if (position.j + 1 < C)
    {
        // Verifica se determinada posição da matriz é LAND (tem valor 1)
        // e se ainda não foi visitada
        if (m[position.i][position.j + 1] == LAND && !visitado[position.i][position.j + 1])
        {
            // Marca a posição como visitada
            visitado[position.i][position.j + 1] = 1;
            return 1;
        }
    }
    return 0;
}

// Função que verifica se existe LAND na célula de baixo da matriz.
// Tem como parâmetros de entrada um ponteiro para a matriz, um ponteiro
// para a matriz que indica se as células já foram visitadas e uma variável
// do tipo Posicao definido anteriormente, como parâmetro de comparação.
// Retorna 1 caso a célula esteja livre e 0 caso contrário.
int verificaBaixo(int** m, int L, int** visitado, Posicao position)
{
    // Verificada se a posição está dentro dos limites da matriz
    if (position.i + 1 < L)
    {
        // Verifica se determinada posição da matriz é LAND (tem valor 1)
        // e se ainda não foi visitada
        if (m[position.i + 1][position.j] == LAND && !visitado[position.i + 1][position.j])
        {
            // Marca a posição como visitada
            visitado[position.i + 1][position.j] = 1;
            return 1;
        }
    }

    return 0;
}

// Função que calcula as áreas correspondentes a ilhas na matriz.
// Recebe como parâmetros de entrada um ponteiro para a matriz e as
// quantidades de linhas e colunas.
// Retorna a maior área encontrada na matriz.
int search_max_area(int** m, int n_rows, int n_cols)
{
    // Cria uma matriz do mesmo tamanho da matriz principal
    // para armazenar as posições que já foram visitadas.
    int **visitado = create_matrix(n_rows, n_cols);

    // Variável que armazenará o valor da área da ilha em cada
    // verificação
    int area;
    // Vetor que armazenará as áreas calculadas
    int vet[100];
    // Variável que conta quantidade de áreas calculadas, além de
    // servir como índice do vetor
    int cont = 0;

    // Ponteiro do tipo Celula que cria a pilha
    Celula *pilha = criaPilha();
    // Variável do tipo Posicao que armazenará a posição [i][j]
    // dos valores que serão verificados
    Posicao position;

    // Zera a matriz de visitados, de modo que todos são inicializados
    // como não visitados
    zeraMat(visitado, n_rows, n_cols);

    for (int i = 0; i < n_rows; i++)
    {
        for (int j = 0; j < n_cols; j++)
        {
            // Zera a variável area a cada verificação de ilha
            area = 0;
            // Caso encontre um valor LAND, começa a verificar as
            // células nos arredores para calcular a área
            if (m[i][j] == LAND && !visitado[i][j])
            {
                // Atribui a posição à variável auxiliar position
                position.i = i;
                position.j = j;

                // Empilha o primeiro valor encontrado na pilha
                empilha(pilha, position);
                visitado[i][j] = 1;
                area++;

                // Enquanto a pilha não estiver vazia, continua verificando
                // todas as células em todas as posições possíveis
                while (!pilhaVazia(pilha))
                {
                    // Verificações em todas as posições
                    // Caso encontre LAND em alguma das posições,
                    // a posição é empilhada e a verificação continua
                    // a partir da última posição colocada na pilha.
                    // Caso não encontre LAND, desempilha os elementos
                    // e continua verificando até encontrar novas células
                    // LAND ou esvaziar a pilha.
                    if (verificaCima(m, visitado, position))
                    {
                        area++;

                        position.i = position.i - 1;
                        position.j = position.j;

                        empilha(pilha, position);
                    }
                    else if (verificaEsquerda(m, visitado, position))
                    {
                        area++;

                        position.i = position.i;
                        position.j = position.j - 1;

                        empilha(pilha, position);
                    }
                    else if (verificaDireita(m, n_cols, visitado, position))
                    {
                        area++;

                        position.i = position.i;
                        position.j = position.j + 1;

                        empilha(pilha, position);
                    }
                    else if (verificaBaixo(m, n_rows, visitado, position))
                    {
                        area++;

                        position.i = position.i + 1;
                        position.j = position.j;

                        empilha(pilha, position);
                    }
                    else
                        position = desempilha(pilha);

                }

                vet[cont] = area;
                cont++;
            }
        }
    }

    // Desaloca a pilha
    pilha = liberaPilha(pilha);

    // Busca o maior valor no vetor, que corresponderá
    // à área da maior ilha
    int maior = vet[0];

    for (int i = 1; i < cont; i++)
        if (maior < vet[i])
            maior = vet[i];

    return maior;
}

int main(void)
{
    int n_rows = 0, n_cols = 0;

    // Lê o número de linhas e colunas
    scanf("%d %d\n", &n_rows, &n_cols);

    // Aloca a matriz
    int **m = create_matrix(n_rows, n_cols);
    // Lê a matriz
    read_input(m, &n_rows, &n_cols);

    // Calcula a área
    int area = search_max_area(m, n_rows, n_cols);
    printf("%d", area);

    /*Função para desalocar a matriz.*/
    destroy_matrix(m, n_rows);

    return 0;
}
