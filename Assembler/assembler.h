#ifndef ISA_ASM_H
#define ISA_ASM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "our_list.h"

#define MAXCHARATLINE 500 // The maximum length of a line in the assembly code

/*
* This function goes over the input file line by line and translate the assembler command into hexa string.
* it writes it into an array and at the end will write it to the output file
* It uses get_labels_lines and write_to_file.
* @param filename - the path of the input file
* @param filename - the path of the output file
* @return - void
*/
void readFile(char* filename, char* output);

/*
* This function goes over the input file line by line and create a List of labels and their line number.
* It also return the max line - max(number of commands, address of .word)
* @param filename - the path of the input file
* @param max_line - a pointer to the integer which keeps the max_line
* @return List* - the list of the labels and their line number
*/
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


/* translate the imm string into int (take care of hexa and dec)
* @param str - the imm string
* @return int - the imm as int
*/
int imm_to_int(char* str);

/*
* This function gets a file path and array of strings (and its size), and print line by line the array into the file
* @param path - file path to write to
* @param arr - the array to write
* @param arr_size - the array size
* @return - void
*/
void write_to_file(char* path, char** arr, int arr_size);

/*
* This main function which runs the assembler program
*/
int main(int argc, char** argv);


#endif ISA_SIM_H

