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


int findOppCode ( char *name); // Function for find the opcode decimal value for a string

int isNumber ( char *string); // returns 1 if it was given a number and -1 if not

int toNum ( char *string); // returns the the decimal representation of a number respresented as a string

int main(int argc, char **argv) // Main
{
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
	       fprintf(stderr, "Was not given either 1 or 2 sets of input arguments.\nShould be: -i [input file] -o [output file]\nExiting\n");
	       exit(EXIT_FAILURE);
        }

    // go through the args and get options
	while ((opt = getopt(argc, argv, "i:o:")) != -1){
		switch (opt){
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
            	fprintf(stderr, "Was given an unexpected argument, was given %s.\n Expected -i [input file] -o [output file]\nExiting\n", opt);
               	exit(EXIT_FAILURE);
       }
	}
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
		fprintf(stderr, "\"%s\" File NOT FOUND!\n", inFileName);
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
			label = strtok (lineBuffer," \t");

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

	char *lineArr[4]; // array to hold the split elements of our line

	while (fgets(lineBuffer, 50, inFile) !=NULL){
		// If Line has no label	
		if (lineBuffer[0] == ' ' | lineBuffer[0] == '\t' && lineArr[0] != NULL){
			lineArr[0] = strtok (lineBuffer," \t");//0th Element Opp Code
			lineArr[1] = strtok (NULL," \t"); //First Element
			lineArr[2] = strtok (NULL," \t"); //Second Element
			lineArr[3] = strtok (NULL," \t"); //Third Element
			printf ("Opp Code: %d | string: %s\n", findOppCode(lineArr[0]), lineArr[0]);

		}// If Line has a label
        else{
			strtok (lineBuffer," \t"); //Label
			lineArr[0] = strtok (NULL," \t"); //0th Element Opp Code
			lineArr[1] = strtok (NULL," \t"); //First Element
			lineArr[2] = strtok (NULL," \t"); //Second Element
			lineArr[3] = strtok (NULL," \t"); //Third Element
			printf ("Opp Code: %d | string: %s\n", findOppCode(lineArr[0]), lineArr[0]);

        }//else

/*		CAST AND ASSIGN VALUES 	  */
        int optCode = findOppCode(lineArr[0]);
	int regA;
	int regB;
	if (isNumber (lineArr[1]) == 1 ){
		regA = toNum ( lineArr[1]);
	}
	else{
		fprintf(stderr, "Invalid value for regA in input file");
	}
	if (isNumber (lineArr[2]) == 1 ){
		regB = toNum ( lineArr[2]);
	}
	else{
		fprintf(stderr, "Invalid value for regB in input file");
	}
	if (1){
		printf("");
	}
	printf("\n\nregA: %d | regB: %d\n\n", regA, regB);
        int instruction;



/*              PACK VALUES INTO INTEGERS    */
        // R type
      	if(optCode == 0 || optCode == 1){
      		printf("Found R type Instruction\n");
      		optCode = optCode << 22;
		//regA = regA << 19;
      		//instruction = instruction | optCode | regA;
		
      		printf("instruction: %d | opCode: %d\n", instruction,optCode);

      	}
      	// I type
      	else if(optCode == 2 || optCode == 3 || optCode == 4){
      		printf("Found I type Instruction\n");

      	}
      	// J type
      	else if(optCode == 5){
      		printf("Found J type Instruction\n");

      	}
      	// O type
      	else if(optCode == 6 || optCode == 7){
      		printf("Found O type Instruction\n");

      	}
      	// Not found
      	else{
      		printf("Opt code was not found\n");
      	}
    }
	fclose(inFile);
 
    return 0;
}//main


// Retruns the integer value of an optcode string. If an invalid opt code is given returns -1
int findOppCode ( char *optCode){

	printf("in findOppCode, optcode: %s\n", optCode);

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

int isNumber ( char *string){
	char *refBuf;
	strtol (string, &refBuf, 8);
	if ( refBuf[0] != '\0' ){
		return 0;
	}
	else {
		return 1;
	}
}//findNumValue 5x67

int toNum ( char *string){

	char *refBuf;
	int result;
	result = strtol (string, &refBuf, 8);
	return result;

}
