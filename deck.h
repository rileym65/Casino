#ifndef _DECK_H
#define _DECK_H

class Deck {
  protected:
    Card** cards;
    int   numDecks;
    int   numCards;
    int   numJokers;
    int   cardPos;
    void newDeck();
  public:
    Deck(int decks,int jokers);
    ~Deck();
    void shuffle();
    Card* dealCard();
    int  cardsLeft();
  };

#endif

