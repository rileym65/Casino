#include <stdlib.h>
#include "header.h"
#include "poker.h"
#include "wildholdem.h"

#ifdef GRAPHIC
#include "images/wildholdem.xpm"
#endif

WildHoldem::WildHoldem(int decks,int jokers,float minbet):
  Poker(decks,jokers,minbet) {
  betAmount=1;
  }

void WildHoldem::clearBets(int p) {
#ifdef GRAPHIC
  rcs_GC gc;
  gc=rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"black");
  rcs_copyArea(display,table,mainScreen,gc,playerBetX(p)-80,playerBetY(p)-90,
               140,217,playerBetX(p)-80,playerBetY(p)-90);
  rcs_closeGC(display,gc);
#endif
  }

int WildHoldem::playerX(int p)
{
#ifdef GRAPHIC
  switch (p) {
    case 0:return 9;
    case 1:return 166;
    case 2:return 334;
    case 3:return 504;
    case 4:return 662;
    case 99:return 325;
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
  return 325;
}

int WildHoldem::playerY(int p)
{
#ifdef GRAPHIC
  switch (p) {
    case 0:return 464;
    case 1:return 488;
    case 2:return 509;
    case 3:return 488;
    case 4:return 464;
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

int WildHoldem::playerBetX(int p)
{
#ifdef GRAPHIC
  switch (p) {
    case 0:return 82;
    case 1:return 239;
    case 2:return 408;
    case 3:return 579;
    case 4:return 736;
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

int WildHoldem::playerBetY(int p)
{
#ifdef GRAPHIC
  switch (p) {
    case 0:return 213;
    case 1:return 240;
    case 2:return 262;
    case 3:return 240;
    case 4:return 213;
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

void WildHoldem::showBetAmount() {
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

void WildHoldem::showPlayers() {
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

float WildHoldem::placeBet(int player) {
  float betReturn;
  char  flag;
  char  betFlags;
#ifdef GRAPHIC
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
               event.d3<=playerBetY(player)+50) {
        betReturn=players[player]->placeBet(betAmount,0,playerBetX(player)-20,playerBetY(player)-50);
//        betReturn=players[player]->placeBet(betAmount,1,playerBetX(player)-50,playerBetY(player)+15);
//        betReturn=players[player]->placeBet(betAmount,2,playerBetX(player)+20,playerBetY(player)+15);
             showPlayers();
             players[i]->paintBets();
             displayScreen();
             flag='P';
             }
/*
           if (event.d1 == 1 && betFlags==1 &&
               event.d2>=playerBetX(player)-30 &&
               event.d2<=playerBetX(player)+30 &&
               event.d3>=playerBetY(player)+70 &&
               event.d3<=playerBetY(player)+130) {
             betReturn=players[player]->placeBet(1,3,playerBetX(player)-20,playerBetY(player)+85);
             betFlags |= 2;
             progressives[PROG_CARIB]+=.75;
             showPlayers();
             players[i]->paintBets();
             displayScreen();
             if (betFlags == 3) flag='P';
             }
*/
           break;
      }
    }
  gc=rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"darkgreen");
  rcs_drawFilledBox(display,mainScreen,gc,10,566,80,29);
  rcs_drawFilledBox(display,mainScreen,gc,210,566,80,29);
  rcs_closeGC(display,gc);
  displayScreen();
#endif
#ifdef CONSOLE
        GotoXY(playerX(i),playerY(i)+7);
        Output("Enter Bet :");
        Input(buffer);
        sscanf(buffer,"%f",&bet);
        betReturn=players[i]->placeBet(bet,0,1,1);
        betReturn=players[i]->placeBet(bet,1,1,1);
        betReturn=players[i]->placeBet(bet,2,1,1);
        GotoXY(playerX(i),playerY(i)+7);
        Output("                       ");
        GotoXY(playerX(i),playerY(i)+1);
        GotoXY(playerX(i),playerY(i)+7);
        Output("Tourn. Bet (y/n):");
        Input(buffer);
        if (buffer[0]=='y') {
          betReturn=players[i]->placeBet(1,3,1,1);
          GotoXY(playerX(i)+17,playerY(i)+1);
          Output("*");
          }
        GotoXY(playerX(i),playerY(i)+7);
        Output("                       ");

        GotoXY(playerX(i),playerY(i)+6);
        sprintf(buffer,"%12.2f",players[i]->money());
        Output("Money $");
        Output(buffer);
        GotoXY(playerX(i),playerY(i)+1);
        sprintf(buffer,"%4.0f %4.0f %4.0f",bet,bet,bet);
        Output(buffer);
#endif
  if (betFlags != 0) flag='P';
  if (flag!='P' && flag!='D') return 0;
    else return betReturn;
  }

void WildHoldem::play()
{
  float bet;
  float betReturn;
#ifdef GRAPHIC
  rcs_GC gc;
  table=rcs_xpmToPixmap(display,mainWindow,wildholdem_xpm);
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
        betReturn=players[i]->placeBet(minBet,0,playerBetX(i)-20,playerBetY(i)-50);
//        betReturn=players[i]->placeBet(minBet,1,playerBetX(i)-50,playerBetY(i)+15);
//        betReturn=players[i]->placeBet(minBet,2,playerBetX(i)+20,playerBetY(i)+15);
//        betReturn=players[i]->placeBet(1,3,playerBetX(i)-20,playerBetY(i)+85);
#ifdef CONSOLE
          GotoXY(playerX(i)+17,playerY(i)+1);
          Output("*");
        GotoXY(playerX(i),playerY(i)+6);
        sprintf(buffer,"%12.2f",players[i]->money());
        Output("Money $");
        Output(buffer);
        GotoXY(playerX(i),playerY(i)+1);
        sprintf(buffer,"%4.0f %4.0f %4.0f",minBet,minBet,minBet);
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

void WildHoldem::round()
{
  int i,j;
  Card *c1,*c2,*c3,*c4;
  unsigned long high;
//  float betReturn;
  int   folded[5];
  Hand* pHand;
#ifdef GRAPHIC
  rcs_GC gc;
#endif
  for (i=0;i<PLAYERS_WILD;i++) folded[i]=0;
  for (i=0;i<PLAYERS_WILD;i++) if (players[i]!=NULL)
    players[i]->newHand(0);
  for (i=0;i<PLAYERS_WILD;i++) if (players[i]!=NULL) {
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
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    rcs_closeGC(display,gc);
    displayScreen();
#endif
#ifdef CONSOLE
  GotoXY(playerX(99),playerY(99));
#endif
   Delay(1);

  for (i=0;i<PLAYERS_WILD;i++) if (players[i]!=NULL && folded[i]==0) {
    if (players[i]->playerType()=='H') {
#ifdef GRAPHIC
      if (actionBox(playerX(i),playerY(i),130,70,"Continue?","Yes","No")==0) {
        players[i]->placeBet(players[i]->getHandBet(0),1,playerBetX(i)-50,playerBetY(i)+15);
        } else {
        players[i]->loseHandBets(0);
        gc=rcs_openGC(display,mainScreen);
        rcs_copyArea(display,table,mainScreen,gc,playerX(i),playerY(i)-120,130,120,playerX(i),playerY(i)-120);
        rcs_closeGC(display,gc);
        folded[i]=1;
        }
/*
      gc=rcs_openGC(display,mainScreen);
      rcs_copyArea(display,table,mainScreen,gc,playerX(i),playerY(i)-120,130,120,playerX(i),playerY(i)-120);
      rcs_closeGC(display,gc);
*/
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
      if (high>PK_PAIR ||
          c1->value()==2 || c2->value()==2 || c3->value()==2 ||
          (c1->getSuit()==c2->getSuit() && c2->getSuit()==c3->getSuit() )) {
        players[i]->placeBet(players[i]->getHandBet(0),1,playerBetX(i)-50,playerBetY(i)+15);
        } else {
        players[i]->loseHandBets(0);
        gc=rcs_openGC(display,mainScreen);
        rcs_copyArea(display,table,mainScreen,gc,playerX(i),playerY(i)-120,130,120,playerX(i),playerY(i)-120);
        rcs_closeGC(display,gc);
        folded[i]=1;
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
    rcs_closeGC(display,gc);
    displayScreen();
#endif
#ifdef CONSOLE
  GotoXY(playerX(99),playerY(99));
#endif
  Delay(1);

/* ******************* Deal first card **************** */
  for (i=0;i<PLAYERS_WILD;i++) if (players[i]!=NULL && folded[i]==0) {
      players[i]->newCard(deck->dealCard(),0);
      players[i]->getHand(0)->cards[3]->setPosition(playerX(i)+3*15,playerY(i)-120);
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
    players[i]->getHand(0)->paint(display,mainScreen,gc,4);
    rcs_closeGC(display,gc);
    displayScreen();
#endif
#ifdef CONSOLE
      players[i]->getHand(0)->display(3);
#endif
      }
    Delay(1);
    }

/* ***************** round 2 ************** */
  for (i=0;i<PLAYERS_WILD;i++) if (players[i]!=NULL && folded[i]==0) {
    if (players[i]->playerType()=='H') {
#ifdef GRAPHIC
      if (actionBox(playerX(i),playerY(i),130,70,"Continue?","Yes","No")==0) {
        players[i]->placeBet(players[i]->getHandBet(0)*2,2,playerBetX(i)+20,playerBetY(i)+15);
        } else {
        players[i]->loseHandBets(0);
        players[i]->loseHandBets(1);
        gc=rcs_openGC(display,mainScreen);
        rcs_copyArea(display,table,mainScreen,gc,playerX(i),playerY(i)-120,130,120,playerX(i),playerY(i)-120);
        rcs_closeGC(display,gc);
        folded[i]=1;
        }
/*
      gc=rcs_openGC(display,mainScreen);
      rcs_copyArea(display,table,mainScreen,gc,playerX(i),playerY(i)-120,130,120,playerX(i),playerY(i)-120);
      rcs_closeGC(display,gc);
*/
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
      c4=pHand->cards[3];
      high=pHand->pokerValue(5,0);
      pHand->cards[0]=c1; pHand->cards[1]=c2; pHand->cards[2]=c3;
      pHand->cards[3]=c4;
      if (high>PK_PAIR ||
          c1->value()==2 || c2->value()==2 || c3->value()==2 || c4->value()==2 ||
          (c1->getSuit()==c2->getSuit() && c2->getSuit()==c3->getSuit() &&
           c3->getSuit()==c4->getSuit() )) {
        players[i]->placeBet(players[i]->getHandBet(0)*2,2,playerBetX(i)+20,playerBetY(i)+15);
        } else {
        players[i]->loseHandBets(0);
        players[i]->loseHandBets(1);
        gc=rcs_openGC(display,mainScreen);
        rcs_copyArea(display,table,mainScreen,gc,playerX(i),playerY(i)-120,130,120,playerX(i),playerY(i)-120);
        rcs_closeGC(display,gc);
        folded[i]=1;
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

/* ******************* Deal Second card **************** */
  for (i=0;i<PLAYERS_WILD;i++) if (players[i]!=NULL && folded[i]==0) {
      players[i]->newCard(deck->dealCard(),0);
      players[i]->getHand(0)->cards[4]->setPosition(playerX(i)+4*15,playerY(i)-120);
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
    players[i]->getHand(0)->paint(display,mainScreen,gc,5);
    rcs_closeGC(display,gc);
    displayScreen();
#endif
#ifdef CONSOLE
      players[i]->getHand(0)->display(3);
#endif
      }
    Delay(1);
    }






#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    rcs_closeGC(display,gc);
    displayScreen();
#endif
#ifdef CONSOLE
  GotoXY(playerX(99),playerY(99));
#endif
  Delay(1);
  for (i=0;i<PLAYERS_WILD;i++) if (players[i]!=NULL && folded[i]==0) {
    pHand=players[i]->getHand(0);
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
    high=pHand->pokerValue(5,2);
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
    if (high>(PK_PAIR|(14l<<24)) && high<PK_2_PAIR) {
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
      players[i]->winHandBets(0,0.25);
      players[i]->winHandBets(1,0.25);
      players[i]->winHandBets(2,0.25);
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
      players[i]->winHandBets(0,1);
      players[i]->winHandBets(1,1);
      players[i]->winHandBets(2,1);
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
      players[i]->winHandBets(0,1);
      players[i]->winHandBets(1,1);
      players[i]->winHandBets(2,1);
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
      players[i]->winHandBets(0,3);
      players[i]->winHandBets(1,3);
      players[i]->winHandBets(2,3);
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
      players[i]->winHandBets(0,4);
      players[i]->winHandBets(1,4);
      players[i]->winHandBets(2,4);
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
      players[i]->winHandBets(0,4);
      players[i]->winHandBets(1,4);
      players[i]->winHandBets(2,4);
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
      players[i]->winHandBets(0,4);
      players[i]->winHandBets(1,4);
      players[i]->winHandBets(2,4);
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
      players[i]->winHandBets(0,10);
      players[i]->winHandBets(1,10);
      players[i]->winHandBets(2,10);
      }
    else if ((high&(15l<<28))==PK_FIVE) {
#ifdef GRAPHIC
      msgBox(playerX(i),playerY(i)-40,120,30,"5 of a Kind");
#endif
#ifdef CONSOLE
      Output("*Straight Flush*");
      GotoXY(playerX(i),playerY(i));
      sprintf(buffer,"%4.0f %4.0f %4.0f ",players[i]->getHandBet(0)*200,
        players[i]->getHandBet(1)*200,players[i]->getHandBet(2)*200);
      Output(buffer);
#endif
      players[i]->winHandBets(0,20);
      players[i]->winHandBets(1,20);
      players[i]->winHandBets(2,20);
      }
    else if ((high&(15l<<28))==PK_ROYALWLD) {
#ifdef GRAPHIC
      msgBox(playerX(i),playerY(i)-40,120,30,"Wild Royal");
#endif
#ifdef CONSOLE
      Output("*Straight Flush*");
      GotoXY(playerX(i),playerY(i));
      sprintf(buffer,"%4.0f %4.0f %4.0f ",players[i]->getHandBet(0)*200,
        players[i]->getHandBet(1)*200,players[i]->getHandBet(2)*200);
      Output(buffer);
#endif
      players[i]->winHandBets(0,30);
      players[i]->winHandBets(1,30);
      players[i]->winHandBets(2,30);
      }
    else if ((high&(15l<<28))==PK_FOURWLD) {
#ifdef GRAPHIC
      msgBox(playerX(i),playerY(i)-40,120,30,"4 Deuces");
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
