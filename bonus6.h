#ifndef _BONUS6_H
#define _BONUS6_H

class Bonus6:public Poker {
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
    void  clearBets(int p);
  public:
    Bonus6(int decks,int jokers,float minbet);
    void play();
};

#endif

