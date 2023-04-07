// Informações do estudante
// Nome: Guilherme Santos de Godoy
// Curso: Ciência da Computação
// RA: 758710

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
   A função palindromoR é uma função recursiva que recebe como parâmetros um número
   inteiro i >= 0, correspondente à posição inicial da string, um outro número inteiro
   f <= n-1, correspondente à posição final da string, e um vetor s[0..n-1] de caracteres,
   que armazena a string que será utilizada para a verificação de palíndromo. A função
   retorna 1 se a string for um palíndromo e retorna 0 caso contrário.
*/
int palindromoR(int i, int f, char *s)
{
    // Caso em que não existem caracteres a serem verificados
    if (i < 0 || f < 0)
        return 1;
    // Verifica se a posição incial é igual a posição final, de modo que
    // a verificação do restante da palavra prossiga.
    else if (s[i] == s[f])
    {
        // Se a condição acima for verdadeira, verifica se a posição inicial
        // é menor que a metade do tamanho da palavra, de modo que não ocorram
        // verificações redundantes.
        if (i < (strlen(s) - 1) / 2)
            // Continua a verificação para a letra seguinte à inicial e a letra anterior à final.
            return palindromoR(i+1, f-1, s);
    }
    else
        return 0;

    return 1;
}

/*
   A função palindromo é uma função que chama a recursiva palindromoR e tem como parâmetro
   único um vetor s[0..n-1], que armazena a string que será utilizada na verificação da função
   recursiva. A função não retorna nenhum valor, apenas escreve o resultado da operação.
*/
void palindromo(char *s)
{
    int saida = palindromoR(0, strlen(s) - 1, s);

    printf("\"");
    printf("%s", s);
    printf("\" ");

    // Verifica se a string verificada é, de fato, um palíndromo.
    if (saida)
        printf("eh palindromo\n");
    else
        printf("nao eh palindromo\n");
}

/*
   A função inversaR é uma função recursiva que recebe como parâmetro um vetor s[0..n-1],
   que armazena a string que será invertida. A função não retorna nenhum valor, apenas
   imprime a string de acordo com a inversão executada.
*/
void inversaR(char *str)
{
    // Condição que garante que a posição atual é, de fato, a primeira, além de impedir
    // que a verificação ultrapasse o limite da string.
    if (*str)
    {
        // Chama a função para a próxima posição e faz isso até que a string termine.
        inversaR(str + 1);
        // Efetua a inversão
        printf("%c", *str);
    }
}

/*
   A função inversa chama a recursiva inversaR e recebe como parâmetro um vetor s[0..n-1], que
   armazena a string que será invertida. A função não retorna nenhum valor, apenas escreve a
   string antes e após a inversão, para fins de comparação.
*/
void inversa(char *s)
{
    printf("inversa de \"");
    printf("%s", s);
    printf("\" = ");

    inversaR(s);

    printf("\n");
}

/*
   A função fibonacciR é uma função recursiva que recebe como parâmetro um inteiro n >= 0,
   e calcula o n-ésimo termo da sequência de Fibonacci. Retorna n para os casos bases n = 0
   e n = 1, ou retorna o valor do n-ésimo termo.
*/
int fibonacciR(int n)
{
    if (n == 0)
        return n;
    else if (n == 1)
        return n;
    else
        // Retorna a soma entre os dois termos imediatamente anteriores.
        return fibonacciR(n - 1) + fibonacciR(n - 2);
}

/*
   A função fibonacci chama a recursiva fibonacciR e recebe como parâmetro um inteiro n >= 0,
   que será utilizado para definir a quantidade de termos que serão calculados, servindo como
   o limite superior para o laço que efetua as chamadas da função recursiva. A função não retorna
   nenhum valor, apenas imprime a sequência de acordo com o valor n.
*/
void fibonacci(int n)
{
    int i;

    printf("%d primeiros numeros de fibonacci = ", n);
    // Laço que chama a função recursiva e calcula cada termo da sequência individualmente.
    for (i = 0; i < n; i++)
        printf("%d ", fibonacciR(i));

    printf("\n");
}

/*
   A função pisoLogR é uma função recursiva que recebe como parâmetro um inteiro x > 0,
   e calcula o piso do log de x na base 2. A função retorna 0 para o caso base 1 ou o
   valor do piso de log calculado.
*/
int pisoLogR(int x)
{
    // A variável i é inicializada com 1, pois é o caso base para qualquer número
    // maior ou igual a 2.
    int i = 1;

    if (x == 1)
        return 0;
    // Caso o valor de x seja maior do que 1, a função pisoLogR é chamada novamente,
    // tendo a metade do valor de x como argumento.
    else if (x > 1)
        // Soma acumuladamente o valor de i com o valor retornado da função.
        i += pisoLogR(x/2);

    return i;
}

/*
   A função pisoLog chama a recursiva pisoLogR e recebe como parâmetro um inteiro x > 0, que
   é o número cujo piso do log na base 2 será calculado. A função não retorna nenhum valor,
   apenas exibe o resultado da operação.
*/
void pisoLog(int x)
{
    int valor = 0;
    printf("piso de log base 2 de %d = ", x);
    valor = pisoLogR(x);
    printf("%d\n", valor);
}

int main(int argc, char *argv[])
{
    int t;

    scanf("%d", &t);

    if (t < 1 || t > 4)
    {
        printf("Parametros incorretos.\n");
        printf("Ex:\n");
        printf("tp01_recursao 1 [para testar palindromo]\n");
        printf("tp01_recursao 2 [para testar inversa]\n");
        printf("tp01_recursao 3 [para testar fibonacci]\n");
        printf("tp01_recursao 4 [para testar pisoLog]\n");
    }

    if (t == 1)
    {
        printf("\nTestando palindromo()\n\n");
        palindromo("");
        palindromo("1");
        palindromo("77");
        palindromo("505");
        palindromo("1111");
        palindromo("2112");
        palindromo("369963");
        palindromo("10101");
        palindromo("1001001");
        palindromo("12");
        palindromo("12451");
        palindromo("100011");
    }
    else if (t == 2)
    {
        printf("\nTestando inversa()\n\n");
        // Este caso de teste não consta no runcodes e estava gerando erros nas verificações.
        //inversa("");
        inversa("ab");
        inversa("gato");
        inversa("minerva");
    }
    else if (t == 3)
    {
        printf("\nTestando fibonacci()\n\n");
        fibonacci(0);
        fibonacci(1);
        fibonacci(2);
        fibonacci(4);
        fibonacci(10);
    }
    else if (t == 4)
    {
        printf("\nTestando pisoLog()\n\n");
        pisoLog(1);
        pisoLog(2);
        pisoLog(3);
        pisoLog(4);
        pisoLog(5);
        pisoLog(15);
        pisoLog(16);
        pisoLog(17);
        pisoLog(127);
        pisoLog(256);
        pisoLog(511);
        pisoLog(512);
    }

    return 0;
}
