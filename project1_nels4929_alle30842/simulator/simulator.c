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
#define NUMREG 8
#define NUMMEMORY 65536

// Structure to hold the state of the simulated machine durring the run of a machine code program
typedef struct state_struct {
	int pc;	// program counter
	int mem[NUMMEMORY]; // array to holm the memory of size NUMMEMORY
	int reg[NUMREG]; // array to hold the registers of size NUMREG
	int num_memory;	// int that holds the highest location of memory used
} statetype;

int convert_num(int num); // sign extends a 16bit number into its 32 bit equivilent
void print_state(statetype *stateptr); // prints the current state of the machine
void print_stats(int n_instrs); // prints statistics on the run of the machine code

int main(int argc, char **argv){
	// Variables
	statetype state;
	int opt; // the value of the opt form getopt
	FILE* inFile; // our input File
	char *inFileName; // our input file name
	int iFlag = 0; // Flag to tell us if an i option (requiered) has been given
	int writeToFileFlag = 0;
	extern char *optarg; // The arguemnt to a opt - used by external
	extern int optind; // the int id of the curent opt location - used by external
	int lineInt;
	int lineArr[4];
	int haltFlag =0;
	int n_instrs =0;
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

    // open file
	inFile = fopen(inFileName, "r");
	char lineBuffer[100]; // Array to hold our line
	// Loop through the lines of the file a second timei
	int i = 0;

	// loops through input file
	while (fgets(lineBuffer, 100, inFile) !=NULL){
		// get line num value
		lineInt  = strtol(lineBuffer,NULL,10);
		// store num into memory
		state.mem[i] = lineInt;
		// increment num_memory
		state.num_memory++;	
		i++;
	}	

	//set pc
	state.pc =0;

	// runn until a halt is found and timidity break
	while (1){

		// get optcode section of instruction
		int optCode = state.mem[state.pc] & 0x1C00000;
		// shift into place
		optCode = optCode >> 22;
	
		// check for halt and end
		if (optCode == 6){
			n_instrs ++;
			break;
		}
	
		// get regA section of instruction
		int regA = state.mem[state.pc] & 0x380000;
		// shift into place
		regA = regA >> 19;
	        
	    // get regB section of instruction
		int regB = state.mem[state.pc] & 0x70000;
		// shift into place
		regB = regB >> 16;
	 
	 	// get imm section of instruction
		int imm = state.mem[state.pc] & 0xFFFF;
		// sign exted the immidiate val
		imm = convert_num(imm);

		// get optcode section of instruction
		int destR = state.mem[state.pc] & 7;
	 
	 	// Print the state of the machine
		print_state(&state);
	 
		// ADD
	    if(optCode == 0){
			state.reg[destR] = state.reg[regA] + state.reg[regB];
	      	state.pc = state.pc +1;
		}
		// NAND
	    else if(optCode == 1){
			state.reg[destR] =~( state.reg[regA] & state.reg[regB]);
	      	state.pc = state.pc +1;
		}
	
		// LW
	    else if(optCode == 2){
			state.reg[regA] = state.mem[state.reg[regB] + imm];
	      	state.pc = state.pc +1;
		}
		// SW
	    else if(optCode == 3){
			state.mem[state.reg[regB] + imm] = state.reg[regA]; 
	      	state.pc = state.pc +1;
	      	if((state.reg[regB] + imm)>=state.num_memory){
	      		state.num_memory = state.reg[regB] + imm + 1;
	      	}
		}
		// BEQ
	    else if(optCode == 4){
			if (state.reg[regA] == state.reg[regB]){
				state.pc = state.pc +  imm;
			}
	      	state.pc = state.pc +1;
		}
		// JALR
	    else if(optCode == 5){
			state.reg[regA] = state.pc +1;
			state.pc =state.reg[regB];
	    }
		// NOOP
	    else if(optCode == 7){
			state.pc = state.pc +1;
	    }
	    // increment the number of instructions
		n_instrs ++;
	}//while

   	// Close files as apropriate
	fclose(inFile);

	// Print apropriate information
    print_state(&state);
	printf("machine halted\n");
	print_stats(n_instrs);

	return 0;
}//main


// convert_num function sign extends a 16bit number into its 32 bit equivilent
int convert_num(int num){
	if (num & (1<<15) ) {
		num -= (1<<16);
	}
	return(num);
}

// print_state function prints the current state of the machine
void print_state(statetype *stateptr){
	int i;
	printf("\n@@@\nstate:\n");
	printf("\tpc %d\n", stateptr->pc);
	printf("\tmemory:\n");
	for(i = 0; i < stateptr->num_memory; i++){
		printf("\t\tmem[%d]=%d\n", i, stateptr->mem[i]);
	}
	printf("\tregisters:\n");
	for(i = 0; i < 8; i++){
		printf("\t\treg[%d]=%d\n", i, stateptr->reg[i]);
	}
	printf("end state\n");
}

// print_stats finction prints statistics on the run of the machine code
void print_stats(int n_instrs){
	printf("INSTRUCTIONS: %d\n", n_instrs); // total executed instructions
}

	
