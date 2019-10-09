#include "header.h"
#include "keno.h"

#ifdef GRAPHIC
#include "images/keno.xpm"
#endif

Keno::Keno(Player* p)
{
  int i;
  player=p;
  betAmount=1;
  for (i=0; i<80; i++) balls[i] = i+1;
  shuffle();
}

void Keno::shuffle() {
  int p1,p2;
  int t;
  for (p1=0; p1<80; p1++) {
    p2 = Random(80);
    t=balls[p1]; balls[p1] = balls[p2]; balls[p2] = t;
    }
  }

void Keno::showPayouts() {
#ifdef GRAPHIC
  rcs_GC gc;
  rcs_Font font;
  gc=rcs_openGC(display,mainScreen);
  font=rcs_openFont(display,KENO_FONT);
  rcs_copyArea(display,table,mainScreen,gc,412,342,306,203,412,342);
  rcs_setFont(display,gc,font);
  rcs_namedForeground(display,gc,"black");
  switch(count) {
    case 1:rcs_drawString(display,mainScreen,gc,420,382," 1: 3\n");
           break;
    case 2:rcs_drawString(display,mainScreen,gc,420,382," 2: 12\n");
           break;
    case 3:rcs_drawString(display,mainScreen,gc,420,382," 2: 1\n");
           rcs_drawString(display,mainScreen,gc,420,402," 3: 43\n");
           break;
    case 4:rcs_drawString(display,mainScreen,gc,420,382," 2: 1\n");
           rcs_drawString(display,mainScreen,gc,420,402," 3: 3\n");
           rcs_drawString(display,mainScreen,gc,420,422," 4: 130\n");
           break;
    case 5:rcs_drawString(display,mainScreen,gc,420,382," 3: 1\n");
           rcs_drawString(display,mainScreen,gc,420,402," 4: 10\n");
           rcs_drawString(display,mainScreen,gc,420,422," 5: 800\n");
           break;
    case 6:rcs_drawString(display,mainScreen,gc,420,382," 3: 1\n");
           rcs_drawString(display,mainScreen,gc,420,402," 4: 4\n");
           rcs_drawString(display,mainScreen,gc,420,422," 5: 95\n");
           rcs_drawString(display,mainScreen,gc,420,442," 6: 1500\n");
           break;
    case 7:rcs_drawString(display,mainScreen,gc,420,382," 4: 1\n");
           rcs_drawString(display,mainScreen,gc,420,402," 5: 25\n");
           rcs_drawString(display,mainScreen,gc,420,422," 6: 350\n");
           rcs_drawString(display,mainScreen,gc,420,442," 7: 8000\n");
           break;
    case 8:rcs_drawString(display,mainScreen,gc,420,382," 5: 9\n");
           rcs_drawString(display,mainScreen,gc,420,402," 6: 90\n");
           rcs_drawString(display,mainScreen,gc,420,422," 7: 1500\n");
           rcs_drawString(display,mainScreen,gc,420,442," 8: 25000\n");
           break;
    case 9:rcs_drawString(display,mainScreen,gc,420,382," 5: 4\n");
           rcs_drawString(display,mainScreen,gc,420,402," 6: 50\n");
           rcs_drawString(display,mainScreen,gc,420,422," 7: 280\n");
           rcs_drawString(display,mainScreen,gc,420,442," 8: 4000\n");
           rcs_drawString(display,mainScreen,gc,420,462," 9: 50000\n");
           break;
   case 10:rcs_drawString(display,mainScreen,gc,420,382," 5: 1\n");
           rcs_drawString(display,mainScreen,gc,420,402," 6: 22\n");
           rcs_drawString(display,mainScreen,gc,420,422," 7: 150\n");
           rcs_drawString(display,mainScreen,gc,420,442," 8: 1000\n");
           rcs_drawString(display,mainScreen,gc,420,462," 9: 5000\n");
           rcs_drawString(display,mainScreen,gc,420,482,"10: 100000\n");
           break;
   case 11:rcs_drawString(display,mainScreen,gc,420,382," 6: 8\n");
           rcs_drawString(display,mainScreen,gc,420,402," 7: 80\n");
           rcs_drawString(display,mainScreen,gc,420,422," 8: 400\n");
           rcs_drawString(display,mainScreen,gc,420,442," 9: 2500\n");
           rcs_drawString(display,mainScreen,gc,420,462,"10: 25000\n");
           rcs_drawString(display,mainScreen,gc,420,482,"11: 100000\n");
           break;
   case 12:rcs_drawString(display,mainScreen,gc,420,382," 6: 5\n");
           rcs_drawString(display,mainScreen,gc,420,402," 7: 32\n");
           rcs_drawString(display,mainScreen,gc,420,422," 8: 200\n");
           rcs_drawString(display,mainScreen,gc,420,442," 9: 1000\n");
           rcs_drawString(display,mainScreen,gc,420,462,"10: 5000\n");
           rcs_drawString(display,mainScreen,gc,420,482,"11: 25000\n");
           rcs_drawString(display,mainScreen,gc,420,502,"12: 100000\n");
           break;
   case 13:rcs_drawString(display,mainScreen,gc,420,382," 0: 1\n");
           rcs_drawString(display,mainScreen,gc,420,402," 6: 1\n");
           rcs_drawString(display,mainScreen,gc,420,422," 7: 20\n");
           rcs_drawString(display,mainScreen,gc,420,442," 8: 80\n");
           rcs_drawString(display,mainScreen,gc,420,462," 9: 600\n");
           rcs_drawString(display,mainScreen,gc,420,482,"10: 3500\n");
           rcs_drawString(display,mainScreen,gc,550,382,"11: 10000\n");
           rcs_drawString(display,mainScreen,gc,550,402,"12: 50000\n");
           rcs_drawString(display,mainScreen,gc,550,422,"13: 100000\n");
           break;
   case 14:rcs_drawString(display,mainScreen,gc,420,382," 0: 1\n");
           rcs_drawString(display,mainScreen,gc,420,402," 6: 1\n");
           rcs_drawString(display,mainScreen,gc,420,422," 7: 9\n");
           rcs_drawString(display,mainScreen,gc,420,442," 8: 42\n");
           rcs_drawString(display,mainScreen,gc,420,462," 9: 310\n");
           rcs_drawString(display,mainScreen,gc,420,482,"10: 1100\n");
           rcs_drawString(display,mainScreen,gc,550,382,"11: 8000\n");
           rcs_drawString(display,mainScreen,gc,550,402,"12: 25000\n");
           rcs_drawString(display,mainScreen,gc,550,422,"13: 50000\n");
           rcs_drawString(display,mainScreen,gc,550,442,"14: 100000\n");
           break;
   case 15:rcs_drawString(display,mainScreen,gc,420,382," 0: 1\n");
           rcs_drawString(display,mainScreen,gc,420,402," 7: 10\n");
           rcs_drawString(display,mainScreen,gc,420,422," 8: 25\n");
           rcs_drawString(display,mainScreen,gc,420,442," 9: 100\n");
           rcs_drawString(display,mainScreen,gc,420,462,"10: 300\n");
           rcs_drawString(display,mainScreen,gc,420,482,"11: 2800\n");
           rcs_drawString(display,mainScreen,gc,550,382,"12: 25000\n");
           rcs_drawString(display,mainScreen,gc,550,402,"13: 50000\n");
           rcs_drawString(display,mainScreen,gc,550,422,"14: 100000\n");
           rcs_drawString(display,mainScreen,gc,550,442,"15: 100000\n");
           break;
    }
  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  displayScreen();
#endif
#ifdef CONSOLE
      switch(count) {
        case 1:GotoXY(50,2); Output(" 1: 3\n");
               break;
        case 2:GotoXY(50,2); Output(" 2: 12\n");
               break;
        case 3:GotoXY(50,2); Output(" 2:  1\n");
               GotoXY(50,3); Output(" 3: 43\n");
               break;
        case 4:GotoXY(50,2); Output(" 2:   1\n");
               GotoXY(50,3); Output(" 3:   3\n");
               GotoXY(50,4); Output(" 4: 130\n");
               break;
        case 5:GotoXY(50,2); Output(" 3:   1\n");
               GotoXY(50,3); Output(" 4:  10\n");
               GotoXY(50,4); Output(" 5: 800\n");
               break;
        case 6:GotoXY(50,2); Output(" 3:    1\n");
               GotoXY(50,3); Output(" 4:    4\n");
               GotoXY(50,4); Output(" 5:   95\n");
               GotoXY(50,5); Output(" 6: 1500\n");
               break;
        case 7:GotoXY(50,2); Output(" 4:    1\n");
               GotoXY(50,3); Output(" 5:   25\n");
               GotoXY(50,4); Output(" 6:  350\n");
               GotoXY(50,5); Output(" 7: 8000\n");
               break;
        case 8:GotoXY(50,2); Output(" 5:     9\n");
               GotoXY(50,3); Output(" 6:    90\n");
               GotoXY(50,4); Output(" 7:  1500\n");
               GotoXY(50,5); Output(" 8: 25000\n");
               break;
        case 9:GotoXY(50,2); Output(" 5:     4\n");
               GotoXY(50,3); Output(" 6:    50\n");
               GotoXY(50,4); Output(" 7:   280\n");
               GotoXY(50,5); Output(" 8:  4000\n");
               GotoXY(50,6); Output(" 9: 50000\n");
               break;
       case 10:GotoXY(50,2); Output(" 5:      1\n");
               GotoXY(50,3); Output(" 6:     22\n");
               GotoXY(50,4); Output(" 7:    150\n");
               GotoXY(50,5); Output(" 8:   1000\n");
               GotoXY(50,6); Output(" 9:   5000\n");
               GotoXY(50,7); Output("10: 100000\n");
               break;
       case 11:GotoXY(50,3); Output(" 6:      8\n");
               GotoXY(50,4); Output(" 7:     80\n");
               GotoXY(50,5); Output(" 8:    400\n");
               GotoXY(50,6); Output(" 9:   2500\n");
               GotoXY(50,7); Output("10:  25000\n");
               GotoXY(50,8); Output("11: 100000\n");
               break;
       case 12:GotoXY(50,2); Output(" 6:      5\n");
               GotoXY(50,3); Output(" 7:     32\n");
               GotoXY(50,4); Output(" 8:    200\n");
               GotoXY(50,5); Output(" 9:   1000\n");
               GotoXY(50,6); Output("10:   5000\n");
               GotoXY(50,7); Output("11:  25000\n");
               GotoXY(50,8); Output("12: 100000\n");
               break;
       case 13:GotoXY(50,2); Output(" 0:      1\n");
               GotoXY(50,3); Output(" 6:      1\n");
               GotoXY(50,4); Output(" 7:     20\n");
               GotoXY(50,5); Output(" 8:     80\n");
               GotoXY(50,6); Output(" 9:    600\n");
               GotoXY(50,7); Output("10:   3500\n");
               GotoXY(50,8); Output("11:  10000\n");
               GotoXY(50,9); Output("12:  50000\n");
               GotoXY(50,10); Output("13: 100000\n");
               break;
       case 14:GotoXY(50,2);  Output(" 0:      1\n");
               GotoXY(50,3);  Output(" 6:      1\n");
               GotoXY(50,4);  Output(" 7:      9\n");
               GotoXY(50,5);  Output(" 8:     42\n");
               GotoXY(50,6);  Output(" 9:    310\n");
               GotoXY(50,7);  Output("10:   1100\n");
               GotoXY(50,8);  Output("11:   8000\n");
               GotoXY(50,9);  Output("12:  25000\n");
               GotoXY(50,10);  Output("13:  50000\n");
               GotoXY(50,11); Output("14: 100000\n");
               break;
       case 15:GotoXY(50,2);  Output(" 0:      1\n");
               GotoXY(50,3);  Output(" 7:     10\n");
               GotoXY(50,4);  Output(" 8:     25\n");
               GotoXY(50,5);  Output(" 9:    100\n");
               GotoXY(50,6);  Output("10:    300\n");
               GotoXY(50,7);  Output("11:   2800\n");
               GotoXY(50,8);  Output("12:  25000\n");
               GotoXY(50,9);  Output("13:  50000\n");
               GotoXY(50,10);  Output("14: 100000\n");
               GotoXY(50,11); Output("15: 100000\n");
               break;
        }
#endif
  }

