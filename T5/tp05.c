#include <stdio.h>
#include <stdlib.h>

#define LIN 4
#define COL 4

typedef struct no No;
struct no{
    int linha;
    int coluna;
    No *prox;
};

typedef struct fila Fila;
struct fila{
    No *inicio;
    No *fim;
    int tamanho;
};

typedef struct coordenada Coordenada;
struct coordenada{
    int linha;
    int coluna;
};

Fila *iniciaFila (){
    Fila *f = malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;
    return f;
}

int filaVazia (Fila *f){
    return (f->inicio == NULL);
}

void insereFila (int linha, int coluna, Fila *f){
    No *nova;

    nova = malloc (sizeof(No));
    nova->linha = linha;
    nova->coluna = coluna;

    if (f->inicio == NULL){
        f->fim = nova;
        f->inicio = f->fim;
        f->tamanho++;
        return;
    }

    (f->fim)->prox = nova;
    f->fim = (f->fim)->prox;
    f->tamanho++;
}


No *removeFila (Fila *f){
    No *aux;
    aux = f->inicio;

    f->inicio = aux->prox;
    f->tamanho--;

    if (f->inicio == NULL)  f->fim = NULL;

    return aux;
}


void imprimeFila (Fila *f){
    int i;
    No *aux;

    i = 0;
    aux = f->inicio;

    if (f->tamanho == 0){
        printf ("Fila vazia.");
    }else{
        while (i < f->tamanho){
            printf("(%d, %d) ", aux->linha, aux->coluna);
            aux = aux->prox;
            i++;
        }

        printf("\n");
    }
}


/* retorna 0 se estiver fora da borda e 1 cc. */
int checagem_borda (int lin, int col, int m, int n){

    if((lin < 0) || (lin >= m) || (col < 0) || (col >= n)){
        return 0;
    }else{
        return 1;
    }
}



/* A funcao imprimeCaminho utiliza:
 *      - uma matriz pais, recebida como argumento, que armazena na posicao [i][j] a casa que foi anteriormente visitada no labirinto
 *      - um vetor caminho, que armazena o caminho percorrido no labirinto.
 *
 * A funcao, insere na ultima posicao do vetor caminho a ultima casa do labirinto (m - 1, n -1)e
 * verifica na matriz de pais, qual foi a ultima casa visitada antes da posicao (m - 1, n - 1).  A funcao insere a ultima essa ultima
 * casa visitada na posicao caminho[tam_v -1] e assim sucessivamente. Dessa maneira, obtemos um vetor no qual cada posicao a partir
 * 0, armazena qual a proxima casa acessada na matriz labirinto, que é o caminho percorrido na matriz libirinto.
 */

void imprimeCaminho (No pais[LIN][COL], int m, int n, int tamanho){

    int i, j;
    Coordenada caminho[tamanho];

    int cont = 0;

    for (i = 0; i < LIN; i++)
    {
        for (j = 0; j < COL; j++)
        {
            if (pais[i][j].linha != -1 && pais[i][j].coluna != -1)
            {
                caminho[cont].linha = i;
                caminho[cont].coluna = j;
                cont++;
            }
        }
    }

    printf ("Caminho percorrido: \n");

    for (i = 0; i < cont - 1; i++){
            printf ("(%d, %d)", caminho[i].linha, caminho[i].coluna);
        if (i != cont)
            printf (" -> ");
    }
    printf ("(%d, %d)", m - 1, n - 1);
    printf ("\n");
}



int anda(int labirinto[LIN][COL], int i, int j)
{
    if (labirinto[i][j] == 1)
        return 0;
    return 1;
}

/* A funcao resolveLabirinto trabalha com
 *      - uma fila, f na qual cada casa visitada insere na proxima posicao dessa fila as suas casas adacentes que são livres.
 *      - uma matriz pais, que armazena na posicao [i][j] um no, em que no.linha e no.coluna armazenam a posicao do no anteriormente
 *              visitada no labirinto
 *      - uma matriz distancia, que armazena a distancia entre a casa (0, 0) e todas as outras casas que são atingiveis a partir de
 *             (0, 0), dessa maneira, a casa (m - 1, n -1) armazena a distancia percorrida no caminho.
 * */
int resolveLabirinto (int labirinto[LIN][COL], int m, int n){
    int i, j, distancia[LIN][COL];
    Fila *f;
    No pais[LIN][COL];
    No *atual;


    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            distancia[i][j] = -1;
            pais[i][j].linha = -1;
            pais[i][j].coluna = -1;
        }
    }

    for (i = 0; i < m; i++){
        for ( j = 0; j < n; j++){
            printf("(%d) ", labirinto[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    f = iniciaFila ();
    insereFila (0, 0, f);
    distancia[0][0] = 0;

    i = j = 0;

    int terminou = 0;

    while (!terminou)
    {

        pais[i][j].linha = i;
        pais[i][j].coluna = j;

        if (anda(labirinto, i, j + 1) && checagem_borda(i, j + 1, LIN, COL))
        {
            distancia[i][j + 1] = distancia[i][j] + 1;
            j++;

            insereFila(i, j, f);
        }
        else if (anda(labirinto, i + 1, j) && checagem_borda(i + 1, j, LIN, COL))
        {
            distancia[i + 1][j] = distancia[i][j] + 1;
            i++;

            insereFila(i, j, f);
        }
        else if (anda(labirinto, i, j - 1) && checagem_borda(i, j - 1, LIN, COL))
        {
            distancia[i][j - 1] = distancia[i][j] + 1;
            j--;

            insereFila(i, j, f);
        }
        else if (anda(labirinto, i - 1, j) && checagem_borda(i - 1, j, LIN, COL))
        {
            distancia[i - 1][j] = distancia[i][j] + 1;
            i--;

            insereFila(i, j, f);
        }
        else
        {
            atual = removeFila(f);
            i = atual->linha;
            j = atual->coluna;
            pais[i][j].linha = i;
            pais[i][j].coluna = j;
            distancia[i][j]--;
        }

        if (i == LIN - 1 && j == COL - 1)
            terminou = 1;
    }

    // PREENCHE A CASA FINAL
    pais[i][j].linha = i;
    pais[i][j].coluna = j;

    printf ("A distancia da casa inicial a final: %d\n", distancia[m-1][n-1]);

    imprimeCaminho (pais, m, n, distancia[m - 1][n - 1] + 1);

    if (distancia[m - 1][n - 1] != -1) {
	return 1;
    }else{
	return 0;
    }

}

int main (){

    /* Declaração dos labirintos */
    /* Lembrem-se de alterar as constantes LIN e COL para rodar as funcoes com labirintos de tamanho diferentes */

    int labirinto1[4][4] = { {0,0,1,1}, {1,0,0,0}, {1,0,1,0}, {1,0,0,0}};
    resolveLabirinto (labirinto1, 4, 4);

    int labirinto2[4][4] = { {0,0,1,1}, {1,0,1,0}, {1,0,1,0}, {1,0,0,0}};
    resolveLabirinto (labirinto2, 4, 4);

    int labirinto3[4][4] = { {0,1,1,1}, {0,1,1,0}, {0,1,1,0}, {0,0,0,0}};
    resolveLabirinto (labirinto3, 4, 4);

    int labirinto4[4][4] = { {0,0,0,0}, {0,1,1,0}, {0,1,1,0}, {1,1,1,0}};
    resolveLabirinto (labirinto4, 4, 4);


    return 0;
}
