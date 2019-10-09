#include <stdlib.h>
#include <math.h>
#include "header.h"
#include "poker.h"
#include "paigow.h"

#ifdef GRAPHIC
#include "images/paigow.xpm"
#endif

Paigow::Paigow(int decks,int jokers,float minbet):
  Poker(decks,jokers,minbet) {
  betAmount=20;
  }

int Paigow::playerX(int p)
{
#ifdef GRAPHIC
  switch (p) {
    case 0:return 9;
    case 1:return 166;
    case 2:return 334;
    case 3:return 504;
    case 4:return 662;
    case 99:return 113;
    }
#endif
#ifdef CONSOLE
  switch (p) {
    case 0:return 60;
    case 1:return 60;
    case 2:return 30;
    case 3:return 1;
    case 4:return 1;
    case 99:return 30;
    }
#endif
  return 113;
}

int Paigow::playerY(int p)
{
#ifdef GRAPHIC
  switch (p) {
    case 0:return 424;
    case 1:return 448;
    case 2:return 469;
    case 3:return 448;
    case 4:return 424;
    case 99:return 21;
    }
#endif
#ifdef CONSOLE
  switch (p) {
    case 0:return 3;
    case 1:return 14;
    case 2:return 17;
    case 3:return 14;
    case 4:return 3;
    case 99:return 5;
    }
#endif
  return 21;
}

int Paigow::playerBetX(int p)
{
#ifdef GRAPHIC
  switch (p) {
    case 0:return 62;
    case 1:return 219;
    case 2:return 388;
    case 3:return 559;
    case 4:return 716;
    case 99:return 33;
    }
#endif
#ifdef CONSOLE
  switch (p) {
    case 0:return 63;
    case 1:return 63;
    case 2:return 33;
    case 3:return 4;
    case 4:return 4;
    case 99:return 33;
    }
#endif
  return 33;
}

int Paigow::playerBetY(int p)
{
#ifdef GRAPHIC
  switch (p) {
    case 0:return 203;
    case 1:return 230;
    case 2:return 252;
    case 3:return 230;
    case 4:return 203;
    case 99:return 5;
    case 98:return 8;
    }
#endif
#ifdef CONSOLE
  switch (p) {
    case 0:return 2;
    case 1:return 13;
    case 2:return 16;
    case 3:return 13;
    case 4:return 2;
    case 99:return 5;
    case 98:return 8;
    }
#endif
  return 5;
}

void Paigow::splitHand(int *s1,int *s2,int p) {
  char flag;
  int  ups;
  int  pos;
  int  y,i;
  int  upCards[7];
  ups=0;
#ifdef GRAPHIC
  rcs_GC gc;
  rcs_Event event;
  for (i=0;i<7;i++) upCards[i]=0;
  flag=' ';
  while (flag==' ') {
    event=getEvent(display);
    if (event.type==EVENT_BUTTON_PRESS && event.d1==1 &&
        event.d2>playerX(p) && event.d2<playerX(p)+120 &&
        event.d3>playerY(p)+40 && event.d3<playerY(p)+70 &&
        ups==2) flag='X';
    if (event.type==EVENT_BUTTON_PRESS && event.d1==1)
      if (event.d2>playerX(p) && event.d2<playerX(p)+150 &&
          event.d3>playerY(p)-140 && event.d3<playerY(p)-20) {
        pos=event.d2-playerX(p)-1; pos /=15;
        if (pos>6) pos=6;
        y=players[p]->getHand(0)->cards[pos]->getY();
        if (y == playerY(p)-140) {
          y=playerY(p)-120;
          ups--;
          upCards[pos]=0;
          } else {
          y=playerY(p)-140;
          ups++;
          upCards[pos]=1;
          }
        players[p]->getHand(0)->cards[pos]->setPosition(playerX(p)+15*pos,y);
    gc=rcs_openGC(display,mainScreen);
    rcs_namedForeground(display,gc,"darkgreen");
    rcs_drawFilledBox(display,mainScreen,gc,playerX(p),playerY(p)-140,154,120);
    players[p]->getHand(0)->paint(display,mainScreen,gc,0);
    rcs_closeGC(display,gc);
    displayScreen();
      }
  
    }
  for (i=0;i<7;i++)
    if (upCards[i]==1) {
      *s1=i;
      upCards[i]=0;
      i=99;
      }
  for (i=0;i<7;i++)
    if (upCards[i]==1) {
      *s2=i;
      i=99;
      }
#endif
  }

