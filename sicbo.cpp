#include <stdlib.h>
#include "header.h"
#include "sicbo.h"

#ifdef GRAPHIC
#include "images/sicbo.xpm"
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

Sicbo::Sicbo(Player* p) {
  player=p;
  d1=new Die(6);
  d1->setPosition(50,470);
  d1->setSize(60);
  d2=new Die(6);
  d2->setPosition(120,470);
  d2->setSize(60);
  d3=new Die(6);
  d3->setPosition(190,470);
  d3->setSize(60);
  betAmount=1;
  }

Sicbo::~Sicbo() {
  delete(d1);
  delete(d2);
  delete(d3);
  }

void Sicbo::showBetAmount() {
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

float Sicbo::placeBet() {
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
           if (event.d1 == 1 && event.d2>=341 && event.d2<=456 &&
                                event.d3>=490 && event.d3<=544) {
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
               (event.d1==1 && event.d2>=40 && event.d2<=152 &&
                event.d3>=362 && event.d3<=424) ||
               (event.d1==1 && event.d2>=161 && event.d2<=273 &&
                event.d3>=362 && event.d3<=424) ||
               (event.d1==1 && event.d2>=282 && event.d2<=394 &&
                event.d3>=362 && event.d3<=424) ||
               (event.d1==1 && event.d2>=402 && event.d2<=514 &&
                event.d3>=362 && event.d3<=424) ||
               (event.d1==1 && event.d2>=525 && event.d2<=636 &&
                event.d3>=362 && event.d3<=424) ||
               (event.d1==1 && event.d2>=647 && event.d2<=759 &&
                event.d3>=362 && event.d3<=424) ||
               (event.d1==1 && event.d2>=40 && event.d2<=130 &&
                event.d3>=29 && event.d3<=161) ||
               (event.d1==1 && event.d2>=668 && event.d2<=758 &&
                event.d3>=29 && event.d3<=161) ||
               (event.d1==1 && event.d2>=142 && event.d2<=178 &&
                event.d3>=66 && event.d3<=161) ||
               (event.d1==1 && event.d2>=190 && event.d2<=226 &&
                event.d3>=66 && event.d3<=161) ||
               (event.d1==1 && event.d2>=237 && event.d2<=273 &&
                event.d3>=66 && event.d3<=161) ||
               (event.d1==1 && event.d2>=524 && event.d2<=559 &&
                event.d3>=66 && event.d3<=161) ||
               (event.d1==1 && event.d2>=572 && event.d2<=608 &&
                event.d3>=66 && event.d3<=161) ||
               (event.d1==1 && event.d2>=619 && event.d2<=656 &&
                event.d3>=66 && event.d3<=161) ||
               (event.d1==1 && event.d2>=367 && event.d2<=431 &&
                event.d3>=66 && event.d3<=161) ||
               (event.d1==1 && event.d2>=287 && event.d2<=355 &&
                event.d3>=65 && event.d3<=87) ||
               (event.d1==1 && event.d2>=287 && event.d2<=355 &&
                event.d3>=102 && event.d3<=124) ||
               (event.d1==1 && event.d2>=287 && event.d2<=355 &&
                event.d3>=139 && event.d3<=160) ||
               (event.d1==1 && event.d2>=443 && event.d2<=511 &&
                event.d3>=65 && event.d3<=87) ||
               (event.d1==1 && event.d2>=443 && event.d2<=511 &&
                event.d3>=102 && event.d3<=124) ||
               (event.d1==1 && event.d2>=443 && event.d2<=511 &&
                event.d3>=139 && event.d3<=160) ||
               (event.d1==1 && event.d2>=40 && event.d2<=80 &&
                event.d3>=175 && event.d3<=256) ||
               (event.d1==1 && event.d2>=93 && event.d2<=133 &&
                event.d3>=175 && event.d3<=256) ||
               (event.d1==1 && event.d2>=145 && event.d2<=185 &&
                event.d3>=175 && event.d3<=256) ||
               (event.d1==1 && event.d2>=197 && event.d2<=237 &&
                event.d3>=175 && event.d3<=256) ||
               (event.d1==1 && event.d2>=248 && event.d2<=288 &&
                event.d3>=175 && event.d3<=256) ||
               (event.d1==1 && event.d2>=300 && event.d2<=340 &&
                event.d3>=175 && event.d3<=256) ||
               (event.d1==1 && event.d2>=352 && event.d2<=392 &&
                event.d3>=175 && event.d3<=256) ||
               (event.d1==1 && event.d2>=405 && event.d2<=445 &&
                event.d3>=175 && event.d3<=256) ||
               (event.d1==1 && event.d2>=456 && event.d2<=496 &&
                event.d3>=175 && event.d3<=256) ||
               (event.d1==1 && event.d2>=509 && event.d2<=549 &&
                event.d3>=175 && event.d3<=256) ||
               (event.d1==1 && event.d2>=561 && event.d2<=601 &&
                event.d3>=175 && event.d3<=256) ||
               (event.d1==1 && event.d2>=613 && event.d2<=653 &&
                event.d3>=175 && event.d3<=256) ||
               (event.d1==1 && event.d2>=664 && event.d2<=704 &&
                event.d3>=175 && event.d3<=256) ||
               (event.d1==1 && event.d2>=717 && event.d2<=757 &&
                event.d3>=175 && event.d3<=256) ||
               (event.d1==1 && event.d2>=40 && event.d2<=77 &&
                event.d3>=269 && event.d3<=351) ||
               (event.d1==1 && event.d2>=89 && event.d2<=125 &&
                event.d3>=269 && event.d3<=351) ||
               (event.d1==1 && event.d2>=137 && event.d2<=174 &&
                event.d3>=269 && event.d3<=351) ||
               (event.d1==1 && event.d2>=184 && event.d2<=221 &&
                event.d3>=269 && event.d3<=351) ||
               (event.d1==1 && event.d2>=232 && event.d2<=269 &&
                event.d3>=269 && event.d3<=351) ||
               (event.d1==1 && event.d2>=280 && event.d2<=317 &&
                event.d3>=269 && event.d3<=351) ||
               (event.d1==1 && event.d2>=327 && event.d2<=365 &&
                event.d3>=269 && event.d3<=351) ||
               (event.d1==1 && event.d2>=376 && event.d2<=415 &&
                event.d3>=269 && event.d3<=351) ||
               (event.d1==1 && event.d2>=425 && event.d2<=464 &&
                event.d3>=269 && event.d3<=351) ||
               (event.d1==1 && event.d2>=475 && event.d2<=513 &&
                event.d3>=269 && event.d3<=351) ||
               (event.d1==1 && event.d2>=524 && event.d2<=562 &&
                event.d3>=269 && event.d3<=351) ||
               (event.d1==1 && event.d2>=573 && event.d2<=611 &&
                event.d3>=269 && event.d3<=351) ||
               (event.d1==1 && event.d2>=621 && event.d2<=659 &&
                event.d3>=269 && event.d3<=351) ||
               (event.d1==1 && event.d2>=669 && event.d2<=708 &&
                event.d3>=269 && event.d3<=351) ||
               (event.d1==1 && event.d2>=719 && event.d2<=757 &&
                event.d3>=269 && event.d3<=351)
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


void Sicbo::showDice() {
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

void Sicbo::rollDice() {
  d1->roll();
  d2->roll();
  d3->roll();
  showDice();
  }

void Sicbo::drawBoard()
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

void Sicbo::showBets()
{
#ifdef GRAPHIC
  rcs_GC gc;
  gc=rcs_openGC(display,mainScreen);
  rcs_copyArea(display,table,mainScreen,gc,0,0,800,470,0,0);
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


void Sicbo::showPlayer() {
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

void Sicbo::play()
{
  float  bet;
  float won;
  float lost;
  char flag;
  int  tripple;
  int  total;
  int  ones,twos,threes,fours,fives,sixes;
#ifdef GRAPHIC
  table=rcs_xpmToPixmap(display,mainWindow,sicbo_xpm);
#endif
  drawBoard();
  flag=' ';
  lost = 0;
  player->clearAllBets();
  while (flag==' ') {
    drawBoard();
    showPlayer();
    bet=placeBet();
    if (bet != 0) {
      rollDice();
      total=d1->getNumber()+d2->getNumber()+d3->getNumber();
      ones=abs((d1->getNumber()==1)+(d2->getNumber()==1)+(d3->getNumber()==1));
      twos=abs((d1->getNumber()==2)+(d2->getNumber()==2)+(d3->getNumber()==2));
      threes=abs((d1->getNumber()==3)+(d2->getNumber()==3)+(d3->getNumber()==3));
      fours=abs((d1->getNumber()==4)+(d2->getNumber()==4)+(d3->getNumber()==4));
      fives=abs((d1->getNumber()==5)+(d2->getNumber()==5)+(d3->getNumber()==5));
      sixes=abs((d1->getNumber()==6)+(d2->getNumber()==6)+(d3->getNumber()==6));
      if (d1->getNumber()==d2->getNumber() &&
          d2->getNumber()==d3->getNumber()) tripple=d1->getNumber();
        else tripple=0;
      if (total>=4 && total<=10 && tripple==0)
        player->winXYBets(40,29,130,161,1);
      if (total>=11 && total<=17 && tripple==0)
        player->winXYBets(668,29,758,161,1);
      if (tripple !=0 ) player->winXYBets(367,66,431,161,30);
      if (tripple ==1 ) player->winXYBets(287,65,355,87,180);
      if (tripple ==2 ) player->winXYBets(287,102,355,124,180);
      if (tripple ==3 ) player->winXYBets(287,139,355,160,180);
      if (tripple ==4 ) player->winXYBets(443,65,511,87,180);
      if (tripple ==5 ) player->winXYBets(443,102,511,124,180);
      if (tripple ==6 ) player->winXYBets(443,139,511,160,180);
      if (ones>1) player->winXYBets(142,66,178,161,10);
      if (twos>1) player->winXYBets(190,66,226,161,10);
      if (threes>1) player->winXYBets(237,66,273,161,10);
      if (fours>1) player->winXYBets(524,66,559,161,10);
      if (fives>1) player->winXYBets(572,66,608,161,10);
      if (sixes>1) player->winXYBets(619,66,656,161,10);
      switch (ones) {
        case 1:player->winXYBets(40,362,152,424,1); break;
        case 2:player->winXYBets(40,362,152,424,2); break;
        case 3:player->winXYBets(40,362,152,424,3); break;
        }
      switch (twos) {
        case 1:player->winXYBets(161,362,273,424,1); break;
        case 2:player->winXYBets(161,362,273,424,2); break;
        case 3:player->winXYBets(161,362,273,424,3); break;
        }
      switch (threes) {
        case 1:player->winXYBets(282,362,394,424,1); break;
        case 2:player->winXYBets(282,362,394,424,2); break;
        case 3:player->winXYBets(282,362,394,424,3); break;
        }
      switch (fours) {
        case 1:player->winXYBets(402,362,514,424,1); break;
        case 2:player->winXYBets(402,362,514,424,2); break;
        case 3:player->winXYBets(402,362,514,424,3); break;
        }
      switch (fives) {
        case 1:player->winXYBets(525,362,636,424,1); break;
        case 2:player->winXYBets(525,362,636,424,2); break;
        case 3:player->winXYBets(525,362,636,424,3); break;
        }
      switch (sixes) {
        case 1:player->winXYBets(647,362,759,424,1); break;
        case 2:player->winXYBets(647,362,759,424,2); break;
        case 3:player->winXYBets(647,362,759,424,3); break;
        }
      switch (total) {
        case 4:player->winXYBets(40,175,80,256,60); break;
        case 5:player->winXYBets(93,175,133,256,30); break;
        case 6:player->winXYBets(145,175,185,256,17); break;
        case 7:player->winXYBets(197,175,237,256,12); break;
        case 8:player->winXYBets(248,175,288,256,8); break;
        case 9:player->winXYBets(300,175,340,256,6); break;
        case 10:player->winXYBets(352,175,392,256,6); break;
        case 11:player->winXYBets(405,175,445,256,6); break;
        case 12:player->winXYBets(459,175,496,256,6); break;
        case 13:player->winXYBets(509,175,549,256,8); break;
        case 14:player->winXYBets(561,175,601,256,12); break;
        case 15:player->winXYBets(613,175,653,256,17); break;
        case 16:player->winXYBets(664,175,704,256,30); break;
        case 17:player->winXYBets(717,175,757,256,60); break;
        }
      if (ones>0 && twos>0) player->winXYBets(40,269,77,351,5);
      if (ones>0 && threes>0) player->winXYBets(89,269,125,351,5);
      if (ones>0 && fours>0) player->winXYBets(137,269,174,351,5);
      if (ones>0 && fives>0) player->winXYBets(184,269,221,351,5);
      if (ones>0 && sixes>0) player->winXYBets(232,269,269,351,5);
      if (twos>0 && threes>0) player->winXYBets(280,269,317,351,5);
      if (twos>0 && fours>0) player->winXYBets(327,269,365,351,5);
      if (twos>0 && fives>0) player->winXYBets(376,269,415,351,5);
      if (twos>0 && sixes>0) player->winXYBets(425,269,464,351,5);
      if (threes>0 && fours>0) player->winXYBets(475,269,513,351,5);
      if (threes>0 && fives>0) player->winXYBets(524,269,562,351,5);
      if (threes>0 && sixes>0) player->winXYBets(573,269,611,351,5);
      if (fours>0 && fives>0) player->winXYBets(621,269,659,351,5);
      if (fours>0 && sixes>0) player->winXYBets(669,269,708,351,5);
      if (fives>0 && sixes>0) player->winXYBets(719,269,757,351,5);


      player->clearNonWinners();
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
