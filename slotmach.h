#ifndef _SLOTMACH_H
#define _SLOTMACH_H

class SlotMachine {
  protected:
    Player* player;
    int maxCoins;
    int betSize;
    int numReels;
    int numPayouts;
    int payLines;
    int coinsIn;
    long credits;
    char reels[10][50];
    char stops[10][50];
    char specials[10][50];
    char payouts[50][10];
    unsigned int  pos[10];
    unsigned int  endPos[10];
    long  value[50];
    int  payAmount;
    rcs_Pixmap symbols[255];
    void displaySymbol(char s);
    void displaySymbol(int x,int y,char s);
    void displayPayoutSymbol(int x,int y,char s);
    void displayPayoutSymbol(char s);
    void displayReels();
    long checkWin(char* pl,char* sp);
    void showPlayer();
    void spin();
    void loadSymbol(char s);
  public:
    SlotMachine(int pl,Player* p,int m,int b);
    ~SlotMachine();
    void addReel(const char* r,const char* sp,const  char* st);
    void addPayout(const char* p,int n);
    void play();
};

#endif

