#include <stdlib.h>
#include "header.h"
#include "poker.h"
#include "three.h"

#ifdef GRAPHIC
#include "images/three.xpm"
#endif

Three::Three(int decks,int jokers,float minbet):
  Poker(decks,jokers,minbet) {
  betAmount=minbet;
  }

int Three::playerX(int p)
{
  switch (p) {
    case 0:return 9;
    case 1:return 166;
    case 2:return 334;
    case 3:return 504;
    case 4:return 662;
    case 99:return 287;
    }
  return 287;
}

int Three::playerY(int p)
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

int Three::playerBetX(int p)
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

int Three::playerBetY(int p)
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

void Three::showBetAmount() {
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

void Three::showPlayers() {
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

float Three::placeBet(int player) {
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
             betReturn=players[player]->placeBet(betAmount,1,playerBetX(player)-30,playerBetY(player)+15);
             betFlags |= 1;
             showPlayers();
             players[i]->paintBets();
             displayScreen();
             if (betFlags == 3) flag='P';
             }
           if (event.d1 == 1 && (betFlags & 2) != 2 &&
               event.d2>=playerBetX(player)-30 &&
               event.d2<=playerBetX(player)+30 &&
               event.d3>=playerBetY(player)+70 &&
               event.d3<=playerBetY(player)+130 &&
               betAmount >= minBet) {
             betReturn=players[player]->placeBet(betAmount,0,playerBetX(player)-20,playerBetY(player)+85);
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

void Three::play()
{
  float tBet;
  float betReturn;
  rcs_GC gc;
  table=rcs_xpmToPixmap(display,mainWindow,three_xpm);
  tBet=1;
  while (tBet!=0) {
    tBet=0;
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
        tBet=placeBet(i);
        }
      else {
        betReturn=players[i]->placeBet(minBet,1,playerBetX(i)-30,playerBetY(i)+15);
        betReturn=players[i]->placeBet(minBet,0,playerBetX(i)-20,playerBetY(i)+85);
        }
      showPlayers();
      players[i]->paintBets();
      displayScreen();

      }
	if (betReturn) ;
    if (tBet!=0) {
      round();
      }
    }
}

void Three::round()
{
  int i,j;
  int high;
  Hand* pHand;
//  float betReturn;
#ifdef GRAPHIC
  rcs_GC gc;
#endif
  for (i=0;i<PLAYERS_THREE;i++) if (players[i]!=NULL)
    players[i]->newHand(0);
  for (i=0;i<PLAYERS_THREE;i++) if (players[i]!=NULL) {
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
  dealerHand->cards[0]=deck->dealCard();
  dealerHand->cards[0]->setPosition(playerX(99),playerY(99));
  dealerHand->cards[1]=deck->dealCard();
  dealerHand->cards[1]->setPosition(playerX(99)+70,playerY(99));
  dealerHand->cards[2]=deck->dealCard();
  dealerHand->cards[2]->setPosition(playerX(99)+140,playerY(99));
  dealerHand->numCards=3;
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    dealerHand->paint(display,mainScreen,gc,3);
    rcs_closeGC(display,gc);
    displayScreen();
#endif
#ifdef CONSOLE
  GotoXY(playerX(99),playerY(99));
  dealerHand->display(3); Delay(1);
#endif
  for (i=0;i<PLAYERS_THREE;i++) if (players[i]!=NULL) {
    if (players[i]->playerType()=='H') {
#ifdef GRAPHIC
      if (actionBox(playerX(i),playerY(i),120,70,"Play","Yes","No")==0) {
            players[i]->placeBet(players[i]->getHandBet(0),2,playerBetX(i)-30,playerBetY(i)-45);
        } else {
        players[i]->loseHandBets(0);
        players[i]->loseHandBets(1);
        gc=rcs_openGC(display,mainScreen);
        rcs_copyArea(display,table,mainScreen,gc,playerX(i),playerY(i)-250,120,310,playerX(i),playerY(i)-250);
        rcs_closeGC(display,gc);
        }
      gc=rcs_openGC(display,mainScreen);
      rcs_copyArea(display,table,mainScreen,gc,playerX(i),playerY(i),120,70,playerX(i),playerY(i));
      rcs_closeGC(display,gc);
#endif
#ifdef CONSOLE
      GotoXY(playerX(i),playerY(i)+7);
      Output("Play ? ");
      Input(buffer);
      if (buffer[0]=='N' || buffer[0]=='n') {
        players[i]->loseHandBets(0);
        players[i]->loseHandBets(1);
        GotoXY(playerX(i),playerY(i)+1);
        Output("          \n");
        } else {
        betReturn=players[i]->placeBet(players[i]->getHandBet(1),2,1,1);
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
      high=pHand->threePokerValue(0);
      if (high>0) {
        players[i]->placeBet(players[i]->getHandBet(1),2,playerBetX(i)-30,playerBetY(i)-45);
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
        } else {
        players[i]->loseHandBets(0);
        players[i]->loseHandBets(1);
#ifdef GRAPHIC
        gc=rcs_openGC(display,mainScreen);
        rcs_copyArea(display,table,mainScreen,gc,playerX(i),playerY(i)-250,120,310,playerX(i),playerY(i)-250);
        rcs_closeGC(display,gc);
#endif
#ifdef CONSOLE
        GotoXY(playerX(i),playerY(i)+1);
        Output("          \n");
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
  GotoXY(playerX(99),playerY(99));
  j=dealerHand->threePokerValue(0);
#ifdef GRAPHIC
  gc=rcs_openGC(display,mainScreen);
  dealerHand->paint(display,mainScreen,gc,0);
  rcs_closeGC(display,gc);
  displayScreen();
#endif
#ifdef CONSOLE
  dealerHand->display(0);
#endif
  Delay(1);
  GotoXY(playerX(99),playerY(99)+2);
  switch (j) {
    case 1:
#ifdef GRAPHIC
           msgBox(playerX(99)+210,playerY(99),120,30,"Pair");
#endif
#ifdef CONSOLE
           Output("Pair\n");
#endif
           break;
    case 2:
#ifdef GRAPHIC
           msgBox(playerX(99)+210,playerY(99),120,30,"Flush");
#endif
#ifdef CONSOLE
           Output("Flush\n");
#endif
           break;
    case 3:
#ifdef GRAPHIC
           msgBox(playerX(99)+210,playerY(99),120,30,"Straight");
#endif
#ifdef CONSOLE
           Output("Straight\n");
#endif
           break;
    case 4:
#ifdef GRAPHIC
           msgBox(playerX(99)+210,playerY(99),120,30,"3 of a kind");
#endif
#ifdef CONSOLE
           Output("3 of a kind\n");
#endif
           break;
    case 5:
#ifdef GRAPHIC
           msgBox(playerX(99)+210,playerY(99),120,30,"Straight Flush");
#endif
#ifdef CONSOLE
           Output("Straight Flush\n");
#endif
           break;
    default:if (dealerHand->cards[2]->value()<12)
#ifdef GRAPHIC
              msgBox(playerX(99)+210,playerY(99),120,30,"Non Qualify");
#endif
#ifdef CONSOLE
              Output("Non Qualify\n");
#endif
              else
#ifdef GRAPHIC
              msgBox(playerX(99)+210,playerY(99),120,30,"High Card");
#endif
#ifdef CONSOLE
              Output("High Card\n");
#endif
    }
  for (i=0;i<PLAYERS_THREE;i++) if (players[i]!=NULL)
    if (players[i]->getHandBet(0)+players[i]->getHandBet(1)>0) {
    pHand=players[i]->getHand(0);
#ifdef GRAPHIC
    for (j=0;j<3;j++)
      players[i]->getHand(0)->cards[j]->setPosition(playerX(i)+j*15,playerY(i)-120);
    gc=rcs_openGC(display,mainScreen);
    pHand->paint(display,mainScreen,gc,0);
    rcs_closeGC(display,gc);
    displayScreen();
#endif
#ifdef CONSOLE
    GotoXY(playerX(i),playerY(i)+3);
    pHand->display(0);
#endif
    high=pHand->threePokerValue(0);
    GotoXY(playerX(i),playerY(i)+2);
    if (high==1) {
#ifdef GRAPHIC
       msgBox(playerX(i),playerY(i)-50,120,30,"Pair");
#endif
#ifdef CONSOLE
      Output("*Pair*");
      GotoXY(playerX(i),playerY(i));
      sprintf(buffer,"%4.0f ",players[i]->getHandBet(0));
      Output(buffer);
#endif
      players[i]->winHandBets(0,1);
      }
    else if (high==2) {
#ifdef GRAPHIC
       msgBox(playerX(i),playerY(i)-50,120,30,"Flush");
#endif
#ifdef CONSOLE
      Output("*Flush*");
      GotoXY(playerX(i),playerY(i));
      sprintf(buffer,"%4.0f ",4*players[i]->getHandBet(0));
      Output(buffer);
#endif
      players[i]->winHandBets(0,4);
      }
    else if (high==3) {
#ifdef GRAPHIC
       msgBox(playerX(i),playerY(i)-50,120,30,"Straight");
#endif
#ifdef CONSOLE
      Output("*Straight*");
      GotoXY(playerX(i),playerY(i));
      sprintf(buffer,"%4.0f ",6*players[i]->getHandBet(0));
      Output(buffer);
#endif
      players[i]->winHandBets(0,6);
      }
    else if (high==4) {
#ifdef GRAPHIC
       msgBox(playerX(i),playerY(i)-50,120,30,"3 of a kind");
#endif
#ifdef CONSOLE
      Output("*3 of a kind*");
      GotoXY(playerX(i),playerY(i));
      sprintf(buffer,"%4.0f ",30*players[i]->getHandBet(0));
      Output(buffer);
#endif
      players[i]->winHandBets(0,30);
      }
    else if (high==5) {
#ifdef GRAPHIC
       msgBox(playerX(i),playerY(i)-50,140,30,"Straight Flush");
#endif
#ifdef CONSOLE
      Output("*Straight flush*");
      GotoXY(playerX(i),playerY(i));
      sprintf(buffer,"%4.0f ",40*players[i]->getHandBet(0));
      Output(buffer);
#endif
      players[i]->winHandBets(0,40);
      }
    else players[i]->loseHandBets(0);
    if (players[i]->getHandBet(1)>0) {
      j=players[i]->getHand(0)->threePokerCmp(dealerHand);
      switch (j) {
        case -1:
#ifdef CONSOLE
                GotoXY(playerX(i)+5,playerY(i)+1);
                Output("            \n");
#endif
                players[i]->loseHandBets(1);
                players[i]->loseHandBets(2);
                break;
        case  0:players[i]->winHandBets(1,0);
                players[i]->winHandBets(2,0);
                break;
        case  1:
#ifdef CONSOLE
                sprintf(buffer,"%4.0f ",players[i]->getHandBet(1));
                GotoXY(playerX(i)+5,playerY(i));
                Output(buffer);
#endif
                players[i]->winHandBets(1,1);
                players[i]->winHandBets(2,0);
                break;
        case  2:
#ifdef CONSOLE
                sprintf(buffer,"%4.0f %4.0f ",players[i]->getHandBet(1),
                        players[i]->getHandBet(2));
                GotoXY(playerX(i)+5,playerY(i));
                Output(buffer);
#endif
                players[i]->winHandBets(1,1);
                players[i]->winHandBets(2,1);
                break;
        }
      }
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    rcs_copyArea(display,table,mainScreen,gc,playerBetX(i)-50,playerBetY(i)-70,120,200,playerBetX(i)-50,playerBetY(i)-70);
    rcs_closeGC(display,gc);
    players[i]->paintBets();
    displayScreen();
    showPlayers();
#endif
#ifdef CONSOLE
    players[i]->showBets();
#endif

    }
  Delay(5);
}
