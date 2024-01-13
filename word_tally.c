#include <stdio.h>
#include <stdlib.h> // for malloc(), free()
#include <string.h>

#include "word_extractor.h"
#include "word_tally.h"

/**
 * A tool to hold the words we care about in an array, and
 * provide a method for processing the file.
 *
 */

// forward declarations
static int updateWordInTallyList(LLNode **wordLists, int maxLen, char *word);
 
/*
 * Here we do all the work, processing the
 * file and determining what to do for each word as we
 * read it.  Once we are done reading, we can then
 * examine our wordsToCheck list and see what their
 * state is
 */
int tallyWordsInFile(char *filename, LLNode **wordLists, int maxLen)
{
	struct WordExtractor *wordExtractor = NULL;
	char *aWord = NULL;
	// add any more variables that you need

	// create the extractor and open the file
	wordExtractor = weCreateExtractor(filename, maxLen);

    if (wordExtractor == NULL) {
		fprintf(stderr, "Failed creating extractor for '%s'\n", filename);
		return 0;
	}

    for (int i = 0; i < maxLen; i++) {
    		wordLists[i] = NULL; // set each wordList head to null
        }

	// read each word from the file using the WordExtractor,
	// and for each tally how often it has been used in
	// the appropriate list

	// In the loop, figure out whether we have seen this
	// word before, and do the appropriate thing if we have

	int totalWordCount = 0;

	while (weHasMoreWords(wordExtractor)) {
		aWord = weGetNextWord(wordExtractor);
		totalWordCount++;

		// figure out whether we have seen this word before,
		// and do the appropriate thing if we have
		updateWordInTallyList(wordLists, maxLen, aWord);
	}

	// is there anything else you need to do at the end of the loop?
	printf("Total word count %d\n", totalWordCount);

	// Close the file when we are done
	weDeleteExtractor(wordExtractor);

	return 1;
}

static int
updateWordInTallyList(LLNode **wordListHeads, int maxLen, char *word)
{
	int len = strlen(word); //take the length of the word
	if(len >= 0){ 
		if(wordListHeads[len] == NULL){ //check if that length of Node is null
                        char * myWord = strdup(word);
			wordListHeads[len] = llNewNode(myWord,1); //then append a new node
		}
		else{
			LLNode * myNode = llLookupKey(wordListHeads[len],word); //else check if that word is already in the LL
		
				if(myNode != NULL){
				myNode->value++; //if we have it we increment the value
				}
			else{   
                char * nextWord = strdup(word);
                LLNode * nextNode = llNewNode(nextWord,1);
				wordListHeads[len] = llPrepend(wordListHeads[len],nextNode); //otherwise we add it to our LL
			}
			return 1;
	    }
	}
	return 1;
}

