#include <stdlib.h>
#include "header.h"
#include "poker.h"
#include "card7.h"

#define PLAYERS 7

Card7::Card7(int decks,int jokers,float minbet,long lo,long hi):
  Poker(decks,jokers,minbet) {
  betLo=lo;
  betHi=hi;
  }

void Card7::showHand(Hand *h) {
#ifdef GRAPHIC
  rcs_GC gc;
    gc=rcs_openGC(display,mainScreen);
    h->paint(display,mainScreen,gc);
    rcs_closeGC(display,gc);
    displayScreen();
#endif
#ifdef CONSOLE
    GotoXY(playerX(p),playerY(p));
    h->display(hidden);
#endif
  }

long Card7::roundBet(int p,int round) {
  Hand *pHand,*tHand;
  int  raise;
  int  i,j;
  unsigned long pValue,hValue,tValue;
#ifdef GRAPHIC
  rcs_GC gc;
  rcs_Event event;
  rcs_Font  font;
  char      flag;
  if (round==1 && betReq==0) return betLo/2;
#endif
  if (players[p]->playerType()=='H') {
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    rcs_namedForeground(display,gc,"white");
    rcs_drawFilledBox(display,mainScreen,gc,playerX(p),playerY(p)-50,100,73);
    rcs_namedForeground(display,gc,"black");
    rcs_drawBox(display,mainScreen,gc,playerX(p)+2,playerY(p)-48,96,69);
    rcs_drawBox(display,mainScreen,gc,playerX(p)+4,playerY(p)-46,92,20);
    rcs_drawBox(display,mainScreen,gc,playerX(p)+4,playerY(p)-24,92,20);
    rcs_drawBox(display,mainScreen,gc,playerX(p)+4,playerY(p)-2,92,20);
    font=rcs_openFont(display,POKER_FONT);
    rcs_setFont(display,gc,font);
    if (betReq==0) strcpy(buffer,"Check");
      else sprintf(buffer,"Call $%ld",betReq-amountBet[p]);
    rcs_drawString(display,mainScreen,gc,playerX(p)+15,playerY(p)-31,buffer);
    rcs_drawString(display,mainScreen,gc,playerX(p)+15,playerY(p)-9,"Fold");
    if (betReq>0)  {
      if (round<3) sprintf(buffer,"Raise $%ld",betLo);
        else sprintf(buffer,"Raise $%ld",betHi);
      } else {
      if (round<3) sprintf(buffer,"Open $%ld",betLo);
        else sprintf(buffer,"Open $%ld",betHi);
      }
      rcs_drawString(display,mainScreen,gc,playerX(p)+15,playerY(p)+13,buffer);
    rcs_closeFont(display,font);
    rcs_closeGC(display,gc);
    displayScreen();
    flag=' ';
    while (flag==' ') {
      event=getEvent(display);
      if (event.type==EVENT_BUTTON_PRESS && event.d1==1) {
        if (event.d2>=playerX(p)+4 && event.d2<=playerX(p)+96 &&
            event.d3>=playerY(p)-46 && event.d3<=playerY(p)-26) flag='C';
        if (event.d2>=playerX(p)+4 && event.d2<=playerX(p)+96 &&
            event.d3>=playerY(p)-24 && event.d3<=playerY(p)-4) flag='F';
        if (event.d2>=playerX(p)+4 && event.d2<=playerX(p)+96 &&
            event.d3>=playerY(p)-2 && event.d3<=playerY(p)+18) flag='R';
        }
      }
    gc=rcs_openGC(display,mainScreen);
    rcs_namedForeground(display,gc,"darkgreen");
    rcs_drawFilledBox(display,mainScreen,gc,playerX(p),playerY(p)-50,100,73);
    rcs_namedForeground(display,gc,"yellow");
    rcs_drawBox(display,mainScreen,gc,playerX(p)-3,playerY(p)-12,170,35);
    rcs_closeGC(display,gc);
    showHand(players[p]->getHand(0));
    showPlayers();
 
    if (flag=='C') return 0;
    if (flag=='R' && round<3) return betLo;
    if (flag=='R' && round>2) return betHi;
    return -1;
#endif
    }
  tHand=new Hand();
  pHand=players[p]->getHand(0);
  for (i=0;i<pHand->numCards;i++) tHand->cards[i]=pHand->cards[i];
  tHand->numCards=pHand->numCards;
  pValue=tHand->pokerValue(5,0);
  hValue=0;
  for (i=0;i<7;i++) if (players[i]!=NULL && i!=p && folded[i]==0) {
    tHand->numCards=0;
    for (j=0;j<round;j++) if (j<4) {
      tHand->cards[j]=players[i]->getHand(0)->cards[j+2];
      tHand->numCards=j+1;
      }
    tValue=tHand->pokerValue(5,0);
    if (tValue>hValue) hValue=tValue;
    }
  delete(tHand);
  if (playersIn==1) return 0;
  if (round==1) {
    if (betReq==0) {
      return betLo/2;
      } else {
      return 0;
      }
    }
  if (round>1) {
    if (hValue>pValue) {
      if (Random(100)<20*round) {
        if (amountBet[p]==betReq) return 0;
        return -1;
        }
      return 0;
      }
    if (pValue>PK_PAIR) raise=1;
    else if (pValue>PK_2_PAIR) raise=5;
    else if (pValue>PK_THREE) raise=7;
    else if (pValue>PK_STRAIGHT) raise=8;
    else if (pValue>PK_FLUSH) raise=9;
    else if (pValue>PK_FULLHOUSE) raise=10;
    else if (pValue>PK_FOUR) raise=11;
    else if (pValue>PK_STFLUSH) raise=12;
    else if (pValue>PK_ROYAL) raise=13;
    raise*=(round+1);
    if (Random(100)<raise) {
      if (round>3) return betHi; else return betLo;
      }
    return 0;
    }
  return 0;
  }

