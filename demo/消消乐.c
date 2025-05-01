#include <stdio.h>

void removesame(int m, int n, int num[][n]);

int main(void)
{
    int m, n;
    scanf("%d%d", &m, &n);
    int num[m][n];
    for (int i = 0; i < n * m; i++)
    {
        scanf("%d", *num + i);
    }
    removesame(m, n, num);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j == n - 1)
                printf("%d\n", num[i][j]);
            else
                printf("%d ", num[i][j]);
        }
    }

    return 0;
}

void removesame(int m, int n, int num[][n])
{
    int i, j;
    int num2[m][n];
    memset(num2, 0, sizeof(num2));

    if (m >= 3 && n < 3)
    {
        for (i = 0; i < n; i++)
        {
            for (j = 1; j < m - 1; j++)
            {
                if (num[j][i] == num[j - 1][i] && num[j + 1][i])
                {
                    num2[j][i] = 1;
                }
            }
        }
    }
    else if (m < 3 && n >= 3)
    {
        for (i = 0; i < m; i++)
        {
            for (j = 1; j < n - 1; j++)
            {
                if (num[i][j] == num[i][j + 1] && num[i][j] == num[i][j - 1])
                {
                    num2[i][j] = 1;
                }
            }
        }
    }
    else if (m >= 3 && n >= 3)
    {
        for (i = 0; i < m; i++)
        {
            for (j = 1; j < n - 1; j++)
            {
                if (num[i][j] == num[i][j + 1] && num[i][j] == num[i][j - 1])
                    num2[i][j] = 1;
            }
        }
        for (j = 0; j < n; j++)
        {
            for (i = 1; i < m - 1; i++)
            {
                if (num[i][j] == num[i + 1][j] && num[i][j] == num[i - 1][j])
                {
                    if (num2[i][j] == 1)
                        num2[i][j] = 3;
                    else
                        num2[i][j] = 2;
                }
            }
        }
    }

    else
        return;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (num2[i][j] == 0)
                continue;
            else if (num2[i][j] == 3)
            {
                num[i][j] = 0;
                num[i][j + 1] = 0;
                num[i][j - 1] = 0;
                num[i][j] = 0;
                num[i + 1][j] = 0;
                num[i - 1][j] = 0;
            }
            else if (num2[i][j] == 1)
            {
                num[i][j] = 0;
                num[i][j + 1] = 0;
                num[i][j - 1] = 0;
            }
            else if (num2[i][j] == 2)
            {
                num[i][j] = 0;
                num[i + 1][j] = 0;
                num[i - 1][j] = 0;
            }
        }
    }
}