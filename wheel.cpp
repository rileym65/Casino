#include <stdlib.h>
#include "header.h"
#include "wheel.h"

#ifdef GRAPHIC
#include "images/money.xpm"
#endif

#define BET_1     0
#define BET_2     1
#define BET_5     2
#define BET_10    3
#define BET_20    4
#define BET_JOKER 5
#define BET_FLAG  6

MoneyWheel::MoneyWheel(Player* p)
{
  player=p;
  betAmount=1;
}

void MoneyWheel::showPlayer() {
#ifdef GRAPHIC
  rcs_GC gc;
  rcs_Font font;
    gc=rcs_openGC(display,mainScreen);
    font=rcs_openFont(display,BET_FONT);
    rcs_setFont(display,gc,font);
    rcs_namedForeground(display,gc,"yellow");
    rcs_copyArea(display,table,mainScreen,gc,250,530,300,26,250,530);
    rcs_drawString(display,mainScreen,gc,250,550,player->getName());
    sprintf(buffer,"%8.0f",player->money());
    rcs_drawString(display,mainScreen,gc,350,550,buffer);
    rcs_closeFont(display,font);
    rcs_closeGC(display,gc);
    displayScreen();
#endif
  }

void MoneyWheel::showBetAmount() {
  rcs_GC gc;
  rcs_Font font;
  char     buffer[80];
  gc=rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"darkgreen");
  rcs_drawFilledBox(display,mainScreen,gc,377,565,99,32);
  rcs_namedForeground(display,gc,"yellow");
  font=rcs_openFont(display,BET_FONT);
  rcs_setFont(display,gc,font);
  sprintf(buffer,"$%ld",betAmount);
  rcs_drawString(display,mainScreen,gc,385,586,buffer);
  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  displayScreen();
  }

float MoneyWheel::placeBet() {
//  float betReturn;
  char  flag;
  long  tBet;
#ifdef GRAPHIC
  rcs_Event event;
  rcs_GC    gc;
  rcs_Font  font;
  tBet=0;
  gc=rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"gray");
  rcs_drawFilledBox(display,mainScreen,gc,10,566,80,29);
  rcs_namedForeground(display,gc,"black");
  rcs_drawBox(display,mainScreen,gc,12,568,76,25);
  font=rcs_openFont(display,BET_FONT);
  rcs_setFont(display,gc,font);
  rcs_drawString(display,mainScreen,gc,32,587,"Exit");
  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  displayScreen();
  flag=' ';
  while (flag==' ') {
    event=getEvent(display);
    switch(event.type) {
      case EVENT_BUTTON_PRESS:
           if (event.d1 == 1 && event.d2>=184 && event.d2<=320 &&
               tBet>0 &&        event.d3>=566 && event.d3<=599) {
             flag='P';
             }
           if (event.d1 == 1 && event.d3>=566 && event.d3<=598) {
             if (event.d1 == 1 && event.d2>=10 && event.d2<=90) {
               flag='X';
               }
             if (event.d2>=490 && event.d2<516) {
               betAmount+=1; showBetAmount();
               }
             if (event.d2>=522 && event.d2<546) {
               betAmount+=5; showBetAmount();
               }
             if (event.d2>=553 && event.d2<578) {
               betAmount+=10; showBetAmount();
               }
             if (event.d2>=584 && event.d2<609) {
               betAmount+=25; showBetAmount();
               }
             if (event.d2>=615 && event.d2<640) {
               betAmount+=50; showBetAmount();
               }
             if (event.d2>=645 && event.d2<671) {
               betAmount+=100; showBetAmount();
               }
             if (event.d2>=676 && event.d2<701) {
               betAmount+=500; showBetAmount();
               }
             if (event.d2>=708 && event.d2<733) {
               betAmount+=1000; showBetAmount();
               }
             if (event.d2>=739 && event.d2<765) {
               betAmount+=5000; showBetAmount();
               }
             if (event.d2>=771 && event.d2<796) {
               betAmount+=10000; showBetAmount();
               }
             }
           if (event.d1 == 3 && event.d3>=566 && event.d3<=598) {
             if (event.d2>=490 && event.d2<516) {
               betAmount-=1;
               if (betAmount<1) betAmount=1;
               showBetAmount();
               }
             if (event.d2>=522 && event.d2<546) {
               betAmount-=5;
               if (betAmount<1) betAmount=1;
               showBetAmount();
               }
             if (event.d2>=553 && event.d2<578) {
               betAmount-=10;
               if (betAmount<1) betAmount=1;
               showBetAmount();
               }
             if (event.d2>=584 && event.d2<609) {
               betAmount-=25;
               if (betAmount<1) betAmount=1;
               showBetAmount();
               }
             if (event.d2>=615 && event.d2<640) {
               betAmount-=50;
               if (betAmount<1) betAmount=1;
               showBetAmount();
               }
             if (event.d2>=645 && event.d2<671) {
               betAmount-=100;
               if (betAmount<1) betAmount=1;
               showBetAmount();
               }
             if (event.d2>=676 && event.d2<701) {
               betAmount-=500;
               if (betAmount<1) betAmount=1;
               showBetAmount();
               }
             if (event.d2>=708 && event.d2<733) {
               betAmount-=1000;
               if (betAmount<1) betAmount=1;
               showBetAmount();
               }
             if (event.d2>=739 && event.d2<765) {
               betAmount-=5000;
               if (betAmount<1) betAmount=1;
               showBetAmount();
               }
             if (event.d2>=771 && event.d2<796) {
               betAmount-=10000;
               if (betAmount<1) betAmount=1;
               showBetAmount();
               }
             }
           if (
               (event.d1 == 1 && event.d2>=27 && event.d2<=257 &&
                event.d3>=429 && event.d3<=525) ||
               (event.d1 == 1 && event.d2>=281 && event.d2<=511 &&
                event.d3>=429 && event.d3<=525) ||
               (event.d1 == 1 && event.d2>=541 && event.d2<=770 &&
                event.d3>=429 && event.d3<=525) ||
               (event.d1 == 1 && event.d2>=29 && event.d2<=139 &&
                event.d3>=310 && event.d3<=409) ||
               (event.d1 == 1 && event.d2>=155 && event.d2<=384 &&
                event.d3>=310 && event.d3<=409) ||
               (event.d1 == 1 && event.d2>=412 && event.d2<=642 &&
                event.d3>=310 && event.d3<=409) ||
               (event.d1 == 1 && event.d2>=661 && event.d2<=772 &&
                event.d3>=310 && event.d3<=409)
                                               ) {
             player->placeBet(betAmount,0,event.d2,event.d3);
             tBet+=betAmount;
             player->paintBets();
             showPlayer();
             }
           break;
      }
    }
  gc=rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"darkgreen");
  rcs_drawFilledBox(display,mainScreen,gc,10,566,80,29);
  rcs_closeGC(display,gc);
  displayScreen();
