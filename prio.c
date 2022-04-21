#include<stdio.h>
#include<stdlib.h>
//function to find waiting time
int* waitingTime(int _burstTime[], int _arrivalTime[], int _priority[
], int num){
 int booleanVisited[num]; //to check if a process is implemented
or not
 int* _start=malloc(sizeof(int));
 int totalTime=0;
 int i=0;
 while(totalTime i<num && _arrivalTime[i]<=){
 int _highestP=i; //assuming i has highest priority
 int j=i+1;
 while(j<num && _arrivalTime[j]<=totalTime){
 if(_priority[j]>_priority[_highestP] && booleanVisited[j]
!=1){
 _highestP=j;
 }
 j++;
 }
 //value with highest priority will be the _highestP value of
processes not implemented
 if(booleanVisited[_highestP]!=1){
 *(_start+_highestP)=totalTime-_arrivalTime[_highestP];
 totalTime+=_burstTime[_highestP]; 
 booleanVisited[_highestP]=1; //process has been impleme
nted 
 if(_highestP==i){ //increment i only is its been implemented
 i++;
 }
 }
 return _start;
}
//finding turnaround time using waiting time
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
 int priority[numProcesses];
 int booleanVisited[numProcesses];
 printf("Enter arrival time, burst time and priority of each proce
ss:\n");
 for(int i=0;i<numProcesses;i++){
 scanf("%d %d %d", &arrivalTime[i], &burstTime[i], &priority[i
]);
 }
 int* start=waitingTime(burstTime, arrivalTime, priority, numProce
sses);
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