/*
 * Command.h Summary:
 *
 *
 *A container that represents a command as described in the assignment.
 *
 *The container supports all commands for SIMP processor.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


/*
*	A struct that represents a SIMP processor command.
*/
typedef struct command
{
	char opcode;
	int rd;
	int rs;
	int rt;
	int rm;
	int imm;
}Command;

/* add operation */
void do_add(int * regs, int rd, int rs, int rt, int imm);

/* sub operation */
void do_sub(int * regs, int rd, int rs, int rt, int imm);

/* and operation */
void do_and(int * regs, int rd, int rs, int rt, int imm);

/* or operation */
void do_or(int * regs, int rd, int rs, int rt, int imm);

/* sll operation */
void do_sll(int * regs, int rd, int rs, int rt, int imm);

/* sra operation */
void do_sra(int * regs, int rd, int rs, int rt, int imm);

/* mac operation */
void do_mac(int * regs, int rd, int rs, int rt, int rm, int imm);

/* branch operation */
void do_branch(int regs[], int * pc, int rd, int rs, int rt, int rm, int imm);

/* jal operation */
void do_jal(int * regs,int * pc, int imm);

/* lw operation */
void do_lw(int *regs, int mem[], int rd, int rs, int rt, int imm);

/* sw operation */
void do_sw(int regs[], int * mem, int rd, int rs, int rt, int imm);

/* jr operation */
void do_jr(int regs[], int * pc, int rd);