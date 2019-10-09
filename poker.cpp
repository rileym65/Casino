#include "header.h"
#include "poker.h"

#define PLAYERS 7
#define XRANGE 200
#define YRANGE 150
#define OFFSETX 400-XRANGE/2
#define OFFSETY 275-YRANGE/2

Poker::Poker(int decks,int jokers,float minbet):
  CardGames(decks,jokers,minbet) {
  }

Poker::~Poker() {
  }

long Poker::roundBet(int p,int round) {
  return 0;
  }

void Poker::bettingRound(int round) {
#ifdef GRAPHIC
  rcs_GC gc;
#endif
  int lastRaiser;
  int raised;
  int starter;
  long betReturn;
  int i;
  for (i=0;i<7;i++) amountBet[i]=0;
  raised=1;
  raisesLeft=3;
  betReq=0;
  lastRaiser=-1;
  starter=-1;
  while (raised!=0) {
    raised=0;
    i=dealer+1;
    if (i==7) i=0;
    while (i!=99) {
      if (players[i]!=NULL && folded[i]!=1) {
        if (starter<0) starter=i;
#ifdef GRAPHIC
        gc=rcs_openGC(display,mainScreen);
        rcs_namedForeground(display,gc,"yellow");
        rcs_drawBox(display,mainScreen,gc,playerX(i)-3,playerY(i)-12,170,35);
        rcs_closeGC(display,gc);
#endif
        betReturn=roundBet(i,round);
        if (betReturn>0 && (raisesLeft>0 || playersIn==2)) {
          betReq+=betReturn;
          raised=1;
          raisesLeft--;
          lastRaiser=i;
          }
        if (betReturn<0) {
          folded[i]=1;
          playersIn--;
#ifdef GRAPHIC
          gc=rcs_openGC(display,mainScreen);
          rcs_namedForeground(display,gc,"darkGreen");
          rcs_drawFilledBox(display,mainScreen,gc,playerX(i),playerY(i)-120,
                      15*players[i]->getHand(0)->numCards+64,100);
          rcs_closeGC(display,gc);
#endif
          } else {
          players[i]->placeBet(betReq-amountBet[i],0,1,1);
          players[i]->loseHandBets(0);
          addToPot(betReq-amountBet[i]);
          amountBet[i]=betReq;
          }
        showPlayers();
#ifdef GRAPHIC
        gc=rcs_openGC(display,mainScreen);
        rcs_namedForeground(display,gc,"darkgreen");
        rcs_drawBox(display,mainScreen,gc,playerX(i)-3,playerY(i)-12,170,35);
        rcs_closeGC(display,gc);
#endif
        Delay(1);
        }
      i++;
      if (i==7) i=0;
      if (i==lastRaiser || (betReq==0 && i==starter)) {
        i=99;
        raised=0;
        }
      }
    }
  }

int Poker::playerX(int p)
{
  switch (p) {
    case 6:return 30;
    case 5:return 30;
    case 4:return 30;
    case 3:return 300;
    case 2:return 600;
    case 1:return 600;
    case 0:return 600;
    case 99:return 200;
    }
  return 200;
}

int Poker::playerY(int p)
{
  switch (p) {
    case 6:return 130;
    case 5:return 280;
    case 4:return 450;
    case 3:return 520;
    case 2:return 450;
    case 1:return 280;
    case 0:return 130;
    case 99:return 3;
    }
  return 3;
}

void Poker::showPlayers() {
  int i;
#ifdef GRAPHIC
  rcs_GC gc;
  rcs_Font font;
#endif
    for (i=0;i<PLAYERS;i++) if (players[i]!=NULL) {
#ifdef GRAPHIC
      gc=rcs_openGC(display,mainScreen);
      font=rcs_openFont(display,PLAYER_FONT);
      rcs_setFont(display,gc,font);
      rcs_namedForeground(display,gc,"darkgreen");
      rcs_drawFilledBox(display,mainScreen,gc,playerX(i),playerY(i),125,22);
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

void Poker::addToPot(long bet) {
  Bet* b;
  long v;
  int  i;
  pot+=bet;
  v=bet/10000;
  bet-=(v*10000);
  if (v>0) {
    b=new Bet(10000);
    for (i=0;i<v;i++) {
      b->setPosition(rcs_random(XRANGE)+OFFSETX,rcs_random(YRANGE)+OFFSETY);
      b->paint(display,mainScreen);
      }
    delete(b);
    }
  v=bet/5000;
  bet-=(v*5000);
  if (v>0) {
    b=new Bet(5000);
    for (i=0;i<v;i++) {
      b->setPosition(rcs_random(XRANGE)+OFFSETX,rcs_random(YRANGE)+OFFSETY);
      b->paint(display,mainScreen);
      }
    delete(b);
    }
  v=bet/1000;
  bet-=(v*1000);
  if (v>0) {
    b=new Bet(1000);
    for (i=0;i<v;i++) {
      b->setPosition(rcs_random(XRANGE)+OFFSETX,rcs_random(YRANGE)+OFFSETY);
      b->paint(display,mainScreen);
      }
    delete(b);
    }
  v=bet/500;
  bet-=(v*500);
  if (v>0) {
    b=new Bet(500);
    for (i=0;i<v;i++) {
      b->setPosition(rcs_random(XRANGE)+OFFSETX,rcs_random(YRANGE)+OFFSETY);
      b->paint(display,mainScreen);
      }
    delete(b);
    }
  v=bet/100;
  bet-=(v*100);
  if (v>0) {
    b=new Bet(100);
    for (i=0;i<v;i++) {
      b->setPosition(rcs_random(XRANGE)+OFFSETX,rcs_random(YRANGE)+OFFSETY);
      b->paint(display,mainScreen);
      }
    delete(b);
    }
  v=bet/50;
  bet-=(v*50);
  if (v>0) {
    b=new Bet(50);
    for (i=0;i<v;i++) {
      b->setPosition(rcs_random(XRANGE)+OFFSETX,rcs_random(YRANGE)+OFFSETY);
      b->paint(display,mainScreen);
      }
    delete(b);
    }
  v=bet/25;
  bet-=(v*25);
  if (v>0) {
    b=new Bet(25);
    for (i=0;i<v;i++) {
      b->setPosition(rcs_random(XRANGE)+OFFSETX,rcs_random(YRANGE)+OFFSETY);
      b->paint(display,mainScreen);
      }
    delete(b);
    }
  v=bet/10;
  bet-=(v*10);
  if (v>0) {
    b=new Bet(10);
    for (i=0;i<v;i++) {
      b->setPosition(rcs_random(XRANGE)+OFFSETX,rcs_random(YRANGE)+OFFSETY);
      b->paint(display,mainScreen);
      }
    delete(b);
    }
  v=bet/5;
  bet-=(v*5);
  if (v>0) {
    b=new Bet(5);
    for (i=0;i<v;i++) {
      b->setPosition(rcs_random(XRANGE)+OFFSETX,rcs_random(YRANGE)+OFFSETY);
      b->paint(display,mainScreen);
      }
    delete(b);
    }
  v=bet;
  if (v>0) {
    b=new Bet(1);
    for (i=0;i<v;i++) {
      b->setPosition(rcs_random(XRANGE)+OFFSETX,rcs_random(YRANGE)+OFFSETY);
      b->paint(display,mainScreen);
      }
    delete(b);
    }
  }

void Poker::play()
{
}

