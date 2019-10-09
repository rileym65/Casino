#ifndef _WAVE_H
#define _WAVE_H

class Wave:public CardGames {
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
    char  computerStrategy(int pc,int dc,int numCards);
  public:
    Wave(int decks,int jokers,float minbet);
    void play();
};

#endif

