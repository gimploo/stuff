/*
The Logical Address in disk is divided into pages.
When in use, these pages are assigned to frames in memory.
The mapping of each page to frame is done by the page table.
Physical Address = frame * page_size + offset
*/ 
#include<stdio.h>
#include<math.h>
//Search function checks if a frame is already allocated or not
int search(int page_table[], int index, int value){
int flag = -1;
for(int i=0;i<index;i++){
if(page_table[i]==value){
return i;
} }
return flag;
}
void main(){
int logical_addr;
int choice = 1, page_bits, page_num;
printf("Enter number of bits in a page:\t");
scanf("%d", &page_bits);
int page_size = pow(2, page_bits);
printf("Enter number of pages in Logical Memory:\t");
scanf("%d", &page_num);
int page_table[page_num];
printf("Assign frame number to all %d pages:\n", page_num);
for(int i=0;i<page_num;i++){
printf("page[%d]:\t", i);
scanf("%d", &page_table[i]);
int check = search(page_table, i, page_table[i]);
if(check != -1){
printf("ERROR: Repeating Frame!\n");
printf("Enter another frame\n");
//repeat the assignment to a new frame
i--; } }
do{
printf("Enter Logical Address to map:\n");
scanf("%d", &logical_addr);
int offset = logical_addr%page_size;
int page = logical_addr/page_size;
if(page>page_num){
printf("Invalid Address!\n");
break;
} 
int physical_addr = page_table[page]*page_size+offset;
printf("The corresponding Physical Address is:\t%d\n", 
physical_addr);
printf("Do you want to continue?(1/0)\n");
scanf("%d", &choice);
}while(choice==1);
}