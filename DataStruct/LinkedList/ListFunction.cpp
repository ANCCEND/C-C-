#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <string>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; // 数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef int ElemType;
typedef struct LNode
{ // 单链表（链式结构）结点的定义
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

typedef struct
{
    struct
    {
        char ListName[30];
        LinkList L;
    } elem[10];
    int length = 0;
} LISTS;

using namespace std;

status InitList(LinkList &L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L == NULL)
    {
        L = (LinkList)malloc(sizeof(LNode));
        L->next = NULL;
        return OK;
    }
    else
        return INFEASIBLE;

    /********** End **********/
}

status DestroyList(LinkList &L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L != NULL)
    {
        DestroyList(L->next);
        free(L);
        L = NULL;
        return OK;
    }
    else
        return INFEASIBLE;

    /********** End **********/
}

status ClearList(LinkList &L)
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L != NULL)
    {
        LNode *stack[LIST_INIT_SIZE];
        LinkList M = L;
        int i = -1;
        while (M->next != NULL)
        {
            stack[++i] = M->next;
            M = M->next;
        }
        while (i != -1)
        {
            free(stack[i--]);
        }
        L->next = NULL;
        return OK;
    }
    else
        return INFEASIBLE;

    /********** End **********/
}

status ListEmpty(LinkList L)
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L != NULL)
    {
        if (L->next == NULL)
            return TRUE;
        else
            return FALSE;
    }
    else
        return INFEASIBLE;

    /********** End **********/
}

int ListLength(LinkList L)
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L != NULL)
    {
        LinkList M = L;
        int i = 0;
        while (M->next != NULL)
        {
            i++;
            M = M->next;
        }
        return i;
    }
    else
        return INFEASIBLE;

    /********** End **********/
}

status GetElem(LinkList L, int i, ElemType &e)
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L != NULL)
    {
        if (i <= 0)
            return ERROR;
        LinkList M = L;
        while (M->next != NULL)
        {
            if (i)
            {
                i--;
                M = M->next;
                //                printf("%d",i);
            }
            else
            {
                e = M->data;
                return OK;
            }
        }
        return ERROR;
    }
    else
        return INFEASIBLE;

    /********** End **********/
}

status LocateElem(LinkList L, ElemType e)
// 如果线性表L存在，查找元素e在线性表L中的位置序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L != NULL)
    {
        LinkList M = L;
        int i = 1; // 记录序号
        while (M->next != NULL)
        {
            if (M->next->data != e)
            {
                i++;
                M = M->next;
            }
            else
                return i;
        }
        return ERROR;
    }
    else
        return INFEASIBLE;

    /********** End **********/
}

status PriorElem(LinkList L, ElemType e, ElemType &pre)
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L != NULL)
    {
        LinkList M = L->next;
        if (M == NULL || M->data == e)
            return ERROR;
        while (M->next != NULL)
        {
            if (M->next->data == e)
            {
                pre = M->data;
                return OK;
            }
            M = M->next;
        }
        return ERROR;
    }
    else
        return INFEASIBLE;

    /********** End **********/
}

status NextElem(LinkList L, ElemType e, ElemType &next)
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L == NULL)
        return INFEASIBLE;
    else
    {
        LinkList M = L->next;
        if (M == NULL)
            return ERROR;
        while (M->next != NULL)
        {
            if (M->data == e)
            {
                next = M->next->data;
                return OK;
            }
            M = M->next;
        }
        return ERROR;
    }

    /********** End **********/
}

status ListInsert(LinkList &L, int i, ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L == NULL)
        return INFEASIBLE;
    else
    {
        LinkList M = L;
        while (i > 1 && M->next != NULL)
        {
            M = M->next;
            i--;
        }
        if (i == 1)
        {
            LinkList temp = (LinkList)malloc(sizeof(LNode));
            temp->data = e;
            temp->next = M->next;
            M->next = temp;
            return OK;
        }
        else
            return ERROR;
    }

    /********** End **********/
}

status ListDelete(LinkList &L, int i, ElemType &e)
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L == NULL)
        return INFEASIBLE;
    else
    {
        LinkList M = L;
        if (M->next == NULL)
            return ERROR;
        while (i > 1 && M->next != NULL)
        {
            M = M->next;
            i--;
        }
        if (i == 1 && M->next != NULL)
        {
            LinkList temp = M->next;
            e = temp->data;
            M->next = temp->next;
            free(temp);
            return OK;
        }
        else
            return ERROR;
    }

    /********** End **********/
}

status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if (L == NULL)
        return INFEASIBLE;
    else
    {
        LinkList M = L->next;
        cout << "表内容：";
        while (M != NULL)
        {
            printf("%d ", M->data);
            M = M->next;
        }
        return OK;
    }

    /********** End **********/
}

