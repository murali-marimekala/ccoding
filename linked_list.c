#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//#define COUNT_N_IN_LIST 0

struct node {
	int data;
	struct node *next;
};

void ChangeToNull(struct node** headRef) {
	*headRef=NULL;
}

void ChangeCaller() {
	struct node* head1;
	struct node* head2;

	ChangeToNull(&head1);
	ChangeToNull(&head2);
}

void PrintyList(struct node* head)
{
	printf("\nEntered %s@%d\n",__FUNCTION__,__LINE__);
	printf("List contians\n");
	while(head != NULL) {
		printf("%d\t",head->data);
		head=head->next;
	}
	printf("\n");
	printf("\nExiting %s@%d\n",__FUNCTION__,__LINE__);
}


struct node* BuildOneTwoThree() {
	struct node* head = NULL;
	struct node* second = NULL;
	struct node* third = NULL;

	head=(struct node*)malloc(sizeof(struct node));
	second=(struct node*)malloc(sizeof(struct node));
	third=(struct node*)malloc(sizeof(struct node));

	head->data = 1;
	head->next = second;

	second->data = 2;
	second->next = third;
	
	third->data = 3;
	third->next = NULL;
	return head;
}

struct node* CopyListRecursive(struct node *head) {
	struct node* current = head;
	if(head == NULL) {
		return NULL;
	}
	else {
		struct node* newList = (struct node*)malloc(sizeof(struct node));
		newList->data = current->data;
		newList->next = CopyListRecursive(current->next);
		return (newList);
	}
}

int Length(struct node* head) {
	struct node* current = head;
	int count = 0;

	while(current != NULL) {
		count++;
		current = current->next;
	}
	return count;
}

void LinkTest() {
	struct node* head = BuildOneTwoThree();
	struct node* newNode;

	newNode = (struct node*)malloc(sizeof(struct node));
	newNode->data=1;
	
	newNode->next = head;
	head = newNode;
}

void WrongPush(struct node* head, int data) {
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	
	newNode->data = data;
	newNode->next = head;
	head = newNode;
}

void WrongPushTest() {
	struct node* head = BuildOneTwoThree();
	WrongPush(head,1);
}

void LengthTest() {
	struct node* myList = BuildOneTwoThree();
	int len = Length(myList);
	printf("Value of len is %d\n",len);
}

void Push(struct node** headRef,int data) {
	printf("\nEntered %s@%d\n",__FUNCTION__,__LINE__);
	struct node *newNode = (struct node*)malloc(sizeof(struct node));
	newNode->data = data;
	newNode->next = *headRef;
	*headRef = newNode;
	printf("\nExiting %s@%d\n",__FUNCTION__,__LINE__);
}

void PushTest() {
	struct node* head = BuildOneTwoThree();
	Push(&head, 1);
	Push(&head, 13);
}

struct node* AddAtHead() {
	struct node* head = NULL;
	int i;
	
	for(i=1; i<6; i++) {
		Push(&head,i);
	}
	return head;
}

struct node* BuildWithSpecialCase() {//+Tail pointer
	struct node* head = NULL;
	struct node* tail; //Tail pointer to add all the other node
	int i;

	Push(&head,1);
	tail = head;

	for(i=2; i<6; i++) {
		Push(&(tail->next),i);
		tail = tail->next;
	}
	printf("Linked list contains...\n");
   while(head != NULL) {
		printf("%d\n",head->data);
		head=head->next;
	}
	return head;
}

struct node* BuildWithDummyNode() {
	struct node dummy; //Dummy node is temporarily the first node
	struct node* tail=&dummy; //Start the tail at the dummy.
										// Build the list of dummy.next (aka tail->next)
   struct node* head=tail;
	int i;
	dummy.next=NULL;

	for(i=1;i<6;i++) {
		Push(&(tail->next),i);
		tail = tail->next;
	}
   PrintyList(head);
	
	return(dummy.next);
}


struct node* BuildWithLocalRef() {
	int i=0;
	struct node* head = NULL;
	struct node** lastPtrRef=&head; //Start out pointing to the head pointer

	for(i=0;i<6;i++) {
		Push(lastPtrRef, i); //Add node at the last pointer in the list
		lastPtrRef= &((*lastPtrRef)->next);//Advance to point to the new last pointer
	}