void Card7::play()
{
  float Bet;
  int i;
#ifdef GRAPHIC
  rcs_GC gc;
#endif
  dealer=0;
  Bet=1;
  while (Bet!=0) {
    while (players[dealer]==NULL) {
      dealer++;
      if (dealer==7) dealer=0;
      }
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    rcs_namedForeground(display,gc,"darkgreen");
    rcs_drawFilledBox(display,mainScreen,gc,0,0,800,600);
    rcs_closeGC(display,gc);
    displayScreen();
#endif
#ifdef CONSOLE
    ClrScr();
#endif
    for (i=0;i<PLAYERS;i++) if (players[i]!=NULL) players[i]->clearAllBets();
    for (i=0;i<PLAYERS;i++) if (players[i]!=NULL) {
      folded[i]=0;
      }
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    rcs_namedForeground(display,gc,"white");
    rcs_drawFilledCircle(display,mainScreen,gc,playerX(dealer)-20,playerY(dealer),15,15);
    rcs_closeGC(display,gc);
#endif
    showPlayers();
#ifdef CONSOLE
    GotoXY(playerX(dealer)-2,playerY(dealer)+1); Output("*");
#endif
    pot=0;
    round();
#ifdef GRAPHIC
    if (actionBox(340,265,120,70,"Next Deal","Yes","No")==0)
      strcpy(buffer,"D"); 
    else strcpy(buffer,"L");
#endif
#ifdef CONSOLE
    GotoXY(20,24); Output("<D>eal, or <L>eave game ?");
    Input(buffer);
#endif
    if (Upcase(buffer[0])=='L') Bet=0;
    dealer++;
    if (dealer==7) dealer=0;
    }
}

