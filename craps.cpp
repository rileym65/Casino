#include "header.h"
#include "craps.h"

#ifdef GRAPHIC
#include "images/craps.xpm"
#endif

#define PASS      0
#define DONT_PASS 1
#define COME      2
#define DONT_COME 3
#define COME_4    4
#define COME_5    5
#define COME_6    6
#define COME_8    7
#define COME_9    8
#define COME_10   9
#define DONT_4    10
#define DONT_5    11
#define DONT_6    12
#define DONT_8    13
#define DONT_9    14
#define DONT_10   15
#define FIELD     16
#define BIG_6     17
#define BIG_8     18
#define ANY_7     19
#define ANY_CRAPS 20
#define PROP_11   21
#define PROP_3    22
#define PROP_2    23
#define PROP_12   24
#define HARD_4    25
#define HARD_6    26
#define HARD_8    27
#define HARD_10   28
#define PLACE_4   29
#define PLACE_5   30
#define PLACE_6   31
#define PLACE_8   32
#define PLACE_9   33
#define PLACE_10  34
#define FREE_4    35
#define FREE_5    36
#define FREE_6    37
#define FREE_8    38
#define FREE_9    39
#define FREE_10   40
#define FREE_PASS 41
#define BUY_4     42
#define BUY_5     43
#define BUY_6     44
#define BUY_8     45
#define BUY_9     46
#define BUY_10    47
#define LAY_4     48
#define LAY_5     49
#define LAY_6     50
#define LAY_8     51
#define LAY_9     52
#define LAY_10    53
#define DFREE_4   54
#define DFREE_5   55
#define DFREE_6   56
#define DFREE_8   57
#define DFREE_9   58
#define DFREE_10  59
#define FREE_DONT 60

Craps::Craps(Player* p,int minbet)
{
  player=p;
  minBet=minbet;
  betAmount=minBet;
  point=0;
  die1=new Die(6);
  die2=new Die(6);
  die1->setSize(40);
  die1->setPosition(90,20);
  die2->setSize(40);
  die2->setPosition(135,20);
}

Craps::~Craps() {
  delete(die1);
  delete(die2);
  }

void Craps::showPlayer() {
#ifdef GRAPHIC
  rcs_GC gc;
  rcs_Font font;
  char     buffer[80];
  gc=rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"darkgreen");
  rcs_drawFilledBox(display,mainScreen,gc,377,525,150,32);
  rcs_namedForeground(display,gc,"yellow");
  font=rcs_openFont(display,BET_FONT);
  rcs_setFont(display,gc,font);
  sprintf(buffer,"%s $%12.2f",player->getName(),player->money());
  rcs_drawString(display,mainScreen,gc,385,540,buffer);
  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  displayScreen();
#endif
  }

