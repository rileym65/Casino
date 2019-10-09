#include <librcs.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "header.h"
#include "player.h"
#include "videokeno.h"

#define GAME_CAVEMAN   1
#define GAME_TOPBOT    2
#define GAME_VIDEO     3
#define GAME_SUPER     4
#define GAME_246       5
#define GAME_369       6
#define GAME_DIAMOND   7
#define GAME_SUPERWAY  8

#include "images/videokeno.xpm"
#include "images/kenored.xpm"
#include "images/kenoblue.xpm"
#include "images/kenoredcheck.xpm"
#include "images/kenobluecheck.xpm"
#include "images/kenobluea.xpm"
#include "images/kenoblueb.xpm"
#include "images/kenobluec.xpm"
#include "images/kenoreda.xpm"
#include "images/kenoredb.xpm"
#include "images/kenoredc.xpm"
#include "images/kenolightning.xpm"
#include "images/kenodiamond.xpm"
#include "images/kenobluedollar.xpm"
#include "images/kenoreddollar.xpm"
#include "images/kenomenukeno.xpm"
#include "images/kenomenusuper.xpm"
#include "images/kenomenu246.xpm"
#include "images/kenomenu369.xpm"
#include "images/kenomenudiamond.xpm"
#include "images/kenomenubonus.xpm"
#include "images/kenomenutop.xpm"
#include "images/kenomenusway.xpm"
#include "images/kenomenu.xpm"

VideoKeno::VideoKeno(Player* p) {
  int i;
  player = p;
  spots = 0;
  bet = 1;
  mult = 1;
  hits = 0;
  game = 0;
  maxBet = 4;
  creditSize = 0.05;
  credits = 0;
  setupStandard();
  for (i=0; i<80; i++) {
    playerSpots[i] = ' ';
    balls[i] = i+1;
    }
  shuffle();
  }

VideoKeno::~VideoKeno() {
  }

void VideoKeno::setGame(int g) {
  game = g;
  player->setGame(g+KENO_BASE);
  player->setSubGame(g+KENO_BASE);
  }

void VideoKeno::drawBoard() {
  int x,y;
  rcs_GC gc;
  rcs_Font font;
  gc=rcs_openGC(display,mainScreen);
  rcs_copyArea(display,table,mainScreen,gc,0,0,800,600,0,0);
  font=rcs_openFont(display,VIDEOKENO_FONT);
  rcs_setFont(display,gc,font);
  rcs_namedForeground(display,gc,"yellow");

  for (x=0; x<10; x++)
    for (y=0; y<8; y++) {
      sprintf(buffer," %2d ",y*10 + x + 1);
        rcs_drawString(display,mainScreen,gc,270+52*x,96+((y>3)?19:0)+47*y,buffer);
      }
  rcs_closeGC(display,gc);
  }

void VideoKeno::drawButtons() {
  rcs_GC gc;
  rcs_Font font;
  gc = rcs_openGC(display,mainScreen);
  font = rcs_openFont(display,ACTION_FONT);
  rcs_setFont(display,gc,font);
  button(gc,10,550,90,30);
  button(gc,130,550,90,30);
  button(gc,260,550,90,30);
  button(gc,360,550,90,30);
  button(gc,500,550,90,30);
  button(gc,650,550,90,30);
  button(gc,300,510,100,30);
  rcs_namedForeground(display,gc,"black");
  rcs_drawString(display,mainScreen,gc,15,570,"Cash Out");
  rcs_drawString(display,mainScreen,gc,150,570,"Menu");
  rcs_drawString(display,mainScreen,gc,280,570,"Bet 1");
  rcs_drawString(display,mainScreen,gc,370,570,"Bet Max");
  rcs_drawString(display,mainScreen,gc,515,570,"Erase");
  rcs_drawString(display,mainScreen,gc,665,570,"Start");
  rcs_drawString(display,mainScreen,gc,305,530,"Pay Table");
  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  }

void VideoKeno::payTable() {
  int    i,j;
  rcs_GC gc;
  rcs_Font font;
  rcs_Event event;
  char buffer[30];
  gc = rcs_openGC(display,mainScreen);
  font=rcs_openFont(display,VIDEOKENO_FONT);
  rcs_setFont(display,gc,font);
  rcs_namedForeground(display,gc,"blue");
  rcs_drawFilledBox(display,mainScreen,gc,0,0,800,600);
  rcs_namedForeground(display,gc,"yellow");
  rcs_drawLine(display,mainScreen,gc,1,75,799,75);
  for (i=0; i<11; i++) {
    sprintf(buffer,"%5d",i);
    if (i != 0) rcs_drawString(display,mainScreen,gc,75*i-25,70,buffer);
    sprintf(buffer,"%2d",i);
    rcs_drawString(display,mainScreen,gc,5,100+30*i,buffer);
    rcs_drawLine(display,mainScreen,gc,1,105+30*i,799,105+30*i);
    rcs_drawLine(display,mainScreen,gc,75*i-30,75,75*i-30,404);
    if (i > 0) {
      for (j=0; j<=10; j++) {
        sprintf(buffer,"%5ld",payouts[i][j]);
        if (payouts[i][j] != 0)
          rcs_drawString(display,mainScreen,gc,75*i-25,100+30*j,buffer);
        }
      }
    }

  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  displayScreen();
  i = 0;
  while (i == 0) {
    event = getEvent(display);
    if (event.type == EVENT_BUTTON_PRESS) {
      i = -1;
      }
    }
  drawBoard();
  showChoices();
  drawPayouts();
  drawStats();
  drawButtons();
  }

