#ifndef _CRAPS_H
#define _CRAPS_H

class Craps {
  protected:
    Player *player;
    Die     *die1;
    Die     *die2;
    int     minBet;
    int     point;
    long    betAmount;
    void    drawBoard();
    void    buyBets();
    void    freeBets();
    void    layBets();
    void    propBets();
    int     rollDice();
    void    showBets();
    float placeBet();
    void  showBetAmount();
    void  showPlayer();
  public:
    Craps(Player* p,int minbet);
    ~Craps();
    void play();
};

#endif

