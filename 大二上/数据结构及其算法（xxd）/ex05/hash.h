#ifndef  _HASH_H_
#define  _HASH_H_
#define MAX_KEY_LEN 100
#define NULL_KEY ""
typedef struct HashNode{
    char key[MAX_KEY_LEN];
    int freq;
    struct HashNode *next;
}HashNode;
typedef struct Hash{
    HashNode *base;
    int size;
    int capacity;
}Hash;
Hash creatHashTable(int capacity);
int hashFunction(char *key);
void InsertHash(Hash *h,char *key);
double calculateASL(Hash h);
void scanFile(Hash *h,const char *file);
void buildVector(Hash h,int *vector);
double caculateSimilarity(int *vector1,int *vector2,int len);
int judgeSimilarity(double similarity);
void destroyHashTable(Hash *h);





#endif