#include <stdlib.h>
#include "header.h"
#include "chuck.h"

#ifdef GRAPHIC
#include "images/chuck.xpm"
#endif

#define BET_1     0
#define BET_2     1
#define BET_3     2
#define BET_4     3
#define BET_5     4
#define BET_6     5
#define BET_OVER  6
#define BET_UNDER 7
#define BET_FIELD 8

Chuck::Chuck(Player* p) {
  player=p;
  d1=new Die(6);
  d1->setPosition(50,460);
  d1->setSize(60);
  d2=new Die(6);
  d2->setPosition(120,460);
  d2->setSize(60);
  d3=new Die(6);
  d3->setPosition(190,460);
  d3->setSize(60);
  betAmount=1;
  }

Chuck::~Chuck() {
  delete(d1);
  delete(d2);
  delete(d3);
  }

void Chuck::showBetAmount() {
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

float Chuck::placeBet() {
//  float betReturn;
  char  flag;
#ifdef GRAPHIC
  rcs_Event event;
  rcs_GC    gc;
  rcs_Font  font;
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
           if (event.d1 == 1 && event.d2>=328 && event.d2<=468 &&
                                event.d3>=469 && event.d3<=526) {
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
               (event.d1 == 1 && event.d2>=64 && event.d2<=140 &&
                event.d3>=144 && event.d3<=279) ||
               (event.d1 == 1 && event.d2>=148 && event.d2<=224 &&
                event.d3>=144 && event.d3<=279) ||
               (event.d1 == 1 && event.d2>=232 && event.d2<=308 &&
                event.d3>=144 && event.d3<=279) ||
               (event.d1 == 1 && event.d2>=316 && event.d2<=391 &&
                event.d3>=144 && event.d3<=279) ||
               (event.d1 == 1 && event.d2>=400 && event.d2<=475 &&
                event.d3>=144 && event.d3<=279) ||
               (event.d1 == 1 && event.d2>=484 && event.d2<=560 &&
                event.d3>=144 && event.d3<=279) ||
               (event.d1 == 1 && event.d2>=568 && event.d2<=644 &&
                event.d3>=144 && event.d3<=279) ||
               (event.d1 == 1 && event.d2>=652 && event.d2<=727 &&
                event.d3>=144 && event.d3<=279) ||
               (event.d1 == 1 && event.d2>=64 && event.d2<=140 &&
                event.d3>=288 && event.d3<=424) ||
               (event.d1 == 1 && event.d2>=148 && event.d2<=644 &&
                event.d3>=288 && event.d3<=424) ||
               (event.d1 == 1 && event.d2>=652 && event.d2<=727 &&
                event.d3>=288 && event.d3<=424)
                                               ) {
             player->placeBet(betAmount,0,event.d2,event.d3);
             player->paintBets();
             showPlayer();
             displayScreen();
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
    GotoXY(1,20);
    Output("Bet (1) (2) (3) (4) (5) (6) (O)ver (U)nder, (F)ield, (R)oll, (Q)uit ");
    Input(buffer);
    GotoXY(69,20); Output("       ");
    if (buffer[0]=='q' || buffer[0]=='Q') flag='X';
    else if (buffer[0]=='r' || buffer[0]=='R') flag='P';
    else if ((buffer[0]>'0' && buffer[0]<'7') ||
              buffer[0]=='o' || buffer[0]=='O' ||
              buffer[0]=='u' || buffer[0]=='U' ||
              buffer[0]=='f' || buffer[0]=='F') {
      betType=buffer[0];
      GotoXY(1,21); Output("Bet ? ");
      Input(buffer);
      GotoXY(1,21); Output("               ");
      bet=atoi(buffer);
      if (bet!=0) {
        switch (betType) {
          case '1':fBet=player->placeBet(bet,BET_1,1,1); break;
          case '2':fBet=player->placeBet(bet,BET_2,1,1); break;
          case '3':fBet=player->placeBet(bet,BET_3,1,1); break;
          case '4':fBet=player->placeBet(bet,BET_4,1,1); break;
          case '5':fBet=player->placeBet(bet,BET_5,1,1); break;
          case '6':fBet=player->placeBet(bet,BET_6,1,1); break;
          case 'O':
          case 'o':fBet=player->placeBet(bet,BET_OVER,1,1); break;
          case 'U':
          case 'u':fBet=player->placeBet(bet,BET_UNDER,1,1); break;
          case 'F':
          case 'f':fBet=player->placeBet(bet,BET_FIELD,1,1); break;
          }
        if (fBet==0) { }
        showBets();
        }
      }
    }

#endif
  if (flag!='P' && flag!='D') return 0;
    else return 1;
  }


void Chuck::showDice() {
#ifdef GRAPHIC
  rcs_GC gc;
  gc=rcs_openGC(display,mainScreen);
  d1->paint(display,mainScreen,gc);
  d2->paint(display,mainScreen,gc);
  d3->paint(display,mainScreen,gc);
  rcs_closeGC(display,gc);
  displayScreen();
#endif
#ifdef CONSOLE
  int die1,die2,die3;
  die1=d1->getNumber();
  die2=d2->getNumber();
  die3=d3->getNumber();
    GotoXY(50,3); Output(" ");
    GotoXY(48,2); Output(" ");
    GotoXY(52,4); Output(" ");
    GotoXY(48,4); Output(" ");
    GotoXY(52,2); Output(" ");
    GotoXY(48,3); Output(" ");
    GotoXY(52,3); Output(" ");
    GotoXY(50,8); Output(" ");
    GotoXY(48,7); Output(" ");
    GotoXY(52,9); Output(" ");
    GotoXY(48,9); Output(" ");
    GotoXY(52,7); Output(" ");
    GotoXY(48,8); Output(" ");
    GotoXY(52,8); Output(" ");
    GotoXY(50,13); Output(" ");
    GotoXY(48,12); Output(" ");
    GotoXY(52,14); Output(" ");
    GotoXY(48,14); Output(" ");
    GotoXY(52,12); Output(" ");
    GotoXY(48,13); Output(" ");
    GotoXY(52,13); Output(" ");
  if (die1==1 || die1==3 || die1==5) {
    GotoXY(50,3); Output("*");
    }
  if (die1!=1) {
    GotoXY(48,2); Output("*");
    GotoXY(52,4); Output("*");
    }
  if (die1>3) {
    GotoXY(48,4); Output("*");
    GotoXY(52,2); Output("*");
    }
  if (die1==6) {
    GotoXY(48,3); Output("*");
    GotoXY(52,3); Output("*");
    }
  if (die2==1 || die2==3 || die2==5) {
    GotoXY(50,8); Output("*");
    }
  if (die2!=1) {
    GotoXY(48,7); Output("*");
    GotoXY(52,9); Output("*");
    }
  if (die2>3) {
    GotoXY(48,9); Output("*");
    GotoXY(52,7); Output("*");
    }
  if (die2==6) {
    GotoXY(48,8); Output("*");
    GotoXY(52,8); Output("*");
    }
  if (die3==1 || die3==3 || die3==5) {
    GotoXY(50,13); Output("*");
    }
  if (die3!=1) {
    GotoXY(48,12); Output("*");
    GotoXY(52,14); Output("*");
    }
  if (die3>3) {
    GotoXY(48,14); Output("*");
    GotoXY(52,12); Output("*");
    }
  if (die3==6) {
    GotoXY(48,13); Output("*");
    GotoXY(52,13); Output("*");
    }
#endif
  }

void Chuck::rollDice() {
  d1->roll();
  d2->roll();
  d3->roll();
  showDice();
  }

void Chuck::drawBoard()
{
#ifdef GRAPHIC
  rcs_GC gc;
  gc=rcs_openGC(display,mainScreen);
  rcs_copyArea(display,table,mainScreen,gc,0,0,800,600,0,0);
  rcs_closeGC(display,gc);
  showBetAmount();
  displayScreen();
#endif
#ifdef CONSOLE
  ClrScr();
  GotoXY(1,1);
  Output("                                             +-------+\n");
  Output("                                             |       |\n");
  Output("                                             |       |\n");
  Output("+--------+---+---+---+---+---+---+--------+  |       |\n");
  Output("|  OVER  | 1 | 2 | 3 | 4 | 5 | 6 |  OVER  |  +-------+\n");
  Output("|   10   |   |   |   |   |   |   |   10   |  +-------+\n");
  Output("|        |   |   |   |   |   |   |        |  |       |\n");
  Output("+--------+---+---+---+---+---+---+--------+  |       |\n");
  Output("|  UNDER |         FIELD         |  UNDER |  |       |\n");
  Output("|   11   |  5 6 7 8 13 14 15 16  |   11   |  +-------+\n");
  Output("|        |                       |        |  +-------+\n");
  Output("+--------+-----------------------+--------+  |       |\n");
  Output("                                             |       |\n");
  Output("                                             |       |\n");
  Output("                                             +-------+\n");
#endif
  showBets();
  showDice();
}

void Chuck::showBets()
{
#ifdef GRAPHIC
  rcs_GC gc;
  gc=rcs_openGC(display,mainScreen);
  rcs_copyArea(display,table,mainScreen,gc,41,118,707,327,41,118);
  rcs_closeGC(display,gc);
  player->paintBets();
  displayScreen();
#endif
#ifdef CONSOLE
  if (player->getHandBet(BET_OVER)>0) {
    GotoXY(6,7); Output("*");
    } else { GotoXY(6,7); Output(" "); }
  if (player->getHandBet(BET_UNDER)>0) {
    GotoXY(6,11); Output("*");
    } else { GotoXY(6,11); Output(" "); }
  if (player->getHandBet(BET_FIELD)>0) {
    GotoXY(22,11); Output("*");
    } else { GotoXY(22,11); Output(" "); }
  if (player->getHandBet(BET_1)>0) {
    GotoXY(12,7); Output("*");
    } else { GotoXY(12,7); Output(" "); }
  if (player->getHandBet(BET_2)>0) {
    GotoXY(16,7); Output("*");
    } else { GotoXY(16,7); Output(" "); }
  if (player->getHandBet(BET_3)>0) {
    GotoXY(20,7); Output("*");
    } else { GotoXY(20,7); Output(" "); }
  if (player->getHandBet(BET_4)>0) {
    GotoXY(24,7); Output("*");
    } else { GotoXY(24,7); Output(" "); }
  if (player->getHandBet(BET_5)>0) {
    GotoXY(28,7); Output("*");
    } else { GotoXY(28,7); Output(" "); }
  if (player->getHandBet(BET_6)>0) {
    GotoXY(32,7); Output("*");
    } else { GotoXY(32,7); Output(" "); }
#endif
}


void Chuck::showPlayer() {
#ifdef GRAPHIC
  rcs_GC gc;
  rcs_Font font;
#endif
    sprintf(buffer,"Money $%12.2f",player->money());
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    font=rcs_openFont(display,BET_FONT);
    rcs_setFont(display,gc,font);
    rcs_namedForeground(display,gc,"darkgreen");
    rcs_drawFilledBox(display,mainScreen,gc,540,480,200,30);
    rcs_namedForeground(display,gc,"yellow");
    rcs_drawString(display,mainScreen,gc,550,500,buffer);
    rcs_closeFont(display,font);
    rcs_closeGC(display,gc);
    displayScreen();
#endif
#ifdef CONSOLE
    GotoXY(1,19);
    Output(buffer);
#endif
    }

void Chuck::play()
{
  float  bet;
  float won;
  float lost;
  char flag;
  int  total;
#ifdef GRAPHIC
  table=rcs_xpmToPixmap(display,mainWindow,chuck_xpm);
#endif
  drawBoard();
  flag=' ';
  player->clearAllBets();
  while (flag==' ') {
    drawBoard();
    showPlayer();
    bet=placeBet();
    if (bet != 0) {
      rollDice();
      total=d1->getNumber()+d2->getNumber()+d3->getNumber();
      won=0; lost=0;
      if (total>10) {
        won+=player->getHandBet(BET_OVER);
        lost+=player->getHandBet(BET_UNDER);
#ifdef GRAPHIC
        player->winXYBets(64,144,140,279,1);
        player->winXYBets(652,144,727,279,1);
        player->loseXYBets(64,288,140,424);
        player->loseXYBets(652,288,727,424);
#endif
#ifdef CONSOLE
        player->winHandBets(BET_OVER,1);
        player->loseHandBets(BET_UNDER);
#endif
        } else {
        won+=player->getHandBet(BET_UNDER);
        lost+=player->getHandBet(BET_OVER);
#ifdef GRAPHIC
        player->loseXYBets(64,144,140,279);
        player->loseXYBets(652,144,727,279);
        player->winXYBets(64,288,140,424,1);
        player->winXYBets(652,288,727,424,1);
#endif
#ifdef CONSOLE
        player->winHandBets(BET_UNDER,1);
        player->loseHandBets(BET_OVER);
#endif
        }
      if ((total>4 && total<9) || (total>12 && total<17)) {
        won+=player->getHandBet(BET_FIELD);
#ifdef GRAPHIC
        player->winXYBets(148,288,644,424,1);
#endif
#ifdef CONSOLE
        player->winHandBets(BET_FIELD,2);
#endif
        }
       else {
        lost+=player->getHandBet(BET_FIELD);
#ifdef GRAPHIC
        player->loseXYBets(148,288,644,424);
#endif
#ifdef CONSOLE
        player->loseHandBets(BET_FIELD);
#endif
        }
      total=abs((d1->getNumber()==1)+(d2->getNumber()==1)+(d3->getNumber()==1));
      switch (total) {
        case 0:lost+=player->getHandBet(BET_1);
#ifdef GRAPHIC
               player->loseXYBets(148,144,224,279); break;
#endif
#ifdef CONSOLE
               player->loseHandBets(BET_1); break;
#endif
        case 1:won+=player->getHandBet(BET_1);
#ifdef GRAPHIC
               player->winXYBets(148,144,224,279,1); break;
#endif
#ifdef CONSOLE
               player->winHandBets(BET_1,1); break;
#endif
        case 2:won+=player->getHandBet(BET_1)*2;
#ifdef GRAPHIC
               player->winXYBets(148,144,224,279,2); break;
#endif
#ifdef CONSOLE
               player->winHandBets(BET_1,2); break;
#endif
        case 3:won+=player->getHandBet(BET_1)*10;
#ifdef GRAPHIC
               player->winXYBets(148,144,224,279,10); break;
#endif
#ifdef CONSOLE
               player->winHandBets(BET_1,10); break;
#endif
        }
      total=abs((d1->getNumber()==2)+(d2->getNumber()==2)+(d3->getNumber()==2));
      switch (total) {
        case 0:lost+=player->getHandBet(BET_2);
#ifdef GRAPHIC
               player->loseXYBets(232,144,308,279); break;
#endif
#ifdef CONSOLE
               player->loseHandBets(BET_2); break;
#endif
        case 1:won+=player->getHandBet(BET_2);
#ifdef GRAPHIC
               player->winXYBets(232,144,308,279,1); break;
#endif
#ifdef CONSOLE
               player->winHandBets(BET_2,1); break;
#endif
        case 2:won+=player->getHandBet(BET_2)*2;
#ifdef GRAPHIC
               player->winXYBets(232,144,308,279,2); break;
#endif
#ifdef CONSOLE
               player->winHandBets(BET_2,2); break;
#endif
        case 3:won+=player->getHandBet(BET_2)*10;
#ifdef GRAPHIC
               player->winXYBets(232,144,308,279,10); break;
#endif
#ifdef CONSOLE
               player->winHandBets(BET_2,10); break;
#endif
        }
      total=abs((d1->getNumber()==3)+(d2->getNumber()==3)+(d3->getNumber()==3));
      switch (total) {
        case 0:lost+=player->getHandBet(BET_3);
#ifdef GRAPHIC
               player->loseXYBets(316,144,391,279); break;
#endif
#ifdef CONSOLE
               player->loseHandBets(BET_3); break;
#endif
        case 1:won+=player->getHandBet(BET_3);
#ifdef GRAPHIC
               player->winXYBets(316,144,391,279,1); break;
#endif
#ifdef CONSOLE
               player->winHandBets(BET_3,1); break;
#endif
        case 2:won+=player->getHandBet(BET_3)*2;
#ifdef GRAPHIC
               player->winXYBets(316,144,391,279,2); break;
#endif
#ifdef CONSOLE
               player->winHandBets(BET_3,2); break;
#endif
        case 3:won+=player->getHandBet(BET_3)*10;
#ifdef GRAPHIC
               player->winXYBets(316,144,391,279,10); break;
#endif
#ifdef CONSOLE
               player->winHandBets(BET_3,10); break;
#endif
        }
      total=abs((d1->getNumber()==4)+(d2->getNumber()==4)+(d3->getNumber()==4));
      switch (total) {
        case 0:lost+=player->getHandBet(BET_4);
#ifdef GRAPHIC
               player->loseXYBets(400,144,475,279); break;
#endif
#ifdef CONSOLE
               player->loseHandBets(BET_4); break;
#endif
        case 1:won+=player->getHandBet(BET_4);
#ifdef GRAPHIC
               player->winXYBets(400,144,475,279,1); break;
#endif
#ifdef CONSOLE
               player->winHandBets(BET_4,1); break;
#endif
        case 2:won+=player->getHandBet(BET_4)*2;
#ifdef GRAPHIC
               player->winXYBets(400,144,475,279,2); break;
#endif
#ifdef CONSOLE
               player->winHandBets(BET_4,2); break;
#endif
        case 3:won+=player->getHandBet(BET_4)*10;
#ifdef GRAPHIC
               player->winXYBets(400,144,475,279,10); break;
#endif
#ifdef CONSOLE
               player->winHandBets(BET_4,10); break;
#endif
        }
      total=abs((d1->getNumber()==5)+(d2->getNumber()==5)+(d3->getNumber()==5));
      switch (total) {
        case 0:lost+=player->getHandBet(BET_5);
#ifdef GRAPHIC
               player->loseXYBets(484,144,560,279); break;
#endif
#ifdef CONSOLE
               player->loseHandBets(BET_5); break;
#endif
        case 1:won+=player->getHandBet(BET_5);
#ifdef GRAPHIC
               player->winXYBets(484,144,560,279,1); break;
#endif
#ifdef CONSOLE
               player->winHandBets(BET_5,1); break;
#endif
        case 2:won+=player->getHandBet(BET_5)*2;
#ifdef GRAPHIC
               player->winXYBets(484,144,560,279,2); break;
#endif
#ifdef CONSOLE
               player->winHandBets(BET_5,2); break;
#endif
        case 3:won+=player->getHandBet(BET_5)*10;
#ifdef GRAPHIC
               player->winXYBets(484,144,560,279,10); break;
#endif
#ifdef CONSOLE
               player->winHandBets(BET_5,10); break;
#endif
        }
      total=abs((d1->getNumber()==6)+(d2->getNumber()==6)+(d3->getNumber()==6));
      switch (total) {
        case 0:lost+=player->getHandBet(BET_6);
#ifdef GRAPHIC
               player->loseXYBets(568,144,644,279); break;
#endif
#ifdef CONSOLE
               player->loseHandBets(BET_6); break;
#endif
        case 1:won+=player->getHandBet(BET_6);
#ifdef GRAPHIC
               player->winXYBets(568,144,644,279,1); break;
#endif
#ifdef CONSOLE
               player->winHandBets(BET_6,1); break;
#endif
        case 2:won+=player->getHandBet(BET_6)*2;
#ifdef GRAPHIC
               player->winXYBets(568,144,644,279,2); break;
#endif
#ifdef CONSOLE
               player->winHandBets(BET_6,2); break;
#endif
        case 3:won+=player->getHandBet(BET_6)*10;
#ifdef GRAPHIC
               player->winXYBets(568,144,644,279,10); break;
#endif
#ifdef CONSOLE
               player->winHandBets(BET_6,10); break;
#endif
        }
      showBets();
      player->clearAllBets();
      won-=lost;
#ifdef CONSOLE
      if (won>=0)
        sprintf(buffer,"WON $%12.2f",won);
       else
        sprintf(buffer,"Lost $%12.2f",-won);
      GotoXY(1,17); Output(buffer);
#endif
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
