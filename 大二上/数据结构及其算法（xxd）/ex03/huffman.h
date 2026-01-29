#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <stdio.h>
typedef struct{
    char ch;
    int parent;
    int rchild;
    int lchild;
    int weight;
}HTNode;
typedef struct{
    HTNode *Htree;
    int root;
}HuffmanTree;
extern HuffmanTree HTree;
extern char* HC[1000];
extern int n;
void selectMin(HTNode *HT,int k,int *s1,int *s2);
void CreateHuffman(HuffmanTree *T,int *w,char *c,int n);
void Initialization(void);
void encoding(void);
void decoding(void);
void print(void);
void TreePrinting(void);
#endif