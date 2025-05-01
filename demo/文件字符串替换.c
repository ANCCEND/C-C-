#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//命令行：.\xxxx 要打开的文件路径 被替换的字符 替换后字符

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("input wrong");
        return 1;
    }
    FILE *filetext = fopen(argv[1], "r");
    FILE *out = fopen("out.txt", "w");
    char line[1024];
    while (fgets(line, sizeof(line), filetext))
    {
        char *p = line, *q = p;

        while ((p = strstr(q, argv[2])) != NULL)
        {
            fwrite(q, 1, p - q, out);
            fwrite(argv[3], 1, strlen(argv[3]), out);
            q = p + strlen(argv[2]);
        }
        if(*q!='\0') fwrite(q, 1, strlen(q), out);
    }

    fclose(out);
    fclose(filetext);
    out = fopen("out.txt", "r");
    while (fgets(line, sizeof(line), out))
    {
        fputs(line, stdout);
    }
    fclose(out);

    return 0;
}