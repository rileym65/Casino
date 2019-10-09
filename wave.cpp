#include <stdlib.h>
#include "header.h"
#include "wave.h"

#ifdef GRAPHIC
#include "images/wave.xpm"
#endif

Wave::Wave(int decks,int jokers,float minbet):
    CardGames(decks,jokers,minbet) {

  betAmount=minbet;
  }

char Wave::computerStrategy(int pc,int dc,int numCards) {
  char ret;
  switch (dc) {
    case 1:
    case 14:
    case 2:switch (numCards) {
             case 1:if (pc<8) ret='H'; else ret='L';
                    break;
             case 2:if (pc<8) ret='H'; 
                      else if (pc>8) ret='L';
                      else ret='S';
                    break;
             case 3:if (pc<7) ret='H'; 
                      else if (pc>9) ret='L';
                      else ret='S';
                    break;
             case 4:if (pc<6) ret='H'; 
                      else if (pc>10) ret='L';
                      else ret='S';
                    break;
             case 5:if (pc<6) ret='H'; 
                      else if (pc>10) ret='L';
                      else ret='S';
                    break;
             case 6:if (pc<7) ret='H'; 
                      else if (pc>9) ret='L';
                      else ret='S';
                    break;
             default:ret='S';
             }
           break;
    case 13:
    case 3:switch (numCards) {
             case 1:if (pc<8) ret='H'; else ret='L';
                    break;
             case 2:if (pc<8) ret='H'; 
                      else if (pc>8) ret='L';
                      else ret='S';
                    break;
             case 3:if (pc<6) ret='H'; 
                      else if (pc>10) ret='L';
                      else ret='S';
                    break;
             case 4:if (pc<6) ret='H'; 
                      else if (pc>10) ret='L';
                      else ret='S';
                    break;
             case 5:if (pc<6) ret='H'; 
                      else if (pc>10) ret='L';
                      else ret='S';
                    break;
             case 6:if (pc<7) ret='H'; 
                      else if (pc>9) ret='L';
                      else ret='S';
                    break;
             default:ret='S';
             }
           break;
    case 12:
    case 4:switch (numCards) {
             case 1:if (pc<8) ret='H'; 
                      else if (pc>8) ret='L';
                      else ret='S';
                    break;
             case 2:if (pc<7) ret='H'; 
                      else if (pc>9) ret='L';
                      else ret='S';
                    break;
             case 3:if (pc<6) ret='H'; 
                      else if (pc>10) ret='L';
                      else ret='S';
                    break;
             case 4:if (pc<5) ret='H'; 
                      else if (pc>11) ret='L';
                      else ret='S';
                    break;
             case 5:if (pc<6) ret='H'; 
                      else if (pc>10) ret='L';
                      else ret='S';
                    break;
             case 6:if (pc<7) ret='H'; 
                      else if (pc>9) ret='L';
                      else ret='S';
                    break;
             default:ret='S';
             }
           break;
    case 11:
    case 5:switch (numCards) {
             case 1:if (pc<7) ret='H'; 
                      else if (pc>9) ret='L';
                      else ret='S';
                    break;
             case 2:if (pc<6) ret='H'; 
                      else if (pc>10) ret='L';
                      else ret='S';
                    break;
             case 3:if (pc<6) ret='H'; 
                      else if (pc>10) ret='L';
                      else ret='S';
                    break;
             case 4:if (pc<6) ret='H'; 
                      else if (pc>10) ret='L';
                      else ret='S';
                    break;
             case 5:if (pc<7) ret='H'; 
                      else if (pc>9) ret='L';
                      else ret='S';
                    break;
             case 6:if (pc<7) ret='H'; 
                      else if (pc>9) ret='L';
                      else ret='S';
                    break;
             default:ret='S';
             }
           break;
    case 10:
    case 6:switch (numCards) {
             case 1:if (pc<5) ret='H'; 
                      else if (pc>11) ret='L';
                      else ret='S';
                    break;
             case 2:if (pc<6) ret='H'; 
                      else if (pc>10) ret='L';
                      else ret='S';
                    break;
             case 3:if (pc<5) ret='H'; 
                      else if (pc>11) ret='L';
                      else ret='S';
                    break;
             case 4:if (pc<6) ret='H'; 
                      else if (pc>10) ret='L';
                      else ret='S';
                    break;
             case 5:if (pc<7) ret='H'; 
                      else if (pc>9) ret='L';
                      else ret='S';
                    break;
             case 6:if (pc<7) ret='H'; 
                      else if (pc>9) ret='L';
                      else ret='S';
                    break;
             default:ret='S';
             }
           break;
    case 9:
    case 7:switch (numCards) {
             case 1:if (pc<4) ret='H'; 
                      else if (pc>12) ret='L';
                      else ret='S';
                    break;
             case 2:if (pc<5) ret='H'; 
                      else if (pc>11) ret='L';
                      else ret='S';
                    break;
             case 3:if (pc<5) ret='H'; 
                      else if (pc>11) ret='L';
                      else ret='S';
                    break;
             case 4:if (pc<6) ret='H'; 
                      else if (pc>10) ret='L';
                      else ret='S';
                    break;
             case 5:if (pc<8) ret='H'; 
                      else if (pc>8) ret='L';
                      else ret='S';
                    break;
             case 6:if (pc<8) ret='H'; 
                      else ret='L';
                    break;
             default:ret='S';
             }
           break;
    case 8:switch (numCards) {
             case 1:if (pc<4) ret='H'; 
                      else if (pc>12) ret='L';
                      else ret='S';
                    break;
             case 2:if (pc<4) ret='H'; 
                      else if (pc>12) ret='L';
                      else ret='S';
                    break;
             case 3:if (pc<5) ret='H'; 
                      else if (pc>11) ret='L';
                      else ret='S';
                    break;
             case 4:if (pc<6) ret='H'; 
                      else if (pc>10) ret='L';
                      else ret='S';
                    break;
             case 5:if (pc<8) ret='H'; 
                      else if (pc>8) ret='L';
                      else ret='S';
                    break;
             case 6:if (pc<8) ret='H'; 
                      else ret='L';
                    break;
             default:ret='S';
             }
           break;
    }
  return ret;
  }

