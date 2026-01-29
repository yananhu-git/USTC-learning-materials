#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "hash.h"
Hash creatHashTable(int m){
    Hash h;
    h.capacity=m;
    h.size=0;
    h.base=(HashNode *)malloc(sizeof(HashNode)*h.capacity);
    if(h.base==NULL){
        printf("failed,quit!\n");
        return h;
    }
    for(int i=0;i<h.capacity;i++){
        strcpy(h.base[i].key,NULL_KEY);
        h.base[i].freq=0;
        h.base[i].next=NULL;
    }
    return h;
}
int hashFunction(char *key){
    int n=strlen(key);
    if(n==0){
        printf("the string length is 0,quit!\n");
        return 0;
    }
    int address=(key[0]*100+key[n-1])%41;
    return address;
}
void InsertHash(Hash * h,char *key){
    if(h==NULL||key==NULL||strlen(key)==0){
        printf("insert failed,quit!\n");
        return;
    }
    int add=hashFunction(key);
    HashNode *cur = &(h->base[add]);
    if(strcmp(h->base[add].key,NULL_KEY)==0){
        strcpy(h->base[add].key,key);
        h->base[add].freq=0;
        h->base[add].next=NULL;
        h->size++;
        return;
    }
    while(cur!=NULL){
        if(strcmp(cur->key,key)==0){
            return;
        }
        if(cur->next==NULL){
            break;
        }
        cur=cur->next;
    }
    HashNode *new_Node=(HashNode*)malloc(sizeof(HashNode));
    if(new_Node==NULL){
        printf("insert failed,quit!\n");
        return;
    }
    strcpy(new_Node->key,key);
    new_Node->freq=0;
    new_Node->next=NULL;
    cur->next=new_Node;
    h->size++;
}
double calculateASL(Hash h){
    int total_len=0;
    int count=0;
    for(int i=0;i<h.capacity;i++){
        HashNode *cur=&(h.base[i]);
        if(strcmp(cur->key,NULL_KEY)!=0){
            int current_len=1;
            total_len+=current_len;
            count++;
            cur=cur->next;
            while(cur!=NULL){
                current_len++;
                total_len+=current_len;
                count++;
                cur=cur->next;
            }

        }
    }
    if(count!=h.size){
        printf("the count number is wrong,quit!\n");
        return -1.0;
    }
    double asl=(double)total_len/h.size;
    return asl;
}
void scanFile(Hash *h,const char *file){
    for(int i=0; i<h->capacity; i++){
        HashNode *cur = &(h->base[i]);
        while(cur != NULL){
            if(strcmp(cur->key, NULL_KEY) != 0){
                cur->freq = 0;
            }
            cur = cur->next;
        }
    }
    FILE *fp=fopen(file,"r");
    if(!fp){
        printf("test.cpp cannot open\n");
        return;
    }
    char words[MAX_KEY_LEN];
    int p=0;
    char c;
    while((c=fgetc(fp))!=EOF){
        if((c>64&&c<91)||(c>96&&c<123)||c=='_'||(c<='9'&&c>='0')){
            words[p++]=c;
            words[p]='\0';
        }else{
            if(p>0){
                int add=hashFunction(words);
                HashNode *cur=&(h->base[add]);
                while(cur!=NULL&&strcmp(cur->key,words)!=0){
                    cur=cur->next;
                }
                if(cur!=NULL){
                    cur->freq++;
                }
            }
            p=0;
        }

    }
    fclose(fp);
}
void buildVector(Hash h,int *vector){
    for(int i=0;i<h.capacity;i++){
        vector[i]=0;
    }
    for(int i=0;i<h.capacity;i++){
        HashNode *cur=&(h.base[i]);
        int position=0;
        while(cur!=NULL){
            if(strcmp(cur->key,NULL_KEY)!=0){
                int idx=i+position*100;
                if(idx<h.capacity+500){
                  vector[idx]=cur->freq;
                }
                position++;
            }
            cur=cur->next;
        }
    }
}
double caculateSimilarity(int *vector1,int *vector2,int len){
    long long dot_product=0;
    long long norm1=0;
    long long norm2=0;
    for(int i=0;i<len;i++){
        dot_product+=(long long)vector1[i]*vector2[i];
        norm1+=(long long )vector1[i]*vector1[i];
        norm2+=(long long )vector2[i]*vector2[i];
    }
    if (norm1==0||norm2==0){
        return 0.0;
    }
    double sqrt_norm1=sqrt(norm1);
    double sqrt_norm2=sqrt(norm2);
    return dot_product/(sqrt_norm1*sqrt_norm2);
}
int judgeSimilarity(double similarity){
    if(similarity>=0.85){
        return 1;
    }else{
        return 0;
    }
}

void destroyHashTable(Hash *h) {
    if (h == NULL || h->base == NULL) {
        return;
    }
    for (int i = 0; i < h->capacity; i++) {
        HashNode *cur = h->base[i].next;
        while (cur != NULL) {
            HashNode *temp = cur; 
            cur = cur->next;       
            free(temp);         
        }
    }

  
    h->base = NULL;     
    h->size = 0;       
    h->capacity = 0;   

}
