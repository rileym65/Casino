#ifndef _PLAYER_H
#define _PLAYER_H

class Player {
  protected:
    char name[30];
    char owner;       /* H-human, C-computer */
    Hand **hand;
    Bet* bets[MAX_BETS];
    double cash;
    int  chips1;
    int  chips5;
    int  chips25;
    int  chips100;
    int  chips500;
    int  chips1000;
    int  pennies;
    int  nickles;
    int  dimes;
    int  quarters;
    int  halfdollars;
    int  dollars;
    int  bills1;
    int  bills5;
    int  bills10;
    int  bills20;
    int  bills50;
    int  bills100;
    int  bluffer;
    int  game;
    int   subGame;
    long  vip;
    double nextBet;
    int   strategy;
    double moneyPaidIn[MAX_GAMES];
    double moneyPaidOut[MAX_GAMES];
    char  kenoLast[80];
  public:
    Player(char* name,char owner);
    ~Player();
    void  addChips(int chipSize,int chipNum);
    void  adjustStrategy();
    void  clearAllBets();
    void  clearBet(int bet);
    Hand* getHand(int h);
    double getHandBet(int hand);
    double getBet();
    char* getName();
    void  addPaidIn(double a);
    void  addPaidOut(double a);
    void  setPaidIn(int game,double a);
    void  setPaidOut(int game,double a);
    double paidIn(int game);
    double paidOut(int game);
    double average(int game);
    void  loseHandBets(int hand);
    double money();
    void  newCard(Card* card,int hand);
    void  newHand(int hand);
    double placeBet(double amount,int hand,int x,int y);
    void  moveHandBet(int hand,int newHand,int x,int y);
    char  playerType();
    void  setGame(int game);
    void  setSubGame(int game);
    void  resetStrategy();
    void  showBets();
    void  paintBets();
    void  clearNonWinners();
    void  clearWonBets();
    void  winHandBets(int hand,double mult);
    void  winXYBets(int x1,int y1,int x2,int y2,double mult);
    void  loseXYBets(int x1,int y1,int x2,int y2);
    void  winMoney(double amount);
    void  winOdds(double amount,double bet,double payoff);
    void  putKenoLast(char* l);
    char* getKenoLast();
    int   getBluffer();
    void  save();
    void  load();
    long  getPaidIn();
    long  getPaidOut();
    void  addVip(long v);
    long  getVip();
    void  addMoney(double m);
    void  subMoney(double m);
    double getMoney();
};

#endif

