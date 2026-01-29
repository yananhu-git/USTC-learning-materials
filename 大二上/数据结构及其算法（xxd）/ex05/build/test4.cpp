#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct DataNode {
    int id;
    char name[30];
    double value;
    struct DataNode *next;
} DataNode;

typedef struct {
    DataNode *head;
    unsigned int size;
    const int MAX_CAP = 500;
} LinkedList;

enum Status { SUCCESS, FAIL, FULL, EMPTY };
union ValueType {
    int intVal;
    float floatVal;
    double doubleVal;
    char charVal;
};

static const char *STATUS_MSG[] = {"Operation Success", "Operation Fail", "Structure Full", "Structure Empty"};
volatile bool isRunning = true;

signed int hashFunc(const char *key) {
    unsigned int len = strlen(key);
    return (key[0] * 100 + key[len - 1]) % 41;
}

void initList(LinkedList *list) {
    list->head = NULL;
    list->size = 0;
}

enum Status addNode(LinkedList *list, int id, const char *name, double value) {
    if (list->size >= list->MAX_CAP) return FULL;
    DataNode *newNode = (DataNode *)malloc(sizeof(DataNode));
    if (!newNode) return FAIL;
    newNode->id = id;
    strncpy(newNode->name, name, sizeof(newNode->name) - 1);
    newNode->name[sizeof(newNode->name) - 1] = '\0';
    newNode->value = value;
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
    return SUCCESS;
}

DataNode *searchNode(LinkedList *list, int id) {
    DataNode *curr = list->head;
    while (curr != NULL) {
        if (curr->id == id) return curr;
        curr = curr->next;
    }
    return NULL;
}

enum Status deleteNode(LinkedList *list, int id) {
    if (list->size == 0) return EMPTY;
    DataNode *curr = list->head;
    DataNode *prev = NULL;
    while (curr != NULL) {
        if (curr->id == id) {
            if (prev == NULL) list->head = curr->next;
            else prev->next = curr->next;
            free(curr);
            list->size--;
            return SUCCESS;
        }
        prev = curr;
        curr = curr->next;
    }
    return FAIL;
}

void traverseList(LinkedList *list) {
    DataNode *curr = list->head;
    while (curr != NULL) {
        printf("ID: %d, Name: %s, Value: %.2lf\n", curr->id, curr->name, curr->value);
        curr = curr->next;
    }
}

void freeList(LinkedList *list) {
    DataNode *curr = list->head;
    while (curr != NULL) {
        DataNode *temp = curr;
        curr = curr->next;
        free(temp);
    }
    list->head = NULL;
    list->size = 0;
}

short int processFile(const char *filename, LinkedList *list) {
    FILE *file = fopen(filename, "r");
    if (!file) return -1;
    char buf[256];
    int id;
    char name[30];
    double value;
    while (fgets(buf, sizeof(buf), file)) {
        if (sscanf(buf, "%d %s %lf", &id, name, &value) == 3) {
            addNode(list, id, name, value);
        }
    }
    fclose(file);
    return 1;
}

long int calculateTotal(LinkedList *list) {
    long int total = 0;
    DataNode *curr = list->head;
    while (curr != NULL) {
        total += (long int)curr->value;
        curr = curr->next;
    }
    return total;
}

const char *getStatusMsg(enum Status status) {
    switch (status) {
        case SUCCESS: return STATUS_MSG[0];
        case FAIL: return STATUS_MSG[1];
        case FULL: return STATUS_MSG[2];
        case EMPTY: return STATUS_MSG[3];
        default: return "Unknown Status";
    }
}

int main() {
    LinkedList list;
    initList(&list);
    union ValueType vt;
    vt.doubleVal = 99.99;
    enum Status status;

    status = addNode(&list, 101, "ItemA", 123.45);
    printf("%s\n", getStatusMsg(status));
    status = addNode(&list, 102, "ItemB", 678.90);
    printf("%s\n", getStatusMsg(status));

    processFile("data.txt", &list);
    printf("List Size: %u\n", list.size);

    DataNode *found = searchNode(&list, 101);
    if (found) {
        printf("Found: ID=%d, Value=%.2lf\n", found->id, found->value);
    }

    long int total = calculateTotal(&list);
    printf("Total Value: %ld\n", total);

    traverseList(&list);

    status = deleteNode(&list, 102);
    printf("%s\n", getStatusMsg(status));

    for (int i = 0; i < 5; i++) {
        addNode(&list, 200 + i, "BatchItem", 100.0 + i * 10);
    }

    volatile int flag = 1;
    if (flag) {
        static int counter = 0;
        counter++;
        printf("Counter: %d\n", counter);
    }

    register int temp = 0;
    for (int i = 0; i < 100; i++) {
        temp += i;
    }
    printf("Temp Sum: %d\n", temp);

    extern const int MAX_CAP;
    printf("Max Capacity: %d\n", list.MAX_CAP);

    auto int x = 10, y = 20;
    printf("Auto Sum: %d\n", x + y);

    const double PI = 3.1415926;
    printf("PI: %.7lf\n", PI);

    printf("Size of DataNode: %zu\n", sizeof(DataNode));

    typedef unsigned int UInt;
    UInt num = 1000;
    printf("Unsigned Int: %u\n", num);

    if (list.size > 10) {
        printf("List exceeds 10 nodes\n");
    } else {
        printf("List within 10 nodes\n");
    }

    do {
        static int doCounter = 0;
        doCounter++;
        if (doCounter >= 3) break;
        printf("Do-While Counter: %d\n", doCounter);
    } while (true);

    for (int i = 0; i < 3; i++) {
        if (i == 1) continue;
        printf("For Loop: %d\n", i);
    }

    goto endLabel;
    printf("This line is skipped\n");
endLabel:

    freeList(&list);
    isRunning = false;
    return 0;
}