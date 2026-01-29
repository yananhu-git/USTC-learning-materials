/*
an implementation of linked list for experiment01Q1
presented by xdxu@ustc.edu.cn
*/
#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

int main(void) {            
    LinkList L;
    ElemType e;
    int i;
    char x;

    // 创建一个空的链表
    printf("1. create an empty linked list...");
    L = createLinkList();
    if (L==NULL) {
        printf("failed!\n");
        return -1;
    } else  {
        printf("success!\n");
    }

    //依次输入6个元素并插入链表
    printf("2. insert elements {'q','w','e','r','t','y'} in turn: ");
    for (i=1; i<=6; i++){
        scanf(" %c", &x);
        if (insertElem(L, i, x)==0) printf("\tinsert %c at %d success!\n", x, i);
    }

    //输出单链表
    printf("3. traverse the linked list: ");
    traverseLinkList(L);

    //获取单链表长度，并判断单链表是否为空
    printf("4. the list has a length of %d, ", getLength(L));    
    if (isListEmpty(L))
        printf("i.e., %s\n", "empty!");
    else
        printf("i.e., %s\n", "not empty.");

    //查找第i个元素
    printf("5. search for the element at position: ");
    scanf("%d", &i); 
    while(getchar()!='\n');
    if(getElem(L, i, &e)==0)
        printf("\tthe %dth element in the list is: %c\n", i, e);

    //插入元素
    printf("6. insert 'f' at position 4...");
    if (insertElem(L, 4, 'f')==0)
        printf("success!\n");
    else 
        printf("fail!\n");    
    printf("\tnow the linked list is: ");
    traverseLinkList(L);
    
    //查询元素的位序
    printf("7. the element for search is: ");
    scanf("%c", &x);
    printf("\tthe element %c in the list is at position %d\n", x, locateElem(L, x));

    //删除元素
    printf("8. delete the 3rd element in the list...");
    if (deleteElem(L, 3, &e)==0)
        printf("success!\n");
    else
        printf("fail!\n");
    printf("\tnow the linked list is: ");
    traverseLinkList(L);

    //销毁链表
    printf("9. destroy the linked List...");
    destroyLinkList(&L);
    if (L==NULL) printf("success!\n");
    
    return 0;
}

