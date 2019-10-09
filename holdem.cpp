#include <stdlib.h>
#include "header.h"
#include "poker.h"
#include "holdem.h"

#ifdef GRAPHIC
#include "images/holdem.xpm"
#endif

Holdem::Holdem(int decks,int jokers,float minbet):
  Poker(decks,jokers,minbet) {
  betAmount=minbet;
  comHand = new Hand(52);
  tmpHand = new Hand(52);
  }

Holdem::~Holdem() {
  delete(comHand);
  delete(tmpHand);
  }

int Holdem::playerX(int p)
{
  switch (p) {
    case 0:return 9;
    case 1:return 166;
    case 2:return 334;
    case 3:return 504;
    case 4:return 662;
    case 99:return 324;
    }
  return 220;
}

int Holdem::playerY(int p)
{
  switch (p) {
    case 0:return 434;
    case 1:return 458;
    case 2:return 479;
    case 3:return 458;
    case 4:return 434;
    case 99:return 2;
    }
  return 21;
}

int Holdem::playerBetX(int p)
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

int Holdem::playerBetY(int p)
{
  switch (p) {
    case 0:return 263;
    case 1:return 290;
    case 2:return 312;
    case 3:return 290;
    case 4:return 263;
    case 99:return 5; 
    case 98:return 8;
    }
  return 5;
}

