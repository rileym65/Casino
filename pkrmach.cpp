#include "header.h"
#include "poker.h"
#include "pkrmach.h"

#ifdef GRAPHIC
#include "images/pkrmach.xpm"
#endif

#define SPC      18
#define CARDX    51
#define CARDY    298

PkrMach::PkrMach(int decks,int jokers,float minbet):
  Poker(decks,jokers,minbet) {
  numPayouts=0;
  wildCard=0;
  progressive=0;
  }

void PkrMach::drawPayouts() {
  int i,j;
  rcs_GC gc;
  rcs_Font font;
  gc = rcs_openGC(display,mainScreen);
  font=rcs_openFont(display,VIDEO_FONT);
  rcs_setFont(display,gc,font);
  rcs_namedForeground(display,gc,"black");
  for (i=0;i<numPayouts;i++) {
    rcs_drawString(display,mainScreen,gc,20,i*SPC+25,payouts[i]);

    for (j=1; j<6; j++) {
      if (progressive != 0) {
        if (j==5 && payoutv[i]>=PK_ROYAL)
          sprintf(buffer,"%8.2f",progressive);
        else sprintf(buffer," %ld",payouta[i]*j);
        } 
      else if (i==0 && j==5) sprintf(buffer," %8ld",payouta[i]*16);
      else sprintf(buffer," %8ld",payouta[i]*j);
      rcs_drawString(display,mainScreen,gc,90+j*90,i*SPC+25,buffer);
      }
    }
  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  }

void PkrMach::showPlayer() {
#ifdef GRAPHIC
  rcs_GC gc;
  rcs_Font font;
  char     buffer[80];
  gc=rcs_openGC(display,mainScreen);
  rcs_copyArea(display,table,mainScreen,gc,625,228,150,150,625,228);
  font=rcs_openFont(display,VIDEO_FONT);
  rcs_setFont(display,gc,font);
  rcs_namedForeground(display,gc,"yellow");
  sprintf(buffer,"$%8.0f",players[0]->money());
  rcs_drawString(display,mainScreen,gc,630,245,players[0]->getName());
  rcs_drawString(display,mainScreen,gc,630,265,buffer);
  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  displayScreen();
#endif
  }

void PkrMach::putWildCard(int c) { wildCard=c; }
void PkrMach::putProgressive(float p) { progressive=p; }

float PkrMach::getProgressive() { return progressive; }

void PkrMach::addPayout(const char* text,unsigned long value,unsigned long hi,
                        long am) {
  payoutv[numPayouts] = value;
  payouth[numPayouts] = hi;
  payouta[numPayouts] = am;
  strcpy(payouts[numPayouts++], text);
  }

/*
void PkrMach::addPayout(unsigned long hand,float amount) {
  payoutHand[numPayouts]=hand;
  payoutAmount[numPayouts++]=amount*minBet;
  }
*/

float PkrMach::findPayout(unsigned long hand,int coinsPlayed) {
  int i;
  float ret;
  char buffer[80];
#ifdef GRAPHIC
  rcs_GC gc;
  rcs_Font font;
#endif
  i=0;
  ret=0;
  while (i<numPayouts) {
    if (hand>=payoutv[i] && hand<=payouth[i]) {
      ret=payouta[i]*coinsPlayed;
      if (coinsPlayed==5 && progressive==0 && i==0) ret=payouta[i]*16;
        else if (coinsPlayed==5 && progressive != 0) {
          if (payoutHand[i]>=PK_ROYAL) {
            ret=progressive;
            progressive=payouta[i]*15;
            }
          }
#ifdef GRAPHIC
      gc=rcs_openGC(display,mainScreen);
      font=rcs_openFont(display,VIDEO_FONT);
      rcs_setFont(display,gc,font);
      rcs_namedForeground(display,gc,"yellow");
#endif
      strcpy(buffer,payouts[i]);
#ifdef GRAPHIC
                     rcs_drawString(display,mainScreen,gc,80,280,buffer);
#endif
#ifdef GRAPHIC
      rcs_closeFont(display,font);
      rcs_closeGC(display,gc);
      displayScreen();
#endif
//      if (ret != 0) {
        sprintf(buffer,"%ld",long(ret));
#ifdef GRAPHIC
        gc=rcs_openGC(display,mainScreen);
        font=rcs_openFont(display,VIDEO_FONT);
        rcs_setFont(display,gc,font);
        rcs_namedForeground(display,gc,"yellow");
        rcs_drawString(display,mainScreen,gc,415,340,buffer);
        rcs_closeFont(display,font);
        rcs_closeGC(display,gc);
        showPlayer();
#endif
#ifdef CONSOLE
        Output(buffer);
#endif
//        }
      return ret;
      }
    i++;
    }
#ifdef GRAPHIC
  gc=rcs_openGC(display,mainScreen);
  font=rcs_openFont(display,VIDEO_FONT);
  rcs_setFont(display,gc,font);
  rcs_namedForeground(display,gc,"yellow");
  rcs_drawString(display,mainScreen,gc,80,280,"Game Over");
  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  displayScreen();
#endif
#ifdef CONSOLE
  Output("Game Over");
#endif
  return 0;
  }

