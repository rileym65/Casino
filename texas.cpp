#include <stdlib.h>
#include "header.h"
#include "poker.h"
#include "texas.h"

#define PLAYERS 7

Texas::Texas(int decks,int jokers,float minbet,long lo,long hi):
  Poker(decks,jokers,minbet) {
  betLo=lo;
  betHi=hi;
  }

void Texas::showHand(Hand *h,int hidden) {
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

long Texas::roundBet(int p,int round) {
  Hand *pHand,*tHand;
  int  call,raise;
  int  i;
  unsigned long value;
  long risk;
#ifdef GRAPHIC
  rcs_GC gc;
  rcs_Event event;
  rcs_Font  font;
  char      flag;
  if (round==1 && betReq==0) return betLo/2;
  if (round==1 && betReq==betLo/2) {
    raisesLeft=3;
    return (betLo-betReq);
    }
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
    showHand(players[p]->getHand(0),0);
    showPlayers();
 
    if (flag=='C') return 0;
    if (flag=='R' && round<3) return betLo;
    if (flag=='R' && round>2) return betHi;
    return -1;
#endif
    }
  tHand=new Hand();
  pHand=players[p]->getHand(0);
  tHand->cards[0]=pHand->cards[0];
  tHand->cards[1]=pHand->cards[1];
  for (i=0;i<dealerHand->numCards;i++) tHand->cards[i+2]=dealerHand->cards[i];
  tHand->numCards=2+dealerHand->numCards;
  value=tHand->pokerValue(5,0);
  delete(tHand);
  if (playersIn==1) return 0;
  if (round==1) {
    if (betReq==0) {
      return betLo/2;
      } else if (betReq==betLo/2) {
      raisesLeft=3;
      return (betLo-betReq);
      } else {
      call=0; raise=0;
      if (pHand->cards[0]->getSuit()==pHand->cards[1]->getSuit()) call+=50;
      if (pHand->cards[0]->value()>9 && pHand->cards[1]->value()>9) call+=50;
      if (pHand->cards[0]->value()==pHand->cards[1]->value()) {
        call+=100;
        raise+=25;
        }
      raise+=players[i]->getBluffer();
      if (Random(100)<call) {
        if (Random(100)<raise) return betLo;
          else return 0;
        } else return -1;
      }
    }
  if (round==2) {
    if (value>PK_PAIR) risk=betLo;
    if (value>PK_2_PAIR) risk=betLo*2;
    if (value>PK_THREE) risk=betLo*3;
    if (value>PK_STRAIGHT) risk=betLo*4;
    if (value>PK_FLUSH) risk=betLo*5;
    if (value>PK_FULLHOUSE) risk=betLo*6;
    if (value>PK_FOUR) risk=betLo*7;
    if (value>PK_STFLUSH) risk=betLo*8;
    if (value>PK_ROYAL) risk=betLo*9;
    if (amountBet[p]<=risk) {
      if (Random(10)<risk/betLo) if (Random(100)<40) return betLo;
      return 0;
      }
    if (amountBet[p]==betReq) return 0;
    if (Random(100)<50) return -1;
    return 0;
    }
  if (round>2) {
    if (value>PK_PAIR) risk=betHi;
    if (value>PK_2_PAIR) risk=betHi*2;
    if (value>PK_THREE) risk=betHi*3;
    if (value>PK_STRAIGHT) risk=betHi*4;
    if (value>PK_FLUSH) risk=betHi*5;
    if (value>PK_FULLHOUSE) risk=betHi*6;
    if (value>PK_FOUR) risk=betHi*7;
    if (value>PK_STFLUSH) risk=betHi*8;
    if (value>PK_ROYAL) risk=betHi*9;
    if (amountBet[p]<=risk) {
      if (Random(10)<risk/betHi) if (Random(100)<40) return betHi;
      return 0;
      }
    if (amountBet[p]==betReq) return 0;
    if (Random(100)<50) return -1;
    return 0;
    }
  return 0;
  }

void Texas::play()
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

void Texas::round()
{
  int  i,j;
  int  winner;
  unsigned long  winHand;
  unsigned long  hv;
  Hand* hand;
  Hand* pHand;
  Card  *c1,*c2,*c3,*c4,*c5;
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
    }
  for (j=0;j<2;j++) {
    i=dealer+1;
    if (i==7) i=0;
    while (i!=99) {
      if (players[i]!=NULL) {
        players[i]->newCard(deck->dealCard(),0);
        hand=players[i]->getHand(0);
        hand->cards[j]->setPosition(playerX(i)+j*15,playerY(i)-120);
        showHand(hand,(players[i]->playerType()=='H')?0:2);

        Delay(1);
        }
      if (i==dealer) i=99;
        else { i++; if (i==7) i=0; }
      }
    }
  dealerHand->numCards=0;
  bettingRound(1);
  if (playersIn>1) {
    dealerHand->cards[0]=deck->dealCard();
    dealerHand->cards[0]->setPosition(playerX(99),playerY(99));
    dealerHand->cards[1]=deck->dealCard();
    dealerHand->cards[1]->setPosition(playerX(99)+70,playerY(99));
    dealerHand->cards[2]=deck->dealCard();
    dealerHand->cards[2]->setPosition(playerX(99)+140,playerY(99));
    dealerHand->numCards=3;
    showHand(dealerHand,0);
    Delay(1);
    bettingRound(2);
    }
  if (playersIn>1) {
    dealerHand->cards[3]=deck->dealCard();
    dealerHand->cards[3]->setPosition(playerX(99)+210,playerY(99));
    dealerHand->numCards=4;
    showHand(dealerHand,0);
    Delay(1);
    bettingRound(3);
    }
  if (playersIn>1) {
    dealerHand->cards[4]=deck->dealCard();
    dealerHand->cards[4]->setPosition(playerX(99)+280,playerY(99));
    dealerHand->numCards=5;
    showHand(dealerHand,0);
    Delay(1);
    bettingRound(4);
    }
  if (playersIn>1) {
    i=dealer+1;
    if (i==7) i=0;
    while (i!=99) {
      if (players[i]!=NULL && folded[i]==0) {
        hand=players[i]->getHand(0);
        showHand(hand,0);
        }
      if (i==dealer) i=99;
        else { i++; if (i==7) i=0; }
      }
    winner=-1;
    winHand=0;
    for (i=0;i<7;i++) if (players[i]!=NULL && folded[i]==0) {
      hand=players[i]->getHand(0);
      pHand=dealerHand;
      pHand->cards[5]=hand->cards[0];
      pHand->cards[6]=hand->cards[1];
      pHand->numCards=7;
      c1=pHand->cards[0]; c2=pHand->cards[1];
      c3=pHand->cards[2]; c4=pHand->cards[3];
      c5=pHand->cards[4];
      hv=pHand->pokerValue(5,0);
      pHand->cards[0]=c1; pHand->cards[1]=c2;
      pHand->cards[2]=c3; pHand->cards[3]=c4;
      pHand->cards[4]=c5;
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

