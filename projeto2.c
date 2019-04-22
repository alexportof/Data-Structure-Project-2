#include <stdio.h>
#include <string.h>

int main() {
int num;
char *teste[30];
char file[100];
FILE *fp;

for(int i = 1;i<10;i++){
    num = i;
    sprintf( file, "DataSet/asphalt/asphalt_0%d.txt", num);
    
    fp = fopen(file, "r");
    if(fp==NULL) {
    printf("Cannot open file.\n");
    exit(2);
    }
    fscanf(fp, "%d", &num);
    printf("%d\n", num);
    fclose(fp);
}
// for(int i = 10;i < 51;i++){
//     num = i;
//     sprintf( file, "asphalt_%d.txt", num);
//     printf("%s\n",file);
// }


    return 0;
}