void VideoKeno::stats() {
  int i;
  int pos;
  int space;
  rcs_GC gc;
  rcs_Font font;
  rcs_Event event;
  char buffer[80];
  gc = rcs_openGC(display,mainScreen);
  font=rcs_openFont(display,STAT_FONT);
  rcs_setFont(display,gc,font);
  rcs_namedForeground(display,gc,"darkgreen");
  rcs_drawFilledBox(display,mainScreen,gc,0,0,800,600);
  rcs_namedForeground(display,gc,"yellow");
  pos = 20;
  space = 20;
  if (player->paidIn(GAME_VIDEO+KENO_BASE)>0) {
    sprintf(buffer,"Video Keno                  %12.2f  %12.2f  %5.2f%%\n",
      player->paidIn(GAME_VIDEO+KENO_BASE),
      player->paidOut(GAME_VIDEO+KENO_BASE),
      player->average(GAME_VIDEO+KENO_BASE));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player->paidIn(GAME_246+KENO_BASE)>0) {
    sprintf(buffer,"  246 Keno                  %12.2f  %12.2f  %5.2f%%\n",
      player->paidIn(GAME_246+KENO_BASE),
      player->paidOut(GAME_246+KENO_BASE),
      player->average(GAME_246+KENO_BASE));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player->paidIn(GAME_369+KENO_BASE)>0) {
    sprintf(buffer,"  369 Keno                  %12.2f  %12.2f  %5.2f%%\n",
      player->paidIn(GAME_369+KENO_BASE),
      player->paidOut(GAME_369+KENO_BASE),
      player->average(GAME_369+KENO_BASE));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player->paidIn(GAME_CAVEMAN+KENO_BASE)>0) {
    sprintf(buffer,"  Bonus Keno                %12.2f  %12.2f  %5.2f%%\n",
      player->paidIn(GAME_CAVEMAN+KENO_BASE),
      player->paidOut(GAME_CAVEMAN+KENO_BASE),
      player->average(GAME_CAVEMAN+KENO_BASE));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player->paidIn(GAME_SUPER+KENO_BASE)>0) {
    sprintf(buffer,"  Super Video Keno          %12.2f  %12.2f  %5.2f%%\n",
      player->paidIn(GAME_SUPER+KENO_BASE),
      player->paidOut(GAME_SUPER+KENO_BASE),
      player->average(GAME_SUPER+KENO_BASE));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player->paidIn(GAME_SUPERWAY+KENO_BASE)>0) {
    sprintf(buffer,"  Super Way Keno            %12.2f  %12.2f  %5.2f%%\n",
      player->paidIn(GAME_SUPERWAY+KENO_BASE),
      player->paidOut(GAME_SUPERWAY+KENO_BASE),
      player->average(GAME_SUPERWAY+KENO_BASE));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player->paidIn(GAME_DIAMOND+KENO_BASE)>0) {
    sprintf(buffer,"  Triple Diamond Keno       %12.2f  %12.2f  %5.2f%%\n",
      player->paidIn(GAME_DIAMOND+KENO_BASE),
      player->paidOut(GAME_DIAMOND+KENO_BASE),
      player->average(GAME_DIAMOND+KENO_BASE));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player->paidIn(GAME_TOPBOT+KENO_BASE)>0) {
    sprintf(buffer,"  Top Bottom Keno           %12.2f  %12.2f  %5.2f%%\n",
      player->paidIn(GAME_TOPBOT+KENO_BASE),
      player->paidOut(GAME_TOPBOT+KENO_BASE),
      player->average(GAME_TOPBOT+KENO_BASE));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  displayScreen();
  i = 0;
  while (i == 0) {
    event = getEvent(display);
    if (event.type == EVENT_BUTTON_PRESS) {
      i = -1;
      }
    }
  }

void VideoKeno::_menu() {
  rcs_GC gc;
  rcs_Font font;
  gc = rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"black");
  rcs_drawFilledBox(display,mainScreen,gc,0,0,800,600);
  rcs_drawPixmap(display,mainScreen,gc,20,150,kenomenukeno_xpm);
  rcs_drawPixmap(display,mainScreen,gc,220,150,kenomenusuper_xpm);
  rcs_drawPixmap(display,mainScreen,gc,20,250,kenomenu246_xpm);
  rcs_drawPixmap(display,mainScreen,gc,220,250,kenomenu369_xpm);
  rcs_drawPixmap(display,mainScreen,gc,420,150,kenomenudiamond_xpm);
  rcs_drawPixmap(display,mainScreen,gc,420,250,kenomenutop_xpm);
  rcs_drawPixmap(display,mainScreen,gc,620,150,kenomenubonus_xpm);
  rcs_drawPixmap(display,mainScreen,gc,620,250,kenomenusway_xpm);
  rcs_drawPixmap(display,mainScreen,gc,70,330,kenomenu_xpm);
  font=rcs_openFont(display,VIDEOKENO_FONT);
  rcs_setFont(display,gc,font);
  rcs_namedForeground(display,gc,"white");
  sprintf(buffer,"Credits: $%.2f",credits);
  rcs_drawString(display,mainScreen,gc,150,500,buffer);
  sprintf(buffer,"Money: %12.2f",player->getMoney());
  rcs_drawString(display,mainScreen,gc,150,540,buffer);

  button(gc,10,560,90,30);
  rcs_drawString(display,mainScreen,gc,20,585,"Stats");

  rcs_namedForeground(display,gc,"white");
  if (creditSize == 0.05) rcs_drawBox(display,mainScreen,gc,68,350,86,65);
  if (creditSize == 0.10) rcs_drawBox(display,mainScreen,gc,155,350,86,65);
  if (creditSize == 0.25) rcs_drawBox(display,mainScreen,gc,242,350,86,65);
  if (creditSize == 0.50) rcs_drawBox(display,mainScreen,gc,329,350,86,65);
  if (creditSize == 1.00) rcs_drawBox(display,mainScreen,gc,416,350,86,65);

  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  displayScreen();
  }

