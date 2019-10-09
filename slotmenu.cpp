#include <stdlib.h>
#include "header.h"
#include "slotmach.h"

#ifdef GRAPHIC
#include "images/slotmenu.xpm"
#endif

void showBetAmount(long betAmount) {
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

void slotStats() {
  double ti,to;
  int i;
  char buffer[255];
#ifdef GRAPHIC
  rcs_GC gc;
  rcs_Font font;
  rcs_Event event;
  int  pos,space;
#endif
  ti=0; to=0;
  for (i=SLOTS_BASE;i<100;i++) {
    ti+=player[0]->paidIn(i);
    to+=player[0]->paidOut(i);
    }
  if (ti==0) ti=.0001;
#ifdef GRAPHIC
  gc=rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"darkgreen");
  rcs_drawFilledBox(display,mainScreen,gc,0,0,800,600);
  rcs_namedForeground(display,gc,"yellow");
  font=rcs_openFont(display,STAT_FONT);
  rcs_setFont(display,gc,font);
  pos=30;
  space=20;
  if (player[0]->paidIn(SLOTS_BASE+1)>0) {
    sprintf(buffer,"Bar Hop                     %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+1),
      player[0]->paidOut(SLOTS_BASE+1),
      player[0]->average(SLOTS_BASE+1));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+2)>0) {
    sprintf(buffer,"Wild Fruits                 %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+2),
      player[0]->paidOut(SLOTS_BASE+2),
      player[0]->average(SLOTS_BASE+2));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+3)>0) {
    sprintf(buffer,"Earthquake                  %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+3),
      player[0]->paidOut(SLOTS_BASE+3),
      player[0]->average(SLOTS_BASE+3));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+4)>0) {
    sprintf(buffer,"Double Fortune              %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+4),
      player[0]->paidOut(SLOTS_BASE+4),
      player[0]->average(SLOTS_BASE+4));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+5)>0) {
    sprintf(buffer,"Super 7s                    %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+5),
      player[0]->paidOut(SLOTS_BASE+5),
      player[0]->average(SLOTS_BASE+5));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+6)>0) {
    sprintf(buffer,"Side Winder                 %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+6),
      player[0]->paidOut(SLOTS_BASE+6),
      player[0]->average(SLOTS_BASE+6));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+7)>0) {
    sprintf(buffer,"4 Wheeler                   %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+7),
      player[0]->paidOut(SLOTS_BASE+7),
      player[0]->average(SLOTS_BASE+7));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+8)>0) {
    sprintf(buffer,"Tripple Play                %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+8),
      player[0]->paidOut(SLOTS_BASE+8),
      player[0]->average(SLOTS_BASE+8));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+9)>0) {
    sprintf(buffer,"5 Way                       %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+9),
      player[0]->paidOut(SLOTS_BASE+9),
      player[0]->average(SLOTS_BASE+9));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+10)>0) {
    sprintf(buffer,"Lo-Ball                     %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+10),
      player[0]->paidOut(SLOTS_BASE+10),
      player[0]->average(SLOTS_BASE+10));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+11)>0) {
    sprintf(buffer,"Stud Poker                  %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+11),
      player[0]->paidOut(SLOTS_BASE+11),
      player[0]->average(SLOTS_BASE+11));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+12)>0) {
    sprintf(buffer,"Gem Hunter                  %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+12),
      player[0]->paidOut(SLOTS_BASE+12),
      player[0]->average(SLOTS_BASE+12));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+13)>0) {
    sprintf(buffer,"Stars and Stripes           %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+13),
      player[0]->paidOut(SLOTS_BASE+13),
      player[0]->average(SLOTS_BASE+13));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+14)>0) {
    sprintf(buffer,"Planes, Trains, Autos       %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+14),
      player[0]->paidOut(SLOTS_BASE+14),
      player[0]->average(SLOTS_BASE+14));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+15)>0) {
    sprintf(buffer,"Sail Away                   %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+15),
      player[0]->paidOut(SLOTS_BASE+15),
      player[0]->average(SLOTS_BASE+15));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+16)>0) {
    sprintf(buffer,"In the Chips                %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+16),
      player[0]->paidOut(SLOTS_BASE+16),
      player[0]->average(SLOTS_BASE+16));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+17)>0) {
    sprintf(buffer,"Spin 'n Win                 %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+17),
      player[0]->paidOut(SLOTS_BASE+17),
      player[0]->average(SLOTS_BASE+17));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+18)>0) {
    sprintf(buffer,"In The Money                %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+18),
      player[0]->paidOut(SLOTS_BASE+18),
      player[0]->average(SLOTS_BASE+18));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+19)>0) {
    sprintf(buffer,"Lucky 7s                    %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+19),
      player[0]->paidOut(SLOTS_BASE+19),
      player[0]->average(SLOTS_BASE+19));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+20)>0) {
    sprintf(buffer,"Wild bill                   %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+20),
      player[0]->paidOut(SLOTS_BASE+20),
      player[0]->average(SLOTS_BASE+20));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+21)>0) {
    sprintf(buffer,"Big Win                     %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+21),
      player[0]->paidOut(SLOTS_BASE+21),
      player[0]->average(SLOTS_BASE+21));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+22)>0) {
    sprintf(buffer,"Wild Life                   %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+22),
      player[0]->paidOut(SLOTS_BASE+22),
      player[0]->average(SLOTS_BASE+22));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+23)>0) {
    sprintf(buffer,"High Life                   %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+23),
      player[0]->paidOut(SLOTS_BASE+23),
      player[0]->average(SLOTS_BASE+23));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+24)>0) {
    sprintf(buffer,"Lucky Stars                 %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+24),
      player[0]->paidOut(SLOTS_BASE+24),
      player[0]->average(SLOTS_BASE+24));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+25)>0) {
    sprintf(buffer,"7 7 7                       %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+25),
      player[0]->paidOut(SLOTS_BASE+25),
      player[0]->average(SLOTS_BASE+25));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+26)>0) {
    sprintf(buffer,"Red, White and Blue         %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+26),
      player[0]->paidOut(SLOTS_BASE+26),
      player[0]->average(SLOTS_BASE+26));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+27)>0) {
    sprintf(buffer,"5 Times Pay                 %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+27),
      player[0]->paidOut(SLOTS_BASE+27),
      player[0]->average(SLOTS_BASE+27));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(SLOTS_BASE+28)>0) {
    sprintf(buffer,"10 Times Pay                %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+28),
      player[0]->paidOut(SLOTS_BASE+28),
      player[0]->average(SLOTS_BASE+28));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }

  sprintf(buffer,"Total                       %12.2f  %12.2f  %5.2f%%\n",ti,to,to/ti*100);
  rcs_drawString(display,mainScreen,gc,20,pos,buffer);

  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  displayScreen();
  getEvent(display);
  while (event.type != EVENT_BUTTON_PRESS) event=getEvent(display);
