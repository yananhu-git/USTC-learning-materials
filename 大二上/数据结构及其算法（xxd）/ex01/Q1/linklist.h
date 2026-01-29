/*
an implementation of linked list for experiment01Q1
presented by xdxu@ustc.edu.cn
*/
#ifndef _LINKLIST_H
#define _LINKLIST_H

typedef char ElemType;
typedef struct LinkNode {
    ElemType data;
    struct LinkNode *next;
} LinkNode, *LinkList;

// create and return an empty linklist with a head node
LinkList createLinkList(void);

// destroy a linklist and free memory
void destroyLinkList(LinkList *L);

// check if the linklist is empty
// if empty return 1, otherwise return 0
int isListEmpty(LinkList L);

// return the length of the linklist
int getLength(LinkList L);

// locate and return the position of the element in the linklist
int locateElem(LinkList L, ElemType e);

// get the element in the linklist at specified position
// if successful return 0, otherwise return -1
int getElem(LinkList L, int i, ElemType *e);

// insert an element at specified position
// if successful return 0, otherwise return -1
int insertElem(LinkList L, int i, ElemType e);

// delete the element at specified position
// if successful return 0, otherwise return -1
int deleteElem(LinkList L, int i, ElemType *e);

// display in turn all the elements in the linklist
void traverseLinkList(LinkList L);

#endif