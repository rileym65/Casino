#include <stdlib.h>
#include <math.h>
#include "header.h"
#include "poker.h"
#include "paigowtiles.h"

#ifdef GRAPHIC
#include "images/paigowtiles.xpm"
#include "images/paigowranks.xpm"
#endif

PaigowTiles::PaigowTiles(int decks,int jokers,float minbet):
  CardGames(decks,jokers,minbet) {
  int i;
  betAmount=20;
  tiles=new PaigowDeck();
  tiles->shuffle();
  dHand=NULL;
  for (i=0;i<5;i++) pHand[i]=NULL;
  for (i=0;i<5;i++) sHand[i]=NULL;
  }

PaigowTiles::~PaigowTiles() {
  delete(tiles);
  }

int PaigowTiles::playerX(int p)
{
#ifdef GRAPHIC
  switch (p) {
    case 0:return 9;
    case 1:return 166;
    case 2:return 334;
    case 3:return 504;
    case 4:return 662;
    case 99:return 340;
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
  return 340;
}

int PaigowTiles::playerY(int p)
{
#ifdef GRAPHIC
  switch (p) {
    case 0:return 424;
    case 1:return 448;
    case 2:return 469;
    case 3:return 448;
    case 4:return 424;
    case 99:return 90;
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
  return 90;
}

int PaigowTiles::playerBetX(int p)
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

int PaigowTiles::playerBetY(int p)
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

void PaigowTiles::swapHands(int p) {
  PaigowTile *l1,*l2, *h1,*h2;
  l1=sHand[p]->removeTile(0);
  l2=sHand[p]->removeTile(0);
  h1=pHand[p]->removeTile(0);
  h2=pHand[p]->removeTile(0);
  pHand[p]->addTile(l1);
  pHand[p]->addTile(l2);
  sHand[p]->addTile(h1);
  sHand[p]->addTile(h2);
  }

void PaigowTiles::splitHand(int p) {
  char flag;
  int  pos;
#ifdef GRAPHIC
  rcs_GC gc;
  rcs_Pixmap backing;
  rcs_Event event;
  gc = rcs_openGC(display,mainWindow);
  backing = rcs_createPixmap(display,mainWindow,508,239);
  rcs_copyArea(display,mainScreen,backing,gc,292,0,508,239,0,0);
  rcs_closeGC(display,gc);
  msgBox(700,20,80,30,"Ranks");
  msgBox(playerX(p),playerY(p)+40,120,30,"Split Hand");
  flag=' ';
  sHand[p]=new PaigowHand();
  sHand[p]->setDirection('H');
  sHand[p]->setPosition(playerX(p),playerY(p)-140);
  while (flag==' ') {
    event=getEvent(display);
    if (event.type==EVENT_BUTTON_PRESS && event.d1==1 &&
        event.d2>playerX(p) && event.d2<playerX(p)+120 &&
        event.d3>playerY(p)+40 && event.d3<playerY(p)+70 &&
        pHand[p]->getNumTiles()==2 && sHand[p]->getNumTiles()==2) flag='X';
    if (event.type==EVENT_BUTTON_PRESS && event.d1==1)
      if (event.d2>playerX(p) && event.d2<playerX(p)+50 &&
          event.d3>playerY(p)-140 && event.d3<playerY(p)-86) {
        pos=event.d3-(playerY(p)-140); pos /=28;
        if (pos>1) pos=1;
        if (pos==1 && sHand[p]->getNumTiles()==2) {
          pHand[p]->addTile(sHand[p]->removeTile(pos));
          }
        if (pos==0 && sHand[p]->getNumTiles()>0) {
          pHand[p]->addTile(sHand[p]->removeTile(pos));
          }
      gc=rcs_openGC(display,mainScreen);
      rcs_namedForeground(display,gc,"darkgreen");
      rcs_drawFilledBox(display,mainScreen,gc,playerX(p)-1,playerY(p)-141,154,122);
      pHand[p]->paint(display,mainScreen,gc);
      sHand[p]->paint(display,mainScreen,gc);
      rcs_closeGC(display,gc);
      displayScreen();
      }
    if (event.type==EVENT_BUTTON_PRESS && event.d1==1) {
      if (event.d2>700 && event.d2<780 &&
          event.d3>20 && event.d3<50) {
        gc = rcs_openGC(display,mainScreen);
        rcs_drawPixmap(display,mainScreen,gc,292,0,paigowranks_xpm);
        rcs_closeGC(display,gc);
        displayScreen();
        }
      if (event.d2>playerX(p) && event.d2<playerX(p)+112 &&
          event.d3>playerY(p)-70 && event.d3<playerY(p)-20) {
        pos=event.d2-playerX(p)-1; pos /=28;
        if (pos>3) pos=3;
        if (pos==3 && pHand[p]->getNumTiles()==4 && sHand[p]->getNumTiles()<2) {
          sHand[p]->addTile(pHand[p]->removeTile(pos));
          }
        if (pos==2 && pHand[p]->getNumTiles()>2 && sHand[p]->getNumTiles()<2) {
          sHand[p]->addTile(pHand[p]->removeTile(pos));
          }
        if (pos<2 && sHand[p]->getNumTiles()<2) {
          sHand[p]->addTile(pHand[p]->removeTile(pos));
          }
        }
      gc=rcs_openGC(display,mainScreen);
      rcs_namedForeground(display,gc,"darkgreen");
      rcs_drawFilledBox(display,mainScreen,gc,playerX(p),playerY(p)-140,154,122);
      pHand[p]->paint(display,mainScreen,gc);
      sHand[p]->paint(display,mainScreen,gc);
      rcs_closeGC(display,gc);
      displayScreen();
      }
  
    }
  gc=rcs_openGC(display,mainScreen);
  if (pHand[p]->getRank() > sHand[p]->getRank()) {
    swapHands(p);
    pHand[p]->paint(display,mainScreen,gc);
    sHand[p]->paint(display,mainScreen,gc);
    }
  rcs_copyArea(display,backing,mainScreen,gc,0,0,508,239,292,0);
  rcs_copyArea(display,table,mainScreen,gc,playerX(p),playerY(p)+40,120,30,playerX(p),playerY(p)+40);
  rcs_closeGC(display,gc);
  showBetAmount();
  displayScreen();
  rcs_closePixmap(display,backing);
#endif
  }

void PaigowTiles::showBetAmount() {
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

void PaigowTiles::showPlayers() {
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


float PaigowTiles::placeBet(int player) {
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
void PaigowTiles::play()
{
  float bet;
  float betReturn;
#ifdef GRAPHIC
  rcs_GC gc;
  table=rcs_xpmToPixmap(display,mainWindow,paigowtiles_xpm);
#endif
printf("AAA\n");
  bet=1;
  while (bet!=0) {
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    rcs_copyArea(display,table,mainScreen,gc,0,0,800,600,0,0);
    showBetAmount();
    displayScreen();
  rcs_closeGC(display,gc);
#endif
#ifdef CONSOLE
    ClrScr();
#endif
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

void PaigowTiles::round() {
  int i,j;
  rcs_GC gc;
  tiles->shuffle();
  for (i=0;i<5;i++)
    if (pHand[i] != NULL) {
      delete(pHand[i]);
      pHand[i]=NULL;
      }
  for (i=0;i<5;i++)
    if (sHand[i] != NULL) {
      delete(sHand[i]);
      sHand[i]=NULL;
      }
/* deal player tiles */
  for (i=0;i<5;i++) if (players[i] != NULL) {
    pHand[i]=new PaigowHand();
    pHand[i]->setPosition(playerX(i),playerY(i)-70);
    for (j=0;j<4;j++) {
      pHand[i]->addTile(tiles->dealTile());
      if (players[i]->playerType()=='H')
        pHand[i]->getTile(j)->setSide('F');
       else
        pHand[i]->getTile(j)->setSide('B');
      }
    gc=rcs_openGC(display,mainScreen);
    pHand[i]->paint(display,mainScreen,gc);
    rcs_closeGC(display,gc);
    displayScreen();
    }


/* deal dealer tiles */
  dHand=new PaigowHand();
  dHand->setPosition(playerX(99),playerY(99));
  for (i=0;i<4;i++) {
    dHand->addTile(tiles->dealTile());
    dHand->getTile(i)->setSide('B');
    }
  gc=rcs_openGC(display,mainScreen);
  dHand->paint(display,mainScreen,gc);
  rcs_closeGC(display,gc);
  displayScreen();

/* find player so he can split his hand */
  for (i=0;i<5;i++) if (players[i] != NULL && players[i]->playerType()=='H') {
    splitHand(i);
    }

/* now perform splits for non-player hands */
  for (i=0;i<5;i++) if (players[i] != NULL && players[i]->playerType()!='H') {
    sHand[i]=new PaigowHand();
    sHand[i]->setDirection('H');
    sHand[i]->setPosition(playerX(i),playerY(i)-140);
    pHand[i]->splitHand(sHand[i]);
    if (pHand[i]->getRank() > sHand[i]->getRank()) swapHands(i);
    gc=rcs_openGC(display,mainScreen);
    rcs_namedForeground(display,gc,"darkgreen");
    rcs_drawFilledBox(display,mainScreen,gc,playerX(i),playerY(i)-140,154,122);
    pHand[i]->paint(display,mainScreen,gc);
    sHand[i]->paint(display,mainScreen,gc);
    rcs_closeGC(display,gc);
    displayScreen();
    Delay(1);
    }

/* now split the dealer hand and show */
  dSHand=new PaigowHand();
  dSHand->setDirection('H');
  dSHand->setPosition(playerX(99),playerY(99)-65);
  dHand->splitHand(dSHand);
  if (dHand->getRank() > dSHand->getRank()) {
    dSHand->addTile(dHand->removeTile(0));
    dSHand->addTile(dHand->removeTile(0));
    dHand->addTile(dSHand->removeTile(0));
    dHand->addTile(dSHand->removeTile(0));
    }
  dHand->setSide('F');
  dSHand->setSide('F');
  gc=rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"darkgreen");
  rcs_drawFilledBox(display,mainScreen,gc,playerX(99),playerY(99)-65,154,122);
  dHand->paint(display,mainScreen,gc);
  dSHand->paint(display,mainScreen,gc);
  rcs_closeGC(display,gc);
  displayScreen();
  Delay(1);

/* now check for winners */
  for (i=0;i<5;i++) if (players[i] != NULL) {
    gc=rcs_openGC(display,mainScreen);
    pHand[i]->setSide('F');
    sHand[i]->setSide('F');
    pHand[i]->paint(display,mainScreen,gc);
    sHand[i]->paint(display,mainScreen,gc);
    rcs_closeGC(display,gc);
    displayScreen();
    j=0;
    if (sHand[i]->getRank() > dSHand->getRank()) {
      msgBox(playerX(i)+58,playerY(i)-130,60,30,"Wins");
      j++;
      } else {
      msgBox(playerX(i)+58,playerY(i)-130,60,30,"Loses");
      }
    if (pHand[i]->getRank() > dHand->getRank()) {
      msgBox(playerX(i)+58,playerY(i)-65,60,30,"Wins");
      j++;
      } else {
      msgBox(playerX(i)+58,playerY(i)-65,60,30,"Loses");
      }
    if (j==2) players[i]->winHandBets(0,0.95);
    else if (j==1) players[i]->winHandBets(0,0);
    else players[i]->loseHandBets(0);
    gc=rcs_openGC(display,mainScreen);
    rcs_copyArea(display,table,mainScreen,gc,playerBetX(i)-50,playerBetY(i)-70,120,100,playerBetX(i)-50,playerBetY(i)-70);
    rcs_closeGC(display,gc);
    players[i]->paintBets();
    displayScreen();
    showPlayers();
    Delay(1);
    }

  for (i=0;i<5;i++)
    if (pHand[i] != NULL) {
      delete(pHand[i]);
      pHand[i]=NULL;
      }
  for (i=0;i<5;i++)
    if (sHand[i] != NULL) {
      delete(sHand[i]);
      sHand[i]=NULL;
      }
  delete(dHand);
  delete(dSHand);
  Delay(5);
}