void Craps::showBetAmount() {
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


float Craps::placeBet() {
//  float betReturn;
  float fbet,fbet2;
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
           if (event.d1 == 1) {
             if (event.d2>=91 && event.d2<=177 &&
                 event.d3>=20 && event.d3<=62) {
               flag='P';
               }
             if (event.d2>=287 && event.d2<=783 &&
                 event.d3>=448 && event.d3<=506 && point==0) {
               player->placeBet(betAmount,PASS,event.d2,event.d3);
               showBets();
               displayScreen();
               }
             if (event.d2>=735 && event.d2<=783 &&
                 event.d3>=8 && event.d3<=506 && point==0) {
               player->placeBet(betAmount,PASS,event.d2,event.d3);
               showBets();
               displayScreen();
               }
             if (event.d2>=80 && event.d2<=139 &&
                 event.d3>=101 && event.d3<=178) {
               player->placeBet(betAmount,HARD_6,event.d2,event.d3);
               showBets();
               displayScreen();
               }
             if (event.d2>=147 && event.d2<=206 &&
                 event.d3>=101 && event.d3<=178) {
               player->placeBet(betAmount,HARD_10,event.d2,event.d3);
               showBets();
               displayScreen();
               }
             if (event.d2>=80 && event.d2<=139 &&
                 event.d3>=188 && event.d3<=263) {
               player->placeBet(betAmount,HARD_8,event.d2,event.d3);
               showBets();
               displayScreen();
               }
             if (event.d2>=147 && event.d2<=206 &&
                 event.d3>=188 && event.d3<=263) {
               player->placeBet(betAmount,HARD_4,event.d2,event.d3);
               showBets();
               displayScreen();
               }
             if (event.d2>=80 && event.d2<=206 &&
                 event.d3>=287 && event.d3<=318) {
               player->placeBet(betAmount,ANY_7,event.d2,event.d3);
               showBets();
               displayScreen();
               }
             if (event.d2>=80 && event.d2<=138 &&
                 event.d3>=329 && event.d3<=406) {
               player->placeBet(betAmount,PROP_2,event.d2,event.d3);
               showBets();
               displayScreen();
               }
             if (event.d2>=148 && event.d2<=206 &&
                 event.d3>=329 && event.d3<=406) {
               player->placeBet(betAmount,PROP_12,event.d2,event.d3);
               showBets();
               displayScreen();
               }
             if (event.d2>=80 && event.d2<=138 &&
                 event.d3>=415 && event.d3<=490) {
               player->placeBet(betAmount,PROP_3,event.d2,event.d3);
               showBets();
               displayScreen();
               }
             if (event.d2>=148 && event.d2<=206 &&
                 event.d3>=415 && event.d3<=490) {
               player->placeBet(betAmount,PROP_11,event.d2,event.d3);
               showBets();
               displayScreen();
               }
             if (event.d2>=80 && event.d2<=206 &&
                 event.d3>=500 && event.d3<=532) {
               player->placeBet(betAmount,ANY_CRAPS,event.d2,event.d3);
               showBets();
               displayScreen();
               }
             if (event.d2>=567 && event.d2<=643 &&
                 event.d3>=297 && event.d3<=440) {
               player->placeBet(betAmount,BIG_6,event.d2,event.d3);
               showBets();
               displayScreen();
               }
             if (event.d2>=652 && event.d2<=727 &&
                 event.d3>=297 && event.d3<=440) {
               player->placeBet(betAmount,BIG_8,event.d2,event.d3);
               showBets();
               displayScreen();
               }
             if (event.d2>=287 && event.d2<=556 && point==0 &&
                 event.d3>=380 && event.d3<=440) {
               player->placeBet(betAmount,DONT_PASS,event.d2,event.d3);
               showBets();
               displayScreen();
               }
             if (event.d2>=680 && event.d2<=727 && point==0 &&
                 event.d3>=8 && event.d3<=286) {
               player->placeBet(betAmount,DONT_PASS,event.d2,event.d3);
               showBets();
               displayScreen();
               }
             if (event.d2>=287 && event.d2<=556 &&
                 event.d3>=297 && event.d3<=369) {
               player->placeBet(betAmount,FIELD,event.d2,event.d3);
               showBets();
               displayScreen();
               }
             if (event.d2>=287 && event.d2<=671 &&
                 event.d3>=214 && event.d3<=286 && point!=0) {
               player->placeBet(betAmount,COME,event.d2,event.d3);
               showBets();
               displayScreen();
               }
             if (event.d2>=400 && event.d2<=446 &&
                 event.d3>=186 && event.d3<=206) {
               player->placeBet(betAmount,PLACE_6,420,196);
               showBets();
               displayScreen();
               }
             if (event.d2>=455 && event.d2<=502 &&
                 event.d3>=186 && event.d3<=206) {
               player->placeBet(betAmount,PLACE_8,475,196);
               showBets();
               displayScreen();
               }
             if (event.d2>=344 && event.d2<=390 &&
                 event.d3>=186 && event.d3<=206) {
               player->placeBet(betAmount,PLACE_5,364,196);
               showBets();
               displayScreen();
               }
             if (event.d2>=268 && event.d2<=334 &&
                 event.d3>=186 && event.d3<=206) {
               player->placeBet(betAmount,PLACE_4,308,196);
               showBets();
               displayScreen();
               }
             if (event.d2>=511 && event.d2<=558 &&
                 event.d3>=186 && event.d3<=206) {
               player->placeBet(betAmount,PLACE_9,531,196);
               showBets();
               displayScreen();
               }
             if (event.d2>=567 && event.d2<=614 &&
                 event.d3>=186 && event.d3<=206) {
               player->placeBet(betAmount,PLACE_10,587,196);
               showBets();
               displayScreen();
               }
             if (event.d2>=400 && event.d2<=446 &&
                 event.d3>=90 && event.d3<=133) {
               player->placeBet(betAmount,BUY_6,420,120);
               showBets();
               displayScreen();
               }
             if (event.d2>=455 && event.d2<=502 &&
                 event.d3>=90 && event.d3<=133) {
               player->placeBet(betAmount,BUY_8,475,120);
               showBets();
               displayScreen();
               }
             if (event.d2>=344 && event.d2<=390 &&
                 event.d3>=90 && event.d3<=133) {
               player->placeBet(betAmount,BUY_5,364,120);
               showBets();
               displayScreen();
               }
             if (event.d2>=511 && event.d2<=558 &&
                 event.d3>=90 && event.d3<=133) {
               player->placeBet(betAmount,BUY_9,531,120);
               showBets();
               displayScreen();
               }
             if (event.d2>=288 && event.d2<=334 &&
                 event.d3>=90 && event.d3<=133) {
               player->placeBet(betAmount,BUY_4,308,120);
               showBets();
               displayScreen();
               }
             if (event.d2>=567 && event.d2<=614 &&
                 event.d3>=90 && event.d3<=133) {
               player->placeBet(betAmount,BUY_10,587,120);
               showBets();
               displayScreen();
               }
             if (event.d2>=400 && event.d2<=446 &&
                 event.d3>=61 && event.d3<=79) {
               player->placeBet(betAmount,LAY_6,420,71);
               showBets();
               displayScreen();
               }
             if (event.d2>=455 && event.d2<=502 &&
                 event.d3>=61 && event.d3<=79) {
               player->placeBet(betAmount,LAY_8,475,71);
               showBets();
               displayScreen();
               }
             if (event.d2>=344 && event.d2<=390 &&
                 event.d3>=61 && event.d3<=79) {
               player->placeBet(betAmount,LAY_5,364,71);
               showBets();
               displayScreen();
               }
             if (event.d2>=511 && event.d2<=558 &&
                 event.d3>=61 && event.d3<=79) {
               player->placeBet(betAmount,LAY_9,531,71);
               showBets();
               displayScreen();
               }
             if (event.d2>=288 && event.d2<=334 &&
                 event.d3>=61 && event.d3<=79) {
               player->placeBet(betAmount,LAY_4,308,71);
               showBets();
               displayScreen();
               }
             if (event.d2>=567 && event.d2<=614 &&
                 event.d3>=61 && event.d3<=79) {
               player->placeBet(betAmount,LAY_10,587,71);
               showBets();
               displayScreen();
               }
             if (event.d2>=624 && event.d2<=670 &&
                 event.d3>=8 && event.d3<=204 && point!=0) {
               player->placeBet(betAmount,DONT_COME,event.d2,event.d3);
               showBets();
               displayScreen();
               }
             if (event.d2>=400 && event.d2<=446 &&
                 event.d3>=133 && event.d3<=174) {
               fbet=player->getHandBet(COME_6);
               fbet2=player->getHandBet(FREE_6);
               if (fbet !=0 && fbet2==0) {
                 fbet *= 2;
                 while (fbet/5 != long(fbet/5)) fbet++;
                 if (betAmount<=fbet)
                   player->placeBet(betAmount,FREE_6,430,159);
                 }
               showBets();
               displayScreen();
               }
             if (event.d2>=455 && event.d2<=502 &&
                 event.d3>=133 && event.d3<=174) {
               fbet=player->getHandBet(COME_8);
               fbet2=player->getHandBet(FREE_8);
               if (fbet !=0 && fbet2==0) {
                 fbet *= 2;
                 while (fbet/5 != long(fbet/5)) fbet++;
                 if (betAmount<=fbet)
                   player->placeBet(betAmount,FREE_8,485,159);
                 }
               showBets();
               displayScreen();
               }
             if (event.d2>=344 && event.d2<=390 &&
                 event.d3>=133 && event.d3<=174) {
               fbet=player->getHandBet(COME_5);
               fbet2=player->getHandBet(FREE_5);
               if (fbet !=0 && fbet2==0) {
                 fbet *= 2;
                 while (fbet/2 != long(fbet/2)) fbet++;
                 if (betAmount<=fbet)
                   player->placeBet(betAmount,FREE_5,374,159);
                 }
               showBets();
               displayScreen();
               }
             if (event.d2>=288 && event.d2<=334 &&
                 event.d3>=133 && event.d3<=174) {
               fbet=player->getHandBet(COME_4);
               fbet2=player->getHandBet(FREE_4);
               if (fbet !=0 && fbet2==0) {
                 fbet *= 2;
                 if (betAmount<=fbet)
                   player->placeBet(betAmount,FREE_4,318,159);
                 }
               showBets();
               displayScreen();
               }
             if (event.d2>=511 && event.d2<=558 &&
                 event.d3>=133 && event.d3<=174) {
               fbet=player->getHandBet(COME_9);
               fbet2=player->getHandBet(FREE_9);
               if (fbet !=0 && fbet2==0) {
                 fbet *= 2;
                 while (fbet/2 != long(fbet/2)) fbet++;
                 if (betAmount<=fbet)
                   player->placeBet(betAmount,FREE_9,541,159);
                 }
               showBets();
               displayScreen();
               }
             if (event.d2>=567 && event.d2<=614 &&
                 event.d3>=133 && event.d3<=174) {
               fbet=player->getHandBet(COME_10);
               fbet2=player->getHandBet(FREE_10);
               if (fbet !=0 && fbet2==0) {
                 fbet *= 2;
                 if (betAmount<=fbet)
                   player->placeBet(betAmount,FREE_10,597,159);
                 }
               showBets();
               displayScreen();
               }
             if (event.d2>=287 && event.d2<=783 &&
                 event.d3>=448 && event.d3<=506 && point!=0) {
               fbet=player->getHandBet(PASS);
               fbet2=player->getHandBet(FREE_PASS);
               if (fbet !=0 && fbet2==0) {
                 fbet *= 2;
                 if (point==5 || point==9) {
                   while (fbet/2 != long(fbet/2)) fbet++;
                   }
                 if (point==6 || point==8) {
                   while (fbet/5 != long(fbet/5)) fbet++;
                   }
                 if (betAmount<=fbet)
                   player->placeBet(betAmount,FREE_PASS,538,514);
                 }
               showBets();
               displayScreen();
               }
             if (event.d2>=400 && event.d2<=446 &&
                 event.d3>=8 && event.d3<=51) {
               fbet=player->getHandBet(DONT_6);
               fbet2=player->getHandBet(DFREE_6);
               if (fbet !=0 && fbet2==0) {
                 fbet=long(fbet*2/.8333333);
                 if (betAmount<=fbet)
                   player->placeBet(betAmount,DFREE_6,430,36);
                 }
               showBets();
               displayScreen();
               }
             if (event.d2>=455 && event.d2<=502 &&
                 event.d3>=8 && event.d3<=51) {
               fbet=player->getHandBet(DONT_8);
               fbet2=player->getHandBet(DFREE_8);
               if (fbet !=0 && fbet2==0) {
                 fbet=long(fbet*2/.8333333);
                 if (betAmount<=fbet)
                   player->placeBet(betAmount,DFREE_8,485,36);
                 }
               showBets();
               displayScreen();
               }
             if (event.d2>=344 && event.d2<=390 &&
                 event.d3>=8 && event.d3<=51) {
               fbet=player->getHandBet(DONT_5);
               fbet2=player->getHandBet(DFREE_5);
               if (fbet !=0 && fbet2==0) {
                 fbet=long(fbet*2/.6666666);
                 if (betAmount<=fbet)
                   player->placeBet(betAmount,DFREE_5,374,36);
                 }
               showBets();
               displayScreen();
               }
             if (event.d2>=511 && event.d2<=558 &&
                 event.d3>=8 && event.d3<=51) {
               fbet=player->getHandBet(DONT_9);
               fbet2=player->getHandBet(DFREE_9);
               if (fbet !=0 && fbet2==0) {
                 fbet=long(fbet*2/.6666666);
                 if (betAmount<=fbet)
                   player->placeBet(betAmount,DFREE_9,541,36);
                 }
               showBets();
               displayScreen();
               }
             if (event.d2>=288 && event.d2<=334 &&
                 event.d3>=8 && event.d3<=51) {
               fbet=player->getHandBet(DONT_4);
               fbet2=player->getHandBet(DFREE_4);
               if (fbet !=0 && fbet2==0) {
                 fbet=long(fbet*2/.5);
                 if (betAmount<=fbet)
                   player->placeBet(betAmount,DFREE_4,318,36);
                 }
               showBets();
               displayScreen();
               }
             if (event.d2>=567 && event.d2<=614 &&
                 event.d3>=8 && event.d3<=51) {
               fbet=player->getHandBet(DONT_10);
               fbet2=player->getHandBet(DFREE_10);
               if (fbet !=0 && fbet2==0) {
                 fbet=long(fbet*2/.5);
                 if (betAmount<=fbet)
                   player->placeBet(betAmount,DFREE_10,597,36);
                 }
               showBets();
               displayScreen();
               }
             if (event.d2>=287 && event.d2<=556 && point != 0 &&
                 event.d3>=380 && event.d3<=440) {
               fbet=player->getHandBet(DONT_PASS);
               fbet2=player->getHandBet(FREE_DONT);
               if (fbet !=0 && fbet2==0) {
                 switch (point) {
                   case  4:
                   case 10: fbet=long(fbet*2/.5); break;
                   case  5:
                   case  9: fbet=long(fbet*2/.666666); break;
                   case  6:
                   case  8: fbet=long(fbet*2/.833333); break;
                   }
                 if (betAmount<=fbet)
                   player->placeBet(betAmount,FREE_DONT,455,444);
                 }
               showBets();
               displayScreen();
               }
             }
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
    if (point==0) while (Upcase(buffer[0])!='R' && Upcase(buffer[0])!='Q') {
      sprintf(buffer,"Money $%12.2f\n",player->money());
      GotoXY(1,21); Output(buffer);
      GotoXY(1,22);
      Output("Place Bets: <P>ass, <D>ont pass, <F>ield, P<L>ace, <6>, <8>,\n");
      Output("Free <O>dds, <B>uy, La<Y>, Propositio<N>, <R>oll, <Q>uit ?");
      Input(buffer);
      GotoXY(1,22);
      Output("                                                            \n");
      Output("                                                            \n");
      if (Upcase(buffer[0])=='L') {
        GotoXY(1,23); Output("Enter Place bet $");
        Input(buffer);
        sscanf(buffer,"%d",&bet);
        GotoXY(1,23); Output("                                           ");
        GotoXY(1,23); Output("Which number: 4, 5, 6, 8, 9, 10 ? ");
        Input(buffer);
        sscanf(buffer,"%d",&i);
        switch (i) {
          case 4:player->placeBet(bet,PLACE_4,1,1); break;
          case 5:player->placeBet(bet,PLACE_5,1,1); break;
          case 6:player->placeBet(bet,PLACE_6,1,1); break;
          case 8:player->placeBet(bet,PLACE_8,1,1); break;
          case 9:player->placeBet(bet,PLACE_9,1,1); break;
          case 10:player->placeBet(bet,PLACE_10,1,1); break;
          }
        GotoXY(1,23); Output("                                           ");
        buffer[0]='\0';
        }
      if (buffer[0]=='p' || buffer[0]=='P') {
        GotoXY(1,23); Output("Enter Pass line bet $");
        Input(buffer);
        sscanf(buffer,"%d",&bet);
        player->placeBet(bet,PASS,1,1);
        GotoXY(1,23); Output("                                 ");
        }
      if (buffer[0]=='d' || buffer[0]=='D') {
        GotoXY(1,23); Output("Enter Don't Pass bet $");
        Input(buffer);
        sscanf(buffer,"%d",&bet);
        player->placeBet(bet,DONT_PASS,1,1);
        GotoXY(1,23); Output("                                 ");
        }
      if (buffer[0]=='f' || buffer[0]=='F') {
        GotoXY(1,23); Output("Enter field bet $");
        Input(buffer);
        sscanf(buffer,"%d",&bet);
        player->placeBet(bet,FIELD,1,1);
        GotoXY(1,23); Output("                                 ");
        }
      if (buffer[0]=='6') {
        GotoXY(1,23); Output("Enter Big 6 bet $");
        Input(buffer);
        sscanf(buffer,"%d",&bet);
        player->placeBet(bet,BIG_6,1,1);
        GotoXY(1,23); Output("                                 ");
        }
      if (buffer[0]=='8') {
        GotoXY(1,23); Output("Enter Big 8 bet $");
        Input(buffer);
        sscanf(buffer,"%d",&bet);
        player->placeBet(bet,BIG_8,1,1);
        GotoXY(1,23); Output("                                 ");
        }
      if (Upcase(buffer[0])=='N') {
        propBets();
        }
      if (Upcase(buffer[0])=='O') {
        freeBets();
        }
      if (Upcase(buffer[0])=='B') {
        buyBets();
        }
      if (Upcase(buffer[0])=='Y') {
        layBets();
        }
      showBets();
      if (Upcase(buffer[0])=='R')
        if (player->getHandBet(PASS)+player->getHandBet(DONT_PASS)==0)
          buffer[0]='\0';
      if (buffer[0]=='q' || buffer[0]=='Q') flag='*';
      }
    if (point!=0) while (Upcase(buffer[0])!='R' && Upcase(buffer[0])!='Q') {
      sprintf(buffer,"Money $%12.2f\n",player->money());
      GotoXY(1,21); Output(buffer);
      GotoXY(1,22);
      Output("Place Bets: <C>ome, <D>ont come, <F>ield, P<L>ace, <6>, <8>, \n");
      Output("Free <O>dds, <B>uy, La<Y>, Propositio<N>, <R>oll, <Q>uit ?");
      Input(buffer);
      GotoXY(1,22);
      Output("                                                            \n");
      Output("                                                            \n");
      if (Upcase(buffer[0])=='L') {
        GotoXY(1,23); Output("Enter Place bet $");
        Input(buffer);
        sscanf(buffer,"%d",&bet);
        GotoXY(1,23); Output("                                           ");
        GotoXY(1,23); Output("Which number: 4, 5, 6, 8, 9, 10 ? ");
        Input(buffer);
        sscanf(buffer,"%d",&i);
        switch (i) {
          case 4:player->placeBet(bet,PLACE_4,1,1); break;
          case 5:player->placeBet(bet,PLACE_5,1,1); break;
          case 6:player->placeBet(bet,PLACE_6,1,1); break;
          case 8:player->placeBet(bet,PLACE_8,1,1); break;
          case 9:player->placeBet(bet,PLACE_9,1,1); break;
          case 10:player->placeBet(bet,PLACE_10,1,1); break;
          }
        GotoXY(1,23); Output("                                           ");
        buffer[0]='\0';
        }
      if (Upcase(buffer[0])=='C') {
        GotoXY(1,23); Output("Enter come bet $");
        Input(buffer);
        sscanf(buffer,"%d",&bet);
        player->placeBet(bet,COME,1,1);
        GotoXY(1,23); Output("                                 ");
        }
      if (Upcase(buffer[0])=='D') {
        GotoXY(1,23); Output("Enter dont come bet $");
        Input(buffer);
        sscanf(buffer,"%d",&bet);
        player->placeBet(bet,DONT_COME,1,1);
        GotoXY(1,23); Output("                                 ");
        }
      if (buffer[0]=='f' || buffer[0]=='F') {
        GotoXY(1,23); Output("Enter field bet $");
        Input(buffer);
        sscanf(buffer,"%d",&bet);
        player->placeBet(bet,FIELD,1,1);
        GotoXY(1,23); Output("                                 ");
        }
      if (buffer[0]=='6') {
        GotoXY(1,23); Output("Enter Big 6 bet $");
        Input(buffer);
        sscanf(buffer,"%d",&bet);
        player->placeBet(bet,BIG_6,1,1);
        GotoXY(1,23); Output("                                 ");
        }
      if (buffer[0]=='8') {
        GotoXY(1,23); Output("Enter Big 8 bet $");
        Input(buffer);
        sscanf(buffer,"%d",&bet);
        player->placeBet(bet,BIG_8,1,1);
        GotoXY(1,23); Output("                                 ");
        }
      if (Upcase(buffer[0])=='N') {
        propBets();
        }
      if (Upcase(buffer[0])=='O') {
        freeBets();
        }
      if (Upcase(buffer[0])=='B') {
        buyBets();
        }
      if (Upcase(buffer[0])=='Y') {
        layBets();
        }
      showBets();
      if (Upcase(buffer[0])=='R')
        if (player->getHandBet(PASS)+player->getHandBet(DONT_PASS)==0)
          buffer[0]='\0';
      if (buffer[0]=='q' || buffer[0]=='Q') flag='*';
      }
#endif
  if (flag!='P' && flag!='D') return 0;
    else return 1;
  }

void Craps::drawBoard()
{
#ifdef GRAPHIC
  rcs_GC gc;
  gc=rcs_openGC(display,mainScreen);
  rcs_copyArea(display,table,mainScreen,gc,0,0,800,600,0,0);
  die1->paint(display,mainScreen,gc);
  die2->paint(display,mainScreen,gc);
  rcs_closeGC(display,gc);
#endif
#ifdef CONSOLE
  ClrScr();
  GotoXY(1,1);
  Output("                                    +----+----+----+----+----+----+-------+\n");
  Output("+-----------------------------+     |    |    |    |    |    |    | DON'T |\n");
  Output("|            SEVEN            |     +----+----+----+----+----+----+ COME  |\n");
  Output("|            4 to 1           |     |    |    |    |    |    |    |       |\n");
  Output("+--------------+--------------+     +----+----+----+----+----+----+       |\n");
  Output("|     3  3     |     5  5     |     |  4 |  5 |  6 |  8 |  9 | 10 |       |\n");
  Output("|    9 to 1    |    7 to 1    |     |    |    |    |    |    |    |       |\n");
  Output("+--------------+--------------+     +----+----+----+----+----+----+-------+\n");
  Output("|     4  4     |     2  2     |     |           C    O    M    E          |\n");
  Output("|    9 to 1    |    7 to 1    |     |                                     |\n");
  Output("+---------+---------+---------+-----+-------------------------------------+\n");
  Output("|   1  2  |   1  1  |   6  6  | C-E |          F   I   E   L   D          |\n");
  Output("| 14 to 1 | 29 to 1 | 29 to 1 |     |  [2] . 3 . 4 . 9 . 10 . 11 . [12]   |\n");
  Output("+---------+---------+---------+ C-E +-------------------------------------+\n");
  Output("|             6  5            |     |    D O N ' T    P A S S     | 6 | 8 |\n");
  Output("|           14 to 1           | C-E |                             |   |   |\n");
  Output("+-----------------------------+     +-----------------------------+---+---+\n");
  Output("|          ANY CRAPS          | C-E |               P A S S               |\n");
  Output("|            7 to 1           |     |                                     |\n");
  Output("+-----------------------------+-----+-------------------------------------+\n");
  switch (point) {
    case 4:GotoXY(38,6); Output("= 4=\n"); break;
    case 5:GotoXY(43,6); Output("= 5=\n"); break;
    case 6:GotoXY(48,6); Output("= 6=\n"); break;
    case 8:GotoXY(53,6); Output("= 8=\n"); break;
    case 9:GotoXY(58,6); Output("= 9=\n"); break;
    case 10:GotoXY(63,6); Output("=10=\n"); break;
    }
  GotoXY(34,5); 
  sprintf(buffer,"%d\n",die1);
  Output(buffer);
  GotoXY(34,7); 
  sprintf(buffer,"%d\n",die2);
  Output(buffer);
#endif
  showBets();
#ifdef GRAPHIC
  showBetAmount();
  displayScreen();
#endif
}

int Craps::rollDice()
{
#ifdef GRAPHIC
  rcs_GC gc;
#endif
  die1->roll();
  die2->roll();
#ifdef GRAPHIC
  gc=rcs_openGC(display,mainScreen);
  die1->paint(display,mainScreen,gc);
  die2->paint(display,mainScreen,gc);
  rcs_closeGC(display,gc);
  displayScreen();
#endif
#ifdef CONSOLE
  GotoXY(34,5); 
  sprintf(buffer,"%d\n",die1);
  Output(buffer);
  GotoXY(34,7); 
  sprintf(buffer,"%d\n",die2);
  Output(buffer);
#endif
  return die1->getNumber()+die2->getNumber();
}

void Craps::showBets()
{
#ifdef GRAPHIC
  rcs_GC gc;
  player->paintBets();
  gc=rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"white");
  switch (point) {
    case 4:rcs_drawFilledCircle(display,mainScreen,gc,298,100,22,22);
           break;
    case 5:rcs_drawFilledCircle(display,mainScreen,gc,354,100,22,22);
           break;
    case 6:rcs_drawFilledCircle(display,mainScreen,gc,410,100,22,22);
           break;
    case 8:rcs_drawFilledCircle(display,mainScreen,gc,465,100,22,22);
           break;
    case 9:rcs_drawFilledCircle(display,mainScreen,gc,521,100,22,22);
           break;
    case 10:rcs_drawFilledCircle(display,mainScreen,gc,577,100,22,22);
           break;
    }
  rcs_namedForeground(display,gc,"black");
  switch (point) {
    case 4:rcs_drawCircle(display,mainScreen,gc,298,100,22,22);
           break;
    case 5:rcs_drawCircle(display,mainScreen,gc,354,100,22,22);
           break;
    case 6:rcs_drawCircle(display,mainScreen,gc,410,100,22,22);
           break;
    case 8:rcs_drawCircle(display,mainScreen,gc,465,100,22,22);
           break;
    case 9:rcs_drawCircle(display,mainScreen,gc,521,100,22,22);
           break;
    case 10:rcs_drawCircle(display,mainScreen,gc,577,100,22,22);
           break;
    }
  showPlayer();
  rcs_closeGC(display,gc);
#endif
#ifdef CONSOLE
  if (player->getHandBet(PASS)>0) {
    GotoXY(57,19); Output("*");
    } else { GotoXY(57,19); Output(" "); }
  if (player->getHandBet(FREE_PASS)>0) {
    GotoXY(58,19); Output("@");
    } else { GotoXY(58,19); Output(" "); }
  if (player->getHandBet(DONT_PASS)>0) {
    GotoXY(53,16); Output("*");
    } else { GotoXY(53,16); Output(" "); }
  if (player->getHandBet(FREE_DONT)>0) {
    GotoXY(54,16); Output("@");
    } else { GotoXY(54,16); Output(" "); }
  if (player->getHandBet(FIELD)>0) {
    GotoXY(43,12); Output("*");
    } else { GotoXY(43,12); Output(" "); }
  if (player->getHandBet(COME)>0) {
    GotoXY(57,10); Output("*");
    } else { GotoXY(57,10); Output(" "); }
  if (player->getHandBet(DONT_COME)>0) {
    GotoXY(71,5); Output("*");
    } else { GotoXY(71,5); Output(" "); }
  if (player->getHandBet(COME_4)>0) {
    GotoXY(40,7); Output("*");
    } else { GotoXY(40,7); Output(" "); }
  if (player->getHandBet(COME_5)>0) {
    GotoXY(45,7); Output("*");
    } else { GotoXY(45,7); Output(" "); }
  if (player->getHandBet(COME_6)>0) {
    GotoXY(50,7); Output("*");
    } else { GotoXY(50,7); Output(" "); }
  if (player->getHandBet(COME_8)>0) {
    GotoXY(55,7); Output("*");
    } else { GotoXY(55,7); Output(" "); }
  if (player->getHandBet(COME_9)>0) {
    GotoXY(60,7); Output("*");
    } else { GotoXY(60,7); Output(" "); }
  if (player->getHandBet(COME_10)>0) {
    GotoXY(65,7); Output("*");
    } else { GotoXY(65,7); Output(" "); }
  if (player->getHandBet(FREE_4)>0) {
    GotoXY(41,7); Output("@");
    } else { GotoXY(41,7); Output(" "); }
  if (player->getHandBet(FREE_5)>0) {
    GotoXY(46,7); Output("@");
    } else { GotoXY(46,7); Output(" "); }
  if (player->getHandBet(FREE_6)>0) {
    GotoXY(51,7); Output("@");
    } else { GotoXY(51,7); Output(" "); }
  if (player->getHandBet(FREE_8)>0) {
    GotoXY(56,7); Output("@");
    } else { GotoXY(56,7); Output(" "); }
  if (player->getHandBet(FREE_9)>0) {
    GotoXY(61,7); Output("@");
    } else { GotoXY(61,7); Output(" "); }
  if (player->getHandBet(FREE_10)>0) {
    GotoXY(66,7); Output("@");
    } else { GotoXY(66,7); Output(" "); }
  if (player->getHandBet(DONT_4)>0) {
    GotoXY(40,2); Output("*");
    } else { GotoXY(40,2); Output(" "); }
  if (player->getHandBet(DONT_5)>0) {
    GotoXY(45,2); Output("*");
    } else { GotoXY(45,2); Output(" "); }
  if (player->getHandBet(DONT_6)>0) {
    GotoXY(50,2); Output("*");
    } else { GotoXY(50,2); Output(" "); }
  if (player->getHandBet(DONT_8)>0) {
    GotoXY(55,2); Output("*");
    } else { GotoXY(55,2); Output(" "); }
  if (player->getHandBet(DONT_9)>0) {
    GotoXY(60,2); Output("*");
    } else { GotoXY(60,2); Output(" "); }
  if (player->getHandBet(DONT_10)>0) {
    GotoXY(65,2); Output("*");
    } else { GotoXY(65,2); Output(" "); }
  if (player->getHandBet(DFREE_4)>0) {
    GotoXY(41,2); Output("@");
    } else { GotoXY(41,2); Output(" "); }
  if (player->getHandBet(DFREE_5)>0) {
    GotoXY(46,2); Output("@");
    } else { GotoXY(46,2); Output(" "); }
  if (player->getHandBet(DFREE_6)>0) {
    GotoXY(51,2); Output("@");
    } else { GotoXY(51,2); Output(" "); }
  if (player->getHandBet(DFREE_8)>0) {
    GotoXY(56,2); Output("@");
    } else { GotoXY(56,2); Output(" "); }
  if (player->getHandBet(DFREE_9)>0) {
    GotoXY(61,2); Output("@");
    } else { GotoXY(61,2); Output(" "); }
  if (player->getHandBet(DFREE_10)>0) {
    GotoXY(66,2); Output("@");
    } else { GotoXY(66,2); Output(" "); }
  if (player->getHandBet(BIG_6)>0) {
    GotoXY(69,16); Output("*");
    } else { GotoXY(69,16); Output(" "); }
  if (player->getHandBet(BIG_8)>0) {
    GotoXY(73,16); Output("*");
    } else { GotoXY(73,16); Output(" "); }
  if (player->getHandBet(ANY_7)>0) {
    GotoXY(8,3); Output("*");
    } else { GotoXY(8,3); Output(" "); }
  if (player->getHandBet(ANY_CRAPS)>0) {
    GotoXY(8,18); Output("*");
    } else { GotoXY(8,18); Output(" "); }
  if (player->getHandBet(PROP_11)>0) {
    GotoXY(8,15); Output("*");
    } else { GotoXY(8,15); Output(" "); }
  if (player->getHandBet(PROP_3)>0) {
    GotoXY(3,12); Output("*");
    } else { GotoXY(3,12); Output(" "); }
  if (player->getHandBet(PROP_2)>0) {
    GotoXY(13,12); Output("*");
    } else { GotoXY(13,12); Output(" "); }
  if (player->getHandBet(PROP_12)>0) {
    GotoXY(23,12); Output("*");
    } else { GotoXY(23,12); Output(" "); }
  if (player->getHandBet(HARD_8)>0) {
    GotoXY(4,9); Output("*");
    } else { GotoXY(4,9); Output(" "); }
  if (player->getHandBet(HARD_6)>0) {
    GotoXY(4,6); Output("*");
    } else { GotoXY(4,6); Output(" "); }
  if (player->getHandBet(HARD_4)>0) {
    GotoXY(19,9); Output("*");
    } else { GotoXY(19,9); Output(" "); }
  if (player->getHandBet(HARD_10)>0) {
    GotoXY(19,6); Output("*");
    } else { GotoXY(19,6); Output(" "); }
  if (player->getHandBet(PLACE_4)>0) {
    GotoXY(40,4); Output("*");
    } else { GotoXY(40,4); Output(" "); }
  if (player->getHandBet(PLACE_5)>0) {
    GotoXY(45,4); Output("*");
    } else { GotoXY(45,4); Output(" "); }
  if (player->getHandBet(PLACE_6)>0) {
    GotoXY(50,4); Output("*");
    } else { GotoXY(50,4); Output(" "); }
  if (player->getHandBet(PLACE_8)>0) {
    GotoXY(55,4); Output("*");
    } else { GotoXY(55,4); Output(" "); }
  if (player->getHandBet(PLACE_9)>0) {
    GotoXY(60,4); Output("*");
    } else { GotoXY(60,4); Output(" "); }
  if (player->getHandBet(PLACE_10)>0) {
    GotoXY(65,4); Output("*");
    } else { GotoXY(65,4); Output(" "); }
  if (player->getHandBet(BUY_4)>0) {
    GotoXY(39,4); Output("B");
    } else { GotoXY(39,4); Output(" "); }
  if (player->getHandBet(BUY_5)>0) {
    GotoXY(44,4); Output("B");
    } else { GotoXY(44,4); Output(" "); }
  if (player->getHandBet(BUY_6)>0) {
    GotoXY(49,4); Output("B");
    } else { GotoXY(49,4); Output(" "); }
  if (player->getHandBet(BUY_8)>0) {
    GotoXY(54,4); Output("B");
    } else { GotoXY(54,4); Output(" "); }
  if (player->getHandBet(BUY_9)>0) {
    GotoXY(59,4); Output("B");
    } else { GotoXY(59,4); Output(" "); }
  if (player->getHandBet(BUY_10)>0) {
    GotoXY(64,4); Output("B");
    } else { GotoXY(64,4); Output(" "); }
  if (player->getHandBet(LAY_4)>0) {
    GotoXY(41,4); Output("L");
    } else { GotoXY(41,4); Output(" "); }
  if (player->getHandBet(LAY_5)>0) {
    GotoXY(46,4); Output("L");
    } else { GotoXY(46,4); Output(" "); }
  if (player->getHandBet(LAY_6)>0) {
    GotoXY(51,4); Output("L");
    } else { GotoXY(51,4); Output(" "); }
  if (player->getHandBet(LAY_8)>0) {
    GotoXY(56,4); Output("L");
    } else { GotoXY(56,4); Output(" "); }
  if (player->getHandBet(LAY_9)>0) {
    GotoXY(61,4); Output("L");
    } else { GotoXY(61,4); Output(" "); }
  if (player->getHandBet(LAY_10)>0) {
    GotoXY(66,4); Output("L");
    } else { GotoXY(66,4); Output(" "); }
  GotoXY(38,6); Output("  4 \n");
  GotoXY(43,6); Output("  5 \n");
  GotoXY(48,6); Output("  6 \n");
  GotoXY(53,6); Output("  8 \n");
  GotoXY(58,6); Output("  9 \n");
  GotoXY(63,6); Output(" 10 \n");
  switch (point) {
    case 4:GotoXY(38,6); Output("= 4=\n"); break;
    case 5:GotoXY(43,6); Output("= 5=\n"); break;
    case 6:GotoXY(48,6); Output("= 6=\n"); break;
    case 8:GotoXY(53,6); Output("= 8=\n"); break;
    case 9:GotoXY(58,6); Output("= 9=\n"); break;
    case 10:GotoXY(63,6); Output("=10=\n"); break;
    }
#endif
}

