#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>	
#include <string.h>
#include "Commands.h"

#define bufSize 500 /* buffer size = length of a line in the input + 1 */
#define memSize (4096*4) /* The size of the memory in words */
#define numOfReg 16 /* Number of registers in the proccessor */

/**
 * A type to represent all opcodes of the SIMP commands
 */
typedef enum {
	ADD = 0,
	SUB = 1,
	AND = 2,
	OR = 3,
	SLL = 4,
	SRA = 5,
	MAC = 6,
	BRANCH = 7,
	JAL = 11,
	LW = 12,
	SW = 13,
	JR = 14,
	HALT = 15
}OP_CODE;

/*
* This function write data to a file by a given filepath.
* @param path - the path of the input file
* @param data - the data to write
* @param isArr - 1 in case the data is an array , 0 in case the data is a number
* @return int - on succses = 0 , on failuer = -1
*/
int writeToFile(char * path, int * data, int len, int isArr);

/*
* This function go over the int array for serching the index of the last non zero member in a int array
* @param data - the int array
* @param len - the length of the int array
* @return int - the index of the last non zero member in a int array
*/
int getLastIndex(int * data, int len);

/*
* This function simulates the assembly program by the given memory snapshot.
* @param data - the int array
* @param len - the length of the int array
* @return int - the index of the last non zero member in a int array
*/
int simulate(int * mem, int * regs, char * trace_path);

/**
 * This function converts a hexadecimal number from a string to a decimal integer
 * @param hexVal - The string containing the hexadecimal number
 * @return int - The decimal value of hex_str
 */
int hex2int(char hexVal[]);

/**
 * This function sets the memory snapshot by reading from memin file.
 * @param fileName - The path of memin.txt file
 * @param mem - A pointer to the memory array
 * @return 0 - On success, if the command is not HALT
 * -1 - If the command was HALT
 */
int setMem(char *fileName, int * mem);

/**
 * This function executes a SIMP command , update the PC pointer , registers values and memory state.
 * @param cm - The command struct contains all needed details.
 * @param mem - The current memory
 * @param regs - The current registers
 * @param pc - The current pc
 * @return 0 - On success, if the command is not HALT
 * -1 - If the command was HALT
 */
int execCommand(Command cm, int * mem, int * regs, int * pc);

