#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* just checking if the gitHub works fine */

typedef struct {
	char* opcode;
	char* rd;
	char* rs;
	char* rt;
	char* rm;
	char* imm;
} Command;

#define MAXCHARATLINE 500

void readFile();
char opcode_to_bin(char* opcode);
char registerName_to_number(char* name);

//NO NEED
char* opcode_to_bin_CHAR(char* opcode);
char* registerName_to_number_CHAR(char* name);

int main(int argc, char** argv) 
{
	readFile();
	return 0;
}


void readFile()
{
	FILE *fp;
	char str[MAXCHARATLINE];
	int j = 1;
	char delimiters[] = " \t\r\n','";
	char* filename = "C:\\Users\\Yotam\\Documents\\fib.asm";
	int i;
	int to_print = 1;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Could not open file %s\n", filename);
		return 1;
	}

	Command* curr = malloc(sizeof(Command*));

	while (fgets(str, MAXCHARATLINE, fp) != NULL)
	{
		
		char* comm[256];
		i = 0;
		comm[i] = strtok(str, delimiters);

		if (comm[0] != NULL && comm[0] != " " )
		{
			
			while (comm[i] != NULL && i<6) {
				i++;
				comm[i] = strtok(NULL, delimiters);
				
			}

			curr->opcode = comm[0];
			curr->rd = comm[1];
			curr->rs = comm[2];
			curr->rt = comm[3];
			curr->rm = comm[4];
			curr->imm = comm[5];

			
			if (strchr(comm[0], ':'))
			{
				if (comm[1] != NULL)
				{
					if (opcode_to_bin(comm[1]) != '!')
					//if (strcmp("!", opcode_to_bin(comm[1])))
					{
						curr->opcode = comm[1];
						curr->rd = comm[2];
						curr->rs = comm[3];
						curr->rt = comm[4];
						curr->rm = comm[5];
						curr->imm = comm[6];
					}
					//printf("problem fixed\n");
				}
				else
				{
					to_print = 0;
					j--;
				}		
			}
			
			if (to_print)
			{
				//printf("LINE#%d: opcde=%s, rd=%s, rs=%s, rt=%s, rm=%s, imm=%s\n", j, curr->opcode, curr->rd, curr->rs, curr->rt, curr->rm, curr->imm);
				//char* num = ;
				/*
				printf("opcode: %s->%c\n", curr->opcode, opcode_to_bin(curr->opcode));
				printf("rd: %s->%c\n", curr->rd, registerName_to_number(curr->rd));
				printf("rs: %s->%c\n", curr->rs, registerName_to_number(curr->rs));
				printf("rt: %s->%c\n", curr->rt, registerName_to_number(curr->rt));
				printf("rm: %s->%c\n", curr->rm, registerName_to_number(curr->rm));
				
				printf("\n");
				*/
				printf("%c%c%c%c%c0000\n", opcode_to_bin(curr->opcode), registerName_to_number(curr->rd), registerName_to_number(curr->rs), registerName_to_number(curr->rt), registerName_to_number(curr->rm));
			}
			
			//printf("LINE#%d: opcde=%s, rd=%s, rs=%s, rt=%s, rm=%s, imm=%s\n", j, curr->opcode, curr->rd, curr->rs, curr->rt, curr->rm, curr->imm);
			
			
			
			
			j++;
			to_print = 1;
		}
		
	}
	fclose(fp);
}

char opcode_to_bin(char* opcode)
{   
	if (strcmp(opcode, "add")==0) //0 = equal
		return '0';
	else if (strcmp(opcode, "sub") == 0)
		return '1';
	else if (strcmp(opcode, "and") == 0)
		return '2';
	else if (strcmp(opcode, "or") == 0)
		return '3';
	else if (strcmp(opcode, "sll") == 0)
		return '4';
	else if (strcmp(opcode, "sra") == 0)
		return '5';
	else if (strcmp(opcode, "mac") == 0)
		return '6';
	else if (strcmp(opcode, "branch") == 0)
		return '7';
	else if (strcmp(opcode, "reserved") == 0)
		return '8';
	/*
	else if (strcmp(opcode, "sub"))
	return 0x9;
	else if (strcmp(opcode, "sub"))
	return 0xa;
	*/
	else if (strcmp(opcode, "jal") == 0)
		return 'B';
	else if (strcmp(opcode, "lw") == 0)
		return 'C';
	else if (strcmp(opcode, "sw") == 0)
		return 'D';
	else if (strcmp(opcode, "jr") == 0)
		return 'E';
	else if (strcmp(opcode, "halt") == 0)
		return 'F';

	return '!';
}


