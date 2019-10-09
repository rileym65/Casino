#include <stdlib.h>
#include "header.h"
#include "bacc.h"

#define PLAYERS 5

#ifdef GRAPHIC
#include "images/bacc.xpm"
#endif

Bacc::Bacc(int decks,int jokers,float minbet):
  CardGames(decks,jokers,minbet) {
  betAmount=minbet;
  }

int Bacc::playerX(int p)
{
  switch (p) {
    case 0:return 30;
    case 1:return 170;
    case 2:return 310;
    case 3:return 485;
    case 4:return 640;
    case 98:return 440;
    case 99:return 157;
    }
  return 157;
}

int Bacc::playerY(int p)
{
  switch (p) {
    case 0:return 370;
    case 1:return 375;
    case 2:return 380;
    case 3:return 376;
    case 4:return 370;
    case 98:return 36;
    case 99:return 36;
    }
  return 36;
}

int Bacc::playerBetX(int p)
{
  switch (p) {
    case 0:return 83;
    case 1:return 213;
    case 2:return 343;
    case 3:return 513;
    case 4:return 653;
    case 98:return 33;
    case 99:return 33;
    }
  return 33;
}

int Bacc::playerBetY(int p)
{
  switch (p) {
    case 0:return 303;
    case 1:return 318;
    case 2:return 323;
    case 3:return 318;
    case 4:return 303;
    case 99:return 5;
    case 98:return 8;
    }
  return 5;
}

int Bacc::playerBetXD(int p)
{
  switch (p) {
    case 0:return 133;
    case 1:return 243;
    case 2:return 353;
    case 3:return 503;
    case 4:return 623;
    case 98:return 33;
    case 99:return 33;
    }
  return 33;
}

int Bacc::playerBetYD(int p)
{
  switch (p) {
    case 0:return 213;
    case 1:return 228;
    case 2:return 233;
    case 3:return 228;
    case 4:return 213;
    case 99:return 5;
    case 98:return 8;
    }
  return 5;
}

void Bacc::showBetAmount() {
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

void Bacc::showPlayers() {
  int i;
  rcs_GC gc;
  rcs_Font font;
    for (i=0;i<PLAYERS;i++) if (players[i]!=NULL) {
      gc=rcs_openGC(display,mainScreen);
      font=rcs_openFont(display,PLAYER_FONT);
      rcs_setFont(display,gc,font);
      rcs_namedForeground(display,gc,"darkgreen");
      rcs_drawFilledBox(display,mainScreen,gc,playerX(i),playerY(i),125,60);
      rcs_namedForeground(display,gc,"yellow");
      rcs_drawString(display,mainScreen,gc,playerX(i),playerY(i),
                     players[i]->getName());
      sprintf(buffer,"Money $%12.2f",players[i]->money());
      rcs_drawString(display,mainScreen,gc,playerX(i),playerY(i)+20,buffer);
      sprintf(buffer,"Comm: $%12.2f",comms[i]);
      rcs_drawString(display,mainScreen,gc,playerX(i),playerY(i)+40,buffer);
      rcs_closeFont(display,font);
      rcs_closeGC(display,gc);
      }
    displayScreen();
  }

float Bacc::placeBet(int player) {
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
               bets[player]='X';
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
           if (event.d1 == 1 && event.d3>=251 && event.d3<=353 &&
               betAmount >= minBet) {
             betReturn=players[player]->placeBet(betAmount,0,playerBetX(player),playerBetY(player));
             bets[player]='P';
             flag='P';
             }
           if (event.d1 == 1 && event.d3>=162 && event.d3<=251 &&
               betAmount >= minBet) {
             betReturn=players[player]->placeBet(betAmount,1,playerBetXD(player),playerBetYD(player));
             bets[player]='D';
             flag='D';
             }
           break;
      }
    }
  gc=rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"darkgreen");
  rcs_drawFilledBox(display,mainScreen,gc,10,566,80,29);
  rcs_closeGC(display,gc);
  displayScreen();
  if (bets[player]!='P' && bets[player]!='D') return 0;
    else return betReturn;
  }

void Bacc::play()
{
  float bet;
  float betReturn;
  int i,j;
  rcs_GC   gc;
  bet=1;
  deck->shuffle();
  for (i=0;i<PLAYERS_BACC;i++) comms[i]=0;
  table=rcs_xpmToPixmap(display,mainWindow,bacc_xpm);
  while (bet!=0) {
    gc=rcs_openGC(display,mainScreen);
    rcs_copyArea(display,table,mainScreen,gc,0,0,800,600,0,0);
    rcs_closeGC(display,gc);
    showBetAmount();
//    displayScreen();
    for (i=0;i<PLAYERS;i++) if (players[i]!=NULL) players[i]->clearAllBets();
    showPlayers();
    for (i=0;i<PLAYERS;i++) if (players[i]!=NULL) {
      if (players[i]->playerType()=='H') {
        bet=placeBet(i);
        }
      else {
        j=Random(3);
        if (j==1) {
          betReturn=players[i]->placeBet(minBet,1,playerBetXD(i),
                                         playerBetYD(i));
          bets[i]='D';
          }
        else {
          betReturn=players[i]->placeBet(minBet,0,playerBetX(i),
                                         playerBetY(i));
          bets[i]='P';
          }
        showPlayers();
        }
      players[i]->paintBets();
      displayScreen();
      }
    if (betReturn) ;
    if (bet!=0) {
      round();
      }
    }
  for (i=0;i<PLAYERS;i++) if (players[i]!=NULL) {
    betReturn=players[i]->placeBet(comms[i],1,playerBetXD(i),
                                         playerBetYD(i));
    players[i]->loseHandBets(1);
    }
}

