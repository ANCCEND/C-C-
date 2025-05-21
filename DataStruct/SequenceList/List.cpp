/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <string>

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
{ // 顺序表(顺序结构)的定义
    ElemType *elem = NULL;
    int length = 0;
    int listsize = LIST_INIT_SIZE;
} SqList;

typedef struct
{ // 线性表的集合类型定义
    struct
    {
        char name[30];
        SqList L;
    } elem[10];
    int length = 0;
} LISTS;
/*-----page 19 on textbook ---------*/
status InitList(SqList &L);
status DestroyList(SqList &L);
status ClearList(SqList &L);
status ListEmpty(SqList L);
status ListLength(SqList L);
status GetElem(SqList L, int i, ElemType &e);
status LocateElem(SqList L, ElemType e); // 简化过
status PriorElem(SqList L, ElemType e, ElemType &pre);
status NextElem(SqList L, ElemType e, ElemType &next);
status ListInsert(SqList &L, int i, ElemType e);
status ListDelete(SqList &L, int i, ElemType &e);
status ListTraverse(SqList L); // 简化过
status MaxSubArray(SqList L);
status SubArrayNum(SqList L, int k);
status sortList(SqList L);
status SaveList(SqList L, char FileName[]);
status LoadList(SqList &L, char FileName[]);
status AddList(LISTS &Lists, char ListName[], SqList &L);
status RemoveList(LISTS &Lists, char ListName[]);
int LocateList(LISTS Lists, char ListName[], SqList &L);
status CreateList(LISTS &Lists, char ListName[]);
/*--------------------------------------------*/
int main(void)
{
    using namespace std;
    SetConsoleOutputCP(65001);
    SqList L;
    LISTS Lists;
    int op = 1;
    int i, e, flag, length, location;
    char Filename[31], Listname[30];
    while (op)
    {
        system("cls");
        printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. InitList(创建表)            11. ListDelete(删除某元素)\n");
        printf("    	  2. DestroyList(删除表)         12. ListTrabverse(输出表)\n");
        printf("    	  3. ClearList(清空表)           13. MaxSubArray(最大子数组和)\n");
        printf("    	  4. ListEmpty(检查表是否为空)    14. SubArrayNum(和为n的子数组个数)\n");
        printf("    	  5. ListLength(输出表长)        15. sortList(元素排序)\n");
        printf("    	  6. GetElem(输出第i个元素)       16. SaveList(保存文件名小于30字符)\n");
        printf("          7. LocateElem(查找元素位置)     17. LoadList(读取文件名小于30字符)\n");
        printf("          8. PriorElem(输出元素前驱)      18. AddList(表名小于30字符)\n");
        printf("          9. NextElem(输出元素后继)       19. RemoveList(表名小于30字符)\n");
        printf("          10. ListInsert(插入元素)        20. LocateList(表名小于30字符)\n");
        printf("                                         21. CreateList(在多线性表中创建一个空表)\n");
        printf("    	  0. Exit\n");
        printf("    tips:多线性表中最多可存储10个表\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~21]:");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            // printf("\n----IntiList功能待实现！\n");
            if (InitList(L) == OK)
                printf("线性表创建成功！\n");
            else
                printf("线性表创建失败：线性表已存在！\n");
            getchar();
            getchar();
            break;

        case 2:
            if (DestroyList(L) == OK)
                printf("线性表销毁成功！\n");
            else
                printf("线性表销毁失败！\n");
            getchar();
            getchar();
            break;

        case 3:
            if (ClearList(L) == OK)
                printf("已删除线性表中所有元素！\n");
            else
                printf("操作失败！\n");
            getchar();
            getchar();
            break;

        case 4:
            if (ListEmpty(L) == OK)
                printf("线性表为空！\n");
            else
                printf("线性表不为空！\n");
            getchar();
            getchar();
            break;

        case 5:
            if ((length = ListLength(L)) != -1)
                printf("线性表长度为：%d\n", length);
            else
                printf("线性表不存在！\n");
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
                printf("位置序号不合法！\n");
            else
                printf("线性表不存在！\n");
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
                printf("它在线性表L的位置序号为：%d\n", location);
            else if (location == 0)
                printf("它不在表中！\n");
            else
                printf("线性表不存在!\n");
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
                printf("线性表不存在！\n");

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
                printf("线性表不存在！\n");

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
                printf("\n");

                if ((flag = ListInsert(L, i, e)) == OK)
                    printf("插入成功！\n");
                else if (flag == ERROR)
                    printf("插入位置不合法！\n");
                else
                {
                    printf("线性表不存在！\n");
                    break;
                }
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
                printf("线性表不存在！\n");

            getchar();
            getchar();
            break;

        case 12:
            if (ListTraverse(L) == INFEASIBLE)
                printf("线性表是空表！\n");
            getchar();
            getchar();
            break;

        case 13:
            MaxSubArray(L);
            getchar();
            getchar();
            break;

        case 14:
            int k;
            printf("输入要查找的子数组和：");
            scanf("%d", &k);
            printf("\n");
            while (getchar() != '\n')
                ;

            if ((flag = SubArrayNum(L, k)) == INFEASIBLE)
                printf("线性表不存在！\n");
            else
                printf("和为%d的子数组个数为：%d\n", k, flag);
            getchar();
            getchar();
            break;

        case 15:
            if (sortList(L) != INFEASIBLE)
                printf("排序成功！\n");
            else
                printf("线性表不存在！\n");
            getchar();
            getchar();
            break;

        case 16:
            printf("请输入要保存的文件名：");
            scanf("%s", Filename);
            while (getchar() != '\n')
                ;
            printf("\n");

            if (SaveList(L, Filename) == OK)
                printf("文件保存成功！\n");
            else
                printf("写入保存失败：线性表不存在！\n");
            getchar();
            getchar();
            break;

        case 17:
            printf("请输入要读取的文件名：");
            if (scanf("%s", Filename) != 1)
            {
                cout << "未输入文件名！" << endl;
            }
            while (getchar() != '\n')
                ;
            printf("\n");

            if (LoadList(L, Filename) == OK)
                printf("文件读取成功！\n");
            else
                printf("线性表已存在！\n");
            getchar();
            getchar();
            break;

        case 18:
            cout << "将当前的链表L加入多线性表中,请输入要加入的表名：";
            scanf("%s", Listname);
            while (getchar() != '\n')
                ;
            printf("\n");

            if ((flag = AddList(Lists, Listname, L)) == OK)
                printf("加入表成功！\n");
            else if (flag == INFEASIBLE)
                printf("多线性表已满！\n");
            else if (flag == -3)
                cout << "名称已被使用！" << endl;
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
            printf("\n");

            if (RemoveList(Lists, Listname) == OK)
                printf("删除线性表%s成功！\n", Listname);
            else
                printf("删除失败，找不到线性表%s\n", Listname);
            getchar();
            getchar();
            break;

        case 20:
            printf("查找线性表并将其载入L，此操作将导致L中现有数据丢失，输入Y确定操作: ");
            while (getchar() != '\n')
                ;
            if (getchar() != 'Y')
                break;
            printf("\n请输入要查找的表名：");
            scanf("%s", Listname);
            while (getchar() != '\n')
                ;
            printf("\n");

            if ((location = LocateList(Lists, Listname, L)) != ERROR)
                printf("表%s的位置序号为:%d\n", Listname, location);
            else
                printf("查找失败，表%s不存在！\n", Listname);
            getchar();
            getchar();
            break;

        case 21:
            printf("请输入要创建的表名：");
            scanf("%s", Listname);
            while (getchar() != '\n')
                ;
            printf("\n");

            if (CreateList(Lists, Listname) == OK)
                printf("新建表成功！\n");
            else
                printf("多线性表已满！\n");
            getchar();
            getchar();
            break;

        case 0:
            break;

        } // end of switch
    } // end of while
    printf("欢迎下次再使用本系统！\n");
    free(L.elem);

    return 0;
} // end of main()
/*--------page 23 on textbook --------------------*/
