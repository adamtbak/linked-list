/*   
 * Implementation of a singly-linked list in C. The data that is linked is that
 * of an integer.
 */

#include <stdio.h>
#include <stdlib.h>

struct ListNode {
	int data;
	struct ListNode *next;		
};

// nodePtr should point to the head of the list
// if nodePtr points to any other member in the list
// other than the first member, we can get an 
// incorrect number of elements returned in this method
int numberOfMembersinList(struct ListNode *nodePtr)
{
	int numberOfMembers = 0;
	while(nodePtr != NULL)
	{
		numberOfMembers++;
		nodePtr = nodePtr->next;
	}
	return numberOfMembers;
}

// nodePtr should point to the head of the list
// if nodePtr is NULL this means the list is empty and we need to create
// the head of the linked list. We need the address of the pointer to
// the head so that we can change where it points to.
void insertMemberToEndOfList(int dataMember, struct ListNode **nodePtr)
{
	struct ListNode *memberToAdd = malloc(sizeof(struct ListNode));
	memberToAdd->data = dataMember;
	memberToAdd->next = NULL;
	 
	// the list is empty and we need to create the head
	if(*nodePtr == NULL)
		*nodePtr = memberToAdd;
	else
	{
		//Traverse the list until you find the last element 
		//then add this element to the last member
		struct ListNode *currentNode = *nodePtr;
		while((*currentNode).next != NULL)
		{
			currentNode = (*currentNode).next;
		};
		
		(*currentNode).next = memberToAdd;	
	}
}

// headPtr should point to the head of the list
void insertMemberToBeggingOfList(int dataMember, struct ListNode **headPtr)
{
	struct ListNode *memberToInsert = malloc(sizeof(struct ListNode));
	memberToInsert->data = dataMember;
	memberToInsert->next = *headPtr;
	
	*headPtr = memberToInsert;
}

void insertAfterSelectedMember(int dataMember, int selectedMember, struct ListNode **headPtr)
{
	struct ListNode *memberToInsert = malloc(sizeof(struct ListNode));
	memberToInsert->data = dataMember;
	
	//Traverse the list until you find the last element 
	//then add this element to the last member
	struct ListNode *currentNode = *headPtr;
	while((*currentNode).data != selectedMember)
	{
		currentNode = (*currentNode).next;
	};
	
	memberToInsert->next = (*currentNode).next;
	(*currentNode).next = memberToInsert;
}

void deleteFirstElement(struct ListNode **headPtr)
{
	struct ListNode *elementToDelete = *headPtr;
	
	if(elementToDelete->next == NULL)
	{
		free(elementToDelete);
		*headPtr = NULL;
		return;
	}
	
	if(elementToDelete->next != NULL)
	{
		// Free the first element last
		*headPtr = (*headPtr)->next;
		free(elementToDelete);
		return;
	}
}

void deleteLastElement(struct ListNode **headPtr)
{	
	struct ListNode *currentElement = *headPtr;
	
	if(currentElement->next == NULL)
	{
		free(currentElement);
		*headPtr = NULL;
		return;
	}
	
	if(currentElement->next != NULL)
	{
		//we look two elements forward because we
		//want to find the second to the last element
		//the second to the last element will become 
		//the new last elment (the tail) after we
		//delete the last element
		while((currentElement->next)->next != NULL)
		{
			currentElement = currentElement->next;
		};	
		
		free(currentElement->next);
		currentElement->next = NULL;	
		return;	
	}
}

void deleteSelectedMember(int memberToDelete, struct ListNode **headPtr)
{
	int index = -1;
	int foundIndex = -1;
	
	// Loop through all the elements of the linked-list to see if
	// the member that we are trying to delete is present and get
	// its "index"
	struct ListNode *currentElement = *headPtr;
	while(currentElement != NULL)
	{
		index++;
					
		if(currentElement->data == memberToDelete)
		{			
			foundIndex = index;
			printf("foundIndex: %d\n", foundIndex);
			break;
		}				
		
		currentElement = currentElement->next;		
	}
	
	if(foundIndex == -1)
	{
		printf("Selected member is not present, nothing deleted");
		return;
	}
		
	if(foundIndex == 0)
	{
		printf("We are inside - foundIndex==0");
		deleteFirstElement(headPtr);
		return;
	}
	
	if(foundIndex > 0)
	{
		struct ListNode *previousElement = *headPtr;
		
		// foundIndex - 1 is index of previous element
		for(int i = 0; i < foundIndex - 1; i++)
		{
			previousElement = previousElement->next;
		}
		
		struct ListNode *elementToDelete = previousElement->next;
		previousElement->next = elementToDelete->next;
		free(elementToDelete);
		
		return;	
	}
}

// listHead should point to the head of the list
void printList(struct ListNode *listHead) 
{
	struct ListNode *currentNode = listHead;
	
	if(currentNode == NULL)
	{
		printf("List is empty");
		return;
	}
	
	while(currentNode != NULL)
	{
		printf("%d ", currentNode->data);
		currentNode = currentNode->next;
	};
}

int main(int argc, char *argv[])
{
	// Create list and add 4 members to list
	printf("Create list and add 4 members to the list.\n");
	struct ListNode *myList = NULL;
	insertMemberToEndOfList(10, &myList);
	insertMemberToEndOfList(15, &myList);
	insertMemberToEndOfList(20, &myList);
	insertMemberToEndOfList(25, &myList);

	// Prink the list
	printList(myList);
	printf("\n");
	
	// Add a member to the beginning of the list
	printf("\nAdd member to beginning of the list\n");
	insertMemberToBeggingOfList(5, &myList);
	printList(myList);
	printf("\n");
	
	// Insert integer 21 after integer 20 in the linked list
	printf("\nInsert 21 after 20\n");
	insertAfterSelectedMember(21, 20, &myList);
	printList(myList);
	printf("\n");
	
	// Delete the first member of the list
	printf("\nDelete first member of the list\n");
	deleteFirstElement(&myList);
	printList(myList);
	printf("\n");
	
	// Delete last member of the list
	printf("\nDelete last member of the list\n");
	deleteLastElement(&myList);
	printList(myList);
	printf("\n");
	
	// Print the total amount of elements in the list
	printf("\nCurrent number of elements in list: %d\n", numberOfMembersinList(myList));
	
	return 0;
}
