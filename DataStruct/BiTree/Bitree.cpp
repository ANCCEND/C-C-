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
#define MAX_NODES 100
#define FOREST_NUM 20

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

typedef struct
// 森林结构定义
{
	struct
	{
		BiTree T;
		char TName[30];
	} elem[FOREST_NUM];
	int TNum = 0;
} Forest;

void visit(BiTree T);
BiTree CreateTree(TElemType definition[], int &flag);
status CreateBiTree(BiTree &T, TElemType definition[]);
void ClearTree(BiTree t);
status ClearBiTree(BiTree &T);
status DestroyBiTree(BiTree &T);
status isEmptyTree(BiTree T);
int BiTreeDepth(BiTree T);
BiTNode *LocateNode(BiTree T, KeyType e);
status Assign(BiTree &T, KeyType e, TElemType value);
BiTNode *GetSibling(BiTree T, KeyType e);
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c);
status DeleteNode(BiTree &T, KeyType e);
status PreOrderTraverse(BiTree T);
status InOrderTraverse(BiTree T);
status PostOrderTraverse(BiTree T);
status LevelOrderTraverse(BiTree T);
void WriteToFile(BiTree T, FILE *fp);
status SaveBiTree(BiTree T, char FileName[]);
BiTree ReadFromFile(FILE *fp);
status LoadBiTree(BiTree &T, char FileName[]);
status MaxPathSum(BiTree T);
BiTree LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2);
status InvertTree(BiTree T);
BiTree CopyTree(BiTree T);
status AddTree(BiTree T, Forest &Trees, char TreeName[]);
status DeleteTree(Forest &Trees, char TreeName[]);
status GetBiTree(BiTree &T, Forest Trees, char TreeName[]);
void DestroyAll(Forest Trees);

