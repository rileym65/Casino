#include "cardgame.h"

class Poker:public CardGames {
  protected:
    long pot;
    int  playersIn;
    int  dealer;
    int  folded[7];
    int  raisesLeft;
    long amountBet[7];
    long betLo;
    long betHi;
    long betReq;
    int  playerX(int p);
    int  playerY(int p);
    void addToPot(long bet);
    void bettingRound(int round);
    void showPlayers();
    virtual long roundBet(int p,int round);
  public:
    Poker(int decks,int jokers,float minbet);
    virtual ~Poker();
    void play();
};
