#include <stdio.h>
#include <string.h>

int main()
{
    int num;
    char *teste[30];
    int matriz[1000][1000];
    char file[100];
    int a = 0, j = 0;
    FILE *fp;

    for (int i = 1; i < 10; i++)
    {
        sprintf(file, "DataSet/asphalt/asphalt_0%d.txt", i);

        fp = fopen(file, "r");
        if (fp == NULL)
        {
            printf("Cannot open file.\n");
            exit(2);
        }
        fscanf(fp, "%d;%d", &matriz[0][0], &matriz[0][1]);

        printf("%d\n", matriz[0][0]);
        // while (!feof(fp)){
        //     while(!feof(fp)){
        //     fscanf(fp, "%d", &matriz[a][j]);
        //     printf("%d\n", matriz[a][j]);
        //     j++;
        //     }
        //     a++;
        // }
        fclose(fp);
    }
    // for(int i = 10;i < 51;i++){
    //     num = i;
    //     sprintf( file, "asphalt_%d.txt", num);
    //     printf("%s\n",file);
    // }

    return 0;
}