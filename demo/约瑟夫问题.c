#include <stdio.h>

int main(void)
{
    int M, N;
    scanf("%d%d", &M, &N);
    int a[M];
    int i, j, k;
    for (i = 0; i < M; i++)
        a[i] = i + 1;

    for (i = M, j = 0; i > 1; i--)
    {
        for (k = 1; k <= N; k++)
        {
            j++;
            if (j > M)
                j = 1;
            while (a[j - 1] == 0)
            {
                j++;
                if (j > M)
                    j = 1;
            }
        }
        a[j - 1] = 0;
    }

    for (i = 0; i < M; i++)
    {
        if (a[i] != 0)
        {
            printf("%d\n", a[i]);
            break;
        }
    }

    return 0;
}