void Keno::showPlayer() {
#ifdef GRAPHIC
  rcs_GC gc;
  rcs_Font font;
    gc=rcs_openGC(display,mainScreen);
    font=rcs_openFont(display,BET_FONT);
    rcs_setFont(display,gc,font);
    rcs_namedForeground(display,gc,"black");
    rcs_copyArea(display,table,mainScreen,gc,150,530,300,26,150,530);
    rcs_drawString(display,mainScreen,gc,150,550,player->getName());
    sprintf(buffer,"%8.0f",player->money());
    rcs_drawString(display,mainScreen,gc,250,550,buffer);
    rcs_closeFont(display,font);
    rcs_closeGC(display,gc);
    displayScreen();
#endif
  }

void Keno::showBetAmount() {
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



float Keno::placeBet() {
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
               event.d2>=252 && event.d2<=336 &&
               event.d3>=52 && event.d3<=85) {
             betReturn=player->placeBet(betAmount,0,293,68);
             gc=rcs_openGC(display,mainScreen);
             font=rcs_openFont(display,KENO_FONT);
             rcs_setFont(display,gc,font);
             sprintf(buffer,"$%ld",betAmount);
             rcs_drawString(display,mainScreen,gc,273,74,buffer);
             rcs_closeFont(display,font);
             rcs_closeGC(display,gc);
             displayScreen();
             rcs_namedForeground(display,gc,"black");
//             player->paintBets();
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
    GotoXY(1,18); Output("Bet $");
    Input(buffer);
    sscanf(buffer,"%f",&bet);
    GotoXY(1,18); Output("                  ");
      player->placeBet(bet,0,1,1);
#endif
  if (flag!='P' && flag!='D') return 0;
    else return betReturn;
  }

void Keno::selectNumbers() {
#ifdef GRAPHIC
  rcs_GC gc;
  rcs_Font font;
  rcs_Event event;
  char flag;
  int x,y,n;
#endif
  for (i=1;i<=80;i++) {
    playerNumbers[i]=0;
    gameNumbers[i]=0;
    }
#ifdef GRAPHIC
  gc=rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"gray");
  rcs_drawFilledBox(display,mainScreen,gc,150,430,80,29);
  rcs_namedForeground(display,gc,"black");
  rcs_drawBox(display,mainScreen,gc,152,430,76,25);
  font=rcs_openFont(display,BET_FONT);
  rcs_setFont(display,gc,font);
  rcs_drawString(display,mainScreen,gc,170,450,"Done");
  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  displayScreen();
  flag=' ';
  count=0;
  while (flag==' ') {
    event=getEvent(display);
    n=0;
    if (event.type == EVENT_BUTTON_PRESS && event.d1==1 &&
        event.d2>=150 && event.d2<=230 && event.d3>=430 && event.d3<=460) {
      flag='X';
      }
    if (event.type == EVENT_BUTTON_PRESS && event.d1==1 &&
        event.d2>=46 && event.d2<=336 && event.d3>=104 && event.d3<=219) {
      n=1+(event.d2-46)/29;
      y=(event.d3-104)/29;
      n+=y*10;
      }
    if (event.type == EVENT_BUTTON_PRESS && event.d1==1 &&
        event.d2>=46 && event.d2<=336 && event.d3>=246 && event.d3<=359) {
      n=1+(event.d2-46)/29;
      y=(event.d3-246)/29;
      n+=y*10+40;
      }
    if (n>0) {
      y=((n-1)/10)*29+104; x=((n-1)%10)*29+46;
      if (n>40) y+=26;
      if (playerNumbers[n]==0 && count<15) {
        count++;
        playerNumbers[n]=1;
        gc=rcs_openGC(display,mainScreen);
        rcs_namedForeground(display,gc,"black");
        rcs_drawLine(display,mainScreen,gc,x,y,x+27,y+27);
        rcs_drawLine(display,mainScreen,gc,x+27,y,x,y+27);
        rcs_closeGC(display,gc);
        displayScreen();
        } else if (playerNumbers[n]==1) {
        count--;
        playerNumbers[n]=0;
        gc=rcs_openGC(display,mainScreen);
        rcs_copyArea(display,table,mainScreen,gc,x,y,27,27,x,y);
        rcs_closeGC(display,gc);
        displayScreen();
        }
      showPayouts();
      }
    }
  gc=rcs_openGC(display,mainScreen);
  rcs_copyArea(display,table,mainScreen,gc,150,430,80,29,150,430);
  rcs_closeGC(display,gc);
#endif
#ifdef CONSOLE
      count=0;
      GotoXY(1,18); Output("numbers (s for same):");
      Input(buffer);
      if (buffer[0]=='s') strcpy(buffer,last); else strcpy(last,buffer);
      bPtr=buffer;
      while (*bPtr!='\0' && count<15) {
        dPtr=temp;
        while (*bPtr>='0' && *bPtr<='9') *dPtr++=*bPtr++;
        *dPtr='\0';
        sscanf(temp,"%d",&number);
        if (number>=1 && number<=80)
          if (playerNumbers[number]==0) {
            count++;
            playerNumbers[number]=1;
            }
        while (*bPtr==' ' || *bPtr==',') bPtr++;
        }
      for (i=1;i<81;i++) if (playerNumbers[i]==1) {
        if (i<41) {
          GotoXY(((i-1) % 10)*4+1,(i-1)/10*2+1); Output("(");
          GotoXY(((i-1) % 10)*4+4,(i-1)/10*2+1); Output(")");
          }
        else {
          GotoXY(((i-1) % 10)*4+1,(i-1)/10*2+2); Output("(");
          GotoXY(((i-1) % 10)*4+4,(i-1)/10*2+2); Output(")");
          }
        }
      GotoXY(1,18); Output("                                                                  ");
      for (i=2;i<15;i++) { GotoXY(50,i); Output("                  \n"); }
#endif
  }

