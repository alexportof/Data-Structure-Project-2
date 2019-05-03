// Álex Porto Ferreira 170119815

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void embaralhar_array(int array[], int n);
void troca(int *a, int *b);
int **tratar_arquivo(char name[], int i, int *tamanho);
double *ilbp(int **matriz, int *tamanho);
double *glcm(int **matriz, int *tamanho);
double calcular_contraste(int **direcao);
double calcular_homogeneidade(int **direcao);
double calcular_energia(int **direcao);
double *normalizar_vetor(double *vetor, int tamanho);
double *calcular_media(int **matriz);

int main()
{
    int **matriz_imagem, *tamanho;
    double *vetor_resultado, *media_matriz_resultados, *vetor_resultado_normalizado, *array_ilbp, *vetor_glcm, **matriz_resultados;
    char file[100];
    char *teste[30];
    int array_teste_asfalto[25], array_teste_grama[25], array_treino_asfalto[25], array_treino_grama[25], array_geral_asfalto[50], array_geral_grama[50];
    int a = 0, n, count;

    // ASFALTO
    for (int i = 0; i < 50; i++)
    {
        array_geral_asfalto[i] = i;
    }

    array_geral_asfalto[0] = 50;
    n = sizeof(array_geral_asfalto) / sizeof(array_geral_asfalto[0]);
    embaralhar_array(array_geral_asfalto, n);
    matriz_resultados = (double **)malloc(25 * sizeof(double *));

    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            array_teste_asfalto[j] = array_geral_asfalto[i];
            i++;
            array_treino_asfalto[j] = array_geral_asfalto[i];
            i++;
        }
    }

    for (int i = 0; i < 25; i++)
    {
        matriz_imagem = tratar_arquivo("asphalt", array_treino_asfalto[i], &tamanho);
        // pra calcular ilbp e glcm preciso do tamanho da matriz
        array_ilbp = ilbp(matriz_imagem, &tamanho);
        vetor_glcm = glcm(matriz_imagem, &tamanho);

        vetor_resultado = (double *)malloc(536 * sizeof(double));
        vetor_resultado_normalizado = (double *)malloc(536 * sizeof(double));
        if (vetor_resultado == NULL || vetor_resultado_normalizado == NULL)
            exit(1);
        count = 0;
        while (count < 536)
        {
            if (count < 512)
            {
                vetor_resultado[count] = array_ilbp[count];
                count++;
            }
            else
            {
                vetor_resultado[count] = vetor_glcm[count - 512];
                count++;
            }
        }
        vetor_resultado_normalizado = normalizar_vetor(vetor_resultado, 536);
        matriz_resultados[i] = (double *)malloc(536 * sizeof(double));
        matriz_resultados[i] = vetor_resultado_normalizado;

        free(matriz_imagem);
        free(vetor_glcm);
        free(array_ilbp);
    }
    media_matriz_resultados = calcular_media(matriz_resultados);

    // GRAMA
    for (int i = 0; i < 50; i++)
    {
        array_geral_grama[i] = i;
    }

    array_geral_grama[0] = 50;
    n = sizeof(array_geral_grama) / sizeof(array_geral_grama[0]);
    embaralhar_array(array_geral_grama, n);
    matriz_resultados = (double **)malloc(25 * sizeof(double *));

    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            array_teste_grama[j] = array_geral_grama[i];
            i++;
            array_treino_grama[j] = array_geral_grama[i];
            i++;
        }
    }

    for (int i = 0; i < 25; i++)
    {
        matriz_imagem = tratar_arquivo("grass", array_treino_grama[i], &tamanho);
        // pra calcular ilbp e glcm preciso do tamanho da matriz
        array_ilbp = ilbp(matriz_imagem, &tamanho);
        vetor_glcm = glcm(matriz_imagem, &tamanho);

        vetor_resultado = (double *)malloc(536 * sizeof(double));
        vetor_resultado_normalizado = (double *)malloc(536 * sizeof(double));
        if (vetor_resultado == NULL || vetor_resultado_normalizado == NULL)
            exit(1);
        count = 0;
        while (count < 536)
        {
            if (count < 512)
            {
                vetor_resultado[count] = array_ilbp[count];
                count++;
            }
            else
            {
                vetor_resultado[count] = vetor_glcm[count - 512];
                count++;
            }
        }
        vetor_resultado_normalizado = normalizar_vetor(vetor_resultado, 536);
        matriz_resultados[i] = (double *)malloc(536 * sizeof(double));
        matriz_resultados[i] = vetor_resultado_normalizado;

        free(matriz_imagem);
        free(vetor_glcm);
        free(array_ilbp);
    }
    media_matriz_resultados = calcular_media(matriz_resultados);

    return 0;
}
double *calcular_media(int **matriz)
{
    double *resultado, media;
    resultado = (double *)calloc(536, sizeof(double));
    if (resultado == NULL)
        exit(1);

    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 536; j++)
        {
            media = matriz[i][j] / 25;
            resultado[j] += media;
        }
    }
    return resultado;
}

