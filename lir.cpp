#include <stdlib.h>
#include "header.h"
#include "poker.h"
#include "lir.h"

#ifdef GRAPHIC
#include "images/lir.xpm"
#endif

Lir::Lir(int decks,int jokers,float minbet):
  Poker(decks,jokers,minbet) {
  betAmount=minbet;
  }

void Lir::clearBets(int p) {
  rcs_GC gc;
  gc=rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"black");
  rcs_copyArea(display,table,mainScreen,gc,playerBetX(p)-80,playerBetY(p)-90,
               140,217,playerBetX(p)-80,playerBetY(p)-90);
  rcs_closeGC(display,gc);
  }

int Lir::playerX(int p)
{
  switch (p) {
    case 0:return 9;
    case 1:return 166;
    case 2:return 334;
    case 3:return 504;
    case 4:return 662;
    case 99:return 325;
    }
  return 325;
}

int Lir::playerY(int p)
{
  switch (p) {
    case 0:return 464;
    case 1:return 488;
    case 2:return 509;
    case 3:return 488;
    case 4:return 464;
    case 99:return 21;
    }
  return 21;
}

int Lir::playerBetX(int p)
{
  switch (p) {
    case 0:return 82;
    case 1:return 239;
    case 2:return 408;
    case 3:return 579;
    case 4:return 736;
    case 99:return 33;
    }
  return 33;
}

int Lir::playerBetY(int p)
{
  switch (p) {
    case 0:return 213;
    case 1:return 240;
    case 2:return 262;
    case 3:return 240;
    case 4:return 213;
    case 99:return 5;
    case 98:return 8;
    }
  return 5;
}