int main(void)
{
	using namespace std;
	SetConsoleOutputCP(65001);
	BiTree T = NULL;
	BiTree Ttemp;
	Forest Trees;
	TElemType value;
	int op = 1;
	KeyType e, e1, e2;
	int i, flag, location, LR;
	char FileName[31], TreeName[31];
	while (op)
	{
		system("cls");
		printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. 创建二叉树         12. 中序遍历\n");
		printf("    	  2. 销毁二叉树         13. 后序遍历\n");
		printf("    	  3. 清空二叉树         14. 按层遍历\n");
		printf("    	  4. 判定空二叉树       15. 最大路径和\n");
		printf("    	  5. 求二叉树深度       16. 最近公共祖先\n");
		printf("    	  6. 查找结点           17. 反转二叉树\n");
		printf("          7. 结点赋值           18. 文件存储二叉树\n");
		printf("          8. 获得兄弟结点       19. 文件读取二叉树\n");
		printf("          9. 插入结点           20. 加入一个二叉树到森林\n");
		printf("          10. 删除结点          21. 从森林移除一个二叉树\n");
		printf("          11. 前序遍历          22. 从森林取得一个二叉树");
		printf("    	  0. Exit\n");
		printf("    tips:森林中最多可容纳20个树\n");
		printf("-------------------------------------------------\n");
		printf("    请选择你的操作[0~22]:");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			cout << "输入要创建的二叉树的前序遍历序列" << endl;
			int i = 0;
			TElemType definition[MAX_NODES];
			do
			{
				scanf("%d %s", &definition[i].key, definition[i].others);
				i++;
			} while (definition[i].key != -1);
			if ((flag = CreateBiTree(T, definition)) == INFEASIBLE)
				cout << "创建失败，二叉树不为空！" << endl;
			else if (flag == OK)
				cout << "二叉树创建成功！" << endl;
			else
				cout << "有重复的关键字！" << endl;
			while (getchar() != '\n')
				;
			getchar();
			break;

		case 2:
			DestroyBiTree(T);
			cout << "二叉树销毁成功！" << endl;
			while (getchar() != '\n')
				;
			getchar();
			break;

		case 3:
			ClearBiTree(T);
			cout << "二叉树清空成功！" << endl;
			while (getchar() != '\n')
				;
			getchar();
			break;

		case 4:
			if (isEmptyTree(T) == OK)
				cout << "二叉树为空！" << endl;
			else
				cout << "二叉树不为空" << endl;
			while (getchar() != '\n')
				;
			getchar();
			break;

		case 5:
			if ((flag = BiTreeDepth(T)) == INFEASIBLE)
				cout << "二叉树为空！" << endl;
			else
				cout << "二叉树深度为" << flag << endl;
			while (getchar() != '\n')
				;
			getchar();
			break;

		case 6:
			cout << "输入要查找的关键字：";
			cin >> e;
			if ((Ttemp = LocateNode(T, e)) == NULL)
				cout << "未查找到该结点。" << endl;
			else
				cout << "已找到该结点：" << Ttemp->data.key << ',' << Ttemp->data.others << endl;
			while (getchar() != '\n')
				;
			getchar();
			break;
		case 7:
			cout << "输入要赋值结点的关键字：";
			cin >> e;
			cout << "输入要赋的键值对（空格隔开）：";
			cin >> value.key >> value.others;
			if ((flag = Assign(T, e, value)) == INFEASIBLE)
				cout << "树为空！" << endl;
			else if (flag == -2)
				cout << "关键字重复！" << endl;
			else if (flag == OK)
				cout << "赋值成功！" << endl;
			else
				cout << "未找到要赋值的结点！" << endl;
			while (getchar() != '\n')
				;
			getchar();
			break;

		case 8:
			cout << "输入要查找兄弟结点的结点的关键字：";
			cin >> e;
			if (T == NULL)
			{
				cout << "树为空！" << endl;
			}

			else
			{
				if ((Ttemp = (GetSibling(T, e))) == NULL)
					cout << "无兄弟结点！" << endl;
				else
					cout << "他的兄弟结点为：" << Ttemp->data.key << ',' << Ttemp->data.others;
			}
			while (getchar() != '\n')
				;
			getchar();
			break;
		case 9:
			cout << "输入要插入结点的位置（关键字）和插入左右（左为0右为1，-1为根结点）：";
			cin >> e >> LR;
			cout << "输入要插入的结点内容（空格隔开）：";
			cin >> value.key >> value.others;
			if ((flag = InsertNode(T, e, LR, value)) == INFEASIBLE)
				cout << "树为空！" << endl;
			else if (flag == -2)
				cout << "关键字重复！" << endl;
			else if (flag == ERROR)
				cout << "未找到插入位置！" << endl;
			else
				cout << "插入成功！" << endl;
			while (getchar() != '\n')
				;
			getchar();
			break;

		case 10:
			cout << "输入要删除结点的关键字：";
			cin >> e;
			if ((flag = DeleteNode(T, e)) == INFEASIBLE)
				cout << "树为空！" << endl;
			else if (flag == ERROR)
				cout << "未找到要删除的结点！" << endl;
			else
				cout << "删除成功！" << endl;
			while (getchar() != '\n')
				;
			getchar();
			break;

		case 11:
			if (PreOrderTraverse(T) == INFEASIBLE)
				cout << "树为空！" << endl;
			else
				cout << "  (先序遍历)" << endl;
			while (getchar() != '\n')
				;
			getchar();
			break;

		case 12:
			if (InOrderTraverse(T) == INFEASIBLE)
				cout << "树为空！" << endl;
			else
				cout << "  (中序遍历)" << endl;
			while (getchar() != '\n')
				;
			getchar();
			break;

		case 13:
			if (PostOrderTraverse(T) == INFEASIBLE)
				cout << "树为空！" << endl;
			else
				cout << "  (后序遍历)" << endl;
			while (getchar() != '\n')
				;
			getchar();
			break;

		case 14:
			if (LevelOrderTraverse(T) == INFEASIBLE)
				cout << "树为空！" << endl;
			else
				cout << "  (层序遍历)" << endl;
			while (getchar() != '\n')
				;
			getchar();
			break;

		case 15:
			if ((flag = MaxPathSum(T)) == INFEASIBLE)
				cout << "树为空！" << endl;
			else
				cout << "最大路径和为：" << flag << endl;
			while (getchar() != '\n')
				;
			getchar();
			break;

		case 16:
			cout << "请输入要查找共同祖先的结点的关键字：";
			cin >> e1 >> e2;
			BiTree temp1, temp2;
			if ((temp1 = LocateNode(T, e1)) && (temp2 = LocateNode(T, e2)))
			{
				if ((Ttemp = LowestCommonAncestor(T, e1, e2)) == NULL)
					cout << "树为空！" << endl;
				else
					cout << "共同祖先为：" << Ttemp->data.key << ',' << Ttemp->data.others << endl;
			}
			else if (temp1 == NULL && temp2 != NULL)
				cout << "第一个结点不在树中！" << endl;
			else if (temp2 == NULL && temp1 != NULL)
				cout << "第二个结点不在树中！" << endl;
			else
				cout << "两个结点都不在树中！" << endl;
			while (getchar() != '\n')
				;
			getchar();
			break;

		case 17:
			if ((flag == InvertTree(T)) == INFEASIBLE)
				cout << "树不存在！" << endl;
			else
				cout << "反转成功！" << endl;
			while (getchar() != '\n')
				;
			getchar();
			break;

		case 18:
			cout << "注意：输入文件名超过30个字符的部分将被截断！" << endl;
			cout << "请输入目标文件名(输入N取消操作)：";
			cin >> FileName;
			if (FileName[0] == 'N' && FileName[1] == 0)
			{
				while (getchar() != '\n')
					;
				break;
			}
			if ((flag = SaveBiTree(T, FileName)) == INFEASIBLE)
				cout << "树为空！" << endl;
			else if (flag == ERROR)
				cout << "打开文件失败！" << endl;
			else
				cout << "存储成功！" << endl;
			while (getchar() != '\n')
				;
			getchar();
			break;

		case 19:
			cout << "注意：输入文件名超过30个字符的部分将被截断！" << endl;
			cout << "请输入目标文件名(输入N取消操作)：";
			cin >> FileName;
			if (FileName[0] == 'N' && FileName[1] == 0)
			{
				while (getchar() != '\n')
					;
				break;
			}
			if ((flag == LoadBiTree(T, FileName)) == INFEASIBLE)
				cout << "树不为空！" << endl;
			else if (flag == ERROR)
				cout << "文件打开失败！" << endl;
			else
				cout << "读取成功！" << endl;
			while (getchar() != '\n')
				;
			getchar();
			break;

		case 20:
			cout << "注意：输入名称超过30个字符的部分将被截断！" << endl;
			cout << "请为将要加入森林的树命名(输入N取消操作)：";
			cin >> TreeName;
			if (TreeName[0] == 'N' && TreeName[1] == 0)
			{
				while (getchar() != '\n')
					;
				break;
			}
			if ((flag == AddTree(T, Trees, TreeName)) == INFEASIBLE)
				cout << "树不存在！" << endl;
			else if (flag == ERROR)
				cout << "多二叉树已满！（" << FOREST_NUM << '）' << endl;
			else
				cout << "加入成功！" << endl;
			while (getchar() != '\n')
				;
			getchar();
			break;

		case 21:
			cout << "注意：输入名称超过30个字符的部分将被截断！" << endl;
			cout << "请输入将要删除的树的名称(输入N取消操作)：";
			cin >> TreeName;
			if (TreeName[0] == 'N' && TreeName[1] == 0)
			{
				while (getchar() != '\n')
					;
				break;
			}
			if ((flag == DeleteTree(Trees, TreeName)) == INFEASIBLE)
				cout << "森林为空！" << endl;
			else if (flag == ERROR)
				cout << "未找到树！" << endl;
			else
				cout << "删除成功！" << endl;
			while (getchar() != '\n')
				;
			getchar();
			break;
		case 22:
			cout << "注意：此操作将清空现有T中的内容并读取一个二叉树，输入名称超过30个字符的部分将被截断！" << endl;
			cout << "请输入将要导入的树的名称(输入N取消操作)：";
			cin >> TreeName;
			if (TreeName[0] == 'N' && TreeName[1] == 0)
			{
				while (getchar() != '\n')
					;
				break;
			}
			if ((flag = GetBiTree(T, Trees, TreeName)) == INFEASIBLE)
				cout << "森林为空！" << endl;
			else if (flag == ERROR)
				cout << "未找到该树！" << endl;
			while (getchar() != '\n')
				;
			getchar();
			break;

		case 0:
			break;
		}
	}
	printf("欢迎下次再使用本系统！\n");
	DestroyAll(Trees);
	return 0;
}