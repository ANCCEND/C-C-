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
    struct LNode *next = NULL;
} LNode, *LinkList;

typedef struct
{
    struct
    {
        char ListName[30];
        LinkList L = NULL;
    } elem[10];
    int length = 0;
} LISTS;

status InitList(LinkList &L);
status DestroyList(LinkList &L);
status ClearList(LinkList &L);
status ListEmpty(LinkList L);
status ListLength(LinkList L);
status GetElem(LinkList L, int i, ElemType &e);
status LocateElem(LinkList L, ElemType e);
status PriorElem(LinkList L, ElemType e, ElemType &pre);
status NextElem(LinkList L, ElemType e, ElemType &next);
status ListInsert(LinkList &L, int i, ElemType e);
status ListDelete(LinkList &L, int i, ElemType &e);
status ListTraverse(LinkList L);
status reverseList(LinkList L);
status RemoveNthFromEnd(LinkList L, int n);
status sortList(LinkList L);
status SaveList(LinkList L, char FileName[]);
status LoadList(LinkList &L, char FileName[]);
status AddList(LISTS &Lists, char ListName[], LinkList L);
status RemoveList(LISTS &Lists, char ListName[]);
status LocateList(LISTS &Lists, char ListName[], LinkList &L);
void DestroyAll(LISTS &Lists, LinkList &L);