void Lir::showBetAmount() {
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

void Lir::showPlayers() {
  int i;
  rcs_GC gc;
  rcs_Font font;
    for (i=0;i<PLAYERS_DSTUD;i++) if (players[i]!=NULL) {
      gc=rcs_openGC(display,mainScreen);
      font=rcs_openFont(display,PLAYER_FONT);
      rcs_setFont(display,gc,font);
      rcs_namedForeground(display,gc,"darkgreen");
      rcs_drawFilledBox(display,mainScreen,gc,playerX(i),playerY(i),125,40);
      rcs_namedForeground(display,gc,"yellow");
      rcs_drawString(display,mainScreen,gc,playerX(i),playerY(i),
                     players[i]->getName());
      sprintf(buffer,"Money $%12.2f",players[i]->money());
      rcs_drawString(display,mainScreen,gc,playerX(i),playerY(i)+20,buffer);
      rcs_closeFont(display,font);
      rcs_closeGC(display,gc);
      }
    displayScreen();
  }

float Lir::placeBet(int player) {
  float betReturn;
  char  flag;
  char  betFlags;
  rcs_Event event;
  rcs_GC    gc;
  rcs_Font  font;
  betFlags=0;
  gc=rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"gray");
  rcs_drawFilledBox(display,mainScreen,gc,10,566,80,29);
  rcs_namedForeground(display,gc,"black");
  rcs_drawBox(display,mainScreen,gc,12,568,76,25);
  font=rcs_openFont(display,BET_FONT);
  rcs_setFont(display,gc,font);
  rcs_drawString(display,mainScreen,gc,32,587,"Exit");

  rcs_namedForeground(display,gc,"gray");
  rcs_drawFilledBox(display,mainScreen,gc,210,566,80,29);
  rcs_namedForeground(display,gc,"black");
  rcs_drawBox(display,mainScreen,gc,212,568,76,25);
  rcs_drawString(display,mainScreen,gc,232,587,"Play");

  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  displayScreen();
  flag=' ';
  while (flag==' ') {
    event=getEvent(display);
    switch(event.type) {
      case EVENT_BUTTON_PRESS:
           if (event.d1 == 1 && event.d3>=566 && event.d3<=598) {
             if (event.d1 == 1 && event.d2>=210 && event.d2<=290) {
               flag='P';
               }
             if (event.d1 == 1 && event.d2>=10 && event.d2<=90) {
               flag='X';
               betFlags=0;
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
           if (event.d1 == 1 && (betFlags & 1) != 1 &&
               event.d2>=playerBetX(player)-50 &&
               event.d2<=playerBetX(player)+50 &&
               event.d3>=playerBetY(player)-50 &&
               event.d3<=playerBetY(player)+50 &&
               betAmount >= minBet) {
        betReturn=players[player]->placeBet(betAmount,0,playerBetX(player)-20,playerBetY(player)-50);
        betReturn=players[player]->placeBet(betAmount,1,playerBetX(player)-50,playerBetY(player)+15);
        betReturn=players[player]->placeBet(betAmount,2,playerBetX(player)+20,playerBetY(player)+15);
             betFlags |= 1;
             showPlayers();
             players[i]->paintBets();
             displayScreen();
             if (betFlags == 3) flag='P';
             }
           if (event.d1 == 1 && betFlags==1 &&
               event.d2>=playerBetX(player)-30 &&
               event.d2<=playerBetX(player)+30 &&
               event.d3>=playerBetY(player)+70 &&
               event.d3<=playerBetY(player)+130) {
             betReturn=players[player]->placeBet(1,3,playerBetX(player)-20,playerBetY(player)+85);
             betFlags |= 2;
             showPlayers();
             players[i]->paintBets();
             displayScreen();
             if (betFlags == 3) flag='P';
             }
           break;
      }
    }
  gc=rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"darkgreen");
  rcs_drawFilledBox(display,mainScreen,gc,10,566,80,29);
  rcs_drawFilledBox(display,mainScreen,gc,210,566,80,29);
  rcs_closeGC(display,gc);
  displayScreen();
  if (betFlags != 0) flag='P';
  if (flag!='P' && flag!='D') return 0;
    else return betReturn;
  }

void Lir::play()
{
  float bet;
  float betReturn;
  rcs_GC gc;
  table=rcs_xpmToPixmap(display,mainWindow,lir_xpm);
  bet=1;
  while (bet!=0) {
    gc=rcs_openGC(display,mainScreen);
    rcs_copyArea(display,table,mainScreen,gc,0,0,800,600,0,0);
    rcs_closeGC(display,gc);
    showBetAmount();
    displayScreen();
    deck->shuffle();
    for (i=0;i<5;i++) if (players[i]!=NULL) players[i]->clearAllBets();
    showPlayers();
    for (i=0;i<5;i++) if (players[i]!=NULL) {
      if (players[i]->playerType()=='H') {
        bet=placeBet(i);
        }
      else {
        betReturn=players[i]->placeBet(minBet,0,playerBetX(i)-20,playerBetY(i)-50);
        betReturn=players[i]->placeBet(minBet,1,playerBetX(i)-50,playerBetY(i)+15);
        betReturn=players[i]->placeBet(minBet,2,playerBetX(i)+20,playerBetY(i)+15);
        betReturn=players[i]->placeBet(1,3,playerBetX(i)-20,playerBetY(i)+85);
        }
      showPlayers();
      players[i]->paintBets();
      displayScreen();
      }
	if (betReturn) ;
    if (bet!=0) {
      round();
      }
    }
  rcs_closePixmap(display,table);
}

void Lir::round()
{
  int i,j;
  Card *c1,*c2,*c3;
  unsigned long high;
  Hand* pHand;
#ifdef GRAPHIC
  rcs_GC gc;
#endif
  for (i=0;i<PLAYERS_LIR;i++) if (players[i]!=NULL)
    players[i]->newHand(0);
  for (i=0;i<PLAYERS_LIR;i++) if (players[i]!=NULL) {
    for (j=0;j<3;j++)  {
      players[i]->newCard(deck->dealCard(),0);
      players[i]->getHand(0)->cards[j]->setPosition(playerX(i)+j*15,playerY(i)-120);
      }
    GotoXY(playerX(i),playerY(i)+3);
    if (players[i]->playerType()=='H') {
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    players[i]->getHand(0)->paint(display,mainScreen,gc,0);
    rcs_closeGC(display,gc);
    displayScreen();
#endif
#ifdef CONSOLE
      players[i]->getHand(0)->display(0);
#endif
      } else {
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    players[i]->getHand(0)->paint(display,mainScreen,gc,3);
    rcs_closeGC(display,gc);
    displayScreen();
#endif
#ifdef CONSOLE
      players[i]->getHand(0)->display(3);
#endif
      }
    Delay(1);
    }

/*
      players[i]->newCard(deck->dealCard(),0);
    GotoXY(playerX(i),playerY(i)+3);
    if (players[i]->playerType()=='H')
      players[i]->getHand(0)->display(0);
     else
      players[i]->getHand(0)->display(3);
    Delay(1);
    }
*/
  dealerHand->cards[0]=deck->dealCard();
  dealerHand->cards[0]->setPosition(playerX(99),playerY(99));
  dealerHand->cards[1]=deck->dealCard();
  dealerHand->cards[1]->setPosition(playerX(99)+70,playerY(99));
  dealerHand->numCards=2;
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    dealerHand->paint(display,mainScreen,gc,2);
    rcs_closeGC(display,gc);
    displayScreen();
#endif
#ifdef CONSOLE
  GotoXY(playerX(99),playerY(99));
  dealerHand->display(2);
#endif
   Delay(1);
  for (i=0;i<PLAYERS_LIR;i++) if (players[i]!=NULL) {
    if (players[i]->playerType()=='H') {
#ifdef GRAPHIC
      if (actionBox(playerX(i),playerY(i),130,70,"Let it ride?","Yes","No")!=0) {
        players[i]->winHandBets(2,0);
        players[i]->loseHandBets(2);
        }
      gc=rcs_openGC(display,mainScreen);
      rcs_copyArea(display,table,mainScreen,gc,playerX(i),playerY(i),130,70,playerX(i),playerY(i));
      rcs_closeGC(display,gc);
#endif
#ifdef CONSOLE
      GotoXY(playerX(i),playerY(i)+7);
      Output("Let it ride ? ");
      Input(buffer);
      if (buffer[0]=='N' || buffer[0]=='n') {
        players[i]->winHandBets(2,0);
        players[i]->loseHandBets(2);
        GotoXY(playerX(i),playerY(i)+1);
        sprintf(buffer,"%4.0f %4.0f %4.0f ",players[i]->getHandBet(0),
          players[i]->getHandBet(1),players[i]->getHandBet(2));
        Output(buffer);
        GotoXY(playerX(i),playerY(i)+6);
        sprintf(buffer,"%12.2f",players[i]->money());
        Output("Money $");
        Output(buffer);
        }
      GotoXY(playerX(i),playerY(i)+7);
      Output("                      ");
#endif
      }
    else {
      pHand=players[i]->getHand(0);
      c1=pHand->cards[0]; c2=pHand->cards[1]; c3=pHand->cards[2];
      high=pHand->pokerValue(5,0);
      pHand->cards[0]=c1; pHand->cards[1]=c2; pHand->cards[2]=c3;
      if (high<(PK_PAIR|(10l<<24))) {
        players[i]->winHandBets(2,0);
        players[i]->loseHandBets(2);
#ifdef CONSOLE
        GotoXY(playerX(i),playerY(i)+1);
        sprintf(buffer,"%4.0f %4.0f %4.0f ",players[i]->getHandBet(0),
          players[i]->getHandBet(1),players[i]->getHandBet(2));
        Output(buffer);
        GotoXY(playerX(i),playerY(i)+6);
        sprintf(buffer,"%12.2f",players[i]->money());
        Output("Money $");
        Output(buffer);
#endif
        }
      }
    clearBets(i);
#ifdef GRAPHIC
    showPlayers();
    players[i]->paintBets();
    displayScreen();
#endif
    Delay(1);
    }
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    dealerHand->paint(display,mainScreen,gc,1);
    rcs_closeGC(display,gc);
    displayScreen();
#endif
#ifdef CONSOLE
  GotoXY(playerX(99),playerY(99));
  dealerHand->display(1);
#endif
  Delay(1);
  for (i=0;i<PLAYERS_LIR;i++) if (players[i]!=NULL) {
    if (players[i]->playerType()=='H') {
#ifdef GRAPHIC
      if (actionBox(playerX(i),playerY(i),130,70,"Let it ride?","Yes","No")!=0) {
        players[i]->winHandBets(1,0);
        players[i]->loseHandBets(1);
        }
      gc=rcs_openGC(display,mainScreen);
      rcs_copyArea(display,table,mainScreen,gc,playerX(i),playerY(i),130,70,playerX(i),playerY(i));
      rcs_closeGC(display,gc);
#endif
#ifdef CONSOLE
      GotoXY(playerX(i),playerY(i)+7);
      Output("Let it ride ? ");
      Input(buffer);
      if (buffer[0]=='N' || buffer[0]=='n') {
        players[i]->winHandBets(1,1);
        players[i]->loseHandBets(1);
        GotoXY(playerX(i),playerY(i)+1);
        sprintf(buffer,"%4.0f %4.0f %4.0f ",players[i]->getHandBet(0),
          players[i]->getHandBet(1),players[i]->getHandBet(2));
        Output(buffer);
        GotoXY(playerX(i),playerY(i)+6);
        sprintf(buffer,"%12.2f",players[i]->money());
        Output("Money $");
        Output(buffer);
        }
      GotoXY(playerX(i),playerY(i)+7);
      Output("                      ");
#endif
      }
    else {
      pHand=players[i]->getHand(0);
      pHand->cards[3]=dealerHand->cards[1];
      pHand->numCards=4;
      c1=pHand->cards[0]; c2=pHand->cards[1]; c3=pHand->cards[2];
      high=pHand->pokerValue(5,0);
      pHand->cards[0]=c1; pHand->cards[1]=c2; pHand->cards[2]=c3;
      if (high<(PK_PAIR|(10l<<24))) {
        players[i]->winHandBets(1,0);
        players[i]->loseHandBets(1);
#ifdef CONSOLE
        GotoXY(playerX(i),playerY(i)+1);
        sprintf(buffer,"%4.0f %4.0f %4.0f ",players[i]->getHandBet(0),
          players[i]->getHandBet(1),players[i]->getHandBet(2));
        Output(buffer);
        GotoXY(playerX(i),playerY(i)+6);
        sprintf(buffer,"%12.2f",players[i]->money());
        Output("Money $");
        Output(buffer);
#endif
        }
      }
    clearBets(i);
#ifdef GRAPHIC
    showPlayers();
    players[i]->paintBets();
    displayScreen();
#endif
    Delay(1);
    }
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    dealerHand->paint(display,mainScreen,gc,0);
    rcs_closeGC(display,gc);
    displayScreen();
#endif
#ifdef CONSOLE
  GotoXY(playerX(99),playerY(99));
  dealerHand->display(0);
#endif
  Delay(1);
  for (i=0;i<PLAYERS_LIR;i++) if (players[i]!=NULL) {
    pHand=players[i]->getHand(0);
    pHand->numCards=3;
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    pHand->paint(display,mainScreen,gc,0);
    rcs_closeGC(display,gc);
    displayScreen();
#endif
#ifdef CONSOLE
    GotoXY(playerX(i),playerY(i)+3);
    pHand->display(0);
#endif
    pHand->cards[3]=dealerHand->cards[0];
    pHand->cards[4]=dealerHand->cards[1];
    pHand->numCards=5;
    high=pHand->pokerValue(5,0);
/*
GotoXY(playerX(i),playerY(i)+4);
printf(">%ld ",(high>>28)&15);
printf("%ld ",(high>>24)&15);
printf("%ld ",(high>>20)&15);
printf("%ld ",(high>>16)&15);
printf("%ld ",(high>>12)&15);
printf("%ld ",(high>>8)&15);
*/
#ifdef CONSOLE
    GotoXY(playerX(i),playerY(i)+2);
#endif
    if (high>(PK_PAIR|(10l<<24)) && high<PK_2_PAIR) {
#ifdef GRAPHIC
      msgBox(playerX(i),playerY(i)-40,120,30,"Pair");
#endif
#ifdef CONSOLE
      Output("*Pair*");
      GotoXY(playerX(i),playerY(i));
      sprintf(buffer,"%4.0f %4.0f %4.0f ",players[i]->getHandBet(0),
        players[i]->getHandBet(1),players[i]->getHandBet(2));
      Output(buffer);
#endif
      players[i]->winHandBets(0,1);
      players[i]->winHandBets(1,1);
      players[i]->winHandBets(2,1);
      players[i]->winHandBets(3,0);
//      players[i]->loseHandBets(3);
      }
    else if ((high&(15l<<28))==PK_2_PAIR) {
#ifdef GRAPHIC
      msgBox(playerX(i),playerY(i)-40,120,30,"2 Pair");
#endif
#ifdef CONSOLE
      Output("*2 Pair*");
      GotoXY(playerX(i),playerY(i));
      sprintf(buffer,"%4.0f %4.0f %4.0f ",players[i]->getHandBet(0)*2,
        players[i]->getHandBet(1)*2,players[i]->getHandBet(2)*2);
      Output(buffer);
#endif
      players[i]->winHandBets(0,2);
      players[i]->winHandBets(1,2);
      players[i]->winHandBets(2,2);
      players[i]->winHandBets(3,2);
//      players[i]->loseHandBets(3);
      }
    else if ((high&(15l<<28))==PK_THREE) {
#ifdef GRAPHIC
      msgBox(playerX(i),playerY(i)-40,120,30,"3 of a kind");
#endif
#ifdef CONSOLE
      Output("*3 of a kind*");
      GotoXY(playerX(i),playerY(i));
      sprintf(buffer,"%4.0f %4.0f %4.0f ",players[i]->getHandBet(0)*3,
        players[i]->getHandBet(1)*3,players[i]->getHandBet(2)*3);
      Output(buffer);
#endif
      players[i]->winHandBets(0,3);
      players[i]->winHandBets(1,3);
      players[i]->winHandBets(2,3);
      players[i]->winHandBets(3,3);
//      players[i]->loseHandBets(3);
      }
    else if ((high&(15l<<28))==PK_STRAIGHT) {
#ifdef GRAPHIC
      msgBox(playerX(i),playerY(i)-40,120,30,"Straight");
#endif
#ifdef CONSOLE
      Output("*Straight*");
      GotoXY(playerX(i),playerY(i));
      sprintf(buffer,"%4.0f %4.0f %4.0f ",players[i]->getHandBet(0)*5,
        players[i]->getHandBet(1)*5,players[i]->getHandBet(2)*5);
      Output(buffer);
#endif
      players[i]->winHandBets(0,5);
      players[i]->winHandBets(1,5);
      players[i]->winHandBets(2,5);
      if (players[i]->getHandBet(3)>0) {
          GotoXY(playerX(i)+15,playerY(i));
          Output("20");
          players[i]->winHandBets(3,25);
        }
      }
    else if ((high&(15l<<28))==PK_FLUSH) {
#ifdef GRAPHIC
      msgBox(playerX(i),playerY(i)-40,120,30,"Flush");
#endif
#ifdef CONSOLE
      Output("*Flush*");
      GotoXY(playerX(i),playerY(i));
      sprintf(buffer,"%4.0f %4.0f %4.0f ",players[i]->getHandBet(0)*8,
        players[i]->getHandBet(1)*8,players[i]->getHandBet(2)*8);
      Output(buffer);
#endif
      players[i]->winHandBets(0,8);
      players[i]->winHandBets(1,8);
      players[i]->winHandBets(2,8);
      if (players[i]->getHandBet(3)>0) {
          GotoXY(playerX(i)+15,playerY(i));
          Output("50");
          players[i]->winHandBets(3,50);
        }
      }
    else if ((high&(15l<<28))==PK_FULLHOUSE) {
#ifdef GRAPHIC
      msgBox(playerX(i),playerY(i)-40,120,30,"Full House");
#endif
#ifdef CONSOLE
      Output("*Full House*");
      GotoXY(playerX(i),playerY(i));
      sprintf(buffer,"%4.0f %4.0f %4.0f ",players[i]->getHandBet(0)*11,
        players[i]->getHandBet(1)*11,players[i]->getHandBet(2)*11);
      Output(buffer);
#endif
      players[i]->winHandBets(0,11);
      players[i]->winHandBets(1,11);
      players[i]->winHandBets(2,11);
      if (players[i]->getHandBet(3)>0) {
          GotoXY(playerX(i)+15,playerY(i));
          Output("75");
          players[i]->winHandBets(3,75);
        }
      }
    else if ((high&(15l<<28))==PK_FOUR) {
#ifdef GRAPHIC
      msgBox(playerX(i),playerY(i)-40,120,30,"4 of a kind");
#endif
#ifdef CONSOLE
      Output("*4 of a kind*");
      GotoXY(playerX(i),playerY(i));
      sprintf(buffer,"%4.0f %4.0f %4.0f ",players[i]->getHandBet(0)*50,
        players[i]->getHandBet(1)*50,players[i]->getHandBet(2)*50);
      Output(buffer);
#endif
      players[i]->winHandBets(0,50);
      players[i]->winHandBets(1,50);
      players[i]->winHandBets(2,50);
      if (players[i]->getHandBet(3)>0) {
          GotoXY(playerX(i)+15,playerY(i));
          Output("200");
          players[i]->winHandBets(3,100);
        }
      }
    else if ((high&(15l<<28))==PK_STFLUSH) {
#ifdef GRAPHIC
      msgBox(playerX(i),playerY(i)-40,120,30,"Straight Flush");
#endif
#ifdef CONSOLE
      Output("*Straight Flush*");
      GotoXY(playerX(i),playerY(i));
      sprintf(buffer,"%4.0f %4.0f %4.0f ",players[i]->getHandBet(0)*200,
        players[i]->getHandBet(1)*200,players[i]->getHandBet(2)*200);
      Output(buffer);
#endif
      players[i]->winHandBets(0,200);
      players[i]->winHandBets(1,200);
      players[i]->winHandBets(2,200);
      if (players[i]->getHandBet(3)>0) {
          GotoXY(playerX(i)+15,playerY(i));
          Output("2000");
          players[i]->winHandBets(3,1000);
        }
      }
    else if ((high&(15l<<28))==PK_ROYAL) {
#ifdef GRAPHIC
      msgBox(playerX(i),playerY(i)-40,120,30,"Royal Flush");
#endif
#ifdef CONSOLE
      Output("*Royal Flush*");
      GotoXY(playerX(i),playerY(i));
      sprintf(buffer,"%4.0f %4.0f %4.0f ",players[i]->getHandBet(0)*1000,
        players[i]->getHandBet(1)*1000,players[i]->getHandBet(2)*1000);
      Output(buffer);
#endif
      players[i]->winHandBets(0,1000);
      players[i]->winHandBets(1,1000);
      players[i]->winHandBets(2,1000);
      if (players[i]->getHandBet(3)>0) {
          GotoXY(playerX(i)+15,playerY(i));
          Output("20000");
          players[i]->winHandBets(3,20000);
        }
      }
    else {
#ifdef CONSOLE
      Output("Game Over");
#endif
      players[i]->loseHandBets(0);
      players[i]->loseHandBets(1);
      players[i]->loseHandBets(2);
      players[i]->loseHandBets(3);
      }
#ifdef GRAPHIC
    clearBets(i);
    players[i]->paintBets();
    displayScreen();
    showPlayers();
#endif
#ifdef CONSOLE
    players[i]->showBets();
#endif

    Delay(1);
    }

  Delay(5);
}
