#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main()
{
char label[10], startaddr[4], opcode[10], operand[10], 
loc_counter[10], str_loc_counter[10], symbol[10], mnemonic[10], 
code[10], obcode[6], location[10], textrecord[100];
 int length, prev_addr, convert, size = 0;
 // Defining text record
 textrecord[0] = 'T';
 textrecord[1] = '^';
 textrecord[2] = '0';
 textrecord[3] = '0';
 int text = 4;
 FILE *fp1, *fp2, *fp3, *fp4, *fp5;
 fp1 = fopen("out.txt", "r");
 fp2 = fopen("optab.txt", "r");
 fp3 = fopen("symbol.txt", "r");
 fp4 = fopen("obCode.txt", "w");
 fp5 = fopen("length.txt", "r");
 fscanf(fp1, "\t%s\t%s\t%s", label, opcode, operand);
 fscanf(fp5, "%d", &length);
 if (strcmp(opcode, "START") == 0)
 {
 // Initialize Header record
 fprintf(fp4, "H^%s^00%s^00%d\n", label, operand, length);
 // save the starting address for End record
 for (int j = 0; j < 4; j++)
 {
 startaddr[j] = operand[j];
 }
 // Enter starting address to header record
 while (text < 8)
 {
 textrecord[text] = operand[text - 4];
 text++;
 }
 textrecord[text] = '^';
 // 9, 10 is for size which will be entered last
 text = 11;
 fscanf(fp1, "%s\t%s\t%s\t%s", loc_counter, label, opcode, 
operand);
 }
 while (strcmp(opcode, "END") != 0)
 {
 fprintf(fp2, "%s\t%s", mnemonic, code);
 while (strcmp(mnemonic, "END") != 0)
 {
 // If found the opcode, generate the machine code for 
instruction
 if (strcmp(opcode, mnemonic) == 0)
 {
 for (int i = 0; i < 2; i++)
 {
 obcode[i] = code[i];
 }
 fscanf(fp3, "%s\t%s", symbol, location);
 // Search symbol table for operand
 while (strcmp(symbol, "END") != 0)
 {
 if (strcmp(operand, symbol) == 0)
 {
 for (int i = 2; i < 6; i++)
 {
 obcode[i] = location[i - 2];
 }
 break;
 }
 // If not found, enter address as 0000
 for (int i = 2; i < 6; i++)
 {
 obcode[i] = '0';
 }
 fscanf(fp3, "%s\t%s", symbol, location);
 }
 fclose(fp3);
 fp3 = fopen("symbol.txt", "r");
 break;
 }
 fscanf(fp2, "%s\t%s", mnemonic, code);
 }
 fclose(fp2);
 fp2 = fopen("optab.txt", "r");
 // If not an opcode, then check if an assembler directive
 /*
 if BYTE, then convert the corresponding ascii characters 
to their ascii values
 and represent the string
 */
 if (strcmp(opcode, "BYTE") == 0)
 {
 int value = 0;
 length = strlen(operand) - 3;
 for (int j = 1; j <= 3; j++)
 {
 // finding the merged value of string of characters
 if (length >= j)
 {
 value *= 100;
 value += (int)operand[1 + j];
 }
 }
 // converting value to string
 for (int i = 5; i >= 0; i--)
 {
 obcode[i] = value % 10 + '0';
 value /= 10;
 }
 }
 /*
 if WORD, then the machine code is the integer specified 
in operand
 */
 else if (strcmp(opcode, "WORD") == 0)
 {
 int value = atoi(operand);
 for (int i = 5; i >= 0; i--)
 {
 obcode[i] = value % 10 + '0';
 value /= 10;
 }
 }
 /*
 if RESW or RESB, no machine code generated
 */
 else if (strcmp(opcode, "RESB") == 0 || strcmp(opcode, 
"RESW") == 0)
 {
 fscanf(fp1, "%s\t%s\t%s\t%s", loc_counter, label, opcode, 
operand);
 continue;
 }
 /*
 If max size of text record reached, then store the text 
record in file
 and initialize a new text record
 */
 if (size == 30)
 {
 textrecord[9] = '3';
 textrecord[10] = '0';
 for (int j = 0; j < text; j++)
 {
 printf("%d\n", j);
 fprintf(fp4, "%c", textrecord[j]);
 if (j < 4)
 {
 continue;
 }
 textrecord[j] = ' ';
 }
 for (int j = 4; j < 8; j++)
 {
 textrecord[j] = loc_counter[j - 4];
 }
 textrecord[text] = '^';
 text++;
 text = 11;
 textrecord[text] = '^';
 text++;
 size = 0;
 }
 // New text record entry
 textrecord[text] = '^';
 text++;
 for (int i = 0; i < 6; i++)
 {
 textrecord[text] = obcode[i];
 text++;
 }
 // increment number of entries in text record
 size += 3;
 fscanf(fp1, "%s\t%s\t%s\t%s", loc_counter, label, opcode, 
operand);
 }
 if (size != 0)
 {
 // Enter number of record in text record
 textrecord[10] = size % 10 + '0';
 size /= 10;
 textrecord[9] = size % 10 + '0';
 // store record
 for (int j = 0; j < text; j++)
 {
 fprintf(fp4, "%c", textrecord[j]);
 }
 }
 // Initialize end record with starting address
 fprintf(fp4, "\nE^00");
 for (int i = 0; i < 4; i++)
 {
 fprintf(fp4, "%c", startaddr[i]);
 } }