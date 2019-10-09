#ifndef _TEXAS_H
#define _TEXAS_H

class Texas:public Poker {
  protected:
    void  round();
    void  showHand(Hand *h,int hidden);
    virtual long roundBet(int p,int round);
  public:
    Texas(int decks,int jokers,float minbet,long lo,long hi);
    void play();
};

#endif

