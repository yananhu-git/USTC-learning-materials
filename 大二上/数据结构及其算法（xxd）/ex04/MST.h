#ifndef _MAT_H_
#define _MAT_H_
#define MAX_VEX 1000
typedef struct ArcNode{
    int adjvex;
    double weight;
    struct ArcNode *next;
}ArcNode;
typedef struct VNode{
    int data;
    struct ArcNode *firstarc;
}VNode;
typedef struct{
    VNode vertices[MAX_VEX];
    int n,e;
}Graph;
typedef struct{
    int data[MAX_VEX];
    int front;
    int rear;
}Queue;
void InitQueue(Queue*q);
void createGraph(Graph *G,int *n,int *e);
void DFS(Graph G,int n);
void BFS(Graph G,int n);
void EnQueue(Queue*q,int vertex);
void DeQueue(Queue*q,int *vertex);
void Prim(Graph G,int n,int e);







#endif