#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <queue>

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
    int adjvex = -3;         // 顶点位置编号
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

typedef struct
{
    struct
    {
        ALGraph G;
        char GName[31];
    } elem[MAX_GRAPH_NUM];
    int GNum = 0;
} Gs;

void visit(VertexType v)
{
    printf(" %d,%s ", v.key, v.others);
}

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

status CreateGraph(ALGraph &G, VertexType V[], KeyType VR[][2])
{
    if (V[0].key == -1)
        return ERROR;

    G.vexnum = G.arcnum = 0;
    G.kind = UDG;

    // 插入顶点
    for (int i = 0; V[i].key != -1; ++i)
    {
        if (LocateVertex(G, V[i].key) != -1 || i >= 20)
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
    if (G.vexnum == 0)
        return INFEASIBLE;
    int location = -1, count = 0, i;
    for (i = 0; i < G.vexnum; i++)
    {
        if (value.key == G.vertices[i].data.key && u != G.vertices[i].data.key)
            return -2;
        if (u == G.vertices[i].data.key)
            location = i;
    }
    if (location == -1)
        return ERROR;
    G.vertices[location].data = value;
    return OK;
}

status FirstAdjVex(ALGraph G, KeyType u)
// 根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回ERROR；
{
    if (G.vexnum == 0)
        return INFEASIBLE;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == u)
            return G.vertices[i].firstarc->adjvex + 1;
    }
    return ERROR;
}

status NextAdjVex(ALGraph G, KeyType v, KeyType w)
// v对应G的一个顶点,w对应v的邻接顶点；操作结果是返回v的（相对于w）下一个邻接顶点的位序；如果w是最后一个邻接顶点，或v、w对应顶点不存在，则返回-1。
{
    if (G.vexnum == 0)
        return INFEASIBLE;
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
                return -2;
            else
                return temp->nextarc->adjvex + 1;
        }
    }
    return ERROR;
}

status InsertVex(ALGraph &G, VertexType value)
// 在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    if (G.vexnum == MAX_VERTEX_NUM)
        return INFEASIBLE;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == value.key)
            return ERROR;
    }
    G.vertices[G.vexnum++].data = value;
    G.vertices[G.vexnum - 1].firstarc = NULL;
    return OK;
}

status DeleteVex(ALGraph &G, KeyType v)
{
    if (G.vexnum == 1)
        return INFEASIBLE;

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
    if (G.vexnum == 0)
        return INFEASIBLE;
    int v1 = LocateVertex(G, v);
    int v2 = LocateVertex(G, w);

    if (v1 == -1 || v2 == -1 || v1 == v2)
        return ERROR;

    ArcNode *check = G.vertices[v1].firstarc;
    while (check)
    {
        if (check->adjvex == v2)
            return -2; // 弧已存在
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
    if (G.vexnum == 0)
        return INFEASIBLE;
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
        return -2;

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
        return -2;

    G.arcnum--;
    return OK;
}

void DFS(ALGraph &G, int v, bool visited[], int flag)
{
    if (flag == 1)
        visit(G.vertices[v].data);
    visited[v] = true;

    for (ArcNode *p = G.vertices[v].firstarc; p != NULL; p = p->nextarc)
    {
        int w = p->adjvex;
        if (!visited[w])
            DFS(G, w, visited, flag);
    }
}

status DFSTraverse(ALGraph &G)
// 对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    using namespace std;
    if (G.vexnum == 0)
    {
        cout << "图为空！";
        return INFEASIBLE;
    }

    bool visited[MAX_VERTEX_NUM] = {false}; // 初始化所有顶点未访问

    cout << "深度优先搜索遍历结果为：" << endl;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (!visited[i])
            DFS(G, i, visited, 1);
    }

    return OK;
}

status BFSTraverse(ALGraph &G)
// 对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    using namespace std;
    if (G.vexnum == 0)
    {
        cout << "图为空！";
        return INFEASIBLE;
    }

    cout << "广度优先搜索遍历结果为：" << endl;
    bool visited[MAX_VERTEX_NUM] = {false};
    int quene[MAX_VERTEX_NUM + 1];
    int front = 0, rear = 0;
    int target;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (visited[i] == false)
        {
            quene[rear++] = i;
            visited[i] = true;

            while (front < rear)
            {
                target = quene[front++];
                visit(G.vertices[target].data);
                ArcNode *temp = G.vertices[target].firstarc;
                while (temp)
                {
                    if (visited[temp->adjvex] == false)
                    {
                        quene[rear++] = temp->adjvex;
                        visited[temp->adjvex] = true;
                    }
                    temp = temp->nextarc;
                }
            }
        }
    }

    return OK;
}

