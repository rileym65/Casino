#ifndef _BINGO_H
#define _BINGO_H

#define TYPE_T         1
#define TYPE_NORMAL    2
#define TYPE_DOUBLE    3
#define TYPE_TRIPLE    4
#define TYPE_HARD      5
#define TYPE_DHARD     6
#define TYPE_COVERALL  7
#define TYPE_X         8

class Bingo {
  protected:
    Player* player;
    int     board[5][5];
    char    marks[5][5];
    char    called[75];
    long    playerBoards[6];
    long    nonPlayerBoards[5000];
    int     nonPlayers;
    int     numbersCalled;
    int     gameNumber;
    int     payoutLevel;
    void    markBoard();
    void    buildBoard(long boardNum);
    int     validate(long boardNum,int typ);
    void    newSheet();
    void    drawBoard(long boardNum,int x,int y);
    void    session();
    void    round(int typ);
    void    drawBingoScreen();
    int     numberOfWinners(int gameType);
    int     playerWinners(int gameType);
    void    figureWinners(int gameType);
    void    showWinner(int gameType);
  public:
    Bingo(Player* p);
    ~Bingo();
    void play();
  };

#endif

