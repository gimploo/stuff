#include<stdio.h>
#include<stdlib.h>
//declaring functions for circular queue
int front=-1;
int rear=-1;
int isempty(){
 if(rear==front && rear==-1 )
 return 1;
 else
 return 0;
}
void enqueue(int value, int cqueue[], int size){
 if(rear==-1 && front==-1)
 front=0;
 rear = (rear+1)%size;
 cqueue[rear]=value;
 
}
int dequeue(int cqueue[], int size){
 if(isempty()==1)
 {
 printf("CQueue is empty\n");
 return -1;
 }
 int temp = cqueue[front];
 if(front==rear)
 {
 front=-1;
 rear=-1;
 }
 else
 {
 front=(front+1)%size;
 }
 return temp;
}
//function to find turnaround time
int* turnaroundTime(int _burstTime[], int _arrivalTime[], int num, in
t queue[], int slice){
 int burstTime[num];
 for(int i=0;i<num;i++){
 burstTime[i]=_burstTime[i]; //creating an alternate array to
not change the actual array
 }
 int* _start=malloc(sizeof(int));
 int totalTime=0;
 enqueue(0, queue, num);
 int k=1;
 while(!isempty()){
 int i=dequeue(queue, num); 
 if(burstTime[i]>=slice){
 burstTime[i]-=slice;
 totalTime+=slice;
 while(k<num && _arrivalTime[k]<=totalTime){
 enqueue(k, queue, num);
 k++;
 }
 if(burstTime[i]!=0)
 enqueue(i, queue, num);
 else{
 *(_start+i)=totalTime-_arrivalTime[i];
 }
 }
 else{
 totalTime+=burstTime[i];
 while(k<num && _arrivalTime[k]<=totalTime){
 enqueue(k, queue, num);
 k++;
 }
 *(_start+i)=totalTime-_arrivalTime[i];
 }
 }
 return _start;
}
//function to find waiting time using turnaround time
void waitingTime(int _burstTime[], int* _turnaround, int num){
 int sum = 0;
 for(int i=0;i<num;i++){
 int wT=(*(_turnaround+i)-_burstTime[i]);
 sum+=wT;
 printf("%d\n", wT);
 }
 float av=(float)sum/num;
 printf("Average waiting time is: %.2f\n", av);
}
void main(){
 int numProcesses, timeSlice;
 printf("Enter number of processes:\n");
 scanf("%d", &numProcesses);
 int queue[numProcesses];
 printf("Enter time slice of RR\n");
 scanf("%d", &timeSlice);
 int burstTime[numProcesses];
 int arrivalTime[numProcesses];
 printf("Enter arrival and burst time of each process:\n");
 for(int i=0;i<numProcesses;i++){
 scanf("%d %d", &arrivalTime[i], &burstTime[i]);
 }
 int* start=turnaroundTime(burstTime, arrivalTime, numProcesses, q
ueue, timeSlice);
 int sum=0;
 printf("Turnaround time for each process is:\n");
 for(int i=0;i<numProcesses;i++){
 sum = sum + *(start+i);
 printf("%d\n", *(start+i));
 }
 float av = (float)sum/numProcesses;
 
 printf("Average turnaround time is: %.2f\n", av);
 printf("Waiting time for each process is:\n");
 waitingTime(burstTime, start, numProcesses);
}