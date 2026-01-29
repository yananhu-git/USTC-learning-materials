#include <stdio.h>
#include <stdlib.h>
#include "MST.h"
#include <float.h> 
int main(){
    int n=0,e=0;
    Graph G;
    createGraph(&G,&n,&e);
    BFS(G,n);
    DFS(G, n);
    Prim(G,n,e);
    return 0;


}