   return (head);
}

struct node* AppendNode(struct node **headRef, int num) {
	struct node* current = *headRef;
	struct node* newNode;

	newNode=(struct node*)malloc(sizeof(struct node));
	newNode->data=num;
	newNode->next=NULL;

	if( current == NULL) {
		*headRef = newNode;
	}
	else	{
		//Locate the last node
		while(current->next != NULL) {
			current = current->next;
		}
	}
	current->next = newNode;
}

struct node* AppendNodeWithPush(struct node** headRef, int num) {
	struct node* current = *headRef;
	
	if( current == NULL) {
		Push(headRef,num);
	}
	else {
		while(current->next != NULL) {
			current = current->next;
		}
		Push(&(current->next),num);
	}
}

struct node* CopyList(struct node *headRef) {
	struct node *current = headRef;
	struct node *newList = NULL;
	struct node *tail = NULL;

	while(current != NULL) {
		if(newList == NULL) {  //Special case for first new node
			newList=(struct node*)malloc(sizeof(struct node));
			newList->data = current->data;
			newList->next = NULL;
			tail = newList;
		}
		else {
			tail->next=(struct node*)malloc(sizeof(struct node));
			tail = tail->next;
			tail->data = current->data;
			printf("Value copied is %d\n",tail->data);
			tail->next = NULL;
		}
		current = current->next;
	}
	return newList;
}

struct node* CopyListWithPush(struct node *head) {
	struct node *current = head; //used to iterate over the original list
	struct node *newList = NULL; //head of new list
	struct node *tail = NULL; //kept pointing to the last node in the new list
	
	while(current != NULL) {  
		if(newList == NULL) {
			Push(&newList,current->data);
			tail=	newList;
		}
		else {
			Push(&(tail->next), current->data);
			tail = tail->next;
		}
		current = current-> next;
	}
	return(newList);
}

struct node* CopyListWithRefPtr(struct node *head) {
	struct node* current = head;
	struct node* newList = NULL;
	struct node** listPtr;

	listPtr = &newList; //Start off pointing to the head itself

	while (current != NULL) {
		Push(listPtr, current->data);
		listPtr = &((*listPtr)->next); //Advance last pointer
		current = current->next;
	}
	return(newList);
} 

int Count(struct node *head, int num) {
	int count = 0;
	struct node* current = head;
#ifdef ALTERNATIVE
	while(current != NULL) {
		if(current->data == num) {
			count++;
		}
		current=current->next;
	}
#else
	for(current = head; current != NULL; current = current->next) {
		if(current->data == num) count++;
	}
#endif
	return count;
}

void CountTest() {
	struct node* head;
   head=BuildOneTwoThree();
	Push(&head,2);
	PrintyList(head);
	printf("2 is found %d times\n",Count(head,2));	
}

int GetNth(struct node *head,int index) {
	int i;
	for(i=0;i<index;i++) {
		head=head->next;
	}
	return head->data;
}

void GetNthTest() {
	struct node* head = BuildOneTwoThree();
	int NthNode=GetNth(head,2);
	printf("Value of the node at index 2 is %d\n",NthNode);
}

void DeleteList(struct node **headRef) {
	struct node* current=*headRef; //deref headRef to get the real head
	struct node* next;
	while(current != NULL) {
		next = current->next; //note the next pointer
		free(current); //delete the node
		current = next; //advance to the next node
	}
	*headRef = NULL; //Again dereference headRef to affect the real head back in the caller
}

void DeleteListTest() {
	struct node* head = BuildOneTwoThree();
	DeleteList(&head);
}

int Pop(struct node **headRef) {
    //Allocate , Link next , Link head 
    struct node* current = *headRef; //Dereference to get the current node
    int return_data = current->data;
    *headRef=current->next; //Advance one level up
    free(current);
    return return_data;
}

void PopTest() {
    struct node* head = BuildOneTwoThree();
    int a=Pop(&head);
    int b=Pop(&head);
    int c=Pop(&head);
    int len=Length(head);
    printf("Value of a=%d,b=%d,c=%d and len=%d\n",a,b,c,len);
}

