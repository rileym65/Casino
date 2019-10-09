#ifndef _HOLDEM_H
#define _HOLDEM_H

class Holdem:public Poker {
  protected:
    long  betAmount;
    Hand* comHand;
    Hand* tmpHand;
    int   playerX(int p);
    int   playerY(int p);
    int   playerBetX(int p);
    int   playerBetY(int p);
    void  round();
    void showPlayers();
    float placeBet(int player);
    void  showBetAmount();
  public:
    Holdem(int decks,int jokers,float minbet);
    ~Holdem();
    void play();
};

#endif

