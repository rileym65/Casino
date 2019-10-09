#ifndef _PAIGOW_H
#define _PAIGOW_H

class Paigow:public Poker {
  protected:
    long betAmount;
    int playerX(int p);
    int playerY(int p);
    int playerBetX(int p);
    int playerBetY(int p);
    void round();
    float placeBet(int player);
    void  showBetAmount();
    void showPlayers();
    void splitHand(int *sp1,int *sp2,int p);
  public:
    Paigow(int decks,int jokers,float minbet);
    void play();
};

#endif