void VideoKeno::menu() {
  int i;
  int insm;
  double den;
  rcs_GC gc;
  rcs_Font font;
  rcs_Event event;
  _menu();
/*
  gc = rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"black");
  rcs_drawFilledBox(display,mainScreen,gc,0,0,800,600);
  rcs_drawPixmap(display,mainScreen,gc,20,150,kenomenukeno_xpm);
  rcs_drawPixmap(display,mainScreen,gc,220,150,kenomenusuper_xpm);
  rcs_drawPixmap(display,mainScreen,gc,20,250,kenomenu246_xpm);
  rcs_drawPixmap(display,mainScreen,gc,220,250,kenomenu369_xpm);
  rcs_drawPixmap(display,mainScreen,gc,420,150,kenomenudiamond_xpm);
  rcs_drawPixmap(display,mainScreen,gc,420,250,kenomenutop_xpm);
  rcs_drawPixmap(display,mainScreen,gc,620,150,kenomenubonus_xpm);
  rcs_drawPixmap(display,mainScreen,gc,620,250,kenomenusway_xpm);
  rcs_drawPixmap(display,mainScreen,gc,70,330,kenomenu_xpm);
  font=rcs_openFont(display,VIDEOKENO_FONT);
  rcs_setFont(display,gc,font);
  rcs_namedForeground(display,gc,"white");
  sprintf(buffer,"Credits: $%.2f",credits);
  rcs_drawString(display,mainScreen,gc,150,500,buffer);
  sprintf(buffer,"Money: %12.2f",player->getMoney());
  rcs_drawString(display,mainScreen,gc,150,540,buffer);

  button(gc,10,560,90,30);
  rcs_drawString(display,mainScreen,gc,20,585,"Stats");

  if (creditSize == 0.05) rcs_drawBox(display,mainScreen,gc,68,350,86,65);
  if (creditSize == 0.10) rcs_drawBox(display,mainScreen,gc,155,350,86,65);
  if (creditSize == 0.25) rcs_drawBox(display,mainScreen,gc,242,350,86,65);
  if (creditSize == 0.50) rcs_drawBox(display,mainScreen,gc,329,350,86,65);
  if (creditSize == 1.00) rcs_drawBox(display,mainScreen,gc,416,350,86,65);

  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  displayScreen();
*/
  game =-1;
  while (game <0) {
    event = getEvent(display);
    insm = -1;
    den = -1.0;
    if (event.type == EVENT_BUTTON_PRESS) {
/* Stats */
      if (event.d1 == 1 && event.d2 >= 12 && event.d3>=561 &&
          event.d2 <= 99 && event.d3<=589) {
        stats();
        _menu();
        }
/* Denomination 0.05 */
      if (event.d1 == 1 && event.d2 >= 68 && event.d3>=350 &&
          event.d2 <= 154 && event.d3<=415) {
        den = 0.05;
        }
/* Denomination 0.10 */
      if (event.d1 == 1 && event.d2 >= 155 && event.d3>=350 &&
          event.d2 <= 241 && event.d3<=415) {
        den = 0.10;
        }
/* Denomination 0.25 */
      if (event.d1 == 1 && event.d2 >= 242 && event.d3>=350 &&
          event.d2 <= 328 && event.d3<=415) {
        den = 0.25;
        }
/* Denomination 0.50 */
      if (event.d1 == 1 && event.d2 >= 329 && event.d3>=350 &&
          event.d2 <= 415 && event.d3<=415) {
        den = 0.50;
        }
/* Denomination 1.00 */
      if (event.d1 == 1 && event.d2 >= 416 && event.d3>=350 &&
          event.d2 <= 502 && event.d3<=415) {
        den = 1.00;
        }
      if (den != -1.0) {
        gc = rcs_openGC(display,mainScreen);
        rcs_namedForeground(display,gc,"black");
        for (i=0;i<5;i++) {
          rcs_drawBox(display,mainScreen,gc,68+87*i,350,86,65);
          }
        setDenomination(den);
        rcs_namedForeground(display,gc,"white");
        if (creditSize == 0.05) rcs_drawBox(display,mainScreen,gc,68,350,86,65);
        if (creditSize == 0.10) rcs_drawBox(display,mainScreen,gc,155,350,86,65);
        if (creditSize == 0.25) rcs_drawBox(display,mainScreen,gc,242,350,86,65);
        if (creditSize == 0.50) rcs_drawBox(display,mainScreen,gc,329,350,86,65);
        if (creditSize == 1.00) rcs_drawBox(display,mainScreen,gc,416,350,86,65);
        font=rcs_openFont(display,VIDEOKENO_FONT);
        rcs_setFont(display,gc,font);
        rcs_namedForeground(display,gc,"black");
        rcs_drawFilledBox(display,mainScreen,gc,136,465,294,103);
        rcs_namedForeground(display,gc,"white");
        sprintf(buffer,"Credits: $%.2f",credits);
        rcs_drawString(display,mainScreen,gc,150,500,buffer);
        sprintf(buffer,"Money: %12.2f",player->getMoney());
        rcs_drawString(display,mainScreen,gc,150,540,buffer);
        rcs_closeFont(display,font);
        rcs_closeGC(display,gc);
        displayScreen();
        }
/* Insert $1 */
      if (event.d1 == 1 && event.d2 >= 537 && event.d3>=333 &&
          event.d2 <= 585 && event.d3<=443 && player->getMoney()>=1) {
        insm = 1;
        }
/* Insert $5 */
      if (event.d1 == 1 && event.d2 >= 593 && event.d3>=333 &&
          event.d2 <= 641 && event.d3<=443 && player->getMoney()>=1) {
        insm = 5;
        }
/* Insert $10 */
      if (event.d1 == 1 && event.d2 >= 646 && event.d3>=333 &&
          event.d2 <= 694 && event.d3<=443 && player->getMoney()>=1) {
        insm = 10;
        }
/* Insert $20 */
      if (event.d1 == 1 && event.d2 >= 537 && event.d3>=449 &&
          event.d2 <= 585 && event.d3<=558 && player->getMoney()>=1) {
        insm = 20;
        }
/* Insert $50 */
      if (event.d1 == 1 && event.d2 >= 593 && event.d3>=449 &&
          event.d2 <= 641 && event.d3<=558 && player->getMoney()>=1) {
        insm = 50;
        }
/* Insert $100 */
      if (event.d1 == 1 && event.d2 >= 646 && event.d3>=449 &&
          event.d2 <= 694 && event.d3<=558 && player->getMoney()>=1) {
        insm = 100;
        }
      if (insm != -1) {
        insertMoney(insm);
        gc = rcs_openGC(display,mainScreen);
        font=rcs_openFont(display,VIDEOKENO_FONT);
        rcs_setFont(display,gc,font);
        rcs_namedForeground(display,gc,"black");
        rcs_drawFilledBox(display,mainScreen,gc,136,465,294,103);
        rcs_namedForeground(display,gc,"white");
        sprintf(buffer,"Credits: $%.2f",credits);
        rcs_drawString(display,mainScreen,gc,150,500,buffer);
        sprintf(buffer,"Money: %12.2f",player->getMoney());
        rcs_drawString(display,mainScreen,gc,150,540,buffer);
        rcs_closeFont(display,font);
        rcs_closeGC(display,gc);
        displayScreen();
        }
/* video keno */
      if (event.d1 == 1 && event.d2 >= 24 && event.d3>=154 &&
          event.d2 <= 166 && event.d3<=215) {
        setGame(GAME_VIDEO);
        }
/* video Super keno */
      if (event.d1 == 1 && event.d2 >= 223 && event.d3>=154 &&
          event.d2 <= 365 && event.d3<=215) {
        setGame(GAME_SUPER);
        }
/* video Triple Diamond */
      if (event.d1 == 1 && event.d2 >= 424 && event.d3>=154 &&
          event.d2 <= 566 && event.d3<=215) {
        setGame(GAME_DIAMOND);
        }
/* video bonus keno */
      if (event.d1 == 1 && event.d2 >= 623 && event.d3>=154 &&
          event.d2 <= 766 && event.d3<=215) {
        setGame(GAME_CAVEMAN);
        }
/* 246 keno */
      if (event.d1 == 1 && event.d2 >= 24 && event.d3>=254 &&
          event.d2 <= 166 && event.d3<=315) {
        setGame(GAME_246);
        }
/* 369 keno */
      if (event.d1 == 1 && event.d2 >= 224 && event.d3>=254 &&
          event.d2 <= 366 && event.d3<=315) {
        setGame(GAME_369);
        }
/* top bottom keno */
      if (event.d1 == 1 && event.d2 >= 424 && event.d3>=254 &&
          event.d2 <= 566 && event.d3<=315) {
        setGame(GAME_TOPBOT);
        }
/* Super Way keno */
      if (event.d1 == 1 && event.d2 >= 623 && event.d3>=254 &&
          event.d2 <= 766 && event.d3<=315) {
        setGame(GAME_SUPERWAY);
        }
      }
    }
  maxBet = 4;
  bet = 1;
  freeMult = 1;
  mult = 1;
  freeGames = 0;
  for (i=0; i<80; i++) playerSpots[i] = ' ';
  spots = 0;
  spotsA = 0;
  spotsB = 0;
  spotsC = 0;
  hitsA = 0;
  hitsB = 0;
  hitsC = 0;
  grA = 0;
  grB = 0;
  grC = 0;
  switch (game) {
    case  GAME_CAVEMAN: setupCaveman(); break;
    case  GAME_TOPBOT : setupTopBottom(); break;
    case  GAME_VIDEO  : setupVideo(); break;
    case  GAME_SUPER  : setupSuper(); break;
    case  GAME_246    : setup246(); break;
    case  GAME_369    : setup369(); break;
    case  GAME_DIAMOND: setupDiamond(); break;
    case  GAME_SUPERWAY: setupSuperWay(); break;
    default: setupStandard(); break;
    }
  Randomize();
  drawBoard();
  drawStats();
  if (game == GAME_TOPBOT) showChoices();
  drawPayouts();
  drawButtons();
  }

