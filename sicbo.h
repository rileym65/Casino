#ifndef _SICBO_H
#define _SICBO_H

class Sicbo {
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
    Sicbo(Player* p);
    ~Sicbo();
    void play();
  };

#endif