void Holdem::showBetAmount() {
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

void Holdem::showPlayers() {
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


float Holdem::placeBet(int player) {
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
/*
  rcs_namedForeground(display,gc,"gray");
  rcs_drawFilledBox(display,mainScreen,gc,210,566,80,29);
  rcs_namedForeground(display,gc,"black");
  rcs_drawBox(display,mainScreen,gc,212,568,76,25);
  rcs_drawString(display,mainScreen,gc,232,587,"Play");
*/
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
             betReturn=players[player]->placeBet(betAmount,0,playerBetX(player)-30,playerBetY(player)+15);
             betFlags |= 1;
             showPlayers();
             players[i]->paintBets();
             displayScreen();
             flag='P';
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

void Holdem::play()
{
  float bet;
  float betReturn;
  rcs_GC gc;
  table=rcs_xpmToPixmap(display,mainWindow,holdem_xpm);

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

void Holdem::round()
{
  int i,j;
  unsigned long high;
  unsigned long dhigh;
  unsigned long dhigh2;
  int payout;
  float bet;
  float betReturn;
  Hand* pHand;
#ifdef GRAPHIC
  rcs_GC gc;
#endif

  for (i=0;i<PLAYERS_HOLDEM;i++) if (players[i]!=NULL)
    players[i]->newHand(0);
  for (i=0;i<PLAYERS_HOLDEM;i++) if (players[i]!=NULL) {
    for (j=0;j<2;j++)  {
      players[i]->newCard(deck->dealCard(),0);
      players[i]->getHand(0)->cards[j]->setPosition(playerX(i)+j*67,playerY(i)-120);
      }
    GotoXY(playerX(i),playerY(i)+3);
    if (players[i]->playerType()=='H') {
    gc=rcs_openGC(display,mainScreen);
    players[i]->getHand(0)->paint(display,mainScreen,gc,0);
    rcs_closeGC(display,gc);
    displayScreen();
      } else {
    gc=rcs_openGC(display,mainScreen);
    players[i]->getHand(0)->paint(display,mainScreen,gc,5);
    rcs_closeGC(display,gc);
    displayScreen();
      }
    Delay(1);
    }

  for (i=0;i<2;i++) {
    dealerHand->cards[i]=deck->dealCard();
      dealerHand->cards[i]->setPosition(playerX(99)+i*70,playerY(99));
    }
  dealerHand->numCards=2;
    gc=rcs_openGC(display,mainScreen);
    dealerHand->paint(display,mainScreen,gc,4);
    rcs_closeGC(display,gc);
    displayScreen();
   Delay(1);

  for (i=0;i<3;i++) {
    comHand->cards[i]=deck->dealCard();
      comHand->cards[i]->setPosition(playerX(99)+i*70-104,playerY(99)+104);
    }
  comHand->numCards=3;
    gc=rcs_openGC(display,mainScreen);
    comHand->paint(display,mainScreen,gc,0);
    rcs_closeGC(display,gc);
    displayScreen();
   Delay(1);
  
  for (i=0;i<PLAYERS_HOLDEM;i++) if (players[i]!=NULL) {
    if (players[i]->playerType()=='H') {
      if (actionBox(playerX(i),playerY(i),120,70,"Play","Yes","No")==0) {
            players[i]->placeBet(players[i]->getHandBet(0)*2,1,playerBetX(i)-30,playerBetY(i)-45);
        } else {
        players[i]->loseHandBets(0);
        gc=rcs_openGC(display,mainScreen);
        rcs_copyArea(display,table,mainScreen,gc,playerX(i),playerY(i)-250,145,310,playerX(i),playerY(i)-250);
        rcs_closeGC(display,gc);
        }
      gc=rcs_openGC(display,mainScreen);
      rcs_copyArea(display,table,mainScreen,gc,playerX(i),playerY(i),120,70,playerX(i),playerY(i));
      rcs_closeGC(display,gc);


      }
    else {
      pHand=players[i]->getHand(0);
      for (j=0; j<2; j++) tmpHand->cards[j] = pHand->cards[j];
      for (j=0; j<3; j++) tmpHand->cards[j+2] = comHand->cards[j];
      tmpHand->numCards = 5;
      high=tmpHand->pokerValue(5,0) & (15l<<28);
      if (high>=PK_PAIR) {
        bet=players[i]->getHandBet(0)*2;
        betReturn=players[i]->placeBet(bet,1,playerBetX(i)-30,playerBetY(i)-45);

        } else {
        players[i]->loseHandBets(0);
        gc=rcs_openGC(display,mainScreen);
        rcs_copyArea(display,table,mainScreen,gc,playerX(i),playerY(i)-250,145,310,playerX(i),playerY(i)-250);
        rcs_closeGC(display,gc);
        }
      }
      players[i]->paintBets();
      displayScreen();
      showPlayers();
      Delay(1);
    }
  for (i=0;i<2;i++) {
    comHand->cards[i+3]=deck->dealCard();
      comHand->cards[i+3]->setPosition(playerX(99)+(i+3)*70-104,playerY(99)+104);
    }
  comHand->numCards=5;
    gc=rcs_openGC(display,mainScreen);
    comHand->paint(display,mainScreen,gc,0);
    rcs_closeGC(display,gc);
    displayScreen();
   Delay(1);

  gc=rcs_openGC(display,mainScreen);
  dealerHand->paint(display,mainScreen,gc,0);
  rcs_closeGC(display,gc);
  displayScreen();
  Delay(1);

  for (j=0; j<2; j++) tmpHand->cards[j] = dealerHand->cards[j];
  for (j=0; j<5; j++) tmpHand->cards[j+2] = comHand->cards[j];
  tmpHand->numCards = 7;
  dhigh=tmpHand->pokerValue(5,0);
  dhigh2 = dhigh;
  dealerHand->sort(0);
  GotoXY(playerX(99),playerY(99)+1);
    if (dhigh < 0x14400000l) {
        msgBox(playerX(99)+10,playerY(99)+45,120,30,"Non-Qualify");
        dhigh=0;
      }
    if ((dhigh&(15l<<28))==PK_PAIR)
      msgBox(playerX(99)+10,playerY(99)+45,120,30,"Pair");
    else if ((dhigh&(15l<<28))==PK_2_PAIR)
      msgBox(playerX(99)+10,playerY(99)+45,120,30,"2 Pair");
    else if ((dhigh&(15l<<28))==PK_THREE)
      msgBox(playerX(99)+10,playerY(99)+45,120,30,"3 of a Kind");
    else if ((dhigh&(15l<<28))==PK_STRAIGHT)
      msgBox(playerX(99)+10,playerY(99)+45,120,30,"Straight");
    else if ((dhigh&(15l<<28))==PK_FLUSH)
      msgBox(playerX(99)+10,playerY(99)+45,120,30,"Flush");
    else if ((dhigh&(15l<<28))==PK_FULLHOUSE)
      msgBox(playerX(99)+10,playerY(99)+45,120,30,"Full House");
    else if ((dhigh&(15l<<28))==PK_FOUR) 
      msgBox(playerX(99)+10,playerY(99)+45,120,30,"4 of a Kind");
    else if ((dhigh&(15l<<28))==PK_STFLUSH)
      msgBox(playerX(99)+10,playerY(99)+45,120,30,"Straight Flush");
    else if ((dhigh&(15l<<28))==PK_ROYAL)
      msgBox(playerX(99)+10,playerY(99)+45,120,30,"Royal Flush");

Delay(1);


  for (i=0;i<PLAYERS_HOLDEM;i++)
    if (players[i]!=NULL && players[i]->getHandBet(0)>0) {
    pHand=players[i]->getHand(0);
    gc=rcs_openGC(display,mainScreen);
    pHand->paint(display,mainScreen,gc,0);
    rcs_closeGC(display,gc);
    displayScreen();

    for (j=0; j<2; j++) tmpHand->cards[j] = pHand->cards[j];
    for (j=0; j<5; j++) tmpHand->cards[j+2] = comHand->cards[j];
    tmpHand->numCards = 7;
    high=tmpHand->pokerValue(5,0);

    if ((high&(15l<<28))==0) {
      msgBox(playerX(i),playerY(i)-50,120,30,"High Card");
      payout=1;
      }
    if ((high&(15l<<28))==PK_PAIR) {
      msgBox(playerX(i),playerY(i)-50,120,30,"Pair");
      payout=1;
      }
    else if ((high&(15l<<28))==PK_2_PAIR) {
      msgBox(playerX(i),playerY(i)-50,120,30,"2 Pair");
      payout=1;
      }
    else if ((high&(15l<<28))==PK_THREE) {
      msgBox(playerX(i),playerY(i)-50,120,30,"3 of a Kind");
      payout=1;
      }
    else if ((high&(15l<<28))==PK_STRAIGHT) {
      msgBox(playerX(i),playerY(i)-50,120,30,"Straight");
      payout=1;
      }
    else if ((high&(15l<<28))==PK_FLUSH) {
      msgBox(playerX(i),playerY(i)-50,120,30,"Flush");
      payout=2;
      }
    else if ((high&(15l<<28))==PK_FULLHOUSE) {
      msgBox(playerX(i),playerY(i)-50,120,30,"Full House");
      payout=3;
      }
    else if ((high&(15l<<28))==PK_FOUR) {
      msgBox(playerX(i),playerY(i)-50,120,30,"4 of a Kind");
      payout=10;
      }
    else if ((high&(15l<<28))==PK_STFLUSH) {
      msgBox(playerX(i),playerY(i)-50,120,30,"Straight Flush");
      payout=20;
      }
    else if ((high&(15l<<28))==PK_ROYAL) {
      msgBox(playerX(i),playerY(i)-50,120,30,"Royal Flush");
      payout=20;
      }

    if (dhigh==0) {
      if (high > dhigh2) players[i]->winHandBets(0,payout);
        else players[i]->winHandBets(0,1);
      players[i]->winHandBets(1,0);
      } else {
      if (high > dhigh2) {
        players[i]->winHandBets(0,payout);
        players[i]->winHandBets(1,1);
        } else {
        players[i]->loseHandBets(0);
        players[i]->loseHandBets(1);
        }
      }
    gc=rcs_openGC(display,mainScreen);
    rcs_copyArea(display,table,mainScreen,gc,playerBetX(i)-50,playerBetY(i)-70,120,100,playerBetX(i)-50,playerBetY(i)-70);
    rcs_closeGC(display,gc);
    players[i]->paintBets();
    displayScreen();
    showPlayers();
    Delay(1);
    }

  if (betReturn) ;
  Delay(5);
}