#endif
#ifdef CONSOLE
  flag=' ';
  while (flag == ' ') {
    GotoXY(1,19);
    sprintf(buffer,"Money $%12.2f",player->money());
    Output(buffer);
    GotoXY(1,20);
    Output("(1)$1, (2)$2, (5)$5, (0)$10, (t)$20, (j)oker, (f)lag, (s)pin, (Q)uit ");
    Input(buffer);
    GotoXY(69,20); Output("       ");
    if (buffer[0]=='q' || buffer[0]=='Q') flag='X';
    else if (buffer[0]=='s' || buffer[0]=='S') flag='P';
    else if ( buffer[0]=='1' || buffer[0]=='2' ||
              buffer[0]=='5' || buffer[0]=='0' ||
              buffer[0]=='t' || buffer[0]=='T' ||
              buffer[0]=='j' || buffer[0]=='J' ||
              buffer[0]=='f' || buffer[0]=='F') {
      BetType=buffer[0];
      GotoXY(1,21); Output("Bet ? ");
      Input(buffer);
      GotoXY(1,21); Output("               ");
      Bet=atoi(buffer);
      if (Bet!=0) {
        switch (BetType) {
          case '1':FBet=player->placeBet(Bet,BET_1,1,1); break;
          case '2':FBet=player->placeBet(Bet,BET_2,1,1); break;
          case '5':FBet=player->placeBet(Bet,BET_5,1,1); break;
          case '0':FBet=player->placeBet(Bet,BET_10,1,1); break;
          case 'T':
          case 't':FBet=player->placeBet(Bet,BET_20,1,1); break;
          case 'F':
          case 'f':FBet=player->placeBet(Bet,BET_FLAG,1,1); break;
          case 'J':
          case 'j':FBet=player->placeBet(Bet,BET_JOKER,1,1); break;
          }
        if (FBet==0) { }
        showBets();
        }
      }
    }

#endif
  if (flag!='P' && flag!='D') return 0;
    else return 1;
  }

