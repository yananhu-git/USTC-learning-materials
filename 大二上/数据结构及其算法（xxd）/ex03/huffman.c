#include "huffman.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
HuffmanTree HTree={NULL,-1};
char* HC[1000]={NULL};
int n=0;
void selectMin(HTNode *HT,int k,int *s1,int *s2){
    int first=0;
    while(first<=k&&HT[first].parent!=-1){
        ++first;
    }
    if(first>k){
        *s1=*s2=-1;
        return;
    }
    int min1=INT_MAX;
    int min2=INT_MAX;
    *s1=*s2=-1;
    for(int i=first;i<=k;++i){
        if(HT[i].parent==-1){
            if(HT[i].weight<min1){
                min2=min1;
                *s2=*s1;
                min1=HT[i].weight;
                *s1=i;
            }
            else if(HT[i].weight<min2&&i!=*s1){
                min2=HT[i].weight;
                *s2=i;
            }
        }
    }
    if(*s1==*s2){
        *s2=-1;
    }
}
void CreateHuffman(HuffmanTree *T,int *w,char *c,int n){
    int m=n*2-1;
    HTNode *HT=T->Htree=(HTNode *)malloc(m*sizeof(HTNode));
    for(int i=0;i<n;i++){
        HT[i].weight = w[i];
        HT[i].parent = -1;
        HT[i].lchild = -1;
        HT[i].rchild = -1;
        HT[i].ch= c[i];
    }
    for(int i=n;i<m;i++){
        HT[i].weight = 0;
        HT[i].parent = -1;
        HT[i].lchild = -1;
        HT[i].rchild = -1;
    }
    for(int i=n;i<m;i++){
        int s1,s2;
        selectMin(HT,i-1,&s1,&s2);
       if (s1 == -1) {
            printf("Error: No valid node found!\n");
            free(T->Htree);
            T->Htree = NULL;
            return;
        }
        T->Htree[s1].parent = i;
        T->Htree[i].lchild = s1;
        if (s2 != -1) {
            T->Htree[s2].parent = i;
            T->Htree[i].rchild = s2;
            T->Htree[i].weight = T->Htree[s1].weight + T->Htree[s2].weight;
        } else {
            T->Htree[i].rchild = -1;
            T->Htree[i].weight = T->Htree[s1].weight;
        }
    }
    T->root=m-1;
}
void Initialization(void){
    int ch;
    FILE *fp=fopen("CharSet.txt","r");
    if(!fp){
        printf("can not open CharSet.txt,quit!\n");
        return ;
    }
    int capacity=16;
    int *w=(int *)malloc(capacity*sizeof(int));
    char *c=(char *)malloc(capacity*sizeof(char));
    while((ch=fgetc(fp))!=EOF){
        if(ch=='\t') continue;
        if(n==capacity){
            capacity*=2;
            w=(int *)realloc(w, capacity * sizeof(int));
            c=(char *)realloc(c, capacity * sizeof(char));
        }
        c[n]=(char)ch;
        while((ch=fgetc(fp))!=EOF&&(ch==' '||ch=='\t')) {}
        ungetc(ch, fp);
        int weight=0;
        while((ch=fgetc(fp))!=EOF&&ch>='0'&&ch<='9'){
            weight=weight*10+(ch-'0');
        }
        w[n]=weight;
        ++n;
        while (ch != EOF && ch != '\n') ch = fgetc(fp);
        if (ch == EOF) break;
    }
    fclose(fp);
    CreateHuffman(&HTree,w,c,n);
    char codon[1000];
    for(int i=0;i<n;++i){
        int current=i,f,start=999;
        codon[999]='\0';
        while(HTree.Htree[current].parent!=-1){
            f=HTree.Htree[current].parent;
            codon[--start]=(HTree.Htree[f].lchild==current?'0':'1');
            current=f;
        }
        HC[i]=(char*)malloc(1000-start);
        strcpy(HC[i],codon+start);
    }
    FILE *out=fopen("hfmTree.txt","w");
    for( int i=0;i<2*n-1;++i){
        fprintf(out,"%d %d %d %d\n", HTree.Htree[i].weight,HTree.Htree[i].parent,HTree.Htree[i].lchild,HTree.Htree[i].rchild);
    }
        fclose(out);
        free(w);
        free(c);
        printf("Initialization complete.The Huffman tree has been saved to hfmTree.txt.\n");

}
void encoding(void){
    FILE *fin=fopen("ToBeTran.txt","rb");
    if(!fin){
        printf("error,the file is not exist!");
        return;
    }
    FILE *fout = fopen("CodeFile.txt", "wb");
    int ch; 
    while ((ch = fgetc(fin)) != EOF)
    {
        for (int j = 0; j < n; ++j)
            if (HTree.Htree[j].lchild == -1 && HTree.Htree[j].rchild == -1 && HTree.Htree[j].ch == (unsigned char)ch) {
                fputs(HC[j], fout);
                break;
            }
    }

    fclose(fin);
    fclose(fout);
    printf("Encoding completed.The encoded result has been saved in CodeFile.txt.\n");
}
void decoding(void){
    if (HTree.root == -1) {  
        printf("error: Huffman tree is not initialized!\n");
        return;
    }
    FILE *fin=fopen("CodeFile.txt","r");
    if(!fin){
        printf("error,can not open CodeFile.txt!\n");
        return;
    }
    FILE *fout=fopen("TextFile.txt","w");
    if(!fout){
        printf("error,can not create TextFile.txt!\n");
        fclose(fin);
        return;
    }
    int current=HTree.root;
    int ch;
    while((ch=fgetc(fin))!=EOF){
        if(ch=='0'){
            current=HTree.Htree[current].lchild;
        }else if(ch=='1'){
            current=HTree.Htree[current].rchild;
        }else{
            continue;
        }
        if (current == -1) {
            current = HTree.root;
            continue;
        }
        if(HTree.Htree[current].lchild==-1&&HTree.Htree[current].rchild==-1){
            fputc(HTree.Htree[current].ch,fout);
            current=HTree.root;
        }
    }
    fclose(fin);
    fclose(fout);
    printf("Decoding completed.The decoded result has been saved in TextFile.txt.\n");
}
void print(void){
    FILE *fin=fopen("CodeFile.txt","r");
    if(!fin){
        printf("error,can not open CodeFile.txt!\n");
        return;
    }
    FILE *fout = fopen("CodePrint.txt", "w");
    if (!fout) {
        printf("error,cannot create CodePrint.txt!\n");
        fclose(fin);
        return;
    }
    int ch;
    int count=0;
    while((ch=fgetc(fin))!=EOF){
        if(ch==' '||ch=='\n'||ch=='\t'){
            continue;
        }
        putchar(ch);
        fputc(ch,fout);
        count++;
        if(count%50==0){
            putchar('\n');
            fputc('\n',fout);
        }
    }
    if(count%50!=0){
        putchar('\n');
        fputc('\n',fout);
    }
    fclose(fin);
    fclose(fout);
    printf("Print completed. The formatted code has been saved in CodePrint.txt.\n");
}
static void recursivePrint(HTNode *HT,int index,int depth,FILE *fp){
    if(index==-1){
        return;
    }
    for(int i=0;i<depth;i++){
        printf("     ");
        fprintf(fp,"     ");
    }
    if(HT[index].ch!='\0'){
        printf("%c(%d)\n", HT[index].ch, HT[index].weight);
        fprintf(fp, "%c (%d)\n", HT[index].ch, HT[index].weight);
    }else{
        printf("<%d>\n", HT[index].weight);
        fprintf(fp, "<%d>\n", HT[index].weight);
    }
    recursivePrint(HT,HT[index].lchild,depth+1,fp);
    recursivePrint(HT,HT[index].rchild,depth+1,fp);
} 
void TreePrinting(void){
    FILE *fp=fopen("TreePrint.txt","w");
     if(!fp){
        printf("error,can not open TreePrint.txt!\n");
        return;
    }
    recursivePrint(HTree.Htree,HTree.root,0,fp);
    fclose(fp);
    printf("Tree printing completed! Tree saved to TreePrint.txt.\n");
}


