#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int MEM_SIZE = 100;
void contiguous_allocation(){
struct dir_table {
int start_index;
int file_size;
};
int memory[MEM_SIZE], flag[MEM_SIZE], file_no=-1, check=0, 
choice=0, file_size;
struct dir_table directory_table[MEM_SIZE];
//initialising arrays
for(int i = 0; i < MEM_SIZE; i++){
memory[i] = -1;
flag[i] = 0;
directory_table[i].start_index= -1;
directory_table[i].file_size= -1;
}
do{
printf("\n--- Contiguous Memory Allocation ---\n");
printf("1. Enter a new file.\n");
printf("2. Display memory.\n");
printf("3. Display directory table.\n");
printf("4. Exit.\n");
printf("Enter your choice: ");
scanf("%d", &choice);
switch(choice){
case 1:
file_no++;
printf("Enter the size of the file: ");
scanf("%d", &file_size);
//allocating memory to this file
for(int i = 0; i < MEM_SIZE; i++){
check = 0;
if(flag[i] == 0){
//checking the next (file_size-1) slots if 
there is sufficient contiguous free space
for(int j = 0; j < file_size; j++){
if(flag[i+j] == 1 || (i+j) >= MEM_SIZE){
check = 1;
//search from next location
i = i+j;
break;
} }
//if there is contiguous free slots available 
assign memory to file
if(check == 0){
for(int j = 0; j < file_size; j++){
flag[i+j] = 1;
memory[i+j] = file_no;
}
directory_table[file_no].start_index = i;
directory_table[file_no].file_size = 
file_size;
check = 2;
} 
} 
//printing allocation details
if(check == 2){
printf("\nThe file has been allocated into 
memory. Details:-\n");
printf("File Number: %d\n", file_no);
printf("File Starting Block: %d\n", 
directory_table[file_no].start_index);
printf("File Size: %d\n", 
directory_table[file_no].file_size);
break;
} }
if(check != 2){
printf("The file could not be allocated into 
memory.\n");
}
break;
case 2:
printf("\nDisplaying memory:-\n");
for(int i = 0; i < 10; i++){
for(int j = 0; j < 10; j++){
printf("%d\t", memory[10*i+j]);
}
printf("\n");
}
break;
case 3:
printf("\nDisplaying directory table:-\n");
printf("File Name\t Start Block\t File Size\n");
for(int i = 0; i <= file_no; i++){
printf("%d\t\t %d\t\t %d\n", i, 
directory_table[i].start_index, directory_table[i].file_size);
}
break;
case 4:
printf("Exiting contiguous memory allocation.\n");
break;
default:
printf("Invalid Input. Try again !\n");
break;
}
}while(choice!=4);
}
void linked_allocation(){
struct mem_block{
int data;
int ptr;
};
struct dir_table {
int start_index;
int last_index;
};
struct mem_block memory[100];
struct dir_table directory_table[100]; 
int check = 0, file_no = -1, free_space = MEM_SIZE, flag[100], 
choice = 0;
//Initializing arrays
for(int i = 0; i < MEM_SIZE; i++){
memory[i].data = -1;
memory[i].ptr = -1;
flag[i] = 0;
directory_table[i].start_index = -1;
directory_table[i].last_index = -1;
}
do{
printf("\n--- Linked File Allocation ---\n");
printf("1. Enter file\n");
printf("2. Display memory\n");
printf("3. Display Directory Table\n");
printf("4. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);
switch(choice){
case 1:
printf("Enter the file size: ");
int file_size;
scanf("%d", &file_size);
if(free_space < file_size){
printf("The file size is larger than the 
remaining free space.\n");
break;
}
else if(file_size <= 0){
printf("Invalid file size !\n");
}
//if control reaches here, then it is posiible to 
allocate memory to the file
file_no++;
//now allocating memory to the file
srand(time(0));
int allocated = 0;
int prev_index = -1;
while(allocated < file_size){
//a random block is selected and if free, is 
allocated to the current file
int curr_index = rand()%MEM_SIZE;
if(flag[curr_index] == 0){
flag[curr_index] = 1;
memory[curr_index].data = file_no;
allocated++;
free_space--;
//if this is the first allocated block, make 
an entry into the directory table
if(allocated == 1){
directory_table[file_no].start_index = 
curr_index;
}
//if this is the last allocated block, record 
it in the directory table
if(allocated == file_size){
directory_table[file_no].last_index = 
curr_index;
}
//linking the current block to its 
predecessor
if(prev_index != -1){
memory[prev_index].ptr = curr_index;
prev_index = curr_index;
}else{
//for the very first block of the file
prev_index = curr_index;
} } }
printf("File has been entered successfully.\n");
break;
case 2:
printf("\nDisplaying memory:-\n");
for(int i = 0; i < 10; i++){
for(int j = 0; j < 10; j++){
printf("%d\t", memory[10*i+j].data);
}
printf("\n");
}
break;
case 3:
printf("\nDisplaying directory table:-\n");
printf("File Name\t Start Block\t End Block\n");
for(int i = 0; i <= file_no; i++){
printf("%d\t\t %d\t\t %d\n", i, 
directory_table[i].start_index, directory_table[i].last_index);
}
//printing individual files in the linked list 
fashion
printf("\nDisplaying the linked list representation 
of files:-\n");
for(int i = 0; i <= file_no; i++){
int curr_index = directory_table[i].start_index;
printf("File #%d: %d", i, curr_index);
while(curr_index != 
directory_table[i].last_index){
curr_index = memory[curr_index].ptr;
printf(" -> %d", curr_index);
}
printf("\n");
}
break;
case 4:
printf("Exiting linked memory allocation\n");
break;
default:
printf("Invalid Input. Try again !\n");
break;
}
}while(choice<4);
}
void indexed_allocation(){
struct block{
int data;
int ptr[99];
};
struct block memory[100];
int flag[100], directory_table[100], file_no = -1, free_space = 
MEM_SIZE, choice = 0, file_size, fat_index;
//Initializing the arrays
for(int i = 0; i < MEM_SIZE; i++){
memory[i].data = -1;
for(int j = 0; j < MEM_SIZE-1; j++){
memory[i].ptr[j] = -1;
}
flag[i] = 0;
directory_table[i]= -1;
}
do{
printf("\n--- Indexed File Allocation ---\n");
printf("1. Enter file\n");
printf("2. Display memory\n");
printf("3. Display Directory Table\n");
printf("4. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);
switch(choice){
case 1:
printf("Enter the file size: ");
scanf("%d", &file_size);
if(free_space < file_size){
printf("The file size is larger than the 
remaining free space.\n");
break;
}
else if(file_size <= 0){
printf("Invalid file size !\n");
}
//if control reaches here, then it is possible to 
allocate memory to the file
file_no++;
srand(time(0));
int allocated = 0;
//finding an index block for file
while(1){
fat_index = rand()%100;
if(flag[fat_index] == 0){
directory_table[file_no] = fat_index; 
flag[fat_index] = 1;
free_space--;
break;
} }
//allocating memory to the file
while(allocated < file_size){
int curr_index = rand()%MEM_SIZE;
//checking if selected slot is free. If yes, 
allocate it to the file
if(flag[curr_index] == 0){
flag[curr_index] = 1;
memory[curr_index].data = file_no;
memory[fat_index].ptr[allocated] = 
curr_index;
allocated++;
free_space--; } }
printf("File has been entered successfully.\n");
break;
case 2:
printf("\nDisplaying memory:-\n");
for(int i = 0; i < 10; i++){
for(int j = 0; j < 10; j++){
printf("%d\t", memory[10*i+j].data);
}
printf("\n");
}
break;
case 3:
printf("\nDisplaying directory table:-\n");
printf("File Name\t Index Block\n");
for(int i = 0; i <= file_no; i++){
printf("%d\t\t %d\n", i, directory_table[i]);
}
printf("\nDisplaying each file seperately:-\n");
for(int i = 0; i <= file_no; i++){
int fat_index = directory_table[i];
printf("File #%d: ", i); 
printf("%d", memory[fat_index].ptr[0]);
for(int j = 1; j < MEM_SIZE-1; j++){
if(memory[fat_index].ptr[j] != -1){
printf(" -> %d", 
memory[fat_index].ptr[j]);
}
else{
break;
} }
printf("\n");
}
break;
case 4:
printf("Exiting indexed memory allocation\n");
break;
default:
printf("Invalid Input. Try again !\n");
break;
}
}while(choice<4);
}
void main(){
int choice=0;
do{
printf("\n******* MENU *******\n");
printf("1. Contiguous File Allocation\n");
printf("2. Linked File Allocation\n");
printf("3. Indexed File Allocation\n");
printf("4. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);
switch(choice){
case 1:
contiguous_allocation();
break;
case 2:
linked_allocation();
break;
case 3:
indexed_allocation();
break;
case 4:
break;
default:
printf("Invalid Input\n"); 
break;
}
}while(choice<4);
}