#ifndef _CARD7_H
#define _CARD7_H

class Card7:public Poker {
  protected:
    void  round();
    void  showHand(Hand *h);
    virtual long roundBet(int p,int round);
  public:
    Card7(int decks,int jokers,float minbet,long lo,long hi);
    void play();
};

#endif

