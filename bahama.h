#ifndef _BAHAMA_H
#define _BAHAMA_H

class Bahama:public Poker {
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
    void  showJackpot();
  public:
    Bahama(int decks,int jokers,float minbet);
    void play();
};

#endif

