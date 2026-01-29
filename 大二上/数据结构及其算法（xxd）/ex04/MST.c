#include <stdio.h>
#include <stdlib.h>
#include "MST.h"
#include <float.h> 
int visited[MAX_VEX] = {0};
void createGraph(Graph *G,int *n,int *e){
    FILE *fp=fopen("data.txt","r");
    if(!fp){
        printf("can not open data.txt,quit!");
        return;
    }
    fscanf(fp,"%d %d\n",n,e);
    for(int i=0;i<*n;i++){
        G->vertices[i].data=i;
        G->vertices[i].firstarc=NULL;
    }
    for(int i=0;i<*e;i++){
        int a,b;
        double w;
        fscanf(fp,"%d  %d  %lf\n",&a,&b,&w);
        ArcNode *p1=(ArcNode *)malloc(sizeof(ArcNode));
        p1->adjvex=b;
        p1->weight=w;
        p1->next = NULL; 
        ArcNode *temp = G->vertices[a].firstarc;
        ArcNode *prev = NULL;
        while (temp != NULL && temp->adjvex < b) {
            prev = temp;
            temp = temp->next;
        }
        if (prev == NULL) {
            p1->next = G->vertices[a].firstarc;
            G->vertices[a].firstarc = p1;
        } else { 
            p1->next = temp;
            prev->next = p1;
        }
        ArcNode *p2=(ArcNode *)malloc(sizeof(ArcNode));
        p2->adjvex=a;
        p2->weight=w;
        p2->next =NULL; 
         temp = G->vertices[b].firstarc;
        prev = NULL;
        while (temp != NULL && temp->adjvex < a) {
            prev = temp;
            temp = temp->next;
        }
        if (prev == NULL) { 
            p2->next = G->vertices[b].firstarc;
            G->vertices[b].firstarc = p2;
        } else { 
            p2->next = temp;
            prev->next = p2;
        }      
    }
    fclose(fp);
}
void DFS_Core(Graph G, int i, FILE *out, int *isFirst){
    visited[i] = 1;
    if (*isFirst) {
        fprintf(out, "%d", i);
        *isFirst = 0;
    } else {
        fprintf(out, " %d", i);
    }
    ArcNode *p = G.vertices[i].firstarc;
    while (p) {
        if (!visited[p->adjvex]) {
            DFS_Core(G, p->adjvex, out, isFirst);
        }
        p = p->next;
    }
}
void DFS(Graph G, int n) {
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }
    FILE *out = fopen("dfs.txt", "w");
    if (!out) {
        printf("can not open dfs.txt,quit!");
        return;
    }
    
    int count = 0;  
   
    fprintf(out, "total connected components: ");
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            count++;
            int isFirst = 1;
            
            fprintf(out, "\ncomponent %d: ", count);
            DFS_Core(G, i, out, &isFirst);
        }
    }
    
   
    fseek(out, 0, SEEK_SET);
    fprintf(out, "total connected components: %d", count);
    
    fclose(out);
}
void InitQueue(Queue*q){
    q->front=0;
    q->rear=0;
}
void EnQueue(Queue*q,int vertex){
    if((q->rear+1)%MAX_VEX==q->front){
        printf("the queue is full,quit!\n");
        return;
    }
    q->data[q->rear]=vertex;
    q->rear = (q->rear + 1) % MAX_VEX;
}
int IsQueueEmpty(Queue *q){
    return q->rear==q->front;
}
void DeQueue(Queue*q,int *vertex){
    if(IsQueueEmpty(q)){
        printf("the queue is empty,quit!\n");
        return;
    }
    *vertex=q->data[q->front];
    q->front=(q->front+1)%MAX_VEX;
}
void BFS(Graph G,int n){
    for(int i=0;i<n;i++){
        visited[i]=0;
    }
    int isFirst=1;
    FILE *out=fopen("bfs.txt","w");
    if(!out){
        printf("can not open bfs.txt,quit!\n");
        return;
    }
    int count=0;
    fprintf(out, "total connected components: ");
    Queue*q=(Queue*)malloc(sizeof(Queue));
    InitQueue(q);
    for(int i=0;i<n;i++){
        if(!visited[i]){
            count++;
            fprintf(out, "\ncomponent %d: ", count);
            visited[i]=1;
            if(isFirst){
                fprintf(out,"%d",i);
                isFirst=0;
            }else{
                fprintf(out," %d",i);
            }
            EnQueue(q,i);
            while(!IsQueueEmpty(q)){
                int current;
                DeQueue(q,&current);
                ArcNode *p=G.vertices[current].firstarc;
                while(p){
                    if(!visited[p->adjvex]){
                        visited[p->adjvex]=1;
                        fprintf(out," %d",p->adjvex);
                        EnQueue(q,p->adjvex);
                    }
                    p=p->next;
                }
                
            }
        }
    }
    fseek(out, 0, SEEK_SET);
    fprintf(out, "total connected components: %d", count);
    free(q);
    fclose(out);
}
void Prim(Graph G,int n,int e){
    double min;
    int minIndex;
    int isAdded[MAX_VEX]={0};
    ArcNode *lowcost[MAX_VEX]={NULL};
    VNode *adjVex[MAX_VEX]={NULL};
    double mstTotalWeight = 0.0;
    isAdded[0]=1;
    ArcNode *temp=G.vertices[0].firstarc;
    while(temp!=NULL){
        lowcost[temp->adjvex]=temp;
        adjVex[temp->adjvex]=&G.vertices[0];
        temp=temp->next;
    }
    for(int i=0;i<n-1;i++){
        min=DBL_MAX;
        minIndex=-1;
        for(int k=0;k<n;k++){
            if(lowcost[k]!=NULL&&isAdded[k]==0&&lowcost[k]->weight<min){
                min=lowcost[k]->weight;
                minIndex=k;
            }
        }
        if(minIndex==-1){
            printf("graph is disconnected,quit!\n");
            printf("MST total weight: 0.0 (invalid)\n");
            return;
        }
        isAdded[minIndex]=1;
        mstTotalWeight += min;
        printf("(%d,%d)\n",adjVex[minIndex]->data,G.vertices[minIndex].data);
        temp=G.vertices[minIndex].firstarc;
        while(temp!=NULL){
            if(isAdded[temp->adjvex]==0){
                if(lowcost[temp->adjvex]==NULL||temp->weight<lowcost[temp->adjvex]->weight){
                    lowcost[temp->adjvex]=temp;
                    adjVex[temp->adjvex]=&G.vertices[minIndex];
                }
            }
            temp=temp->next;
        }
    }
     printf("total weight: %.2lf\n", mstTotalWeight);
}