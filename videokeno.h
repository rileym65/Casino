#ifndef _KENO_H
#define _KENO_H

class VideoKeno {
  protected:
    Player* player;
    int  drawn;
    int  min;
    int  max;
    int  maxBet;
    int  spots;
    int  spotsA;
    int  spotsB;
    int  spotsC;
    int  bet;
    int  balls[80];
    int  grA;
    int  grB;
    int  grC;
    int  freeGames;
    int  freeMult;
    double credits;
    long creditsWon;
    long mult;
    double creditSize;
    double sessionVip;
    int  hits;
    int  hitsA;
    int  hitsB;
    int  hitsC;
    int  game;
    char playerSpots[80];
    char picked[80];
    long payouts[41][21];
    void clearPayouts();
    void setupStandard();
    void setupCaveman();
    void setupTopBottom();
    void setupVideo();
    void setupSuper();
    void setupSuperWay();
    void setup246();
    void setup369();
    void setupDiamond();
    void markSpot(int num);
    void drawBoard();
    void drawPayouts();
    void drawButtons();
    void showChoices();
    int  doInput();
    void drawStats();
    void round();
    void shuffle();
    void spotClicked(int n);
    void menu();
    void payTable();
    void _menu();
    void stats();
  public:
    VideoKeno(Player* p);
    ~VideoKeno();
    void play();
    void setGame(int g);
    void setDenomination(double d);
    void insertMoney(int m);
    void cashOut();
    double getMoney();
    long   getVip();
  };

#endif