int MoneyWheel::spinWheel() {
#ifdef GRAPHIC
  rcs_GC gc;
#endif
  wheelPos=Random(54);
  GotoXY(20,15);
  if (wheelPos==1) {
#ifdef GRAPHIC
  gc=rcs_openGC(display,mainScreen);
  rcs_copyArea(display,table,mainScreen,gc,38,323,90,60,300,200);
  rcs_closeGC(display,gc);
#endif
#ifdef CONSOLE
    Output("flag ");
#endif
    return 7; }
  if (wheelPos==2) {
#ifdef GRAPHIC
  gc=rcs_openGC(display,mainScreen);
  rcs_copyArea(display,table,mainScreen,gc,671,323,90,60,300,200);
  rcs_closeGC(display,gc);
#endif
#ifdef CONSOLE
    Output("Joker");
#endif
    return 6; }
  if (wheelPos<5)  {
#ifdef GRAPHIC
  gc=rcs_openGC(display,mainScreen);
  rcs_copyArea(display,table,mainScreen,gc,412,310,230,96,280,200);
  rcs_closeGC(display,gc);
#endif
#ifdef CONSOLE
    Output("$20  ");
#endif
    return 5; }
  if (wheelPos<9)  {
#ifdef GRAPHIC
  gc=rcs_openGC(display,mainScreen);
  rcs_copyArea(display,table,mainScreen,gc,155,310,230,96,280,200);
  rcs_closeGC(display,gc);
#endif
#ifdef CONSOLE
    Output("$10  ");
#endif
    return 4; }
  if (wheelPos<17) {
#ifdef GRAPHIC
  gc=rcs_openGC(display,mainScreen);
  rcs_copyArea(display,table,mainScreen,gc,541,429,230,96,280,200);
  rcs_closeGC(display,gc);
#endif
#ifdef CONSOLE
    Output("$5   ");
#endif
    return 3; }
  if (wheelPos<32) {
#ifdef GRAPHIC
  gc=rcs_openGC(display,mainScreen);
  rcs_copyArea(display,table,mainScreen,gc,281,429,230,96,280,200);
  rcs_closeGC(display,gc);
#endif
#ifdef CONSOLE
    Output("$2   ");
#endif
    return 2; }
#ifdef GRAPHIC
  gc=rcs_openGC(display,mainScreen);
  rcs_copyArea(display,table,mainScreen,gc,27,429,230,96,280,200);
  rcs_closeGC(display,gc);
#endif
#ifdef CONSOLE
  Output("$1   ");
#endif
  return 1;
  }

void MoneyWheel::drawBoard()
{
#ifdef GRAPHIC
  rcs_GC gc;
  gc=rcs_openGC(display,mainScreen);
  rcs_copyArea(display,table,mainScreen,gc,0,0,800,600,0,0);
  rcs_closeGC(display,gc);
  showBetAmount();
#endif
#ifdef CONSOLE
  ClrScr();
  GotoXY(1,1);
  Output("       +----------+  +----------+\n");
  Output("       |  JOKER   |  |   FLAG   |\n");
  Output("       |          |  |          |\n");
  Output("       +----------+  +----------+\n");
  Output("       +----------+  +----------+\n");
  Output("       |    $10   |  |    $20   |\n");
  Output("       |          |  |          |\n");
  Output("       +----------+  +----------+\n");
  Output("+----------+  +----------+  +----------+\n");
  Output("|    $1    |  |    $2    |  |    $5    |\n");
  Output("|          |  |          |  |          |\n");
  Output("+----------+  +----------+  +----------+\n");
#endif
  showBets();
}

void MoneyWheel::showBets()
{
#ifdef GRAPHIC
  player->paintBets();
  displayScreen();
#endif
#ifdef CONSOLE
  if (player->getHandBet(BET_1)>0) {
    GotoXY(7,11); Output("*");
    } else { GotoXY(7,11); Output(" "); }
  if (player->getHandBet(BET_2)>0) {
    GotoXY(21,11); Output("*");
    } else { GotoXY(21,11); Output(" "); }
  if (player->getHandBet(BET_5)>0) {
    GotoXY(35,11); Output("*");
    } else { GotoXY(35,11); Output(" "); }
  if (player->getHandBet(BET_10)>0) {
    GotoXY(15,7); Output("*");
    } else { GotoXY(15,7); Output(" "); }
  if (player->getHandBet(BET_20)>0) {
    GotoXY(29,7); Output("*");
    } else { GotoXY(29,7); Output(" "); }
  if (player->getHandBet(BET_JOKER)>0) {
    GotoXY(15,3); Output("*");
    } else { GotoXY(15,3); Output(" "); }
  if (player->getHandBet(BET_FLAG)>0) {
    GotoXY(29,3); Output("*");
    } else { GotoXY(29,3); Output(" "); }
#endif
}


