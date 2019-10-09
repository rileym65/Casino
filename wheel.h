#ifndef _WHEEL_H
#define _WHEEL_H

class MoneyWheel {
  protected:
    long betAmount;
    Player* player;
    int wheelPos;
    void showBets();
    void drawBoard();
    void clearBoard();
    int spinWheel();
    float placeBet();
    void  showBetAmount();
    void  showPlayer();
  public:
    MoneyWheel(Player* p);
    void play();
};

#endif
