#include <stdlib.h>
#include "header.h"
#include "poker.h"
#include "dstud.h"

#ifdef GRAPHIC
#include "images/dstud.xpm"
#endif

DStud::DStud(int decks,int jokers,float minbet):
  Poker(decks,jokers,minbet) {
  betAmount=minbet;
  }

int DStud::playerX(int p)
{
  switch (p) {
    case 0:return 9;
    case 1:return 166;
    case 2:return 334;
    case 3:return 504;
    case 4:return 662;
    case 99:return 256;
    }
  return 256;
}

int DStud::playerY(int p)
{
  switch (p) {
    case 0:return 384;
    case 1:return 408;
    case 2:return 429;
    case 3:return 408;
    case 4:return 384;
    case 99:return 21;
    }
  return 21;
}

int DStud::playerBetX(int p)
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

int DStud::playerBetY(int p)
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

void DStud::showBetAmount() {
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

void DStud::showPlayers() {
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

float DStud::placeBet(int player) {
  float betReturn;
  char  flag;
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
           if (event.d1 == 1 &&
               event.d2>=playerBetX(player)-50 &&
               event.d2<=playerBetX(player)+50 &&
               event.d3>=playerBetY(player)-50 &&
               event.d3<=playerBetY(player)+50 &&
               betAmount >= minBet) {
             betReturn=players[player]->placeBet(betAmount,0,playerBetX(player)-30,playerBetY(player)+15);
             flag='P';
             }
           break;
      }
    }
  gc=rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"darkgreen");
  rcs_drawFilledBox(display,mainScreen,gc,10,566,80,29);
  rcs_closeGC(display,gc);
  displayScreen();
  if (flag!='P' && flag!='D') return 0;
    else return betReturn;
  }