void InsertNth(struct node **headRef,int index, int data) {
	int i=0;
	struct node* current=*headRef;

	if(index == 0) {
		Push(headRef,data);
	} else {
		for(i=0;i<index-1;i++) {
			if(current != NULL) {
				current=current->next;
			} else {
				printf("Current node is null\n");
			}
		}

		//Check one last time
		assert(current != NULL);
	   Push(&current->next,data);		// Pointer being pushed on is not in stack. 
													//So it works. Push works for any node pointer
	}
}

void InsertNthTest() {
    struct node *head=(struct node*)malloc(sizeof(struct node));
    InsertNth(&head,0,13);
    InsertNth(&head,1,42);
    InsertNth(&head,1,5);
    InsertNth(&head,2,20);
    PrintyList(head);
}

void SortedInsert(struct node** headRef, struct node* newNode) {
	struct node* current = *headRef;

	printf("\nEntered %s@%d\n",__FUNCTION__,__LINE__);
		
	//Special case of head end
	if( *headRef == NULL || (*headRef)->data >= newNode->data) {
		newNode->next = *headRef;
		*headRef = newNode;
	} else {
		//Traverse to the node where the current node is less than or equal to new Node
	   while((current->next != NULL)&&(current->next->data <= newNode->data)) {
		    current=current->next;
	   }
      // we found the relevant node where we need to place new node next to it
	   newNode->next = current->next;  //Make new node next to point to current node
	   current->next = newNode;
	   printf("\nExiting %s@%d\n",__FUNCTION__,__LINE__);
	}
}

void SortedInsertTest() {
	printf("\nEntered %s@%d\n",__FUNCTION__,__LINE__);
	struct node *head = BuildOneTwoThree();
	PrintyList(head);
	struct node *newNode = (struct node*)malloc(sizeof(struct node));
	newNode->data=12;
	SortedInsert(&head,newNode);
	PrintyList(head);
	printf("\nExiting %s@%d\n",__FUNCTION__,__LINE__);
}

void SortedInsert2(struct node** headRef, struct node* newNode) {
	struct node dummy;
	struct node* current=&dummy;
	dummy.next = *headRef;

	printf("\nEntered %s@%d\n",__FUNCTION__,__LINE__);
		
   //Traverse to the node where the current node is less than or equal to new Node
	while((current->next != NULL)&&(current->next->data <= newNode->data)) {
  		current=current->next;
	}
	// we found the relevant node where we need to place new node next to it
	newNode->next = current->next;  //Make new node next to point to current node
	current->next = newNode;
	printf("\nExiting %s@%d\n",__FUNCTION__,__LINE__);
	
	*headRef=dummy.next; //Set null to the end pointer
}

void SortedInsertTest2() {
	printf("\nEntered %s@%d\n",__FUNCTION__,__LINE__);
	struct node *head = NULL;//BuildOneTwoThree();
	PrintyList(head);
	struct node *newNode = (struct node*)malloc(sizeof(struct node));
	newNode->data=13;
	SortedInsert2(&head,newNode);
	PrintyList(head);
	printf("\nExiting %s@%d\n",__FUNCTION__,__LINE__);
}

int main() {
#ifdef ID105_Basics
	struct node *head=NULL;
	struct node *copyhead=NULL;
	head = (struct node*)malloc(sizeof(struct node));
	copyhead = (struct node*)malloc(sizeof(struct node));
	AppendNodeWithPush(&head,30);
	PrintyList(head);
	copyhead = CopyListWithPush(head);
	printf("Copy list is ...\n");	
	PrintyList(head);
	
	head = AppendNode(&head,20);
	PrintyList(head);
	head = BuildWithLocalRef();
	PrintyList(head);
	copyhead = CopyList(head);
	PrintyList(copyhead);
	printf("Copy List with Ref Ptr list is ....\n");
	copyhead = CopyListWithRefPtr(head);
	PrintyList(copyhead);

	printf("Copy using Recursive copy\n");
	copyhead=NULL;
	copyhead=CopyListRecursive(head);
	PrintyList(copyhead);
	
	head = BuildWithDummyNode();
	PrintyList(head);
	BuildWithSpecialCase();
	LengthTest();
	PushTest();
	WrongPushTest();
#endif
   // InsertNthTest();
    //PopTest();
 	//CountTest();
	//GetNthTest();
	//DeleteListTest();
	//SortedInsertTest();
	SortedInsertTest2();
	return 0;
}
