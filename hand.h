#ifndef _HAND_H
#define _HAND_H

class Hand {
  protected:
    byte straightCount;
    byte straightHigh;
    byte stFlushCount;
    byte stFlushHigh;
    int  wildCount;
    unsigned long computeHandValue(unsigned long value);
    unsigned long computePaigowValue(unsigned long value);
    int  numbers[15];
    int  suits[4];
    byte combinations[10];
  public:
    Hand();
    ~Hand();
    Card** cards;
    int  numCards;
    void sort(int wild);
    int  bjValue();
    int  bjCmp(Hand* h);
    int  baccValue();
    int  baccCmp(Hand* h);
    unsigned long  pokerValue(int maxCards,int wild);
    unsigned long  paigowValue();
    Hand* paigowSplit(int c1,int c2);
    int  pokerCmp(Hand* h);
    int  threePokerValue(int wild);
    int  threePokerCmp(Hand* h);
    void display(int hidden);
};

#endif

