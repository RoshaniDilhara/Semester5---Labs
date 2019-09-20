#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int numofnodes=0;

#define MAX 80
#define ALPHABET_SIZE 26

typedef struct tnode *Tptr;
typedef struct linked_str *Lptr;

typedef struct tnode{
    Tptr children[26];
    Lptr linked_str;
		unsigned int isLeaf: 1; // 1 -> when node is a leaf node
}tnode;

//for going through a given list
typedef struct linked_str{
	char letter;
	Lptr next;
}linked_str;

//creating a new node
Tptr createNode(){
	  int i;
		numofnodes = numofnodes+1; //count the number of nodes
    Tptr temp_node = (Tptr)malloc(sizeof(tnode)); //allocate space for new node
    temp_node->linked_str = NULL;
    temp_node->isLeaf = 0;
    for (i=0;i<ALPHABET_SIZE;i++){
    	temp_node->children[i] = NULL;
    }
    return temp_node;
}


Tptr linked_strBreak(Tptr pre_Node,Tptr node,Lptr brk_Point){
    Tptr temp_node = createNode();
    Lptr newString = brk_Point->next;
    brk_Point->next = NULL;

    temp_node->linked_str = node->linked_str;
    node->linked_str = newString;
    temp_node->children[(newString->letter) - 97] = node;

    pre_Node->children[(temp_node->linked_str->letter) - 97] = temp_node;

    return temp_node;
}


//join the letters
Lptr linked_strAppend(char* str,int start,int end){
    int i;

		Lptr current = (Lptr) malloc(sizeof(linked_str)); //allocate space for a letters in a given list
		current -> letter = str[start];
		current -> next = NULL;
    Lptr newString = NULL;
    Lptr current2 = current;

    for(i=start+1;i<end;i++){
				Lptr newString = (Lptr) malloc(sizeof(linked_str));
				newString -> letter = str[i];
				newString -> next = NULL;
        current->next = newString;
        current = current->next;
    }
    current = NULL;
    return current2;
}


//insert a new word to a node
void insertNode(Tptr head,char* word){
    int indexOf_LastLetter = strlen(word)-1;
    int i=0;

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

    Tptr curr_n = head; //initializing current node as head
		Tptr pre_Node = NULL; //initializing the nodes to NULL
    Tptr temp_node = NULL;
    Lptr currentLetter = NULL;
    Lptr previousLetter = NULL;
    currentLetter = curr_n->linked_str;

    while(i<indexOf_LastLetter){
    	 	if(currentLetter == NULL){
		    		if(!(curr_n->children[word[i] - 97])){
		    			temp_node = createNode();
		    			temp_node->linked_str = linked_strAppend(word,i,indexOf_LastLetter);
		                temp_node->isLeaf = 1; //end of the word
		    			curr_n->children[word[i] - 97] = temp_node;
		    			break;
		    		}
		    		else{
		                pre_Node = curr_n;
		                curr_n = curr_n->children[word[i] - 97];
		                previousLetter = curr_n->linked_str;
		    						currentLetter = curr_n->linked_str->next;
		    		}
    	}
        else{
    		if (currentLetter->letter != word[i]){
    			curr_n = linked_strBreak(pre_Node,curr_n,previousLetter);
    			temp_node = createNode();
    			temp_node->linked_str = linked_strAppend(word,i,indexOf_LastLetter);
                temp_node->isLeaf = 1; //end of the word
    			curr_n->children[word[i] - 97] = temp_node;
    			break;
    		}
            else{
                previousLetter = currentLetter;
    						currentLetter = currentLetter->next;
    		}
    	}
    	i++;
    }
}

//search through nodes
Tptr searchNodes(Tptr head,char* word){
    int index_last = strlen(word);
    int i=0;

    Tptr curr_n = head;
    Lptr currentLetter = curr_n->linked_str;

    while(i<index_last){

    	if((currentLetter) == NULL){
            curr_n = curr_n->children[word[i] - 97];
    		currentLetter = curr_n->linked_str->next;
    	}
        else{
    		currentLetter = currentLetter->next;
    	}
        i++;
    }

    while(currentLetter != NULL){
    	word[index_last] = currentLetter->letter;
    	currentLetter = currentLetter->next;
    	index_last++;
    }
    word[index_last] = '\0';
    return curr_n;
}

//recursive function to print auto suggested words for a given node
void printSuggetions(Tptr suggestedNode,char buffer[],int bufferSize){
    Tptr curr_n = suggestedNode;
    int i,j,newSize1,newSize2;

    if(curr_n->isLeaf){
            printf("%s\n",buffer);
    }

    for (i=0;i<ALPHABET_SIZE;i++){
        if((curr_n->children[i])!=NULL){

						    newSize1 = bufferSize;
						    linked_str* currentLetter = curr_n->children[i]->linked_str;

						    while (currentLetter != NULL){
						        buffer[newSize1] = currentLetter->letter;
						        newSize1++;
						        currentLetter = currentLetter->next;
						    }
						    buffer[newSize1] = '\0';
						    newSize2 =  newSize1-1;

            printSuggetions(curr_n->children[i],buffer,newSize2 + 1);
        }
    }
}

// test above functions
int main(int argc, char **argv){

  Tptr head = NULL;//creating an empty node
  char text[MAX];
	FILE *fp;

	// Check if a filename has been specified in the command
	if (argc < 2){
				printf("Missing Filename\n");
				return(1);
	 }else{
  			fp = fopen(argv[1], "r"); // Open file in read-only mode
	 }
  if (fp == NULL){// Check whether an available file has been specified in the command
      fprintf(stderr, "Error while opening the file\n");
      exit(0);
  }

  head = createNode();
  // int i=1;
      clock_t beginTime_Insert = clock(); //begin the time for insertion
      while(1)
      {
          fgets(text,MAX,fp);
					strlwr(text); // uppercase to lowercase conversion in the wordlist
          insertNode(head,text);//insert all the words in to the tree
          // printf("%s %d\n",text,i++);
          if(feof(fp))
              break;
      }
      clock_t endTime_Insert = clock(); //end counting time for inserting
      double spentTime_Insert = (double)(endTime_Insert-beginTime_Insert)/CLOCKS_PER_SEC;
      printf(">>>>>>>>>>Insertion Time: %f s\n",spentTime_Insert);
      fclose(fp);

    while(1){

				printf("\n");

        printf("Enter a keyword to search: ");
        scanf("%s",&text); //scan the letter/word(prefix) from the command line
        strlwr(text); // uppercase to lowercase conversion in the wordlist

				printf("************************\n");

        clock_t beginTime_Autocom = clock(); //begin counting time for auto complete
        Tptr suggestedNode = searchNodes(head,text);
        printSuggetions(suggestedNode,text,strlen(text)); //print the autocompleted words according to the prefix
        clock_t endTime_Autocom = clock();//end counting time for auto complete
				printf("************************\n");

        double spentTime_Autocom = (double)(endTime_Autocom-beginTime_Autocom)/CLOCKS_PER_SEC;

        printf(">>>>>>>>>>Time for autocompletion: %f s\n",spentTime_Autocom);

				printf("sizeof a node : %ld Bytes\n",sizeof(head)) ;
				printf("Nodes : %d\n",numofnodes );
        printf("Memory: %d Bytes\n",sizeof(*(head))*numofnodes);

    }
    return 0;
}