/*status SaveGraph(ALGraph G, char FileName[])
// 将图的数据写入到文件FileName中
{
    if (G.vexnum == 0)
        return INFEASIBLE;

    FILE *fp = fopen(FileName, "w");
    if (fp == NULL)
        return ERROR;

    fprintf(fp, "%d\n", G.kind);
    for (int i = 0; i < G.vexnum; i++)
    {
        fprintf(fp, "%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);
    }
    fprintf(fp, "-1 null\n");

    for (int i = 0; i < G.vexnum; i++)
    {
        ArcNode *temp = G.vertices[i].firstarc;

        ArcNode* stack[MAX_VERTEX_NUM * (MAX_VERTEX_NUM - 1) / 2];
        int top=-1;
        while(temp){
            stack[++top]=temp;
            temp=temp->nextarc;
        }

        while (top>=0)
        {
            temp=stack[top--];
            if (i < temp->adjvex)
            {
                fprintf(fp, "%d %d ", G.vertices[i].data.key, G.vertices[temp->adjvex].data.key);
            }
        }
    }
    fprintf(fp, "-1 -1\n");
    fclose(fp);

    return OK;
}*/

/*status LoadGraph(ALGraph &G, char FileName[])
// 读入文件FileName的图数据，创建图的邻接表
{
    if (G.vexnum != 0)
        return INFEASIBLE;

    FILE *fp = fopen(FileName, "r");
    if (fp == NULL)
        return ERROR;

    fscanf(fp, "%d", &G.kind);
    int i = 0;
    VertexType V[MAX_VERTEX_NUM + 1];
    KeyType VR[MAX_VERTEX_NUM * (MAX_VERTEX_NUM - 1) / 2 + 1][2];
    do
    {
        fscanf(fp, "%d %s ", &V[i].key, V[i].others);
        if (V[i].key == -1)
            break;
        i++;
    } while (i < MAX_VERTEX_NUM);

    i = 0;
    do
    {
        fscanf(fp, "%d %d ", &VR[i][0], &VR[i][1]);
        if (VR[i][0] == -1)
            break;
        i++;
    } while (1);

    CreateGraph(G, V, VR);

    fclose(fp);
    return OK;
}*/

status SaveGraph(ALGraph G, char FileName[])
// 将图的数据写入到文件FileName中
{
    if (G.vexnum == 0)
        return INFEASIBLE;

    FILE *fp = fopen(FileName, "w");
    if (fp == NULL)
        return ERROR;

    fprintf(fp, "%d %d %d\n", G.kind, G.vexnum, G.arcnum);

    for (int i = 0; i < G.vexnum; i++)
    {
        fprintf(fp, "%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);
        ArcNode *temp = G.vertices[i].firstarc;
        while (temp)
        {
            fprintf(fp, "%d ", temp->adjvex);
            temp = temp->nextarc;
        }
        fprintf(fp, "-1 \n");
    }

    fclose(fp);
    return OK;
}

status LoadGraph(ALGraph &G, char FileName[])
// 读入文件FileName的图数据，创建图的邻接表
{
    if (G.vexnum != 0)
        return INFEASIBLE;

    FILE *fp = fopen(FileName, "r");
    if (fp == NULL)
        return ERROR;

    fscanf(fp, "%d %d %d", &G.kind, &G.vexnum, &G.arcnum);
    int arc;

    for (int i = 0; i < G.vexnum; i++)
    {
        fscanf(fp, "%d %s ", &G.vertices[i].data.key, G.vertices[i].data.others);

        fscanf(fp, "%d ", &arc);
        if (arc == -1)
            G.vertices[i].firstarc = NULL;
        else
        {
            ArcNode *temp = (ArcNode *)malloc(sizeof(ArcNode));
            temp->adjvex = arc;
            temp->nextarc = NULL;
            G.vertices[i].firstarc = temp;
            while (1)
            {
                fscanf(fp, "%d ", &arc);
                if (arc == -1)
                    break;
                ArcNode *newNode = (ArcNode *)malloc(sizeof(ArcNode));
                newNode->adjvex = arc;
                newNode->nextarc = NULL;
                temp->nextarc = newNode;
                temp = newNode;
            }
        }
    }

    fclose(fp);
    return OK;
}

void kBFS(ALGraph G, int start, bool target[], int k)
{
    using namespace std;
    queue<pair<int, int>> q; // pair<顶点下标, 当前层数>
    bool visited[MAX_VERTEX_NUM] = {false};

    q.push({start, 0});
    visited[start] = true;

    while (!q.empty())
    {
        auto [u, depth] = q.front();
        q.pop();

        // 跳过自己
        if (depth > 0 && depth < k)
        {
            visit(G.vertices[u].data); // 打印或处理该顶点
            target[u] = true;
        }

        if (depth >= k - 1)
            continue;

        for (ArcNode *p = G.vertices[u].firstarc; p; p = p->nextarc)
        {
            int v = p->adjvex;
            if (!visited[v])
            {
                visited[v] = true;
                q.push({v, depth + 1});
            }
        }
    }
}

status VerticesSetLessThanK(ALGraph G, KeyType v, int k)
{
    if (G.vexnum == 0)
        return INFEASIBLE;

    bool target[MAX_VERTEX_NUM] = {false};
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == v)
        {
            using namespace std;
            cout << "与顶点v距离小于k的顶点：" << endl;
            kBFS(G, i, target, k + 1);
            return OK;
        }
    }
    return ERROR;
}