status reverseList(LinkList L)
{
    // 翻转链表
    if (L == NULL)
        return INFEASIBLE;
    else
    {
        LinkList prev = NULL, curr = L->next, temp = NULL;
        while (curr != NULL)
        {
            temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }
        L->next = prev;
        return OK;
    }
}

status RemoveNthFromEnd(LinkList L, int n)
{
    // 删除链表中倒数第n个元素,表不存在返回INFEASIBLE，元素数量不足n返回ERROR，删除成功返回OK
    if (L == NULL)
        return INFEASIBLE;
    else
    {
        LinkList slow = L->next, fast = L->next;
        for (int i = 0; i < n; i++)
        {
            fast = fast->next;
            if (fast == NULL)
                return ERROR;
        }
        while (fast->next != NULL)
        {
            fast = fast->next;
            slow = slow->next;
        }
        LinkList temp = slow->next;
        slow->next = temp->next;
        free(temp);
        return OK;
    }
}

LNode *merge(LNode *left, LNode *right)
{
    LNode dummy, *p = &dummy;
    dummy.next = NULL;
    while (left != NULL && right != NULL)
    {
        if (left->data < right->data)
        {
            p->next = left;
            left = left->next;
        }
        else
        {
            p->next = right;
            right = right->next;
        }
        p = p->next;
    }
    p->next = (left != NULL) ? left : right;
    return dummy.next;
}

LNode *split(LNode *head)
{
    LNode *fast = head->next, *slow = head;
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    LNode *mid = slow->next;
    slow->next = NULL;
    return mid;
}

LNode *mergeSort(LNode *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    LNode *mid = split(head);
    LNode *left = mergeSort(head);
    LNode *right = mergeSort(mid);
    return merge(left, right);
}

status sortList(LinkList L)
{
    if (L == NULL)
        return INFEASIBLE;
    else
    {
        LinkList head = L->next;
        L->next = mergeSort(head);
        return OK;
    }
}

status SaveList(LinkList L, char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    if (L == NULL)
        return INFEASIBLE;
    else
    {
        FILE *fp = fopen(FileName, "wb");
        if (fp == NULL)
            return ERROR;
        LinkList M = L->next;
        while (M != NULL)
        {
            fwrite(&M->data, sizeof(M->data), 1, fp);
            M = M->next;
        }
        fclose(fp);
        return OK;
    }

    /********** End 1 **********/
}

status LoadList(LinkList &L, char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    if (L != NULL)
        return INFEASIBLE;
    else
    {
        FILE *fp = fopen(FileName, "rb");
        if (fp == NULL)

            return ERROR;

        L = (LinkList)malloc(sizeof(LNode));
        LinkList M = L;
        int i;
        while (fread(&i, sizeof(i), 1, fp))
        {
            M->next = (LinkList)malloc(sizeof(LNode));
            M = M->next;
            M->data = i;
            M->next = NULL;
        }
        fclose(fp);
        return OK;
    }

    /********** End 2 **********/
}

status AddList(LISTS &Lists, char ListName[], LinkList L)
{
    if (L == NULL)
        return INFEASIBLE;
    else
    {
        if (Lists.length == 10)
            return ERROR;

        int length = Lists.length;
        for (int i = 0; i < length; i++)
        {
            if (strcmp(Lists.elem[i].ListName, ListName) == 0)
            {
                return -3;
            }
        }

        LinkList temp = (LinkList)malloc(sizeof(LNode));
        Lists.elem[length].L = temp;
        while (L != NULL)
        {
            temp->next = L->next;
            temp = temp->next;
            L = L->next;
        }

        strcpy(Lists.elem[length].ListName, ListName);
        Lists.length++;
        return OK;
    }
}

status RemoveList(LISTS &Lists, char ListName[])
{
    if (Lists.length == 0)
        return INFEASIBLE;
    else
    {
        int length = Lists.length;
        for (int i = 0; i < length; i++)
        {
            if (strcmp(ListName, Lists.elem[i].ListName) == 0)
            {
                LinkList temp = Lists.elem[i].L;

                DestroyList(temp);
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
}

status LocateList(LISTS &Lists, char ListName[], LinkList &L)
{
    if (Lists.length == 0)
        return INFEASIBLE;
    else
    {
        int length = Lists.length;
        for (int i = 0; i < length; i++)
        {
            if (strcmp(ListName, Lists.elem[i].ListName) == 0)
            {
                L = Lists.elem[i].L;
                return i + 1;
            }
        }
        return ERROR;
    }
}

void DestroyAll(LISTS &Lists, LinkList &L)
{
    int length = Lists.length;
    int flag = 0;
    for (int i = 0; i < length; i++)
    {
        if (Lists.elem[i].L == L)
            flag = 1;
        DestroyList(Lists.elem[i].L);
    }
    if (flag)
        DestroyList(L);
}