void VideoKeno::play() {
  int i,j;
  int cleared;
  int play;
  rcs_Event event;
  table = rcs_xpmToPixmap(display,mainWindow,videokeno_xpm);
  sessionVip = 0;
  cleared = 0;
  menu();
/*
  maxBet = 4;
  bet = 1;
  freeMult = 1;
  freeGames = 0;
  for (i=0; i<80; i++) playerSpots[i] = ' ';
  spots = 0;
  spotsA = 0;
  spotsB = 0;
  spotsC = 0;
  hitsA = 0;
  hitsB = 0;
  hitsC = 0;
  grA = 0;
  grB = 0;
  grC = 0;
  switch (game) {
    case  GAME_CAVEMAN: setupCaveman(); break;
    case  GAME_TOPBOT : setupTopBottom(); break;
    case  GAME_VIDEO  : setupVideo(); break;
    case  GAME_SUPER  : setupSuper(); break;
    case  GAME_246    : setup246(); break;
    case  GAME_369    : setup369(); break;
    case  GAME_DIAMOND: setupDiamond(); break;
    case  GAME_SUPERWAY: setupSuperWay(); break;
    default: setupStandard(); break;
    }
*/
  Randomize();
  drawBoard();
  drawStats();
  if (game == GAME_TOPBOT) showChoices();
  drawPayouts();
  drawButtons();
  displayScreen();
  while (1) {
    event = getEvent(display);
    if (event.type == EVENT_BUTTON_PRESS) {
      i=-1;
/* Erase */
      if (event.d1 == 1 && event.d2 >= 501 && event.d3>=552 &&
          event.d2 <= 589 && event.d3<=581) {
        for (j=0; j<80; j++) playerSpots[j] = ' ';
        spots = 0;
        spotsA = 0;
        spotsB = 0;
        spotsC = 0;
        cleared = 1;
        showChoices();
        drawStats();
        drawPayouts();
        drawButtons();
        displayScreen();
        }
/* Cash Out */
      if (event.d1 == 1 && event.d2 >= 11 && event.d3>=552 &&
          event.d2 <= 101 && event.d3<=581) {
        return;
        }
/* Pay Table */
      if (event.d1 == 1 && event.d2 >= 301 && event.d3>=512 &&
          event.d2 <= 400 && event.d3<=539) {
        payTable();
        cleared = 0;
        displayScreen();
        }
/* Menu */
      if (event.d1 == 1 && event.d2 >= 131 && event.d3>=552 &&
          event.d2 <= 218 && event.d3<=581) {
        menu();
        cleared = 0;
        displayScreen();
        }
/* Bet 1 */
      if (event.d1 == 1 && event.d2 >= 262 && event.d3>=552 &&
          event.d2 <= 349 && event.d3<=581) {
        if (++bet > maxBet) bet=1;
        drawStats();
        drawPayouts();
        displayScreen();
        }
/* Bet Max */
      if (event.d1 == 1 && event.d2 >= 362 && event.d3>=552 &&
          event.d2 <= 449 && event.d3<=581) {
        bet=maxBet;
        drawStats();
        drawPayouts();
        displayScreen();
        }
/* check for clicking on 1-40 */
      if (event.d1 == 1 && event.d2 >= 265 && event.d3>=64 &&
          event.d2 <= 787 && event.d3<=253) {
        i = 1 + (event.d2-265)/52 + ((event.d3-64)/47 )*10;
        }
      if (event.d1 == 1 && event.d2 >= 265 && event.d3>=271 &&
          event.d2 <= 787 && event.d3<=462) {
        i = 41 + (event.d2-265)/52 + ((event.d3-271)/47 )*10;
        }
      if (i != -1) {
        if (cleared == 0) {
          showChoices();
          drawButtons();
          cleared = 1;
          }
        spotClicked(i);
        drawStats();
        displayScreen();
        }
/* Start */
      if (event.d1 == 1 && event.d2 >= 651 && event.d3>=552 &&
          event.d2 <= 740 && event.d3<=581 &&
          bet*creditSize <= credits && spots >= min) {
        credits -= (bet * creditSize);
        player->addPaidIn((double)(bet * creditSize));
        sessionVip += (double)(creditSize * bet);
        mult = 1;
        play = 1;
        while (play == 1 || freeGames > 0) {
          play = 0;
          showChoices();
          drawStats();
          drawPayouts();
          round();
          if (game == GAME_246 || game == GAME_369 || game == GAME_SUPERWAY) {
            player->addPaidOut((double)(creditsWon * creditSize));
            credits += creditsWon*creditSize;
            } else {
            player->addPaidOut((double)(payouts[spots][hits]*bet*mult * creditSize));
            credits += payouts[spots][hits]*bet*mult*creditSize;
            }
          drawStats();
          hitsA = 0;
          hitsB = 0;
          hitsC = 0;
          hits = 0;
          cleared = 0;
          if (freeGames != 0) Delay(2);
          }
        drawButtons();
        displayScreen();
        }
      }
/*
    mult = 1;
    drawStats();
    if (freeGames == 0) {
      key = doInput();
      if (key < 0) {
        player->addVip(long(sessionVip));
        return;
        }
      credits -= bet;
      player->paidIn(bet);
      sessionVip += (double)(creditSize * bet);
      }
    drawStats();
    drawPayouts();
    showChoices();
    round();
  
    if (freeGames != 0) {
//      rawPrint(10,11," F R E E   G A M E");
      Delay(3);
      } else {
//      rawPrint(10,11," G A M E   O V E R");
      Delay(5);
      }
    hitsA = 0;
    hitsB = 0;
    hitsC = 0;
*/
    }
  }

void VideoKeno::clearPayouts() {
  int x,y;
  for (x=0; x<41; x++)
    for (y=0; y<21; y++) payouts[x][y] = 0;
  }

void VideoKeno::setupTopBottom() {
  int i;
  for (i=0;i<40;i++) playerSpots[i] = '*';
  for (i=40;i<80;i++) playerSpots[i] = ' ';
  spots = 40;
  min = 40;
  max = 40;
  clearPayouts();
  clearPayouts();

  payouts[40][20] = 12500;
  payouts[40][0]  = 12500;
  payouts[40][19] = 5000;
  payouts[40][1]  = 5000;
  payouts[40][18] = 492;
  payouts[40][2]  = 492;
  payouts[40][17] = 122;
  payouts[40][3]  = 122;
  payouts[40][16] = 28;
  payouts[40][4]  = 28;
  payouts[40][15] = 11;
  payouts[40][5]  = 11;
  payouts[40][14] = 3;
  payouts[40][6]  = 3;
  payouts[40][13] = 2;
  payouts[40][7]  = 2;
  payouts[40][12]  = 1;
  }

void VideoKeno::setup246() {
  min = 6;
  max = 6;
  grA = 2;
  grB = 2;
  grC = 2;
  maxBet = 28;
  clearPayouts();

  payouts[2][1] = 1;
  payouts[2][2] = 9;

  payouts[4][2] = 2;
  payouts[4][3] = 5;
  payouts[4][4] = 70;

  payouts[6][3] = 3;
  payouts[6][4] = 4;
  payouts[6][5] = 48;
  payouts[6][6] = 1500;
  }

void VideoKeno::setupSuperWay() {
  min = 9;
  max = 9;
  grA = 4;
  grB = 3;
  grC = 2;
  maxBet = 28;
  clearPayouts();

  payouts[2][1] = 1;
  payouts[2][2] = 9;

  payouts[3][2] = 2;
  payouts[3][3] = 44;

  payouts[4][2] = 2;
  payouts[4][3] = 5;
  payouts[4][4] = 80;

  payouts[5][3] = 3;
  payouts[5][4] = 9;
  payouts[5][5] = 800;

  payouts[6][3] = 3;
  payouts[6][4] = 4;
  payouts[6][5] = 56;
  payouts[6][6] = 1500;

  payouts[7][3] = 1;
  payouts[7][4] = 2;
  payouts[7][5] = 16;
  payouts[7][6] = 380;
  payouts[7][7] = 7000;

  payouts[9][4] = 1;
  payouts[9][5] = 6;
  payouts[9][6] = 38;
  payouts[9][7] = 300;
  payouts[9][8] = 4700;
  payouts[9][9] = 10000;
  }

void VideoKeno::setup369() {
  min = 9;
  max = 9;
  grA = 3;
  grB = 3;
  grC = 3;
  maxBet = 28;
  clearPayouts();

  payouts[3][2] = 2;
  payouts[3][3] = 44;

  payouts[6][3] = 3;
  payouts[6][4] = 4;
  payouts[6][5] = 54;
  payouts[6][6] = 1600;

  payouts[9][4] = 1;
  payouts[9][5] = 6;
  payouts[9][6] = 38;
  payouts[9][7] = 300;
  payouts[9][8] = 4700;
  payouts[9][9] = 10000;
  }

void VideoKeno::setupCaveman() {
  min = 2;
  max = 10;
  clearPayouts();

  payouts[2][1] = 1;
  payouts[2][2] = 3;

  payouts[3][2] = 2;
  payouts[3][3] = 24;

  payouts[4][2] = 1;
  payouts[4][3] = 5;
  payouts[4][4] = 67;

  payouts[5][2] = 1;
  payouts[5][3] = 2;
  payouts[5][4] = 5;
  payouts[5][5] = 215;

  payouts[6][3] = 2;
  payouts[6][4] = 5;
  payouts[6][5] = 49;
  payouts[6][6] = 800;

  payouts[7][3] = 1;
  payouts[7][4] = 3;
  payouts[7][5] = 12;
  payouts[7][6] = 245;
  payouts[7][7] = 2000;

  payouts[8][3] = 1;
  payouts[8][4] = 2;
  payouts[8][5] = 4;
  payouts[8][6] = 48;
  payouts[8][7] = 500;
  payouts[8][8] = 2000;

  payouts[9][4] = 1;
  payouts[9][5] = 5;
  payouts[9][6] = 35;
  payouts[9][7] = 255;
  payouts[9][8] = 1500;
  payouts[9][9] = 2000;

  payouts[10][4] = 1;
  payouts[10][5] = 4;
  payouts[10][6] = 9;
  payouts[10][7] = 100;
  payouts[10][8] = 300;
  payouts[10][9] = 1500;
  payouts[10][10] = 2000;
  }