void PkrMach::play()
{
  int Bet;
  int i;
  char flag;
  unsigned long high;
  float pay;
  int Keep[5];
//  int Top;
  float Amount;
  Card* card;
  Hand* hand;
#ifdef GRAPHIC
  rcs_GC gc;
  rcs_Font font;
  rcs_Event event;
  table=rcs_xpmToPixmap(display,mainWindow,pkrmach_xpm);
#endif
  hand=new Hand();
#ifdef GRAPHIC
    gc=rcs_openGC(display,mainScreen);
    rcs_copyArea(display,table,mainScreen,gc,0,0,800,600,0,0);
    rcs_closeGC(display,gc);
    displayScreen();
#endif
#ifdef CONSOLE
  ClrScr();
#endif
#ifdef GRAPHIC
  gc=rcs_openGC(display,mainScreen);
  font=rcs_openFont(display,VIDEO_FONT);
  rcs_setFont(display,gc,font);
  rcs_namedForeground(display,gc,"black");
#endif
  drawPayouts();
#ifdef GRAPHIC
  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  displayScreen();
#endif
  Bet=1;
  while (Bet!=0) {
    showPlayer();
    GotoXY(1,numPayouts+7);
    deck->shuffle();
    players[0]->clearAllBets();
#ifdef GRAPHIC
    flag=' ';
    Bet=0;
    while (flag == ' ') {
      event=getEvent(display);
      if (event.type==EVENT_BUTTON_PRESS && event.d1==1 && Bet<5 &&
          ((event.d2>=530 && event.d2<=597 && event.d3>=420 && event.d3<=460) ||
           (event.d2>=335 && event.d2<=393 && event.d3>=480 && event.d3<=515))) {
        Bet++;
        sprintf(buffer,"%d",Bet);
        gc=rcs_openGC(display,mainScreen);
        font=rcs_openFont(display,VIDEO_FONT);
        rcs_setFont(display,gc,font);
        rcs_namedForeground(display,gc,"yellow");
        rcs_copyArea(display,table,mainScreen,gc,399,350,84,150,399,350);
        rcs_drawString(display,mainScreen,gc,435,400,buffer);
        rcs_closeFont(display,font);
        rcs_closeGC(display,gc);
        displayScreen();
        if (Bet == 5) flag='P';
        }
      if (event.type==EVENT_BUTTON_PRESS && event.d1==1 && Bet<5 &&
          event.d2>=415 && event.d2<=474 && event.d3>=480 && event.d3<=515) {
        Bet=5;
        sprintf(buffer,"%d",Bet);
        gc=rcs_openGC(display,mainScreen);
        font=rcs_openFont(display,VIDEO_FONT);
        rcs_setFont(display,gc,font);
        rcs_namedForeground(display,gc,"yellow");
        rcs_copyArea(display,table,mainScreen,gc,399,350,84,150,399,350);
        rcs_drawString(display,mainScreen,gc,435,400,buffer);
        rcs_closeFont(display,font);
        rcs_closeGC(display,gc);
        displayScreen();
        flag='P';
        }
      if (event.type==EVENT_BUTTON_PRESS && event.d1==1 && 
          event.d2>=414 && event.d2<=473 && event.d3>=432 && event.d3<=469) {
        flag='P';
        }
      }
#endif
#ifdef CONSOLE
    sprintf(buffer,"Money $%12.2f",players[0]->money());
    Output(buffer);
    GotoXY(1,numPayouts+8); Output("Bet ?");
    Input(buffer);
    sscanf(buffer,"%d",&Bet);
#endif
    if (Bet!=0) {
      if (Bet>5) Bet=5;
      if (Bet==5 && progressive!=0) {
        progressive += minBet/5;
        sprintf(buffer,"   %8.2f",progressive);
        GotoXY(55,1); Output(buffer);
        sprintf(buffer,"   %8.2f",payoutAmount[1]*5+progressive*0.003);
        GotoXY(55,2); Output(buffer);
        sprintf(buffer,"   %8.2f",payoutAmount[2]*5+progressive*0.001);
        GotoXY(55,3); Output(buffer);
        }
//      if (Bet==5) Top=800; else Top=250;
      Amount=players[0]->placeBet(Bet*int(minBet),0,1,1);
      if (Amount) ;
#ifdef GRAPHIC
    showPlayer();
    gc=rcs_openGC(display,mainScreen);
    rcs_copyArea(display,table,mainScreen,gc,70,260,250,30,70,260);
    rcs_copyArea(display,table,mainScreen,gc,52,396,350,30,52,396);
    rcs_copyArea(display,table,mainScreen,gc,399,262,150,90,399,262);
    rcs_namedForeground(display,gc,"black");
//    rcs_drawFilledBox(display,mainScreen,gc,70,260,250,30);
    rcs_closeGC(display,gc);
    displayScreen();
#endif
#ifdef CONSOLE
      GotoXY(1,numPayouts+8); Output("                 ");
      GotoXY(1,numPayouts+2); Output("                                   ");
      GotoXY(1,numPayouts+4); Output("                 ");
      GotoXY(1,numPayouts+7);
      sprintf(buffer,"Money $%12.2f",players[0]->money());
      Output(buffer);
      GotoXY(1,numPayouts+4); printf("### ### ### ### ###");
      GotoXY(1,numPayouts+5); printf(" 1   2   3   4   5 ");
      GotoXY(1,numPayouts+4);
#endif
      hand->numCards=0;
      for (i=0;i<5;i++) {
        card=deck->dealCard();
        card->setSide('B');
        card->setPosition(CARDX+i*70,CARDY);
        hand->cards[hand->numCards++]=card;
        }
#ifdef GRAPHIC
      gc=rcs_openGC(display,mainScreen);
      for (i=0;i<5;i++) hand->cards[i]->paint(display,mainScreen,gc);
      rcs_closeGC(display,gc);
      displayScreen();
#endif
      for (i=0;i<5;i++) {
#ifdef GRAPHIC
        gc=rcs_openGC(display,mainScreen);
        hand->cards[i]->setSide('F');
        hand->cards[i]->paint(display,mainScreen,gc);
        rcs_closeGC(display,gc);
        displayScreen();
#endif
#ifdef CONSOLE
        GotoXY(1+(i*4),numPayouts+4);
        switch(hand->cards[i]->value()) {
          case 0:Output(" *"); break;
          case 1:Output(" A"); break;
          case 2:Output(" 2"); break;
          case 3:Output(" 3"); break;
          case 4:Output(" 4"); break;
          case 5:Output(" 5"); break;
          case 6:Output(" 6"); break;
          case 7:Output(" 7"); break;
          case 8:Output(" 8"); break;
          case 9:Output(" 9"); break;
          case 10:Output("10"); break;
          case 11:Output(" J"); break;
          case 12:Output(" Q"); break;
          case 13:Output(" K"); break;
          case 14:Output(" A"); break;
          }
        buffer[1]=' '; buffer[0]=hand->cards[i]->getSuit();
        buffer[2]='\0';
        Output(buffer);
#endif
        Delay(1);
        }
      for (i=0;i<5;i++) Keep[i]=0;
#ifdef GRAPHIC
      flag=' ';
      gc=rcs_openGC(display,mainScreen);
      font=rcs_openFont(display,VIDEO_FONT);
      rcs_setFont(display,gc,font);
      rcs_namedForeground(display,gc,"yellow");
      while (flag==' ') {
        event=getEvent(display);
        if (event.type==EVENT_BUTTON_PRESS && event.d1==1 && 
            event.d2>=52 && event.d2<=115 && event.d3>=299 && event.d3<=470) {
          Keep[0]=(Keep[0]==1) ? 0 : 1;
          if (Keep[0]==1) {
            rcs_drawString(display,mainScreen,gc,52,410,"HOLD");
            } else {
            rcs_copyArea(display,table,mainScreen,gc,52,396,65,30,52,396);
            }
          displayScreen();
          }
        if (event.type==EVENT_BUTTON_PRESS && event.d1==1 && 
            event.d2>=124 && event.d2<=185 && event.d3>=299 && event.d3<=470) {
          Keep[1]=(Keep[1]==1) ? 0 : 1;
          if (Keep[1]==1) {
            rcs_drawString(display,mainScreen,gc,124,410,"HOLD");
            } else {
            rcs_copyArea(display,table,mainScreen,gc,124,396,65,30,124,396);
            }
          displayScreen();
          }
        if (event.type==EVENT_BUTTON_PRESS && event.d1==1 && 
            event.d2>=193 && event.d2<=254 && event.d3>=299 && event.d3<=470) {
          Keep[2]=(Keep[2]==1) ? 0 : 1;
          if (Keep[2]==1) {
            rcs_drawString(display,mainScreen,gc,193,410,"HOLD");
            } else {
            rcs_copyArea(display,table,mainScreen,gc,193,396,65,30,193,396);
            }
          displayScreen();
          }
        if (event.type==EVENT_BUTTON_PRESS && event.d1==1 && 
            event.d2>=263 && event.d2<=324 && event.d3>=299 && event.d3<=470) {
          Keep[3]=(Keep[3]==1) ? 0 : 1;
          if (Keep[3]==1) {
            rcs_drawString(display,mainScreen,gc,263,410,"HOLD");
            } else {
            rcs_copyArea(display,table,mainScreen,gc,263,396,65,30,263,396);
            }
          displayScreen();
          }
        if (event.type==EVENT_BUTTON_PRESS && event.d1==1 && 
            event.d2>=332 && event.d2<=394 && event.d3>=299 && event.d3<=470) {
          Keep[4]=(Keep[4]==1) ? 0 : 1;
          if (Keep[4]==1) {
            rcs_drawString(display,mainScreen,gc,332,410,"HOLD");
            } else {
            rcs_copyArea(display,table,mainScreen,gc,332,396,65,30,332,396);
            }
          displayScreen();
          }
        if (event.type==EVENT_BUTTON_PRESS && event.d1==1 && 
            event.d2>=414 && event.d2<=473 && event.d3>=432 && event.d3<=470) {
          flag='P';
          }

        }
      rcs_closeFont(display,font);
      rcs_closeGC(display,gc);
#endif
#ifdef CONSOLE
      GotoXY(1,numPayouts+8); Output("Holds ?");
      Input(buffer);
      bPtr=buffer;
      GotoXY(1,numPayouts+8); Output("                 ");
      for (i=0;i<5;i++) Keep[i]=0;
      while (*bPtr!='\0') {
        switch (*bPtr) {
          case '1':Keep[0]=1; break;
          case '2':Keep[1]=1; break;
          case '3':Keep[2]=1; break;
          case '4':Keep[3]=1; break;
          case '5':Keep[4]=1; break;
          }
        bPtr++;
        }
#endif
      for (i=0;i<5;i++) if (Keep[i]==0) {
        hand->cards[i]=deck->dealCard();
#ifdef GRAPHIC
        gc=rcs_openGC(display,mainScreen);
        hand->cards[i]->setSide('B');
        hand->cards[i]->setPosition(CARDX+i*70,CARDY);
        hand->cards[i]->paint(display,mainScreen,gc);
        rcs_closeGC(display,gc);
        displayScreen();
#endif
#ifdef CONSOLE
        GotoXY(1+i*4,numPayouts+4); printf("###");
#endif
        }
      Delay(1);
      for (i=0;i<5;i++) if (Keep[i]==0) {
#ifdef GRAPHIC
        gc=rcs_openGC(display,mainScreen);
        hand->cards[i]->setSide('F');
        hand->cards[i]->paint(display,mainScreen,gc);
        rcs_closeGC(display,gc);
        displayScreen();
#endif
#ifdef CONSOLE
        GotoXY(1+(i*4),numPayouts+4);
        switch(hand->cards[i]->value()) {
          case 0:Output(" *"); break;
          case 1:Output(" A"); break;
          case 2:Output(" 2"); break;
          case 3:Output(" 3"); break;
          case 4:Output(" 4"); break;
          case 5:Output(" 5"); break;
          case 6:Output(" 6"); break;
          case 7:Output(" 7"); break;
          case 8:Output(" 8"); break;
          case 9:Output(" 9"); break;
          case 10:Output("10"); break;
          case 11:Output(" J"); break;
          case 12:Output(" Q"); break;
          case 13:Output(" K"); break;
          case 14:Output(" A"); break;
          }
        buffer[1]=' '; buffer[0]=hand->cards[i]->getSuit();
        buffer[2]='\0';
        Output(buffer);
#endif
        Delay(1);
        }
      high=hand->pokerValue(5,wildCard);
      GotoXY(1,numPayouts+2);
      pay=findPayout(high,Bet);
//      if (pay != 0) players[0]->winHandBets(0,pay);
      if (pay != 0) players[0]->winMoney(pay);
      players[0]->loseHandBets(0);
      }
    }
  delete(hand);
}

