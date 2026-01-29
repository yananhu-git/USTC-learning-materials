#include <stdio.h>
#include <stdlib.h>
#include "park.h"
void initParkingLot(ParkingLot *lot,int n){
    lot->count=0;
}
void initWaitingQueue(WaitingQueue *queue,int m){
    queue->front=0;
    queue->rear=0;
    queue->count=0;
}
int isFull(ParkingLot *lot,int n){
    return lot->count==n;
}
int isEmpty(ParkingLot *lot){
    return lot->count==0;
}
int isFullQueue(WaitingQueue *queue,int m){
    return queue->count==m;
}
int isEmptyQueue(WaitingQueue *queue){
    return queue->count==0;
}
void parkCar(ParkingLot *lot,carData car,int n){
    if(isFull(lot,n)==1){
        printf("car %d cannot park,lot is full.\n",car.carnum);
    }
    else{
        lot->cars[lot->count]=car;
        lot->count++;
        printf("car %d is parking...at position %d.\n",car.carnum,lot->count);
    }
}
void moveCars(ParkingLot *lot,int from,int n){
    int to=from+1;
    while(to<n){
        lot->cars[to-1]=lot->cars[to];
        to++;
    }
    lot->count--;
}
void leaveCar(ParkingLot *lot,int carNum,int currentTime,int n){
    for(int i=0;i<n;i++){
        if(lot->cars[i].carnum==carNum){  
            moveCars(lot,i,n);
            return;
        }
    }
    printf("car %d not found in lot.\n",carNum);
}
void enqueue(WaitingQueue *queue,carData car,int m){
    if(!isFullQueue(queue,m)){
        queue->cars[queue->rear]=car;
        printf("car %d is parking...waiting as %d-th one.\n",car.carnum,queue->rear+1);
        queue->rear=(queue->rear+1)%500;
        queue->count++;
        
    }
    else{
        printf("queue is full,cannot add car %d.\n",car.carnum);
    }
}
carData dequeue(WaitingQueue *queue){
    if(!isEmptyQueue(queue)){
        carData car=queue->cars[queue->front];
        queue->front=(queue->front+1)%500;
        queue->count--;
        return car;
    }
    carData nullCar={0};
    return nullCar;
}
void printLot(ParkingLot *lot){
    printf("printing cars in parking lot...\n");
    for(int i=0;i<lot->count;i++){
        printf("%d      %d\n",lot->cars[i].carnum,lot->cars[i].arriveTime);
    }
}
void printQueue(WaitingQueue *queue){
    printf("printing cars in wait queue...\n");
    for(int i=0;i<queue->count;i++){
        carData car=queue->cars[(queue->front+i)%500];
        printf("%d      %d\n",car.carnum,car.arriveTime);
    }
}