#include <stdio.h>
#include <stdlib.h>
#include "clinklist.h"
CLinkList* createCLinkList() {
    CLinkList* list = (CLinkList*)malloc(sizeof(CLinkList));
    if (list == NULL) {
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    return list;
}

void showCLinkList(CLinkList * L){
    if(L==NULL || L->head == NULL){
        printf("The list is empty!\n");
        return;
    }
    Node *p=L->head;

    do{
        printf("(%d,%d) ",p->data.gameID,p->data.passwd);
        p=p->next;
    }while(p!=L->head);
    printf("\n");
}

void clearCLinkList(CLinkList * L){
    if(L==NULL|| L->head == NULL){
        return;
    }
    Node *p=L->head;
    do{
        Node* temp=p;
        p=p->next;
        free(temp);
    }while(p!=L->head);
    L->head=NULL;
}

void destroyCLinkList(CLinkList ** L){
    if(L==NULL||*L==NULL){
        return;
    }
    clearCLinkList(*L);
    free(*L);
    *L=NULL;
}

void insertTail(CLinkList *L, GamePlayer player) {
    if (L == NULL) {
        return;
}
    Node *q = (Node*)malloc(sizeof(Node));
    if (q == NULL) {
        exit(EXIT_FAILURE);
    }
    q->data = player;
    if (L->head == NULL) {
        L->head = q;
        q->next = q;
    } else {
        Node *p = L->head;
        while (p->next != L->head) {
            p = p->next;
        }
        p->next = q;
        q->next = L->head;
    }
}
