#include "assembler.h"

/*
* This function copies the source string into the target string
* @param target - a pointer to the target char
* @param source - a pointer to the source char
* @return - void
*/
void copy_string(char *target, char *source) {
	while (*source) {
		*target = *source;
		source++;
		target++;
	}
	*target = '\0';
}


int main(int argc, char** argv) 
{
	//char* input = "C:\\Users\\Yotam\\Documents\\binom2.asm";
	//char* output = "C:\\Users\\Yotam\\Documents\\meminbinom2.txt";
	//"C:\\Users\\Yotam\\Documents\\binom2.asm" "C:\\Users\\Yotam\\Documents\\meminbinom2.txt"
	
	
	if (argc != 3)
	{
		printf("Error: invalid number of arguments\n");
	}
	

	const char* input = argv[1];
	const char* output = argv[2];
	
	readFile(input, output);
	return 0;
}


List* get_labels_lines(char* filename, int* max_line) {
	FILE *fp;
	char line[MAXCHARATLINE];
	unsigned int j = 0;
	char delimiters[] = " \t\r\n,";
	int word_address;
	List* labels = initList();

	/* trying to open the file */
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Could not open file %s\n", filename);
		return 1;
	}

	/* goes over the file line by line */
	while (fgets(line, MAXCHARATLINE, fp) != NULL)
	{
		/* if it's not a command - skip it */
		if (line[0] == '\n' || line[0] == '\r' || line[0] == '#') {
			continue;
		}

		char* comm[256];
		comm[0] = strtok(line, delimiters);
		if (comm[0] != NULL)
		{
			if (strchr(comm[0], '#')) /* skip a comment line */
			{
				continue;
			}

			if (strchr(comm[0], ':')) /* check whether it's a label (contains : )*/
			{
				addNode(labels, comm[0], j);
				comm[1] = strtok(NULL, delimiters);
				if (comm[1] == NULL)
					continue;
			}

			if (strstr(comm[0], ".word")) /* check whether it's a .word command */
			{
				comm[1] = strtok(NULL, delimiters);

				/* translate the address from hexa to decimal */
				word_address = imm_to_int(comm[1]);

				if (word_address + 1 > (*max_line)) /* max_line = max(max_line, address of current of .word) */
					(*max_line) = word_address + 1;
			}

			j++;
		}
	}

	//j--;

	/* max_line = max(number of commands, biggest address of .word */
	if (j > (*max_line))
	{
		(*max_line) = j;
	}

	fclose(fp);
	return labels;
}

void readFile(char* input, char* output)
{
	FILE *fp;
	char line[MAXCHARATLINE];
	int i, j = 0, address, data, max_line = 0;
	char delimiters[] = " \t\r\n,";
	char opcode, rd, rs, rm, rt;
	//char str[3] = "000";
	List* labels = get_labels_lines(input, &max_line);
	char** memin = (char**)malloc(max_line * sizeof(char*));

	/* initalizing the memin array to zeros */
	for (int k = 0; k < max_line; k++)
	{
		memin[k] = (char*)malloc((sizeof(char) * 9));
		memcpy(memin[k], "00000000\0", 9);
	}

	/* open the assembler input file for reading */
	fp = fopen(input, "r");
	if (fp == NULL) {
		printf("Could not open file %s\n", input);
		return 1;
	}

	/* read the assembler line by line */
	while (fgets(line, MAXCHARATLINE, fp) != NULL)
	{
		/* if it's not a command - skip it */
		//printf("line[0]=%c\n", line[0]);
		if (line[0] == '\n' || line[0] == '\r' || line[0] == '#') {
			continue;
		}

		char* comm[256];
		i = 0;
		comm[i] = strtok(line, delimiters);

		/* divide the command into blocks */
		if (comm[0] != NULL)
		{
			if (strchr(comm[0], '#')) /* skip a comment line */
			{
				continue;
			}

			if (strchr(comm[0], ':')) /* if it's a LABEL and empty line after it - skip it*/
			{
				comm[0] = strtok(NULL, delimiters);
				if (comm[0] == NULL)
					continue;
			}

			/* else - tok the line into it's 5 blocks */
			while (comm[i] != NULL && i<6) {
				i++;
				comm[i] = strtok(NULL, delimiters);
			}

			/* check if the imm block it's a label - if it is, convert the label to the line in the code*/
			int find = find_node(labels, comm[5]);
			int c5 = 0;
			if (find == -1) /* label was not found */
			{
				c5 = imm_to_int(comm[5]);
			}
			else
			{
				c5 = find;
			}

			/* if the command is not ".word"*/
			if (!strchr(comm[0], '.'))
			{
				//printf("LINE#%d: opcde=%s, rd=%s, rs=%s, rt=%s, rm=%s, imm=%s       ", j, comm[0], comm[1], comm[2], comm[3], comm[4], comm[5]);
				opcode = opcode_to_bin(comm[0]);
				rd = registerName_to_number(comm[1]);
				rs = registerName_to_number(comm[2]);
				rt = registerName_to_number(comm[3]);
				rm = registerName_to_number(comm[4]);
				//imm = comm[5];

				char curr_instruction[9] = "00000000";
				
				sprintf(curr_instruction, "%c%c%c%c%c%.3X", opcode, rd, rs, rt, rm, c5);
				copy_string(memin[j], curr_instruction);
			}
			else 
			{ /* the command is .word*/
				/* if hexa - convert to dec */
				address = imm_to_int(comm[1]);
				data = imm_to_int(comm[2]);
				sprintf(memin[address], "%.8X", data);
			}

			j++;
		}
		else
			continue;

	}

	write_to_file(output, memin, max_line);
	//scanf("%d", &i);
	/* need to free the memory */
	destroyArray(memin, max_line);
	destroyList(labels);
	fclose(fp);
}

int imm_to_int(char* str) {
	if (strstr(str, "0x") || strstr(str, "0X"))
	{
		return (int)strtol(str, NULL, 16);
	}
	else
	{
		return (int)strtol(str, NULL, 10);
	}
}

void write_to_file(char* filename, char** memin, int memin_len) {
	FILE *fp;
	fp = fopen(filename, "w");
	//fp = fopen("C:\\Users\\Yotam\\Documents\\memout.txt", "w");

	for (int i = 0; i < memin_len; i++) {
		fprintf(fp, "%s\n", memin[i]);
	}

	fclose(fp);
}

void destroyArray(char** arr, int len)
{
	for (int i = 0; i < len;i++)
	{
		free(arr[i]);
	}

	free(arr);
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
	if (strcmp(name, "$zero") == 0 || strcmp(name, "0") == 0) // 0 = equal
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