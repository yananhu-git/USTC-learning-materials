#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "hash.h"
int main(){
    FILE *fp=fopen("key.txt","r");
    if(!fp){
        printf("open key.txt failed,quit!\n");
        return 0;
    }
    int m=43;
    Hash h=creatHashTable(m);
    char line[256];
    while(fgets(line,sizeof(line),fp)){
       line[strlen(line)-1]='\0';
       InsertHash(&h,line);
    }
    double a=calculateASL( h);
    printf("asl is %lf\n",a);
    fclose(fp);
    const char *files[]={"test1.cpp","test2.cpp","test3.cpp","test4.cpp"};
    int freq[4][543]={0};
    for(int i=0;i<4;i++){
        for(int j=0;j<543;j++){
            freq[i][j]=0;
        }
    }
    for(int i=0;i<4;i++){
        scanFile(&h,files[i]);
        buildVector(h,freq[i]);
    }
     for(int i=0;i<4;i++){
        for(int j=i+1;j<4;j++){
            double solution=caculateSimilarity(freq[i],freq[j],543);
            printf("test%d and test%d:similarity=%.6lf\n",i+1,j+1,solution);
            if(judgeSimilarity(solution)){
                printf("is similar\n");

            }else{
                printf("is not similar\n");
            }
        }
    }
  destroyHashTable(&h);
    return 0;
    
}