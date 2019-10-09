#include <stdlib.h>
#include "header.h"
#include "spanish.h"

#define SPCY 25
#ifdef GRAPHIC
#include "images/spanish21.xpm"
#endif

Spanish::Spanish(int decks,int jokers,float minbet):
    CardGames(decks,jokers,minbet) {
  betAmount=2;
  }

int Spanish::playerX(int p)
{
#ifdef GRAPHIC
  switch (p) {
    case 0:return 9;
    case 1:return 166;
    case 2:return 334;
    case 3:return 504;
    case 4:return 662;
    case 99:return 213;
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
  return 213;
}

int Spanish::playerY(int p)
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

int Spanish::playerBetX(int p)
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

int Spanish::playerBetY(int p)
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

void Spanish::showBetAmount() {
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

void Spanish::showPlayers() {
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

float Spanish::placeBet(int player) {
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
               if (betAmount<2) betAmount=2;
               showBetAmount();
               }
             if (event.d2>=522 && event.d2<546) {
               betAmount-=5;
               if (betAmount<2) betAmount=2;
               showBetAmount();
               }
             if (event.d2>=553 && event.d2<578) {
               betAmount-=10;
               if (betAmount<2) betAmount=2;
               showBetAmount();
               }
             if (event.d2>=584 && event.d2<609) {
               betAmount-=25;
               if (betAmount<2) betAmount=2;
               showBetAmount();
               }
             if (event.d2>=615 && event.d2<640) {
               betAmount-=50;
               if (betAmount<2) betAmount=2;
               showBetAmount();
               }
             if (event.d2>=645 && event.d2<671) {
               betAmount-=100;
               if (betAmount<2) betAmount=2;
               showBetAmount();
               }
             if (event.d2>=676 && event.d2<701) {
               betAmount-=500;
               if (betAmount<2) betAmount=2;
               showBetAmount();
               }
             if (event.d2>=708 && event.d2<733) {
               betAmount-=1000;
               if (betAmount<2) betAmount=2;
               showBetAmount();
               }
             if (event.d2>=739 && event.d2<765) {
               betAmount-=5000;
               if (betAmount<2) betAmount=2;
               showBetAmount();
               }
             if (event.d2>=771 && event.d2<796) {
               betAmount-=10000;
               if (betAmount<2) betAmount=2;
               showBetAmount();
               }
             }
           if (event.d1 == 1 &&
               event.d2>=playerBetX(player)-50 &&
               event.d2<=playerBetX(player)+50 &&
               event.d3>=playerBetY(player)-50 &&
               event.d3<=playerBetY(player)+50 && (betAmount & 1)!=1) {
             betReturn=players[player]->placeBet(betAmount,0,playerBetX(player)-30,playerBetY(player)+20);
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
        GotoXY(playerX(i),playerY(i)+7);
        Output("Enter Bet :");
        Input(buffer);
        sscanf(buffer,"%f",&bet);
        betReturn=players[i]->placeBet(bet,0,1,1);
        GotoXY(playerX(i),playerY(i)+7);
        Output("                       ");
        GotoXY(playerX(i),playerY(i)+6);
        sprintf(buffer,"%12.2f",players[i]->money());
        Output("Money $");
        Output(buffer);
        GotoXY(playerX(i),playerY(i)+7);
        sprintf(buffer,"%12.2f",bet);
        Output("Bet $");
        Output(buffer);
#endif
  if (flag!='P' && flag!='D') return 0;
    else return betReturn;
  }

void Spanish::play()
{
  float bet;
  float betReturn;
#ifdef GRAPHIC
  rcs_GC gc;
  table=rcs_xpmToPixmap(display,mainWindow,spanish21_xpm);
#endif
  bet=1;
  deck->shuffle();
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
    for (i=0;i<5;i++) if (players[i]!=NULL) players[i]->clearAllBets();
    showPlayers();
    for (i=0;i<5;i++) if (players[i]!=NULL) {
      if (players[i]->playerType()=='H') {
        bet=placeBet(i);
        }
      else {
        betReturn=players[i]->placeBet(players[i]->getBet()*2,0,playerBetX(i)-30,playerBetY(i)+20);
#ifdef CONSOLE
        GotoXY(playerX(i),playerY(i)+6);
        sprintf(buffer,"%12.2f",players[i]->money());
        Output("Money $");
        Output(buffer);
        GotoXY(playerX(i),playerY(i)+7);
        sprintf(buffer,"%12.2f",players[i]->getBet());
        Output("Bet $");
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

char Spanish::computerPlayer(Hand* dHand,Hand* pHand)
{
  int count;
  char r;
  r='S';
  if (numSplits<3 && pHand->cards[0]->value()==pHand->cards[1]->value()) {
    switch(pHand->cards[0]->value()) {
      case 3:
      case 2:if (dHand->cards[1]->value()>3 && dHand->cards[1]->value()<8) {
               return 'P';
               }
             break;
      case 6:if (dHand->cards[1]->value()>2 && dHand->cards[1]->value()<7) {
               return 'P';
               }
             break;
      case 7:if (dHand->cards[1]->value()>1 && dHand->cards[1]->value()<8) {
               return 'P';
               }
             break;
      case 1:
      case 14:
      case 8:return 'P';
      case 9:if (dHand->cards[1]->value()!=7 && dHand->cards[1]->value()!=10 &&
                 dHand->cards[1]->value()!=14) {
               return 'P';
               }
             break;
      }
    }
  count=pHand->bjValue();
  if (count>0) {
    if (count<10) r='H';
    else if (count>16) r='S';
    else if (count==11) r='D';
    else if (dHand->cards[1]->value()==1) r='H';
    else if (count==10 && dHand->cards[1]->value()>9) r='H';
    else if (count==10 && dHand->cards[1]->value()==1) r='H';
    else if (count==10 && dHand->cards[1]->value()<10) r='D';
    else if (count==12 && dHand->cards[1]->value()<3) r='H';
    else if (count>11 && dHand->cards[1]->value()<7) r='S';
    else if (count>11 && dHand->cards[1]->value()>6) r='H';
    }
  else {
    count=abs(count);
    if (count<18) r='H';
    else if (count==18 && dHand->cards[1]->value()>8) r='H';
    else if (count==18 && dHand->cards[2]->value()==1) r='H';
    else r='S';
    }
  if (pHand->numCards>2 && r=='D') r='H';
  return r;
}

void Spanish::showHand(Hand *h,int hidden) {
#ifdef GRAPHIC
  rcs_GC gc;
    gc=rcs_openGC(display,mainScreen);
    h->paint(display,mainScreen,gc,hidden);
    rcs_closeGC(display,gc);
    displayScreen();
#endif
#ifdef CONSOLE
    GotoXY(playerX(p),playerY(p));
    h->display(hidden);
#endif
  }

void Spanish::round()
{
  int  i,j;
  Card* card;
  Hand* hand;
  int  cHand;
  int  count;
  int  dCount;
  int  hidden;
  char flag;
  char bFlags;
  char buffer[80];
  float amount;
  int  sixes;
  int  sevens;
  int  eights;
#ifdef GRAPHIC
  rcs_GC gc;
  rcs_Font font;
  rcs_Event event;
  char      flag2;
#endif
  if (deck->cardsLeft()<50) {
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
  for (i=0;i<5;i++) if (players[i]!=NULL)
    for (j=0;j<4;j++) players[i]->newHand(j);
  for (i=0;i<5;i++) if (players[i]!=NULL) {
    players[i]->newCard(deck->dealSpanishCard(),0);
    players[i]->getHand(0)->cards[0]->setPosition(playerX(i),playerY(i)-160);
      showHand(players[i]->getHand(0),(players[i]->playerType()=='H')?0:1);
    Delay(1);
    }
  dealerHand->cards[0]=deck->dealSpanishCard();
  dealerHand->cards[0]->setPosition(playerX(99),playerY(99));
  dealerHand->numCards=1;
  showHand(dealerHand,1);
  Delay(1);
  for (i=0;i<5;i++) if (players[i]!=NULL) {
    players[i]->newCard(deck->dealSpanishCard(),0);
    players[i]->getHand(0)->cards[1]->setPosition(playerX(i)+15,playerY(i)-160);
      showHand(players[i]->getHand(0),(players[i]->playerType()=='H')?0:2);
    Delay(1);
    }
  card=deck->dealSpanishCard();
  dealerHand->cards[1]=card;
  dealerHand->cards[1]->setPosition(playerX(99)+70,playerY(99));
  dealerHand->numCards=2;
  showHand(dealerHand,1);
  count=abs(dealerHand->bjValue());
  if (card->value()==1 || card->value()==14) {
    for (i=0;i<5;i++) if (players[i]!=NULL)
      if (players[i]->playerType()=='H') {
#ifdef GRAPHIC
      if (actionBox(playerX(i),playerY(i)+40,120,70,"Insurance","Yes","No")==0) buffer[0]='Y'; else buffer[0]='N';
#endif
#ifdef CONSOLE
        GotoXY(20,23);
        Output("    Insurance ?");
        Input(buffer);
        GotoXY(20,23);
        Output("                      ");
#endif
        if (buffer[0]=='y' || buffer[0]=='Y') {
          amount=players[i]->getHandBet(0);
          amount/=2;
          amount=players[i]->placeBet(amount,4,1,1);
          if (count==21) players[i]->winHandBets(4,1);
            else players[i]->loseHandBets(4);
          }
        }
    }
  if (count==21) {
    GotoXY(playerX(99),playerY(99)+1);
    Output("*** BLACKJACK ***");
    for (i=0; i<5; i++) if (players[i]!=NULL) {
      hand=players[i]->getHand(0);
      count=abs(hand->bjValue());
      if (count==21) {
#ifdef CONSOLE
        GotoXY(playerX(i),playerY(i));
#endif
        showHand(hand,0);
#ifdef CONSOLE
        Output("  *** BlackJack ***");
#endif
        players[i]->winHandBets(0,0);
        players[i]->newHand(0);
        }
      else {
#ifdef CONSOLE
        GotoXY(playerX(i),playerY(i));
#endif
        showHand(hand,0);
        players[i]->newHand(0);
        players[i]->loseHandBets(0);
        players[i]->adjustStrategy();
        }
#ifdef GRAPHIC
      gc=rcs_openGC(display,mainScreen);
      rcs_copyArea(display,table,mainScreen,gc,playerBetX(i)-50,playerBetY(i)-70,120,110,playerBetX(i)-50,playerBetY(i)-70);
      rcs_closeGC(display,gc);
      players[i]->paintBets();
      displayScreen();
      showPlayers();
#endif
#ifdef CONSOLE
      players[i]->showBets();
#endif

      }
    }
  for (i=0;i<5;i++) if (players[i]!=NULL) {
    hand=players[i]->getHand(0);
    count=abs(hand->bjValue());
    if (count==21) {
      showHand(hand,(players[i]->playerType()=='H')?0:0);
#ifdef CONSOLE
      GotoXY(playerX(i),playerY(i));
      Output("  $$$ Blackjack $$$");
#endif
      players[i]->newHand(0);
      players[i]->winHandBets(0,1.5);
#ifdef GRAPHIC
      showPlayers();
      players[i]->paintBets();
      displayScreen();
#endif
#ifdef CONSOLE
      players[i]->showBets();
#endif

      }
    }
  for (i=0;i<5;i++) if (players[i]!=NULL) {
    numSplits=0;
    if (players[i]->playerType()=='H')
      hidden=0;
    else
      hidden=2;
    cHand=0;
    while (cHand<4) {
      hand=players[i]->getHand(cHand);
      if (hand->numCards>0) {
        flag=' ';
#ifdef CONSOLE
        GotoXY(playerX(i),playerY(i)+cHand);
#endif
        showHand(hand,hidden);
        count=abs(hand->bjValue());
        while (flag==' ') {
          hand=players[i]->getHand(cHand);
          count=hand->bjValue();
          if (players[i]->playerType()=='H') {
#ifdef GRAPHIC
            bFlags=0;
            if (count>=9 && count<=11) bFlags |= 1;
            if (hand->numCards==2 && hand->cards[0]->value()==hand->cards[1]->value()) bFlags |=2;
            gc=rcs_openGC(display,mainScreen);
            font=rcs_openFont(display,ACTION_FONT);
            rcs_setFont(display,gc,font); 
            rcs_namedForeground(display,gc,"white");
            rcs_drawFilledBox(display,mainScreen,gc,playerX(i),playerY(i)+10,100,90);
            rcs_namedForeground(display,gc,"black");
            rcs_drawBox(display,mainScreen,gc,playerX(i)+5,playerY(i)+15,90,20);
            rcs_drawString(display,mainScreen,gc,playerX(i)+12,playerY(i)+31,"Stand");
            rcs_drawBox(display,mainScreen,gc,playerX(i)+5,playerY(i)+35,90,20);
            rcs_drawString(display,mainScreen,gc,playerX(i)+20,playerY(i)+51,"Hit");
            if ((bFlags & 1)==1) {
              rcs_drawBox(display,mainScreen,gc,playerX(i)+5,playerY(i)+55,90,20);
              rcs_drawString(display,mainScreen,gc,playerX(i)+10,playerY(i)+71,"Double");
              }
            if ((bFlags & 2)==2) {
              rcs_drawBox(display,mainScreen,gc,playerX(i)+5,playerY(i)+75,90,20);
              rcs_drawString(display,mainScreen,gc,playerX(i)+10,playerY(i)+91,"Split");
              }

            rcs_closeFont(display,font);
            rcs_closeGC(display,gc);
            displayScreen();
            flag2=' ';
            while (flag2==' ') {
              event=getEvent(display);
              if (event.type==EVENT_BUTTON_PRESS && event.d1==1) {
                if (event.d2>=playerX(i)+5 && event.d2<=playerX(i)+95 &&
                    event.d3>playerY(i)+15 && event.d3<playerY(i)+35) {
                  buffer[0]='S';
                  buffer[1]='\0';
                  flag2='X';
                  }
                if (event.d2>=playerX(i)+5 && event.d2<=playerX(i)+95 &&
                    event.d3>playerY(i)+35 && event.d3<playerY(i)+55) {
                  buffer[0]='H';
                  buffer[1]='\0';
                  flag2='X';
                  }
                if (event.d2>=playerX(i)+5 && event.d2<=playerX(i)+95 &&
                    event.d3>playerY(i)+55 && event.d3<playerY(i)+75 &&
                    (bFlags & 1)==1) {
                  buffer[0]='D';
                  buffer[1]='\0';
                  flag2='X';
                  }
                if (event.d2>=playerX(i)+5 && event.d2<=playerX(i)+95 &&
                    event.d3>playerY(i)+75 && event.d3<playerY(i)+95 &&
                    (bFlags & 2)==2) {
                  buffer[0]='P';
                  buffer[1]='\0';
                  flag2='X';
                  }
                }
              }
            gc=rcs_openGC(display,mainScreen);
            rcs_copyArea(display,table,mainScreen,gc,playerX(i),playerY(i)+10,100,90,playerX(i),playerY(i)+10);
            rcs_closeGC(display,gc);
            displayScreen();
            showPlayers();
#endif
#ifdef CONSOLE
            GotoXY(20,23);
            Output("    <H>it, <S>tand, s<P>lit, <D>ouble ?");
            Input(buffer);
            GotoXY(20,23);
            Output("                                                ");
#endif
            }
          else {
            buffer[0]=computerPlayer(dealerHand,players[i]->getHand(cHand));
            buffer[1]='\n'; buffer[1]='\0';
            Delay(1);
            }
          if (buffer[0]=='h' || buffer[0]=='H') {
              players[i]->newCard(deck->dealSpanishCard(),cHand);
              hand=players[i]->getHand(cHand);
              hand->cards[hand->numCards-1]->setPosition(playerX(i)+15*(hand->numCards-1),playerY(i)-160+cHand*SPCY);
#ifdef CONSOLE
              GotoXY(playerX(i),playerY(i)+cHand);
#endif
              showHand(hand,hidden);
              if (hand->bjValue()>21) {
#ifdef CONSOLE
                GotoXY(playerX(i),playerY(i)+cHand);
#endif
                showHand(hand,0);
/*                Output("  >>>BUST<<<");  */
                players[i]->loseHandBets(cHand);
                players[i]->newHand(cHand);
                players[i]->adjustStrategy();
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    rcs_copyArea(display,table,mainScreen,gc,playerBetX(i)-50,playerBetY(i)-70,120,110,playerBetX(i)-50,playerBetY(i)-70);
    rcs_closeGC(display,gc);
    players[i]->paintBets();
    displayScreen();
    showPlayers();
#endif
#ifdef CONSOLE
    players[i]->showBets();
#endif
                flag='B';
                }
              }
            if (buffer[0]=='d' || buffer[0]=='D') {
              if (count>=9 && count<=11) {
                players[i]->newCard(deck->dealSpanishCard(),cHand);
                hand=players[i]->getHand(cHand);
              hand->cards[hand->numCards-1]->setPosition(playerX(i)+15*(hand->numCards-1),playerY(i)-160+cHand*SPCY);
#ifdef CONSOLE
                GotoXY(playerX(i),playerY(i)+cHand);
#endif
                showHand(hand,hidden);
                amount=players[i]->getHandBet(cHand);
                amount=players[i]->placeBet(amount,cHand,playerBetX(i)-10,playerBetY(i)+20);
#ifdef GRAPHIC
                showPlayers();
                players[i]->paintBets();
                displayScreen();
#endif
#ifdef CONSOLE
                players[i]->showBets();
#endif

                flag='*';
                }
               else {
                Output("Not Allowed");
                hand->display(0);
                }
              }
            if (buffer[0]=='p' || buffer[0]=='P') {
              if (hand->cards[0]->value()==hand->cards[1]->value() &&
                  hand->numCards==2) {
                  split(i,cHand);
                  hidden=0;
                  hand=players[i]->getHand(cHand);
#ifdef CONSOLE
                  GotoXY(playerX(i),playerY(i)+cHand);
#endif
                  showHand(hand,hidden);
                }
               else {
                Output("Not Allowed");
                GotoXY(playerX(i),playerY(i)+cHand);
                hand->display(0);
                }
              }
            if (buffer[0]=='s' || buffer[0]=='S') {
            flag='*';
              }
          }
        }
      cHand++;
      }
    }
#ifdef CONSOLE
  GotoXY(playerX(99),playerY(99));
#endif
  showHand(dealerHand,0); Delay(1);
  count=dealerHand->bjValue();
  while (count>-18 && count<17) {
    dealerHand->cards[dealerHand->numCards++]=deck->dealSpanishCard();
    dealerHand->cards[dealerHand->numCards-1]->setPosition(playerX(99)+70*(dealerHand->numCards-1),playerY(99));
    count=dealerHand->bjValue();
#ifdef CONSOLE
    GotoXY(playerX(99),playerY(99));
#endif
    showHand(dealerHand,0); Delay(1);
    if (count>21) {
#ifdef GRAPHIC
    msgBox(playerX(99)+35,playerY(99)+30,100,30,"BUST");
#endif
#ifdef CONSOLE
      GotoXY(playerX(99),playerY(99)+1);
      Output("  >>>BUST<<<");
#endif
      } 
    }
  dCount=abs(count);
  for (i=0;i<5;i++) if (players[i]!=NULL) for (cHand=0;cHand<4;cHand++) {
    hand=players[i]->getHand(cHand);
    if (hand->numCards>0) {
      count=abs(hand->bjValue());
#ifdef CONSOLE
      GotoXY(playerX(i),playerY(i)+cHand);
#endif
      showHand(hand,0);
#ifdef CONSOLE
      GotoXY(playerX(i),playerY(i)+cHand);
#endif

      if (count==21) {
        if (hand->numCards==5) {
          players[i]->winHandBets(cHand,1.5);
          }
        else if (hand->numCards==6) {
          players[i]->winHandBets(cHand,2);
          }
        else if (hand->numCards>6) {
          players[i]->winHandBets(cHand,3);
          }
        else if (hand->numCards==3) {
          if (hand->cards[0]->value()==7 &&
              hand->cards[1]->value()==7 &&
              hand->cards[2]->value()==7) {
            if (hand->cards[0]->getSuit()=='S' &&
                hand->cards[1]->getSuit()=='S' &&
                hand->cards[2]->getSuit()=='S') {
              players[i]->winHandBets(cHand,3);
              }
            else if (hand->cards[0]->getSuit()==hand->cards[1]->getSuit() &&
                     hand->cards[1]->getSuit()==hand->cards[2]->getSuit()) {
              players[i]->winHandBets(cHand,2);
              }
            else players[i]->winHandBets(cHand,1.5);
            } else {
            sixes=abs((hand->cards[0]->value()==6)+
                      (hand->cards[1]->value()==6)+
                      (hand->cards[2]->value()==6));
            sevens=abs((hand->cards[0]->value()==7)+
                      (hand->cards[1]->value()==7)+
                      (hand->cards[2]->value()==7));
            eights=abs((hand->cards[0]->value()==8)+
                      (hand->cards[1]->value()==8)+
                      (hand->cards[2]->value()==8));
            if (sixes==1 && sevens==1 && eights==1) {
              if (hand->cards[0]->getSuit()=='S' &&
                  hand->cards[1]->getSuit()=='S' &&
                  hand->cards[2]->getSuit()=='S') {
                players[i]->winHandBets(cHand,3);
                }
              else if (hand->cards[0]->getSuit()==hand->cards[1]->getSuit() &&
                       hand->cards[1]->getSuit()==hand->cards[2]->getSuit()) {
                players[i]->winHandBets(cHand,2);
                }
              else players[i]->winHandBets(cHand,1.5);
              } else players[i]->winHandBets(cHand,1);
            }
          } else players[i]->winHandBets(cHand,1);
        }



      else if (dCount>21 && count<22) {
        players[i]->winHandBets(cHand,1);
#ifdef CONSOLE
        Output("  *** Wins ***");
#endif
        }
      else if (dCount<count) {
        players[i]->winHandBets(cHand,1);
#ifdef CONSOLE
        Output("  *** Wins ***");
#endif
        }
      else if (dCount==count) {
        players[i]->winHandBets(cHand,0);
#ifdef CONSOLE
        Output("  --- Push ---");
#endif
        }
      else {
             players[i]->loseHandBets(cHand);
#ifdef CONSOLE
             Output("  Loses.");
#endif
             players[i]->adjustStrategy(); 
             }
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    rcs_copyArea(display,table,mainScreen,gc,playerBetX(i)-50,playerBetY(i)-70,120,110,playerBetX(i)-50,playerBetY(i)-70);
    rcs_closeGC(display,gc);
    players[i]->paintBets();
    displayScreen();
    showPlayers();
#endif
#ifdef CONSOLE
    players[i]->showBets();
#endif
    Delay(2);
      }
    }
  Delay(5);
}

void Spanish::split(int p,int cHand)
{
  float amount;
  Hand* hand[4];
  Card* card1;
  Card* card2;
  int x,y;
  hand[0]=players[p]->getHand(0);
  hand[1]=players[p]->getHand(1);
  hand[2]=players[p]->getHand(2);
  hand[3]=players[p]->getHand(3);
  if (numSplits==3) return;
    numSplits++;
    hand[cHand]->numCards=1;
    hand[numSplits]->numCards=1;
    hand[numSplits]->cards[0]=hand[cHand]->cards[1];
    hand[numSplits]->cards[0]->setPosition(playerX(p)+15*(hand[numSplits]->numCards-1),playerY(p)-160+numSplits*SPCY);
    card1=deck->dealSpanishCard();
    card2=deck->dealSpanishCard();
    players[p]->newCard(card1,cHand);
    players[p]->newCard(card2,numSplits);
    card1->setPosition(playerX(p)+15*(hand[cHand]->numCards-1),playerY(p)-160+cHand*SPCY);
    card2->setPosition(playerX(p)+15*(hand[numSplits]->numCards-1),playerY(p)-160+numSplits*SPCY);
    switch(numSplits) {
      case 1:x=playerBetX(p)+20; y=playerBetY(p)+20; break;
      case 2:x=playerBetX(p)-30; y=playerBetY(p)-30; break;
      case 3:x=playerBetX(p)+20; y=playerBetY(p)-30; break;
      }
    amount=players[p]->getHandBet(cHand);
    amount=players[p]->placeBet(amount,numSplits,x,y);
#ifdef GRAPHIC
    showPlayers();
    players[p]->paintBets();
    displayScreen();
#endif
#ifdef CONSOLE
    players[p]->showBets();
#endif

}

