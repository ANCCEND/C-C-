#include "stdio.h"
#include "stdlib.h"

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_NODES 100

typedef int status;
typedef int KeyType;
typedef struct
{
    KeyType key;
    char others[20];
} TElemType; // 二叉树结点类型定义

typedef struct BiTNode
{ // 二叉链表结点的定义
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

#include <string.h>

void visit(BiTree T)
{
    printf(" %d,%s", T->data.key, T->data.others);
}

BiTree CreateTree(TElemType definition[], int &flag)
{
    int data = definition[flag++].key;
    if (data == 0 || data == -1)
        return NULL;
    else
    {
        BiTree NewNode = (BiTree)malloc(sizeof(BiTNode));
        NewNode->data.key = data;
        strcpy(NewNode->data.others, definition[flag - 1].others);
        NewNode->lchild = CreateTree(definition, flag);
        NewNode->rchild = CreateTree(definition, flag);
        return NewNode;
    }
}

status CreateBiTree(BiTree &T, TElemType definition[])
/*根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    int flag = 0, prelength = 0, currlength = 0;
    while (definition[prelength].key != -1)
        prelength++;
    prelength++;
    TElemType redefine[prelength];
    for (int i = 0; i < prelength; i++)
    {
        int isSame = 0;
        for (int j = 0; j < currlength; j++)
        {
            if (definition[i].key != 0 && redefine[j].key == definition[i].key)
            {
                return INFEASIBLE;
            }
        }
        if (isSame == 0)
        {
            redefine[currlength++] = definition[i];
        }
        else
            continue;
    }
    T = CreateTree(redefine, flag);
    return OK;
}

void ClearTree(BiTree t)
{
    if (t == NULL)
        return;
    ClearTree(t->lchild);
    ClearTree(t->rchild);
    free(t);
}

status ClearBiTree(BiTree &T)
// 将二叉树设置成空，并删除所有结点，释放结点空间
{
    ClearTree(T);
    T = NULL;
    return OK;
}

int BiTreeDepth(BiTree T)
// 求二叉树T的深度
{
    if (T == NULL)
        return 0;
    int ldepth = BiTreeDepth(T->lchild);
    int rdepth = BiTreeDepth(T->rchild);

    return (ldepth > rdepth ? ldepth : rdepth) + 1;
}

BiTNode *LocateNode(BiTree T, KeyType e)
// 查找结点
{
    if (T == NULL)
        return ERROR;

    int top = -1;
    BiTree stack[MAX_NODES];
    stack[++top] = T;
    while (top >= 0)
    {
        BiTree p = stack[top--];
        if (p->data.key == e)
            return p;

        if (p->rchild)
            stack[++top] = p->rchild;
        if (p->rchild)
            stack[++top] = p->lchild;
    }
    return NULL;
}

status Assign(BiTree &T, KeyType e, TElemType value)
// 实现结点赋值。此题允许通过增加其它函数辅助实现本关任务
{
    if (T == NULL)
        return INFEASIBLE;

    BiTree stack[MAX_NODES], temp;
    int top = -1;
    stack[++top] = T;
    int flag = 0;
    int isSame = 0;

    while (top >= 0)
    {
        BiTree p = stack[top--];
        if (p->data.key == value.key)
        {
            isSame = 1;
            temp = p;
        }

        if (p->rchild)
            stack[++top] = p->rchild;
        if (p->lchild)
            stack[++top] = p->lchild;
    }

    stack[++top] = T;

    while (top >= 0)
    {
        BiTree p = stack[top--];

        if (p->data.key == e)
        {
            if (e == value.key)
            {
                p->data = value;
                return OK;
            }
            else
            {
                if (isSame)
                    return INFEASIBLE;
                else
                {
                    p->data = value;
                    return OK;
                }
            }
        }
        if (p->rchild)
            stack[++top] = p->rchild;
        if (p->lchild)
            stack[++top] = p->lchild;
    }
    return ERROR;
}

BiTNode *GetSibling(BiTree T, KeyType e)
// 实现获得兄弟结点
{
    if (T->data.key == e)
        return NULL;

    BiTree stack[MAX_NODES];
    int top = -1;
    stack[++top] = T;

    while (top >= 0)
    {
        BiTree p = stack[top--];

        if (p->rchild)
        {
            if (p->rchild->data.key == e)
                return p->lchild;
            stack[++top] = p->rchild;
        }
        if (p->lchild)
        {
            if (p->lchild->data.key == e)
                return p->rchild;
            stack[++top] = p->lchild;
        }
    }
    return NULL;
}

status InsertNode(BiTree &T, KeyType e, int LR, TElemType c)
// 插入结点。此题允许通过增加其它函数辅助实现本关任务
{
    if (T == NULL)
        return INFEASIBLE;

    if (LR == -1)
    {
        BiTree temp = T;
        T = (BiTree)malloc(sizeof(BiTNode));
        T->data = c;
        T->rchild = temp;
        T->lchild = NULL;
        return OK;
    }

    BiTree stack[MAX_NODES];
    int top = -1;
    stack[++top] = T;

    while (top >= 0)
    {
        BiTree p = stack[top--];
        if (p->data.key == c.key)
            return ERROR;

        if (p->rchild)
            stack[++top] = p->rchild;
        if (p->lchild)
            stack[++top] = p->lchild;
    }

    stack[++top] = T;

    while (top >= 0)
    {
        BiTree p = stack[top--];

        if (p->data.key == e)
        {
            if (LR == 0)
            {
                BiTree temp = p->lchild;
                p->lchild = (BiTree)malloc(sizeof(BiTNode));
                p->lchild->data = c;
                p->lchild->rchild = temp;
                p->lchild->lchild = NULL;
            }
            else
            {
                BiTree temp = p->rchild;
                p->rchild = (BiTree)malloc(sizeof(BiTNode));
                p->rchild->data = c;
                p->rchild->rchild = temp;
                p->rchild->lchild = NULL;
            }
            return OK;
        }
        if (p->rchild)
            stack[++top] = p->rchild;
        if (p->lchild)
            stack[++top] = p->lchild;
    }
    return ERROR;
}

status DeleteNode(BiTree &T, KeyType e)
// 删除结点。此题允许通过增加其它函数辅助实现本关任务
/*如关键字为e的结点度为0，删除即可；
如关键字为e的结点度为1，用关键字为e的结点孩子代替被删除的e位置；
如关键字为e的结点度为2，用e的左子树（简称为LC）代替被删除的e位置，将e的右子树（简称为RC）作为LC中最右节点的右子树。*/
{
    if (T == NULL)
        return INFEASIBLE;

    if (T->data.key == e)
    {
        if (T->lchild == NULL && T->rchild == NULL)
        {
            free(T);
            T = NULL;
            return OK;
        }
        else if (T->lchild == NULL || T->rchild == NULL)
        {
            BiTree temp = T->lchild ? T->lchild : T->rchild;
            free(T);
            T = temp;
            return OK;
        }
        else
        {
            BiTree tagl = T->lchild, tagr = T->rchild; // 存储要删除的结点的左右子树
            free(T);
            T = tagl;
            while (tagl->rchild != NULL)
            {
                tagl = tagl->rchild;
            }
            tagl->rchild = tagr;
            return OK;
        }
    }

    BiTree stack[MAX_NODES];
    int top = -1;
    stack[++top] = T;

    while (top >= 0)
    {
        BiTree p = stack[top--];

        if ((p->lchild && p->lchild->data.key == e) || (p->rchild && p->rchild->data.key == e))
        {
            int isLeft = 0;
            if (p->lchild->data.key == e)
                isLeft = 1;

            BiTree tag; // 存储要删除的结点
            if (isLeft)
                tag = p->lchild;
            else
                tag = p->rchild;
            if (tag->lchild == NULL && tag->rchild == NULL)
            {
                free(tag);
                if (isLeft)
                    p->lchild = NULL;
                else
                    p->rchild = NULL;
                return OK;
            }
            else if (tag->lchild == NULL || tag->rchild == NULL)
            {
                BiTree temp = tag->lchild ? tag->lchild : tag->rchild;
                free(tag);
                if (isLeft)
                    p->lchild = temp;
                else
                    p->rchild = temp;
                return OK;
            }
            else
            {
                BiTree tagl = tag->lchild, tagr = tag->rchild; // 存储要删除的结点的左右子树
                free(tag);
                if (isLeft)
                {
                    p->lchild = tagl;
                    while (tagl->rchild != NULL)
                    {
                        tagl = tagl->rchild;
                    }
                    tagl->rchild = tagr;
                }
                else
                {
                    p->rchild = tagl;
                    while (tagl->rchild != NULL)
                    {
                        tagl = tagl->rchild;
                    }
                    tagl->rchild = tagr;
                }
                return OK;
            }
        }

        if (p->rchild)
            stack[++top] = p->rchild;
        if (p->lchild)
            stack[++top] = p->lchild;
    }
    return ERROR;
}

status PreOrderTraverse(BiTree T, void (*visit)(BiTree))
// 先序遍历二叉树T
{
    if (T == NULL)
        return INFEASIBLE;
    BiTree stack[MAX_NODES];
    int top = -1;
    stack[++top] = T;

    while (top >= 0)
    {
        BiTree p = stack[top--];

        visit(p);

        if (p->rchild)
        {
            stack[++top] = p->rchild;
        }
        if (p->lchild)
        {
            stack[++top] = p->lchild;
        }
    }
    return OK;
}

status InOrderTraverse(BiTree T, void (*visit)(BiTree))
// 中序遍历二叉树T
{
    if (T == NULL)
        return INFEASIBLE;

    BiTree stack[MAX_NODES];
    int top = -1;
    BiTree p = T;

    while (p != NULL || top >= 0)
    {
        while (p != NULL)
        {
            stack[++top] = p;
            p = p->lchild;
        }
        if (top >= 0)
        {
            p = stack[top--];
            visit(p);
            p = p->rchild;
        }
    }
    return OK;
}

status PostOrderTraverse(BiTree T, void (*visit)(BiTree))
// 后序遍历二叉树T
{
    if (T == NULL)
        return INFEASIBLE;

    PostOrderTraverse(T->lchild, visit);
    PostOrderTraverse(T->rchild, visit);
    visit(T);
    return OK;
}

status LevelOrderTraverse(BiTree T, void (*visit)(BiTree))
// 按层遍历二叉树T
{
    BiTree quene[MAX_NODES];
    int front = 0, rear = 0;
    quene[rear++] = T;

    while (front < rear)
    {
        BiTree temp = quene[front++];
        visit(temp);
        if (temp->lchild)
            quene[rear++] = temp->lchild;
        if (temp->rchild)
            quene[rear++] = temp->rchild;
    }
    return OK;
}

void WriteToFile(BiTree T, FILE *fp)
{
    if (T == NULL)
    {
        fprintf(fp, "-1 #\n");
        return;
    }

    fprintf(fp, "%d %s\n", T->data.key, T->data.others);
    WriteToFile(T->lchild, fp);
    WriteToFile(T->rchild, fp);
}

status SaveBiTree(BiTree T, char FileName[])
// 将二叉树的结点数据写入到文件FileName中
{
    if (T == NULL)
        return INFEASIBLE;
    FILE *fp = fopen(FileName, "w");
    if (fp == NULL)
        return ERROR;
    WriteToFile(T, fp);
    fclose(fp);
    return OK;
}

BiTree ReadFromFile(FILE *fp)
{
    char line[MAX_NODES];
    if (fgets(line, sizeof(line), fp) == NULL)
        return NULL;

    if (line[0] == '#')
        return NULL;

    TElemType data;
    sscanf(line, "%d %s", &data.key, data.others);
    if (data.key == -1 && data.others[0] == '#')
        return NULL;

    BiTree node = (BiTree)malloc(sizeof(BiTNode));
    node->data.key = data.key;
    strcpy(node->data.others, data.others);
    node->lchild = ReadFromFile(fp);
    node->rchild = ReadFromFile(fp);
    return node;
}

status LoadBiTree(BiTree &T, char FileName[])
// 读入文件FileName的结点数据，创建二叉树
{
    if (T != NULL)
        return INFEASIBLE;

    FILE *fp = fopen(FileName, "r");
    T = ReadFromFile(fp);
}

status MaxPathSum(BiTree T)
{
    if (T == NULL)
        return 0;

    // 如果是叶子节点，直接返回自己的值
    if (T->lchild == NULL && T->rchild == NULL)
        return T->data.key;

    int leftSum = MaxPathSum(T->lchild);
    int rightSum = MaxPathSum(T->rchild);

    // 只有一边存在时，只能走那一边
    if (T->lchild == NULL)
        return T->data.key + rightSum;
    if (T->rchild == NULL)
        return T->data.key + leftSum;

    // 两边都存在，选较大的一边
    return T->data.key + (leftSum > rightSum ? leftSum : rightSum);
}

BiTree LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2)
{
    if (T == NULL)
        return NULL;

    if (T->data.key == e1 || T->data.key == e2)
        return T;

    BiTree left = LowestCommonAncestor(T->lchild, e1, e2);
    BiTree right = LowestCommonAncestor(T->rchild, e1, e2);

    if (left != NULL && right != NULL)
        return T; // e1 和 e2 分别在左右子树，当前节点是最近公共祖先

    return left != NULL ? left : right;
}

status InvertTree(BiTree T)
{
    if (T == NULL)
        return INFEASIBLE;
    BiTree temp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = temp;

    InvertTree(T->lchild);
    InvertTree(T->rchild);
    return OK;
}