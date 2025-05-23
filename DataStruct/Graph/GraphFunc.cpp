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
{                             // 头结点及其数组类型定义
    VertexType data;          // 顶点信息
    ArcNode *firstarc = NULL; // 指向第一条弧
} VNode, AdjList[MAX_VERTEX_NUM];
typedef struct
{                               // 邻接表的类型定义
    AdjList vertices;           // 头结点数组
    int vexnum = 0, arcnum = 0; // 顶点数、弧数
    GraphKind kind;             // 图的类型
} ALGraph;

status DestroyGraph(ALGraph &G)
/*销毁无向图G,删除G的全部顶点和边*/
{
    int vexnum = G.vexnum;
    for (int i = 0; i < vexnum; i++)
    {
        ArcNode *temp = G.vertices[i].firstarc;
        while (temp != NULL)
        {
            ArcNode *temp2 = temp->nextarc;
            free(temp);
            temp = temp2;
        }
        G.vertices[i].firstarc = NULL;
    }
    G.vexnum = G.arcnum = 0;
    return OK;
}

int LocateVertex(ALGraph &G, KeyType key)
{
    for (int i = 0; i < G.vexnum; ++i)
    {
        if (G.vertices[i].data.key == key)
            return i;
    }
    return -1;
}

status CreateCraph(ALGraph &G, VertexType V[], KeyType VR[][2])
{
    if (V[0].key == -1)
        return ERROR;

    G.vexnum = G.arcnum = 0;
    G.kind = UDG;

    // 插入顶点
    for (int i = 0; V[i].key != -1; ++i)
    {
        if (LocateVertex(G, V[i].key) != -1 || i > 20)
        {
            G.vexnum = 0;
            return ERROR; // 重复 key
        }
        G.vertices[G.vexnum].data = V[i];
        G.vertices[G.vexnum].firstarc = NULL;
        G.vexnum++;
    }

    // 插入边
    for (int i = 0; VR[i][0] != -1 && VR[i][1] != -1; ++i)
    {
        int v1 = LocateVertex(G, VR[i][0]);
        int v2 = LocateVertex(G, VR[i][1]);

        if (v1 == -1 || v2 == -1 || v1 == v2)
        {
            DestroyGraph(G);
            return ERROR;
        }

        // 插入 v1 -> v2
        ArcNode *p1 = (ArcNode *)malloc(sizeof(ArcNode));
        p1->adjvex = v2;
        p1->nextarc = G.vertices[v1].firstarc;
        G.vertices[v1].firstarc = p1;

        // 插入 v2 -> v1（无向图）
        ArcNode *p2 = (ArcNode *)malloc(sizeof(ArcNode));
        p2->adjvex = v1;
        p2->nextarc = G.vertices[v2].firstarc;
        G.vertices[v2].firstarc = p2;

        G.arcnum++;
    }

    return OK;
}

status PutVex(ALGraph &G, KeyType u, VertexType value)
// 根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
// 如果查找失败或关键字不唯一，返回ERROR
{
    int location = -1, count = 0, i;
    for (i = 0; i < G.vexnum; i++)
    {
        if (value.key == G.vertices[i].data.key && u != G.vertices[i].data.key)
            return ERROR;
        if (u == G.vertices[i].data.key)
            location = i;
    }
    if (location == -1)
        return ERROR;
    G.vertices[location].data = value;
    return OK;
}

int FirstAdjVex(ALGraph G, KeyType u)
// 根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == u)
            return G.vertices[i].firstarc->adjvex;
    }
    return INFEASIBLE;
}

int NextAdjVex(ALGraph G, KeyType v, KeyType w)
// v对应G的一个顶点,w对应v的邻接顶点；操作结果是返回v的（相对于w）下一个邻接顶点的位序；如果w是最后一个邻接顶点，或v、w对应顶点不存在，则返回-1。
{
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == v)
        {
            ArcNode *temp = G.vertices[i].firstarc;
            while (temp != NULL && G.vertices[temp->adjvex].data.key != w)
            {
                temp = temp->nextarc;
            }
            if (temp == NULL || temp->nextarc == NULL)
                return INFEASIBLE;
            else
                return temp->nextarc->adjvex;
        }
    }
    return INFEASIBLE;
}