double *normalizar_vetor(double *vetor, int tamanho)
{
    double *vetor_normalizado;
    vetor_normalizado = (double *)malloc(tamanho * sizeof(double));
    if (vetor_normalizado == NULL)
        exit(1);
    int menor = vetor[0];
    //printf("\n\nVETOR CONCATENADO\n\n");
    for (int i = 1; i < tamanho; i++)
    {
        // printf("%d ", vetor[i]);
        if (vetor[i] < menor)
            menor = vetor[i];
    }
    int maior = vetor[0];
    for (int i = 1; i < tamanho; i++)
    {
        if (vetor[i] > maior)
            maior = vetor[i];
    }
    //printf("\nNORMALIZAR VETOR\n");
    for (int i = 0; i < tamanho; i++)
    {
        vetor_normalizado[i] = (vetor[i] - menor) / (maior - menor);
        //printf("%d  ", vetor_normalizado[i]);
    }
    return vetor_normalizado;
}

double *glcm(int **matriz, int *tamanho)
{
    int **norte, **nordeste, **leste, **sudeste, **sul, **sudoeste, **oeste, **noroeste;
    double *resultado;
    resultado = (double *)calloc(24, sizeof(double));
    norte = (int **)calloc(256, sizeof(int *));
    nordeste = (int **)calloc(256, sizeof(int *));
    sul = (int **)calloc(256, sizeof(int *));
    leste = (int **)calloc(256, sizeof(int *));
    oeste = (int **)calloc(256, sizeof(int *));
    sudoeste = (int **)calloc(256, sizeof(int *));
    sudeste = (int **)calloc(256, sizeof(int *));
    noroeste = (int **)calloc(256, sizeof(int *));
    if (resultado == NULL || norte == NULL || sul == NULL || leste == NULL || oeste == NULL || sudoeste == NULL || sudeste == NULL || noroeste == NULL)
        exit(1);
    for (int i = 0; i < 256; i++)
    {
        norte[i] = (int *)calloc(256, sizeof(int));
        nordeste[i] = (int *)calloc(256, sizeof(int));
        sul[i] = (int *)calloc(256, sizeof(int));
        leste[i] = (int *)calloc(256, sizeof(int));
        oeste[i] = (int *)calloc(256, sizeof(int));
        sudoeste[i] = (int *)calloc(256, sizeof(int));
        sudeste[i] = (int *)calloc(256, sizeof(int));
        noroeste[i] = (int *)calloc(256, sizeof(int));

        if (norte[i] == NULL || sul[i] == NULL || leste[i] == NULL || oeste[i] == NULL || sudoeste[i] == NULL || sudeste[i] == NULL || noroeste[i] == NULL)
        {
            free(norte);
            free(nordeste);
            free(sul);
            free(leste);
            free(oeste);
            free(sudoeste);
            free(sudeste);
            free(noroeste);
            exit(1);
        }
    }
    int loop = *tamanho - 1;
    for (int i = 1; i < loop; i++)
    {
        for (int j = 1; j < loop; j++)
        {
            int ponto_central = matriz[i][j];

            int valor_norte = matriz[i - 1][j];
            norte[ponto_central][valor_norte] += 1;

            int valor_nordeste = matriz[i - 1][j + 1];
            nordeste[ponto_central][valor_nordeste] += 1;

            int valor_leste = matriz[i][j + 1];
            leste[ponto_central][valor_leste] += 1;

            int valor_sudeste = matriz[i + 1][j + 1];
            sudeste[ponto_central][valor_sudeste] += 1;

            int valor_sul = matriz[i + 1][j];
            sul[ponto_central][valor_sul] += 1;

            int valor_sudoeste = matriz[i + 1][j - 1];
            sudoeste[ponto_central][valor_sudoeste] += 1;

            int valor_oeste = matriz[i][j - 1];
            oeste[ponto_central][valor_oeste] += 1;

            int valor_noroeste = matriz[i - 1][j - 1];
            noroeste[ponto_central][valor_noroeste] += 1;
        }
    }

    resultado[1] = calcular_energia(norte);
    resultado[4] = calcular_energia(nordeste);
    resultado[7] = calcular_energia(leste);
    resultado[10] = calcular_energia(sudeste);
    resultado[13] = calcular_energia(sul);
    resultado[16] = calcular_energia(sudoeste);
    resultado[19] = calcular_energia(oeste);
    resultado[22] = calcular_energia(noroeste);

    resultado[0] = calcular_contraste(norte);
    resultado[3] = calcular_contraste(nordeste);
    resultado[6] = calcular_contraste(leste);
    resultado[9] = calcular_contraste(sudeste);
    resultado[12] = calcular_contraste(sul);
    resultado[15] = calcular_contraste(sudoeste);
    resultado[18] = calcular_contraste(oeste);
    resultado[21] = calcular_contraste(noroeste);

    resultado[2] = calcular_homogeneidade(norte);
    resultado[5] = calcular_homogeneidade(nordeste);
    resultado[8] = calcular_homogeneidade(leste);
    resultado[11] = calcular_homogeneidade(sudeste);
    resultado[14] = calcular_homogeneidade(sul);
    resultado[17] = calcular_homogeneidade(sudoeste);
    resultado[20] = calcular_homogeneidade(oeste);
    resultado[23] = calcular_homogeneidade(noroeste);

    for (int i = 0; i < 250; i++)
    {
        free(norte[i]);
        free(sul[i]);
        free(leste[i]);
        free(oeste[i]);
        free(sudoeste[i]);
        free(sudeste[i]);
        free(noroeste[i]);
    }
    free(norte);
    free(sul);
    free(leste);
    free(oeste);
    free(sudoeste);
    free(sudeste);
    free(noroeste);
    return resultado;
}

