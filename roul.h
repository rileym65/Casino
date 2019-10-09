#ifndef _ROUL_H
#define _ROUL_H

class Roul {
  protected:
    long   betAmount;
    Player *player;
    int    minBet;
    void  drawBoard();
    int   findColumn(int number);
    int   findRow(int number);
    void  findXY(int number,int* x,int* y);
    float insideBets();
    float outsideBets();
    float placeBet();
    void  showBetAmount();
    void  showPlayer();
    void  showBets();
  public:
    Roul(Player* p,int minbet);
    void play();
};

#endif

