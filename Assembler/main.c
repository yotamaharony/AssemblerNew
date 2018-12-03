#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "our_list.h"

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
#define MEMORY_SIZE 512

void readFile();
List* get_labels_lines( char* filename);
char opcode_to_bin(char* opcode);
char registerName_to_number(char* name);
int imm_to_hex(char* imm);
void label_to_hex(char* str, int imm);

int main(int argc, char** argv) 
{
	char* filename = "C:\\Users\\Yotam\\Documents\\fib.asm";
	//get_labels_lines(labels, filename);
	//List* labels = get_labels_lines(filename);

	//printf("\n");
	readFile();
	return 0;
}

List* get_labels_lines( char* filename) {
	FILE *fp;
	char line[MAXCHARATLINE];
	unsigned int j = 1;
	char delimiters[] = " \t\r\n,";
	int i;
	List* labels = initList();

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Could not open file %s\n", filename);
		return 1;
	}

	while (fgets(line, MAXCHARATLINE, fp) != NULL)
	{
		if (line[0] == '\n' || line[0] == '\r' || line[0] == '#') {
			continue;
		}

		char* comm[256];
		i = 0;
		comm[i] = strtok(line, delimiters);
		if (comm[0] != NULL)
		{
			if (strchr(comm[0], ':'))
			{
				//labels[j] = comm[0];
				addNode(labels, comm[0], j-1);
			}

			j++;
		}
	}

	/*
	Node* temp = labels->head;
	while (temp)
	{
		printf("%s:%d\n", temp->label_name, temp->line_number);
		temp = temp->next;
	}
	*/
	fclose(fp);
	return labels;
}

void readFile()
{
	FILE *fp;
	char line[MAXCHARATLINE];
	int j = 1;
	char delimiters[] = " \t\r\n,";
	char* filename = "C:\\Users\\Yotam\\Documents\\fib.asm";
	int i;
	char opcode, rd, rs, rm, rt;
	//char imm[3];
	char str[3] = "000";
	List* labels = get_labels_lines(filename);

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Could not open file %s\n", filename);
		return 1;
	}

	while (fgets(line, MAXCHARATLINE, fp) != NULL)
	{
		if (line[0] == '\n' || line[0] == '\r' || line[0] == '#') {
			continue;
		}

		char* comm[256];
		i = 0;
		comm[i] = strtok(line, delimiters);
		if (comm[0] != NULL)
		{
			if (strchr(comm[0], ':'))
			{
				comm[0] = strtok(NULL, delimiters);
				//printf("switch: %s\n", comm[0]);
				if (comm[0] == NULL)
					continue;
			}

			while (comm[i] != NULL && i<6) {
				i++;
				comm[i] = strtok(NULL, delimiters);
			}
			//printf("LINE#%d: opcde=%s, rd=%s, rs=%s, rt=%s, rm=%s, imm=%s\n", j, comm[0], comm[1], comm[2], comm[3], comm[4], comm[5]);

			/* currently not working correctly */
			int find = find_node(labels, comm[5]);
			if (find != -1)
			{
				label_to_hex(str, find);
				//printf("new try: %04x\n", find);
				//printf("%s: %d %s ", comm[5], find, str);
				comm[5] = str;
			}
			else
			{// convert the imm to hex
				itoa(atoi(comm[5]), str, 16);
				comm[5] = str;
				//label_to_hex(str, atoi(comm[5]));
			}

			

			if (!strchr(comm[0], '.'))
			{
				//printf("LINE#%d: opcde=%s, rd=%s, rs=%s, rt=%s, rm=%s, imm=%s       ", j, comm[0], comm[1], comm[2], comm[3], comm[4], comm[5]);
				opcode = opcode_to_bin(comm[0]);
				rd = registerName_to_number(comm[1]);
				rs = registerName_to_number(comm[2]);
				rt = registerName_to_number(comm[3]);
				rm = registerName_to_number(comm[4]);
				//imm = comm[5];
				
				int imm_size = strlen(comm[5]);
				if (imm_size == 1)
					printf("%c%c%c%c%c00%s\n", opcode, rd, rs, rt, rm, strupr(comm[5]));
				else if (imm_size == 2)
					printf("%c%c%c%c%c0%s\n", opcode, rd, rs, rt, rm, strupr(comm[5]));
				else
					printf("%c%c%c%c%c%s\n", opcode, rd, rs, rt, rm, strupr(comm[5]));
				
				//printf("%c%c%c%c%c0000\n", opcode_to_bin(comm[0]), registerName_to_number(comm[1]), registerName_to_number(comm[2]), registerName_to_number(comm[3]), registerName_to_number(comm[4]));
				//printf("%c%c%c%c%c%04d\n", opcode_to_bin(comm[0]), registerName_to_number(comm[1]), registerName_to_number(comm[2]), registerName_to_number(comm[3]), registerName_to_number(comm[4]), atoi(comm[5]));
			}
			else
			{
				/* do .word*/
			}

			j++;
		}
		else
			continue;

	}


	scanf("%d", &i);
	fclose(fp);
}

int imm_to_hex(char* imm) {
	if (strstr(imm, "0x") != NULL) { // Num is in hexadecimal
		return (int)strtol(imm, NULL, 0);
	}
	return strtol(imm, NULL, 10);
}

void label_to_hex(char* str, int imm) {
	itoa(imm, str, 16);
	int size = strlen(itoa);
	if (strlen == 1)
		//str = strcat("00", str);
		strcat(str, "00");
	else if (strlen == 2)
		str = strcat("0", str);
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
	if (strcmp(name, "$zero") == 0 || strcmp(name, "0") == 0) //0 = equal
		return '0';
	else if (strcmp(name, "$at") == 0 || strcmp(name, "1") == 0)
		return '1';
	else if (strcmp(name, "$v0") == 0 || strcmp(name, "2") == 0)
		return '2';
	else if (strcmp(name, "$a0") == 0 || strcmp(name, "3") == 0)
		return '3';
	else if (strcmp(name, "$a1") == 0 || strcmp(name, "4") == 0)
		return '4';
	else if (strcmp(name, "$t0") == 0 || strcmp(name, "5") == 0)
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
		return 'F';

	return "!";
}