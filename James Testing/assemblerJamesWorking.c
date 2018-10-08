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

// void checkParam(char *param, int lineNumber, int paramNum); // checks the given param string to ensure it is valid

int findOppCode (char *name); // Function for find the opcode decimal value for a string

int isNumber (char *string); // returns 1 if it was given a number and -1 if not

int toNum (char *string); // returns the the decimal representation of a number respresented as a string

int handleParams (char *paramString, GHashTable* hash, int lineNumber, int paramNum); // process the params from a assembly instructions

int main(int argc, char **argv){
	// Variables
	int opt; // the value of the opt form getopt
	FILE* inFile; // our input File
	FILE* outFile; // our output File
	char *inFileName; // our input file name
	char *outFileName; // our output file name
	int iFlag = 0; // Flag to tell us if an i option (requiered) has been given
	int writeToFileFlag = 0; // Flag to indicate if we shuld write to file or write to screen
	int offsetMin = -32768;
	int offsetMax = 32767;

	extern char *optarg; // The arguemnt to a opt - used by external
	extern int optind; // the int id of the curent opt location - used by external

	// Hash map that will hold the labels of the assembly code and the line number of the label
	GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal); 

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
				// printf("inFileName: %s\n", inFileName);
				iFlag = 1;
				break;
			case 'o':
				outFileName = optarg;
				// printf("outFileName: %s\n", outFileName);
				writeToFileFlag = 1;
				break;
			default:
				// this dosent do anything, if an invalid option is given get opt will exit the program
				// printf("in default");
            	fprintf(stderr, "Was given an unexpected argument, was given %d.\n Expected -i [input file] -o [output file]\nExiting\n", opt);
               	exit(EXIT_FAILURE);
       }
	}
	// Check to make sure we were given an input file
	if (iFlag == 0) {
       fprintf(stderr, "Expected minimum option -i\nNot Provided\nExiting\n");
       exit(EXIT_FAILURE);
    } // if

	// Process inFile
	/*-------------------------FIRST PASS OVER FILE------------------------------*/
	inFile = fopen(inFileName, "r");

	// Verify in file
    if(inFile == NULL){
		fprintf(stderr, "\"%s\" In file not found!\nExiting\n", inFileName);
		exit(EXIT_FAILURE);
	} // if

	int lineAddress = 0; // The current line of the file we are on
	char lineBuffer[100]; // Array to hold our line
	char * label; // label var

	// Loop through the lines of the file
	while (fgets(lineBuffer, 100, inFile) !=NULL){
		// If we have found not white space at the begining of the line (i.e. a label)
		if (lineBuffer[0] != ' ' && lineBuffer[0] != '\t'){
			// get label string
			label = g_strdup(strtok (lineBuffer," \t\n"));

			if(strlen(label) > 6){
				fprintf(stderr, "Label '%s' is too long. Max 6 chars.\nExiting\n", label);
               	exit(EXIT_FAILURE);
			} // if
			// Check that the lable starts with a letter
			if(isalpha(label[0])){
				// loop through the lable characters
				for (int i = 0; i < strlen(label); i++){
					//check that it is only letters and numbers are in the lable
					if (!isalpha(label[i]) && !isdigit(label[i])){
						fprintf(stderr, "Label '%s' contains invalid characters. Must contain only numbers and letterts.\nExiting\n", label);
               			exit(EXIT_FAILURE);
					} // if
				} // for
				// Check if the lable is alredy in the hash map
				if (g_hash_table_contains (hash, g_strdup(label)) == 1){
					fprintf(stderr, "Label '%s' apeared more than once.\nExiting\n", label);
               		exit(EXIT_FAILURE);
				}// if
				else{
					// store the label string and corisponding line value in the hash table
					g_hash_table_insert(hash, label, GINT_TO_POINTER(lineAddress));
				} // else
			} // if 
			// if the lable started with an invalid character
			else{
				fprintf(stderr, "Label '%s' starts with an invalid characters. Must start with a letter.\nExiting\n", label);
               	exit(EXIT_FAILURE);
			}// else
		}// if
		//increment line number
		lineAddress++;
	}// while

	fclose(inFile); // close the file

	/*-------------------------SECOND PASS OVER FILE------------------------------*/
	inFile = fopen(inFileName, "r");
	outFile = fopen(outFileName, "w");

	char *lineArr[4]; // array to hold the split elements of our line
	int lineNum = 0;
	int loopStarted = 0;

	// Loop through the lines of the file a second time
	while (fgets(lineBuffer, 100, inFile) !=NULL){
		// This is used to ensure a new line isent te first or last thing in the output file
		if(writeToFileFlag == 1 && loopStarted == 1){
			fprintf(outFile, "\n"); // write to file
		}
		loopStarted = 1; // toggel flag
		// If Line has no label	
		if (lineBuffer[0] == ' ' | lineBuffer[0] == '\t'){
			lineArr[0] = strtok (lineBuffer," \t\n");//0th Element Opp Code
			lineArr[1] = strtok (NULL," \t\n"); //First Element
			lineArr[2] = strtok (NULL," \t\n"); //Second Element
			lineArr[3] = strtok (NULL," \t\n"); //Third Element

		}// If Line has a label
        else{
			strtok (lineBuffer," \t"); //Label
			lineArr[0] = strtok (NULL," \t\n"); //0th Element Opp Code
			lineArr[1] = strtok (NULL," \t\n"); //First Element
			lineArr[2] = strtok (NULL," \t\n"); //Second Element
			lineArr[3] = strtok (NULL," \t\n"); //Third Element

        }//else
		// printf("--------------------\n");
		// printf("lineArr[0]:%s\n", lineArr[0]);
	 //    printf("lineArr[1]:%s\n", lineArr[1]);
	 //    printf("lineArr[2]:%s\n", lineArr[2]);
	 //    printf("lineArr[3]:%s\n", lineArr[3]);

		/*	PACK VALUES INTO INTEGERS    */
		// if (lineArr[0] == NULL || strcmp( "\n", lineArr[0]) == 0){
  //     			fprintf(stderr, "Opt Code '%s' not given\nExiting\n");
  //              	exit(EXIT_FAILURE);
  //     		}
	    int optCode = findOppCode(lineArr[0]);
	    int destReg;
	  	int regA;
	  	int regB;
	  	int offset;
	  	int instruction = 0;

	  	int optCodeOffset = 22;
		int regAOffset = 19;
	  	int regBOffset = 16;
	  	int negMask = 65535;

      	// 31-25 unused
      	// 24-22 optCode
      	// 21-19 regA
      	// 18-16 regB
      	// 2-0 destReg or 15-0 offset/immidiate

        // R type
      	if(optCode == 0 || optCode == 1){
      		// printf("Found R type Instruction\n");
      		// Get instruction params
      		regA = handleParams(lineArr[2], hash, lineNum, 2);
      		regB = handleParams(lineArr[3], hash, lineNum, 3);
      		destReg = handleParams(lineArr[1], hash, lineNum, 1);

      		// printf("optcode: %d\n", optCode);
      		// printf("regA: %d\n", regA);
      		// printf("regB: %d\n", regB);
      		// printf("destReg: %d\n", destReg);

      		// Do shifting
      		optCode = optCode << optCodeOffset;
      		regA = regA << regAOffset;
      		regB = regB << regBOffset;

      		// Or instruction together
      		//instruction = instruction | optCode | regA | regB | destReg;
      		instruction = instruction | optCode;
      		instruction = instruction | regA;
      		instruction = instruction | regB;
      		instruction = instruction | destReg;
      	}
      	// I type
      	else if(optCode == 2 || optCode == 3 || optCode == 4){
      		// printf("Found I type Instruction\n");
      		// Get instruction params
      		regA = handleParams(lineArr[1], hash, lineNum, 1);
      		regB = handleParams(lineArr[2], hash, lineNum, 2);
      		offset = handleParams(lineArr[3], hash, lineNum, 3);

      		// printf("optcode: %d\n", optCode);
      		// printf("regA: %d\n", regA);
      		// printf("regB: %d\n", regB);
      		

      		// Do shifting
      		optCode = optCode << optCodeOffset;
      		regA = regA << regAOffset;
      		regB = regB << regBOffset;

      		 if (g_hash_table_contains (hash, g_strdup(lineArr[3])) == 1){
      		 	if (offset - lineNum < 0){
      		 		offset = offset - lineNum - 1;
      		 	}//if
      		 	else if (offset - lineNum >= 0){
      		 		offset = offset - lineNum;
      		 	}//else if
      		 }//if
			//printf("offset: %d\n", offset);
      		offset = offset & negMask;


      		// Or instruction together
      		instruction = instruction | optCode;
      		instruction = instruction | regA;
      		instruction = instruction | regB;
      		instruction = instruction | offset;
      	}//else if
      	// J type
      	else if(optCode == 5){
      		// printf("Found J type Instruction\n");
      		// Get instruction params
      		regA = handleParams(lineArr[1], hash, lineNum, 1);
      		regB = handleParams(lineArr[2], hash, lineNum, 2);

      		// printf("optcode: %d\n", optCode);
      		// printf("regA: %d\n", regA);
      		// printf("regB: %d\n", regB);

      		// Do shifting
      		optCode = optCode << optCodeOffset;
      		regA = regA << regAOffset;
      		regB = regB << regBOffset;

      		// Or instruction together
      		instruction = instruction | optCode;
      		instruction = instruction | regA;
      		instruction = instruction | regB;
      	}//else if
      	// O type
      	else if(optCode == 6 || optCode == 7){
      		// printf("Found O type Instruction\n");
      		// printf("optcode: %d\n", optCode);

      		// Do shifting
      		optCode = optCode << optCodeOffset;

      		// Or instruction together
      		instruction = instruction | optCode;
      	}//else if
		// .fill directive
      	else if(optCode == -1 && strcmp( ".fill", lineArr[0]) == 0){
      		// printf("Found .fill directive\n");
			instruction = handleParams(lineArr[1], hash, lineNum, 1);
      	}//else if
      	// check if opcode is not valid
      	else{
      		fprintf(stderr, "Opt code '%s' is invalid found\n", lineArr[0]);
            exit(EXIT_FAILURE);
      	}//else
      	if(writeToFileFlag == 0){
      		printf("%d\n", instruction);
      	}else{
      		fprintf(outFile, "%d", instruction); // write to file
      	}
      	lineNum++;
    }
	fclose(inFile);
	if(writeToFileFlag == 1){
		fclose(outFile);
	}
    return 0;
}//main