int main(void)
{
    using namespace std;
    SetConsoleOutputCP(65001);
    LinkList L = NULL;
    LISTS Lists;
    int op = 1;
    int i, e, flag, length, location, n;
    char Filename[31], Listname[30];
    while (op)
    {
        system("cls");
        printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. InitList(创建表)            11. ListDelete(删除某元素)\n");
        printf("    	  2. DestroyList(删除表)         12. ListTrabverse(输出表)\n");
        printf("    	  3. ClearList(清空表)           13. reverseList(反转表)\n");
        printf("    	  4. ListEmpty(检查表是否为空)    14. RemoveNthFromEnd(删除倒数第n个元素)\n");
        printf("    	  5. ListLength(输出表长)        15. sortList(元素排序)\n");
        printf("    	  6. GetElem(输出第i个元素)       16. SaveList(保存文件名小于30字符)\n");
        printf("          7. LocateElem(查找元素位置)     17. LoadList(读取文件名小于30字符)\n");
        printf("          8. PriorElem(输出元素前驱)      18. AddList(表名小于30字符)\n");
        printf("          9. NextElem(输出元素后继)       19. RemoveList(表名小于30字符)\n");
        printf("          10. ListInsert(插入元素)        20. LocateList(表名小于30字符)\n");
        printf("    	  0. Exit\n");
        printf("    tips:多链表中最多可容纳10个表\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~20]:");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            // printf("\n----IntiList功能待实现！\n");
            if (InitList(L) == OK)
                printf("链表创建成功！\n");
            else
                printf("链表创建失败！\n");
            getchar();
            getchar();
            break;

        case 2:
            if (DestroyList(L) == OK)
                printf("链表销毁成功！\n");
            else
                printf("链表销毁失败！\n");
            getchar();
            getchar();
            break;

        case 3:
            if (ClearList(L) == OK)
                printf("已删除链表中所有元素！\n");
            else
                printf("操作失败！\n");
            getchar();
            getchar();
            break;

        case 4:
            if (ListEmpty(L) == OK)
                printf("链表为空！\n");
            else
                printf("链表不为空！\n");
            getchar();
            getchar();
            break;

        case 5:
            if ((length = ListLength(L)) != -1)
                printf("链表长度为：%d\n", length);
            else
                printf("链表不存在！\n");
            getchar();
            getchar();
            break;

        case 6:
            printf("请输入要查找的元素位置序号：");
            scanf("%d", &i);
            while (getchar() != '\n')
                ;
            printf("\n");

            if ((flag = GetElem(L, i, e)) == OK)
                printf("第%d个元素为：%d\n", i, e);
            else if (flag == ERROR)
                printf("查找位置不合法！\n");
            else
                printf("链表不存在！\n");
            getchar();
            getchar();
            break;

        case 7:
            printf("请输入要查找的元素：");
            scanf("%d", &e);
            while (getchar() != '\n')
                ;
            printf("\n");
            if ((location = LocateElem(L, e)) > 0)
                printf("它在链表L的位置序号为：%d\n", location);
            else if (location == 0)
                printf("它不在表中！\n");
            else
                printf("链表不存在!\n");
            getchar();
            getchar();
            break;

        case 8:
            int pre;
            printf("请输入要查找前驱的元素：");
            scanf("%d", &e);
            while (getchar() != '\n')
                ;
            printf("\n");

            if ((flag = PriorElem(L, e, pre)) == OK)
                printf("该元素的前驱为：%d\n", pre);
            else if (flag == 0)
                printf("该元素不在表中或没有前驱！\n");
            else
                printf("链表不存在！\n");

            getchar();
            getchar();
            break;

        case 9:
            int next;
            printf("请输入要查找后继的元素：");
            scanf("%d", &e);
            while (getchar() != '\n')
                ;

            if ((flag = NextElem(L, e, next)) == OK)
                printf("该元素的后继为：%d\n", next);
            else if (flag == ERROR)
                printf("该元素不在表中或没有后继！\n");
            else
                printf("链表不存在！\n");

            getchar();
            getchar();
            break;

        case 10:
            do
            {
                printf("请输入要插入的元素位置(输入-1回到菜单)：");
                scanf("%d", &i);
                if (i == -1)
                    break;
                printf("请输入要插入的元素值：");
                scanf("%d", &e);
                while (getchar() != '\n')
                    ;

                if ((flag = ListInsert(L, i, e)) == OK)
                    printf("插入成功！\n");
                else if (flag == ERROR)
                    printf("插入位置不合法！\n");
                else
                    printf("链表不存在！\n");
            } while (1);

            getchar();
            getchar();
            break;

        case 11:
            printf("请输入要删除的元素位置：");
            scanf("%d", &i);
            while (getchar() != '\n')
                ;
            printf("\n");

            if ((flag = ListDelete(L, i, e)) == OK)
                printf("成功删除第%d个元素%d\n", i, e);
            else if (flag == ERROR)
                printf("删除位置不合法！\n");
            else
                printf("链表不存在！\n");

            getchar();
            getchar();
            break;

        case 12:
            if (ListTraverse(L) == INFEASIBLE)
                printf("链表是空表！\n");
            getchar();
            getchar();
            break;

        case 13:
            if (reverseList(L) == OK)
                printf("反转成功！\n");
            else
                printf("链表为空！\n");
            getchar();
            getchar();
            break;

        case 14:
            cout << "输入要删除倒数第几个元素：";
            if (scanf("%d", &n) != 1)
            {
                cout << "未输入数字！" << endl;
                getchar();
                getchar();
                break;
            }
            while (getchar() != '\n')
                ;
            if ((flag = RemoveNthFromEnd(L, n)) == INFEASIBLE)
                cout << "表不存在！" << endl;
            else if (flag == ERROR)
                cout << "表长不足" << n << endl;
            else
                cout << "删除成功！" << endl;
            getchar();
            getchar();
            break;

        case 15:
            if (sortList(L) != INFEASIBLE)
                printf("排序成功！\n");
            else
                printf("链表不存在！\n");
            getchar();
            getchar();
            break;

        case 16:
            printf("请输入要保存的文件名：");
            scanf("%s", Filename);
            while (getchar() != '\n')
                ;
            printf("\n");

            if ((flag = SaveList(L, Filename)) == OK)
                printf("文件保存成功！\n");
            else if (flag == INFEASIBLE)
                printf("写入保存失败：链表不存在！\n");
            else
                cout << "文件打开失败！" << endl;
            getchar();
            getchar();
            break;

        case 17:
            printf("请输入要读取的文件名：");
            scanf("%s", Filename);
            while (getchar() != '\n')
                ;
            printf("\n");

            if ((flag = LoadList(L, Filename)) == OK)
                printf("文件读取成功！\n");
            else if (flag == INFEASIBLE)
                printf("读取失败：链表已存在！\n");
            else
                cout << "文件打开失败！" << endl;
            getchar();
            getchar();
            break;

        case 18:
            cout << "将当前的链表L加入多线性表中,请输入要加入的表名：";
            if (scanf("%s", Listname) != 1)
            {
                cout << "未输入表名！" << endl;
                break;
            }
            while (getchar() != '\n')
                ;
            printf("\n");

            if ((flag = AddList(Lists, Listname, L)) == OK)
                printf("加入表成功！\n");
            else if (flag == ERROR)
                printf("多线性表已满！\n");
            else if (flag == -3)
                cout << "名称已被使用!" << endl;
            else
                printf("要加入的线性表不存在！\n");
            getchar();
            getchar();
            break;

        case 19:
            printf("请输入要删除的表名：");
            scanf("%s", Listname);
            while (getchar() != '\n')
                ;

            if ((flag = RemoveList(Lists, Listname)) == OK)
                printf("删除链表%s成功！\n", Listname);
            else if (flag == ERROR)
                printf("删除失败，找不到链表%s\n", Listname);
            else
                cout << "多链表为空！" << endl;
            getchar();
            getchar();
            break;

        case 20:
            printf("查找线性表并将其载入L，此操作将导致L中现有数据丢失，输入Y确定操作: ");
            if (getchar() != 'Y')
                break;
            printf("\n请输入要查找的表名：");
            scanf("%s", Listname);
            while (getchar() != '\n')
                ;
            printf("\n");

            if ((location = LocateList(Lists, Listname, L)) == ERROR)
                printf("查找失败，表%s不在多链表中！\n", Listname);
            else if (location == INFEASIBLE)
                cout << "多链表表为空！" << endl;
            else
                printf("表%s的位置序号为:%d\n", Listname, location);
            getchar();
            getchar();
            break;

        case 0:
            break;
        }
    }
    printf("欢迎下次再使用本系统！\n");
    DestroyAll(Lists, L);
    return 0;
}