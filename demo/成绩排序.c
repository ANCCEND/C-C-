#include <stdio.h>
#include <string.h>

typedef struct
{
    char name[40];
    int score;
} Student;

void input(int *n, Student stdscore[]);
void sort(int n, Student stdscore[]);
void output(Student stdscore[], int);
void quickSort(Student stdscore[], int l, int r);
void quickSort_n(Student stdscore[], int l, int r);
void seek(int l, int r, int score, Student stdscore[]);

int main(void)
{
    int ctl, n, score;
    Student stdscore[100];
    printf("输入:\n");
    printf("0 :退出\n");
    printf("1 :输入学生人数n后输入学生姓名和分数，中间用空格隔开");
    printf("2 :排序");
    printf("3 :输出名单");
    printf("4 :按分数查找(请先排序)");

    while (scanf("%d", &ctl) == 1)
    {
        switch (ctl)
        {
        case 0:
            return 0;
        case 1:
            input(&n, stdscore);
            break;
        case 2:
            sort(n, stdscore);
            break;
        case 3:
            output(stdscore, n);
            break;
        case 4:
            scanf("%d", &score);
            seek(0, n - 1, score, stdscore);
            break;
        }
    }
    return 0;
}

void input(int *n, Student stdscore[])
{
    scanf("%d", n);
    for (int i = 0; *n > 0 && i < *n; i++)
    {
        scanf("%s %d", stdscore[i].name, &stdscore[i].score);
    }
}

void sort(int n, Student stdscore[])
{
    if (n > 1)
    {
        quickSort(stdscore, 0, n - 1);
        for (int i = 0; i < n - 1; i++)
        {
            if (stdscore[i].score == stdscore[i + 1].score)
            {
                int j;
                for (j = i; stdscore[i].score == stdscore[j].score; j++)
                    ;
                j -= 1;
                quickSort_n(stdscore, i, j);
            }
        }
    }
}

void output(Student stdscore[], int n)
{
    if (n > 0)
    {
        for (int i = 0; i < n; i++)
        {
            printf("%s %d\n", stdscore[i].name, stdscore[i].score);
        }
    }
}

void seek(int l, int r, int score, Student stdscore[])
{
    if (l < r)
    {
        int i, mid;
        mid = (l + r) / 2;
        if (stdscore[mid].score > score)
        {
            if (mid==l) mid=r;
            seek(mid, r, score, stdscore);
        }
        else if (stdscore[mid].score == score)
        {
            for (i = mid; i >= 0 && stdscore[i].score == score; i--)
                ;
            i += 1;
            while (i <= r && stdscore[i].score == score)
            {
                printf("%s %d\n", stdscore[i].name, stdscore[i].score);
                i++;
            }
        }
        else if (stdscore[mid].score < score)
            seek(l, mid, score, stdscore);
    }
    else if (l == r)
    {
        if(stdscore[l].score == score)
            printf("%s %d\n", stdscore[l].name, stdscore[l].score);
        else printf("not found\n");
    }
    else
        printf("not found\n");
}

void quickSort(Student stdscore[], int l, int r)
{
    if (l < r)
    {
        int i, j, M;
        Student temp;
        M = stdscore[r].score;
        i = l;
        for (j = l; j <= r; j++)
        {
            if (stdscore[j].score > M)
            {
                temp = stdscore[i];
                stdscore[i] = stdscore[j];
                stdscore[j] = temp;
                i++;
            }
        }
        temp = stdscore[i];
        stdscore[i] = stdscore[r];
        stdscore[r] = temp;

        quickSort(stdscore, 0, i - 1);
        if (i + 1 < r)
        {
            quickSort(stdscore, i + 1, r);
        }
    }
}

void quickSort_n(Student stdscore[], int l, int r)
{
    if (l < r)
    {
        Student exc;
        int x, i = l;

        for (x = l; x <= r; x++)
        {
            if (strcmp(stdscore[x].name, stdscore[l].name) < 0)
            {
                exc = stdscore[x];
                stdscore[x] = stdscore[i];
                stdscore[i] = exc;
                i++;
            }
        }
        if (i - l > 0)
        {
            exc = stdscore[i - 1];
            stdscore[i - 1] = stdscore[l];
            stdscore[l] = exc;
            quickSort_n(stdscore, l, i - 1);
            quickSort_n(stdscore, i, r);
        }
    }
}