#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void strsort(char **s, int size)
{
    char *temp;

    int i, j;
    for (i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size - i - 1; j++)
        {
            if (strcmp(*(s + j), *(s + j + 1)) > 0)
            {
                temp = *(s + j);
                *(s + j) = *(s + j + 1);
                *(s + j + 1) = temp;
            }
        }
    }
}

int main()
{
    int i, N;
    scanf("%d", &N);
    getchar();

    char *s[N], t[50];
    for (i = 0; i < N; i++)
    {
        fgets(t, sizeof(t), stdin);
        t[strcspn(t, "\n")] = '\0';

        s[i] = (char *)malloc(strlen(t) + 1);
        strcpy(s[i], t);
    }
    strsort(s, N);
    for (i = 0; i < N; i++)
    {
        puts(s[i]);
        free(s[i]);
    }

    return 0;
}