void Card7::round()
{
  int  i,j,rnd;
  int  winner;
  unsigned long  winHand;
  unsigned long  hv;
  Hand* hand;
#ifdef GRAPHIC
  rcs_GC gc;
#endif
  deck->shuffle();
  dealerHand=new Hand();
  dealerHand->numCards=0;
  pot=0;
  playersIn=0;
  for (i=0;i<PLAYERS;i++) if (players[i]!=NULL) {
    players[i]->newHand(0);
    playersIn++;
    players[i]->placeBet(betHi/5,0,1,1);
    players[i]->loseHandBets(0);
    addToPot(betHi/5);
    showPlayers();
    }
  for (j=0;j<3;j++) {
    i=dealer+1;
    if (i==7) i=0;
    while (i!=99) {
      if (players[i]!=NULL) {
        players[i]->newCard(deck->dealCard(),0);
        hand=players[i]->getHand(0);
        hand->cards[j]->setPosition(playerX(i)+j*15,playerY(i)-120);
        if (j==2 || players[i]->playerType()=='H') hand->cards[j]->setSide('F');
          else hand->cards[j]->setSide('B');
        showHand(hand);

        Delay(1);
        }
      if (i==dealer) i=99;
        else { i++; if (i==7) i=0; }
      }
    }
  bettingRound(1);
  for (rnd=2;rnd<6;rnd++) {
    i=dealer+1;
    if (i==7) i=0;
    while (i!=99) {
      if (players[i]!=NULL && folded[i]==0) {
        players[i]->newCard(deck->dealCard(),0);
        hand=players[i]->getHand(0);
        hand->cards[hand->numCards-1]->setPosition(playerX(i)+(hand->numCards-1)*15,playerY(i)-120);
        if (rnd<5 || players[i]->playerType()=='H')
          hand->cards[hand->numCards-1]->setSide('F');
        else
          hand->cards[hand->numCards-1]->setSide('B');
        showHand(hand);

        Delay(1);
        }
      if (i==dealer) i=99;
        else { i++; if (i==7) i=0; }
      }
    bettingRound(rnd);
    }

  if (playersIn>1) {
    i=dealer+1;
    if (i==7) i=0;
    while (i!=99) {
      if (players[i]!=NULL && folded[i]==0) {
        hand=players[i]->getHand(0);
        for (j=0;j<7;j++) hand->cards[j]->setSide('F');
        showHand(hand);
        }
      if (i==dealer) i=99;
        else { i++; if (i==7) i=0; }
      }
    winner=-1;
    winHand=0;
    for (i=0;i<7;i++) if (players[i]!=NULL && folded[i]==0) {
      hand=players[i]->getHand(0);
      hv=hand->pokerValue(5,0);
  #ifdef GRAPHIC
      switch (hv&(15l<<28)) {
        case PK_NONE:msgBox(playerX(i),playerY(i)-50,120,30,"High Card\n"); break;
        case PK_PAIR:msgBox(playerX(i),playerY(i)-50,120,30,"Pair\n"); break;
        case PK_2_PAIR:msgBox(playerX(i),playerY(i)-50,120,30,"2 Pair\n"); break;
        case PK_THREE:msgBox(playerX(i),playerY(i)-50,120,30,"3 of a Kind\n"); break;
        case PK_STRAIGHT:msgBox(playerX(i),playerY(i)-50,120,30,"Straight\n"); break;
        case PK_FLUSH:msgBox(playerX(i),playerY(i)-50,120,30,"Flush\n"); break;
        case PK_FULLHOUSE:msgBox(playerX(i),playerY(i)-50,120,30,"Full House\n"); break;
        case PK_FOUR:msgBox(playerX(i),playerY(i)-50,120,30,"4 of a Kind\n"); break;
        case PK_STFLUSH:msgBox(playerX(i),playerY(i)-50,120,30,"Straight Flush\n"); break;
        case PK_ROYAL:msgBox(playerX(i),playerY(i)-50,120,30,"Royal Flush\n"); break;
        }
  #endif
  #ifdef CONSOLE
      GotoXY(playerX(i),playerY(i)-1);
      switch (hv&(15l<<28)) {
        case PK_NONE:Output("High Card\n"); break;
        case PK_PAIR:Output("Pair\n"); break;
        case PK_2_PAIR:Output("2 Pair\n"); break;
        case PK_THREE:Output("3 of a Kind\n"); break;
        case PK_STRAIGHT:Output("Straight\n"); break;
        case PK_FLUSH:Output("Flush\n"); break;
        case PK_FULLHOUSE:Output("Full House\n"); break;
        case PK_FOUR:Output("4 of a Kind\n"); break;
        case PK_STFLUSH:Output("Straight Flush\n"); break;
        case PK_ROYAL:Output("Royal Flush\n"); break;
        }
  #endif
      if (hv>winHand) {
        winner=i;
        winHand=hv;
        }
      }
    } else {
    for (i=0;i<7;i++) if (players[i]!=NULL && folded[i]==0) winner=i;
    }
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    rcs_namedForeground(display,gc,"red");
    rcs_drawFilledCircle(display,mainScreen,gc,playerX(winner)-30,playerY(winner)-50,25,25);
    rcs_closeGC(display,gc);
    displayScreen();
#endif
#ifdef CONSOLE
  GotoXY(playerX(winner)+6,playerY(winner));
  Output("* winner *\n");
#endif
  players[winner]->winMoney(float(pot));
  showPlayers();
}

