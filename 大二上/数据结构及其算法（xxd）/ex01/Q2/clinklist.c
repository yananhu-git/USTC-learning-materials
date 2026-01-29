/*
an template of solving Josephus problem via circularly linked list for experiment01Q2
presented by xdxu@ustc.edu.cn
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// include head files of your data structure and dependencies here
#include "clinklist.h"

// an template of the problem solver, you can redefine the interface and have your own implementations

int playJosephus(CLinkList* L, int initPasswd) {
    if (L == NULL || L->head == NULL) {
        return -1;
    }
    int m = initPasswd;
    Node* p = L->head;
    Node* prev = NULL;
    if (prev == NULL) {
        prev = L->head;
        while (prev->next != L->head) {
            prev = prev->next;
        }
    }
    while (L->head->next != L->head) {
        for (int i = 1; i < m; i++) {
            prev = p;
            p = p->next;
        }
        printf("%d ", p->data.gameID);
        m = p->data.passwd;
        if (p == L->head) {
            L->head = p->next;
        }
        prev->next = p->next;
        Node* temp = p;
        p = p->next;
        free(temp);
    }

    int winner = L->head->data.gameID;
    free(L->head);
    L->head = NULL;
    return winner;
}
// an template of the main function, you can have your own implementations  
// please do not modify the read-play-check process in the main function,
// and your implementation must support reading input data from a formatted game.txt  
int main(void) {
    CLinkList* L = createCLinkList(); // create an empty clinklist
    GamePlayer player;
    FILE *fp = fopen("game.txt", "r"); // open game.txt
    int count;
    char groupID[10]={0};
    int numPlayers, initPasswd, solution;
    int numGroups = 0, acc = 0, winner;
    if (fp == NULL) {
        printf("open file error, quit!\n");
        return -1;
    }
    while (1) {
    if (fscanf(fp, "%[^,],%d,%d,%d\n", groupID, &numPlayers, &initPasswd, &solution) != 4) {
        break;
    }
    if (groupID[0] != 'g') {
        break;
    }
    printf("game %s started...\n", groupID);
    count = 0;
    while (count < numPlayers) {
        GamePlayer player;
        if (fscanf(fp, "%d,%d\n", &player.gameID, &player.passwd) != 2) {
            break;
        }
        insertTail(L, player);
        count++;
    }
        printf("the initial list is:\n");
        showCLinkList(L); // print the initial Josephus ring
        printf("the losers are in turn:\n");
        winner = playJosephus(L, initPasswd); //  play the game and print the losers
        printf("\nthe winner is: %d.\n", winner); //  print the winner
        clearCLinkList(L); // clear the clinklist for the next group
        if (winner == solution) acc++;
        numGroups++;
        printf("\n");
    }
    fclose(fp);
    destroyCLinkList(&L);
    printf("acc: %d/%d = %.2f\n", acc, numGroups, (double)acc / numGroups); // calculate accuracy

    return 0;
}

                                                                   