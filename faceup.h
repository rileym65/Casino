#ifndef _FACEUP_H
#define _FACEUP_H

class Faceup:public CardGames {
  protected:
    char computerPlayer(Hand* dHand,Hand* pHand);
    long betAmount;
    int numSplits;
    int playerX(int p);
    int playerY(int p);
    int playerBetX(int p);
    int playerBetY(int p);
    void round();
    void split(int ip,int cHand);
    float placeBet(int player);
    void  showBetAmount();
    void showPlayers();
    void showHand(Hand *h,int hidden);
  public:
    Faceup(int decks,int jokers,float minbet);
    void play();
};

#endif