status ShortestPathLength(ALGraph G, KeyType v, KeyType w)
{
    if (G.vexnum == 0)
        return INFEASIBLE;

    int start = -1, end = -1;

    // 查找 key 对应的顶点编号
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == v)
            start = i;
        if (G.vertices[i].data.key == w)
            end = i;
    }

    if (start == -1 || end == -1)
        return -2; // 起点或终点不存在

    if (start == end)
        return 0; // 起点和终点相同，路径长度为0

    // 广度优先搜索 BFS
    bool visited[MAX_VERTEX_NUM] = {false};
    int distance[MAX_VERTEX_NUM] = {0}; // 存储距离
    int queue[MAX_VERTEX_NUM];
    int front = 0, rear = 0;

    visited[start] = true;
    queue[rear++] = start;

    while (front < rear)
    {
        int u = queue[front++];
        ArcNode *p = G.vertices[u].firstarc;
        while (p)
        {
            int v = p->adjvex;
            if (!visited[v])
            {
                visited[v] = true;
                distance[v] = distance[u] + 1;
                if (v == end)
                    return distance[v]; // 找到终点，返回距离
                queue[rear++] = v;
            }
            p = p->nextarc;
        }
    }

    return -3; // 无法到达
}

status ConnectedComponentsNums(ALGraph G)
{
    if (G.vexnum == 0)
        return INFEASIBLE;

    bool visited[MAX_VERTEX_NUM] = {false}; // 初始化所有顶点未访问
    int count = 0;

    for (int i = 0; i < G.vexnum; i++)
    {
        if (!visited[i])
        {
            DFS(G, i, visited, 0);
            count++;
        }
    }

    return count;
}

ALGraph CopyGraph(ALGraph G)
{
    ALGraph newG;
    newG.vexnum = G.vexnum;
    newG.arcnum = G.arcnum;
    newG.kind = G.kind;

    // 复制顶点数据
    for (int i = 0; i < G.vexnum; i++)
    {
        newG.vertices[i].data = G.vertices[i].data;
        newG.vertices[i].firstarc = NULL;

        ArcNode *arc = G.vertices[i].firstarc;
        ArcNode *last = NULL;

        while (arc)
        {
            ArcNode *newNode = (ArcNode *)malloc(sizeof(ArcNode));
            newNode->adjvex = arc->adjvex;
            newNode->nextarc = NULL;

            if (last == NULL)
                newG.vertices[i].firstarc = newNode;
            else
                last->nextarc = newNode;

            last = newNode;
            arc = arc->nextarc;
        }
    }

    return newG;
}

status AddGraph(Gs &Graphs, ALGraph G, char GraphName[])
{
    if (G.vexnum == 0)
        return INFEASIBLE;
    if (Graphs.GNum == MAX_GRAPH_NUM)
        return ERROR;
    for (int i = 0; i < Graphs.GNum; i++)
    {
        if (strcmp(Graphs.elem[i].GName, GraphName) == 0)
            return -2; // 已存在同名图，拒绝添加
    }

    Graphs.elem[Graphs.GNum].G = CopyGraph(G);
    strcpy(Graphs.elem[Graphs.GNum].GName, GraphName);
    Graphs.GNum++;
    return OK;
}

status GetGraph(Gs Graphs, ALGraph &G, char GraphName[])
{
    if (Graphs.GNum == 0)
        return INFEASIBLE;
    for (int i = 0; i < Graphs.GNum; i++)
    {
        if (strcmp(Graphs.elem[i].GName, GraphName) == 0)
        {
            G = CopyGraph(Graphs.elem[i].G);
            return OK;
        }
    }
    return ERROR;
}

status DeleteGraph(Gs &Graphs, char GraphName[])
{
    if (Graphs.GNum == 0)
        return INFEASIBLE;
    for (int i = 0; i < Graphs.GNum; i++)
    {
        if (strcmp(Graphs.elem[i].GName, GraphName) == 0)
        {
            DestroyGraph(Graphs.elem[i].G);
            for (int j = i; j < Graphs.GNum - 1; j++)
            {
                Graphs.elem[j] = Graphs.elem[j + 1];
            }
            Graphs.GNum--;
            return OK;
        }
    }
    return ERROR;
}

void DestroyAll(Gs &Graphs, ALGraph &G)
{
    for (int i = 0; i < Graphs.GNum; i++)
    {
        DestroyGraph(Graphs.elem[i].G);
    }
    Graphs.GNum = 0;
    DestroyGraph(G);
}