#include<stdio.h>
#include<stdlib.h>
//function to find waiting time
int* waitingTime(int _burstTime[], int _arrivalTime[], int num){
 int* _start=malloc(sizeof(int));
 *_start=0; //waiting time of first process is always 0
 int totalTime =_burstTime[0];
 for(int i=1;i<num;i++){
 *(_start+i)=totalTime-_arrivalTime[i];
 totalTime+=_burstTime[i];
 }
 return _start;
}
//function to find turnaround time using waiting time
void turnaroundTime(int _burstTime[], int* _waiting, int num){
 int sum = 0;
 for(int i=0;i<num;i++){
 int taT=(*(_waiting+i)+_burstTime[i]);
 sum+=taT;
 printf("%d\n", taT);
 }
 float av=(float)sum/num;
 printf("Average turnaround time is: %.2f\n", av);
}
void main(){
 int numProcesses;
 printf("Enter number of processes:\n");
 scanf("%d", &numProcesses);
 int burstTime[numProcesses];
 int arrivalTime[numProcesses];
 printf("Enter arrival and burst time of each process:\n");
 for(int i=0;i<numProcesses;i++){
 scanf("%d %d", &arrivalTime[i], &burstTime[i]);
 }
 int* start=waitingTime(burstTime, arrivalTime, numProcesses);
 int sum=0;
 printf("Waiting time for each process is:\n");
 for(int i=0;i<numProcesses;i++){
 sum = sum + *(start+i);
 printf("%d\n", *(start+i));
 }
 float av = (float)sum/numProcesses;
 printf("Average waiting time is: %.2f\n", av);
 printf("Turnaround time for each process is:\n");
 turnaroundTime(burstTime, start, numProcesses);
}