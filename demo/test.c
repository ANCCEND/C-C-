#include <stdio.h>

int main(void)
{
    int n, m;
    FILE *file=fopen("matrix1.in","rb");
    fread(&n,sizeof(int),1,file);
    fread(&m,sizeof(int),1,file);
    int num[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            fscanf(file,"%d",&num[i][j]);
        }
    }
    for (int j = m - 1; j >= 0; j--)
    {
        for (int i = 0; i < n; i++)
        {
            if (i == n - 1)
                printf("%d\n", num[i][j]);
            else
                printf("%d ", num[i][j]);
        }
    }
    fclose(file);

    return 0;
}