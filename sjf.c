#include<stdio.h>
#include<stdlib.h>
//function to find waiting time
int* waitingTime(int _burstTime[], int _arrivalTime[], int num){
 int booleanVisited[num]; //to check if a process is implemented
or not
 int* _start=malloc(sizeof(int));
 int totalTime=0;
 int i=0;
 while(i<num && _arrivalTime[i]<=totalTime){
 int _leastBurst=i; //assuming i has least burst
 int j=i+1;
 while(j<num && _arrivalTime[j]<=totalTime){
 if(_burstTime[j]<_burstTime[_leastBurst] && booleanVisite
d[j]!=1){
 _leastBurst=j;
 }
 j++;
 }
 //value with least burst will be the _leastBurst value of pro
cesses not implemented
 if(booleanVisited[_leastBurst]!=1){
 *(_start+_leastBurst)=totalTime-
_arrivalTime[_leastBurst];
 totalTime+=_burstTime[_leastBurst];
 booleanVisited[_leastBurst]=1; //process has been imple
mented 
 }
 
 if(_leastBurst==i){ //increment i only is its been implement
ed
 i++;
 }
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
 int booleanVisited[numProcesses];
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