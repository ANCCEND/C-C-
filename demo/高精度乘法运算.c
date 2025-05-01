#include <stdio.h>
#include <string.h>
#define MAX 200

void str_to_arr(char *a, int *len_a);
void Multiply(const char a[MAX], const char b[MAX], char result[2 * MAX + 2], int len_a, int len_b);
void Carry(char *rs);
void PrintResult(char *rs);

int main(void)
{
    char a[MAX] = {0}, b[MAX] = {0}, result[2 * MAX + 2] = {0};
    int len_a, len_b;
    scanf("%s %s", a, b);
    str_to_arr(a, &len_a);
    str_to_arr(b, &len_b);
    Multiply(a, b, result, len_a, len_b);
    PrintResult(result);

    return 0;
}

void str_to_arr(char *a, int *len_a)
{
    *len_a = strlen(a);
    char temp;
    for (int i = 0; i < *len_a / 2; i++)
    {
        temp = a[*len_a - i - 1] - '0';
        a[*len_a - i - 1] = a[i] - '0';
        a[i] = temp;
    }
    if (*len_a % 2)
        a[*len_a / 2] -= '0';
}

void Multiply(const char a[MAX], const char b[MAX], char result[2 * MAX + 2], int len_a, int len_b)
{
    for (int i = 0; i < len_b; i++)
    {
        for (int j = 0; j < len_a; j++)
        {
            result[j + i] += b[i] * a[j];
        }
        Carry(result);
    }
}

void Carry(char *rs)
{
    int temp;
    for (int i = 0; i < 2 * MAX + 1; i++)
    {
        if (rs[i] >= 10)
        {
            temp = rs[i] / 10;
            rs[i] %= 10;
            rs[i + 1] += temp;
        }
    }
}

void PrintResult(char *rs)
{
    int i;
    for (i = 2 * MAX + 1; i >= 0; i--)
    {
        if (rs[i] != 0)
            break;
    }
    while (i >= 0)
    {
        printf("%c", rs[i--] + '0');
    }
}