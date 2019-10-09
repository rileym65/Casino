#include <stdlib.h>
#include "header.h"
#include "poker.h"
#include "boston5.h"

#ifdef GRAPHIC
#include "images/boston5.xpm"
#endif

Boston5::Boston5(int decks,int jokers,float minbet):
  Poker(decks,jokers,minbet) {
  betAmount=minbet;
  comHand = new Hand(52);
  tmpHand = new Hand(52);
  }

Boston5::~Boston5() {
  delete(comHand);
  delete(tmpHand);
  }

int Boston5::playerX(int p)
{
  switch (p) {
    case 0:return 9;
    case 1:return 166;
    case 2:return 334;
    case 3:return 504;
    case 4:return 662;
    case 99:return 225;
    }
  return 325;
}

int Boston5::playerY(int p)
{
  switch (p) {
    case 0:return 464;
    case 1:return 488;
    case 2:return 509;
    case 3:return 488;
    case 4:return 464;
    case 99:return 17;
    }
  return 21;
}
int Boston5::playerBetX(int p)
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

int Boston5::playerBetY(int p)
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

void Boston5::clearBets(int p) {
  rcs_GC gc;
  gc=rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"black");
  rcs_copyArea(display,table,mainScreen,gc,playerBetX(p)-80,playerBetY(p)-90,
               140,217,playerBetX(p)-80,playerBetY(p)-90);
  rcs_closeGC(display,gc);
  }


