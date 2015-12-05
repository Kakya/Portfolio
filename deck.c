#include <stdlib.h>
#include <stdio.h>

#include "deck.h"

card_ptr new_card(int face, suit_type suit) {
   card_ptr t = (card_ptr)malloc(sizeof(card_rec));
   t->face = face;
   t->suit = suit;
   return t;
}
deck_ptr new_deck(card_ptr card)
{
	deck_ptr d = (deck_ptr)malloc(sizeof(deck_rec));
	d -> card = card;
	d->next = NULL;
	return d;
}
int compare_face(card_ptr card1, card_ptr card2) {
   if (card1 == NULL || card2 == NULL) return 0;
   return card1->face == card2->face;
}

int compare_suit(card_ptr card1, card_ptr card2) {
   if (card1 == NULL || card2 == NULL) return 0;
   return card1->suit== card2->suit;
}

void output_deck(deck_ptr deck) {
  if (deck) {
    printf("\nResult: ");
    while (deck) {
       print_card(deck->card);
       deck=deck->next; 
    }
  } else printf("You Won!!");
}


/* Implement the functions below: */

card_ptr get_topcard(deck_ptr deck) {
/* return ptr to card at top of deck */
  return deck->card;
}

card_ptr get_comparecard(deck_ptr deck) {
/* return pointer to fourth card from the top of the deck */
	//Start an iterator to reach the fourth card.
	int iter = 0;
	deck_ptr temp = deck;
	//iterator goes to 3 as we want the fourth card, i.e. the "-> next" of the third card
	while(iter < 3)
	{
		temp = temp -> next;
		iter++;
	}
	//return the card
  return temp->card;
}

deck_ptr add_deck(card_ptr card, deck_ptr deck) {
  /* 'push' the card onto the deck */
	//create an empty deck pointer that will serve as the new deck
  deck_ptr newDeck = (deck_ptr)malloc(sizeof(deck_rec));
  //assign card and next fields and then return the new deck
  newDeck -> card = card;
  newDeck -> next = deck;
  return newDeck;
}



deck_ptr remove_two(deck_ptr deck) {
  /* remove cards 2 and 3 (from the top) and return a pointer to the new deck - be sure to
   fix up the pointers correctly */
	//Put the middle two cards in temp vars
   deck_ptr tDel = deck -> next;
   deck_ptr tDel2 = deck -> next -> next;
   //put the fourth card in a temp var
   deck_ptr temp = tDel2 -> next;
   //connect the top to the fourth card
   //removign the middle two cards from the LL
   deck -> next = temp;
   //free up the memory of the two cards
   free(tDel);
   free(tDel2);
  return deck;
}

deck_ptr remove_four(deck_ptr deck) {
   /* remove the top four cards on the deck and return a pointer to the new deck */
	//Same concept as the comparecard func
   int iter = 0;
   deck_ptr temp = deck;
   //Must be set to Null. Caused me a bug where the compiler would set it to a random address when it wasn't set to null.
   deck_ptr temp2 = NULL;
   //Iter goes up to 4 as we aren't finding the fourth card, but we also need to do remove it.
   while(iter<4)
   {
   	//temp2 holds the next card to be removed
    temp2 = temp->next;
    //free the card as it is no longer needed.
    free(temp);
    //temp will hold the deck after the four cards are removed
    temp = temp2;
    iter++;
   }
  return temp;
}


void delete_deck(deck_ptr deck) {
  /* free all of the space used */
  free(deck)
}