status InsertVex(ALGraph &G, VertexType v)
// 在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    if (G.vexnum == MAX_VERTEX_NUM)
        return ERROR;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == v.key)
            return ERROR;
    }
    G.vertices[G.vexnum++].data = v;
    return OK;
}

status DeleteVex(ALGraph &G, KeyType v)
{
    if (G.vexnum == 1)
        return ERROR;

    int index = -1, count = 0;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == v)
        {
            index = i;
            break;
        }
    }
    if (index == -1)
        return ERROR;

    // 1. 删除该顶点的边表
    ArcNode *p = G.vertices[index].firstarc;
    while (p)
    {
        ArcNode *toDelete = p;
        p = p->nextarc;
        free(toDelete);
        count++;
    }

    // 2. 删除其他顶点中指向该顶点的边
    for (int i = 0; i < G.vexnum; i++)
    {
        if (i == index)
            continue;

        ArcNode *p = G.vertices[i].firstarc;
        ArcNode *prev = NULL;

        while (p)
        {
            if (p->adjvex == index)
            {
                ArcNode *toDelete = p;
                if (prev == NULL)
                    G.vertices[i].firstarc = p->nextarc;
                else
                    prev->nextarc = p->nextarc;

                p = p->nextarc;
                free(toDelete);
                count++;
            }
            else
            {
                // 更新索引
                if (p->adjvex > index)
                    p->adjvex--;

                prev = p;
                p = p->nextarc;
            }
        }
    }

    // 3. 删除顶点，左移顶点数组
    for (int i = index; i < G.vexnum - 1; i++)
    {
        G.vertices[i] = G.vertices[i + 1];
    }
    G.vexnum--;
    G.arcnum -= count / 2;

    return OK;
}

status InsertArc(ALGraph &G, KeyType v, KeyType w)
// 在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{

    int v1 = LocateVertex(G, v);
    int v2 = LocateVertex(G, w);

    if (v1 == -1 || v2 == -1 || v1 == v2)
        return ERROR;

    ArcNode *check = G.vertices[v1].firstarc;
    while (check)
    {
        if (check->adjvex == v2)
            return ERROR; // 边已存在
        check = check->nextarc;
    }

    // 插入 v1 -> v2
    ArcNode *p1 = (ArcNode *)malloc(sizeof(ArcNode));
    p1->adjvex = v2;
    p1->nextarc = G.vertices[v1].firstarc;
    G.vertices[v1].firstarc = p1;

    // 插入 v2 -> v1（无向图）
    ArcNode *p2 = (ArcNode *)malloc(sizeof(ArcNode));
    p2->adjvex = v1;
    p2->nextarc = G.vertices[v2].firstarc;
    G.vertices[v2].firstarc = p2;

    G.arcnum++;

    return OK;
}

status DeleteArc(ALGraph &G, KeyType v, KeyType w)
// 在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    int v1 = LocateVertex(G, v);
    int v2 = LocateVertex(G, w);

    if (v1 == -1 || v2 == -1 || v1 == v2)
        return ERROR;

    int count = 0;
    ArcNode *temp = G.vertices[v1].firstarc, *prev = NULL;
    int isDeleted = 0;

    while (temp)
    {
        if (temp->adjvex == v2)
        {
            if (prev == NULL)
            {
                G.vertices[v1].firstarc = temp->nextarc;
                free(temp);
                isDeleted = 1;
            }
            else
            {
                prev->nextarc = temp->nextarc;
                free(temp);
                isDeleted = 1;
            }
            break;
        }
        prev = temp;
        temp = temp->nextarc;
    }

    if (isDeleted == 0)
        return ERROR;

    temp = G.vertices[v2].firstarc, prev = NULL;
    isDeleted = 0;
    while (temp)
    {
        if (temp->adjvex == v1)
        {
            if (prev == NULL)
            {
                G.vertices[VXATape_2].firstarc = temp->nextarc;
                free(temp);
                isDeleted = 1;
            }
            else
            {
                prev->nextarc = temp->nextarc;
                free(temp);
                isDeleted = 1;
            }
            break;
        }
        prev = temp;
        temp = temp->nextarc;
    }

    if (isDeleted == 0)
        return ERROR;

    G.arcnum--;
    return OK;
}