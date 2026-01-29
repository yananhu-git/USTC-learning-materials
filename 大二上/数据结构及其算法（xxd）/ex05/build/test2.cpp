#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef struct User {
    unsigned int uid;
    char username[20];
    char password[20];
    float score;
    struct User *prev;
    struct User *next;
} User;

typedef struct {
    User *head;
    User *tail;
    int count;
} DoublyLinkedList;

enum UserRole { ADMIN, USER, GUEST };
union ConfigData {
    int intVal;
    float floatVal;
    bool boolVal;
    char strVal[50];
};

static DoublyLinkedList userList;
volatile bool isServerRunning = true;
const int MAX_USERS = 200;
extern const char *DEFAULT_PASS = "123456";

signed char initUserList() {
    userList.head = NULL;
    userList.tail = NULL;
    userList.count = 0;
    return 1;
}

enum Status { OK, ERROR, DUPLICATE, OUT_OF_MEMORY };
const char *getStatusStr(enum Status status) {
    switch (status) {
        case OK: return "OK";
        case ERROR: return "Error";
        case DUPLICATE: return "Duplicate Entry";
        case OUT_OF_MEMORY: return "Out of Memory";
        default: return "Unknown Status";
    }
}

User *createUser(unsigned int uid, const char *username, const char *password, float score) {
    User *user = (User *)malloc(sizeof(User));
    if (!user) return NULL;
    user->uid = uid;
    strncpy(user->username, username, sizeof(user->username) - 1);
    user->username[sizeof(user->username) - 1] = '\0';
    strncpy(user->password, password, sizeof(user->password) - 1);
    user->password[sizeof(user->password) - 1] = '\0';
    user->score = score;
    user->prev = NULL;
    user->next = NULL;
    return user;
}

enum Status addUser(unsigned int uid, const char *username, const char *password, float score) {
    if (userList.count >= MAX_USERS) return OUT_OF_MEMORY;
    if (searchUser(uid)) return DUPLICATE;
    User *newUser = createUser(uid, username, password, score);
    if (!newUser) return OUT_OF_MEMORY;
    if (!userList.head) {
        userList.head = newUser;
        userList.tail = newUser;
    } else {
        newUser->prev = userList.tail;
        userList.tail->next = newUser;
        userList.tail = newUser;
    }
    userList.count++;
    return OK;
}

User *searchUser(unsigned int uid) {
    User *curr = userList.head;
    while (curr) {
        if (curr->uid == uid) return curr;
        curr = curr->next;
    }
    return NULL;
}

enum Status updateScore(unsigned int uid, float newScore) {
    User *user = searchUser(uid);
    if (!user) return ERROR;
    user->score = newScore;
    return OK;
}

void deleteAllUsers() {
    User *curr = userList.head;
    while (curr) {
        User *temp = curr;
        curr = curr->next;
        free(temp);
    }
    userList.head = NULL;
    userList.tail = NULL;
    userList.count = 0;
}

long long calculateTotalScore() {
    long long total = 0;
    User *curr = userList.head;
    while (curr) {
        total += (long long)curr->score;
        curr = curr->next;
    }
    return total;
}

short int importUsers(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return -1;
    char buf[256];
    unsigned int uid;
    char username[20], password[20];
    float score;
    while (fgets(buf, sizeof(buf), file)) {
        if (sscanf(buf, "%u %s %s %f", &uid, username, password, &score) == 4) {
            addUser(uid, username, password, score);
        }
    }
    fclose(file);
    return 1;
}

void exportUsers(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) return;
    User *curr = userList.head;
    while (curr) {
        fprintf(file, "%u %s %s %.2f\n", curr->uid, curr->username, curr->password, curr->score);
        curr = curr->next;
    }
    fclose(file);
}

typedef long long BigInt;
BigInt generateRandomId() {
    srand((unsigned int)time(NULL));
    return (BigInt)(rand() % 1000000 + 100000);
}

int main() {
    initUserList();
    union ConfigData config;
    config.boolVal = true;
    enum UserRole role = USER;

    enum Status status = addUser(1001, "Alice", "alice123", 95.5f);
    printf("Add Alice: %s\n", getStatusStr(status));
    status = addUser(1002, "Bob", "bob456", 88.0f);
    printf("Add Bob: %s\n", getStatusStr(status));

    importUsers("users.txt");
    printf("Total Users: %d\n", userList.count);

    User *found = searchUser(1001);
    if (found) {
        printf("Found User: %s, Score: %.2f\n", found->username, found->score);
    }

    status = updateScore(1002, 92.3f);
    printf("Update Bob's Score: %s\n", getStatusStr(status));

    long long totalScore = calculateTotalScore();
    printf("Total Score of All Users: %lld\n", totalScore);

    exportUsers("updated_users.txt");

    for (int i = 0; i < 10; i++) {
        BigInt uid = generateRandomId();
        char uname[20];
        sprintf(uname, "User%d", i + 10);
        addUser((unsigned int)(uid % 10000), uname, DEFAULT_PASS, 60.0f + rand() % 40);
    }

    volatile int runCount = 0;
    while (isServerRunning && runCount < 5) {
        printf("Server Running: Count=%d\n", runCount);
        runCount++;
        if (runCount == 3) continue;
        sleep(1);
    }

    do {
        static int loopCnt = 0;
        loopCnt++;
        if (loopCnt > 2) break;
        printf("Do-While Loop: %d\n", loopCnt);
    } while (true);

    switch (role) {
        case ADMIN:
            printf("Role: Admin\n");
            break;
        case USER:
            printf("Role: Regular User\n");
            break;
        case GUEST:
            printf("Role: Guest\n");
            break;
        default:
            printf("Role: Unknown\n");
    }

    register int sum = 0;
    for (int i = 1; i <= 100; i++) {
        sum += i;
    }
    printf("Sum 1-100: %d\n", sum);

    auto double avgScore = (double)totalScore / userList.count;
    printf("Average Score: %.2lf\n", avgScore);

    const float PASS_SCORE = 60.0f;
    printf("Pass Score Threshold: %.1f\n", PASS_SCORE);

    printf("Size of User Struct: %zu\n", sizeof(User));

    unsigned long userCount = (unsigned long)userList.count;
    printf("Unsigned User Count: %lu\n", userCount);

    signed long diff = 1000 - (signed long)userList.count;
    printf("Difference: %ld\n", diff);

    if (userList.count > 50) {
        printf("More than 50 users registered\n");
    } else {
        printf("Less than 50 users registered\n");
    }

    goto exitPoint;
    printf("Unreachable Code\n");
exitPoint:

    deleteAllUsers();
    isServerRunning = false;
    return 0;
}