void DStud::play()
{
  float bet;
  float betReturn;
  rcs_GC gc;
  table=rcs_xpmToPixmap(display,mainWindow,dstud_xpm);
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
        betReturn=players[i]->placeBet(minBet,0,playerBetX(i)-30,playerBetY(i)+15);
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

void DStud::round()
{
  int i;
  unsigned long high;
  Hand* pHand;
  Card* card;
#ifdef GRAPHIC
  rcs_GC gc;
#endif
  for (i=0;i<PLAYERS_DSTUD;i++) if (players[i]!=NULL)
    players[i]->newHand(0);
  for (i=0;i<PLAYERS_DSTUD;i++) if (players[i]!=NULL) {
    players[i]->newCard(deck->dealCard(),0);
    players[i]->getHand(0)->cards[0]->setPosition(playerX(i)+28,playerY(i)-115);
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
      players[i]->getHand(0)->paint(display,mainScreen,gc,0);
      rcs_closeGC(display,gc);
      displayScreen();
#endif
#ifdef CONSOLE
      players[i]->getHand(0)->display(0);
#endif
      }
    Delay(1);
    }
  for (i=0;i<4;i++) {
    dealerHand->cards[i]=deck->dealCard();
    dealerHand->cards[i]->setPosition(playerX(99)+i*70,playerY(99));
    dealerHand->numCards=i+1;
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
  }
/*
  dealerHand->cards[1]=deck->dealCard();
  dealerHand->cards[2]=deck->dealCard();
  dealerHand->cards[3]=deck->dealCard();
*/
  for (i=0;i<PLAYERS_DSTUD;i++) if (players[i]!=NULL) {
    if (players[i]->playerType()=='H') {
#ifdef GRAPHIC
      if (actionBox(playerX(i),playerY(i)+40,120,70,"Double","Yes","No")==0) {
            players[i]->placeBet(players[i]->getHandBet(0),1,playerBetX(i)-30,playerBetY(i)-45);
        }
#endif
#ifdef CONSOLE
      GotoXY(playerX(i),playerY(i)+7);
      Output("Double ? ");
      Input(buffer);
      if (buffer[0]=='Y' || buffer[0]=='y') {
        players[i]->placeBet(players[i]->getHandBet(0),1,1,1);
        GotoXY(playerX(i),playerY(i)+1);
        sprintf(buffer,"%4.0f %4.0f ",players[i]->getHandBet(0),
          players[i]->getHandBet(1));
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
      pHand->cards[1]=dealerHand->cards[1];
      pHand->cards[2]=dealerHand->cards[2];
      pHand->cards[3]=dealerHand->cards[3];
      pHand->numCards=4;
      card=pHand->cards[0];
      high=pHand->pokerValue(5,0);
      pHand->cards[0]=card;
      if (high<(PK_PAIR | (6l<<24)) ) {
        } else {
        players[i]->placeBet(players[i]->getHandBet(0),1,playerBetX(i)-30,playerBetY(i)-45);
#ifdef CONSOLE
        GotoXY(playerX(i),playerY(i)+1);
        sprintf(buffer,"%4.0f %4.0f ",players[i]->getHandBet(0),
          players[i]->getHandBet(1));
        Output(buffer);
        GotoXY(playerX(i),playerY(i)+6);
        sprintf(buffer,"%12.2f",players[i]->money());
        Output("Money $");
        Output(buffer);
#endif
        }
      }
#ifdef GRAPHIC
    players[i]->paintBets();
    displayScreen();
    showPlayers();
#endif
#ifdef CONSOLE
    players[i]->showBets();
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
  for (i=0;i<PLAYERS_DSTUD;i++) if (players[i]!=NULL) {
    pHand=players[i]->getHand(0);
    pHand->cards[1]=dealerHand->cards[0];
    pHand->cards[2]=dealerHand->cards[1];
    pHand->cards[3]=dealerHand->cards[2];
    pHand->cards[4]=dealerHand->cards[3];
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
    GotoXY(playerX(i),playerY(i)+2);
    if (high>(0x16l<<24) && high<(0x1bl<<24)) {
#ifdef GRAPHIC
      msgBox(playerX(i),playerY(i)+40,120,30,"Lo Pair");
#endif
#ifdef CONSOLE
      Output("*Lo Pair*");
      GotoXY(playerX(i),playerY(i));
      sprintf(buffer,"%4.0f %4.0f ",0.0,0.0);
      Output(buffer);
#endif
      players[i]->winHandBets(0,0);
      players[i]->winHandBets(1,0);
      }
    else if (high>(0x1bl<<24) && high<(0x20l<<24)) {
#ifdef GRAPHIC
      msgBox(playerX(i),playerY(i)+40,120,30,"Hi Pair");
#endif
#ifdef CONSOLE
      Output("*Hi Pair*");
      GotoXY(playerX(i),playerY(i));
      sprintf(buffer,"%4.0f %4.0f ",players[i]->getHandBet(0),
        players[i]->getHandBet(1));
      Output(buffer);
#endif
      players[i]->winHandBets(0,1);
      players[i]->winHandBets(1,1);
      }
    else if ((high&(15l<<28))==PK_2_PAIR) {
#ifdef GRAPHIC
      msgBox(playerX(i),playerY(i)+40,120,30,"2 Pair");
#endif
#ifdef CONSOLE
      Output("*2 Pair*");
      GotoXY(playerX(i),playerY(i));
      sprintf(buffer,"%4.0f %4.0f ",2*players[i]->getHandBet(0),
        2*players[i]->getHandBet(1));
      Output(buffer);
#endif
      players[i]->winHandBets(0,2);
      players[i]->winHandBets(1,2);
      }
    else if ((high&(15l<<28))==PK_THREE) {
#ifdef GRAPHIC
      msgBox(playerX(i),playerY(i)+40,120,30,"3 of a kind");
#endif
#ifdef CONSOLE
      Output("*3 of a kind*");
      GotoXY(playerX(i),playerY(i));
      sprintf(buffer,"%4.0f %4.0f ",3*players[i]->getHandBet(0),
        3*players[i]->getHandBet(1));
      Output(buffer);
#endif
      players[i]->winHandBets(0,3);
      players[i]->winHandBets(1,3);
      }
    else if ((high&(15l<<28))==PK_STRAIGHT) {
#ifdef GRAPHIC
      msgBox(playerX(i),playerY(i)+40,120,30,"Straight");
#endif
#ifdef CONSOLE
      Output("*Straight*");
      GotoXY(playerX(i),playerY(i));
      sprintf(buffer,"%4.0f %4.0f ",5*players[i]->getHandBet(0),
        5*players[i]->getHandBet(1));
      Output(buffer);
#endif
      players[i]->winHandBets(0,5);
      players[i]->winHandBets(1,5);
      }
    else if ((high&(15l<<28))==PK_FLUSH) {
#ifdef GRAPHIC
      msgBox(playerX(i),playerY(i)+40,120,30,"Flush");
#endif
#ifdef CONSOLE
      Output("*Flush*");
      GotoXY(playerX(i),playerY(i));
      sprintf(buffer,"%4.0f %4.0f ",8*players[i]->getHandBet(0),
        8*players[i]->getHandBet(1));
      Output(buffer);
#endif
      players[i]->winHandBets(0,8);
      players[i]->winHandBets(1,8);
      }
    else if ((high&(15l<<28))==PK_FULLHOUSE) {
#ifdef GRAPHIC
      msgBox(playerX(i),playerY(i)+40,120,30,"Full House");
#endif
#ifdef CONSOLE
      Output("*Full House*");
      GotoXY(playerX(i),playerY(i));
      sprintf(buffer,"%4.0f %4.0f ",11*players[i]->getHandBet(0),
        11*players[i]->getHandBet(1));
      Output(buffer);
#endif
      players[i]->winHandBets(0,11);
      players[i]->winHandBets(1,11);
      }
    else if ((high&(15l<<28))==PK_FOUR) {
#ifdef GRAPHIC
      msgBox(playerX(i),playerY(i)+40,120,30,"4 of a kind");
#endif
#ifdef CONSOLE
      Output("*4 of a kind*");
      GotoXY(playerX(i),playerY(i));
      sprintf(buffer,"%4.0f %4.0f ",50*players[i]->getHandBet(0),
        50*players[i]->getHandBet(1));
      Output(buffer);
#endif
      players[i]->winHandBets(0,50);
      players[i]->winHandBets(1,50);
      }
    else if ((high&(15l<<28))==PK_STFLUSH) {
#ifdef GRAPHIC
      msgBox(playerX(i),playerY(i)+40,120,30,"Straight Flush");
#endif
#ifdef CONSOLE
      Output("*Straight Flush*");
      GotoXY(playerX(i),playerY(i));
      sprintf(buffer,"%4.0f %4.0f ",200*players[i]->getHandBet(0),
        200*players[i]->getHandBet(1));
      Output(buffer);
#endif
      players[i]->winHandBets(0,200);
      players[i]->winHandBets(1,200);
      }
    else if ((high&(15l<<28))==PK_ROYAL) {
#ifdef GRAPHIC
      msgBox(playerX(i),playerY(i)+40,120,30,"Royal Flush");
#endif
#ifdef CONSOLE
      Output("*Royal Flush*");
      GotoXY(playerX(i),playerY(i));
      sprintf(buffer,"%4.0f %4.0f ",2000*players[i]->getHandBet(0),
        2000*players[i]->getHandBet(1));
      Output(buffer);
#endif
      players[i]->winHandBets(0,2000);
      players[i]->winHandBets(1,2000);
      }
    else {
#ifdef CONSOLE
      Output("Game Over");
#endif
      players[i]->loseHandBets(0);
      players[i]->loseHandBets(1);
      }
    }
#ifdef GRAPHIC
  gc=rcs_openGC(display,mainScreen);
  for (i=0;i<5;i++)
    rcs_copyArea(display,table,mainScreen,gc,playerBetX(i)-50,playerBetY(i)-50,100,100,playerBetX(i)-50,playerBetY(i)-50);
  rcs_closeGC(display,gc);
  showPlayers();
  showBetAmount();
  for (i=0;i<PLAYERS_DSTUD;i++) if (players[i]!=NULL) players[i]->paintBets();
  displayScreen();
#endif

  Delay(5);
}
