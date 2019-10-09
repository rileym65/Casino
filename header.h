#include <stdio.h>
#include <string.h>
#include <librcs.h>

#define MENU_OFFSET_X     70
#define MENU_OFFSET_Y     30
#define MENU_SPACING_X    250
#define MENU_SPACING_Y    30
#define MENU_FONT         "-*-new century schoolbook-*-r-*-*-18-*-*-*-*-*-*-*"
#define PLAYER_FONT       "-*-new century schoolbook-*-r-*-*-14-*-*-*-*-*-*-*"
#define BET_FONT          "-*-new century schoolbook-*-r-*-*-14-*-*-*-*-*-*-*"
#define ACTION_FONT       "-*-new century schoolbook-*-r-*-*-14-*-*-*-*-*-*-*"
#define VIDEO_FONT        "-*-new century schoolbook-*-r-*-*-14-*-*-*-*-*-*-*"
#define KENO_FONT         "-*-new century schoolbook-*-r-*-*-14-*-*-*-*-*-*-*"
#define STAT_FONT         "-*-courier-*-r-*-*-14-*-*-*-*-*-*-*"
#define SLOT_FONT         "-*-courier-*-r-*-*-14-*-*-*-*-*-*-*"
#define SLOT_STAT_FONT    "-*-courier-*-r-*-*-12-*-*-*-*-*-*-*"
#define ROULETTE_FONT     "-*-new century schoolbook-*-r-*-*-18-*-*-*-*-*-*-*"
#define POKER_FONT        "-*-new century schoolbook-*-r-*-*-14-*-*-*-*-*-*-*"
#define BINGO_FONT        "-*-new century schoolbook-*-r-*-*-14-*-*-*-*-*-*-*"
#define VIDEOKENO_FONT    "-*-new century schoolbook-*-r-*-*-24-*-*-*-*-*-*-*"
#define KENO_STAT_FONT    "-*-courier-*-r-*-*-14-*-*-*-*-*-*-*"

#ifndef _BYTE
#define _BYTE
typedef unsigned char byte;
#endif

#ifdef SUPPORT
#define prefix
#else
#define prefix extern
#endif

#define PLAYERS_BACC  5
#define PLAYERS_BJ    5
#define PLAYERS_CARIB 5
#define PLAYERS_HOLDEM 5
#define PLAYERS_LIR   5
#define PLAYERS_DSTUD 5
#define PLAYERS_THREE 5
#define PLAYERS_TEXAS 7
#define PLAYERS_CARD7 7
#define PLAYERS_REDDOG 5
#define PLAYERS_PAIGOW 5
#define PLAYERS_PAIGOWT 5
#define PLAYERS_WAR    5
#define PLAYERS_WAVE   5
#define PLAYERS_WILD   5
#define PLAYERS_BAHAMA 5
#define PLAYERS_ROYAL  5
#define PLAYERS_ARUBA  5
#define PLAYERS_BONUS6 5
#define PLAYERS_BOSTON5 5
#define PLAYERS_FLOP    5
#define PLAYERS_357     5

#define MAX_BETS    100
#define MAX_PLAYERS 20
#define MAX_GAMES   200
#define MAX_PROG    20
#define MAX_HANDS   5

/*
#define PK_NONE      (unsigned long)0l<<28
#define PK_PAIR      (unsigned long)1l<<28
#define PK_2_PAIR    (unsigned long)2l<<28
#define PK_3_PAIR    (unsigned long)3l<<28
#define PK_THREE     (unsigned long)4l<<28
#define PK_STRAIGHT  (unsigned long)5l<<28
#define PK_FLUSH     (unsigned long)6l<<28
#define PK_FULLHOUSE (unsigned long)7l<<28
#define PK_3_THREE   (unsigned long)8l<<28
#define PK_FOUR      (unsigned long)9l<<28
#define PK_STFLUSH   (unsigned long)10l<<28
#define PK_FIVE      (unsigned long)11l<<28
#define PK_ROYALWLD  (unsigned long)12l<<28
#define PK_FOURWLD   (unsigned long)13l<<28
#define PK_ROYAL     (unsigned long)14l<<28
#define PK_FIVEWLD   (unsigned long)15l<<28
*/