double *ilbp(int **matriz, int *tamanho)
{
    double media, *array_ilbp;
    int pixels[9], array_pos_media[9], numero_decimal, menor_binario;
    array_ilbp = (double *)calloc(512, sizeof(double));
    if (array_ilbp == NULL)
        exit(1);

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
        exit(1);

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
            if (matriz_imagem == NULL)
                exit(1);
            matriz_imagem[linha] = (int *)malloc(sizeof(int)); //alocando a coluna da proxima linha
            if (matriz_imagem[linha] == NULL)
                exit(1);
            coluna = 0;
        }
        else
        {
            coluna++;
            matriz_imagem[linha] = (int *)realloc(matriz_imagem[linha], (coluna + 1) * sizeof(int)); //alocando a coluna da mesma linha
            if (matriz_imagem[linha] == NULL)
                exit(1);
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
double calcular_contraste(int **matriz)
{
    double soma = 0;
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
            soma += pow(i - j, 2) * matriz[i][j];
    }

    return soma;
}

double calcular_energia(int **matriz)
{
    double soma = 0;
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
            soma += pow(matriz[i][j], 2);
    }

    return soma;
}

double calcular_homogeneidade(int **matriz)
{
    double soma = 0;
    for (int i = 0; i < 256; i++)
    {
        for (int j = 0; j < 256; j++)
            soma += (matriz[i][j]) / (1 + sqrt(pow(i - j, 2)));
    }

    return soma;
}