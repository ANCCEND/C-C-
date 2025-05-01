/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1

typedef int status;
typedef int ElemType; // 数据元素类型定义

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef struct
{ // 顺序表（顺序结构）的定义
    ElemType *elem = NULL;
    int length;
    int listsize;
} SqList;

typedef struct
{ // 线性表的集合类型定义
    struct
    {
        char name[30];
        SqList L;
    } elem[10];
    int length;
} LISTS;

using namespace std;

status InitList(SqList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{

    if (L.elem == NULL)
    {
        L.elem = (ElemType *)malloc(sizeof(int) * LIST_INIT_SIZE);
        L.length = 0;
        L.listsize = LIST_INIT_SIZE;
        return OK;
    }
    else
        return INFEASIBLE;
}

status DestroyList(SqList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{

    if (L.elem)
    {
        free(L.elem);
        L.elem = NULL;
        L.length = L.listsize = 0;
        return OK;
    }
    else
        return INFEASIBLE;
}

status ClearList(SqList &L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{

    if (L.elem)
    {
        L.length = 0;
        return OK;
    }
    else
        return INFEASIBLE;
}

status ListEmpty(SqList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{

    if (L.elem)
    {
        if (L.length)
            return FALSE;
        else
            return TRUE;
    }
    else
        return INFEASIBLE;
}

status ListLength(SqList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{

    if (L.elem)
    {
        return L.length;
    }
    else
        return INFEASIBLE;
}

status GetElem(SqList L, int i, ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{

    if (L.elem)
    {
        if (i <= L.length && i > 0)
        {
            e = L.elem[i - 1];
            return OK;
        }
        else
            return ERROR;
    }
    else
        return INFEASIBLE;
}

int LocateElem(SqList L, ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号并返回该序号；如果e不存在，返回0；当线性表L不存在时，返回INFEASIBLE（即-1）。
{

    if (L.elem)
    {
        for (int i = 0; i < L.length; i++)
        {
            if (L.elem[i] == e)
                return i + 1;
        }
        return 0;
    }
    else
        return INFEASIBLE;
}

status PriorElem(SqList L, ElemType e, ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{

    if (L.elem)
    {
        for (int i = 0; i < L.length; i++)
        {
            if (L.elem[i] == e && i)
            {
                pre = L.elem[i - 1];
                return OK;
            }
        }
        return ERROR;
    }
    else
        return INFEASIBLE;
}

status NextElem(SqList L, ElemType e, ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{

    if (L.elem)
    {
        for (int i = 0; i < L.length; i++)
        {
            if (L.elem[i] == e && i != L.length - 1)
            {
                next = L.elem[i + 1];
                return OK;
            }
        }
        return ERROR;
    }
    else
        return INFEASIBLE;
}

status ListInsert(SqList &L, int i, ElemType e)

{

    if (L.elem)
    {

        if (i > 0 && i <= L.length + 1)
        {
            if (L.length == L.listsize)
            {
                L.elem = (ElemType *)realloc(L.elem, sizeof(ElemType) * (L.length + 1));
                L.listsize++;
            }
            for (int j = L.length - 1; j >= i - 1 && j >= 0; j--)
            {
                L.elem[j + 1] = L.elem[j];
            }
            L.elem[i - 1] = e;
            L.length++;
            return OK;
        }
        else
            return ERROR;
    }
    else
        return INFEASIBLE;
}

status ListDelete(SqList &L, int i, ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{

    if (L.elem)
    {
        if (i > 0 && i <= L.length)
        {
            e = L.elem[i - 1];
            for (int j = i - 1; j < L.length - 1; j++)
            {
                L.elem[j] = L.elem[j + 1];
            }
            L.length--;
            return OK;
        }
        else
            return ERROR;
    }
    else
        return INFEASIBLE;
}

status ListTraverse(SqList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{

    if (L.elem)
    {
        cout<<"表内容：";
        for (int i = 0; i < L.length; i++)
        {
            if (i == L.length - 1)
                printf("%d", L.elem[i]);
            else
                printf("%d ", L.elem[i]);
        }
        return OK;
    }
    else
        return INFEASIBLE;
}

status MaxSubArray(SqList L)
{
    // Kadane查找最大连续子数组和
    if (L.elem)
    {
        int currentSum = L.elem[0];
        int maxSum = L.elem[0];
        int length = L.length;

        for (int i = 1; i < length; i++)
        {
            currentSum = L.elem[i] > (L.elem[i] + currentSum) ? L.elem[i] : (L.elem[i] + currentSum);
            maxSum = maxSum > currentSum ? maxSum : currentSum;
        }
        printf("最大连续子数组和为：%d\n", maxSum);
        return maxSum;
    }
    else
    {
        printf("数组不存在！\n");
        return INFEASIBLE;
    }
}

status SubArrayNum(SqList L, int k)
{
    // 查找和为k的子数组
    if (L.elem)
    {
        int num = 0, sum;
        for (int i = 0; i < L.length; i++)
        {
            sum = 0;
            for (int j = i; j < L.length; j++)
            {
                sum += L.elem[j];
                if (sum == k)
                {
                    num++;
                    break;
                }
            }
        }
        return num;
    }
    else
        return INFEASIBLE;
}

int compare(const void *A, const void *B)
{
    int a = *(int *)A, b = *(int *)B;
    return a - b;
}

status sortList(SqList L)
{
    // 如果线性表L存在，将L排序，返回OK，否则返回INFEASIBLE
    if (L.elem)
    {
        qsort(L.elem, L.length, sizeof(int), compare);
        return OK;
    }
    else
        return INFEASIBLE;
}

status SaveList(SqList L, char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    if (L.elem)
    {
        FILE *fp = fopen(FileName, "wb");
        if (fp == NULL)
        {
            printf("文件打开失败\n ");
            return INFEASIBLE;
        }

        fwrite(L.elem, sizeof(ElemType), L.length, fp);
        fclose(fp);
        return OK;
    }
    else
        return INFEASIBLE;
}

status LoadList(SqList &L, char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{

    if (L.elem == NULL)
    {
        FILE *fp = fopen(FileName, "rb");
        if (fp == NULL)
        {
            printf("文件打开失败\n ");
            return INFEASIBLE;
        }
        L.elem = (ElemType *)malloc(sizeof(ElemType) * LIST_INIT_SIZE);
        L.listsize = LIST_INIT_SIZE;

        while (fread(&L.elem[L.length], sizeof(ElemType), 1, fp))
        {
            L.length++;
        }
        fclose(fp);
        return OK;
    }
    else
        return INFEASIBLE;
}

status CreateList(LISTS &Lists, char ListName[])
{
    // 在Lists中增加一个名称为ListName的空线性表
    if (Lists.length <= 10)
    {
        strncpy(Lists.elem[Lists.length].name, ListName, sizeof(Lists.elem[Lists.length].name));
        Lists.length++;
        Lists.elem[Lists.length - 1].L.elem = NULL;
        Lists.elem[Lists.length - 1].L.length = 0;
        Lists.elem[Lists.length - 1].L.listsize = 0;
        InitList(Lists.elem[Lists.length - 1].L);
        return OK;
    }
    else
        return INFEASIBLE;
}

status AddList(LISTS &Lists, char ListName[], SqList &L)
// 在Lists中增加一个名称为ListName的线性表L
{

    if (L.elem == NULL)
        return ERROR;
    if (Lists.length <= 10)
    {
        int length = Lists.length;
        for (int i = 0; i < length; i++)
        {
            if (strcmp(ListName, Lists.elem[i].name) == 0)
                return -3;
        }

        strncpy(Lists.elem[Lists.length].name, ListName, sizeof(Lists.elem[Lists.length].name));
        Lists.length++;
        Lists.elem[Lists.length - 1].L = L;

        return OK;
    }
    else
        return INFEASIBLE;
}

status RemoveList(LISTS &Lists, char ListName[])
// Lists中删除一个名称为ListName的线性表
{

    for (int i = 0; i < Lists.length; i++)
    {
        if (strcmp(Lists.elem[i].name, ListName) == 0)
        {
            DestroyList(Lists.elem[i].L);
            for (int j = i; j < Lists.length - 1; j++)
            {
                Lists.elem[j] = Lists.elem[j + 1];
            }
            Lists.length--;
            return OK;
        }
    }
    return ERROR;
}

int LocateList(LISTS Lists, char ListName[], SqList &L)
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{

    for (int i = 0; i < Lists.length; i++)
    {
        if (strcmp(Lists.elem[i].name, ListName) == 0)
        {
            L = Lists.elem[i].L;
            return i + 1;
        }
    }
    return ERROR;
}