void Paigow::showBetAmount() {
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

void Paigow::showPlayers() {
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


float Paigow::placeBet(int player) {
  float betReturn;
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
               if (betAmount<20) betAmount=20;
               showBetAmount();
               }
             if (event.d2>=522 && event.d2<546) {
               betAmount-=5;
               if (betAmount<20) betAmount=20;
               showBetAmount();
               }
             if (event.d2>=553 && event.d2<578) {
               betAmount-=10;
               if (betAmount<20) betAmount=20;
               showBetAmount();
               }
             if (event.d2>=584 && event.d2<609) {
               betAmount-=25;
               if (betAmount<20) betAmount=20;
               showBetAmount();
               }
             if (event.d2>=615 && event.d2<640) {
               betAmount-=50;
               if (betAmount<20) betAmount=20;
               showBetAmount();
               }
             if (event.d2>=645 && event.d2<671) {
               betAmount-=100;
               if (betAmount<20) betAmount=20;
               showBetAmount();
               }
             if (event.d2>=676 && event.d2<701) {
               betAmount-=500;
               if (betAmount<20) betAmount=20;
               showBetAmount();
               }
             if (event.d2>=708 && event.d2<733) {
               betAmount-=1000;
               if (betAmount<20) betAmount=20;
               showBetAmount();
               }
             if (event.d2>=739 && event.d2<765) {
               betAmount-=5000;
               if (betAmount<20) betAmount=20;
               showBetAmount();
               }
             if (event.d2>=771 && event.d2<796) {
               betAmount-=10000;
               if (betAmount<20) betAmount=20;
               showBetAmount();
               }
             }
           if (event.d1 == 1 &&
               event.d2>=playerBetX(player)-50 &&
               event.d2<=playerBetX(player)+50 &&
               event.d3>=playerBetY(player)-50 &&
               event.d3<=playerBetY(player)+50) {
             betReturn=players[player]->placeBet(betAmount,0,playerBetX(player),playerBetY(player));
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
#endif
#ifdef CONSOLE
        bet=1;
        while (bet>0 && bet<minBet) {
          GotoXY(playerX(i),playerY(i)+7);
          Output("                  ");
          GotoXY(playerX(i),playerY(i)+7);
          Output("Enter Bet :");
          Input(buffer);
          sscanf(buffer,"%f",&bet);
          }
        betReturn=players[i]->placeBet(bet,0,1,1);
        GotoXY(playerX(i),playerY(i)+7);
        Output("                       ");
        GotoXY(playerX(i),playerY(i)+7);
        Output("                       ");

        GotoXY(playerX(i),playerY(i)+6);
        sprintf(buffer,"%12.2f",players[i]->money());
        Output("Money $");
        Output(buffer);
        GotoXY(playerX(i),playerY(i)+1);
        sprintf(buffer,"%4.0f ",bet);
        Output(buffer);
#endif
  if (flag!='P' && flag!='D') return 0;
    else return betReturn;
  }
void Paigow::play()
{
  float bet;
  float betReturn;
#ifdef GRAPHIC
  rcs_GC gc;
  table=rcs_xpmToPixmap(display,mainWindow,paigow_xpm);
#endif
  bet=1;
  while (bet!=0) {
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    rcs_copyArea(display,table,mainScreen,gc,0,0,800,600,0,0);
    rcs_closeGC(display,gc);
    showBetAmount();
    displayScreen();
#endif
#ifdef CONSOLE
    ClrScr();
#endif
    deck->shuffle();
    for (i=0;i<5;i++) if (players[i]!=NULL) players[i]->clearAllBets();
    showPlayers();
    for (i=0;i<5;i++) if (players[i]!=NULL) {
      if (players[i]->playerType()=='H') {
        bet=placeBet(i);
        }
      else {
        betReturn=players[i]->placeBet(minBet,0,playerBetX(i),playerBetY(i));
#ifdef CONSOLE
        GotoXY(playerX(i),playerY(i)+6);
        sprintf(buffer,"%12.2f",players[i]->money());
        Output("Money $");
        Output(buffer);
        GotoXY(playerX(i),playerY(i)+1);
        sprintf(buffer,"%4.0f ",minBet);
        Output(buffer);
#endif
        }
#ifdef GRAPHIC
      showPlayers();
      players[i]->paintBets();
      displayScreen();
#endif
#ifdef CONSOLE
      players[i]->showBets();
#endif

      }
	if (betReturn) ;
    if (bet!=0) {
      round();
      }
    }
#ifdef GRAPHIC
  rcs_closePixmap(display,table);
#endif
}

void Paigow::round()
{
  int i,j;
  Hand* dealerHand2;
  Hand  pHand2;
  Hand* tHand;
#ifdef GRAPHIC
  rcs_GC gc;
#endif

  int   pSplit1,pSplit2;
  unsigned long DValue1;
  unsigned long DValue2;
  unsigned long PValue1;
  unsigned long PValue2;
  for (i=0;i<PLAYERS_PAIGOW;i++) if (players[i]!=NULL)
    players[i]->newHand(0);
  for (i=0;i<PLAYERS_PAIGOW;i++) if (players[i]!=NULL) {
    for (j=0;j<7;j++)  {
      players[i]->newCard(deck->dealCard(),0);
      players[i]->getHand(0)->cards[j]->setPosition(playerX(i)+j*15,playerY(i)-120);
      }
#ifdef CONSOLE
    GotoXY(playerX(i),playerY(i)+3);
#endif
    players[i]->getHand(0)->sort(0);
    for (j=0;j<7;j++) 
      players[i]->getHand(0)->cards[j]->setPosition(playerX(i)+j*15,playerY(i)-120);
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
    players[i]->getHand(0)->paint(display,mainScreen,gc,7);
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
    for (j=0;j<7;j++) players[i]->newCard(deck->dealCard(),0);
    GotoXY(playerX(i),playerY(i)+3);
    if (players[i]->playerType()=='H') {
      players[i]->getHand(0)->sort(0);
      players[i]->getHand(0)->display(0);
      }
     else
      players[i]->getHand(0)->display(7);
    Delay(1);
    }
*/
  for (j=0;j<7;j++) dealerHand->cards[j]=deck->dealCard();
  dealerHand->numCards=7;
  for (j=0;j<7;j++) 
    dealerHand->cards[j]->setPosition(playerX(99)+j*70,playerY(99));
  dealerHand->cards[5]->setPosition(playerX(99)+6*70,playerY(99));
  dealerHand->cards[6]->setPosition(playerX(99)+7*70,playerY(99));
#ifdef GRAPHIC
  gc=rcs_openGC(display,mainScreen);
  dealerHand->paint(display,mainScreen,gc,7);
  rcs_closeGC(display,gc);
  displayScreen();
#endif

#ifdef CONSOLE
  GotoXY(playerX(99),playerY(99)+1);
  dealerHand->display(7);
#endif
  Delay(1);
  for (i=0;i<PLAYERS_PAIGOW;i++) if (players[i]!=NULL) {
    if (players[i]->playerType()=='H') {
#ifdef GRAPHIC
      msgBox(playerX(i),playerY(i)+40,120,30,"Split Hand");
      splitHand(&pSplit1,&pSplit2,i);
#endif
#ifdef CONSOLE
      GotoXY(playerX(i),playerY(i)+4);
      Output("1  2  3  4  5  6  7      \n");
      pSplit1=-1; pSplit2=-1;
      while (pSplit1==-1 || pSplit2==-1) {
        GotoXY(playerX(i),playerY(i)+7);
        Output("                    ");
        GotoXY(playerX(i),playerY(i)+7);
        Output("Split hand: "); Input(buffer);
        for (j=0;j<strlen(buffer);j++)
          if (buffer[j]>='1' && buffer[j]<='7') {
            pSplit1=pSplit2;
            pSplit2=buffer[j]-0x31;
            }
        }
      GotoXY(playerX(i),playerY(i)+4);
      Output("                         \n");
      GotoXY(playerX(i),playerY(i)+7);
      Output("                    ");
#endif
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    rcs_copyArea(display,table,mainScreen,gc,playerX(i),playerY(i)+40,120,30,playerX(i),playerY(i)+40);
    rcs_closeGC(display,gc);
    showBetAmount();
    displayScreen();
#endif

      }
    }


  dealerHand2=dealerHand->paigowSplit(-1,-1);
  DValue1=dealerHand->paigowValue();
  DValue2=dealerHand2->paigowValue();
  for (j=0;j<5;j++) 
    dealerHand->cards[j]->setPosition(playerX(99)+j*70,playerY(99));
  for (j=0;j<2;j++) 
    dealerHand2->cards[j]->setPosition(playerX(99)+j*70+70*6,playerY(99));
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    dealerHand->paint(display,mainScreen,gc,0);
    dealerHand2->paint(display,mainScreen,gc,0);
    rcs_closeGC(display,gc);
    displayScreen();
#endif

#ifdef CONSOLE
  GotoXY(playerX(99),playerY(99)+1);
  Output("                         \n");
  GotoXY(playerX(99),playerY(99)+1);
  dealerHand->display(0);
  GotoXY(playerX(99),playerY(99));
  dealerHand2->display(0);
#endif
  Delay(1);
  for (i=0;i<PLAYERS_PAIGOW;i++) if (players[i]!=NULL) {
#ifdef CONSOLE
    GotoXY(playerX(i),playerY(i)+3);
    Output("                         \n");
    GotoXY(playerX(i),playerY(i)+3);
#endif
    if (players[i]->playerType()=='H') {
      tHand=players[i]->getHand(0)->paigowSplit(pSplit1,pSplit2);
      } else {
      tHand=players[i]->getHand(0)->paigowSplit(-1,-1);
     }
      PValue1=players[i]->getHand(0)->paigowValue();
      PValue2=tHand->paigowValue();
      for (j=0;j<5;j++)
        players[i]->getHand(0)->cards[j]->setPosition(playerX(i)+j*15,playerY(i)-120);
      for (j=0;j<2;j++)
        tHand->cards[j]->setPosition(playerX(i)+j*15+15*5,playerY(i)-140);
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    rcs_namedForeground(display,gc,"darkgreen");
    rcs_drawFilledBox(display,mainScreen,gc,playerX(i),playerY(i)-140,154,120);
    players[i]->getHand(0)->paint(display,mainScreen,gc,0);
    tHand->paint(display,mainScreen,gc,0);
    rcs_closeGC(display,gc);
    displayScreen();

#endif
#ifdef CONSOLE
      players[i]->getHand(0)->display(0);
      GotoXY(playerX(i),playerY(i)+2);
      tHand->display(0);
#endif
      tHand->deleteHand(tHand);

#ifdef CONSOLE
    GotoXY(playerX(i)+20,playerY(i)+3);
#endif
    if (PValue1>DValue1)
#ifdef GRAPHIC
      msgBox(playerX(i),playerY(i)-60,60,30,"Wins");
#endif
#ifdef CONSOLE
      Output("<-W");
#endif
    else
#ifdef GRAPHIC
      msgBox(playerX(i),playerY(i)-60,60,30,"Loses");
#endif
#ifdef CONSOLE
      Output("<-L");
#endif
    GotoXY(playerX(i)+20,playerY(i)+2);
    if (PValue2>DValue2)
#ifdef GRAPHIC
      msgBox(playerX(i)+5*15,playerY(i)-80,60,30,"Wins");
#endif
#ifdef CONSOLE
      Output("<-W");
#endif
    else
#ifdef GRAPHIC
      msgBox(playerX(i)+5*15,playerY(i)-80,60,30,"Loses");
#endif
#ifdef CONSOLE
      Output("<-L");
#endif

    if (PValue1>PValue2 && PValue1>DValue1 && PValue2>DValue2) {
#ifdef CONSOLE
      GotoXY(playerX(i)+7,playerY(i)+1);
      winnings=(players[i]->getHandBet(0)*0.95);
      winnings=floor(winnings);
      sprintf(buffer,"%4.0f ",winnings);
      Output(buffer);
#endif
      players[i]->winHandBets(0,0.95);
      }
    else if (PValue1>PValue2 &&
             (PValue1>DValue1 || PValue2>DValue2)) {
      players[i]->winHandBets(0,0);
      } else {
#ifdef CONSOLE
      GotoXY(playerX(i),playerY(i)+1);
      Output("      ");
#endif
      players[i]->loseHandBets(0);
      }
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    rcs_copyArea(display,table,mainScreen,gc,playerBetX(i)-50,playerBetY(i)-70,120,100,playerBetX(i)-50,playerBetY(i)-70);
    rcs_closeGC(display,gc);
    players[i]->paintBets();
    displayScreen();
    showPlayers();
#endif
#ifdef CONSOLE
    players[i]->showBets();
#endif

    Delay(1);
    }
//Input(buffer);
  Delay(5);
  dealerHand2->deleteHand(dealerHand2);
}
