#ifndef _P357_H
#define _P357_H

class P357:public Poker {
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
    P357(int decks,int jokers,float minbet);
    void play();
};

#endif

