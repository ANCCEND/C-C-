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
status InsertVex(ALGraph &G, VertexType v);
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
    KeyType key, v, u, w;
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
        printf("    tips:最多可以管理20个图\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~20]:");
        scanf("%d", &op);
        switch (op)
        {
                }
    }
    printf("欢迎下次再使用本系统！\n");
    DestroyAll(Graphs, G);
    return 0;
}