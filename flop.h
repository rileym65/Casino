#ifndef _FLOP_H
#define _FLOP_H

class Flop:public Poker {
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
    Flop(int decks,int jokers,float minbet);
    void play();
};

#endif

