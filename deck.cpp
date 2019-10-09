#include <stdlib.h>
#include "librcs.h"

Deck::Deck(int decks,int jokers) {
  numCards=(52+jokers)*decks;
  numDecks=decks;
  numJokers=jokers;
  cards=(Card**)calloc(sizeof(Card*),numCards);
  newDeck();
  }

Deck::~Deck() {
  int i;
  for (i=0;i<numCards;i++) delete(cards[i]);
  free(cards);
  }

void Deck::newDeck() {
  int i,j;
  int  value;
  char suit;
  value=1;
  suit='H';
  rcs_randomize();
  i=0;
  for (j=0;j<numJokers*numDecks;j++) cards[i++]=new Card(0,'J');
  while (i<numCards) {
    cards[i++]=new Card(value++,suit);
    if (value==14) {
      value=1;
      switch (suit) {
        case 'H':suit='D'; break;
        case 'D':suit='C'; break;
        case 'C':suit='S'; break;
        case 'S':suit='H'; break;
        }
      }
    }
  cardPos=numCards-1;
}

int  Deck::cardsLeft() {
  return cardPos+1;
  }

Card* Deck::dealCard()
{
  if (cardPos<0) return NULL;
  return cards[cardPos--];
}

Card* Deck::dealSpanishCard() {
  Card *ret;
  ret=cards[cardPos--];
  while (ret->value()==10) ret=cards[cardPos--];
  return ret;
  }

void Deck::shuffle()
{
  int  i;
/*  int  value;  */
  int  p1,p2;
/*  char suit;  */
  Card* tcard;
  rcs_randomize();
  p1=0;
  for (i=0;i<numCards*5;i++) {
    p2=rcs_random(numCards);
    tcard=cards[p1];
    cards[p1]=cards[p2];
    cards[p2]=tcard;
    p1++;
    if (p1==numCards) p1=0;
    }
  cardPos=numCards-1;
}

void Deck::removeByValue(int v) {
  int i,j;
/*   char flag; */
  i=0;
  while (i<numCards) {
    if (cards[i]->value() == v) {
      for (j=i;j<numCards-1;j++) cards[j]=cards[j+1];
      numCards--;
      } else i++;
    }
  cards=(Card**)realloc(cards,sizeof(Card*)*numCards);
  cardPos=numCards-1;
  }


