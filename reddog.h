#ifndef _REDDOG_H
#define _REDDOG_H

class Reddog:public CardGames {
  protected:
    long betAmount;
    void round();
    int playerX(int p);
    int playerY(int p);
    int playerBetX(int p);
    int playerBetY(int p);
    void showPlayers();
    float placeBet(int player);
    void  showBetAmount();
  public:
    Reddog(int decks,int jokers,float minbet);
    void play();
};

#endif