char registerName_to_number(char* name)
{
	if (strcmp(name, "$zero") == 0) //0 = equal
		return '0';
	else if (strcmp(name, "$at") == 0)
		return '1';
	else if (strcmp(name, "$v0") == 0)
		return '2';
	else if (strcmp(name, "$a0") == 0)
		return '3';
	else if (strcmp(name, "$a1") == 0)
		return '4';
	else if (strcmp(name, "$t0") == 0)
		return '5';
	else if (strcmp(name, "$t1") == 0)
		return '6';
	else if (strcmp(name, "$t2") == 0)
		return '7';
	else if (strcmp(name, "$t3") == 0)
		return '8';
	else if (strcmp(name, "$s0") == 0)
		return '9';
	else if (strcmp(name, "$s1") == 0)
		return 'A';
	else if (strcmp(name, "$s2") == 0)
		return 'B';
	else if (strcmp(name, "$gp") == 0)
		return 'C';
	else if (strcmp(name, "$sp") == 0)
		return 'D';
	else if (strcmp(name, "$fp") == 0)
		return 'E';
	else if (strcmp(name, "$ra") == 0)
		return "F";

	return "!";
}

/* this function can be removed */
char* opcode_to_bin_CHAR(char* opcode)
{
	if (strcmp(opcode, "add") == 0) //0 = equal
		return "0000";
	else if (strcmp(opcode, "sub") == 0)
		return "0001";
	else if (strcmp(opcode, "and") == 0)
		return "0002";
	else if (strcmp(opcode, "or") == 0)
		return "0003";
	else if (strcmp(opcode, "sll") == 0)
		return "0004";
	else if (strcmp(opcode, "sra") == 0)
		return "0005";
	else if (strcmp(opcode, "mac") == 0)
		return "0006";
	else if (strcmp(opcode, "branch") == 0)
		return "0007";
	else if (strcmp(opcode, "reserved") == 0)
		return "0008";
	/*
	else if (strcmp(opcode, "sub"))
	return 0x9;
	else if (strcmp(opcode, "sub"))
	return 0xa;
	*/
	else if (strcmp(opcode, "jal") == 0)
		return "0011";
	else if (strcmp(opcode, "lw") == 0)
		return "0012";
	else if (strcmp(opcode, "sw") == 0)
		return "0013";
	else if (strcmp(opcode, "jr") == 0)
		return "0014";
	else if (strcmp(opcode, "halt") == 0)
		return "0015";

	return "!";
}

/* this function can be removed */
char* registerName_to_number_CHAR(char* name)
{
	if (strcmp(name, "$zero") == 0) //0 = equal
		return "0000";
	else if (strcmp(name, "$at") == 0)
		return "0001";
	else if (strcmp(name, "$v0") == 0)
		return "0002";
	else if (strcmp(name, "$a0") == 0)
		return "0003";
	else if (strcmp(name, "$a1") == 0)
		return "0004";
	else if (strcmp(name, "$t0") == 0)
		return "0005";
	else if (strcmp(name, "$t1") == 0)
		return "0006";
	else if (strcmp(name, "$t2") == 0)
		return "0007";
	else if (strcmp(name, "$t3") == 0)
		return "0008";
	else if (strcmp(name, "$s0") == 0)
		return "0009";
	else if (strcmp(name, "$s1") == 0)
		return "0010";
	else if (strcmp(name, "$s2") == 0)
		return "0011";
	else if (strcmp(name, "$gp") == 0)
		return "0012";
	else if (strcmp(name, "$sp") == 0)
		return "0013";
	else if (strcmp(name, "$fp") == 0)
		return "0014";
	else if (strcmp(name, "$ra") == 0)
		return "0015";

	return "!";
}