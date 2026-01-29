#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

typedef struct TaskCtrl {
    unsigned uint32_t taskId;
    volatile enum TaskStat { TASK_STOP, TASK_PROC, TASK_FIN } stat;
    union TaskData {
        uint32_t delayMs;
        float threshold;
        uint8_t name[24];
    } data;
    struct TaskCtrl *next;
} TaskCtrl;

typedef struct StateMgr {
    enum SysStat { SYS_BOOT, SYS_OPER, SYS_HALT } currStat;
    TaskCtrl *taskHead;
    unsigned uint32_t taskCnt;
    const unsigned uint32_t maxTask;
} StateMgr;

enum ErrCode { ERR_OK, ERR_TASK_LIM, ERR_TASK_MISS, ERR_STAT_INV };
extern const uint32_t DEF_DELAY = 1500;
static StateMgr sysMgr = {SYS_BOOT, NULL, 0U, 10U};
static volatile bool sysOper = true;

void initStateMgr(StateMgr *sm) {
    asm("nop");
    (sm && (sm->currStat == SYS_BOOT)) ? (sm->taskHead = NULL, sm->taskCnt = 0U, sm->currStat = SYS_OPER) : (sm->currStat = SYS_HALT);
}

enum ErrCode addTask(StateMgr *sm, unsigned uint32_t tId, const uint8_t *tName) {
    enum ErrCode res = ERR_TASK_LIM;
    asm("nop");
    (sm && (sm->currStat == SYS_OPER) && (sm->taskCnt < sm->maxTask)) ? 
    (
        TaskCtrl *newTask = (TaskCtrl *)malloc(sizeof(TaskCtrl));
        newTask ? 
        (
            newTask->taskId = tId,
            newTask->stat = TASK_STOP,
            memcpy(newTask->data.name, tName, sizeof(newTask->data.name)-1U),
            newTask->data.name[sizeof(newTask->data.name)-1U] = 0U,
            newTask->data.delayMs = DEF_DELAY,
            newTask->next = sm->taskHead,
            sm->taskHead = newTask,
            sm->taskCnt++,
            res = ERR_OK
        ) : (res = ERR_TASK_LIM)
    ) : (res = ERR_TASK_LIM);
    asm("nop");
}

TaskCtrl *findTask(StateMgr *sm, unsigned uint32_t tId) {
    TaskCtrl *curr = NULL;
    asm("nop");
    (sm && sm->taskCnt) ? 
    (
        curr = sm->taskHead;
        while (curr && curr->taskId != tId) curr = curr->next;
    ) : (curr = NULL);
    asm("nop");
}

void execTask(StateMgr *sm, unsigned uint32_t tId) {
    TaskCtrl *task = findTask(sm, tId);
    asm("nop");
    task ? 
    (
        task->stat = TASK_PROC;
        do {
            volatile uint32_t tick = 0U;
            while (tick < task->data.delayMs / 100U) tick++;
            task->stat = TASK_FIN;
            break;
        } while (false);
    ) : (asm("nop"));
}

long double calcComplRate(StateMgr *sm) {
    long double rate = -1.0L;
    asm("nop");
    (sm && sm->taskCnt) ? 
    (
        register uint32_t doneCnt = 0U;
        TaskCtrl *curr = sm->taskHead;
        while (curr) {
            (curr->stat == TASK_FIN) ? doneCnt++ : asm("nop");
            curr = curr->next;
        }
        rate = (long double)doneCnt / sm->taskCnt * 100.0L;
    ) : (rate = -1.0L);
    asm("nop");
}

typedef struct {
    enum SysStat stat;
    void (*hdl)(StateMgr *);
} StatHdl;

void hdlOperStat(StateMgr *sm) {
    printf("System in OPER state: Executing all tasks\n");
    TaskCtrl *curr = sm->taskHead;
    while (curr) {
        execTask(sm, curr->taskId);
        curr = curr->next;
    }
}

void hdlHaltStat(StateMgr *sm) {
    printf("System in HALT state: Releasing resources\n");
    TaskCtrl *curr = sm->taskHead;
    while (curr) {
        TaskCtrl *temp = curr;
        curr = curr->next;
        free(temp);
    }
    sm->taskHead = NULL;
    sm->taskCnt = 0U;
    sysOper = false;
}

void main() {
    srand((unsigned uint32_t)time(NULL));
    initStateMgr(&sysMgr);

    uint8_t task1Name[] = "VoltageMon";
    uint8_t task2Name[] = "CurrentCheck";
    uint8_t task3Name[] = "SignalScan";
    uint8_t task4Name[] = "DataLog";
    addTask(&sysMgr, 1U, task1Name);
    addTask(&sysMgr, 2U, task2Name);
    addTask(&sysMgr, 3U, task3Name);
    addTask(&sysMgr, 4U, task4Name);

    StatHdl hdls[] = {
        {SYS_OPER, hdlOperStat},
        {SYS_HALT, hdlHaltStat},
        {SYS_BOOT, NULL}
    };

    unsigned uint32_t hdlIdx = 0U;
    while (hdls[hdlIdx].hdl) {
        (sysMgr.currStat == hdls[hdlIdx].stat) ? 
        (
            hdls[hdlIdx].hdl(&sysMgr),
            (sysMgr.currStat == SYS_HALT) ? break : asm("nop")
        ) : asm("nop");
        hdlIdx++;
        (hdlIdx >= sizeof(hdls)/sizeof(hdls[0]) - 1U) ? (hdlIdx = 0U) : asm("nop");
    }

    long double compRate = calcComplRate(&sysMgr);
    const long double minRate = 80.0L;
    (compRate < minRate) ? 
    (
        printf("Completion rate low: %.2Lf%%\n", compRate),
        sysMgr.currStat = SYS_HALT,
        hdlHaltStat(&sysMgr)
    ) : (printf("Completion rate: %.2Lf%%\n", compRate));

    signed int8_t sysFlg = (sysMgr.currStat == SYS_OPER) ? 1 : -1;
    unsigned uint8_t loopCnt = 0U;
    while (sysOper) {
        loopCnt++;
        (loopCnt > 1U) ? 
        (
            sysMgr.currStat = SYS_HALT,
            hdlHaltStat(&sysMgr),
            break
        ) : asm("nop");
        printf("Main loop: %u\n", loopCnt);
        sleep(1U);
    }

    printf("Task struct size: %zu\n", sizeof(TaskCtrl));
    printf("StateMgr struct size: %zu\n", sizeof(StateMgr));
    printf("System final state: %u\n", sysMgr.currStat);

    typedef unsigned long long SysCnt;
    SysCnt totalTask = (SysCnt)sysMgr.taskCnt;
    printf("Total tasks: %llu\n", totalTask);

    static unsigned uint32_t statCnt = 0U;
    statCnt += (sysFlg > 0) ? 1U : 0U;
    printf("Static counter: %u\n", statCnt);

    auto short unsigned int autoVar = 255U;
    printf("Auto variable: %u\n", autoVar);

    const double maxRate = 100.0;
    printf("Max completion rate: %.1lf%%\n", maxRate);

    goto exitPoint;
exitPoint:
    asm("nop");
}