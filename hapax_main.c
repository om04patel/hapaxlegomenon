#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "word_tally.h"


/** function to be passed in to llFree to delete allocated keys */
void deleteKey(LLNode *node, void *userdata)
{
	if (node->key != NULL) {
		free(node->key);
	}
}


/** Delete the contents of all of the word lists
 *
 * This function assumes that both the nodes and
 * the keys within the nodes have been allocated
 * using malloc() and need to be freed.
 */
void
deleteWordLists(LLNode **wordListHeads, int maxLen)
{
	int i;

	for (i = 0; i < maxLen; i++) {
		if (wordListHeads[i] != NULL) {
			llFree(wordListHeads[i], deleteKey, NULL);
			wordListHeads[i] = NULL;
		}
	}
}


/** print out all of the data in a word list */
int
printData(char *filename, LLNode *wordListHeads[], int maxLen)
{
	LLNode *node;
	int i;

	printf("All word count data from file '%s':\n", filename);

	/**
	 * For each length, if the list is not null, print out
	 * the values in the list
	 */
	for (i = 0; i <= maxLen; i++) {
		node = wordListHeads[i];
		if (node != NULL) {
			printf("Length %d:\n", i);
			while (node != NULL) {
				printf("    '%s' %d\n", node->key, node->value);
                node = node->next;
			}
		}
	}
	return 0;
}

int
printHapax(char *filename, LLNode *wordListHeads[],
		int maxLen, int hapaxLength)
{
	int countTheHapx = 0;
    printf("hapax legomenon from file %s\n",filename);

        LLNode *node = wordListHeads[hapaxLength]; //access the node with the desired length
        while (node != NULL) { 
            if (1 == node->value) { //check if that is the only occurence and therefore a hapax legomenon
                printf("%s\n", node->key); //we print the word
                countTheHapx++;
            }
            node = node->next;  //move onto next node
        
    }

    return countTheHapx;
}


/* print out the command line help */
void
usage()
{
	fprintf(stderr, "\n");
	fprintf(stderr, "Find and print the hapax legomena in one or more files.\n");
	fprintf(stderr, "A \"hapax legomenon\" is a word that occurs only once in the file\n");

	fprintf(stderr, "\n");
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "    hapax [<options>] <datafile> [ <datafile> ...]\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "Options:\n");
	fprintf(stderr, "-d     : print out all data loaded before printing hapax legomena.\n");
	fprintf(stderr, "-h     : this help.  You are looking at it.\n");
	fprintf(stderr, "-l <N> : only print hapax legomena of length <N>.\n");
	fprintf(stderr, "       : If no -l option is given, all hapax legomena are printed.\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "Sample command line:\n");
	fprintf(stderr, "    hapax -l 5 smalldata.txt");
	fprintf(stderr, "\n");
	fprintf(stderr, "This example would print all words of length 5 that exist in the\n");
	fprintf(stderr, "file \"smalldata.txt\".\n");
	fprintf(stderr, "\n");

	// exit the program
	exit(1);
}


/**
 * Program mainline
 */

// define the maximum length of word we will look for, and by extension,
// the number of entries that must be in the array of word lists
#define	MAX_WORD_LEN	24

int
main(int argc, char **argv){
	int shouldPrintData = 0, didProcessing = 0, printHapaxLength = -1;

	/** TODO: allocate an array of list heads of the required size */
	struct LLNode * wordListHeads[MAX_WORD_LEN + 1];
    char * filename = NULL;
	for(int i = 0; i < MAX_WORD_LEN + 1; i++){
		wordListHeads[i] = NULL;  //initialise each node to null
	}
   
	for (int i = 1; i < argc; i++) {
	if(argv[i][0] == '-'){
    	if (strcmp(argv[i],"-h") == 0){  //return help menu
        	usage();
        	return 0;
    	}
    	else if (strcmp(argv[i],"-d") == 0){
        	shouldPrintData = 1; //conditional for print data
    	}
    	else if (strcmp(argv[i],"-l") == 0 && i + 1 < argc){
        	printHapaxLength = atoi(argv[++i]); //convert the string to int
			if(printHapaxLength < 0){
				printf("Invalid number < 0\n");  //conditional check to make sure ints are positive
				return 0;
			}
    	}
	}
	else
	{
		filename = argv[i];
	}
	}
	

// After processing options, check if a filename was provided and process it
if (filename != NULL) {
    int result = tallyWordsInFile(filename, wordListHeads, MAX_WORD_LEN); //call tallywords function
    if (result == 0) {
        fprintf(stderr, "Error: Processing '%s' failed -- exiting\n", filename);
        return 1;
    }
    didProcessing = 1;
	printf("Tally Loaded\n");

    if (shouldPrintData == 1) {
        printData(filename, wordListHeads, MAX_WORD_LEN); //call printData based on user input
    }
    if (printHapaxLength >= 0) {
        int hapaxResult = printHapax(filename, wordListHeads, MAX_WORD_LEN, printHapaxLength); //calling hapax
        if (hapaxResult < 0) {
            fprintf(stderr, "Error: Unable to print hapax for '%s'\n", filename);
        }
    }
	if (printHapaxLength == -1) { //if no value for hapax length is provided
            printf("All hapax legomena from file %s:\n", filename); //print all hapax
            for (int i = 1; i <= MAX_WORD_LEN; i++) {
                struct LLNode *node = wordListHeads[i];
                while (node != NULL) {
                    if (node->value == 1) {
                        printf("%s\n", node->key);
                    }
                    node = node->next;
                }
            }
}   }

	if (!didProcessing) {
		fprintf(stderr, "No data processed -- provide the name of"
				" a file on the command line\n");
		usage();
		return 1;
	}

	deleteWordLists(wordListHeads,MAX_WORD_LEN);  //calling deleteWordLists to free memory
	
	return 0;}