void Craps::freeBets()
{
  int bet;
  GotoXY(1,22);
  Output("<P>ass, D<O>nt Pass, Come: <4>, <5>, <6>, <8>, <9>, <1>0\n");
  Output("Dont come: <A> 4, <B> 5, <C> 6, <D> 8, <E> 9, <F> 10, <N>one ?");
  Input(buffer);
  GotoXY(1,22);
  Output("                                                            \n");
  Output("                                                                      \n");
  if (Upcase(buffer[0])=='P' && player->getHandBet(PASS)>0) {
    GotoXY(1,23); Output("Enter Odds bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,FREE_PASS,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (Upcase(buffer[0])=='O' && player->getHandBet(DONT_PASS)>0) {
    GotoXY(1,23); Output("Enter Odds bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,FREE_DONT,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (buffer[0]=='4' && player->getHandBet(COME_4)>0) {
    GotoXY(1,23); Output("Enter Odds bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,FREE_4,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (buffer[0]=='5' && player->getHandBet(COME_5)>0) {
    GotoXY(1,23); Output("Enter Odds bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,FREE_5,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (buffer[0]=='6' && player->getHandBet(COME_6)>0) {
    GotoXY(1,23); Output("Enter Odds bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,FREE_6,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (buffer[0]=='8' && player->getHandBet(COME_8)>0) {
    GotoXY(1,23); Output("Enter Odds bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,FREE_8,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (buffer[0]=='9' && player->getHandBet(COME_9)>0) {
    GotoXY(1,23); Output("Enter Odds bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,FREE_9,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (buffer[0]=='1' && player->getHandBet(COME_10)>0) {
    GotoXY(1,23); Output("Enter Odds bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,FREE_10,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (buffer[0]=='A' && player->getHandBet(DONT_4)>0) {
    GotoXY(1,23); Output("Enter Odds bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,DFREE_4,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (buffer[0]=='B' && player->getHandBet(DONT_5)>0) {
    GotoXY(1,23); Output("Enter Odds bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,DFREE_5,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (buffer[0]=='C' && player->getHandBet(DONT_6)>0) {
    GotoXY(1,23); Output("Enter Odds bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,DFREE_6,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (buffer[0]=='D' && player->getHandBet(DONT_8)>0) {
    GotoXY(1,23); Output("Enter Odds bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,DFREE_8,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (buffer[0]=='E' && player->getHandBet(DONT_9)>0) {
    GotoXY(1,23); Output("Enter Odds bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,DFREE_9,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (buffer[0]=='F' && player->getHandBet(DONT_10)>0) {
    GotoXY(1,23); Output("Enter Odds bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,DFREE_10,1,1);
    GotoXY(1,23); Output("                                 ");
    }
}

void Craps::buyBets()
{
  int bet;
  float comm;
  GotoXY(1,22);
  Output("Which Number : <4>, <5>, <6>, <8>, <9>, <1>0, <N>one ?");
  Input(buffer);
  GotoXY(1,22);
  Output("                                                            \n");
  Output("                                                            \n");
  bet=0;
  if (buffer[0]=='4') {
    GotoXY(1,23); Output("Enter Buy bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,BUY_4,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (buffer[0]=='5') {
    GotoXY(1,23); Output("Enter Buy bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,BUY_5,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (buffer[0]=='6') {
    GotoXY(1,23); Output("Enter Buy bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,BUY_6,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (buffer[0]=='8') {
    GotoXY(1,23); Output("Enter Buy bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,BUY_8,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (buffer[0]=='9') {
    GotoXY(1,23); Output("Enter Buy bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,BUY_9,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (buffer[0]=='1') {
    GotoXY(1,23); Output("Enter Buy bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,BUY_10,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  if (bet>0) {
    comm=bet;
    comm*=0.05;
    bet=0;
    while (comm>=1) { comm--; bet++; }
    if (comm>0) bet++;
    player->placeBet(bet,999,1,1);
    player->loseHandBets(999);
    }
}

void Craps::layBets()
{
  int bet;
  float comm;
  GotoXY(1,22);
  Output("Which Number : <4>, <5>, <6>, <8>, <9>, <1>0, <N>one ?");
  Input(buffer);
  GotoXY(1,22);
  Output("                                                            \n");
  Output("                                                            \n");
  bet=0;
  if (buffer[0]=='4') {
    GotoXY(1,23); Output("Enter Lay bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,LAY_4,1,1);
    GotoXY(1,23); Output("                                 ");
    comm=bet; comm=comm/2;
    }
  else if (buffer[0]=='5') {
    GotoXY(1,23); Output("Enter Lay bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,LAY_5,1,1);
    GotoXY(1,23); Output("                                 ");
    comm=bet; comm=comm*2/3;
    }
  else if (buffer[0]=='6') {
    GotoXY(1,23); Output("Enter Lay bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,LAY_6,1,1);
    GotoXY(1,23); Output("                                 ");
    comm=bet; comm=comm*5/6;
    }
  else if (buffer[0]=='8') {
    GotoXY(1,23); Output("Enter Lay bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,LAY_8,1,1);
    GotoXY(1,23); Output("                                 ");
    comm=bet; comm=comm*5/6;
    }
  else if (buffer[0]=='9') {
    GotoXY(1,23); Output("Enter Lay bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,LAY_9,1,1);
    GotoXY(1,23); Output("                                 ");
    comm=bet; comm=comm*2/3;
    }
  else if (buffer[0]=='1') {
    GotoXY(1,23); Output("Enter Lay bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,LAY_10,1,1);
    GotoXY(1,23); Output("                                 ");
    comm=bet; comm=comm/2;
    }
  if (bet>0) {
    comm*=0.05;
    bet=0;
    while (comm>=1) { comm--; bet++; }
    if (comm>0) bet++;
    player->placeBet(bet,999,1,1);
    player->loseHandBets(999);
    }
}


void Craps::propBets()
{
  int bet;
  GotoXY(1,22);
  Output("Place Bets: Any <7>, Any cra<P>s, <2>, <3>, <1>1, <T>welve \n");
  Output("<A> Hard 4, <B> Hard 6, <C> Hard 8, <D> Hard 10, <N>one ?");
  Input(buffer);
  GotoXY(1,22);
  Output("                                                            \n");
  Output("                                                            \n");
  if (buffer[0]=='1') {
    GotoXY(1,23); Output("Enter 11 bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,PROP_11,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (buffer[0]=='2') {
    GotoXY(1,23); Output("Enter 2 bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,PROP_2,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (buffer[0]=='3') {
    GotoXY(1,23); Output("Enter 3 bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,PROP_3,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (buffer[0]=='7') {
    GotoXY(1,23); Output("Enter Any 7 bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,ANY_7,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (Upcase(buffer[0])=='P') {
    GotoXY(1,23); Output("Enter Any Craps bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,ANY_CRAPS,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (Upcase(buffer[0])=='T') {
    GotoXY(1,23); Output("Enter Twelve bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,PROP_12,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (Upcase(buffer[0])=='A') {
    GotoXY(1,23); Output("Enter Hard 4 bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,HARD_4,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (Upcase(buffer[0])=='B') {
    GotoXY(1,23); Output("Enter Hard 6 bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,HARD_6,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (Upcase(buffer[0])=='C') {
    GotoXY(1,23); Output("Enter Hard 8 bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,HARD_8,1,1);
    GotoXY(1,23); Output("                                 ");
    }
  else if (Upcase(buffer[0])=='D') {
    GotoXY(1,23); Output("Enter Hard 10 bet $");
    Input(buffer);
    sscanf(buffer,"%d",&bet);
    player->placeBet(bet,HARD_10,1,1);
    GotoXY(1,23); Output("                                 ");
    }
}

void Craps::play()
{
  int  dice;
  float fBet;
  char flag;
#ifdef GRAPHIC
  rcs_GC gc;
  table=rcs_xpmToPixmap(display,mainWindow,craps_xpm);
#endif
  rollDice();
  drawBoard();
  rollDice();
  flag=' ';
  player->clearAllBets();
  while (flag==' ') {
    showBets();
    buffer[0]='\0';
    fBet=placeBet();
    if (fBet != 0) {
      dice=rollDice();
      if (dice==point) {
        player->winHandBets(PASS,1);
        player->loseHandBets(DONT_PASS);
        fBet=player->getHandBet(FREE_PASS);
        if (fBet>0) {
          switch (point) {
            case 4: player->winHandBets(FREE_PASS,2); break;
            case 5: player->winHandBets(FREE_PASS,1.5); break;
            case 6: player->winHandBets(FREE_PASS,1.2); break;
            case 8: player->winHandBets(FREE_PASS,1.2); break;
            case 9: player->winHandBets(FREE_PASS,1.5); break;
            case 10: player->winHandBets(FREE_PASS,2); break;
            }
          }
        showBets();
        }
      if (dice == 7) player->winHandBets(ANY_7,4);
        else player->loseHandBets(ANY_7);
      if (dice == 2 || dice==3 || dice==12) player->winHandBets(ANY_CRAPS,7);
         else player->loseHandBets(ANY_CRAPS);
      if (dice == 2) player->winHandBets(PROP_2,29);
         else player->loseHandBets(PROP_2);
      if (dice == 3) player->winHandBets(PROP_3,14);
         else player->loseHandBets(PROP_3);
      if (dice == 11) player->winHandBets(PROP_11,14);
         else player->loseHandBets(PROP_11);
      if (dice == 12) player->winHandBets(PROP_12,29);
         else player->loseHandBets(PROP_12);
      switch (dice) {
        case 2:player->winHandBets(FIELD,2);
               break;
        case 3:player->winHandBets(FIELD,1);
               break;
        case 4:player->winHandBets(FIELD,1);
               player->winHandBets(COME_4,1);
               player->loseHandBets(DONT_4);
               player->loseHandBets(LAY_4);
               player->loseHandBets(DFREE_4);
               if (die1->getNumber()==die2->getNumber()) player->winHandBets(HARD_4,7);
                 else player->loseHandBets(HARD_4);
               player->winHandBets(PLACE_4,1.8);
               player->winHandBets(BUY_4,2);
               player->winHandBets(FREE_4,2);
               break;
        case 5:player->loseHandBets(FIELD);
               player->winHandBets(COME_5,1);
               player->loseHandBets(DONT_5);
               player->loseHandBets(LAY_5);
               player->loseHandBets(DFREE_5);
               player->winHandBets(PLACE_5,1.4);
               player->winHandBets(BUY_5,1.5);
               player->winHandBets(FREE_5,1.5);
               break;
        case 6:player->loseHandBets(FIELD);
               player->winHandBets(COME_6,1);
               player->loseHandBets(DONT_6);
               player->winHandBets(BIG_6,1);
               player->loseHandBets(LAY_6);
               player->loseHandBets(DFREE_6);
               if (die1->getNumber()==die2->getNumber()) player->winHandBets(HARD_6,9);
                 else player->loseHandBets(HARD_6);
               player->winHandBets(PLACE_6,1.166666);
               player->winHandBets(BUY_6,1.2);
               player->winHandBets(FREE_6,1.2);
               break;
        case 7:player->loseHandBets(FIELD);
               player->winHandBets(DONT_4,1);
               player->winHandBets(DONT_5,1);
               player->winHandBets(DONT_6,1);
               player->winHandBets(DONT_8,1);
               player->winHandBets(DONT_9,1);
               player->winHandBets(DONT_10,1);
               player->loseHandBets(COME_4);
               player->loseHandBets(COME_5);
               player->loseHandBets(COME_6);
               player->loseHandBets(COME_8);
               player->loseHandBets(COME_9);
               player->loseHandBets(COME_10);
               player->loseHandBets(BIG_6);
               player->loseHandBets(BIG_8);
               player->loseHandBets(HARD_4);
               player->loseHandBets(HARD_6);
               player->loseHandBets(HARD_8);
               player->loseHandBets(HARD_10);
               player->loseHandBets(PLACE_4);
               player->loseHandBets(PLACE_5);
               player->loseHandBets(PLACE_6);
               player->loseHandBets(PLACE_8);
               player->loseHandBets(PLACE_9);
               player->loseHandBets(PLACE_10);
               player->loseHandBets(FREE_4);
               player->loseHandBets(FREE_5);
               player->loseHandBets(FREE_6);
               player->loseHandBets(FREE_8);
               player->loseHandBets(FREE_9);
               player->loseHandBets(FREE_10);
               player->loseHandBets(FREE_PASS);
               player->loseHandBets(BUY_4);
               player->loseHandBets(BUY_5);
               player->loseHandBets(BUY_6);
               player->loseHandBets(BUY_8);
               player->loseHandBets(BUY_9);
               player->loseHandBets(BUY_10);
               player->winHandBets(LAY_4,0.5);
               player->winHandBets(LAY_5,0.6666666);
               player->winHandBets(LAY_6,0.8333333);
               player->winHandBets(LAY_8,0.8333333);
               player->winHandBets(LAY_9,0.6666666);
               player->winHandBets(LAY_10,0.5);
               player->winHandBets(DFREE_4,0.5);
               player->winHandBets(DFREE_5,0.666666);
               player->winHandBets(DFREE_6,0.833333);
               player->winHandBets(DFREE_8,0.833333);
               player->winHandBets(DFREE_9,0.666666);
               player->winHandBets(DFREE_10,0.5);
               fBet=player->getHandBet(FREE_DONT);
               if (fBet>0) {
                 player->winHandBets(FREE_DONT,0);
                 switch (point) {
                   case 4:player->winHandBets(FREE_DONT,0.5); break;
                   case 5:player->winHandBets(FREE_DONT,0.666666); break;
                   case 6:player->winHandBets(FREE_DONT,0.833333); break;
                   case 8:player->winHandBets(FREE_DONT,0.833333); break;
                   case 9:player->winHandBets(FREE_DONT,0.666666); break;
                   case 10:player->winHandBets(FREE_DONT,0.5); break;
                   }
                 }
               break;
        case 8:player->loseHandBets(FIELD);
               player->winHandBets(COME_8,1);
               player->loseHandBets(DONT_8);
               player->loseHandBets(LAY_8);
               player->winHandBets(BIG_8,1);
               player->loseHandBets(DFREE_8);
               if (die1->getNumber()==die2->getNumber()) player->winHandBets(HARD_8,9);
                 else player->loseHandBets(HARD_8);
               player->winHandBets(PLACE_8,1.166666);
               player->winHandBets(BUY_8,1.2);
               player->winHandBets(FREE_8,1.2);
               break;
        case 9:player->winHandBets(FIELD,1);
               player->winHandBets(COME_9,1);
               player->loseHandBets(DONT_9);
               player->loseHandBets(LAY_9);
               player->loseHandBets(DFREE_9);
               player->winHandBets(PLACE_9,1.4);
               player->winHandBets(BUY_9,1.5);
               player->winHandBets(FREE_9,1.5);
               break;
       case 10:player->winHandBets(FIELD,1);
               player->winHandBets(COME_10,1);
               player->loseHandBets(DONT_10);
               player->loseHandBets(LAY_10);
               player->loseHandBets(DFREE_10);
               if (die1->getNumber()==die2->getNumber()) player->winHandBets(HARD_10,7);
                 else player->loseHandBets(HARD_10);
               player->winHandBets(PLACE_10,1.8);
               player->winHandBets(BUY_10,2);
               player->winHandBets(FREE_10,2);
               break;
       case 11:player->winHandBets(FIELD,1);
               break;
       case 12:player->winHandBets(FIELD,2);
               break;
        }
      showBets();
      if (player->getHandBet(COME)>0) {
        switch (dice) {
          case 7:
          case 11:player->winHandBets(COME,1);
                  showBets();
                  break;
          case 2:
          case 3: player->loseHandBets(COME);
                  showBets();
                  break;
          case 12: player->loseHandBets(COME);
                  showBets();
                  break;
          case  4:fBet=player->getHandBet(COME);
                  player->moveHandBet(COME,COME_4,293,164);
//                  player->winHandBets(COME,0);
//                  player->placeBet(fBet,COME_4,1,1);
                  showBets();
                  break;
          case  5:fBet=player->getHandBet(COME);
                  player->moveHandBet(COME,COME_5,349,164);
//                  player->winHandBets(COME,0);
//                  player->placeBet(fBet,COME_5,1,1);
                  showBets();
                  break;
          case  6:fBet=player->getHandBet(COME);
                  player->moveHandBet(COME,COME_6,405,164);
//                  player->winHandBets(COME,0);
//                  player->placeBet(fBet,COME_6,1,1);
                  showBets();
                  break;
          case  8:fBet=player->getHandBet(COME);
                  player->moveHandBet(COME,COME_8,460,164);
//                  player->winHandBets(COME,0);
//                  player->placeBet(fBet,COME_8,1,1);
                  showBets();
                  break;
          case  9:fBet=player->getHandBet(COME);
                  player->moveHandBet(COME,COME_9,516,164);
//                  player->winHandBets(COME,0);
//                  player->placeBet(fBet,COME_9,1,1);
                  showBets();
                  break;
          case 10:fBet=player->getHandBet(COME);
                  player->moveHandBet(COME,COME_10,572,164);
//                  player->winHandBets(COME,0);
//                  player->placeBet(fBet,COME_10,1,1);
                  showBets();
                  break;
          }
        }
      if (player->getHandBet(DONT_COME)>0) {
        switch (dice) {
          case 7:
          case 11:player->loseHandBets(DONT_COME);
                  showBets();
                  break;
          case 2:
          case 3: player->winHandBets(DONT_COME,1);
                  showBets();
                  break;
          case 12: player->winHandBets(DONT_COME,0);
                  showBets();
                  break;
          case  4:player->moveHandBet(DONT_COME,DONT_4,298,41);
                  showBets();
                  break;
          case  5:player->moveHandBet(DONT_COME,DONT_5,354,41);
                  showBets();
                  break;
          case  6:player->moveHandBet(DONT_COME,DONT_6,410,41);
                  showBets();
                  break;
          case  8:player->moveHandBet(DONT_COME,DONT_8,465,41);
                  showBets();
                  break;
          case  9:player->moveHandBet(DONT_COME,DONT_9,521,41);
                  showBets();
                  break;
          case 10:player->moveHandBet(DONT_COME,DONT_10,577,41);
                  showBets();
                  break;
          }
        }
      if (point==0) {
        if (dice==7 || dice==11) {
          player->winHandBets(PASS,1);
          player->loseHandBets(DONT_PASS);
          showBets();
          }
        else if (dice==2 || dice==3) {
          player->loseHandBets(PASS);
          player->winHandBets(DONT_PASS,1);
          showBets();
          }
        else if (dice==12) {
          player->loseHandBets(PASS);
          player->winHandBets(DONT_PASS,0);
          showBets();
          }
        else {
          point=dice;
          showBets();
          }
        }
      else {
        if (dice==7) {
          player->loseHandBets(PASS);
          player->winHandBets(DONT_PASS,1);
          point=0;
          }
        if (dice==point) {
          point=0; showBets();
          player->loseHandBets(FREE_DONT);
          }
        }
  drawBoard();
  Delay(5);
#ifdef GRAPHIC
  gc=rcs_openGC(display,mainScreen);
  rcs_copyArea(display,table,mainScreen,gc,0,0,800,600,0,0);
  player->clearWonBets();
  if (dice==7) player->clearAllBets();
  rcs_closeGC(display,gc);
  drawBoard();
#endif
      } else flag='X';
    }
#ifdef GRAPHIC
  rcs_closePixmap(display,table);
#endif
}
