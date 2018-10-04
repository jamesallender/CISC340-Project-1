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

int main(int argc, char **argv)
{
	char *argument = argv[2];

    char line[8];

	char* pEnd;

	int index;

	index = 0;

	int opt;

	FILE* inFile;
	FILE* outFile;
	char *inFileName;
    char *outFileName;
    // extern char *optarg;
    // extern int optind, optopt;

	int labelCount;

	extern char * optarg;

	GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);

	printf("\nNum Args: %d\n", argc);

	// Verify correct # of args given
	if (argc != 3 && argc != 5 ) {
	       fprintf(stderr, "Expected minimum option -i\n");
	       exit(EXIT_FAILURE);
        }

    // go through the args and get options
    printf("befor while\n");
	while ((opt = getopt(argc, argv, "io:")) != -1){
		switch (opt){
			printf("top of switch");
			case 'i':
				printf("optarg: %s\n", optarg)
				//inFileName = optarg;
				inFileName = argv[2];
				printf("inFileName: %s", inFileName);
				break;
			case 'o':
				outFileName = optarg;
				printf("outFileName: %s", inFileName);
				break;
			default:
            	fprintf(stderr, "Usage: %s [-i input file] \n",
                    	argv[0]);
               	exit(EXIT_FAILURE);
       }
	}

	// Process in File
     inFile = fopen(inFileName, "r");
			int lineAddress = 0;
			while (fgets(line, 50, inFile) !=NULL)
        		{

				if (line[0] == ' ' | line[0] == '\t'){}

				else{
					labelCount = labelCount + 1;
					char * label;
                                        label = strtok (line," \t");
					g_hash_table_insert(hash, label, GINT_TO_POINTER(lineAddress));
					
					int myVal = GPOINTER_TO_INT(g_hash_table_lookup(hash, label));
					printf ("label: %s | address: %d\n",label, myVal);                                                  
				}//else
			lineAddress++;
			}
			
			fclose(inFile);


/*		SECOND PASS		*/


			inFile = fopen(inFileName, "r");

			char *lineArr[6];

			while (fgets(line, 50, inFile) !=NULL)
                        {
			
				//Cond: Line has no label	
				if (line[0] == ' ' | line[0] == '\t' && lineArr[0] != NULL){
					
					lineArr[0] = strtok (line," \t");//Opp Code
						
					lineArr[1] = strtok (NULL," \t"); //First Element

					lineArr[2] = strtok (NULL," \t"); //Second Element

					lineArr[3] = strtok (NULL," \t"); //Third Element

					printf ("Opp Code: %d | string: %s\n", findOppCode(lineArr[0]), lineArr[0]);

				}
    				
				//Cond: Line has a label
                else{
					lineArr[0] = strtok (line," \t"); //Label

					lineArr[1] = strtok (NULL," \t"); //Opp Code
	
					lineArr[2] = strtok (NULL," \t"); //First Element

					lineArr[3] = strtok (NULL," \t"); //Second Element

					lineArr[4] = strtok (NULL," \t"); //Third Element
	
					printf ("Opp Code: %d | string: %s\n", findOppCode(lineArr[1]), lineArr[1]);

                                }//else
                            	
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