#endif
#ifdef CONSOLE
  ClrScr();
  if (player[0]->paidIn(SLOTS_BASE+1)>0)
    printf("Bar                       %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+1),
      player[0]->paidOut(SLOTS_BASE+1),
      player[0]->average(SLOTS_BASE+1));
  if (player[0]->paidIn(SLOTS_BASE+2)>0)
    printf("Wild Fruits               %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+2),
      player[0]->paidOut(SLOTS_BASE+2),
      player[0]->average(SLOTS_BASE+2));
  if (player[0]->paidIn(SLOTS_BASE+3)>0)
    printf("Earthquake                %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+3),
      player[0]->paidOut(SLOTS_BASE+3),
      player[0]->average(SLOTS_BASE+3));
  if (player[0]->paidIn(SLOTS_BASE+4)>0)
    printf("Double Fortune            %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+4),
      player[0]->paidOut(SLOTS_BASE+4),
      player[0]->average(SLOTS_BASE+4));
  if (player[0]->paidIn(SLOTS_BASE+5)>0)
    printf("Super 7s                  %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+5),
      player[0]->paidOut(SLOTS_BASE+5),
      player[0]->average(SLOTS_BASE+5));
  if (player[0]->paidIn(SLOTS_BASE+6)>0)
    printf("Sidewinder                %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+6),
      player[0]->paidOut(SLOTS_BASE+6),
      player[0]->average(SLOTS_BASE+6));
  if (player[0]->paidIn(SLOTS_BASE+7)>0)
    printf("4 Wheeler                 %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+7),
      player[0]->paidOut(SLOTS_BASE+7),
      player[0]->average(SLOTS_BASE+7));
  if (player[0]->paidIn(SLOTS_BASE+8)>0)
    printf("Tripple Play              %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+8),
      player[0]->paidOut(SLOTS_BASE+8),
      player[0]->average(SLOTS_BASE+8));
  if (player[0]->paidIn(SLOTS_BASE+9)>0)
    printf("5-Way                     %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+9),
      player[0]->paidOut(SLOTS_BASE+9),
      player[0]->average(SLOTS_BASE+9));
  if (player[0]->paidIn(SLOTS_BASE+10)>0)
    printf("Lo-Ball                   %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+10),
      player[0]->paidOut(SLOTS_BASE+10),
      player[0]->average(SLOTS_BASE+10));
  if (player[0]->paidIn(SLOTS_BASE+11)>0)
    printf("Stud Poker                %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+11),
      player[0]->paidOut(SLOTS_BASE+11),
      player[0]->average(SLOTS_BASE+11));
  if (player[0]->paidIn(SLOTS_BASE+12)>0)
    printf("Gem Hunter                %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+12),
      player[0]->paidOut(SLOTS_BASE+12),
      player[0]->average(SLOTS_BASE+12));
  if (player[0]->paidIn(SLOTS_BASE+13)>0)
    printf("Stars and Stripes         %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+13),
      player[0]->paidOut(SLOTS_BASE+13),
      player[0]->average(SLOTS_BASE+13));
  if (player[0]->paidIn(SLOTS_BASE+14)>0)
    printf("Planes, Trains and Autos  %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+14),
      player[0]->paidOut(SLOTS_BASE+14),
      player[0]->average(SLOTS_BASE+14));
  if (player[0]->paidIn(SLOTS_BASE+15)>0)
    printf("Sail Away                 %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+15),
      player[0]->paidOut(SLOTS_BASE+15),
      player[0]->average(SLOTS_BASE+15));
  if (player[0]->paidIn(SLOTS_BASE+16)>0)
    printf("In The Chips              %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+16),
      player[0]->paidOut(SLOTS_BASE+16),
      player[0]->average(SLOTS_BASE+16));
  if (player[0]->paidIn(SLOTS_BASE+17)>0)
    printf("Spin n Win                %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+17),
      player[0]->paidOut(SLOTS_BASE+17),
      player[0]->average(SLOTS_BASE+17));
  if (player[0]->paidIn(SLOTS_BASE+18)>0)
    printf("In The Money              %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+18),
      player[0]->paidOut(SLOTS_BASE+18),
      player[0]->average(SLOTS_BASE+18));
  if (player[0]->paidIn(SLOTS_BASE+19)>0)
    printf("Lucky 7s                  %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+19),
      player[0]->paidOut(SLOTS_BASE+19),
      player[0]->average(SLOTS_BASE+19));
  if (player[0]->paidIn(SLOTS_BASE+20)>0)
    printf("Wild Bill                 %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+20),
      player[0]->paidOut(SLOTS_BASE+20),
      player[0]->average(SLOTS_BASE+20));
  if (player[0]->paidIn(SLOTS_BASE+21)>0)
    printf("Big Win                   %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(SLOTS_BASE+21),
      player[0]->paidOut(SLOTS_BASE+21),
      player[0]->average(SLOTS_BASE+21));
  printf("Total                     %12.2f   %12.2f   %5.2f%%\n",
    ti,to,to/ti*100);
  printf("Press <enter> to continue\n");
  fgets(buffer,10,stdin);