// void checkParam(char *param, int lineNumber, int paramNum){
// 	if (lineArr[0] == NULL || strcmp( "\n", lineArr[0]) == 0){
//   			fprintf(stderr, "Instruction on line number %d is invalid, error in param %d\nExiting\n");
//            	exit(EXIT_FAILURE);
//   		}
// }

// Retruns the integer value of an optcode string. If an invalid opt code is given returns -1
int findOppCode (char *optCode){
	//printf("in findOppCode, optcode: %s\n", optCode);
	int optCodeInt;

	// printf("optCode: %s\n", optCode);

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

// function returns 0 if the given string was not a number otherwise returns 1 if string was a number
int isNumber (char *string){
	char *refBuf;
	strtol (string, &refBuf, 8);
	if ( *refBuf == '\0' ){
		return 1;
	}
	else {
		return 0;
	}
}//findNumValue

// Function converts a number in string form into its integer form
int toNum (char *string){

	char *refBuf;
	int result;
	result = strtol (string, &refBuf, 8);
	return result;

}

// process the params from a assembly instructions and returns the int value
int handleParams (char *paramString, GHashTable* hash, int lineNumber, int paramNum){
	if (paramString == NULL || strcmp( "\n", paramString) == 1 || strcmp( "\t", paramString) == 1 || strcmp( " ", paramString) == 1){
  			fprintf(stderr, "Instruction on line number %d is invalid, error in param %d\nExiting\n", lineNumber, paramNum);
           	exit(EXIT_FAILURE);
  		}
    
	int retVal;
	retVal = 0;
	if (isNumber (paramString) == 1 ){
		retVal = toNum ( paramString );
	}// if
	else if ( g_hash_table_contains (hash, g_strdup(paramString)) == 1 ){ // check if in hash table then look up
		retVal = GPOINTER_TO_INT(g_hash_table_lookup (hash, g_strdup(paramString)));
		// printf("found a label!!!!\n");

	}//else if
	else{
		fprintf(stderr, "Invalid value '%s' on line %d, param %d ", paramString, lineNumber, paramNum);
	}//esle
    	return retVal;
}