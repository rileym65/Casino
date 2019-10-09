#ifndef _PKRMACH_H
#define _PKRMACH_H

class PkrMach:public Poker {
  protected:
    unsigned long payoutv[20];
    unsigned long payouth[20];
    unsigned long payoutHand[20];
    long          payouta[20];
    char          payouts[20][40];
    float         payoutAmount[20];
    int           numPayouts;
    float         findPayout(unsigned long hand,int coinsPlayed);
    int           wildCard;
    float         progressive;
    void          showPlayer();
    void          drawPayouts();
  public:
    PkrMach(int decks,int jokers,float minbet);
//    void addPayout(unsigned long hand,float amount);
    void addPayout(const char* text,unsigned long value,unsigned long hi,long am);
    void putWildCard(int c);
    void putProgressive(float p);
    float getProgressive();
    void play();
};

#endif