int Wave::playerX(int p)
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

int Wave::playerY(int p)
{
  switch (p) {
    case 0:return 424;
    case 1:return 448;
    case 2:return 469;
    case 3:return 448;
    case 4:return 424;
    case 99:return 21;
    }
  return 21;
}

int Wave::playerBetX(int p)
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

int Wave::playerBetY(int p)
{
  switch (p) {
    case 0:return 203;
    case 1:return 230;
    case 2:return 252;
    case 3:return 230;
    case 4:return 203;
    case 99:return 5;
    case 98:return 8;
    }
  return 5;
}

void Wave::showBetAmount() {
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

void Wave::showPlayers() {
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


float Wave::placeBet(int player) {
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

void Wave::play()
{
  float bet;
  float betReturn;
  rcs_GC gc;
  table=rcs_xpmToPixmap(display,mainWindow,wave_xpm);

  deck->shuffle();
  bet=1;
  while (bet!=0) {
    gc=rcs_openGC(display,mainScreen);
    rcs_copyArea(display,table,mainScreen,gc,0,0,800,600,0,0);
    rcs_closeGC(display,gc);
    showBetAmount();
    displayScreen();
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

void Wave::round()
{
  int i;
  int numCards;
  char  stood;
  float betReturn;
  rcs_Font font;
  rcs_Event event;
  char  flag;
#ifdef GRAPHIC
  rcs_GC gc;
#endif
  if (deck->cardsLeft()<52) {
#ifdef GRAPHIC
    msgBox(332,142,120,30,"Shuffling...");
#endif
#ifdef CONSOLE
    GotoXY(playerX(99),playerY(99));
    Output("Shuffling...");
#endif
    deck->shuffle();
    Delay(5);
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    rcs_copyArea(display,table,mainScreen,gc,332,142,120,30,332,142);
    rcs_closeGC(display,gc);
    displayScreen();
#endif
#ifdef CONSOLE
    GotoXY(playerX(99),playerY(99));
    Output("              ");
#endif
    }

/*  C.Value=10; C.Suit='D'; */
  for (i=0;i<PLAYERS_WAR;i++) if (players[i]!=NULL)
    players[i]->newHand(0);
  for (i=0;i<PLAYERS_WAR;i++) if (players[i]!=NULL) {
    players[i]->newCard(deck->dealCard(),0);
    players[i]->getHand(0)->cards[0]->setPosition(playerX(i),playerY(i)-150);
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
      players[i]->getHand(0)->display(3);
#endif
      }
    Delay(1);
    }

  dealerHand->cards[0]=deck->dealCard();
  dealerHand->cards[0]->setPosition(playerX(99),playerY(99));
  dealerHand->numCards=1;
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
  for (i=0;i<PLAYERS_WAR;i++) if (players[i]!=NULL) {
    stood='N';
    numCards=1;
    while (stood != 'Y') {
      if (players[i]->playerType()=='H') {
        gc=rcs_openGC(display,mainScreen);
        font=rcs_openFont(display,ACTION_FONT);
        rcs_setFont(display,gc,font);
        rcs_namedForeground(display,gc,"white");
        rcs_drawFilledBox(display,mainScreen,gc,playerX(i),playerY(i)+10,100,70);
        rcs_namedForeground(display,gc,"black");
        rcs_drawBox(display,mainScreen,gc,playerX(i)+5,playerY(i)+15,90,20);
        rcs_drawString(display,mainScreen,gc,playerX(i)+12,playerY(i)+31,"High");
        rcs_drawBox(display,mainScreen,gc,playerX(i)+5,playerY(i)+35,90,20);
        rcs_drawString(display,mainScreen,gc,playerX(i)+20,playerY(i)+51,"Stand");
        rcs_drawBox(display,mainScreen,gc,playerX(i)+5,playerY(i)+55,90,20);
        rcs_drawString(display,mainScreen,gc,playerX(i)+20,playerY(i)+71,"Low");

        rcs_closeFont(display,font);
        rcs_closeGC(display,gc);
        displayScreen();
        flag=' ';
        while (flag==' ') {
          event=getEvent(display);
          if (event.type==EVENT_BUTTON_PRESS && event.d1==1) {
            if (event.d2>=playerX(i)+5 && event.d2<=playerX(i)+95 &&
                event.d3>playerY(i)+15 && event.d3<playerY(i)+35) {
              stood='H';
              flag='X';
              }
            if (event.d2>=playerX(i)+5 && event.d2<=playerX(i)+95 &&
                event.d3>playerY(i)+35 && event.d3<playerY(i)+55) {
              stood='Y';
              flag='X';
              }
            if (event.d2>=playerX(i)+5 && event.d2<=playerX(i)+95 &&
                event.d3>playerY(i)+55 && event.d3<playerY(i)+75) {
              stood='L';
              flag='X';
              }
            }
          }
          gc=rcs_openGC(display,mainScreen);
          rcs_copyArea(display,table,mainScreen,gc,playerX(i),playerY(i)+10,100,70,playerX(i),playerY(i)+10);
          rcs_closeGC(display,gc);
          displayScreen();
          showPlayers();
        } else {
        stood=computerStrategy(players[i]->getHand(0)->cards[numCards-1]->value(),
                               dealerHand->cards[0]->value(),numCards);
        if (stood=='S') stood='Y';
        }
      if (stood=='H' || stood=='L') {
        if (stood=='H') msgBox(playerX(i),playerY(i)-45,60,30,"High");
          else msgBox(playerX(i),playerY(i)-45,60,30,"Low");
        Delay(1);
        players[i]->newCard(deck->dealCard(),0);
        players[i]->getHand(0)->cards[numCards]->setPosition(playerX(i)+numCards*15,playerY(i)-150);
        gc=rcs_openGC(display,mainScreen);
        players[i]->getHand(0)->paint(display,mainScreen,gc,0);
        rcs_closeGC(display,gc);
        displayScreen();
        if (players[i]->getHand(0)->cards[numCards]->value() ==
            players[i]->getHand(0)->cards[numCards-1]->value()) {
          players[i]->loseHandBets(0);
          players[i]->getHand(0)->numCards=0;
          Delay(1);
          stood='Y';
          gc=rcs_openGC(display,mainScreen);
          rcs_namedForeground(display,gc,"dark green");
          rcs_drawFilledBox(display,mainScreen,gc,playerX(i),playerY(i)-150,154,96);
          rcs_closeGC(display,gc);
          msgBox(playerX(i),playerY(i)-45,60,30,"Fail");
          }
        if (stood=='H' &&
            players[i]->getHand(0)->cards[numCards]->value() <
            players[i]->getHand(0)->cards[numCards-1]->value()) {
          players[i]->loseHandBets(0);
          players[i]->getHand(0)->numCards=0;
          stood='Y';
          Delay(1);
          gc=rcs_openGC(display,mainScreen);
          rcs_namedForeground(display,gc,"dark green");
          rcs_drawFilledBox(display,mainScreen,gc,playerX(i),playerY(i)-150,154,96);
          rcs_closeGC(display,gc);
          msgBox(playerX(i),playerY(i)-45,60,30,"Fail");
          }
        if (stood=='L' &&
            players[i]->getHand(0)->cards[numCards]->value() >
            players[i]->getHand(0)->cards[numCards-1]->value()) {
          players[i]->loseHandBets(0);
          players[i]->getHand(0)->numCards=0;
          stood='Y';
          Delay(1);
          gc=rcs_openGC(display,mainScreen);
          rcs_namedForeground(display,gc,"dark green");
          rcs_drawFilledBox(display,mainScreen,gc,playerX(i),playerY(i)-150,154,96);
          rcs_closeGC(display,gc);
          msgBox(playerX(i),playerY(i)-45,60,30,"Fail");
          }
        if (++numCards == 7 && stood != 'Y') {
          stood='Y';
          players[i]->winHandBets(0,6);
          players[i]->paintBets();
          displayScreen();
          players[i]->newHand(0);
          msgBox(playerX(i),playerY(i)-45,60,30,"Wave");
          }
        Delay(1);
        } else {
        msgBox(playerX(i),playerY(i)-45,60,30,"Stand");
        }
  
      }

#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    rcs_copyArea(display,table,mainScreen,gc,playerBetX(i)-50,playerBetY(i)-70,120,130,playerBetX(i)-50,playerBetY(i)-70);
    rcs_closeGC(display,gc);
    players[i]->paintBets();
    displayScreen();
    showPlayers();
#endif
    Delay(1);
    }

/* now the dealer hand */
  numCards=1;
  while (numCards>0) {
    if (numCards==1) {
      if (dealerHand->cards[0]->value()<8) stood='H';
        else stood='L';
      } else {
      if (dealerHand->cards[numCards-1]->value()<5) stood='H';
        else if (dealerHand->cards[numCards-1]->value()>10) stood='L';
        else stood='S';
      }
    if (stood=='S') msgBox(370,120,60,30,"Stand");
    if (stood=='H') msgBox(370,120,60,30,"High");
    if (stood=='L') msgBox(370,120,60,30,"Low");
    Delay(1);
    if (stood=='L' || stood=='H') {
      dealerHand->cards[numCards]=deck->dealCard();
      dealerHand->cards[numCards]->setPosition(playerX(99)+numCards*15,playerY(99));
      numCards++;
      dealerHand->numCards=numCards;
      gc=rcs_openGC(display,mainScreen);
      dealerHand->paint(display,mainScreen,gc,0);
      rcs_closeGC(display,gc);
      displayScreen();
      Delay(1);
      if (dealerHand->cards[numCards-1]->value() ==
          dealerHand->cards[numCards-2]->value()) {
        dealerHand->numCards=0;
        stood='S';
        msgBox(370,120,60,30,"Fail");
        Delay(1);
        }
      if (stood=='H' &&
          dealerHand->cards[numCards-1]->value() <
          dealerHand->cards[numCards-2]->value()) {
        dealerHand->numCards=0;
        stood='S';
        msgBox(370,120,60,30,"Fail");
        Delay(1);
        }
      if (stood=='L' &&
          dealerHand->cards[numCards-1]->value() >
          dealerHand->cards[numCards-2]->value()) {
        dealerHand->numCards=0;
        stood='S';
        msgBox(370,120,60,30,"Fail");
        Delay(1);
        }
      }
    if (stood=='S') numCards=0;
    }

/* look for the winners */
  for (i=0;i<PLAYERS_WAR;i++)
    if (players[i]!=NULL && players[i]->getHand(0)->numCards != 0) {
      if (dealerHand->numCards==0) 
        players[i]->winHandBets(0,1);
      else if (players[i]->getHand(0)->numCards > dealerHand->numCards) {
        players[i]->winHandBets(0,players[i]->getHand(0)->numCards-
                                  dealerHand->numCards);
        }
      else if (players[i]->getHand(0)->numCards == dealerHand->numCards) {
        players[i]->winHandBets(0,0);
        }
      else players[i]->loseHandBets(0);
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    rcs_copyArea(display,table,mainScreen,gc,playerBetX(i)-50,playerBetY(i)-70,120,130,playerBetX(i)-50,playerBetY(i)-70);
    rcs_closeGC(display,gc);
    players[i]->paintBets();
    displayScreen();
    showPlayers();
#endif
    Delay(1);
    }


  if (betReturn);
  Delay(5);
}
