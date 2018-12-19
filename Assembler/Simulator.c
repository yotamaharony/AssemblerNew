#include "Simulator.h"

int main(int argc, char*argv[])
{
	int mem[memSize] = { 0 };
	int regs[numOfReg] = { 0 };
	int lines;
	int numOfInst = 0;
	char * memin_path;
	char * memout_path;
	char * regout_path;
	char * trace_path;
	char * count_path;

	if (argc < 6) {
		printf("Invalid number of arguments.\n");
		return 1;
	}
	memin_path  = argv[1];
	memout_path = argv[2];
	regout_path = argv[3];
	trace_path  = argv[4];
	count_path  = argv[5];

	lines = setMem(memin_path, mem);
	if (lines == -1)
		return 1;
	numOfInst = simulate(mem,regs,trace_path);
	if (numOfInst == -1) 
		return 0;
	if (writeToFile(memout_path, mem,memSize,1) == -1)
		return 0;
	if (writeToFile(regout_path, regs,numOfReg,1) == -1)
		return 0;
	if (writeToFile(count_path, numOfInst,0,0) == -1)
		return 0;
	return 0;
}

int writeToFile(char * path, int * data,int len,int isArr) {
	FILE * f;
	f = fopen(path, "w");
	if (f == NULL) {
		perror("fopen error:");
		return -1;
	}
	if (isArr) { /* if the data is an array - write every member in different line */
		if(len == memSize)
			 len = getLastIndex(data, len) + 1; /* if the data is the memory - print til the last non zero cell */
		for (int i = 0; i < len; i++) {
			fprintf(f,"%.8X\n", data[i]);
		}
	}
	else
		fprintf(f,"%d\n", data); /* else write number */
	fclose(f);
	return 0;
}

int getLastIndex(int * data, int len) {
	int i = 0;
	int result = 0;
	for (i = 0; i < len; i++) {
		if (data[i] != 0)
			result = i;
	}
	return result;
}

int simulate(int * mem,int * regs,char * trace_path) {
	int result = 1; 
	int count = 0; /* commands counter */
	int pc = 0; /* pc pointer */
	int i = 0;
	FILE * traceF;
	traceF = fopen(trace_path, "w");
	if (traceF == NULL) {
		perror("fopen error:");
		return -1;
	}
	while (pc < memSize && result == 1) { /* keep simulate til pc is no longer valid or the commnd is HALT */
		Command cm;
		cm.opcode = (mem[pc] >> 28) & 0xf; /* get opcode bits */
		cm.rd = (mem[pc] >> 24) & 0xf; /* get rd bits */
		cm.rs = (mem[pc] >> 20) & 0xf; /* get rs bits */
		cm.rt = (mem[pc] >> 16) & 0xf; /* get rt bits */
		cm.rm = (mem[pc] >> 12) & 0xf; /* get tm bits */
		cm.imm = (mem[pc] << 20) >> 20; /* get imm bits */

		fprintf(traceF, "%.8X %.8X ", pc, mem[pc]); /* writes the pc and inst to trace file */
		for (i = 0; i < numOfReg; i++) {
			fprintf(traceF, "%.8X", regs[i]); /* writes regs to trace file */
			if(i != numOfReg-1)
				fprintf(traceF, " ");
		}
		fprintf(traceF,"\n"); /* new line */
		result = execCommand(cm, mem, regs,&pc); /* exec the command */
		count++; /* update the commands counter */
	}
	fclose(traceF);
	return count;
}

int hex2int(char hexVal[]) {
	int len = strlen(hexVal);
	int base = 1;
	int dec_val = 0;
	for (int i = len - 1; i >= 0; i--) {
		if (hexVal[i] >= '0' && hexVal[i] <= '9') {
			dec_val += (hexVal[i] - 48)*base;
			base = base * 16;
		}
		else if (hexVal[i] >= 'A' && hexVal[i] <= 'F') {
			dec_val += (hexVal[i] - 55)*base;
			base = base * 16;
		}
	}
	return dec_val;
}

int setMem(char *fileName, int * mem) {
	char buf[bufSize];
	FILE * fp;
	char * line = NULL;
	int i = 0;
	if ((fp = fopen(fileName, "r")) == NULL) {
		perror("fopen :");
		return -1;
	}
	while (fgets(buf, sizeof(buf), fp) != NULL) {
		if (buf[strlen(buf) - 1] == '\n') /* ignore \n at the end of the line */
			buf[strlen(buf) - 1] = '\0';
		mem[i] = hex2int(buf); /* insert memory value */
		i++;
	}
	fclose(fp);
	return i;
}

int execCommand(Command cm,int * mem,int * regs,int * pc)
{
	int result = 1;
	switch (cm.opcode)
	{
	case ADD:
		do_add(regs,cm.rd, cm.rs, cm.rt, cm.imm);
		*pc += 1;
		break;
	case SUB:
		do_sub(regs, cm.rd, cm.rs, cm.rt, cm.imm);
		*pc += 1;
		break;
	case AND:
		do_and(regs, cm.rd, cm.rs, cm.rt, cm.imm);
		*pc += 1;
		break;
	case OR:
		do_or(regs, cm.rd,cm.rs, cm.rt, cm.imm);
		*pc += 1;
		break;
	case SLL:
		do_sll(regs, cm.rd, cm.rs, cm.rt, cm.imm);
		*pc += 1;
		break;
	case SRA:
		do_sra(regs, cm.rd, cm.rs, cm.rt, cm.imm);
		*pc += 1;
		break;
	case MAC:
		do_mac(regs, cm.rd, cm.rs, cm.rt,cm.rm,cm.imm);
		*pc += 1;
		break;
	case BRANCH:
		do_branch(regs,pc, cm.rd, cm.rs, cm.rt,cm.rm, cm.imm);
		break;
	case JAL:
		do_jal(regs,pc,cm.imm);
		break;
	case LW:
		do_lw(regs,mem, cm.rd, cm.rs, cm.rt, cm.imm);
		*pc += 1;
		break;
	case SW:
		do_sw(regs,mem, cm.rd, cm.rs, cm.rt, cm.imm);
		*pc += 1;
		break;
	case JR:
		do_jr(regs,pc,cm.rd);
		break;
	case HALT:
		result = 0;
		break;
	}
	return result;
}



