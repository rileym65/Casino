#ifndef _WAR_H
#define _WAR_H

class War:public Poker {
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
  public:
    War(int decks,int jokers,float minbet);
    void play();
};

#endif