void Keno::drawBoard()
{
#ifdef GRAPHIC
  rcs_GC gc;
  rcs_Font font;
  int x,y,i,j;
  gc=rcs_openGC(display,mainScreen);
  font=rcs_openFont(display,KENO_FONT);
  rcs_setFont(display,gc,font);
  rcs_copyArea(display,table,mainScreen,gc,0,0,800,600,0,0);
  rcs_namedForeground(display,gc,"black");
  x=425,y=71;
  j=0;
  for (i=1;i<81;i++) {
    sprintf(buffer,"%d",i);
    rcs_drawString(display,mainScreen,gc,x,y,buffer);
    x+=29;
    if (++j == 10) {
      j=0;
      x=425;
      y+=29;
      if (i==40) y+=25;
      }
    }
  rcs_closeGC(display,gc);
  displayScreen();
  showBetAmount();
#endif
#ifdef CONSOLE
  ClrScr();
  Output("  1   2   3   4   5   6   7   8   9  10 \n\n");
  Output(" 11  12  13  14  15  16  17  18  19  20 \n\n");
  Output(" 21  22  23  24  25  26  27  28  29  30 \n\n");
  Output(" 31  32  33  34  35  36  37  38  39  40 \n\n\n");
  Output(" 41  42  43  44  45  46  47  48  49  50 \n\n");
  Output(" 51  52  53  54  55  56  57  58  59  60 \n\n");
  Output(" 61  62  63  64  65  66  67  68  69  70 \n\n");
  Output(" 71  72  73  74  75  76  77  78  79  80 \n\n");
#endif
}