void VideoKeno::setupVideo() {
  min = 1;
  max = 10;
  clearPayouts();

  payouts[1][1] = 3;

  payouts[2][2] = 14;

  payouts[3][2] = 2;
  payouts[3][3] = 42;

  payouts[4][2] = 2;
  payouts[4][3] = 5;
  payouts[4][4] = 68;

  payouts[5][3] = 3;
  payouts[5][4] = 10;
  payouts[5][5] = 740;

  payouts[6][3] = 2;
  payouts[6][4] = 4;
  payouts[6][5] = 46;
  payouts[6][6] = 1600;

  payouts[7][3] = 1;
  payouts[7][4] = 2;
  payouts[7][5] = 21;
  payouts[7][6] = 300;
  payouts[7][7] = 7000;

  payouts[8][4] = 2;
  payouts[8][5] = 12;
  payouts[8][6] = 98;
  payouts[8][7] = 1250;
  payouts[8][8] = 8000;

  payouts[9][4] = 1;
  payouts[9][5] = 6;
  payouts[9][6] = 40;
  payouts[9][7] = 300;
  payouts[9][8] = 4000;
  payouts[9][9] = 9000;

  payouts[10][5] = 5;
  payouts[10][6] = 21;
  payouts[10][7] = 115;
  payouts[10][8] = 1000;
  payouts[10][9] = 4000;
  payouts[10][10] = 10000;
  }

void VideoKeno::setupSuper() {
  min = 1;
  max = 10;
  clearPayouts();

  payouts[1][1] = 3;

  payouts[2][2] = 11;

  payouts[3][2] = 1;
  payouts[3][3] = 35;

  payouts[4][2] = 1;
  payouts[4][3] = 4;
  payouts[4][4] = 73;

  payouts[5][3] = 2;
  payouts[5][4] = 10;
  payouts[5][5] = 400;

  payouts[6][3] = 1;
  payouts[6][4] = 3;
  payouts[6][5] = 68;
  payouts[6][6] = 800;

  payouts[7][3] = 1;
  payouts[7][4] = 2;
  payouts[7][5] = 8;
  payouts[7][6] = 222;
  payouts[7][7] = 800;

  payouts[8][4] = 1;
  payouts[8][5] = 6;
  payouts[8][6] = 58;
  payouts[8][7] = 850;
  payouts[8][8] = 2500;

  payouts[9][4] = 1;
  payouts[9][5] = 2;
  payouts[9][6] = 14;
  payouts[9][7] = 275;
  payouts[9][8] = 1200;
  payouts[9][9] = 2500;

  payouts[10][5] = 1;
  payouts[10][6] = 12;
  payouts[10][7] = 75;
  payouts[10][8] = 850;
  payouts[10][9] = 1200;
  payouts[10][10] = 2500;
  }

void VideoKeno::setupStandard() {
  min = 1;
  max = 15;
  clearPayouts();
  payouts[1][1]=3;

  payouts[2][2]=12;

  payouts[3][2]=1;
  payouts[3][3]=43;

  payouts[4][2]=1;
  payouts[4][3]=3;
  payouts[4][4]=130;

  payouts[5][3]=1;
  payouts[5][4]=10;
  payouts[5][5]=800;

  payouts[6][3]=1;
  payouts[6][4]=4;
  payouts[6][5]=95;
  payouts[6][6]=1500;

  payouts[7][4]=1;
  payouts[7][5]=25;
  payouts[7][6]=350;
  payouts[7][7]=8000;

  payouts[8][5]=9;
  payouts[8][6]=90;
  payouts[8][7]=1500;
  payouts[8][8]=25000;

  payouts[9][5]=4;
  payouts[9][6]=50;
  payouts[9][7]=280;
  payouts[9][8]=4000;
  payouts[9][9]=50000;

  payouts[10][5]=1;
  payouts[10][6]=22;
  payouts[10][7]=150;
  payouts[10][8]=1000;
  payouts[10][9]=5000;
  payouts[10][10]=100000;

  payouts[11][6]=8;
  payouts[11][7]=80;
  payouts[11][8]=400;
  payouts[11][9]=2500;
  payouts[11][10]=25000;
  payouts[11][11]=100000;

  payouts[12][6]=5;
  payouts[12][7]=32;
  payouts[12][8]=200;
  payouts[12][9]=1000;
  payouts[12][10]=5000;
  payouts[12][11]=25000;
  payouts[12][12]=100000;

  payouts[13][0]=1;
  payouts[13][6]=1;
  payouts[13][7]=20;
  payouts[13][8]=80;
  payouts[13][9]=600;
  payouts[13][10]=3500;
  payouts[13][11]=10000;
  payouts[13][12]=50000;
  payouts[13][13]=100000;

  payouts[14][0]=1;
  payouts[14][6]=1;
  payouts[14][7]=9;
  payouts[14][8]=42;
  payouts[14][9]=310;
  payouts[14][10]=1100;
  payouts[14][11]=8000;
  payouts[14][12]=25000;
  payouts[14][13]=50000;
  payouts[14][14]=100000;

  payouts[15][0]=1;
  payouts[15][7]=10;
  payouts[15][8]=25;
  payouts[15][9]=100;
  payouts[15][10]=300;
  payouts[15][11]=2800;
  payouts[15][12]=25000;
  payouts[15][13]=50000;
  payouts[15][14]=100000;
  payouts[15][15]=100000;
  }

void VideoKeno::setupDiamond() {
  min = 2;
  max = 10;
  freeMult = 3;
  clearPayouts();

  payouts[2][2] = 11;

  payouts[3][2] = 1;
  payouts[3][3] = 39;

  payouts[4][2] = 1;
  payouts[4][3] = 5;
  payouts[4][4] = 85;

  payouts[5][3] = 1;
  payouts[5][4] = 9;
  payouts[5][5] = 774;

  payouts[6][0] = 1;
  payouts[6][4] = 4;
  payouts[6][5] = 71;
  payouts[6][6] = 1500;

  payouts[7][0] = 1;
  payouts[7][4] = 1;
  payouts[7][5] = 20;
  payouts[7][6] = 354;
  payouts[7][7] = 3500;

  payouts[8][0] = 1;
  payouts[8][4] = 1;
  payouts[8][5] = 8;
  payouts[8][6] = 50;
  payouts[8][7] = 1500;
  payouts[8][8] = 3500;

  payouts[9][0] = 1;
  payouts[9][4] = 1;
  payouts[9][5] = 3;
  payouts[9][6] = 40;
  payouts[9][7] = 226;
  payouts[9][8] = 1500;
  payouts[9][9] = 3500;

  payouts[10][0] = 1;
  payouts[10][5] = 2;
  payouts[10][6] = 23;
  payouts[10][7] = 105;
  payouts[10][8] = 700;
  payouts[10][9] = 1500;
  payouts[10][10] = 3500;
  }

