
class Keno {
  protected:
    long   betAmount;
    Player *player;
    int    count;
    int    balls[80];
    int    playerNumbers[81];
    int    gameNumbers[81];
    float  checkNumbers();
    void   drawBoard();
    void   pickNumbers();
    void showPlayer();
    float placeBet();
    void  showBetAmount();
    void  selectNumbers();
    void  showPayouts();
    void  shuffle();
  public:
    Keno(Player* p);
    void play();
};
