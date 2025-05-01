#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node
{
    char ch;
    struct node *next;
} Node;

int num, control; // num计数总数，control用来控制他那个sb输出条件

void createNode(Node *head);
void printNode(Node *head);
void insertNode(Node *head, char m);
void scanNode(Node *, char);
void deleteNode(Node *q, Node *p);

int main(void)
{
    Node head;
    createNode(&head);
    printNode(&head);
    printNode(&head);
    char m;
    scanf("%c", &m);
    scanNode(&head, m);
    printNode(&head);

    return 0;
}

void createNode(Node *head)
{
    char ch = getchar();
    Node *p;
    if (ch != '\n')
    {
        Node *node = (Node *)malloc(sizeof(Node));
        head->next = node;
        node->ch = ch;
        node->next = NULL;
        num++;
        p = node;
    }
    while ((ch = getchar()) != '\n')
    {
        Node *node = (Node *)malloc(sizeof(Node));
        p->next = node;
        node->ch = ch;
        node->next = NULL;
        p = node;
        num++;
    }
    control = 1;
}

void printNode(Node *head)
{
    Node *p = head->next;
    if (control)
    {
        for (int i = 0; i < num; i++)
        {
            printf("%c ", p->ch);
            p = p->next;
        }
        printf("\n");
    }
    else
    {
        for (int i = 0; i < num; i++)
        {
            printf("%c", p->ch);
            p = p->next;
        }
        printf("\n");
    }
    control = 0;
}

void scanNode(Node *head, char m)
{
    Node *p = head->next, *q = head, *differece;
    int mark = 0, diff = 100, a; // mark判断有没有找到字符，diff记录字符差值
    for (int i = 0; i < num; i++)
    {
        if (p->ch == m)
        {
            mark = 1;
            deleteNode(q, p);
            p = q;
        }
        if (p->ch - m < 0) // 找差值最小的节点
            a = m - p->ch;
        else
            a = p->ch - m;
        if (a < diff)
        {
            diff = a;
            differece = p;
        }

        q = p;
        p = p->next;
    }
    if (mark == 0)
    {
        insertNode(differece, m);
    }
}

void deleteNode(Node *q, Node *p)
{
    q->next = p->next;
    free(p);
    num--;
}

void insertNode(Node *p, char m)
{
    Node *newnode = (Node *)malloc(sizeof(Node));
    Node *temp;
    temp = p->next;
    p->next = newnode;
    newnode->next = temp;
    newnode->ch = m;
    num++;
}