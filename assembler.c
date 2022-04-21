#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main()
{
FILE *f1, *f2, *f3, *f4, *f5;
int len, i, pos = 1;
char arg[20], mne[20]; // mne is a variable that hold the 
mneumonic
char opnd[20], label[20], name[20], mne1[20], opnd1[20], 
pos1[10], pos2[10];
f1 = fopen("input_macro.txt", "r"); // input file
f2 = fopen("namtab.txt", "w+"); // nametab file
f3 = fopen("deftab.txt", "w+"); // deftab file
f4 = fopen("argtab.txt", "w+"); // argtab file
f5 = fopen("op.txt", "w+"); // exapnded code file
fscanf(f1, "%s%s%s", label, mne, opnd);
while (strcmp(mne, "END") != 0)
{
// if it's a macro then, execute the following statements
if (strcmp(mne, "MACRO") == 0)
{
fprintf(f2, "%s\n", label); // adding name of the macro 
to the name tab
fseek(f2, SEEK_SET, 0); // the next time, we read the 
nametab (if required) it should happen from begining
fprintf(f3, "%s\t%s\n", label, opnd);
fscanf(f1, "%s%s%s", label, mne, opnd);
// reading the statements inside the macro from the input 
file, till MEND is encountered
while (strcmp(mne, "MEND") != 0)
{
if (opnd[0] == '&')
{
sprintf(pos1, "%d", pos); // to convert the read 
integer into string, with a base 10
strcpy(pos2, "?");
strcpy(opnd, strcat(pos2, pos1));
pos = pos + 1;
}
// printing the statement to deftab file and reading the next 
instruction from input file
fprintf(f3, "%s\t%s\n", mne, opnd); 
fscanf(f1, "%s%s%s", label, mne, opnd);
}
// priniting the MEND statement to the detfab
fprintf(f3, "%s", mne);
}
// if it's not a macro, then execute the else block
else
{
// scanning the nametab for the name of the macro, if it 
has been called again in the input text file
fscanf(f2, "%s", name);
// search if the macro of that name has been recorded in 
the name tab
if (strcmp(mne, name) == 0)
{
len = strlen(opnd);
for (i = 0; i < len; i++)
{
if (opnd[i] != ',')
fprintf(f4, "%c", opnd[i]); // adding the 
operands into argtab
else
fprintf(f4, "\n");
}
fseek(f3, SEEK_SET, 0); // setting file pointer to 
the begining
fseek(f4, SEEK_SET, 0);
// reading the deftab 
fscanf(f3, "%s%s", mne1, opnd1);
fprintf(f5, ".\t%s\t%s\n", mne1, opnd);
fscanf(f3, "%s%s", mne1, opnd1);
while (strcmp(mne1, "MEND") != 0)
{
if (opnd1[0] == '?')
{
fscanf(f4, "%s", arg);
fprintf(f5, "-\t%s\t%s\n", mne1, arg); // 
print mneumonic from deftab and argument from argtab
}
else
fprintf(f5, "-\t%s\t%s\n", mne1, opnd1);
fscanf(f3, "%s%s", mne1, opnd1); //read next line 
from deftab
} }
else
fprintf(f5, "%s\t%s\t%s\n", label, mne, opnd); // if 
macro name not found in nametab
}
fscanf(f1, "%s%s%s", label, mne, opnd); // reading next 
statement from input tab
}
fprintf(f5, "%s\t%s\t%s", label, mne, opnd); // printing END to 
optab ( expanded code )
fclose(f1);
fclose(f2);
fclose(f3);
fclose(f4);
fclose(f5);
printf("files created and updated \n");
printf("1. argtab.txt\n");
printf("2. namtab.txt\n");
printf("3. deftab.txt\n");
printf("4. op.txt\n");
printf("Program executd succesfully");
}