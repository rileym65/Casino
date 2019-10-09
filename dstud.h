#ifndef _DSTUD_H
#define _DSTUD_H

class DStud:public Poker {
  protected:
    long  betAmount;
    int   playerX(int P);
    int   playerY(int P);
    int   playerBetX(int P);
    int   playerBetY(int P);
    void showPlayers();
    float placeBet(int player);
    void  showBetAmount();
    void  round();
  public:
    DStud(int decks,int jokers,float minbet);
    void play();
};

#endif

