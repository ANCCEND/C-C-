#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node
{
    long data;
    struct node *next;
} NODE;

void calculate(NODE **head);
void push(NODE **head, long value);

int main(void)
{
    NODE *head = malloc(sizeof(NODE));
    head->next = NULL;
    head->data = 0;
    calculate(&head);
    free(head);

    return 0;
}

void calculate(NODE **head)
{
    char ch;
    ch = getchar();
    if (ch <= '9' && ch >= '0' || ch == '-')
    {
        if (ch == '-')
        {
            char temp = getchar();
            if (temp >= '0' && temp <= '9') // 处理负数
            {
                NODE *newnode = malloc(sizeof(NODE));
                newnode->data = 0;
                char next[10];
                int i = 0;
                next[i++] = temp;
                while ((temp = getchar()) <= '9' && temp >= '0')
                {
                    next[i++] = ch;
                }
                long x = 1;
                for (i -= 1; i >= 0; i--)
                {
                    newnode->data += (next[i] - '0') * x;
                    x *= 10;
                }
                newnode->data = -1 * newnode->data;

                newnode->next = *head;
                *head = newnode;
            }
        }
        else
        {
            char next[10];
            int i = 0;
            next[i++] = ch;
            while ((ch = getchar()) <= '9' && ch >= '0')
            {
                next[i++] = ch;
            }
            long x = 1;
            for (i -= 1; i >= 0; i--)
            {
                (*head)->data += (next[i] - '0') * x;
                x *= 10;
            }
        }
    }
    else
        return;

    while ((ch = getchar()) != '\n')
    {
        if (ch == ' ')
        {
            continue;
        }
        else if (ch <= '9' && ch >= '0')
        {
            NODE *newnode = malloc(sizeof(NODE));
            newnode->data = 0;
            char next[10];
            int i = 0;
            next[i++] = ch;
            while ((ch = getchar()) <= '9' && ch >= '0')
            {
                next[i++] = ch;
            }
            long x = 1;
            for (i -= 1; i >= 0; i--)
            {
                newnode->data += (next[i] - '0') * x;
                x *= 10;
            }

            newnode->next = *head;
            *head = newnode;
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            if (ch == '-')
            {
                char temp = getchar();
                if (temp >= '0' && temp <= '9') // 处理负数
                {
                    NODE *newnode = malloc(sizeof(NODE));
                    newnode->data = 0;
                    char next[10];
                    int i = 0;
                    next[i++] = temp;
                    while ((temp = getchar()) <= '9' && temp >= '0')
                    {
                        next[i++] = ch;
                    }
                    long x = 1;
                    for (i -= 1; i >= 0; i--)
                    {
                        newnode->data += (next[i] - '0') * x;
                        x *= 10;
                    }
                    newnode->data = -1 * newnode->data;

                    newnode->next = *head;
                    *head = newnode;
                    continue;
                }
                else if ((*head) != NULL && (*head)->next != NULL)
                {
                    long a = (*head)->next->data, b = (*head)->data;
                    push(head, a - b);
                }
                if(temp=='\n') break;
            }
            else if ((*head) != NULL && (*head)->next != NULL)
            {
                long a = (*head)->next->data, b = (*head)->data;
                if (ch == '+')
                    push(head, a + b);
                else if (ch == '*')
                    push(head, a * b);
                else if (ch == '/')
                    push(head, a / b);
            }
        }
    }
    printf("%d", (*head)->data);
}

void push(NODE **head, long value)
{
    (*head)->next->data = value;
    NODE *p = (*head)->next;
    free(*head);
    *head = p;
}