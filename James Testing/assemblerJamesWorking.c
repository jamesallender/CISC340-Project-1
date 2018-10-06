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


int findOppCode (char *name); // Function for find the opcode decimal value for a string

int isNumber (char *string); // returns 1 if it was given a number and -1 if not

int toNum (char *string); // returns the the decimal representation of a number respresented as a string

int handleParams (char *string, GHashTable* hash); // process the params from a assembly instructions

int main(int argc, char **argv){
	printf("Top of main\n");
	// Variables
	int opt; // the value of the opt form getopt
	FILE* inFile; // our input File
	FILE* outFile; // our output File
	char *inFileName; // our input file name
	char *outFileName; // our output file name
	int iFlag = 0; // Flag to tell us if an i option (requiered) has been given
	int writeToFileFlag = 0; // Flag to indicate if we shuld write to file or write to screen

	extern char *optarg; // The arguemnt to a opt - used by external
	extern int optind; // the int id of the curent opt location - used by external

	// Hash map that will hold the labels of the assembly code and the line number of the label
	GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal); 

	// Verify correct # of args given either 3 or 5 for 1 or 2 options (i,o)
	if (argc != 3 && argc != 5 ) {
	       fprintf(stderr, "Was not given either 1 or 2 sets of input arguments.\nShould be:\t-i [input file] -o [output file]\nOr:\t\t-i [input file]\nExiting\n");
	       exit(EXIT_FAILURE);
        }

    printf("befor While switch\n");
    // go through the args and get options
	while ((opt = getopt(argc, argv, "i:o:")) != -1){
		switch (opt){
			printf("in switch");
			case 'i':
				inFileName = optarg;
				printf("inFileName: %s\n", inFileName);
				iFlag = 1;
				break;
			case 'o':
				outFileName = optarg;
				printf("outFileName: %s\n", outFileName);
				writeToFileFlag = 1;
				break;
			default:
				// this dosent do anything, if an invalid option is given get opt will exit the program
				printf("in default");
            	fprintf(stderr, "Was given an unexpected argument, was given %d.\n Expected -i [input file] -o [output file]\nExiting\n", opt);
               	exit(EXIT_FAILURE);
       }
	}
	printf("After While switch\n");
	// Check to make sure we were given an input file
	if (iFlag == 0) {
       fprintf(stderr, "Expected minimum option -i\nNot Provided\nExiting\n");
       exit(EXIT_FAILURE);
    }

	// Process inFile
	/*		FIRST PASS OVER FILE	*/
	inFile = fopen(inFileName, "r");

	// Verify in file
    if(inFile == NULL)
	{
		fprintf(stderr, "\"%s\" File not found!\nExiting\n", inFileName);
		exit(EXIT_FAILURE);
	}
	int lineAddress = 0; // The current line of the file we are on
	char lineBuffer[100]; // Array to hold our line
	char * label; // lable var

	// Loop through our file
	while (fgets(lineBuffer, 100, inFile) !=NULL){
		// If we have found not white space at the begining of the line (i.e. a lable)
		if (lineBuffer[0] != ' ' && lineBuffer[0] != '\t'){
			
			// get lable string
			label = g_strdup(strtok (lineBuffer," \t\n"));

			// store the lable string and corisponding line value in the hash table
			g_hash_table_insert(hash, label, GINT_TO_POINTER(lineAddress));
			
			// Testing //
			int myVal = GPOINTER_TO_INT(g_hash_table_lookup(hash, label));
			printf ("label: %s | address: %d\n",label, myVal);           
			// Testing //

		}//if
		
		
		//increment line number
		lineAddress++;
	}

	fclose(inFile); // close the file

	/*		SECOND PASS	OVER FILE 	*/
	inFile = fopen(inFileName, "r");

	//int testPrint = GPOINTER_TO_INT(g_hash_table_lookup(hash, "start"));
	//		printf ("\n\n\n\naddress: %d\n\n\n\n"testPrint);  

	char *lineArr[4]; // array to hold the split elements of our line
	int lineNum = 0;

	while (fgets(lineBuffer, 100, inFile) !=NULL){
		// If Line has no label	
		if (lineBuffer[0] == ' ' | lineBuffer[0] == '\t'){
			lineArr[0] = strtok (lineBuffer," \t");//0th Element Opp Code
			lineArr[1] = strtok (NULL," \t\n"); //First Element
			lineArr[2] = strtok (NULL," \t\n"); //Second Element
			lineArr[3] = strtok (NULL," \t\n"); //Third Element
			//printf ("Opp Code: %d | string: %s\n", findOppCode(lineArr[0]), lineArr[0]);

		}// If Line has a label
        else{
			strtok (lineBuffer," \t"); //Label
			lineArr[0] = strtok (NULL," \t\n"); //0th Element Opp Code
			lineArr[1] = strtok (NULL," \t\n"); //First Element
			lineArr[2] = strtok (NULL," \t\n"); //Second Element
			lineArr[3] = strtok (NULL," \t\n"); //Third Element
			//printf ("Opp Code: %d | string: %s\n", findOppCode(lineArr[0]), lineArr[0]);

        }//else
		printf("--------------------\n");
		printf("lineArr[0]:%s\n", lineArr[0]);
	    printf("lineArr[1]:%s\n", lineArr[1]);
	    printf("lineArr[2]:%s\n", lineArr[2]);
	    printf("lineArr[3]:%s\n", lineArr[3]);

		/*	PACK VALUES INTO INTEGERS    */
	    int optCode = findOppCode(lineArr[0]);
	    int destReg;
	  	int regA;
	  	int regB;
	  	int offset;
	  	int instruction = 0;

	  	int optCodeOffset = 22;
		int regAOffset = 19;
	  	int regBOffset = 16;

      	// 31-25 unused
      	// 24-22 optCode
      	// 21-19 regA
      	// 18-16 regB
      	// 2-0 destReg or 15-0 offset/immidiate

        // R type
      	if(optCode == 0 || optCode == 1){
      		printf("Found R type Instruction\n");
      		// Get instruction params
      		regA = handleParams(lineArr[2], hash);
      		regB = handleParams(lineArr[3], hash);
      		destReg = handleParams(lineArr[1], hash);

      		printf("optcode: %d\n", optCode);
      		printf("regA: %d\n", regA);
      		printf("regB: %d\n", regB);
      		printf("destReg: %d\n", destReg);

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

      		printf("R instruction: %d\n", instruction);
      	}
      	// I type
      	else if(optCode == 2 || optCode == 3 || optCode == 4){
      		printf("Found I type Instruction\n");
      		// Get instruction params
      		regA = handleParams(lineArr[1], hash);
      		regB = handleParams(lineArr[2], hash);
      		offset = handleParams(lineArr[3], hash);

      		printf("optcode: %d\n", optCode);
      		printf("regA: %d\n", regA);
      		printf("regB: %d\n", regB);
      		

      		// Do shifting
      		optCode = optCode << optCodeOffset;
      		regA = regA << regAOffset;
      		regB = regB << regBOffset;

      		 if (g_hash_table_contains (hash, g_strdup(lineArr[3])) == 1){
      		 	offset = offset - lineNum + 1;
      		 }
			printf("offset: %d\n", offset);
      		offset = offset << 16;
      		offset = offset >> 16;

      		// Or instruction together
      		instruction = instruction | optCode;
      		instruction = instruction | regA;
      		instruction = instruction | regB;
      		instruction = instruction | offset - lineNum + 1;

      		printf("I instruction: %d\n", instruction);

      	}
      	// J type
      	else if(optCode == 5){
      		printf("Found J type Instruction\n");
      		// Get instruction params
      		regA = handleParams(lineArr[2], hash);
      		regB = handleParams(lineArr[3], hash);

      		printf("optcode: %d\n", optCode);
      		printf("regA: %d\n", regA);
      		printf("regB: %d\n", regB);

      		// Do shifting
      		optCode = optCode << optCodeOffset;
      		regA = regA << regAOffset;
      		regB = regB << regBOffset;

      		// Or instruction together
      		instruction = instruction | optCode;
      		instruction = instruction | regA;
      		instruction = instruction | regB;

      		printf("J instruction: %d\n", instruction);
      	}
      	// O type
      	else if(optCode == 6 || optCode == 7){
      		printf("Found O type Instruction\n");\
      		printf("optcode: %d\n", optCode);

      		// Do shifting
      		optCode = optCode << optCodeOffset;

      		// Or instruction together
      		instruction = instruction | optCode;

      		printf("J instruction: %d\n", instruction);
      	}
		// .fill directive
      	else if(optCode == -1 && strcmp( ".fill", lineArr[0]) == 0){
      		printf("Found .fill directive\n");
			instruction = handleParams(lineArr[1], hash);

      		printf(".fill directive: %d\n", instruction);
      	}
      	// opt codeNot found
      	else{
      		printf("Opt code '%d' was not found\n", optCode);
      	}
      	lineNum++;
    }
	fclose(inFile);
 
    return 0;
}//main


// Retruns the integer value of an optcode string. If an invalid opt code is given returns -1
int findOppCode (char *optCode){
	//printf("in findOppCode, optcode: %s\n", optCode);
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
int handleParams (char *paramString, GHashTable* hash){
/*		CAST AND ASSIGN VALUES 	  */
    
	int retVal;
	retVal = 0;
	if (isNumber (paramString) == 1 ){
		retVal = toNum ( paramString );
	}
	else if ( g_hash_table_contains (hash, g_strdup(paramString)) == 1 ){ // check if in hash table then look up
		retVal = GPOINTER_TO_INT(g_hash_table_lookup (hash, g_strdup(paramString)));
		printf("found a label!!!!\n");

	}else{
		fprintf(stderr, "Invalid value for regA in input file");
	}
	

    	return retVal;
}
