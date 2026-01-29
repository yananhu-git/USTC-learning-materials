#ifndef CLINKLIST_H
#define CLINKLIST_H

typedef struct {
    int gameID;
    int passwd;
} GamePlayer;

typedef struct Node {
    GamePlayer data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} CLinkList;

CLinkList* createCLinkList();
void insertTail(CLinkList *L, GamePlayer player);
void showCLinkList(CLinkList *L);
void clearCLinkList(CLinkList *L);
void destroyCLinkList(CLinkList **L);


#endif