float Keno::checkNumbers()
{
  int   found;
  int   i;
  float ret;
  found=0;
  for (i=1;i<81;i++) if (playerNumbers[i]+gameNumbers[i]==2) found++;
#ifdef CONSOLE
  sprintf(buffer,"found: %d  \n",found);
  GotoXY(50,14); Output(buffer);
#endif
  ret=0;
  switch (count) {
    case 1:switch (found) {
             case 1:ret=3; break;
             }
           break;
    case 2:switch (found) {
             case 2:ret=12; break;
             }
           break;
    case 3:switch (found) {
             case 2:ret=1; break;
             case 3:ret=43; break;
             }
           break;
    case 4:switch (found) {
             case 2:ret=1; break;
             case 3:ret=3; break;
             case 4:ret=130; break;
             }
           break;
    case 5:switch (found) {
             case 3:ret=1; break;
             case 4:ret=10; break;
             case 5:ret=800; break;
             }
           break;
    case 6:switch (found) {
             case 3:ret=1; break;
             case 4:ret=4; break;
             case 5:ret=95; break;
             case 6:ret=1500; break;
             }
           break;
    case 7:switch (found) {
             case 4:ret=1; break;
             case 5:ret=25; break;
             case 6:ret=350; break;
             case 7:ret=8000; break;
             }
           break;
    case 8:switch (found) {
             case 5:ret=9; break;
             case 6:ret=90; break;
             case 7:ret=1500; break;
             case 8:ret=25000; break;
             }
           break;
    case 9:switch (found) {
             case 5:ret=4; break;
             case 6:ret=50; break;
             case 7:ret=280; break;
             case 8:ret=4000; break;
             case 9:ret=50000; break;
             }
           break;
    case 10:switch (found) {
             case 5:ret=1; break;
             case 6:ret=22; break;
             case 7:ret=150; break;
             case 8:ret=1000; break;
             case 9:ret=5000; break;
             case 10:ret=100000; break;
             }
           break;
    case 11:switch (found) {
             case 6:ret=8; break;
             case 7:ret=80; break;
             case 8:ret=400; break;
             case 9:ret=2500; break;
             case 10:ret=25000; break;
             case 11:ret=100000; break;
             }
           break;
    case 12:switch (found) {
             case 6:ret=5; break;
             case 7:ret=32; break;
             case 8:ret=200; break;
             case 9:ret=1000; break;
             case 10:ret=5000; break;
             case 11:ret=25000; break;
             case 12:ret=100000; break;
             }
           break;
    case 13:switch (found) {
             case 0:ret=1; break;
             case 6:ret=1; break;
             case 7:ret=20; break;
             case 8:ret=80; break;
             case 9:ret=600; break;
             case 10:ret=3500; break;
             case 11:ret=10000; break;
             case 12:ret=50000; break;
             case 13:ret=100000; break;
             }
           break;
    case 14:switch (found) {
             case 0:ret=1; break;
             case 6:ret=1; break;
             case 7:ret=9; break;
             case 8:ret=42; break;
             case 9:ret=310; break;
             case 10:ret=1100; break;
             case 11:ret=8000; break;
             case 12:ret=25000; break;
             case 13:ret=50000; break;
             case 14:ret=100000; break;
             }
           break;
    case 15:switch (found) {
             case 0:ret=1; break;
             case 7:ret=10; break;
             case 8:ret=25; break;
             case 9:ret=100; break;
             case 10:ret=300; break;
             case 11:ret=2800; break;
             case 12:ret=25000; break;
             case 13:ret=50000; break;
             case 14:ret=100000; break;
             case 15:ret=100000; break;
             }
           break;
    }
  return ret;
}

