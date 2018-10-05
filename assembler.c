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


int findOppCode ( char *name);

int isNumber ( char *string);

int toNum ( char *string);

int main(int argc, char **argv)
{
	int opt; // the value of the opt form getopt
	FILE* inFile; // our input File
	FILE* outFile; // our output File
	char *inFileName; // our input file name
	char *outFileName; // our output file name
	bool iFlag = 0; // Flag to tell us if an i option (requiered) has been given

	extern char *optarg; 
	extern int optind;

	GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);

	printf("\nNum Args: %d\n", argc);

	// Verify correct # of args given
	if (argc != 3 && argc != 5 ) {
	       fprintf(stderr, "Was not given either 1 or 2 sets of input arguments.\nShould be: -i [input file] -o [output file]\nExiting\n");
	       exit(EXIT_FAILURE);
        }

    // go through the args and get options
    printf("befor while\n");
	while ((opt = getopt(argc, argv, "i:o:")) != -1){
		switch (opt){
			printf("top of switch");
			case 'i':
				inFileName = optarg;
				printf("inFileName: %s\n", inFileName);
				iFlag = 1;
				break;
			case 'o':
				outFileName = optarg;
				printf("outFileName: %s\n", outFileName);
				break;
			default:
            	fprintf(stderr, "Was given an unexpected argument.\n Expected -i [input file] -o [output file]\nExiting\n",
                    	argv[0]);
               	exit(EXIT_FAILURE);
       }
	}
	// Check to make sure we were given an input file
	if (iFlag == 0) {
       fprintf(stderr, "Expected minimum option -i\nNot Provided\nExiting\n");
       exit(EXIT_FAILURE);
    }

	// Process inFile
	/*		FIRST PASS		*/
	inFile = fopen(inFileName, "r");
	int lineAddress = 0;
	char line[5];
	int labelCount;
	while (fgets(line, 50, inFile) !=NULL){
		if (line[0] != ' ' && line[0] != '\t'){
			labelCount = labelCount + 1;
			char * label;
                                label = strtok (line," \t");
			g_hash_table_insert(hash, label, GINT_TO_POINTER(lineAddress));
			
			int myVal = GPOINTER_TO_INT(g_hash_table_lookup(hash, label));
			printf ("label: %s | address: %d\n",label, myVal);                                                  
		}//if
	lineAddress++;
	}
	fclose(inFile);

/*		SECOND PASS		*/
	inFile = fopen(inFileName, "r");

	char *lineArr[4];

	while (fgets(line, 50, inFile) !=NULL){
		//Cond: Line has no label	
		if (line[0] == ' ' | line[0] == '\t' && lineArr[0] != NULL){
			
			lineArr[0] = strtok (line," \t");//0th Element Opp Code
				
			lineArr[1] = strtok (NULL," \t"); //First Element

			lineArr[2] = strtok (NULL," \t"); //Second Element

			lineArr[3] = strtok (NULL," \t"); //Third Element

			printf ("Opp Code: %d | string: %s\n", findOppCode(lineArr[0]), lineArr[0]);

		}// if
		//Cond: Line has a label
        else{
			strtok (line," \t"); //Label

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


int findOppCode ( char *name){

	if ( strcmp( "add", name) == 0 ){
		return 0;
	}
	if ( strcmp( "nand", name) == 0 ){
		return 1;
	}
	if ( strcmp( "lw", name) == 0 ){
		return 2;
	}
	if ( strcmp( "sw", name) == 0 ){
		return 3;
	}
	if ( strcmp( "beq", name) == 0 ){
		return 4;
	}
	if ( strcmp( "jalr", name) == 0 ){
		return 5;
	}
	if ( strcmp( "halt", name) == 0 ){
		return 6;
	}
	if ( strcmp( "noop", name) == 0 ){
		return 7;
	}
	
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
