#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct {
	int regs[16];
	int pc;
	char* inst;
} Trace;

/* add operation */
void do_add(Trace* R, int rd, int rs, int rt, int imm) {
	R->regs[rd] = R->regs[rs] + (R->regs[rt] + imm);
}

/* sub operation */
void do_sub(Trace* R, int rd, int rs, int rt, int imm) {
	R->regs[rd] = R->regs[rs] - (R->regs[rt] + imm);
}

/* and operation */
void do_and(Trace* R, int rd, int rs, int rt, int imm) {
	R->regs[rd] = R->regs[rs] & R->regs[rt] & imm;
}

/* or operation */
void do_or(Trace* R, int rd, int rs, int rt, int imm) {
	R->regs[rd] = R->regs[rs] | R->regs[rt] | imm;
}

/* sll operation */
void do_sll(Trace* R, int rd, int rs, int rt, int imm) {
	R->regs[rd] = R->regs[rs] << (R->regs[rt] + imm);
}

/* sra operation */
void do_sra(Trace* R, int rd, int rs, int rt, int imm) {
	R->regs[rd] = R->regs[rs] >> (R->regs[rt] + imm);
}

/* mac operation */
void do_mac(Trace* R, int rd, int rs, int rt, int rm, int imm) {
	R->regs[rd] = R->regs[rs] * R->regs[rt] + R->regs[rm] + imm;
}

/* branch operation */
void do_branch(Trace* R, int rd, int rs, int rt, int rm, int imm, int* pc) {
	switch (rm) {

	case 0:
		if (R->regs[rs] == R->regs[rt])
			*pc = imm;
		break;

	case 1:
		if (R->regs[rs] != R->regs[rt])
			*pc = imm;
		break;

	case 2:
		if (R->regs[rs] > R->regs[rt])
			*pc = imm;
		break;
	
	case 3:
		if (R->regs[rs] < R->regs[rt])
			*pc = imm;
		break;

	case 4:
		if (R->regs[rs] >= R->regs[rt])
			*pc = imm;
		break;

	case 5:
		if (R->regs[rs] <= R->regs[rt])
			*pc = imm;
		break;

	}
}

/* jal operation */
void do_jal(Trace* R, int imm,  int* pc) {
	R->regs[15] = (*pc + 1) & 0xfff;
	*pc = imm;
}

/* lw operation */
void do_lw(Trace* R, int rd, int rs, int rt, int imm) {
	
}

/* sw operation */
void do_sw(Trace* R, int rd, int rs, int rt, int imm) {

}

/* jr operation */
void do_jr(Trace* R, int rd, int* pc) {
	*pc = R->regs[rd] & 0xfff;
}

/* halt operation */
void do_halt(Trace* R) {

}


/*
int main(int argc, char** argv)
{
	Trace s;

	return 0;
}
*/
