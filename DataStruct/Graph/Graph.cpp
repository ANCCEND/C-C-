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
#define MAX_VERTEX_NUM 20
#define MAX_GRAPH_NUM 20

typedef int status;
typedef int KeyType;
typedef enum
{
    DG,
    DN,
    UDG,
    UDN
} GraphKind;
typedef struct
{
    KeyType key;
    char others[20];
} VertexType; // 顶点类型定义

typedef struct ArcNode
{                            // 表结点类型定义
    int adjvex;              // 顶点位置编号
    struct ArcNode *nextarc; // 下一个表结点指针
} ArcNode;
typedef struct VNode
{                      // 头结点及其数组类型定义
    VertexType data;   // 顶点信息
    ArcNode *firstarc; // 指向第一条弧
} VNode, AdjList[MAX_VERTEX_NUM];
typedef struct
{                               // 邻接表的类型定义
    AdjList vertices;           // 头结点数组
    int vexnum = 0, arcnum = 0; // 顶点数、弧数
    GraphKind kind;             // 图的类型
} ALGraph;
typedef struct
{
    struct
    {
        ALGraph G;
        char GName[31];
    } elem[MAX_GRAPH_NUM];
    int GNum = 0;
} Gs;

status DestroyGraph(ALGraph &G);
int LocateVertex(ALGraph &G, KeyType key);
status CreateGraph(ALGraph &G, VertexType V[], KeyType VR[][2]);
status PutVex(ALGraph &G, KeyType u, VertexType value);
status FirstAdjVex(ALGraph G, KeyType u);
status NextAdjVex(ALGraph G, KeyType v, KeyType w);
status InsertVex(ALGraph &G, VertexType value);
status DeleteVex(ALGraph &G, KeyType v);
status InsertArc(ALGraph &G, KeyType v, KeyType w);
status DeleteArc(ALGraph &G, KeyType v, KeyType w);
status DFSTraverse(ALGraph &G);
status BFSTraverse(ALGraph &G);
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph &G, char FileName[]);
status VerticesSetLessThanK(ALGraph G, KeyType v, int k);
status ShortestPathLength(ALGraph G, KeyType v, KeyType w);
status ConnectedComponentsNums(ALGraph G);
ALGraph CopyGraph(ALGraph G);
status AddGraph(Gs &Graphs, ALGraph G, char GraphName[]);
status GetGraph(Gs Graphs, ALGraph &G, char GraphName[]);
status DeleteGraph(Gs &Graphs, char GraphName[]);
void DestroyAll(Gs &Graphs, ALGraph &G);