void VideoKeno::drawPayouts() {
  rcs_GC gc;
  rcs_Font font;
  int i,l;
  gc = rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"white");
  font = rcs_openFont(display,KENO_STAT_FONT);
  rcs_setFont(display,gc,font);
  rcs_copyArea(display,table,mainScreen,gc,14,194,164,344,14,194);
  sprintf(buffer,"Marked: %d",spots);
  rcs_drawString(display,mainScreen,gc,25,460,buffer);
  sprintf(buffer,"Hits: %d",hits);
  rcs_drawString(display,mainScreen,gc,25,480,buffer);
  rcs_namedForeground(display,gc,"yellow");
  if (game == GAME_246 || game == GAME_369 || game == GAME_SUPERWAY) {
    sprintf(buffer,"A - B - C  :%2d/%d",hitsA + hitsB + hitsC, grA+grB+grC);
    rcs_drawString(display,mainScreen,gc,20,215,buffer);
    sprintf(buffer,"A - B      :%2d/%d",hitsA + hitsB, grA+grB);
    rcs_drawString(display,mainScreen,gc,20,248,buffer);
    sprintf(buffer,"A - C      :%2d/%d",hitsA + hitsC, grA+grC);
    rcs_drawString(display,mainScreen,gc,20,281,buffer);
    sprintf(buffer,"B - C      :%2d/%d",hitsB + hitsC, grB+grC);
    rcs_drawString(display,mainScreen,gc,20,314,buffer);
    sprintf(buffer,"A          :%2d/%d",hitsA, grA);
    rcs_drawString(display,mainScreen,gc,20,347,buffer);
    sprintf(buffer,"B          :%2d/%d",hitsB, grB);
    rcs_drawString(display,mainScreen,gc,20,380,buffer);
    sprintf(buffer,"C          :%2d/%d",hitsC, grC);
    rcs_drawString(display,mainScreen,gc,20,413,buffer);

      creditsWon = 0;
      i = ( (bet % 7) >=1) ? (bet+7)/7 : bet/7;
      sprintf(buffer,"Bet: %1d  Won: %-5ld",i,
        payouts[grA+grB+grC][hitsA+hitsB+hitsC]*i);
      if (payouts[grA+grB+grC][hitsA+hitsB+hitsC]*i > 0) {
        rcs_namedForeground(display,gc,"yellow");
        rcs_drawFilledBox(display,mainScreen,gc,18,217,154,13);
        rcs_namedForeground(display,gc,"blue");
        }
      rcs_drawString(display,mainScreen,gc,20,227,buffer);
      rcs_namedForeground(display,gc,"yellow");
      creditsWon += payouts[grA+grB+grC][hitsA+hitsB+hitsC]*i;

      i = ( (bet % 7) >=2) ? (bet+7)/7 : bet/7;
      sprintf(buffer,"Bet: %1d  Won: %-5ld",i,
        payouts[grA+grB][hitsA+hitsB]*i);
      if (payouts[grA+grB][hitsA+hitsB]*i > 0) {
        rcs_namedForeground(display,gc,"yellow");
        rcs_drawFilledBox(display,mainScreen,gc,18,250,154,13);
        rcs_namedForeground(display,gc,"blue");
        }
      rcs_drawString(display,mainScreen,gc,20,260,buffer);
      rcs_namedForeground(display,gc,"yellow");
      creditsWon += payouts[grA+grB][hitsA+hitsB]*i;

      i = ( (bet % 7) >=3) ? (bet+7)/7 : bet/7;
      sprintf(buffer,"Bet: %1d  Won: %-5ld",i,
        payouts[grA+grC][hitsA+hitsC]*i);
      if (payouts[grA+grC][hitsA+hitsC]*i > 0) {
        rcs_namedForeground(display,gc,"yellow");
        rcs_drawFilledBox(display,mainScreen,gc,18,283,154,13);
        rcs_namedForeground(display,gc,"blue");
        }
      rcs_drawString(display,mainScreen,gc,20,293,buffer);
      rcs_namedForeground(display,gc,"yellow");
      creditsWon += payouts[grA+grC][hitsA+hitsC]*i;

      i = ( (bet % 7) >=4) ? (bet+7)/7 : bet/7;
      sprintf(buffer,"Bet: %1d  Won: %-5ld",i,
        payouts[grB+grC][hitsB+hitsC]*i);
      if (payouts[grB+grC][hitsB+hitsC]*i > 0) {
        rcs_namedForeground(display,gc,"yellow");
        rcs_drawFilledBox(display,mainScreen,gc,18,316,154,13);
        rcs_namedForeground(display,gc,"blue");
        }
      rcs_drawString(display,mainScreen,gc,20,326,buffer);
      rcs_namedForeground(display,gc,"yellow");
      creditsWon += payouts[grB+grC][hitsB+hitsC]*i;

      i = ( (bet % 7) >=5) ? (bet+7)/7 : bet/7;
      sprintf(buffer,"Bet: %1d  Won: %-5ld",i,
        payouts[grA][hitsA]*i);
      if (payouts[grA][hitsA]*i > 0) {
        rcs_namedForeground(display,gc,"yellow");
        rcs_drawFilledBox(display,mainScreen,gc,18,349,154,13);
        rcs_namedForeground(display,gc,"blue");
        }
      rcs_drawString(display,mainScreen,gc,20,359,buffer);
      rcs_namedForeground(display,gc,"yellow");
      creditsWon += payouts[grA][hitsA]*i;

      i = ( (bet % 7) >=6) ? (bet+7)/7 : bet/7;
      sprintf(buffer,"Bet: %1d  Won: %-5ld",i,
        payouts[grB][hitsB]*i);
      if (payouts[grB][hitsB]*i > 0) {
        rcs_namedForeground(display,gc,"yellow");
        rcs_drawFilledBox(display,mainScreen,gc,18,382,154,13);
        rcs_namedForeground(display,gc,"blue");
        }
      rcs_drawString(display,mainScreen,gc,20,392,buffer);
      rcs_namedForeground(display,gc,"yellow");
      creditsWon += payouts[grB][hitsB]*i;

      i = bet / 7;
      sprintf(buffer,"Bet: %1d  Won: %-5ld",i,
        payouts[grC][hitsC]*i);
      if (payouts[grC][hitsC]*i > 0) {
        rcs_namedForeground(display,gc,"yellow");
        rcs_drawFilledBox(display,mainScreen,gc,18,415,154,13);
        rcs_namedForeground(display,gc,"blue");
        }
      rcs_drawString(display,mainScreen,gc,20,425,buffer);
      rcs_namedForeground(display,gc,"yellow");
      creditsWon += payouts[grC][hitsC]*i;

      sprintf(buffer,"Won: %ld",creditsWon);
      rcs_namedForeground(display,gc,"white");
      rcs_drawString(display,mainScreen,gc,25,500,buffer);
      rcs_closeFont(display,font);
      rcs_closeGC(display,gc);
    return;
    }
  if (game == GAME_TOPBOT) {
    l = 0;
    for (i=0; i<8; i++)
      if (payouts[40][i] != 0 || payouts[40][20-i] != 0) {
        if (i == hits || (20-i) == hits) {
          rcs_namedForeground(display,gc,"yellow");
          rcs_drawFilledBox(display,mainScreen,gc,18,226+17*l,154,17);
          rcs_namedForeground(display,gc,"blue");
          }
        sprintf(buffer,"%2d or %2d  %6ld",i,20-i,payouts[spots][i]*bet*mult);
        rcs_drawString(display,mainScreen,gc,22,240+17*(l++),buffer);
        if (i == hits || (20-i) == hits) rcs_namedForeground(display,gc,"yellow");
        }
    if (hits == 12) {
      rcs_namedForeground(display,gc,"yellow");
      rcs_drawFilledBox(display,mainScreen,gc,18,226+17*l,154,17);
      rcs_namedForeground(display,gc,"blue");
      }
    sprintf(buffer," 12       %6ld",payouts[spots][12]*bet*mult);
    rcs_drawString(display,mainScreen,gc,22,240+17*(l++),buffer);
    rcs_closeFont(display,font);
    rcs_closeGC(display,gc);
    return;
    }
  if (mult > 1) {
    sprintf(buffer,"Mult x%ld",mult);
    rcs_namedForeground(display,gc,"red");
    rcs_drawString(display,mainScreen,gc,25,220,buffer);
    rcs_namedForeground(display,gc,"yellow");
    }
  l = 0;
  for (i=0; i<21; i++)
    if (payouts[spots][i] != 0) {
      if (i == hits) {
        rcs_namedForeground(display,gc,"yellow");
        rcs_drawFilledBox(display,mainScreen,gc,18,226+17*l,154,17);
        rcs_namedForeground(display,gc,"blue");
        }
      sprintf(buffer,"%2d     %9.2f",i,payouts[spots][i]*bet*mult*creditSize);
        rcs_drawString(display,mainScreen,gc,25,240+17*(l++),buffer);
      if (i == hits) rcs_namedForeground(display,gc,"yellow");
      }
  }