void Keno::pickNumbers()
{
  int i;
  int n;
#ifdef GRAPHIC
  rcs_GC gc;
  rcs_Font font;
  int x,y;
  gc=rcs_openGC(display,mainScreen);
  font=rcs_openFont(display,KENO_FONT);
  rcs_setFont(display,gc,font);
  shuffle();
#endif
  for (i=0;i<20;i++) {
    n = balls[i];
/*
    n=Random(80)+1;
    while (gameNumbers[n]!=0) n=Random(80)+1;
*/
    gameNumbers[n]=1;
#ifdef GRAPHIC
    x=((n-1)%10)*29 + 420;
    y=((n-1)/10)*29 + 50;
    if (n>40) y+=26;
    rcs_namedForeground(display,gc,"red");
    rcs_drawFilledBox(display,mainScreen,gc,x,y,27,27);
    rcs_namedForeground(display,gc,"black");
    sprintf(buffer,"%d",n);
    rcs_drawString(display,mainScreen,gc,x+5,y+20,buffer);
    if (playerNumbers[n]==1) {
      y=((n-1)/10)*29+104; x=((n-1)%10)*29+46;
      if (n>40) y+=26;
      rcs_drawFilledCircle(display,mainScreen,gc,x,y,27,27);
      }
    displayScreen();
#endif
#ifdef CONSOLE
    if (n<41) {
      GotoXY(((n-1) % 10)*4+2,(n-1)/10*2+1); Output("**");
      }
    else {
      GotoXY(((n-1) % 10)*4+2,(n-1)/10*2+2); Output("**");
      }
#endif
    Delay(1);
    }
#ifdef GRAPHIC
  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
#endif
}