void Boston5::showBetAmount() {
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

void Boston5::showPlayers() {
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

float Boston5::placeBet(int player) {
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
        betReturn=players[player]->placeBet(betAmount*2,1,playerBetX(player)-50,playerBetY(player)+15);
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
               event.d3<=playerBetY(player)+130 &&
               betAmount >= minBet) {
             betReturn=players[player]->placeBet(betAmount,3,playerBetX(player)-20,playerBetY(player)+85);
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



void Boston5::play()
{
  float bet;
  float betReturn;
  rcs_GC gc;
  table=rcs_xpmToPixmap(display,mainWindow,boston5_xpm);

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
        betReturn=players[i]->placeBet(minBet*2,1,playerBetX(i)-50,playerBetY(i)+15);
        betReturn=players[i]->placeBet(minBet,3,playerBetX(i)-20,playerBetY(i)+85);
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

void Boston5::round()
{
  int i,j;
  unsigned long high;
  unsigned long dhigh;
  int payout;
  float bet;
  float betReturn;
  Hand* pHand;
  rcs_GC gc;

  for (i=0;i<PLAYERS_BOSTON5;i++) if (players[i]!=NULL)
    players[i]->newHand(0);
  for (i=0;i<PLAYERS_BOSTON5;i++) if (players[i]!=NULL) {
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
    players[i]->getHand(0)->paint(display,mainScreen,gc,5);
    rcs_closeGC(display,gc);
    displayScreen();
      }
    Delay(1);
    }

  for (i=0;i<3;i++) {
    dealerHand->cards[i]=deck->dealCard();
      dealerHand->cards[i]->setPosition(playerX(99)+i*70,playerY(99));
    }
  dealerHand->numCards=3;
    gc=rcs_openGC(display,mainScreen);
    dealerHand->paint(display,mainScreen,gc,4);
    rcs_closeGC(display,gc);
    displayScreen();
   Delay(1);
  
  for (i=0;i<PLAYERS_BOSTON5;i++)
    if (players[i]!=NULL && players[i]->getHandBet(3) > 0) {
      pHand=players[i]->getHand(0);
      high = pHand->threePokerValue(0);
     if (high == 1) players[i]->winHandBets(3,1);
     else if (high == 2) players[i]->winHandBets(3,4);
     else if (high == 3) players[i]->winHandBets(3,6);
     else if (high == 4) players[i]->winHandBets(3,30);
     else if (high == 5) players[i]->winHandBets(3,40);
     else players[i]->loseHandBets(3);
      clearBets(i);
      players[i]->paintBets();
      displayScreen();
      showPlayers();
    }

  for (i=0;i<PLAYERS_BOSTON5;i++) if (players[i]!=NULL) {
    if (players[i]->playerType()=='H') {
      if (actionBox(playerX(i),playerY(i),120,70,"Play","Yes","No")==0) {
        players[i]->placeBet(players[i]->getHandBet(0)*2,2,playerBetX(i)+20,playerBetY(i)+15);
        } else {
        players[i]->loseHandBets(0);
        players[i]->loseHandBets(1);
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
      high=pHand->pokerValue(5,0) & (15l<<28);
      if (high>=(0x0ed<<20) || rcs_random(100) > 5) {
        bet=players[i]->getHandBet(1);
        betReturn=players[i]->placeBet(bet,2,playerBetX(i)+20,playerBetY(i)+15);

        } else {
        players[i]->loseHandBets(0);
        players[i]->loseHandBets(1);
        gc=rcs_openGC(display,mainScreen);
        rcs_copyArea(display,table,mainScreen,gc,playerX(i),playerY(i)-250,145,310,playerX(i),playerY(i)-250);
        rcs_closeGC(display,gc);
        }
      }
      clearBets(i);
      players[i]->paintBets();
      displayScreen();
      showPlayers();
      Delay(1);
    }

  for (i=0;i<PLAYERS_BOSTON5;i++)
    if (players[i]!=NULL && players[i]->getHandBet(0)>0) {
    pHand=players[i]->getHand(0);
    for (j=0;j<2;j++)  {
      players[i]->newCard(deck->dealCard(),0);
      players[i]->getHand(0)->cards[j+3]->setPosition(playerX(i)+(j+3)*15,playerY(i)-120);
      }
    for (j=0; j<5; j++)
      players[i]->getHand(0)->cards[j]->setPosition(playerX(i)+j*15,playerY(i)-120);
    gc=rcs_openGC(display,mainScreen);
    if (players[i]->playerType()=='H')
      players[i]->getHand(0)->paint(display,mainScreen,gc,0);
    else 
      players[i]->getHand(0)->paint(display,mainScreen,gc,5);
    rcs_closeGC(display,gc);
    displayScreen();
    Delay(1);
    }

  for (i=0;i<2;i++) {
    dealerHand->cards[i+3]=deck->dealCard();
    dealerHand->cards[i+3]->setPosition(playerX(99)+(i+3)*70,playerY(99));
    }
  dealerHand->numCards = 5;
  gc=rcs_openGC(display,mainScreen);
  dealerHand->paint(display,mainScreen,gc,0);
  rcs_closeGC(display,gc);
  displayScreen();
  Delay(1);

  dhigh=dealerHand->pokerValue(5,0);
  dealerHand->sort(0);
  GotoXY(playerX(99),playerY(99)+1);
    if ((dhigh&(15l<<28))==0)
      msgBox(playerX(99)+10,playerY(99)+45,120,30,"High Card");
    else if ((dhigh&(15l<<28))==PK_PAIR)
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


  for (i=0;i<PLAYERS_BOSTON5;i++)
    if (players[i]!=NULL && players[i]->getHandBet(0)>0) {
    pHand=players[i]->getHand(0);
    gc=rcs_openGC(display,mainScreen);
    pHand->paint(display,mainScreen,gc,0);
    rcs_closeGC(display,gc);
    displayScreen();

    high=pHand->pokerValue(5,0);

    if ((high&(15l<<28))==0) {
      msgBox(playerX(i),playerY(i)-50,120,30,"High Card");
      payout=0;
      }
    if ((high&(15l<<28))==PK_PAIR) {
      msgBox(playerX(i),playerY(i)-50,120,30,"Pair");
      payout=0;
      }
    else if ((high&(15l<<28))==PK_2_PAIR) {
      msgBox(playerX(i),playerY(i)-50,120,30,"2 Pair");
      payout=2;
      }
    else if ((high&(15l<<28))==PK_THREE) {
      msgBox(playerX(i),playerY(i)-50,120,30,"3 of a Kind");
      payout=5;
      }
    else if ((high&(15l<<28))==PK_STRAIGHT) {
      msgBox(playerX(i),playerY(i)-50,120,30,"Straight");
      payout=10;
      }
    else if ((high&(15l<<28))==PK_FLUSH) {
      msgBox(playerX(i),playerY(i)-50,120,30,"Flush");
      payout=15;
      }
    else if ((high&(15l<<28))==PK_FULLHOUSE) {
      msgBox(playerX(i),playerY(i)-50,120,30,"Full House");
      payout=25;
      }
    else if ((high&(15l<<28))==PK_FOUR) {
      msgBox(playerX(i),playerY(i)-50,120,30,"4 of a Kind");
      payout=100;
      }
    else if ((high&(15l<<28))==PK_STFLUSH) {
      msgBox(playerX(i),playerY(i)-50,120,30,"Straight Flush");
      payout=200;
      }
    else if ((high&(15l<<28))==PK_ROYAL) {
      msgBox(playerX(i),playerY(i)-50,120,30,"Royal Flush");
      payout=1000;
      }

      if (high > dhigh) {
        players[i]->winHandBets(1,1);
        players[i]->winHandBets(2,1);
        players[i]->winHandBets(0,payout);
        } else {
        payout -= 1;
        players[i]->loseHandBets(1);
        players[i]->loseHandBets(2);
        if (payout >= 0) player[i]->winHandBets(0,payout);
          else players[i]->loseHandBets(0);
        }
    gc=rcs_openGC(display,mainScreen);
    rcs_copyArea(display,table,mainScreen,gc,playerBetX(i)-75,playerBetY(i)-70,165,100,playerBetX(i)-75,playerBetY(i)-70);
    rcs_closeGC(display,gc);
    players[i]->paintBets();
    displayScreen();
    showPlayers();
    Delay(1);
    }

  if (betReturn) ;
  Delay(5);
}
