/* 
James Allender
Mitchell Nelson
CISC-340 
Project 01
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <glib.h>
#include <string.h>
#include <ctype.h>

int convert_num(int num);
void print_state(statetype *stateptr);
void print_stats(int n_instrs);

// Structure for
typedef struct state_struct {
	int pc;
	int mem[NUMMEMORY];
	int reg[NUMREGS];
	int num_memory;
} statetype;

int main(int argc, char **argv){
	// Variables
	int opt; // the value of the opt form getopt
	FILE* inFile; // our input File
	char *inFileName; // our input file name
	int iFlag = 0; // Flag to tell us if an i option (requiered) has been given

	extern char *optarg; // The arguemnt to a opt - used by external
	extern int optind; // the int id of the curent opt location - used by external

	// Verify correct # of args given either 3 or 5 for 1 or 2 options (i,o)
	if (argc != 3) {
	       fprintf(stderr, "Was not given either 1 or 2 sets of input arguments.\nShould be:\t-i [input file]\nExiting\n");
	       exit(EXIT_FAILURE);
        }

    // go through the args and get options
	while ((opt = getopt(argc, argv, "i:o:")) != -1){
		switch (opt){
			case 'i':
				inFileName = optarg;
				iFlag = 1;
				break;
			default:
            	fprintf(stderr, "Was given an unexpected argument, was given %d.\n Expected -i [input file]\nExiting\n", opt);
               	exit(EXIT_FAILURE);
       }
	}
	// Check to make sure we were given an input file
	if (iFlag == 0) {
       fprintf(stderr, "Expected minimum option -i\nNot Provided\nExiting\n");
       exit(EXIT_FAILURE);
    } // if


	/*-------------------------PROCESS FILE------------------------------*/
	inFile = fopen(inFileName, "r");

	// Loop through the lines of the file a second time
	while (fgets(lineBuffer, 100, inFile) !=NULL){


		// "add" 0
		// "nand" 1
		// "lw" 2
		// "sw"  3
		// "beq" 4
		// "jalr" 5
		// "halt" 6
		// "noop" 7;
        // R type
      	if(optCode == 0 || optCode == 1){

      	}

      	// I type
      	else if(optCode == 2 || optCode == 3 || optCode == 4){

      	}//else if

      	// J type
      	else if(optCode == 5){

      	}//else if

      	// O type
      	else if(optCode == 6 || optCode == 7){

      	}//else if

		// .fill directive
      	else if(optCode == -1 && strcmp( ".fill", lineArr[0]) == 0){

      	}//else if

      	// check if opcode is not valid
      	else{
      		fprintf(stderr, "Invalid instruction\n", lineArr[0]);
            exit(EXIT_FAILURE);
      	}//else

    }
    // Close files as apropriate
	fclose(inFile);
	if(writeToFileFlag == 1){
		fclose(outFile);
	}
    return 0;
}//main


int convert_num(int num){
	if (num & (1<<15) ) {
		num -= (1<<16);
	}
	return(num);
}

void print_state(statetype *stateptr){
	int i;
	printf("\n@@@\nstate:\n");
	printf("\tpc %d\n", stateptr->pc);
	printf("\tmemory:\n");
	for(i = 0; i < stateptr->nummemory; i++){
		printf("\t\tmem[%d]=%d\n", i, stateptr->mem[i]);
	}
	printf("\tregisters:\n");
	for(i = 0; i < NUMREGS; i++){
		printf("\t\treg[%d]=%d\n", i, stateptr->reg[i]);
	}
	printf("end state\n");
}

void print_stats(int n_instrs){
	printf("INSTRUCTIONS: %d\n", n_instrs); // total executed instructions
}	