int VideoKeno::doInput() {
  int cursorX;
  int cursorY;
  int key;
  int i,j;
  showChoices();
/*
  for (i=0; i<80; i++)
    if (playerSpots[i] != ' ') {
      nx=i % 10;
      ny=i / 10;
      rawPrint(nx*4 + 4,( (ny<4) ? ny + 1 : ny + 2 )," ** " );
      }
*/
  cursorX = 0;
  cursorY = 0;
  GotoXY(10,15);
  printf("Bet: %2d\n",bet);
  key = 1;
  while (key != 0) {
//    rawPrint(cursorX*4 + 4,(cursorY < 4) ? cursorY + 1 : cursorY + 2,"<");
//    rawPrint(cursorX*4 + 7,(cursorY < 4) ? cursorY + 1 : cursorY + 2,">");
//    while ((key = Inkey()) == 0);
//    rawPrint(cursorX*4 + 4,(cursorY < 4) ? cursorY + 1 : cursorY + 2," ");
//    rawPrint(cursorX*4 + 7,(cursorY < 4) ? cursorY + 1 : cursorY + 2," ");
    if (key == 27) return -1;
    if (key == MTERM_RIGHT) {
      if (++cursorX == 10) cursorX = 0;
      }
    if (key == MTERM_LEFT) {
      if (--cursorX == -1) cursorX = 9;
      }
    if (key == MTERM_DOWN) {
      if (++cursorY == 8) cursorY = 0;
      }
    if (key == MTERM_UP) {
      if (--cursorY == -1) cursorY = 7;
      }
    if (key == '+' && bet < maxBet) {
      bet++;
      GotoXY(10,15);
      printf("Bet: %2d\n",bet);
      drawPayouts();
      }
    if (key == '-' && bet > 1) {
      bet--;
      GotoXY(10,15);
      printf("Bet: %2d\n",bet);
      drawPayouts();
      }
    if (key == 13 && spots >= min && bet <= credits) {
      key = 0;
      }
    if (key == 32) {
      i = cursorY*10 + cursorX;
      switch (game) {
        case GAME_TOPBOT:
          drawBoard();
          for (j=0;j<80;j++) playerSpots[j]=' ';
          if (i < 40) {
            for (j=0; j<40; j++) playerSpots[j]='*';
            } else {
            for (j=40; j<80; j++) playerSpots[j]='*';
            }
          showChoices();
          break;
        case GAME_246:
        case GAME_369:
        case GAME_SUPERWAY:
          if (playerSpots[i] != ' ') {
            switch (playerSpots[i]) {
              case 'A': spotsA--; break;
              case 'B': spotsB--; break;
              case 'C': spotsC--; break;
              }
            playerSpots[i] = ' ';
            sprintf(buffer,"%2d",i+1);
//            rawPrint(cursorX*4 + 5,(cursorY<4) ? cursorY+1 : cursorY+2,buffer);
            spots--;
            drawPayouts();
            } else if (spots < max) {
            if (spotsA < grA) { playerSpots[i] = 'A'; spotsA++; }
            else if (spotsB < grB) { playerSpots[i] = 'B'; spotsB++; }
            else { playerSpots[i] = 'C'; spotsC++; }
/*
            rawPrint(cursorX*4 + 5,(cursorY<4) ? cursorY+1 : cursorY+2,"**");
*/
            showChoices();
            spots++;
            drawPayouts();
            }
          break;
        default:
          if (playerSpots[i] != ' ') {
            playerSpots[i] = ' ';
            sprintf(buffer,"%2d",i+1);
//            rawPrint(cursorX*4 + 5,(cursorY<4) ? cursorY+1 : cursorY+2,buffer);
            spots--;
            drawPayouts();
            } else if (spots < max) {
            playerSpots[i] = '*';
//            rawPrint(cursorX*4 + 5,(cursorY<4) ? cursorY+1 : cursorY+2,"**");
            spots++;
            drawPayouts();
            }
        }
      }
    }
  return 0;
  }

void VideoKeno::round() {
  int i;
  int n;
  int cx,cy;
  int eggs;
  int diamonds;
  char freeGameFlag;
  rcs_GC gc;
  diamonds = 0;
  drawn = 0;
  hits = 0;
  eggs = 0;
  hitsA = 0;
  hitsB = 0;
  hitsC = 0;
  time_t  start;
  creditsWon = 0;
  sprintf(buffer,"Catch: %2d  win: %-7ld",hits,payouts[spots][hits]*bet*mult);
//  rawPrint(5,17,buffer);
  for (i=0; i<80; i++) picked[i] = ' ';
/*
  for (i=0; i<80; i++)
    if (playerSpots[i] != ' ') {
      cx=i % 10;
      cy=i / 10;
      sprintf(buffer,"(%2d)",i+1);
      rawPrint(cx*4 + 4,( (cy<4) ? cy + 1 : cy + 2 ), buffer );
      }
*/
  if (game == GAME_CAVEMAN) {
    gc = rcs_openGC(display,mainScreen);
    for (i=0; i<3; i++) {
      n=Random(80);
      while (playerSpots[n] != ' ') n=Random(80);
      cx=268 + (n % 10) * 52;
      cy=67 + ((n > 39) ? 19 : 0) + (n / 10) * 47;
      rcs_drawPixmap(display,mainScreen,gc,cx,cy,kenobluedollar_xpm);
      playerSpots[n] = 'o';
      }
    rcs_closeGC(display,gc);
    displayScreen();
    }
  if (game == GAME_DIAMOND) {
    for (i=0; i<3; i++) {
      n=Random(80);
      while (playerSpots[n] != ' ') n=Random(80);
      playerSpots[n] = 'd';
      }
    }
  shuffle();
  freeGameFlag = ' ';
  if (freeGames != 0) {
    mult = freeMult;
    drawPayouts();
    freeGames--;
    freeGameFlag = '*';
    }
  for (i=0; i<20; i++) {
    n=balls[i]-1;
    drawn++;
    cx=n % 10;
    cy=n / 10;
/*
    rawPrint(cx*4 + 5,( (cy<4) ? cy + 1 : cy + 2 ), "**" );
*/
    markSpot(n);
    if (playerSpots[n] == 'A') {
      hits++;
      hitsA++;
      drawPayouts();
      }
    if (playerSpots[n] == 'B') {
      hits++;
      hitsB++;
      drawPayouts();
      }
    if (playerSpots[n] == 'C') {
      hits++;
      hitsC++;
      drawPayouts();
      }
    if (playerSpots[n] == '*') {
      hits++;
      drawPayouts();
      }
    if (playerSpots[n] == 'o') {
      eggs++;
      if (eggs == 2) mult = 4;
      if (eggs == 3) mult = 10;
      drawPayouts();
      }
    if (playerSpots[n] == 'd') {
      diamonds++;
      if (diamonds == 3) {
        mult *= 3;
        if (freeGameFlag != '*') freeGames = 3;
        }
      drawPayouts();
//      rawPrint(cx*4 + 5,( (cy<4) ? cy + 1 : cy + 2 ), "<>" );
      }
    if (i==0 && playerSpots[n] == '*' && game == 4) {
      mult = 4;
      drawPayouts();
      }
    if (game == GAME_246 || game == GAME_369 || game == GAME_SUPERWAY) {
      sprintf(buffer,"Catch: %2d  won: %-7ld   : $%-12.2f",hits,
        creditsWon,
        (double)(creditsWon * creditSize));
      } else {
      sprintf(buffer,"Catch: %2d  won: %-7ld   : $%-12.2f",hits,
        payouts[spots][hits]*bet*mult,
        (double)(bet*mult*payouts[spots][hits] * creditSize));
      }
//    rawPrint(5,17,buffer);
    picked[n] = '*';
    start=rcs_time()+250;
    while (rcs_time() < start && abs(start - rcs_time()) < 1000);
//    Delay(1);
    }
  for (i=0; i<80; i++)
    if (playerSpots[i] != '*' &&
        playerSpots[i] != 'A' &&
        playerSpots[i] != 'B' &&
        playerSpots[i] != 'C') playerSpots[i]=' ';
  }

