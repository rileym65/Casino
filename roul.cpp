#include "header.h"
#include "roul.h"

#ifdef GRAPHIC
#include "images/roulette.xpm"
#endif

Roul::Roul(Player* p,int minbet)
{
  player=p;
  minBet=minbet;
  betAmount=1;
}

void Roul::showBets() {
  player->paintBets();
  }

float Roul::placeBet() {
  char  flag;
#ifdef GRAPHIC
  rcs_Event event;
  rcs_GC    gc;
  rcs_Font  font;
  showBetAmount();
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
               if (event.d2>=80 && event.d2<93 &&
                   event.d3>224 && event.d3<=395) {
                 player->placeBet(betAmount,0,event.d2,event.d3);
                 showBets();
                 showPlayer();
                 }
               if (event.d2>=41 && event.d2<80 &&
                   event.d3>224 && event.d3<=395) {
                 player->placeBet(betAmount,0,event.d2,event.d3);
                 showBets();
                 showPlayer();
                 }
             if (event.d2>=93 && event.d2<=705 &&
                 event.d3>=212 && event.d3<406) {
                 player->placeBet(betAmount,0,event.d2,event.d3);
                 showBets();
                 showPlayer();
                 }

             if (event.d3>407 && event.d3<=456) {
               if ((event.d2>=92 && event.d2<=292) ||
                   (event.d2>=301 && event.d2<=500) ||
                   (event.d2>=508 && event.d2<=708)) {
                 player->placeBet(betAmount,0,event.d2,event.d3);
                 showBets();
                 showPlayer();
                 }
               }
             if (event.d3>466 && event.d3<=518) {
               if ((event.d2>=92 && event.d2<=187) ||
                   (event.d2>=300 && event.d2<=395) ||
                   (event.d2>=405 && event.d2<=499) ||
                   (event.d2>=196 && event.d2<=292) ||
                   (event.d2>=509 && event.d2<=604) ||
                   (event.d2>=612 && event.d2<=708)) {
                 player->placeBet(betAmount,0,event.d2,event.d3);
                 showBets();
                 showPlayer();
                 }
               }
             if (event.d2>716 && event.d2<=760) {
               if ((event.d3>=221 && event.d3<=274) ||
                   (event.d3>=283 && event.d3<=336) ||
                   (event.d3>=344 && event.d3<=397)) {
                 player->placeBet(betAmount,0,event.d2,event.d3);
                 showBets();
                 showPlayer();
                 }
               }
             }
           if (event.d1 == 1 && event.d3>=566 && event.d3<=598) {
             if (event.d1 == 1 && event.d2>=180 && event.d2<=289) {
               flag='P';
               }
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
  if (flag!='P' && flag!='D') return 0;
    else return 1;
  }

void Roul::showPlayer() {
#ifdef GRAPHIC
  rcs_GC gc;
  rcs_Font font;
  char     buffer[80];
  gc=rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"darkgreen");
  rcs_drawFilledBox(display,mainScreen,gc,377,529,150,28);
  rcs_namedForeground(display,gc,"yellow");
  font=rcs_openFont(display,BET_FONT);
  rcs_setFont(display,gc,font);
  sprintf(buffer,"%s $%12.2f",player->getName(),player->money());
  rcs_drawString(display,mainScreen,gc,385,544,buffer);
  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  displayScreen();
#endif
  }

