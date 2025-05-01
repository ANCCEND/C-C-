#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int Rmstr(char str[], char substr[]);

int main(void)
{
    char str[100], substr[100];
    int t;
    gets(str);
    gets(substr);
    t = Rmstr(str, substr);
    printf("%s\n%d", str, t);

    return 0;
}

int Rmstr(char str[], char substr[])
{
    char *p, *t = str;
    int len = strlen(substr);
    if (!strstr(str, substr))
    {
        return 0;
    }
    else
    {
        while (p = strstr(t, substr))
        {
            t = p;
            for (; *(p + len - 1) != '\0'; p++)
            {
                *p = *(p + len);
            }
            *p = '\0';
        }
        return 1;
    }
}