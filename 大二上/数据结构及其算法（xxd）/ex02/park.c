#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "park.h"
int main(){
    ParkingLot lot;
    WaitingQueue queue;
    carData car;
    FILE *fp=fopen("park.txt","r");
    char groupID[20]={0};
    char command[10];
    int count,carnum,time;
    int  number,m,n,unitPrice,solution;
    int numGroups=0,acc=0;
    if(fp==NULL){
        printf("open file error,quit!\n");
        return -1;
    }
    
    while(fscanf(fp," %[^,],%d,%d,%d,%d,%d\n",groupID,&number,&m,&n,&unitPrice,&solution)==6){
        int income=0,lastTime=0;
        numGroups++;
        if(groupID[0]!='g'){
            printf("error");
            continue;
        }
        initParkingLot(&lot, n);
        initWaitingQueue(&queue, m);
        printf("\n");
        printf("group %s started...\n",groupID);
        count=0;
        while(count<number){
            if(fscanf(fp," %[^,],%d,%d\n",command,&carnum,&time)!=3){
                break;
            }
            count++;
            lastTime=time;
            car.carnum=carnum;
            car.arriveTime=time;
            car.leaveTime=0;
            switch(command[0]){
                case'A':
                    if(!isFull(&lot,n)){
                        parkCar(&lot,car,n);
                    }else{
                        enqueue(&queue,car,m);
                    }
                    break;
                case 'D':{
                    int found=0;
                    for(int i = 0; i < lot.count; i++){
                        if(lot.cars[i].carnum == carnum){
                            found=1;
                            int parkingTime = time - lot.cars[i].arriveTime;
                            income += parkingTime * unitPrice;
                            printf("car %d is leaving...%d yuan paid.\n", carnum, parkingTime * unitPrice);
                            leaveCar(&lot, carnum, time, n);
                            if(!isEmptyQueue(&queue) && !isFull(&lot, n)) {
                                carData waitingCar = dequeue(&queue);
                                waitingCar.arriveTime=time;
                                parkCar(&lot, waitingCar, n);
                            }
                            break;
                        }
                    }
                    if(!found){
                        printf("car %d is not in the parkinglot.\n",carnum);
                    }
                    break;
                }
                case 'P':
                    printLot(&lot);
                    break;
                case 'W':
                    printQueue(&queue);
                break;
            }
        }
        if(income==solution){
            acc++;
        }  
        printf("\n");
    }
    printf("acc:%d/%d=%.2f\n",acc,numGroups,(float)acc/numGroups);
    fclose(fp);
    return 0;
}