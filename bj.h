#ifndef _BJ_H
#define _BJ_H

class Bj:public CardGames {
  protected:
    char computerPlayer(Hand* dHand,Hand* pHand);
    long betAmount;
    int  numSplits;
    int  playerX(int p);
    int  playerY(int p);
    int  playerBetX(int p);
    int  playerBetY(int p);
    void round();
    void split(int p,int cHand);
    float placeBet(int player);
    void  showBetAmount();
    void showPlayers();
    void showHand(Hand *h,int hidden);
  public:
    Bj(int decks,int jokers,float minbet);
    void play();
};

#endif

