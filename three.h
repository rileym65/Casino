#ifndef _THREE_H
#define _THREE_H

class Three:public Poker {
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
    Three(int decks,int jokers,float minbet);
    void play();
};

#endif