void VideoKeno::drawStats() {
  rcs_GC gc;
  rcs_Font font;
  gc = rcs_openGC(display,mainScreen);
  font = rcs_openFont(display,VIDEOKENO_FONT);
  rcs_setFont(display,gc,font);
  rcs_namedForeground(display,gc,"white");
  rcs_copyArea(display,table,mainScreen,gc,266,463,524,45,266,463);
  sprintf(buffer,"Credits: $%.2lf     ",credits);
  rcs_drawString(display,mainScreen,gc,500,500,buffer);
  sprintf(buffer,"Bet: %d",bet);
  rcs_drawString(display,mainScreen,gc,270,500,buffer);
  sprintf(buffer,"Session Vip: %ld",long(sessionVip));
//  rawPrint(20,24,buffer);
  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  }

void VideoKeno::setDenomination(double d) {
  creditSize = d;
/*
  double mon;
  mon=(double)(credits * creditSize);
  mon /= creditSize;
  credits = long(mon);
*/
  }

double VideoKeno::getMoney() { return player->getMoney(); }
long   VideoKeno::getVip() { return player->getVip(); }

void VideoKeno::insertMoney(int m) {
  credits += m;
  player->subMoney(m);
  }

void VideoKeno::cashOut() {
  player->addMoney( credits );
  credits = 0;
  }

void VideoKeno::shuffle() {
  int p1,p2;
  int i;
  int t;
  p1 = 0;
  for (i=0; i<160; i++) {
    p2 = Random(80);
    t = balls[p1];
    balls[p1] = balls[p2];
    balls[p2] = t;
    if (++p1 == 80) p1 = 0;
    }
  }

void VideoKeno::spotClicked(int n) {
  char buffer[5];
  rcs_GC gc;
  rcs_Font font;
  int x,y;
  int j;
  n--;
  gc=rcs_openGC(display,mainScreen);
  font=rcs_openFont(display,VIDEOKENO_FONT);
  rcs_setFont(display,gc,font);
  x=268 + (n % 10) * 52;
  y=67 + ((n > 39) ? 19 : 0) + (n / 10) * 47;
  switch(game) {
        case GAME_246:
        case GAME_369:
        case GAME_SUPERWAY:
          if (playerSpots[n] != ' ') {
            switch (playerSpots[n]) {
              case 'A': spotsA--; break;
              case 'B': spotsB--; break;
              case 'C': spotsC--; break;
              }
            playerSpots[n] = ' ';
            rcs_drawPixmap(display,mainScreen,gc,x,y,kenoblue_xpm);
            sprintf(buffer," %2d ",n+1);
            rcs_namedForeground(display,gc,"yellow");
            rcs_drawString(display,mainScreen,gc,x+2,29+y,buffer);
            spots--;
            drawBoard();
            drawPayouts();
            showChoices();
            drawButtons();
            } else if (spots < max) {
            if (spotsA < grA) { playerSpots[n] = 'A'; spotsA++; }
            else if (spotsB < grB) { playerSpots[n] = 'B'; spotsB++; }
            else { playerSpots[n] = 'C'; spotsC++; }
            showChoices();
            spots++;
            drawPayouts();
            drawButtons();
            }
          break;
        case GAME_TOPBOT:
          drawBoard();
          for (j=0;j<80;j++) playerSpots[j]=' ';
          if (n < 40) {
            for (j=0; j<40; j++) playerSpots[j]='*';
            } else {
            for (j=40; j<80; j++) playerSpots[j]='*';
            }
          showChoices();
          drawButtons();
          break;
    default:
            if (playerSpots[n] != ' ') {
              playerSpots[n] = ' ';
              rcs_drawPixmap(display,mainScreen,gc,x,y,kenoblue_xpm);
              sprintf(buffer," %2d ",n+1);
              rcs_namedForeground(display,gc,"yellow");
              rcs_drawString(display,mainScreen,gc,x+2,29+y,buffer);
              spots--;
              } else if (spots < max) {
              playerSpots[n] = '*';
              rcs_drawPixmap(display,mainScreen,gc,x,y,kenobluecheck_xpm);
              spots++;
              }
    }
/*
    if (key == 32) {
      i = cursorY*10 + cursorX;
      switch (game) {
        default:
        }
      }
*/
  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  drawPayouts();
  }


void VideoKeno::showChoices() {
  int i;
  int x,y;
  rcs_GC gc;
  drawBoard();
  gc = rcs_openGC(display,mainScreen);
  for (i=0; i<80; i++)
    if (playerSpots[i] != ' ') {
      x=268 + (i % 10) * 52;
      y=67 + ((i > 39) ? 19 : 0) + (i / 10) * 47;
      switch (playerSpots[i]) {
        case 'A': rcs_drawPixmap(display,mainScreen,gc,x,y,kenobluea_xpm);
                  break;
        case 'B': rcs_drawPixmap(display,mainScreen,gc,x,y,kenoblueb_xpm);
                  break;
        case 'C': rcs_drawPixmap(display,mainScreen,gc,x,y,kenobluec_xpm);
                  break;
        default : rcs_drawPixmap(display,mainScreen,gc,x,y,kenobluecheck_xpm);
        }
      }
  rcs_closeGC(display,gc);
  }

void VideoKeno::markSpot(int num) {
  int x, y;
  rcs_GC gc;
  rcs_Font font;
  gc = rcs_openGC(display,mainScreen);
  font=rcs_openFont(display,VIDEOKENO_FONT);
  rcs_setFont(display,gc,font);
  x=268 + (num % 10) * 52;
  y=67 + ((num > 39) ? 19 : 0) + (num / 10) * 47;
  switch (playerSpots[num]) {
    case 'A': rcs_drawPixmap(display,mainScreen,gc,x,y,kenoreda_xpm);
              break;
    case 'B': rcs_drawPixmap(display,mainScreen,gc,x,y,kenoredb_xpm);
              break;
    case 'C': rcs_drawPixmap(display,mainScreen,gc,x,y,kenoredc_xpm);
              break;
    case 'd': rcs_drawPixmap(display,mainScreen,gc,x,y,kenodiamond_xpm);
              break;
    case 'o': rcs_drawPixmap(display,mainScreen,gc,x,y,kenoreddollar_xpm);
              break;
    case '*': if (drawn == 1 && game == GAME_SUPER) 
                rcs_drawPixmap(display,mainScreen,gc,x,y,kenolightning_xpm);
                else rcs_drawPixmap(display,mainScreen,gc,x,y,kenoredcheck_xpm);
              break;
    default : rcs_drawPixmap(display,mainScreen,gc,x,y,kenored_xpm);
              sprintf(buffer," %2d ",num+1);
              rcs_namedForeground(display,gc,"yellow");
              rcs_drawString(display,mainScreen,gc,x+2,29+y,buffer);
    }
  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  displayScreen();
  }

