#ifndef ISA_ASM_H
#define ISA_ASM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "our_list.h"

#define MAXCHARATLINE 500 // The maximum length of a line in the assembly code
#define MEMORY_SIZE 512   //


void readFile(char* filename);

List* get_labels_lines(char* filename, int* max_line);

/*
* This function translates the opcode in the assembler: from opcode to its hexa representation 
* @param opcode - the opcode char
* @return - the char it represents ( add = 0, sub = 1...)
*/
char opcode_to_bin(char* opcode);

/*
* This function translates the register name in the assembler: from its name to its hexa representation
* @param name - the register name
* @return - the char it represents  in hexa( $zero = 0, $at = 1...)
*/
char registerName_to_number(char* name);

void label_to_hex(char* str, int imm);

/*
* This function gets a file path and array of strings (and its size), and print line by line the array into the file
* @param path - file path to write to
* @param arr - the array to write
* @param arr_size - the array size
* @return - void
*/
void write_to_file(char* path, char** arr, int arr_size);

int main(int argc, char** argv);


#endif ISA_SIM_H

