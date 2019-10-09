#ifndef _PAIGOWT_H
#define _PAIGOWT_H

class PaigowTiles:public CardGames {
  protected:
    PaigowDeck* tiles;
    PaigowHand* dHand;
    PaigowHand* dSHand;
    PaigowHand* pHand[5];
    PaigowHand* sHand[5];
    long betAmount;
    int playerX(int p);
    int playerY(int p);
    int playerBetX(int p);
    int playerBetY(int p);
    void round();
    float placeBet(int player);
    void  showBetAmount();
    void showPlayers();
    void splitHand(int p);
    void swapHands(int p);
  public:
    PaigowTiles(int decks,int jokers,float minbet);
    ~PaigowTiles();
    void play();
};

#endif

