/*
an implementation of linked list for experiment01Q1
presented by xdxu@ustc.edu.cn
*/
#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

// create and return an empty linklist with a head node
LinkList createLinkList(void) {
    LinkList head=NULL;
    head = (LinkList) malloc(sizeof(LinkNode));
    if (head==NULL) return NULL;
    return head;
}

// destroy a linklist and free memory
void destroyLinkList(LinkList *L) {
    LinkNode *p;
    ElemType e;
    if (*L==NULL) return;
    while (!isListEmpty(*L)) {
        deleteElem(*L, 1, &e); // delete the first node
    }
    free(*L); // free the head node
    *L = NULL;
    return;
}

// check if the linklist is empty
// if empty return 1, otherwise return 0
int isListEmpty(LinkList L) {
    return (L->next==NULL);
}

// return the length of the linklist
int getLength(LinkList L) {
    LinkNode *p;
    int k = 0;
    if (L->next==NULL) return k;
    p = L->next;
    while (p) {
        p = p->next;
        k++;
    }
    return k;
}

// locate and return the position of the element in the linklist
int locateElem(LinkList L, ElemType e) {
    int j = 1;
    LinkNode *p = L;
    if (L->next==NULL) return 0;
    p = L->next;
    while (p && p->data != e) {
        p = p->next;
        j++;
    }
    if (p) return j;
    else return 0;
}

// get the element in the linklist at specified position
// if successful return 0, otherwise return -1
int getElem(LinkList L, int i, ElemType *e) {
    int j = 1;
    LinkNode *p ;
    if (L->next==NULL) return -1;
    if (i<1 || i>getLength(L)) {
        printf("getItem: invalid i, quit!\n");
        return -1;
    }
    p = L->next;
    while (j<i && p) {
        p = p->next;
        j++;
    }
    if (p) {
        *e = p->data;
        return 0;
    } else
        return -1;
}

// insert an element at specified position
// if successful return 0, otherwise return -1
int insertElem(LinkList L, int i, ElemType e) {
    int j = 0;
    LinkNode *p, *s;
    int len = getLength(L);
    if(L==NULL) return -1;
    if (i<1 || i>getLength(L)+1) {
        printf("insertItem: invalid i, quit!\n");
        return -1;
    }
    p = L;
   while (j<i-1&&p) {
        p = p->next;
        j++;
    }
    s = (LinkList)malloc(sizeof(LinkNode));
    s->data = e;
    if (i==1) {
        s->next = L->next; // insert as the first node
        L->next = s;
    } else {
        s->next = p->next;
        p->next = s;
    }
    return 0;
}

// delete the element at specified position
// if successful return 0, otherwise return -1
int deleteElem(LinkList L, int i, ElemType *e) {
    int j = 1;
    LinkNode *p, *q;
    if (i<1 || i>getLength(L)) {
        printf("deleteItem: invalid i, quit!\n");
        return -1;
    }
    p = L->next;
    while (j<i-1) {
        p = p->next;
        j++;
    }
    if (i==1) {
        q = L->next; // delete the first node
        L->next = q->next;
        *e = q->data;
    } else {
        q = p->next;
        p->next = q->next;
        *e = q->data;
    }
    free(q);
    return 0;
}

// display in turn all the elements in the linklist
void traverseLinkList(LinkList L) {
    LinkNode *p;
    if (L->next == NULL) return;
    p = L->next;
    while (p) {
        printf("%c ", p->data);
        p = p->next;
    }
    printf("\n");
}
