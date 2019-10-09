#include <stdlib.h>
#include "header.h"
#include "reddog.h"

#ifdef GRAPHIC
#include "images/reddog.xpm"
#endif

Reddog::Reddog(int decks,int jokers,float minbet):
  CardGames(decks,jokers,minbet) {
  betAmount=minbet;
  }

int Reddog::playerX(int p)
{
  switch (p) {
    case 0:return 9;
    case 1:return 166;
    case 2:return 334;
    case 3:return 504;
    case 4:return 662;
    case 99:return 290;
    }
  return 290;
}

int Reddog::playerY(int p)
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

int Reddog::playerBetX(int p)
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

int Reddog::playerBetY(int p)
{
  switch (p) {
    case 0:return 323;
    case 1:return 350;
    case 2:return 372;
    case 3:return 350;
    case 4:return 323;
    case 99:return 5;
    case 98:return 8;
    }
  return 5;
}

void Reddog::showBetAmount() {
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

void Reddog::showPlayers() {
  int i;
  rcs_GC gc;
  rcs_Font font;
    for (i=0;i<PLAYERS_REDDOG;i++) if (players[i]!=NULL) {
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
      rcs_closeFont(display,font);
      rcs_closeGC(display,gc);
      }
    displayScreen();
  }

float Reddog::placeBet(int player) {
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


void Reddog::play()
{
  float bet;
  float betReturn;
  rcs_GC gc;
  bet=1;
  table=rcs_xpmToPixmap(display,mainWindow,reddog_xpm);
  deck->shuffle();
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
        betReturn=players[i]->placeBet(minBet,0,playerBetX(i)-30,
                                       playerBetY(i)+15);
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
  rcs_closePixmap(display,table);
}

void Reddog::round()
{
  int  i,j;
  Card* card;
  Hand* hand;
  int  spread;
//  float betReturn;
//  char  flag;
#ifdef GRAPHIC
  rcs_GC gc;
#endif
  hand=new Hand();
  if (deck->cardsLeft()<22) {
    GotoXY(playerX(99),playerY(99));
    Output("Shuffling...");
    deck->shuffle();
    Delay(1);
    GotoXY(playerX(99),playerY(99));
    Output("              ");
    }
  card=deck->dealCard();
  hand->cards[0]=card;
  hand->cards[0]->setPosition(playerX(99),playerY(99));
  hand->numCards=1;
#ifdef GRAPHIC
  gc=rcs_openGC(display,mainScreen);
  hand->paint(display,mainScreen,gc,0);
  rcs_closeGC(display,gc);
  displayScreen();
  Delay(1);
#endif
#ifdef CONSOLE
  GotoXY(playerX(99),playerY(99));
  hand->display(0);
  Delay(1);
#endif
  card=deck->dealCard();
  hand->cards[1]=card;
  hand->cards[1]->setPosition(playerX(99)+140,playerY(99));
  hand->numCards=2;
#ifdef GRAPHIC
  gc=rcs_openGC(display,mainScreen);
  hand->paint(display,mainScreen,gc,0);
  rcs_closeGC(display,gc);
  displayScreen();
  Delay(1);
#endif
#ifdef CONSOLE
  GotoXY(playerX(99),playerY(99));
  hand->display(0);
  Delay(1);
#endif
  spread=abs(hand->cards[0]->value()-hand->cards[1]->value());
  if (spread==1) {
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    rcs_namedForeground(display,gc,"white");
    rcs_drawFilledCircle(display,mainScreen,gc,23+11*56,160,30,30);
    rcs_closeGC(display,gc);
    displayScreen();
#endif
#ifdef CONSOLE
    GotoXY(playerX(99),playerY(99)+1);
    Output("PUSH");
#endif
    Delay(5);
    for (i=0; i<5; i++) if (players[i] != NULL) {
      players[i]->newHand(0);
      players[i]->winHandBets(0,0);
      }
    return;
    }
  if (spread==0) {
    card=deck->dealCard();
    hand->cards[2]=card;
    hand->cards[2]->setPosition(playerX(99)+70,playerY(99));
    hand->numCards=3;
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    hand->paint(display,mainScreen,gc,0);
    rcs_closeGC(display,gc);
    displayScreen();
    Delay(1);
#endif
#ifdef CONSOLE
    GotoXY(playerX(99),playerY(99));
    hand->display(0);
    Delay(1);
#endif
    if (hand->cards[0]->value()==hand->cards[2]->value()) {
#ifdef GRAPHIC
      gc=rcs_openGC(display,mainScreen);
      rcs_namedForeground(display,gc,"white");
      rcs_drawFilledCircle(display,mainScreen,gc,23+13*56,160,30,30);
      rcs_closeGC(display,gc);
      displayScreen();
#endif
#ifdef CONSOLE
      GotoXY(playerX(99),playerY(99)+1);
      Output("Triple");
#endif
      for (i=0; i<5; i++) if (players[i] != NULL) {
        players[i]->newHand(0);
        players[i]->winHandBets(0,11);
        }
      } else {
#ifdef GRAPHIC
      gc=rcs_openGC(display,mainScreen);
      rcs_namedForeground(display,gc,"white");
      rcs_drawFilledCircle(display,mainScreen,gc,23+12*56,160,30,30);
      rcs_closeGC(display,gc);
      displayScreen();
#endif
#ifdef CONSOLE
      GotoXY(playerX(99),playerY(99)+1);
      Output("PUSH");
#endif
      for (i=0; i<5; i++) if (players[i] != NULL) {
        players[i]->newHand(0);
        players[i]->winHandBets(0,0);
        }
      }
    Delay(5);
    return;
    }
  spread--;
#ifdef GRAPHIC
  gc=rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"white");
  rcs_drawFilledCircle(display,mainScreen,gc,23+(spread-1)*56,160,30,30);
  rcs_closeGC(display,gc);
  displayScreen();
#endif
#ifdef CONSOLE
  sprintf(buffer,"Spread %d",spread);
  GotoXY(playerX(99),playerY(99)+2);
  Output(buffer);
#endif
  for (i=0;i<5;i++) if (players[i] != NULL) {
    GotoXY(playerX(i),playerY(i)+8);
    if (players[i]->playerType()=='H') {
#ifdef GRAPHIC
      if (actionBox(playerX(i),playerY(i)+40,120,70,"Double","Yes","No")==0) {
            players[i]->placeBet(players[i]->getHandBet(0),1,playerBetX(i)-30,playerBetY(i)-45);
//            flag='y';
        }
/*
      gc=rcs_openGC(display,mainScreen);
      rcs_namedForeground(display,gc,"darkgreen");
      rcs_drawFilledBox(display,mainScreen,gc,playerX(i),playerY(i)+40,120,70);
      rcs_closeGC(display,gc);
*/
#endif
#ifdef CONSOLE
      GotoXY(playerX(i),playerY(i)+8);
      Output("Double (y/n)?");
      Input(buffer);
      GotoXY(playerX(i),playerY(i)+8);
      Output("                 ");
      if (buffer[0]=='y' || buffer[0]=='Y') {
        betReturn=players[i]->placeBet(players[i]->getHandBet(0),1,1,1);
        GotoXY(playerX(i),playerY(i)+6);
        sprintf(buffer,"%12.2f",players[i]->money());
        Output("Money $");
        Output(buffer);
        GotoXY(playerX(i),playerY(i)+7);
        sprintf(buffer,"%12.2f",players[i]->getHandBet(0)+
                                players[i]->getHandBet(1));
        Output("Bet $");
        Output(buffer);
        }
#endif
      } else {
      if (spread>6) {
        players[i]->placeBet(players[i]->getHandBet(0),1,playerBetX(i)-30,playerBetY(i)-45);
#ifdef CONSOLE
        GotoXY(playerX(i),playerY(i)+6);
        sprintf(buffer,"%12.2f",players[i]->money());
        Output("Money $");
        Output(buffer);
        GotoXY(playerX(i),playerY(i)+7);
        sprintf(buffer,"%12.2f",players[i]->getHandBet(0)+
                                players[i]->getHandBet(1));
        Output("Bet $");
        Output(buffer);
#endif
        }
      Delay(1);
      }
#ifdef GRAPHIC
    players[i]->paintBets();
    displayScreen();
    showPlayers();
#endif
#ifdef CONSOLE
    players[i]->showBets();
#endif
    }
  card=deck->dealCard();
  hand->cards[2]=card;
  hand->cards[2]->setPosition(playerX(99)+70,playerY(99));
  hand->numCards=3;
#ifdef GRAPHIC
  gc=rcs_openGC(display,mainScreen);
  hand->paint(display,mainScreen,gc,0);
  rcs_closeGC(display,gc);
  displayScreen();
  Delay(1);
#endif
#ifdef CONSOLE
  GotoXY(playerX(99),playerY(99));
  hand->display(0);
  Delay(1);
#endif
  if (hand->cards[0]->value()<hand->cards[1]->value()) {
    i=hand->cards[0]->value(); j=hand->cards[1]->value();
    } else {
    j=hand->cards[0]->value(); i=hand->cards[1]->value();
    }
  GotoXY(playerX(99),playerY(99)+1);
  if (card->value()>i && card->value()<j) {
#ifdef CONSOLE
    switch (spread) {
      case 1:Output("WIN 5:1"); break;
      case 2:Output("WIN 4:1"); break;
      case 3:Output("WIN 2:1"); break;
      default:Output("WIN 1:1"); break;
      }
#endif
    for (i=0; i<5; i++) if (players[i] != NULL) {
      players[i]->newHand(0);
      switch (spread) {
        case 1:players[i]->winHandBets(0,5);
               players[i]->winHandBets(1,5); break;
        case 2:players[i]->winHandBets(0,4);
               players[i]->winHandBets(1,4); break;
        case 3:players[i]->winHandBets(0,2);
               players[i]->winHandBets(1,2); break;
        default:players[i]->winHandBets(0,1);
               players[i]->winHandBets(1,1); break;
        }
      }
    } else {
#ifdef CONSOLE
    Output("Lose");
#endif
    for (i=0; i<5; i++) if (players[i] != NULL) {
      players[i]->loseHandBets(0);
      players[i]->loseHandBets(1);
      players[i]->adjustStrategy();
      }
    }
#ifdef GRAPHIC
  gc=rcs_openGC(display,mainScreen);
  rcs_copyArea(display,table,mainScreen,gc,0,217,800,380,0,217);
  hand->paint(display,mainScreen,gc,0);
  rcs_closeGC(display,gc);
  showPlayers();
  showBetAmount();
  for (i=0;i<PLAYERS_REDDOG;i++) if (players[i]!=NULL) players[i]->paintBets();
  displayScreen();
#endif
  Delay(5);
  delete(hand);
  }