void Roul::showBetAmount() {
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

void Roul::drawBoard()
{
#ifdef GRAPHIC
  rcs_GC gc;
  gc=rcs_openGC(display,mainScreen);
  rcs_copyArea(display,table,mainScreen,gc,0,0,800,600,0,0);
  rcs_closeGC(display,gc);
  showPlayer();
#endif
#ifdef CONSOLE
  ClrScr();
  Output("     +----+----+----+----+----+----+----+----+----+----+----+----+-----+\n");
  Output("+----+  3 |  6 |  9 | 12 | 15 | 18 | 21 | 24 | 27 | 30 | 33 | 36 | 2-1 |\n");
  Output("| 00 +----+----+----+----+----+----+----+----+----+----+----+----+-----+\n");
  Output("+----+  2 |  5 |  8 | 11 | 14 | 17 | 20 | 23 | 26 | 29 | 32 | 35 | 2-1 |\n");
  Output("|  0 +----+----+----+----+----+----+----+----+----+----+----+----+-----+\n");
  Output("+----+  1 |  4 |  7 | 10 | 13 | 16 | 19 | 22 | 25 | 28 | 31 | 34 | 2-1 |\n");
  Output("     +----+----+----+----+----+----+----+----+----+----+----+----+-----+\n");
  Output("     |      1st 12       |      2nd 12       |      3rd 12       |\n");
  Output("     +---------+---------+---------+---------+---------+---------+\n");
  Output("     | 1 to 18 |  Even   |   Red   |  Black  |   Odd   | 19 to 36|\n");
  Output("     +---------+---------+---------+---------+---------+---------+\n");
#endif
}

int Roul::findColumn(int number)
{
  int r;
  if ((number % 3)==0) r=3;
  if (((number+1) % 3)==0) r=2;
  if (((number+2) % 3)==0) r=1;
  return r;
}

int Roul::findRow(int number)
{
  int r;
  r=(number-1)/3;
  return (r+1);
}

void Roul::findXY(int number,int* x,int* y)
{
#ifdef GRAPHIC
  *x=114+52*(findRow(number)-1);
  *y=369-61*(findColumn(number)-1);
#endif
#ifdef CONSOLE
  *x=5*findRow(number)+4;
  *y=8-(findColumn(number)*2);
#endif
}

float Roul::insideBets()
{
  int   x,y;
  int   number;
  char  *bPtr;
  char  *dPtr;
  char  temp[20];
  float ret;
  float Bet;
  float amount;
  GotoXY(5,17); Output("Bet amount $ ");
  Input(buffer);
  sscanf(buffer,"%f",&Bet);
  ret=0;
  if (Bet>0) {
    Output("<S>ingle, <H>oriz. Split, <V>ert. Split, <T>rio, <C>orner\n");
    Output("<5> number bet, <B>lock, <N>one ?");
    Input(buffer);
    GotoXY(5,17); Output("                                    \n");
    Output("                                                                        \n");
    Output("                                                                        \n");
    bPtr=buffer;
    GotoXY(5,17);
    if (Upcase(buffer[0])=='T') {
      Output("Enter Trios :");
      Input(buffer);
      while (*bPtr!='\0') {
        dPtr=temp;
        while (*bPtr>='0' && *bPtr<='9') *dPtr++=*bPtr++;
        *dPtr='\0';
        sscanf(temp,"%d",&number);
        if (number>=1 && number<=36) {
          ret+=Bet;
          findXY(number,&x,&y);
          amount=player->placeBet(Bet,0,x,7);
          }
        while (*bPtr==' ' || *bPtr==',') bPtr++;
        }
      }
    else if (Upcase(buffer[0])=='5') {
      ret+=Bet;
      amount=player->placeBet(Bet,0,6,7);
      }
    else if (Upcase(buffer[0])=='B') {
      Output("Enter Blocks :");
      Input(buffer);
      while (*bPtr!='\0') {
        dPtr=temp;
        while (*bPtr>='0' && *bPtr<='9') *dPtr++=*bPtr++;
        *dPtr='\0';
        sscanf(temp,"%d",&number);
        if (number>=1 && number<=33) {
          ret+=Bet;
          findXY(number,&x,&y);
          amount=player->placeBet(Bet,0,x+2,7);
          }
        while (*bPtr==' ' || *bPtr==',') bPtr++;
        }
      }
    else if (Upcase(buffer[0])=='C') {
      Output("Enter Corners :");
      Input(buffer);
      while (*bPtr!='\0') {
        dPtr=temp;
        while (*bPtr>='0' && *bPtr<='9') *dPtr++=*bPtr++;
        *dPtr='\0';
        sscanf(temp,"%d",&number);
        if (number>=1 && number<=33 && findColumn(number)>1) {
          ret+=Bet;
          findXY(number,&x,&y);
          amount=player->placeBet(Bet,0,x+2,y+1);
          }
        while (*bPtr==' ' || *bPtr==',') bPtr++;
        }
      }
    else if (Upcase(buffer[0])=='S') {
      Output("Enter Singles :");
      Input(buffer);
      while (*bPtr!='\0') {
        dPtr=temp;
        while (*bPtr>='0' && *bPtr<='9') *dPtr++=*bPtr++;
        *dPtr='\0';
        sscanf(temp,"%d",&number);
        if (number>=1 && number<=36) {
          ret+=Bet;
          findXY(number,&x,&y);
          amount=player->placeBet(Bet,0,x-1,y);
          }
        else if (strcmp(temp,"00")==0) {
          ret+=Bet;
          amount=player->placeBet(Bet,0,3,3);
          }
        else if (strcmp(temp,"0")==0) {
          ret+=Bet;
          amount=player->placeBet(Bet,0,3,5);
          }
        while (*bPtr==' ' || *bPtr==',') bPtr++;
        }
      }
    else if (Upcase(buffer[0])=='V') {
      Output("Enter Vertical Splits :");
      Input(buffer);
      while (*bPtr!='\0') {
        dPtr=temp;
        while (*bPtr>='0' && *bPtr<='9') *dPtr++=*bPtr++;
        *dPtr='\0';
        sscanf(temp,"%d",&number);
        if (number>=1 && number<=36 && findColumn(number)>1) {
          ret+=Bet;
          findXY(number,&x,&y);
          amount=player->placeBet(Bet,0,x,y+1);
          }
        while (*bPtr==' ' || *bPtr==',') bPtr++;
        }
      }
    else if (Upcase(buffer[0])=='H') {
      Output("Enter Vertical Splits :");
      Input(buffer);
      while (*bPtr!='\0') {
        dPtr=temp;
        while (*bPtr>='0' && *bPtr<='9') *dPtr++=*bPtr++;
        *dPtr='\0';
        sscanf(temp,"%d",&number);
        if (number>=1 && number<=33) {
          ret+=Bet;
          findXY(number,&x,&y);
          amount=player->placeBet(Bet,0,x+2,y);
          }
        while (*bPtr==' ' || *bPtr==',') bPtr++;
        }
      }
    player->showBets();
    }
  buffer[0]='\0';
  GotoXY(5,17); Output("                                    \n");
  Output("                                                                        \n");
  Output("                                                                        \n");
  if (amount) ;
  return ret;
}

float Roul::outsideBets()
{
  float ret;
  float Bet;
  GotoXY(5,17); Output("Bet amount $ ");
  Input(buffer);
  sscanf(buffer,"%f",&Bet);
  ret=0;
  if (Bet>0) {
    Output("<F>irst 12, <S>econd 12, <T>hird 12, <E>ven, <Odd>, <R>ed, <B>lack\n");
    Output("1 to 1<8>, 19 to 3<6>, Column <1>, Column <2>, Column <3>, <N>one ?");
    Input(buffer);
    if (Upcase(buffer[0])=='F') {
      ret=Bet;
      Bet=player->placeBet(Bet,0,10,8);
      }
    else if (Upcase(buffer[0])=='S') {
      ret=Bet;
      Bet=player->placeBet(Bet,0,30,8);
      }
    else if (Upcase(buffer[0])=='T') {
      ret=Bet;
      Bet=player->placeBet(Bet,0,50,8);
      }
    else if (Upcase(buffer[0])=='E') {
      ret=Bet;
      Bet=player->placeBet(Bet,0,24,10);
      }
    else if (Upcase(buffer[0])=='O') {
      ret=Bet;
      Bet=player->placeBet(Bet,0,54,10);
      }
    else if (Upcase(buffer[0])=='R') {
      ret=Bet;
      Bet=player->placeBet(Bet,0,34,10);
      }
    else if (Upcase(buffer[0])=='B') {
      ret=Bet;
      Bet=player->placeBet(Bet,0,44,10);
      }
    else if (Upcase(buffer[0])=='8') {
      ret=Bet;
      Bet=player->placeBet(Bet,0,12,10);
      }
    else if (Upcase(buffer[0])=='6') {
      ret=Bet;
      Bet=player->placeBet(Bet,0,63,10);
      }
    else if (Upcase(buffer[0])=='1') {
      ret=Bet;
      Bet=player->placeBet(Bet,0,69,6);
      }
    else if (Upcase(buffer[0])=='2') {
      ret=Bet;
      Bet=player->placeBet(Bet,0,69,4);
      }
    else if (Upcase(buffer[0])=='3') {
      ret=Bet;
      Bet=player->placeBet(Bet,0,69,2);
      }
    player->showBets();
    }
  GotoXY(5,17); Output("                                    \n");
  Output("                                                                        \n");
  Output("                                                                        \n");
  buffer[0]='\0';
  return ret;
}

void Roul::play()
{
  float Bet;
  int number;
  int x,y;
  char Color;
#ifdef GRAPHIC
  rcs_GC gc;
  rcs_Font font;
  table=rcs_xpmToPixmap(display,mainWindow,roulette_xpm);
#endif
  drawBoard();
  Bet=1;
  while (Bet!=0) {  
    Bet=placeBet();
#ifdef CONSOLE
    buffer[0]='\n';
    Bet=0;
    while (Upcase(buffer[0])!='S' && Upcase(buffer[0])!='Q') {
      GotoXY(5,15);
      sprintf(buffer,"Money $%12.2f\n",player->money());
      Output(buffer);
      Output("<I>nside bets, <O>utside bets, <S>pin, <Q>uit ?");
      Input(buffer);
      if (Upcase(buffer[0])=='O') Bet+=outsideBets();
      else if (Upcase(buffer[0])=='I') Bet+=insideBets();
      else if (Upcase(buffer[0])=='S' && Bet<minBet) buffer[0]='\0';
      }
#endif
    if (Bet>0) {
      number=Random(38)+1;
      findXY(number,&x,&y);
      if (number<37) Color='B'; else Color='G';
      switch (number) {
        case 1: case 3: case 5: case 7: case 9: case 12: case 14: case 16:
        case 18: case 19: case 21: case 23: case 25: case 27: case 30:
        case 32: case 34: case 36:
          Color='R';
        }
#ifdef GRAPHIC
      if (number<=36) {
// direct number win
        player->winXYBets(x-21,y-24,x+18,y+24,35);
// Pair with up
        if (findColumn(number)!=3) player->winXYBets(x-21,y-36,x+19,y-25,17);
// Pair with down
        if (findColumn(number)!=1) player->winXYBets(x-21,y+25,x+19,y+36,17);
// Pair with left
        if (number>3) player->winXYBets(x-33,y-24,x-22,y+24,17);
// Pair with right
        if (number<34) player->winXYBets(x+19,y-24,x+30,y+24,17);
// quad upper left
        if (number>3 && findColumn(number)!=3)
          player->winXYBets(x-33,y-36,x-22,y-25,8);
// quad upper right
        if (number<34 && findColumn(number)!=3)
          player->winXYBets(x+19,y-36,x+30,y-25,8);
// quad lower left
        if (number>3 && findColumn(number)!=1)
          player->winXYBets(x-33,y+25,x-22,y+36,8);
// quad lower right
        if (number<34 && findColumn(number)!=1)
          player->winXYBets(x+19,y+25,x+30,y+36,8);
// Row, top
        player->winXYBets(x-21,211,x+19,222,11);
// Row, bottom
        player->winXYBets(x-21,394,x+19,405,11);
// Block, top left
        if (number>3) player->winXYBets(x-33,211,x-22,222,5);
// Block, top right
        if (number<34) player->winXYBets(x+19,211,x+30,222,5);
// Block, bottom left
        if (number>3) player->winXYBets(x-33,394,x-22,405,5);
// Block, bottom right
        if (number<34) player->winXYBets(x+19,394,x+30,405,5);

        if (number>=1 && number<=12) player->winXYBets(92,408,292,456,2);
        if (number>=13 && number<=24) player->winXYBets(301,408,500,456,2);
        if (number>=25 && number<=36) player->winXYBets(508,408,708,456,2);
        if (number>=1 && number<=18) player->winXYBets(92,466,187,518,1);
        if (number>=19 && number<=36) player->winXYBets(612,466,708,518,1);
        if (Color=='R') player->winXYBets(300,466,395,518,1);
        if (Color=='B') player->winXYBets(405,466,499,518,1);
        if ((number & 1)==1) player->winXYBets(509,466,604,518,1);
        if ((number & 1)==0) player->winXYBets(196,466,292,518,1);
        if ((number % 3)==0) player->winXYBets(716,221,760,274,2);
        if (((number+1) % 3)==0) player->winXYBets(716,283,760,336,2);
        if (((number+2) % 3)==0) player->winXYBets(716,344,760,397,2);
        } else if (number==37) {
        player->winXYBets(41,317,79,397,35);
        player->winXYBets(41,301,79,316,17);
        } else if (number==38) {
        player->winXYBets(41,222,79,300,35);
        player->winXYBets(41,301,79,316,17);
        }
      if (number>36 || number<4) player->winXYBets(80,301,92,316,6);
      if (number==37 || number==1) player->winXYBets(80,317,92,395,17);
      if (number==38 || number==3) player->winXYBets(80,224,92,300,17);
#endif
#ifdef CONSOLE
      sprintf(buffer,"%d ",number);
      if (number==37) strcpy(buffer,"0 ");
      if (number==38) strcpy(buffer,"00 ");
      GotoXY(5,13); Output(buffer); 
      if (Color=='R') Output("Red\n"); 
        else if (Color=='B') Output("Black\n");
        else Output("\n");
      if (number==37)
        player->winXYBets(3,5,3,5,36); /* 0 */
      if (number==38)
        player->winXYBets(3,3,3,3,36); /* 00 */
      if (number<4 || number>36)
        player->winXYBets(6,7,6,7,7); /* 5 number */
      if (number<37) {
        if (number>=1 && number<=18) player->winXYBets(12,10,12,10,2);
        if (number>=19 && number<=36) player->winXYBets(63,10,63,10,2);
        if (number>=1 && number<=12) player->winXYBets(10,8,10,8,3);
        if (number>=13 && number<=24) player->winXYBets(30,8,30,8,3);
        if (number>=25 && number<=36) player->winXYBets(50,8,50,8,3);
        if ((number & 1)==1) player->winXYBets(54,10,54,10,2);
        if ((number & 1)==0) player->winXYBets(24,10,24,10,2);
        if (Color=='R') player->winXYBets(34,10,34,10,2);
        if (Color=='B') player->winXYBets(44,10,44,10,2);
        if ((number % 3)==0) player->winXYBets(69,2,69,2,3);
        if (((number+1) % 3)==0)  player->winXYBets(69,4,69,4,3);
        if (((number+2) % 3)==0)  player->winXYBets(69,6,69,6,3);

        player->winXYBets(x-1,y,x-1,y,36); /* single */
        player->winXYBets(x+2,y,x+2,y,18); /* split */
        player->winXYBets(x-3,y,x-3,y,18); /* split */
        if (findColumn(number)>1)
          player->winXYBets(x,y+1,x,y+1,18); /* split */
        player->winXYBets(x,y-1,x,y-1,18); /* split */
        player->winXYBets(x,7,x,7,12);     /* trio */
        player->winXYBets(x+2,y-1,x+2,y-1,9); /* Corner */
        player->winXYBets(x-3,y-1,x-3,y-1,9); /* Corner */
        if (findColumn(number)>1) {
          player->winXYBets(x+2,y+1,x+2,y+1,9); /* Corner */
          player->winXYBets(x-3,y+1,x-3,y+1,9); /* Corner */
          }
        if (findRow(number)>1)
          player->winXYBets(x-3,7,x-3,7,6); /* Block */
        if (findRow(number)<12)
          player->winXYBets(x+2,7,x+2,7,6); /* Block */
        }
#endif
      drawBoard();
      player->clearNonWinners();
      showBets();
      gc=rcs_openGC(display,mainScreen);
      rcs_namedForeground(display,gc,"yellow");
      rcs_drawFilledBox(display,mainScreen,gc,370,120,60,60);
      switch (Color) {
        case 'R':rcs_namedForeground(display,gc,"red"); break;
        case 'B':rcs_namedForeground(display,gc,"black"); break;
        case 'G':rcs_namedForeground(display,gc,"darkgreen"); break;
        }
      rcs_drawFilledBox(display,mainScreen,gc,375,125,50,50);
      rcs_namedForeground(display,gc,"white");
      font=rcs_openFont(display,ROULETTE_FONT);
      rcs_setFont(display,gc,font);
      if (number<37) sprintf(buffer,"%2d",number);
      else if (number==37) sprintf(buffer,"0");
      else if (number==38) sprintf(buffer,"00");
      rcs_drawString(display,mainScreen,gc,390,155,buffer);
      rcs_closeFont(display,font);
      rcs_closeGC(display,gc);
      displayScreen();
      Delay(5);
      player->clearAllBets();
      drawBoard();
      }
    }
#ifdef GRAPHIC
  rcs_closePixmap(display,table);
#endif
}