void Keno::play()
{
  float bet;
  float ret;
  int   i;
  char  last[80];
#ifdef GRAPHIC
  rcs_GC gc;
  table=rcs_xpmToPixmap(display,mainWindow,keno_xpm);
#endif
  strcpy(last,player->getKenoLast());
  bet=1;
  while (bet!=0) {
    drawBoard();
    showPlayer();
    player->clearAllBets();
    bet=placeBet();
    showPlayer();
    if (bet>0) {
      for (i=1;i<=80;i++) {
        playerNumbers[i]=0;
        gameNumbers[i]=0;
        }
      selectNumbers();
      showPayouts();
      Delay(2);
      pickNumbers();
      ret=checkNumbers();
      if (ret>0) {
#ifdef CONSOLE
        GotoXY(1,20);
        sprintf(buffer,"Won $%6.0f",ret);
        Output(buffer);
#endif
        player->winHandBets(0,ret-1);
        }
      else {
#ifdef CONSOLE
        GotoXY(1,20);
        Output("                 ");
#endif
        player->loseHandBets(0);
        }
#ifdef GRAPHIC
      gc=rcs_openGC(display,mainScreen);
//      rcs_copyArea(display,table,mainScreen,gc,247,19,100,70,247,19);
      player->paintBets();
      displayScreen();
      rcs_closeGC(display,gc);
#endif
      showPlayer();
      Delay(5);
      }
    player->putKenoLast(last);
    }
  rcs_closePixmap(display,table);
}