int main(void)
{
    using namespace std;
    SetConsoleOutputCP(65001);
    ALGraph G;
    Gs Graphs;
    VertexType V[MAX_VERTEX_NUM + 1], value;
    KeyType VR[MAX_VERTEX_NUM * (MAX_VERTEX_NUM - 1) / 2 + 1][2];
    int op = 1;
    KeyType key, v, k, w;
    int i, flag, location;
    char FileName[31], GraphName[31];
    while (op)
    {
        system("cls");
        printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. 创建图             11. 深度优先搜索遍历\n");
        printf("    	  2. 销毁图             12. 广度优先搜索遍历\n");
        printf("    	  3. 查找顶点           13. 距离小于k的顶点集合\n");
        printf("    	  4. 顶点赋值           14. 顶点间最短路径长度\n");
        printf("    	  5. 获得第一邻接点      15. 图的连通分量\n");
        printf("    	  6. 获得下一邻接点      16. 文件保存图\n");
        printf("          7. 插入顶点           17. 文件读取图\n");
        printf("          8. 删除顶点           18. 添加一个图到多图管理中\n");
        printf("          9. 插入弧             19. 移除一个图\n");
        printf("          10. 删除弧            20. 取得一个图\n");
        printf("    	  0. Exit\n");
        printf("    tips:最多可以管理%d个图，每个图的顶点数小于%d，创建的图为无向图。\n", MAX_GRAPH_NUM, MAX_VERTEX_NUM);
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~20]:");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            // 5 a 8 b 7 c 6 d -1 nil 5 6 5 7 6 7 7 8 -1 -1
            if (G.vexnum != 0)
            {
                cout << "图不为空！" << endl;
            }
            else
            {
                cout << "请输入图的顶点序列（关键字 内容），（以 -1 nil 结尾）：" << endl;
                int i;
                for (i = 0; i < MAX_VERTEX_NUM; i++)
                {
                    cin >> V[i].key >> V[i].others;
                    if (V[i].key == -1)
                        break;
                }

                if (i == MAX_VERTEX_NUM && V[i - 1].key != -1)
                {
                    V[i].key = -1;
                    strcpy(V[i].others, "nil");
                }
                cout << "请输入图的边序列（关键字 关键字），以（-1 -1）结尾：" << endl;
                int maxArc = MAX_VERTEX_NUM * (MAX_VERTEX_NUM - 1) / 2;
                for (i = 0; i < maxArc; i++)
                {
                    cin >> VR[i][0] >> VR[i][1];
                    if (VR[i][0] == -1 && VR[i][1] == -1)
                        break;
                }

                if (i == maxArc && VR[i - 1][0] != -1)
                    VR[i][0] = VR[i][1] = -1;

                if ((flag = CreateGraph(G, V, VR)) == INFEASIBLE)
                {
                    cout << "顶点序列为空！" << endl;
                }
                else if (flag == ERROR)
                {
                    cout << "出现重复顶点" << endl;
                }
                else if (flag == -2)
                    cout << "边不合法！" << endl;
                else
                {
                    cout << "图创建成功！" << endl;
                }
            }
            while (getchar() != '\n')
                ;
            getchar();
            break;

        case 2:
            if (DestroyGraph(G) == OK)
                cout << "销毁图成功！" << endl;
            while (getchar() != '\n')
                ;
            getchar();
            break;

        case 3:
            cout << "请输入需要查找的顶点的关键字：" << endl;
            cin >> key;
            if (G.vexnum == 0)
            {
                cout << "图为空！" << endl;
                break;
            }
            if ((flag = LocateVertex(G, key)) == -1)
                cout << "未找到顶点！" << endl;
            else
                cout << "找到顶点：" << G.vertices[flag].data.key << ", " << G.vertices[flag].data.others;
            while (getchar() != '\n')
                ;
            getchar();
            break;

        case 4:
            cout << "请输入需要赋值的顶点的关键字：" << endl;
            cin >> key;
            cout << "请输入需要赋的值（关键字 内容）：" << endl;
            cin >> value.key >> value.others;
            if ((flag = PutVex(G, key, value)) == INFEASIBLE)
                cout << "图为空！";
            else if (flag == ERROR)
                cout << "未找到顶点！";
            else if (flag == -2)
                cout << "关键字重复！";
            else
                cout << "赋值成功！";
            cout << endl;
            while (getchar() != '\n')
                ;
            getchar();
            break;

        case 5:
            cout << "请输入需要获得第一邻接点的顶点关键字：" << endl;
            cin >> key;
            if ((flag = FirstAdjVex(G, key)) == INFEASIBLE)
                cout << "图为空！";
            else if (flag == ERROR)
                cout << "未找到顶点！";
            else if (flag == -3)
                cout << "无第一邻接点！";
            else
                cout << "第一邻接点为：" << G.vertices[flag - 1].data.key << ", " << G.vertices[flag - 1].data.others;
            cout << endl;
            while (getchar() != '\n')
                ;
            getchar();
            break;

        case 6:
            cout << "请输入需要获得下一邻接点的两个顶点v,w的关键字：" << endl;
            cin >> v >> w;
            if ((flag = NextAdjVex(G, v, w)) == INFEASIBLE)
                cout << "图为空！";
            else if (flag == ERROR)
                cout << "未找到顶点！";
            else if (flag == -2)
                cout << "无下一邻接点或v无邻接点！";
            else
                cout << "下一邻接点为：" << G.vertices[flag - 1].data.key << ", " << G.vertices[flag - 1].data.others;
            cout << endl;
            while (getchar() != '\n')
                ;
            getchar();
            break;

        case 7:
            cout << "请输入要插入的顶点信息（关键字 内容）：" << endl;
            cin >> value.key >> value.others;
            if ((flag = InsertVex(G, value)) == INFEASIBLE)
                cout << "图已满！";
            else if (flag == ERROR)
                cout << "关键字重复！";
            else
                cout << "插入成功！";
            cout << endl;
            while (getchar() != '\n')
                ;
            getchar();
            break;

        case 8:
            cout << "请输入需要删除顶点的关键字：" << endl;
            cin >> key;
            if ((flag = DeleteVex(G, key)) == INFEASIBLE)
                cout << "图中仅剩最后一个顶点！";
            else if (flag == ERROR)
                cout << "未找到要删除的顶点！";
            else
                cout << "删除成功！";
            cout << endl;
            while (getchar() != '\n')
                ;
            getchar();
            break;

        case 9:
            cout << "请输入要加入的弧：" << endl;
            cin >> v >> w;
            if ((flag = InsertArc(G, v, w)) == INFEASIBLE)
                cout << "图为空！";
            else if (flag == ERROR)
                cout << "未找到与弧关联的顶点或弧的两顶点相同！";
            else if (flag == -2)
                cout << "弧已存在！";
            else
                cout << "加入成功！";
            cout << endl;
            while (getchar() != '\n')
                ;
            getchar();
            break;

        case 10:
            cout << "请输入要删除的弧：" << endl;
            cin >> v >> w;
            if ((flag = DeleteArc(G, v, w)) == INFEASIBLE)
                cout << "图为空！";
            else if (flag == ERROR)
                cout << "未找到与弧关联的顶点或弧的两顶点相同！";
            else if (flag == -2)
                cout << "弧不存在！";
            else
                cout << "删除成功！";
            cout << endl;
            while (getchar() != '\n')
                ;
            getchar();
            break;

        case 11:
            DFSTraverse(G);
            while (getchar() != '\n')
                ;
            getchar();
            break;

        case 12:
            BFSTraverse(G);
            while (getchar() != '\n')
                ;
            getchar();
            break;

        case 13:
            cout << "请输入顶点v的关键字与距离k：";
            cin >> v >> k;
            if ((flag = VerticesSetLessThanK(G, v, k)) == INFEASIBLE)
                cout << "图为空！";
            else if (flag == ERROR)
                cout << "未找到顶点v！";
            cout << endl;
            while (getchar() != '\n')
                ;
            getchar();
            break;

        case 14:
            cout << "请输入两顶点的关键字：";
            cin >> v >> w;
            if ((flag = ShortestPathLength(G, v, w)) == INFEASIBLE)
                cout << "图为空！";
            else if (flag == -2)
                cout << "起点或终点不存在！";
            else if (flag == -3)
                cout << "两顶点间无通路！";
            else
                cout << "两顶点间最短路径为：" << flag;
            cout << endl;
            while (getchar() != '\n')
                ;
            getchar();
            break;

        case 15:
            if ((flag = ConnectedComponentsNums(G)) == INFEASIBLE)
                cout << "图为空！";
            else
                cout << "图拥有" << flag << "个连通分量";
            cout << endl;
            while (getchar() != '\n')
                ;
            getchar();
            break;

        case 16:
            cout << "请输入要保存的文件名(小于30个字符，输入N取消保存)：";
            cin >> FileName;
            if (FileName[0] == 'N' && FileName[1] == 0)
                break;
            if ((flag = SaveGraph(G, FileName)) == INFEASIBLE)
                cout << "图为空！";
            else if (flag == ERROR)
                cout << "文件打开失败！";
            else
                cout << "保存成功！";
            cout << endl;
            while (getchar() != '\n')
                ;
            getchar();
            break;

        case 17:
            cout << "请输入要读取的文件名（小于30字符，输入N取消读取）：";
            cin >> FileName;
            if (FileName[0] == 'N' && FileName[1] == 0)
                break;
            if ((flag = LoadGraph(G, FileName)) == INFEASIBLE)
                cout << "图不为空！";
            else if (flag == ERROR)
                cout << "打开文件失败！";
            else
                cout << "读取成功！";
            cout << endl;
            while (getchar() != '\n')
                ;
            getchar();
            break;

        case 18:
            cout << "请输入要加入的图的名称（小于30字符）：";
            cin >> GraphName;
            if ((flag = AddGraph(Graphs, G, GraphName)) == INFEASIBLE)
                cout << "图为空！";
            else if (flag == ERROR)
                cout << "图的数量达到上限！";
            else if (flag == -2)
                cout << "已存在同名图！";
            else
                cout << "添加成功！";
            cout << endl;
            while (getchar() != '\n')
                ;
            getchar();
            break;

        case 19:
            cout << "请输入要删除的图的名称（小于30字符）：";
            cin >> GraphName;
            if ((flag = DeleteGraph(Graphs, GraphName)) == INFEASIBLE)
                cout << "图集为空！";
            else if (flag == ERROR)
                cout << "未找到目标图！";
            else
                cout << "删除成功！";
            cout << endl;
            while (getchar() != '\n')
                ;
            getchar();
            break;

        case 20:
            cout << "请输入要取得的图的名称（小于30字符）：";
            cin >> GraphName;
            if ((flag = GetGraph(Graphs, G, GraphName)) == INFEASIBLE)
                cout << "现有图不为空！";
            else if (flag == ERROR)
                cout << "未找到目标图！";
            else
                cout << "读取成功！";
            cout << endl;
            while (getchar() != '\n')
                ;
            getchar();
            break;

        case 0:
            break;
        }
    }
    printf("欢迎下次再使用本系统！\n");
    DestroyAll(Graphs, G);
    return 0;
}