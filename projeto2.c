#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void embaralhar_array(int array[], int n);
void troca(int *a, int *b);
int **tratar_arquivo(char name[], int i, int *tamanho);
int tamanho_matriz(int tamanho, int **matriz);
int *ilbp(int **matriz, int *tamanho);
int *glcm(int **matriz, int *tamanho);

int main()
{
    int **matriz_imagem, *tamanho, *matriz_ilbp, *matriz_glcm;
    char file[100];
    char *teste[30];
    int array_teste[25], array_treino[25], array_geral[50];
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
    for (int i = 0; i < 25; i++)
    {
        matriz_imagem = tratar_arquivo("asphalt", array_treino[i], &tamanho);
        // pra calcular ilbp e glcm preciso do tamanho da matriz
        matriz_ilbp = ilbp(matriz_imagem, &tamanho);
        matriz_glcm = glcm(matriz_imagem, &tamanho);

        free(matriz_ilbp);
        free(matriz_imagem);
    }

    return 0;
}

int *glcm(int **matriz, int *tamanho)
{
    int **norte, **nordeste, **leste, **sudeste, **sul, **sudoeste, **oeste, **noroeste;
}

int *ilbp(int **matriz, int *tamanho)
{
    float media;
    int pixels[9], *array_ilbp, array_pos_media[9], numero_decimal, menor_binario;
    array_ilbp = (int *)calloc(512, sizeof(int));

    for (int i = 1; i < *tamanho - 1; i++)
    {
        for (int j = 1; j < *tamanho - 1; j++)
        {
            pixels[0] = matriz[i - 1][j - 1];
            pixels[1] = matriz[i - 1][j];
            pixels[2] = matriz[i - 1][j + 1];
            pixels[3] = matriz[i][j - 1];
            pixels[4] = matriz[i][j];
            pixels[5] = matriz[i][j + 1];
            pixels[6] = matriz[i + 1][j - 1];
            pixels[7] = matriz[i + 1][j];
            pixels[8] = matriz[i + 1][j + 1];

            media = (pixels[0] + pixels[1] + pixels[2] + pixels[3] + pixels[4] + pixels[5] + pixels[6] + pixels[7] + pixels[8]) / 9.0;

            for (int i = 0; i < 9; i++)
            {
                if (pixels[i] > media)
                    array_pos_media[i] = 1;
                else
                    array_pos_media[i] = 0;
            }

            numero_decimal = 1 * array_pos_media[8] + 2 * array_pos_media[7] + 4 * array_pos_media[6] + 8 * array_pos_media[5] + 16 * array_pos_media[4] + 32 * array_pos_media[3] + 64 * array_pos_media[2] + 128 * array_pos_media[1] + 256 * array_pos_media[0];
            menor_binario = numero_decimal;
            int k = 9, n = 9;
            while (k > 0)
            {
                int temp = array_pos_media[n - 1];
                for (int i = n - 1; i > 0; i--)
                {
                    array_pos_media[i] = array_pos_media[i - 1];
                }
                array_pos_media[0] = temp;
                numero_decimal = 1 * array_pos_media[8] + 2 * array_pos_media[7] + 4 * array_pos_media[6] + 8 * array_pos_media[5] + 16 * array_pos_media[4] + 32 * array_pos_media[3] + 64 * array_pos_media[2] + 128 * array_pos_media[1] + 256 * array_pos_media[0];
                if (numero_decimal < menor_binario)
                    menor_binario = numero_decimal;
                k--;
            }
            array_ilbp[menor_binario] += 1;
        }
    }
    return array_ilbp;
}
int **tratar_arquivo(char name[], int arquivo, int *tamanho) // pra ser possivel a partir dessa funcao acessar o tamanho e a matriz,é necessario declarar tamanho como ponteiro
{
    FILE *fp;
    char caractere, file[100];
    int **matriz_imagem;
    int linha = 0, coluna = 0, valor;

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
    int a = 0;
    while (!feof(fp))
    {
        fscanf(fp, "%d%c", &valor, &caractere);
        matriz_imagem[linha][coluna] = valor;

        if (caractere == '\n')
        {
            a++;
            linha++;
            matriz_imagem = (int **)realloc(matriz_imagem, (linha + 1) * sizeof(int *)); //realocando na proxima linha
            matriz_imagem[linha] = (int *)malloc(sizeof(int));                           //alocando a coluna da proxima linha
            coluna = 0;
        }
        else
        {
            coluna++;
            matriz_imagem[linha] = (int *)realloc(matriz_imagem[linha], (coluna + 1) * sizeof(int)); //alocando a coluna da mesma linha
        }
    }
    *tamanho = linha - 1;
    fclose(fp);

    return matriz_imagem;
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