#ifndef _CHUCK_H
#define _CHUCK_H

class Chuck {
  protected:
    long betAmount;
    Player* player;
    Die  *d1,*d2,*d3;
    void showBets();
    void showDice();
    void drawBoard();
    void clearBoard();
    void rollDice();
    float placeBet();
    void  showBetAmount();
    void  showPlayer();
  public:
    Chuck(Player* p);
    ~Chuck();
    void play();
  };

#endif

