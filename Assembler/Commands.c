#include "Commands.h"

/* add operation */
void do_add(int * regs, int rd, int rs, int rt, int imm) {
	regs[rd] = regs[rs] + (regs[rt] + imm);
}

/* sub operation */
void do_sub(int * regs, int rd, int rs, int rt, int imm) {
	regs[rd] = regs[rs] - regs[rt] - imm;
}

/* and operation */
void do_and(int * regs, int rd, int rs, int rt, int imm) {
	regs[rd] = regs[rs] & regs[rt] & imm;
}

/* or operation */
void do_or(int * regs, int rd, int rs, int rt, int imm) {
	regs[rd] = regs[rs] | regs[rt] | imm;
}

/* sll operation */
void do_sll(int * regs,int rd, int rs, int rt, int imm) {
	regs[rd] = regs[rs] << (regs[rt] + imm);
}

/* sra operation */
void do_sra(int * regs, int rd, int rs, int rt, int imm) {
	regs[rd] = regs[rs] >> (regs[rt] + imm);
}

/* mac operation */
void do_mac(int * regs, int rd, int rs, int rt, int rm, int imm) {
	regs[rd] = regs[rs] * regs[rt] + regs[rm] + imm;
}

/* branch operation */
void do_branch(int regs[], int * pc,int rd, int rs, int rt, int rm, int imm) {
	switch (rm) {

	case 0:
		if (regs[rs] == regs[rt])
			*pc = imm;
		else *pc += 1;
		break;

	case 1:
		if (regs[rs] != regs[rt])
			*pc = imm;
		else *pc += 1;
		break;

	case 2:
		if (regs[rs] > regs[rt])
			*pc = imm;
		else *pc += 1;
		break;
	case 3:
		if (regs[rs] < regs[rt])
			*pc = imm;
		else *pc += 1;
		break;

	case 4:
		if (regs[rs] >= regs[rt])
			*pc = imm;
		else *pc += 1;
		break;

	case 5:
		if (regs[rs] <= regs[rt])
			*pc = imm;
		else *pc += 1;
		break;
	}
}

/* jal operation */
void do_jal(int * reg, int *pc, int imm) {
	reg[15] = ((*pc) + 1) & 0xfff;
	*pc = imm;
}

/* lw operation */
void do_lw(int *regs,int mem[], int rd, int rs, int rt, int imm) {
	regs[rd] = mem[(regs[rs] + imm) & 0xfff];
}

/* sw operation */
void do_sw(int regs[],int * mem,int rd, int rs, int rt, int imm) {
	mem[(regs[rs] + imm) & 0xfff] = regs[rd];
}

/* jr operation */
void do_jr(int regs[],int *pc, int rd) {
	*pc = regs[rd] & 0xfff;
}