#endif
  }

void Slots(Player* p) {
  int  i;
  double ti,to;
  SlotMachine *slots;
  long betAmount;
#ifdef GRAPHIC
  rcs_GC gc;
  rcs_Event event;
  char      flag;
#endif
  i=1;
  betAmount=1;
  while (i != 0) {
#ifdef GRAPHIC
    table=rcs_xpmToPixmap(display,mainWindow,slotmenu_xpm);
    gc=rcs_openGC(display,mainScreen);
    rcs_copyArea(display,table,mainScreen,gc,0,0,800,600,0,0);
    rcs_closeGC(display,gc);
    showBetAmount(betAmount);
    displayScreen();
    flag=' ';
    while (flag==' ') {
      event=getEvent(display);
      if (event.type==EVENT_BUTTON_PRESS && event.d1==1) {
        if (event.d2>=490 && event.d2<=516 &&
            event.d3>=566 && event.d3<=598) {
          betAmount=1;
          showBetAmount(betAmount);
          }
        if (event.d2>=522 && event.d2<=546 &&
            event.d3>=566 && event.d3<=598) {
          betAmount=5;
          showBetAmount(betAmount);
          }
        if (event.d2>=553 && event.d2<=578 &&
            event.d3>=566 && event.d3<=598) {
          betAmount=10;
          showBetAmount(betAmount);
          }
        if (event.d2>=584 && event.d2<=609 &&
            event.d3>=566 && event.d3<=598) {
          betAmount=25;
          showBetAmount(betAmount);
          }
        if (event.d2>=615 && event.d2<=640 &&
            event.d3>=566 && event.d3<=598) {
          betAmount=50;
          showBetAmount(betAmount);
          }
        if (event.d2>=645 && event.d2<=671 &&
            event.d3>=566 && event.d3<=598) {
          betAmount=100;
          showBetAmount(betAmount);
          }
        if (event.d2>=676 && event.d2<=701 &&
            event.d3>=566 && event.d3<=598) {
          betAmount=500;
          showBetAmount(betAmount);
          }
        if (event.d2>=708 && event.d2<=733 &&
            event.d3>=566 && event.d3<=598) {
          betAmount=1000;
          showBetAmount(betAmount);
          }
        if (event.d2>=16 && event.d2<=108 &&
            event.d3>=16 && event.d3<=127) {
          i=1;
          flag='X';
          }
        if (event.d2>=120 && event.d2<=213 &&
            event.d3>=16 && event.d3<=127) {
          i=2;
          flag='X';
          }
        if (event.d2>=226 && event.d2<=319 &&
            event.d3>=16 && event.d3<=127) {
          i=3;
          flag='X';
          }
        if (event.d2>=330 && event.d2<=424 &&
            event.d3>=16 && event.d3<=127) {
          i=4;
          flag='X';
          }
        if (event.d2>=435 && event.d2<=530 &&
            event.d3>=16 && event.d3<=127) {
          i=5;
          flag='X';
          }
        if (event.d2>=539 && event.d2<=633 &&
            event.d3>=16 && event.d3<=127) {
          i=6;
          flag='X';
          }
        if (event.d2>=644 && event.d2<=753 &&
            event.d3>=16 && event.d3<=127) {
          i=7;
          flag='X';
          }
        if (event.d2>=16 && event.d2<=110 &&
            event.d3>=147 && event.d3<=258) {
          i=8;
          flag='X';
          }
        if (event.d2>=119 && event.d2<=213 &&
            event.d3>=147 && event.d3<=258) {
          i=9;
          flag='X';
          }
        if (event.d2>=224 && event.d2<=332 &&
            event.d3>=147 && event.d3<=258) {
          i=10;
          flag='X';
          }
        if (event.d2>=341 && event.d2<=465 &&
            event.d3>=147 && event.d3<=258) {
          i=11;
          flag='X';
          }
        if (event.d2>=475 && event.d2<=568 &&
            event.d3>=147 && event.d3<=258) {
          i=12;
          flag='X';
          }
        if (event.d2>=578 && event.d2<=672 &&
            event.d3>=147 && event.d3<=258) {
          i=13;
          flag='X';
          }
        if (event.d2>=683 && event.d2<=776 &&
            event.d3>=147 && event.d3<=258) {
          i=14;
          flag='X';
          }
        if (event.d2>=16 && event.d2<=388 &&
            event.d3>=277 && event.d3<=388) {
          i=15;
          flag='X';
          }
        if (event.d2>=135 && event.d2<=228 &&
            event.d3>=277 && event.d3<=388) {
          i=16;
          flag='X';
          }
        if (event.d2>=238 && event.d2<=331 &&
            event.d3>=277 && event.d3<=388) {
          i=17;
          flag='X';
          }
        if (event.d2>=340 && event.d2<=438 &&
            event.d3>=275 && event.d3<=389) {
          i=18;
          flag='X';
          }
        if (event.d2>=446 && event.d2<=539 &&
            event.d3>=275 && event.d3<=389) {
          i=19;
          flag='X';
          }
        if (event.d2>=551 && event.d2<=659 &&
            event.d3>=275 && event.d3<=389) {
          i=20;
          flag='X';
          }
        if (event.d2>=671 && event.d2<=767 &&
            event.d3>=275 && event.d3<=389) {
          i=21;
          flag='X';
          }
        if (event.d2>=15 && event.d2<=110 &&
            event.d3>=406 && event.d3<=521) {
          i=22;
          flag='X';
          }
        if (event.d2>=122 && event.d2<=215 &&
            event.d3>=406 && event.d3<=521) {
          i=23;
          flag='X';
          }
        if (event.d2>=226 && event.d2<=321 &&
            event.d3>=406 && event.d3<=521) {
          i=24;
          flag='X';
          }
        if (event.d2>=331 && event.d2<=429 &&
            event.d3>=406 && event.d3<=521) {
          i=25;
          flag='X';
          }
        if (event.d2>=435 && event.d2<=532 &&
            event.d3>=406 && event.d3<=521) {
          i=26;
          flag='X';
          }
        if (event.d2>=542 && event.d2<=638 &&
            event.d3>=406 && event.d3<=521) {
          i=27;
          flag='X';
          }
        if (event.d2>=649 && event.d2<=746 &&
            event.d3>=406 && event.d3<=521) {
          i=28;
          flag='X';
          }
        if (event.d2>=7 && event.d2<=91 &&
            event.d3>=567 && event.d3<=598) {
          i=0;
          flag='X';
          }
        if (event.d2>=130 && event.d2<=214 &&
            event.d3>=567 && event.d3<=598) {
          i=99;
          flag='X';
          }
        }
      }
    rcs_closePixmap(display,table);
#endif
#ifdef CONSOLE
    ClrScr();
    Output("1. Bar\n");
    Output("2. Wild Fruits\n");
    Output("3. Earthquake\n");
    Output("4. Double Fortune\n");
    Output("5. Super 7s\n");
    Output("6. Sidewinder\n");
    Output("7. 4 Wheeler\n");
    Output("8. Tripple Play\n");
    Output("9. 5-Way\n");
    Output("10. Lo-ball\n");
    Output("11. Stud Poker\n");
    Output("12. Gem Hunt\n");
    Output("13. Stars and Stripes\n");
    Output("14. Planes, Trains, and Automobiles\n");
    Output("15. Sail Away\n");
    Output("16. In The Chips\n");
    Output("17. Spin n Win\n");
    Output("18. In The Money\n");
    Output("19. Lucky 7s\n");
    Output("20. Wild Bill\n");
    Output("21. Big Win\n");
    Output("22. Wild Life\n");
    Output("23. High Life\n");
    Output("24. Lucky Stars\n");
    Output("25. 7 7 7\n");
    Output("26. Red, White and Blue\n");
    Output("27. 5 Times Pay\n");
    Output("28. 10 Times Pay\n");
    Output("\n99. Stats\n");
    Input(buffer);
    sscanf(buffer,"%d",&i);
#endif
    p->setSubGame(i);
    if (i == 99) slotStats();
    if (i==1) {
      p->setSubGame(SLOTS_BASE+1);
      if ((slots=new SlotMachine(1,p,3,betAmount)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("- - = - - # - - = - - - ",
                     "                        ",
                     "000000000000000000000000");
      slots->addReel("- - = - - # - - = - - - ",
                     "                        ",
                     "000000000000000000000000");
      slots->addReel("- - = - - # - - = - - - ",
                     "                        ",
                     "000000000000000000000000");
      slots->addPayout("###",500);
      slots->addPayout("===",150);
      slots->addPayout("---",9);
      slots->addPayout("///",3);
      slots->play();
      delete(slots);
      }
    if (i==2) {
      p->setSubGame(SLOTS_BASE+2);
      if ((slots=new SlotMachine(1,p,3,1)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("C C B P C * P C B C C O ",
                     "          *             ",
                     "000000000000000000000000");
      slots->addReel("C C O C P * C P B C P O ",
                     "          *             ",
                     "000000000000000000000000");
      slots->addReel("C C O C P * C P B C P O ",
                     "          *             ",
                     "000000000000000000000000");
      slots->addPayout("***",1000);
      slots->addPayout("BBB",50);
      slots->addPayout("OOO",30);
      slots->addPayout("PPP",25);
      slots->addPayout("CCC",10);
      slots->addPayout("?CC",5);
      slots->addPayout("??C",1);
      slots->play();
      delete(slots);
      }
    if (i==3) {
      p->setSubGame(SLOTS_BASE+3);
      if ((slots=new SlotMachine(1,p,3,1)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("- - = - - V - - = - - - ",
                     "         v*             ",
                     "000000000000000000000000");
      slots->addReel("- - = - - ^ - - = - - - ",
                     "          *^            ",
                     "000000000000000000000000");
      slots->addReel("- - = - - V - - = - - - ",
                     "         v*             ",
                     "000000000000000000000000");
      slots->addPayout("***",175);
      slots->addPayout("===",30);
      slots->addPayout("---",6);
      slots->addPayout("///",1);
      slots->play();
      delete(slots);
      }
    if (i==4) {
      p->setSubGame(SLOTS_BASE+4);
      if ((slots=new SlotMachine(1,p,3,1)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("C C B P C X P C B C C O ",
                     "          2             ",
                     "000000000050000000000000");
      slots->addReel("C C O C P X C P B C P O ",
                     "          2             ",
                     "000000000050000000000000");
      slots->addReel("C C O C P X C P B C P O ",
                     "          2             ",
                     "000000000050000000000000");
      slots->addPayout("XXX",6000);
      slots->addPayout("BBB",50);
      slots->addPayout("OOO",30);
      slots->addPayout("PPP",20);
      slots->addPayout("CCC",10);
      slots->addPayout("?CC",3);
      slots->addPayout("??C",2);
      slots->play();
      delete(slots);
      }
    if (i==5) {
      p->setSubGame(SLOTS_BASE+5);
      if ((slots=new SlotMachine(1,p,3,1)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("C C - $ C 7 - = C C = - ",
                     "                        ",
                     "000000000090000000000000");
      slots->addReel("C C - $ C 7 - = C C = - ",
                     "                        ",
                     "000000000090000000000000");
      slots->addReel("C C - $ C 7 - = C C = - ",
                     "                        ",
                     "000000000090000000000000");
      slots->addPayout("777",10000);
      slots->addPayout("?77",1000);
      slots->addPayout("??7",30);
      slots->addPayout("$$$",400);
      slots->addPayout("===",100);
      slots->addPayout("---",50);
      slots->addPayout("///",10);
      slots->addPayout("CCC",10);
      slots->addPayout("?CC",6);
      slots->addPayout("??C",1);
      slots->play();
      delete(slots);
      }
    if (i==6) {
      p->setSubGame(SLOTS_BASE+6);
      if ((slots=new SlotMachine(1,p,3,1)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("C $ B P C > P C B C C O ",
                     "          >             ",
                     "009000000000000000000000");
      slots->addReel("C > O C P $ C P B < P O ",
                     "  >               <     ",
                     "000000000090000000000000");
      slots->addReel("C $ O C P < C P B C P O ",
                     "          <             ",
                     "009000000000000000000000");
      slots->addPayout("$$$",1000);
      slots->addPayout("BBB",150);
      slots->addPayout("OOO",75);
      slots->addPayout("PPP",20);
      slots->addPayout("CCC",10);
      slots->addPayout("?CC",3);
      slots->addPayout("??C",1);
      slots->play();
      delete(slots);
      }
    if (i==7) {
      p->setSubGame(SLOTS_BASE+7);
      if ((slots=new SlotMachine(1,p,3,1)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("C C B P C * P C B C C O ",
                     "          *             ",
                     "000000000000000000000000");
      slots->addReel("C C O C P * C P B C P O ",
                     "          *             ",
                     "000000000000000000000000");
      slots->addReel("C C O C P * C P B C P O ",
                     "          *             ",
                     "000000000000000000000000");
      slots->addReel("C C O C P * C P B C P O ",
                     "          *             ",
                     "000000000000000000000000");
      slots->addPayout("****",10000);
      slots->addPayout("BBBB",1000);
      slots->addPayout("OOOO",300);
      slots->addPayout("PPPP",150);
      slots->addPayout("CCCC",25);
      slots->addPayout("?CCC",12);
      slots->addPayout("??CC",3);
      slots->addPayout("???C",1);
      slots->play();
      delete(slots);
      }
    if (i==8) {
      p->setSubGame(SLOTS_BASE+8);
      if ((slots=new SlotMachine(3,p,3,1)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("S D U S 7 U S D 7 S D $ ",
                     "                        ",
                     "000000000000000000000000");
      slots->addReel("S D U S 7 U S D U S D $ ",
                     "                        ",
                     "000000000000000000000000");
      slots->addReel("S D U S 7 U S D U S D $ ",
                     "                        ",
                     "000000000000000000000000");
      slots->addPayout("$$$",1100);
      slots->addPayout("777",500);
      slots->addPayout("UUU",200);
      slots->addPayout("DDD",100);
      slots->addPayout("SSS",25);
      slots->addPayout("?SS",3);
      slots->addPayout("??S",1);
      slots->play();
      delete(slots);
      }
    if (i==9) {
      p->setSubGame(SLOTS_BASE+9);
      if ((slots=new SlotMachine(5,p,5,1)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("S D U S 7 U S D 7 S D $ ",
                     "                        ",
                     "000000000000000000000000");
      slots->addReel("S D U S 7 U S D U S D $ ",
                     "                        ",
                     "000000000000000000000000");
      slots->addReel("S D U S 7 U S D U S D $ ",
                     "                        ",
                     "000000000000000000000000");
      slots->addPayout("$$$",1100);
      slots->addPayout("777",500);
      slots->addPayout("UUU",200);
      slots->addPayout("DDD",100);
      slots->addPayout("SSS",25);
      slots->addPayout("?SS",3);
      slots->addPayout("??S",1);
      slots->play();
      delete(slots);
      }
    if (i==10) {
      p->setSubGame(SLOTS_BASE+10);
      if ((slots=new SlotMachine(1,p,5,1)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("S - S - S b S - S - S - ",
                     "                        ",
                     "050505050095050505050505");
      slots->addReel("S - S - S a S l S - S - ",
                     "                        ",
                     "050505050095050505050505");
      slots->addReel("S - S - S l S o S - S - ",
                     "                        ",
                     "050505050095050505050505");
      slots->addReel("S - S - S l S - S - S - ",
                     "                        ",
                     "050505050095050505050505");
      slots->addPayout("ball",25000);
      slots->addPayout(" lo ",100);
      slots->addPayout("----",8);
      slots->addPayout("SSSS",4);
      slots->addPayout("?SSS",3);
      slots->addPayout("??SS",2);
      slots->addPayout("???S",1);
      slots->play();
      delete(slots);
      }
    if (i==11) {
      p->setSubGame(SLOTS_BASE+11);
      if ((slots=new SlotMachine(1,p,5,1)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("a k q j + 9 8 7 6 5 4 3 ",
                     "                        ",
                     "000000000000000000000000");
      slots->addReel("a k q j + 9 8 7 6 5 4 3 ",
                     "                        ",
                     "000000000000000000000000");
      slots->addReel("a k q j + 9 8 7 6 5 4 3 ",
                     "                        ",
                     "000000000000000000000000");
      slots->addReel("a k q j + 9 8 7 6 5 4 3 ",
                     "                        ",
                     "000000000000000000000000");
      slots->addReel("a k q j + 9 8 7 6 5 4 3 ",
                     "                        ",
                     "000000000000000000000000");
      slots->addPayout("aaaaa",25000);
      slots->addPayout("|FIVE",10000);
      slots->addPayout("|FOUR",1000);
      slots->addPayout("|FULL",500);
      slots->addPayout("|THRE",20);
      slots->addPayout("|TWOP",9);
      slots->addPayout("|PAIR",2);
      slots->play();
      delete(slots);
      }
    if (i==12) {
      p->setSubGame(SLOTS_BASE+12);
      if ((slots=new SlotMachine(1,p,3,1)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("A A E H A D H A E A A R ",
                     "                        ",
                     "000000000000000000000000");
      slots->addReel("A A R A H D A H E A H R ",
                     "                        ",
                     "000000000000000000000000");
      slots->addReel("A A R A H D A H E A H R ",
                     "                        ",
                     "000000000000000000000000");
      slots->addPayout("DDD",1000);
      slots->addPayout("EEE",500);
      slots->addPayout("RRR",100);
      slots->addPayout("HHH",50);
      slots->addPayout("AAA",25);
      slots->addPayout("?AA",3);
      slots->addPayout("??A",1);
      slots->addPayout("...",1);
      slots->play();
      delete(slots);
      }
    if (i==13) {
      p->setSubGame(SLOTS_BASE+13);
      if ((slots=new SlotMachine(1,p,3,1)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("- = K - # = I - # J = K - = # - = K - # J ",
                     "                                          ",
                     "000000000000000000000000000000000000000000");
      slots->addReel("- K = # - J = # - I = K - # = - = K - # I ",
                     "                                          ",
                     "000000000000000000000000000000000000000000");
      slots->addReel("- = J - = K - = # - = - J = - # - # - # I ",
                     "                                          ",
                     "000000000000000000000000000000000000000000");
      slots->addPayout("IJK",5000);
      slots->addPayout("III",1500);
      slots->addPayout("JJJ",1000);
      slots->addPayout("KKK",500);
      slots->addPayout("###",230);
      slots->addPayout("===",75);
      slots->addPayout("---",30);
      slots->addPayout("///",6);
      slots->play();
      delete(slots);
      }
    if (i==14) {
      p->setSubGame(SLOTS_BASE+14);
      if ((slots=new SlotMachine(1,p,3,1)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("W Z W T Q Z W Z T W Z W Q T W F ",
                     "                                ",
                     "00000000000000000000000000000000");
      slots->addReel("W Z W T Q Z W Z T W Z W Q T W F ",
                     "                                ",
                     "00000000000000000000000000000000");
      slots->addReel("W Z W T Q Z W Z T W Z W Q T W F ",
                     "                                ",
                     "00000000000000000000000000000000");
      slots->addPayout("FFF",2500);
      slots->addPayout("QQQ",500);
      slots->addPayout("TTT",250);
      slots->addPayout("ZZZ",60);
      slots->addPayout("WWW",25);
      slots->addPayout("?WW",3);
      slots->addPayout("??W",1);
      slots->play();
      delete(slots);
      }
    if (i==15) {
      p->setSubGame(SLOTS_BASE+15);
      if ((slots=new SlotMachine(1,p,3,1)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("s G M G N G M Y G a N G M G N Y G M G ",
                     "                                      ",
                     "50000000000000000000000000000000000000");
      slots->addReel("a G M G N G M Y G w N G M G N Y G M G ",
                     "                                      ",
                     "50000000000000000000000000000000000000");
      slots->addReel("i G M G N G M Y G a N G M G N Y G M G ",
                     "                                      ",
                     "50000000000000000000000000000000000000");
      slots->addReel("l G M G N G M Y G y N G M G N Y G M G ",
                     "                                      ",
                     "50000000000000000000000000000000000000");
      slots->addPayout("sail",25000);
      slots->addPayout("away",10000);
      slots->addPayout("YYYY",1000);
      slots->addPayout("NNNN",500);
      slots->addPayout("MMMM",250);
      slots->addPayout("GGGG",125);
      slots->addPayout("?GGG",50);
      slots->addPayout("??GG",9);
      slots->addPayout("???G",4);
      slots->play();
      delete(slots);
      }
    if (i==16) {
      p->setSubGame(SLOTS_BASE+16);
      if ((slots=new SlotMachine(5,p,5,1)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("! % @ & ! @ ( ! @ ! & % ! % ( @ ! % @ & ! ( % @ ! & ) ",
                     "                                                      ",
                     "000000000000000000000000000000000000000000000000000000");
      slots->addReel("! % @ ! & ! @ ( ! @ ! & % ! % ( @ ! % @ ! & ! ( % @ ! & ) ",
                     "                                                          ",
                     "0000000000000000000000000000000000000000000000000000000000");
      slots->addReel("! % ! @ ! & ! @ ! ( ! @ ! & ! % ! % ! ( @ ! % ! @ ! & ! ( ! % @ ! & ) ",
                     "                                                                      ",
                     "0000000000000000000000000000000000000000000000000000000000000000000000");
      slots->addPayout(")))",30000);
      slots->addPayout("(((",3000);
      slots->addPayout("&&&",300);
      slots->addPayout("%%%",75);
      slots->addPayout("@@@",15);
      slots->addPayout("!!!",3);
      slots->addPayout("?!!",2);
      slots->addPayout("??!",1);
      slots->play();
      delete(slots);
      }
    if (i==17) {
      p->setSubGame(SLOTS_BASE+17);
      if ((slots=new SlotMachine(1,p,3,1)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("0 0 3 0 0 0 4 0 0 5 0 3 0 0 4 0 0 0 5 0 0 4 0 0 3 0 0 7 0 4 0 0 ",
                     "                                                                ",
                     "0000900000009000009000900000900000009000009000009000009000900000");
      slots->addReel("0 0 2 0 0 5 0 2 0 7 0 5 0 0 2 0 0 7 0 5 0 2 0 0 5 0 2 0 0 2 0 0 ",
                     "                                                                ",
                     "0000800000900080009000900000800000900090008000009000800000800000");
      slots->addReel("0 5 0 0 5 0 0 5 0 0 5 0 0 5 0 0 5 0 0 0 5 0 0 0 5 0 0 5 0 0 ",
                     "                                                            ",
                     "000000000000000000000000000000000000000000000000000000000000");
      slots->addPayout("|##",500);
      slots->play();
      delete(slots);
      }
    if (i==18) {
      p->setSubGame(SLOTS_BASE+18);
      if ((slots=new SlotMachine(1,p,3,1)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("] $ ] % ] & ] % ] % ] & ~ ] % ] & ] % ] $ ] % ",
                     "                                              ",
                     "0050000000000000000000009000000000000000500000");
      slots->addReel("] $ ] % ] & ] % ] ] ] & ~ ] % ] & ] % ] $ ] % ",
                     "                                              ",
                     "0050000000000000000000009000000000000000500000");
      slots->addReel("] $ ] % ] & ] % ] % ] & ~ ] % ] & ] % ] $ ] % ",
                     "                                              ",
                     "0050000000000000000000009000000000000000500000");
      slots->addPayout("~~~",125000);
      slots->addPayout("?~~",15000);
      slots->addPayout("??~",100);
      slots->addPayout("$$$",5000);
      slots->addPayout("&&&",300);
      slots->addPayout("%%%",75);
      slots->addPayout("]]]",3);
      slots->addPayout("?]]",2);
      slots->addPayout("??]",1);
      slots->play();
      delete(slots);
      }
    if (i==19) {
      p->setSubGame(SLOTS_BASE+19);
      if ((slots=new SlotMachine(1,p,3,1)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("$ I J $ J K $ J 7 $ I J K $ J $ K ",
                     "                                  ",
                     "0000000000000000000000000000000000");
      slots->addReel("$ I J $ J K $ J 7 $ I J K $ J $ K ",
                     "                                  ",
                     "0000000000000000000000000000000000");
      slots->addReel("$ I J $ J K $ J 7 $ I J K $ J $ K ",
                     "                                  ",
                     "0000000000000000000000000000000000");
      slots->addPayout("777",1000);
      slots->addPayout("III",200);
      slots->addPayout("KKK",100);
      slots->addPayout("JJJ",40);
      slots->addPayout("$$$",10);
      slots->addPayout("|2$",2);
      slots->addPayout("|1$",1);
      slots->play();
      delete(slots);
      }
    if (i==20) {
      p->setSubGame(SLOTS_BASE+20);
      if ((slots=new SlotMachine(1,p,3,1)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("$*-*]*=*D*]*-*U*]*=*-*]*D*$*]*-*=*U*-*]*D*=*U*]*D*-*=*",
                     " * * * * * * * * * * * * * * * * * * * * * * * * * * *",
                     "090909090909090909090909090909090909090909090909090909");
      slots->addReel("$*-*]*=*D*]*-*U*]*=*-*]*D*$*]*-*=*U*-*]*D*=*U*]*D*-*=*",
                     " * * * * * * * * * * * * * * * * * * * * * * * * * * *",
                     "090909090909090909090909090909090909090909090909090909");
      slots->addReel("$*-*]*=*D*]*-*U*]*=*-*]*D*$*]*-*=*U*-*]*D*=*U*]*D*-*=*",
                     " * * * * * * * * * * * * * * * * * * * * * * * * * * *",
                     "090909090909090909090909090909090909090909090909090909");
      slots->addReel("$*-*]*=*D*]*-*U*]*=*-*]*D*$*]*-*=*U*-*]*D*=*U*]*D*-*=*",
                     " * * * * * * * * * * * * * * * * * * * * * * * * * * *",
                     "090909090909090909090909090909090909090909090909090909");
      slots->addPayout("****",10000);
      slots->addPayout("$$$$",1000);
      slots->addPayout("UUUU",500);
      slots->addPayout("DDDD",250);
      slots->addPayout("====",125);
      slots->addPayout("----",30);
      slots->addPayout("]]]]",20);
      slots->addPayout("|1]",1);
      slots->play();
      delete(slots);
      }
    if (i==21) {
      p->setSubGame(SLOTS_BASE+21);
      if ((slots=new SlotMachine(3,p,3,1)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("D ] U D 7 U D $ ] 7 D ] w $ ",
                     "                            ",
                     "0000000000000000000000000000");
      slots->addReel("D ] U D 7 U D $ ] U D ] i $ ",
                     "                            ",
                     "0000000000000000000000000000");
      slots->addReel("D ] U D 7 U D $ ] U D ] n $ ",
                     "                            ",
                     "0000000000000000000000000000");
      slots->addPayout("win",1500);
      slots->addPayout("777",500);
      slots->addPayout("$$$",250);
      slots->addPayout("UUU",125);
      slots->addPayout("]]]",25);
      slots->addPayout("DDD",5);
      slots->addPayout("|2D",2);
      slots->addPayout("|1D",1);
      slots->play();
      delete(slots);
      }
    if (i==22) {
      p->setSubGame(SLOTS_BASE+22);
      if ((slots=new SlotMachine(1,p,3,betAmount)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("> $ U ^ D U * U D V U U ",
                     ">     *^    *    v*     ",
                     "000000000000000000000000");
      slots->addReel("> $ U ^ D U * U D V < U ",
                     ">     *^    *    v* <   ",
                     "000000000000000000000000");
      slots->addReel("< $ U ^ D U * U D V U U ",
                     "<     *^    *    v*     ",
                     "000000000000000000000000");
      slots->addPayout("***",20);
      slots->addPayout("$$$",9);
      slots->addPayout("DDD",6);
      slots->addPayout("UUU",1);
      slots->play();
      delete(slots);
      }
    if (i==23) {
      p->setSubGame(SLOTS_BASE+23);
      if ((slots=new SlotMachine(1,p,3,betAmount)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("D N F D N Q D N D F N D ",
                     "                        ",
                     "000000000000000000000000");
      slots->addReel("D N F > N Q D < D F N D ",
                     "      >       <         ",
                     "000000000000000000000000");
      slots->addReel("D N F D N Q D N D F D D ",
                     "                        ",
                     "000000000000000000000000");
      slots->addPayout("QQQ",250);
      slots->addPayout("FFF",50);
      slots->addPayout("NNN",25);
      slots->addPayout("DDD",6);
      slots->addPayout("?DD",2);
      slots->addPayout("??D",1);
      slots->play();
      delete(slots);
      }
    if (i==24) {
      p->setSubGame(SLOTS_BASE+24);
      if ((slots=new SlotMachine(5,p,5,1)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("S K J S K I S K S J K S ",
                     "                        ",
                     "000000000000000000000000");
      slots->addReel("S K S I K S J S I K S K ",
                     "                        ",
                     "000000000000000000000000");
      slots->addReel("S J K S J S I S J S J S ",
                     "                        ",
                     "000000000000000000000000");
      slots->addPayout("IJK",1000);
      slots->addPayout("III",500);
      slots->addPayout("JJJ",250);
      slots->addPayout("KKK",100);
      slots->addPayout("SSS",25);
      slots->addPayout("?SS",2);
      slots->addPayout("??S",1);
      slots->play();
      delete(slots);
      }
    if (i==25) {
      p->setSubGame(SLOTS_BASE+25);
      if ((slots=new SlotMachine(1,p,3,betAmount)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("{ = : # - ; - # - : = - ",
                     "                        ",
                     "000000000000000000000000");
      slots->addReel("# = { # - ; = { - : = - ",
                     "                        ",
                     "000000000000000000000000");
      slots->addReel("- # { = - ; - { = : # - ",
                     "                        ",
                     "000000000000000000000000");
      slots->addPayout(";;;",1500);
      slots->addPayout(":::",500);
      slots->addPayout("{{{",250);
      slots->addPayout("###",250);
      slots->addPayout("===",125);
      slots->addPayout("---",75);
      slots->addPayout("___",20);
      slots->addPayout("///",3);
      slots->play();
      delete(slots);
      }
    if (i==26) {
      p->setSubGame(SLOTS_BASE+26);
      if ((slots=new SlotMachine(1,p,3,betAmount)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("| C } - C { C | - | - C ",
                     "                        ",
                     "000000000000000000000000");
      slots->addReel("C - } C - { - | C } - C ",
                     "                        ",
                     "000000000000000000000000");
      slots->addReel("{ | C - | C - | C } - C ",
                     "                        ",
                     "000000000000000000000000");
      slots->addPayout("{{{",1000);
      slots->addPayout("}}}",500);
      slots->addPayout("|||",250);
      slots->addPayout("---",125);
      slots->addPayout("___",15);
      slots->addPayout("CCC",3);
      slots->addPayout("?CC",2);
      slots->addPayout("??C",1);
      slots->play();
      delete(slots);
      }
    if (i==27) {
      p->setSubGame(SLOTS_BASE+27);
      if ((slots=new SlotMachine(1,p,3,betAmount)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("C = C # C - [ - C = C - ",
                     "            5           ",
                     "000000000000900000000000");
      slots->addReel("C = C # C - [ - C = C - ",
                     "            5           ",
                     "000000000000900000000000");
      slots->addReel("C = C # C - [ - C = C - ",
                     "            5           ",
                     "000000000000900000000000");
      slots->addPayout("[[[",30000);
      slots->addPayout("###",1000);
      slots->addPayout("===",250);
      slots->addPayout("---",60);
      slots->addPayout("CCC",4);
      slots->addPayout("?CC",2);
      slots->addPayout("??C",1);
      slots->play();
      delete(slots);
      }
    if (i==28) {
      p->setSubGame(SLOTS_BASE+28);
      if ((slots=new SlotMachine(1,p,3,betAmount)) == NULL) {
        Output("Out of memory\n");
        exit(1);
        }
      slots->addReel("C = C # C - , - C = C - ",
                     "            1           ",
                     "000000000000900000000000");
      slots->addReel("C = C # C - , - C = C - ",
                     "            1           ",
                     "000000000000900000000000");
      slots->addReel("C = C # C - , - C = C - ",
                     "            1           ",
                     "000000000000900000000000");
      slots->addPayout(",,,",50000);
      slots->addPayout("###",500);
      slots->addPayout("===",125);
      slots->addPayout("---",25);
      slots->addPayout("CCC",3);
      slots->addPayout("?CC",2);
      slots->addPayout("??C",1);
      slots->play();
      delete(slots);
      }
    }
  ti=0; to=0;
  for (i=SLOTS_BASE;i<85;i++) {
    ti+=player[0]->paidIn(i);
    to+=player[0]->paidOut(i);
    }
  p->setPaidIn(GAME_SLOTS,ti);
  p->setPaidOut(GAME_SLOTS,to);
  }

