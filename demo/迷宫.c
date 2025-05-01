#include <stdio.h>

int m, n;
int num[50][50];
int num2[50][50];
int count;

int isSafe(int, int);
void walk(int, int);
void printSolution(void);

int main(void)
{
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &num[i][j]);
            num2[i][j] = 0;
        }
    }
    walk(0, 0);

    return 0;
}

int isSafe(int x, int y)
{
    return (x >= 0 && x < m && y >= 0 && y < n && num[x][y] && num2[x][y] == 0);
}

void walk(int x, int y)
{
    if (x + 1 == m && y + 1 == n)
    {
        num2[x][y] = 1;
        printSolution();
        num2[x][y] = 0;
        return;
    }
    num2[x][y] = 1;
    if (isSafe(x - 1, y))
    {
        walk(x - 1, y);
    }
    if (isSafe(x, y + 1))
    {
        walk(x, y + 1);
    }
    if (isSafe(x + 1, y))
    {
        walk(x + 1, y);
    }
    if (isSafe(x, y - 1))
    {
        walk(x, y - 1);
    }
    num2[x][y] = 0;
}

void printSolution(void)
{
    printf("%d\n", ++count);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j == n - 1)
            {
                printf("%d\n", num2[i][j]);
            }
            else
                printf("%d  ", num2[i][j]);
        }
    }
}