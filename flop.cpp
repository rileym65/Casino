#include <stdlib.h>
#include "header.h"
#include "poker.h"
#include "flop.h"

#ifdef GRAPHIC
#include "images/flop.xpm"
#endif

Flop::Flop(int decks,int jokers,float minbet):
  Poker(decks,jokers,minbet) {
  betAmount=minbet;
  }

void Flop::clearBets(int p) {
#ifdef GRAPHIC
  rcs_GC gc;
  gc=rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"black");
  rcs_copyArea(display,table,mainScreen,gc,playerBetX(p)-80,playerBetY(p)-90,
               140,217,playerBetX(p)-80,playerBetY(p)-90);
  rcs_closeGC(display,gc);
#endif
  }

int Flop::playerX(int p)
{
  switch (p) {
    case 0:return 9;
    case 1:return 166;
    case 2:return 334;
    case 3:return 504;
    case 4:return 662;
    case 99:return 291;
    }
  return 325;
}

int Flop::playerY(int p)
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

int Flop::playerBetX(int p)
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

int Flop::playerBetY(int p)
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

void Flop::showBetAmount() {
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

void Flop::showPlayers() {
  int i;
#ifdef GRAPHIC
  rcs_GC gc;
  rcs_Font font;
#endif
    for (i=0;i<PLAYERS_DSTUD;i++) if (players[i]!=NULL) {
#ifdef GRAPHIC
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
#endif
#ifdef CONSOLE
      GotoXY(playerX(i),playerY(i));
      Output(players[i]->getName());
      GotoXY(playerX(i),playerY(i)+1);
      Output("Money $");
      sprintf(buffer,"%12.2f",players[i]->money());
      Output(buffer);
      GotoXY(playerX(i),playerY(i)+2);
      Output("Comm: $");
      sprintf(buffer,"%12.2f",comms[i]);
      Output(buffer);
#endif
      }
#ifdef GRAPHIC
    displayScreen();
#endif
  }

float Flop::placeBet(int player) {
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
           if (betAmount >= minBet &&
               event.d1 == 1 && (betFlags & 1) != 1 &&
               event.d2>=playerBetX(player)-50 &&
               event.d2<=playerBetX(player)+50 &&
               event.d3>=playerBetY(player)-50 &&
               event.d3<=playerBetY(player)+50) {
        betReturn=players[player]->placeBet(5,0,playerBetX(player)-20,playerBetY(player)-50);
        betReturn=players[player]->placeBet(betAmount,1,playerBetX(player)-50,playerBetY(player)+15);
//        betReturn=players[player]->placeBet(betAmount,2,playerBetX(player)+20,playerBetY(player)+15);
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

void Flop::play()
{
  float bet;
  float betReturn;
  rcs_GC gc;
  table=rcs_xpmToPixmap(display,mainWindow,flop_xpm);
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
//        betReturn=players[i]->placeBet(minBet,2,playerBetX(i)+20,playerBetY(i)+15);
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

void Flop::round()
{
  int i,j;
  Card *c1,*c2,*c3;
  unsigned long high;
  unsigned long high2;
  Hand* pHand;
//  float betReturn;
  int   potPlayer;
  int   potCount;
  char  flag;
  unsigned long potValue;
  rcs_GC gc;
  for (i=0;i<PLAYERS_FLOP;i++) if (players[i]!=NULL)
    players[i]->newHand(0);
  for (i=0;i<PLAYERS_FLOP;i++) if (players[i]!=NULL) {
    for (j=0;j<3;j++)  {
      players[i]->newCard(deck->dealCard(),0);
      players[i]->getHand(0)->cards[j]->setPosition(playerX(i)+j*15,playerY(i)-120);
      }
    GotoXY(playerX(i),playerY(i)+3);
    if (players[i]->playerType()=='H') {
    gc=rcs_openGC(display,mainScreen);
    players[i]->getHand(0)->paint(display,mainScreen,gc,0);
    rcs_closeGC(display,gc);
    displayScreen();
      } else {
    gc=rcs_openGC(display,mainScreen);
    players[i]->getHand(0)->paint(display,mainScreen,gc,3);
    rcs_closeGC(display,gc);
    displayScreen();
      }
    Delay(1);
    }

  dealerHand->cards[0]=deck->dealCard();
  dealerHand->cards[0]->setPosition(playerX(99),playerY(99));
  dealerHand->cards[1]=deck->dealCard();
  dealerHand->cards[1]->setPosition(playerX(99)+70,playerY(99));
  dealerHand->cards[2]=deck->dealCard();
  dealerHand->cards[2]->setPosition(playerX(99)+140,playerY(99));
  dealerHand->numCards=3;
    gc=rcs_openGC(display,mainScreen);
    dealerHand->paint(display,mainScreen,gc,3);
    rcs_closeGC(display,gc);
    displayScreen();
   Delay(1);
  for (i=0;i<PLAYERS_FLOP;i++) if (players[i]!=NULL) {
    if (players[i]->playerType()=='H') {
      if (actionBox(playerX(i),playerY(i),130,70,"Raise?","Yes","No")!=0) {
        players[i]->loseHandBets(1);
        } else {
        players[i]->placeBet(players[i]->getHandBet(1),2,playerBetX(i)+20,playerBetY(i)+15);
        }
      gc=rcs_openGC(display,mainScreen);
      rcs_copyArea(display,table,mainScreen,gc,playerX(i),playerY(i),130,70,playerX(i),playerY(i));
      rcs_closeGC(display,gc);
      }
    else {
      flag = 'N';
      pHand=players[i]->getHand(0);
      c1=pHand->cards[0]; c2=pHand->cards[1]; c3=pHand->cards[2];
      high=pHand->pokerValue(5,0);
      if ((high&(15l<<28))>=PK_PAIR) {
        flag = 'Y';
        }
      if (c1->getSuit() == c2->getSuit() &&
          c1->getSuit() == c3->getSuit()) {
        flag = 'Y';
        }
      if (c1->value() > 10 ||
          c2->value() > 10 ||
          c3->value() > 10) {
        flag = 'Y';
        }
      high = pHand->threePokerValue(0);
      if (high == 3) {
        flag = 'Y';
        }
      pHand->cards[0]=c1; pHand->cards[1]=c2; pHand->cards[2]=c3;
      if (flag == 'Y') {
        players[i]->placeBet(players[i]->getHandBet(1),2,playerBetX(i)+20,playerBetY(i)+15);
        } else {
        players[i]->loseHandBets(1);
        }
      }
    clearBets(i);
    showPlayers();
    players[i]->paintBets();
    displayScreen();
    Delay(1);
    }
    gc=rcs_openGC(display,mainScreen);
    dealerHand->paint(display,mainScreen,gc,0);
    rcs_closeGC(display,gc);
    displayScreen();
  Delay(1);
  potPlayer = 0;
  potValue = 0;
  potCount = 0;
  for (i=0;i<PLAYERS_FLOP;i++) if (players[i]!=NULL) {
    pHand=players[i]->getHand(0);
    pHand->numCards=3;
    gc=rcs_openGC(display,mainScreen);
    pHand->paint(display,mainScreen,gc,0);
    rcs_closeGC(display,gc);
    displayScreen();
    c1 = pHand->cards[0];
    c2 = pHand->cards[1];
    c3 = pHand->cards[2];

    pHand->cards[3]=dealerHand->cards[0];
    pHand->cards[4]=dealerHand->cards[1];
    pHand->numCards=5;
    high=pHand->pokerValue(5,0);
    pHand->cards[0]=c1; pHand->cards[1]=c2; pHand->cards[2]=c3;
    pHand->cards[3]=dealerHand->cards[0];
    pHand->cards[4]=dealerHand->cards[2];
    pHand->numCards=5;
    high2=pHand->pokerValue(5,0);
    if (high2 > high) high = high2;
    pHand->cards[0]=c1; pHand->cards[1]=c2; pHand->cards[2]=c3;
    pHand->cards[3]=dealerHand->cards[1];
    pHand->cards[4]=dealerHand->cards[2];
    pHand->numCards=5;
    high2=pHand->pokerValue(5,0);
    if (high2 > high) high = high2;
    potCount++;
    if (high > potValue) {
      potPlayer = i;
      potValue = high;
      }
    if (high>(PK_PAIR|(11l<<24)) && high<PK_2_PAIR) {
      msgBox(playerX(i),playerY(i)-40,120,30,"Hi Pair");
      players[i]->winHandBets(1,1);
      players[i]->winHandBets(2,1);
      }
    else if ((high&(15l<<28))==PK_2_PAIR) {
      msgBox(playerX(i),playerY(i)-40,120,30,"2 Pair");
      players[i]->winHandBets(1,1);
      players[i]->winHandBets(2,2);
      }
    else if ((high&(15l<<28))==PK_THREE) {
      msgBox(playerX(i),playerY(i)-40,120,30,"3 of a kind");
      players[i]->winHandBets(1,1);
      players[i]->winHandBets(2,4);
      }
    else if ((high&(15l<<28))==PK_STRAIGHT) {
      msgBox(playerX(i),playerY(i)-40,120,30,"Straight");
      players[i]->winHandBets(1,1);
      players[i]->winHandBets(2,11);
      }
    else if ((high&(15l<<28))==PK_FLUSH) {
      msgBox(playerX(i),playerY(i)-40,120,30,"Flush");
      players[i]->winHandBets(1,1);
      players[i]->winHandBets(2,20);
      }
    else if ((high&(15l<<28))==PK_FULLHOUSE) {
      msgBox(playerX(i),playerY(i)-40,120,30,"Full House");
      players[i]->winHandBets(1,1);
      players[i]->winHandBets(2,30);
      }
    else if ((high&(15l<<28))==PK_FOUR) {
      msgBox(playerX(i),playerY(i)-40,120,30,"4 of a kind");
      players[i]->winHandBets(1,1);
      players[i]->winHandBets(2,100);
      }
    else if ((high&(15l<<28))==PK_STFLUSH) {
      msgBox(playerX(i),playerY(i)-40,120,30,"Straight Flush");
      players[i]->winHandBets(1,1);
      players[i]->winHandBets(2,500);
      }
    else if ((high&(15l<<28))==PK_ROYAL) {
      msgBox(playerX(i),playerY(i)-40,120,30,"Royal Flush");
      players[i]->winHandBets(1,1);
      players[i]->winHandBets(2,1000);
      }
    else {
      if ((high&(15l<<28))==PK_PAIR)
        msgBox(playerX(i),playerY(i)-40,120,30,"Lo Pair");
      else
        msgBox(playerX(i),playerY(i)-40,120,30,"High Card");
      players[i]->loseHandBets(1);
      players[i]->loseHandBets(2);
      }
    clearBets(i);
    players[i]->paintBets();
    displayScreen();
    showPlayers();

    Delay(1);
    }
  for (i=0;i<PLAYERS_FLOP;i++) if (players[i]!=NULL) {
    if (i == potPlayer) {
      players[i]->winHandBets(0,potCount-1);
      } else {
      players[i]->loseHandBets(0);
      }
    clearBets(i);
    players[i]->paintBets();
    displayScreen();
    showPlayers();
    }

  Delay(5);
}
