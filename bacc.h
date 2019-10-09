#ifndef _BACC_H
#define _BACC_H

class Bacc:public CardGames {
  protected:
    char  bets[PLAYERS_BACC];
    float comms[PLAYERS_BACC];
    long  betAmount;
    int   playerBetX(int Player);
    int   playerBetY(int Player);
    int   playerBetXD(int Player);
    int   playerBetYD(int Player);
    int   playerX(int Player);
    int   playerY(int Player);
    void  round();
    void  showPlayers();
    float placeBet(int player);
    void  showBetAmount();
  public:
    Bacc(int decks,int jokers,float minbet);
    void play();
};

#endif