#define GAME_BJ      1
#define GAME_BACC    2
#define GAME_VPOKER  3
#define GAME_VPOKER2 4
#define GAME_VPOKER3 5
#define GAME_VPOKER4 6
#define GAME_LIR     7
#define GAME_CRAPS   8
#define GAME_ROUL    9
#define GAME_SLOTS   10
#define GAME_KENO    11
#define GAME_CARIB   12
#define GAME_TEXAS   13
#define GAME_VPOKERP 14
#define GAME_FACEUP  15
#define GAME_REDDOG  16
#define GAME_CHUCK   17
#define GAME_WHEEL   18
#define GAME_DSTUD   19
#define GAME_THREE   20
#define GAME_PAIGOW  21
#define GAME_VPOKERDJ  22
#define GAME_VPOKERJ2  23
#define GAME_CARD7     24
#define GAME_SICBO     25
#define GAME_SPANISH   26
#define GAME_WAR       27
#define GAME_WILD      28
#define GAME_BAHAMA    29
#define GAME_ROYAL     30
#define GAME_ARUBA     31
#define GAME_PAIGOWT   32
#define GAME_WAVE      33
#define GAME_SUPERFUN  34
#define GAME_BONUS6    35
#define GAME_BINGO     36
#define GAME_VPOKER8   37
#define GAME_VPOKERB   38
#define GAME_VPOKER2B  39
#define GAME_VPOKER3B  40
#define GAME_357       41
#define GAME_FLOP      42
#define GAME_BOSTON5   43
#define GAME_HOLDEM    44
#define KENO_BASE      90
#define SLOTS_BASE     150

#define PROG_CARIB     1
#define PROG_VPOKER1   2
#define PROG_VPOKER5   3
#define PROG_VPOKER10  4
#define PROG_VPOKER25  5
#define PROG_VPOKER100 6
#define PROG_BAHAMA    7
#define PROG_ARUBA     8
#define PROG_BINGO     9

/*
#include "card.h"
#include "deck.h"
#include "hand.h"
*/

struct WHEEL {
  char Entry[24][5];
};

struct BET {
  int x;
  int y;
  int hand;
  int chips1;
  int chips5;
  int chips25;
  int chips100;
  int chips500;
  int chips1000;
};

#include "player.h"

#include "cardgame.h"

#ifdef GRAPHIC
prefix  rcs_Pixmap   mainScreen;
prefix  rcs_Display* display;
prefix  rcs_Window   rootWindow;
prefix  rcs_Window   mainWindow;
prefix  rcs_Pixmap   table;
#endif    

prefix int  i;

prefix int abs(int inp);
prefix void Slots(Player* player);
prefix char Upcase(char i);

prefix char buffer[80];
prefix Player* player[MAX_PLAYERS];
prefix double progressives[20];
prefix char   saveFileName[1024];

prefix void ClrScr();
prefix void Delay(int sec);
prefix void GotoXY(int x,int y);
prefix void Input(char* Buffer);
prefix void Output(const char* Buffer);
prefix int Random(int size);
prefix void Randomize();
prefix void makeName(char* buffer);
prefix void clearScreen();
prefix void getSaveFileName(char* envp[],char* filename,char* dest);
#ifdef GRAPHIC
prefix rcs_Event getEvent(rcs_Display* d);
prefix rcs_Event pollEvent(rcs_Display* d);
prefix void      displayScreen();
int actionBox(int x,int y,int w,int h,const char *msg,const char *b1,const char *b2);
int msgBox(int x,int y,int w,int h,const char *msg);
void button(rcs_GC gc,int x,int y,int w,int h);
#endif

