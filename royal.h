#ifndef _ROYAL_H
#define _ROYAL_H

class Royal:public CardGames {
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
    Royal(int decks,int jokers,float minbet);
    void play();
};

#endif

