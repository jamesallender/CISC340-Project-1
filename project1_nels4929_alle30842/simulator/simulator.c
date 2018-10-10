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

int findOppCode (char *name); // Function for find the opcode decimal value for a string

int isNumber (char *string); // returns 1 if it was given a number and -1 if not

int toNum (char *string); // returns the the decimal representation of a number respresented as a string

int handleParams (char *paramString, GHashTable* hash, int lineNumber, int paramNum); // process the params from a assembly instructions

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
	FILE* outFile; // our output File
	char *inFileName; // our input file name
	char *outFileName; // our output file name
	int iFlag = 0; // Flag to tell us if an i option (requiered) has been given

	extern char *optarg; // The arguemnt to a opt - used by external
	extern int optind; // the int id of the curent opt location - used by external

	// Verify correct # of args given either 3 or 5 for 1 or 2 options (i,o)
	if (argc != 3 && argc != 5 ) {
	       fprintf(stderr, "Was not given either 1 or 2 sets of input arguments.\nShould be:\t-i [input file] -o [output file]\nOr:\t\t-i [input file]\nExiting\n");
	       exit(EXIT_FAILURE);
        }

    // go through the args and get options
	while ((opt = getopt(argc, argv, "i:o:")) != -1){
		switch (opt){
			case 'i':
				inFileName = optarg;
				iFlag = 1;
				break;
			case 'o':
				outFileName = optarg;
				writeToFileFlag = 1;
				break;
			default:
            	fprintf(stderr, "Was given an unexpected argument, was given %d.\n Expected -i [input file] -o [output file]\nExiting\n", opt);
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
	outFile = fopen(outFileName, "w");

	// Loop through the lines of the file a second time
	while (fgets(lineBuffer, 100, inFile) !=NULL){

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


// Retruns the integer value of an optcode string. If an invalid opt code is given returns -1
int findOppCode (char *optCode){
	int optCodeInt;

	if ( strcmp( "add", optCode) == 0 ){
		optCodeInt = 0;
	}
	else if ( strcmp( "nand", optCode) == 0 ){
		optCodeInt = 1;
	}
	else if ( strcmp( "lw", optCode) == 0 ){
		optCodeInt = 2;
	}
	else if ( strcmp( "sw", optCode) == 0 ){
		optCodeInt = 3;
	}
	else if ( strcmp( "beq", optCode) == 0 ){
		optCodeInt = 4;
	}
	else if ( strcmp( "jalr", optCode) == 0 ){
		optCodeInt = 5;
	}
	else if ( strcmp( "halt", optCode) == 0 ){
		optCodeInt = 6;
	}
	else if ( strcmp( "noop", optCode) == 0 ){
		optCodeInt = 7;
	}
	else{
		optCodeInt = -1;
	}
	return optCodeInt;
}//findOppCode

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
