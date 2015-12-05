//Hussein Zamzami CS262-003 G00737304
#include <stdio.h>
#include <stdlib.h>
struct Node{
	//ints used to hold all the information.
	//data values, 1, 11, 12, and 13 will print the necessary faces.
	int data;
	//suits are sorted as such: Suit 0: Clubs,  Suit 1: Diamonds, Suit 2: Hearts, and Suit 3: Spades. 
	int suit;
	struct Node *next;
};
//Some function names needed to be changed a little to be used. these are all the functions in both parts of the project.
//Funcs for P1
struct Node *OnewList(void);
struct Node *Odelete(struct Node *prev);
struct Node *Oinsert(struct Node *prev, int data);
int Olength(struct Node *head);
void OprintList(struct Node *head);
//Funcs for p2
struct Node *newList(void);
struct Node *delete(struct Node *prev);
struct Node *insertCard(struct Node *prev, int data, int suit);
struct Node *insert(struct Node *prev, struct Node *new);
int length(struct Node *head);
void printList(struct Node *head);
void fillDeck(struct Node *head);
struct Node *randomShuffle(struct Node *olddeck);

int main()
{
	//Single main function, split by a print statement between the first and second part of the project.
	srandom(7304);
	printf("Part 1 of the Project:\n");
	struct Node *head;
	head = malloc(sizeof(struct Node));
	head = OnewList();
	int i;
	int j;
	i=0;
	//Generate Random nums and add into list, printing out after every insertion
	while(i<10)
	{
		j = random()%(1000 + 0);
		Oinsert(head, j);
		OprintList(head->next);
		printf("Length of list: %d\n", Olength(head));
		i++;
	}
	//Start the second part, the random shuffles.
	printf("Part 2 of the Project:\n");
	//Generate Unshuffled Deck and print it.
	struct Node *newHead;
	newHead = malloc(sizeof(struct Node));
	newHead = newList();
	fillDeck(newHead);
	printList(newHead->next);
	printf("Length is: %d\n", length(newHead));
	struct Node *shuffledDeck;
	shuffledDeck = malloc(sizeof(struct Node));
	//Shuffle the deck and print the shuffled result.
	shuffledDeck=randomShuffle(newHead);
	printList(shuffledDeck->next);
	printf("Length is: %d\n", length(shuffledDeck));
}
struct Node *OnewList(void)
{
	//Generate an empty dummy node.
	struct Node *head;
	head = malloc(sizeof(struct Node));
	head->data = NULL;
	head->next = NULL;
	return head;
}
struct Node *Odelete(struct Node *prev)
{
	//Empty the node after this one, changing the links in the process.
	struct Node *temp;
	temp = malloc(sizeof(struct Node));
	temp = prev -> next;
	prev->next = temp->next;
	temp->next = NULL;
	temp->data = NULL;
	return prev -> next;
}
//All the funcs for P1
struct Node *Oinsert(struct Node *prev, int data)
{
	//Find the correct node through a while loop, starting at the head and add the necessary node.
	struct Node *temp;
	while(prev -> next && data > prev -> next -> data)
		prev = prev -> next;
	temp = malloc(sizeof(struct Node));
	temp->data = data;
	temp->next = prev->next;
	prev->next = temp;
	return prev -> next;
}
int Olength(struct Node *head)
{
	//Loop through a list, incrementing a counter to check the length.
	int length = 0;
	head = head -> next;
	while(head)
	{
		length++;
		head = head -> next;
	}
	return length;
}
void OprintList(struct Node *head)
{
	//Similar to Olength, but instead of incrementing a counter, print the node.
	while(head)
	{
		printf("%d\n", head->data) ;
		head = head -> next;
	}
}
//All the funcs for P2
struct Node *newList(void)
{
	//The same as its P1 equivalent.
	struct Node *head;
	head = malloc(sizeof(struct Node));
	head->data = NULL;
	head->next = NULL;
	head->suit = NULL;
	return head;
}
void fillDeck(struct Node *head)
{
	//Generates a deck that is sorted by suit through the use of nested for-loops.
	int i;
	i = 0;
	int suit;
	for(suit = 0; suit<4; suit++)
	{
		int value;
		for(value = 1; value<=13; value++)
		{
			insertCard(head, value, suit);
			i++;
			head = head->next;
		}
	}
}
struct Node *delete(struct Node *prev)
{
	//Same as its P1 equivalent.
	struct Node *temp;
	temp = malloc(sizeof(struct Node));
	temp = prev -> next;
	prev->next = temp->next;
	temp->next = NULL;
	temp->data = NULL;
	temp->suit = NULL;
	return prev -> next;
}
struct Node *insertCard(struct Node *prev, int data, int suit)
{
	//Adds cards in fillDeck, similar to *insert, but takes int data and int suit as its args.
	struct Node *temp;
	temp = malloc(sizeof(struct Node));
	temp->data = data;
	temp->suit = suit;
	temp->next = prev->next;
	prev->next = temp;
	return prev -> next;
}
struct Node *insert(struct Node *prev, struct Node *new)
{
	//Only change is no looping as we don't need to add them in order, as a random shuffle is desired.
	struct Node *temp;
	temp = malloc(sizeof(struct Node));
	temp -> data = new -> data;
	temp -> suit = new -> suit;
	temp->next = prev->next;
	prev->next = temp;
	return prev -> next;
}
int length(struct Node *head)
{
	//Same as its P1 equivalent.
	int length = 0;
	head = head -> next;
	while(head)
	{
		length++;
		head = head -> next;
	}
	return length;
}
struct Node *randomShuffle(struct Node *olddeck)
{
	//Shuffles the incoming sorted deck.
	struct Node *iterator;
	int deckLength;
	deckLength	= length(olddeck);
	struct Node *newDeck;
	newDeck = malloc(sizeof(struct Node));
	int i;
	int j;
	int ctr;
	for(i=deckLength-1; i>=0; i--)
	{
		ctr=0;
		iterator = olddeck;
		j=random()%(i+1);
		//Uses index generated from the previous line to find the node just before the node referenced. 
		//This makes using the delete function possible to delete the node from the list.
		while(iterator->next && ctr < j-1)
		{
			iterator=iterator->next;
			ctr++;
		}
		//Put the node generated, referenced by iterator->next, into the new deck.
		insert(newDeck, iterator->next);
		//delete from previous deck.
		delete(iterator);
	}
	return newDeck;
}

void printList(struct Node *head)
{
	//Similar to its equivalent, except that it takes into account faces and suit.
	while(head)
	{
		//All values > 1 and < 11 will be numbers printed.
		if(head -> data > 1 && head -> data < 11)
			printf("(%d", head->data);
		else
		{
			//Find the correct face to print.
			if(head->data == 1)
				printf("(A");
			if(head->data == 11)
				printf("(J");
			if(head->data == 12)
				printf("(Q");
			if(head->data == 13)
				printf("(K");
		}
		//Add suit to the printed out list.
		if(head -> suit == 0)
			printf(",C)\n");
		if(head -> suit == 1)
			printf(",D)\n");
		if(head -> suit == 2)
			printf(",H)\n");
		if(head -> suit == 3)
			printf(",S)\n");
		head = head -> next;
	}
}