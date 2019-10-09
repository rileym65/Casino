#ifndef _BOSTON5_H
#define _BOSTON5_H

class Boston5:public Poker {
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
    void  clearBets(int p);
  public:
    Boston5(int decks,int jokers,float minbet);
    ~Boston5();
    void play();
};

#endif