void MoneyWheel::play()
{
  int  i;
  float FBet;
  float won;
  float lost;
  char flag;
#ifdef GRAPHIC
  rcs_GC gc;
  table=rcs_xpmToPixmap(display,mainWindow,money_xpm);
#endif
  flag=' ';
  while (flag==' ') {
    player->clearAllBets();
    drawBoard();
    showPlayer();
    FBet=placeBet();
    if (FBet>0) {
      i=spinWheel();
      won=0; lost=0;
      switch (i) {
        case 1:won+=player->getHandBet(BET_1);
#ifdef GRAPHIC
               player->winXYBets(27,429,257,525,1);
               player->clearNonWinners();
#endif
#ifdef CONSOLE
               player->winHandBets(BET_1,1);
               player->loseHandBets(BET_2);
               player->loseHandBets(BET_5);
               player->loseHandBets(BET_10);
               player->loseHandBets(BET_20);
               player->loseHandBets(BET_JOKER);
               player->loseHandBets(BET_FLAG);
#endif
               break;
        case 2:won+=player->getHandBet(BET_2)*2;
#ifdef GRAPHIC
               player->winXYBets(281,429,511,525,2);
               player->clearNonWinners();
#endif
#ifdef CONSOLE
               player->winHandBets(BET_2,2);
               player->loseHandBets(BET_1);
               player->loseHandBets(BET_5);
               player->loseHandBets(BET_10);
               player->loseHandBets(BET_20);
               player->loseHandBets(BET_JOKER);
               player->loseHandBets(BET_FLAG);
#endif
               break;
        case 3:won+=player->getHandBet(BET_5)*5;
#ifdef GRAPHIC
               player->winXYBets(541,429,770,525,5);
               player->clearNonWinners();
#endif
#ifdef CONSOLE
               player->winHandBets(BET_5,5);
               player->loseHandBets(BET_2);
               player->loseHandBets(BET_1);
               player->loseHandBets(BET_10);
               player->loseHandBets(BET_20);
               player->loseHandBets(BET_JOKER);
               player->loseHandBets(BET_FLAG);
#endif
               break;
        case 4:won+=player->getHandBet(BET_10)*10;
#ifdef GRAPHIC
               player->winXYBets(155,310,384,409,10);
               player->clearNonWinners();
#endif
#ifdef CONSOLE
               player->winHandBets(BET_10,10);
               player->loseHandBets(BET_2);
               player->loseHandBets(BET_5);
               player->loseHandBets(BET_1);
               player->loseHandBets(BET_20);
               player->loseHandBets(BET_JOKER);
               player->loseHandBets(BET_FLAG);
#endif
               break;
        case 5:won+=player->getHandBet(BET_20)*20;
#ifdef GRAPHIC
               player->winXYBets(412,310,642,409,20);
               player->clearNonWinners();
#endif
#ifdef CONSOLE
               player->winHandBets(BET_20,20);
               player->loseHandBets(BET_2);
               player->loseHandBets(BET_5);
               player->loseHandBets(BET_10);
               player->loseHandBets(BET_1);
               player->loseHandBets(BET_JOKER);
               player->loseHandBets(BET_FLAG);
#endif
               break;
        case 6:won+=player->getHandBet(BET_JOKER)*40;
#ifdef GRAPHIC
               player->winXYBets(661,310,772,409,40);
               player->clearNonWinners();
#endif
#ifdef CONSOLE
               player->winHandBets(BET_JOKER,40);
               player->loseHandBets(BET_2);
               player->loseHandBets(BET_5);
               player->loseHandBets(BET_10);
               player->loseHandBets(BET_20);
               player->loseHandBets(BET_1);
               player->loseHandBets(BET_FLAG);
#endif
               break;
        case 7:won+=player->getHandBet(BET_FLAG)*40;
#ifdef GRAPHIC
               player->winXYBets(29,310,139,409,40);
               player->clearNonWinners();
#endif
#ifdef CONSOLE
               player->winHandBets(BET_FLAG,40);
               player->loseHandBets(BET_2);
               player->loseHandBets(BET_5);
               player->loseHandBets(BET_10);
               player->loseHandBets(BET_20);
               player->loseHandBets(BET_JOKER);
               player->loseHandBets(BET_1);
#endif
               break;
        }
      lost=player->getHandBet(BET_1)+
           player->getHandBet(BET_2)+
           player->getHandBet(BET_5)+
           player->getHandBet(BET_10)+
           player->getHandBet(BET_20)+
           player->getHandBet(BET_JOKER)+
           player->getHandBet(BET_FLAG);

      won-=lost;
#ifdef CONSOLE
      if (won>=0)
        sprintf(buffer,"WON $%12.2f",won);
       else
        sprintf(buffer,"Lost $%12.2f",-won);
      GotoXY(1,17); Output(buffer);
#endif
#ifdef GRAPHIC
      gc=rcs_openGC(display,mainScreen);
      rcs_copyArea(display,table,mainScreen,gc,6,294,788,236,6,294);
      rcs_closeGC(display,gc);
#endif
      showBets();
      showPlayer();
      Delay(5);
#ifdef CONSOLE
      GotoXY(1,17); Output("                    ");
#endif
      } else flag='X';
    }
#ifdef GRAPHIC
  rcs_closePixmap(display,table);
#endif
}
