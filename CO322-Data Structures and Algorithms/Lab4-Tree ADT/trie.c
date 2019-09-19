#include <stdio.h>
#include<time.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 26

int nodeCount=0;

//node in the trie
typedef struct tNode *Tptr;

typedef struct tNode{
	Tptr children[SIZE];
	unsigned int isLeaf: 1;// 1 -> when node is a leaf node
} tNode;

// get the index of the caharacter
int getCharIndex(char c){
    return c-'a';
}

//inserting new words to nodes
void insertWord(Tptr elemnt, char *word) {

	Tptr root = elemnt;//start from the root newNode
	int i;

	int k, j;
			// Remove Characters in String Except Alphabets
	    for(k = 0; word[k] != '\0'; ++k){
	        while (!( (word[k] >= 'a' && word[k] <= 'z') || (word[k] >= 'A' && word[k] <= 'Z') || word[k] == '\0') ){
	            for(j = k; word[j] != '\0'; ++j){
	                word[j] = word[j+1];
	            }
	            word[j] = '\0';
	        }
	    }
	    // printf("Output String: %s",word);

	 	for (i = 0; i < strlen(word); i++) {


			 		// nodeCount = nodeCount+1;
					int charvalIndex = getCharIndex(word[i]);
					Tptr current = elemnt->children[charvalIndex];
						// printf("Output index: %d\n",charvalIndex);
						// create a new node if path doesn't exists
					if (current == NULL) {
						nodeCount = nodeCount+1;
						current = malloc (sizeof (tNode));
						current->isLeaf = 0;
						for(int i = 0; i < SIZE; i++){
								current->children[i] = NULL;
						}

					}


					if(i + 1 == strlen(word)){
						current->isLeaf = 1;// mark current node as leaf.We have reached the end of the string
					}

					elemnt->children[charvalIndex] = current;
					elemnt = elemnt->children[charvalIndex];
					// nodeCount = nodeCount+1;
					// printf("%d\n",nodeCount );
		}

	elemnt = root;
}


char *join(char *prefix, char part) {

	char *str = malloc (sizeof (char) * (strlen (prefix) + 2));
	int i = 0;
		while (prefix[i] != '\0') {
			str[i] = prefix[i++];}

	str[i++] = part;
	str[i] = '\0';

	return str;
}

//recursive function to print auto suggested words for a given node
void printSuggestions(Tptr elemnt, char *prefix) {

	if (elemnt == NULL){
		return;
	}

	if (elemnt->isLeaf){
		 printf("%s\n", prefix);
	 }

	for (int i = 0; i < SIZE; i++){
		if(elemnt->children[i] != NULL){
			printSuggestions (elemnt->children[i], join (prefix, i + 'a'));
		}
	}
}

//autocomplete the according to the prefix
void autocomplete(Tptr elemnt, char *prefix) {
	for (int i = 0; i < strlen (prefix); i++){
		elemnt = elemnt->children[prefix[i] - 'a'];
	}
	printSuggestions (elemnt, prefix);
}


// test above functions
int main(int argc, char **argv) {

	tNode node;
	node.isLeaf = 0;
	for (int i = 0; i < SIZE; i++){
		 node.children[i] = NULL;
	 }

	FILE *file;
	char *fileName;
	char ch;

	// Check if a filename has been specified in the command
  if (argc < 2){
        printf("Missing Filename\n");
        return(1);
   }
   else{
        fileName = argv[1]; //get the file from the command line as an argument
		    file = fopen(fileName,"r");// Open file in read-only mode
   }

	 if (file == NULL){// Check whether an available file has been specified in the command
       fprintf(stderr, "Error while opening the file\n");
       exit(0);
   }

	char str[SIZE];
  int i=0;

	clock_t beginTime_Insert = clock();//begin counting time for inserting
	while (!feof (file)) {
		fscanf (file, "%s", str);
		strlwr(str);// uppercase to lowercase conversion in the wordlist
		insertWord(&node, str);//insert the file to the trie
		// printf("%s%d\n",str,i++);
	}

	clock_t endTime_Insert = clock();//end counting time for inserting
	double spentTime_Insert = (double)(endTime_Insert-beginTime_Insert)/CLOCKS_PER_SEC;
	printf(">>>>>>>>>>Insertion Time: %f s\n",spentTime_Insert);//total time spent for insertion
	fclose (file);

	char input[100];

	while (1) {
		printf("\n");
		printf ("Enter a keyword to search: ");//enter word to search
		scanf ("%s", input); //scan the letter/word from the command line
		strlwr(input); // uppercase to lowercase conversion of the input letters/word

		printf("-----------------------\n");

		clock_t beginTime_Autocom = clock();//begin counting time for auto complete
		autocomplete (&node, input); //auto complete
		clock_t endTime_Autocom = clock();//end counting time for auto complete

		printf("-----------------------\n");

		double spentTime_Autocom = (double)(endTime_Autocom-beginTime_Autocom)/CLOCKS_PER_SEC;
		printf(">>>>>>>>>>Time for autocompletion: %f s\n",spentTime_Autocom);
		// printf("%d\n",nodeCount );
		printf("sizeof a node : %ld Bytes\n",sizeof(&node)) ;
		printf("Nodes : %d\n",nodeCount );
		printf("Memory Taken: %d Bytes\n",sizeof((node))*nodeCount);

	}

	return 0;
}
