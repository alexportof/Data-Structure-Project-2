#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void embaralhar_array(int array[], int n);
void troca(int *a, int *b);
int **tratar_arquivo(char name[], int i);

int main()
{
    int **matriz_imagem;
    char *teste[30];
    int array_teste[25], array_treino[25], array_geral[50];
    //int **matriz;
    char file[100];
    int a = 0, j = 0, n;

    for (int i = 0; i < 50; i++)
    {
        array_geral[i] = i;
    }
    array_geral[0] = 50;
    n = sizeof(array_geral) / sizeof(array_geral[0]);
    embaralhar_array(array_geral, n);
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            array_teste[j] = array_geral[i];
            i++;
            array_treino[j] = array_geral[i];
            i++;
        }
    }
    matriz_imagem = tratar_arquivo("asphalt", 1);
    //printf("%d\n", matriz_imagem[0][0]);
    //
    // for (int i = 0; i < 25; i++)
    // {
    //     matriz_imagem = tratar_arquivo("asphalt", array_treino[i]);
    //     //printf("%d", matriz_imagem[0][0]);
    //     // free(matriz_imagem);
    // }

    return 0;
}

void embaralhar_array(int array[], int n)
{
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        troca(&array[i], &array[j]);
    }
}
void troca(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int **tratar_arquivo(char name[], int arquivo)
{
    FILE *fp;
    char file[100];
    int **matriz_imagem;
    int linha = 0, coluna = 0, valor, caractere;

    matriz_imagem = (int **)malloc(sizeof(int *)); //alocação linha
    matriz_imagem[0] = (int *)malloc(sizeof(int)); // alocação coluna
    //colunas sempre serao alocadas e linhas realocadas

    if (matriz_imagem[0] == NULL || matriz_imagem == NULL)
    {
        printf("deu pra alocar nao");
        exit(1);
    }
    sprintf(file, "DataSet/%s/%s_%.2d.txt", name, name, arquivo);
    fp = fopen(file, "r");
    if (fp == NULL)
    {
        printf("Não foi possivel abrir o Aquivo %d\n", arquivo);
        exit(2);
    }
    linha = 0;
    coluna = 0;
    int a = 0;
    while (!feof(fp))
    {
        fscanf(fp, "%d%c", &valor, &caractere);
        // printf("%d%c", valor, caractere);
        matriz_imagem[linha][coluna] = valor;

        if (caractere == '\n')
        {
            printf("nunca entra nesse caralho é");
            a++;
            linha++;
            matriz_imagem = (int **)realloc(matriz_imagem, (linha + 1) * sizeof(int *)); //realocando na proxima linha
            matriz_imagem[linha] = (int *)malloc(sizeof(int));                           //alocando a coluna da proxima linha
            coluna = 0;
        }
        else
        {
            printf("%d", a);
            a++;
            //coluna++;
            // matriz_imagem[linha] = (int *)malloc(sizeof(int)); //alocando a coluna da mesma linha
        }
    }

    fclose(fp);

    return 0;
}