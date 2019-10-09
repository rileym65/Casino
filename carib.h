#ifndef _CARIB_H
#define _CARIB_H

class Carib:public Poker {
  protected:
    long  betAmount;
    int   playerX(int p);
    int   playerY(int p);
    int   playerBetX(int p);
    int   playerBetY(int p);
    void  round();
    void showPlayers();
    float placeBet(int player);
    void  showBetAmount();
    void  showJackpot();
  public:
    Carib(int decks,int jokers,float minbet);
    void play();
};

#endif

