#ifndef PARK_H
#define PARK_H
#include <stdio.h>
typedef struct{
    int carnum;
    int arriveTime;
    int leaveTime;
}carData;

typedef struct{
    carData cars[1000];
    int count;
}ParkingLot;
typedef struct{
    carData cars[1000];
    int front;
    int rear;
    int count;
}WaitingQueue;
void initParkingLot(ParkingLot *lot,int n);
void initWaitingQueue(WaitingQueue *queue,int m);
int isFull(ParkingLot *lot,int n);
int isEmpty(ParkingLot *lot);
int isFullQueue(WaitingQueue *queue,int m);
int isEmptyQueue(WaitingQueue *queue);
void parkCar(ParkingLot *lot,carData car,int n);
void moveCars(ParkingLot *lot,int leaveCar,int n);
void leaveCar(ParkingLot *lot,int carnum,int currentTime,int n);
void enqueue(WaitingQueue *queue,carData car,int m);
carData dequeue(WaitingQueue *queue);
void printLot(ParkingLot *lot);
void printQueue(WaitingQueue *queue);
#endif