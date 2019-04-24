#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
int **tratar_arquivo(char name[], int i)
{
    FILE *fp;
    char file[100];
    sprintf(file, "DataSet/%s/%s_%.2d.txt", name, name, i);
    printf("%.2d\t", i);
    printf("abriu\n");
    fp = fopen(file, "r");
    if (fp == NULL)
    {
        printf("Cannot open file. %d\n", i);
        exit(2);
    }
    // fscanf(fp, "%d", matriz[0][0]);

    fclose(fp);
    // return matriz;
}

int main()
{
    int **num;
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
    for (int i = 0; i < 25; i++)
    {
        num = tratar_arquivo("asphalt", array_treino[i]);
    }

    return 0;
}