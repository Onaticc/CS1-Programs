/*Frantzy Jerome
Lab Assignment_4
COP 3502C*/

#include <stdio.h>
#include <stdlib.h>

//structs
typedef struct node {
	char letter;
	struct node* next;
} node;

// function prototypes
int length(node* head);
char* toCString(node* head);
void insertChar(node** pointerHead, char c);
void deleteList(node** pointerHead);

// Returns number of nodes in the linkedList.
int length(node* head){
	int count = 0;
    node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head){
 	int len = length(head);
    char* str = (char*)malloc((len + 1) * sizeof(char)); // memeory allocation 

    if (str == NULL) {
        // Handle memory allocation error
        return NULL;
    }
    node* current = head;
    int i = 0;
    while (current != NULL) {
        str[i] = current->letter;
        i++;
        current = current->next;
    }
    str[len] = '\0';

    return str;
}

// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pointerHead, char c) {
    node* newNode = (node*)malloc(sizeof(node)); // allocate memory
    newNode->letter = c;
    newNode->next = NULL;

    if (*pointerHead == NULL) {
        // If the list is empty, the new node becomes the head
        *pointerHead = newNode;
    } else {
        node* current = *pointerHead;

        // Traverse to the last node
        while (current->next != NULL) {
            current = current->next;
        }

        // Append the new node to the end of the list
        current->next = newNode;
    }
}

// Deletes all nodes in the linkedList.
void deleteList(node** pointerHead) {
    node* current = *pointerHead;
    node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *pointerHead = NULL;  // Set the head pointer to null after deleting all nodes
}

int main(void){
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt","r");
	
	if (inFile == NULL) {
    printf("Failed to open the input file.\n");
    return 1;  // Return an error code to indicate the issue
	}

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile," %c", &c);
			insertChar(&head, c);
		}

		str = toCString(head);
		printf("String is : %s\n", str);

		free(str);
		deleteList(&head);

		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}

	fclose(inFile);

	return 0;
}