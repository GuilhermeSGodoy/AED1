// Nome: Guilherme Santos de Godoy
// RA: 758710
// Curso: Ciência da Computação

#include <stdio.h>
#include <stdlib.h>

unsigned long long contarInversoes(int v[], int n) {

    int i, j, aux;
    unsigned long long num_inv = 0;

    for (j = 1; j < n; j++) {
        aux = v[j];

        for (i = j - 1; i >= 0 && aux < v[i]; i--)
            v[i + 1] = v[i];

        num_inv += j - 1 - i;
        v[i + 1] = aux;
    }

    return num_inv;
}

int main()
{
    int n;

    scanf("%d", &n);

    int v[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);

    int res = contarInversoes(v, n);

    printf("%d\n", res);

    return 0;
}