void Bacc::round()
{
  Hand dHand;
  Hand pHand;
  int  dCount;
  int  pCount;
  int  Winner;
  int  Draw;
  Card* card;
  float Amount;
  rcs_GC   gc;
  if (deck->cardsLeft()<22) {
    GotoXY(playerX(99),playerY(99));
    Output("Shuffling...");
    deck->shuffle();
    Delay(1);
    GotoXY(playerX(99),playerY(99));
    Output("              ");
    }
  dHand.numCards=0;
  pHand.numCards=0;
  pHand.cards[0]=deck->dealCard();
  pHand.cards[0]->setPosition(playerX(98),playerY(98));
  pHand.numCards++;
  gc=rcs_openGC(display,mainScreen);
  pHand.paint(display,mainScreen,gc,0);
  rcs_closeGC(display,gc);
  displayScreen();
  Delay(1);
  dHand.cards[0]=deck->dealCard();
  dHand.cards[0]->setPosition(playerX(99),playerY(99));
  dHand.numCards++;
  gc=rcs_openGC(display,mainScreen);
  dHand.paint(display,mainScreen,gc,0);
  rcs_closeGC(display,gc);
  displayScreen();
  Delay(1);
  pHand.cards[1]=deck->dealCard();
  pHand.cards[1]->setPosition(playerX(98)+70,playerY(98));
  pHand.numCards++;
  gc=rcs_openGC(display,mainScreen);
  pHand.paint(display,mainScreen,gc,0);
  rcs_closeGC(display,gc);
  displayScreen();
  Delay(1);
  dHand.cards[1]=deck->dealCard();
  dHand.cards[1]->setPosition(playerX(99)+70,playerY(99));
  dHand.numCards++;
  gc=rcs_openGC(display,mainScreen);
  dHand.paint(display,mainScreen,gc,0);
  rcs_closeGC(display,gc);
  displayScreen();
  Delay(1);
  dCount=dHand.baccValue();
  pCount=pHand.baccValue();
  if (dCount>7 || pCount>7) {
    if (dCount>7) {
      }
    if (pCount>7) {
      }
    if (dCount>pCount) Winner=1;
    else if (pCount>dCount) Winner=0;
    else Winner=2;
    }
  else {
    if (pCount<6) {
      card=deck->dealCard();
      pHand.cards[2]=card;
      pHand.cards[2]->setPosition(playerX(98)+140,playerY(98));
      pHand.numCards++;
      gc=rcs_openGC(display,mainScreen);
      pHand.paint(display,mainScreen,gc,0);
      rcs_closeGC(display,gc);
      displayScreen();
      Delay(1);
      Draw=0;
      if (dCount<3) Draw=1;
      else if (dCount==3 && card->value()!=8) Draw=1;
      else if (dCount==4 && card->value()>1 && card->value()<8) Draw=1;
      else if (dCount==5 && card->value()>3 && card->value()<8) Draw=1;
      else if (dCount==6 && card->value()>5 && card->value()<8) Draw=1;
      if (Draw==1) {
        dHand.cards[2]=deck->dealCard();
        dHand.cards[2]->setPosition(playerX(99)+140,playerY(99));
        dHand.numCards++;
        gc=rcs_openGC(display,mainScreen);
        dHand.paint(display,mainScreen,gc,0);
        rcs_closeGC(display,gc);
        displayScreen();
        Delay(1);
        }
      }
      else if (dCount<6) {
        dHand.cards[2]=deck->dealCard();
        dHand.cards[2]->setPosition(playerX(99)+140,playerY(99));
        dHand.numCards++;
        gc=rcs_openGC(display,mainScreen);
        dHand.paint(display,mainScreen,gc,0);
        rcs_closeGC(display,gc);
        displayScreen();
        Delay(1);
        }
    dCount=dHand.baccValue();
    pCount=pHand.baccValue();
    if (dCount>pCount) Winner=1;
    else if (pCount>dCount) Winner=0;
    else Winner=2;
    }
  for (i=0;i<PLAYERS_BACC;i++) if (players[i]!=NULL) {
    GotoXY(playerBetX(i)+6,playerBetY(i)-1);
    if (Winner==2) {
      players[i]->winHandBets(0,0);
      players[i]->winHandBets(1,0);
      }
    else if (Winner==0 && bets[i]=='P') {
      players[i]->winHandBets(0,1);
      players[i]->loseHandBets(1);
      }
    else if (Winner==1 && bets[i]=='D') {
      Amount=players[i]->getHandBet(1);
      comms[i]+=(Amount*0.05);
      players[i]->winHandBets(1,1);
      players[i]->loseHandBets(0);
      }
    else {
//      players[i]->winHandBets(1,1);
      players[i]->adjustStrategy();
      players[i]->loseHandBets(0);
      players[i]->loseHandBets(1);
      }
    }
  gc=rcs_openGC(display,mainScreen);
  rcs_copyArea(display,table,mainScreen,gc,0,0,800,600,0,0);
  dHand.paint(display,mainScreen,gc,0);
  pHand.paint(display,mainScreen,gc,0);
  rcs_closeGC(display,gc);
  showPlayers();
  showBetAmount();
  for (i=0;i<PLAYERS_BACC;i++) if (players[i]!=NULL) players[i]->paintBets();
  displayScreen();

  Delay(5);
}
