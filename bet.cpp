#include "librcs.h"
#include "header.h"
#include <math.h>

#include "images/chip1.xpm"
#include "images/chip10.xpm"
#include "images/chip100.xpm"
#include "images/chip1000.xpm"
#include "images/chip10000.xpm"
#include "images/chip5.xpm"
#include "images/chip50.xpm"
#include "images/chip500.xpm"
#include "images/chip5000.xpm"
#include "images/chip25.xpm"

Bet::Bet(long bet) {
  value=bet;
  won=0;
  hand=0;
  x=0;
  y=0;
  }

void Bet::clear() { 
  value=0;
  hand=0;
  x=0;
  y=0;
  }

void Bet::clearWonBet() {
  if (won != 0) clear();
  }

void Bet::clearNonWinner() {
  if (won == 0) clear();
  }

void Bet::place(long b) {
  value=b;
  won=0;
  }

int  Bet::getHand() { return hand; }
long Bet::getValue() { return value; }
int  Bet::getX() { return x; }
int  Bet::getY() { return y; }

void Bet::setPosition(int nx,int ny) {
  x=nx;
  y=ny;
  }

void Bet::putHand(int h) { hand=h; }

void Bet::display() {
  char buffer[20];
  GotoXY(x,y);
  sprintf(buffer,"%ld",value);
  Output((const char*)buffer);
  if (won>0) {
    GotoXY(x,y-1);
    sprintf(buffer,"%ld",won);
    Output((const char*)buffer);
    }
  }

void Bet::loseHandBet(int h) {
  if (h == hand) {
    value=0;
    won=0;
    }
  }

long Bet::winHandBet(int h,float mult) {
  if (h == hand) {
    won=long(floor(value*mult+.005));
    return value+won;
    }
   else return 0;
  }

void Bet::loseXYBet(int x1,int y1,int x2,int y2) {
  if (x>=x1 && x<=x2 && y>=y1 && y<=y2) {
    value=0;
    won=0;
    }
  }

long Bet::winXYBet(int x1,int y1,int x2,int y2,float mult) {
  if (x>=x1 && x<=x2 && y>=y1 && y<=y2) {
    won=long(value*mult);
    return value+won; 
    }
    else return 0;
  }

void Bet::paint(rcs_Display* display,rcs_Window win) {
  rcs_GC gc1;
  gc1=rcs_openGC(display,win);
  paintChips(display,win,gc1,x-13,y-13,value);
  paintChips(display,win,gc1,x-13,y-13-30,won);
  rcs_closeGC(display,gc1);
  }

void Bet::paintChips(rcs_Display* display,rcs_Window win,rcs_GC gc,
                     int cx,int cy,long amount) {
  long v;
  int chip1,chip5,chip10,chip25,chip50,chip100,chip500,chip1000,chip5000;
  int chip10000,x1,i;
  if (amount == 0) return;
  v=amount;
  chip10000=v/10000; v-=chip10000*10000;
  chip5000=v/5000; v-=chip5000*5000;
  chip1000=v/1000; v-=chip1000*1000;
  chip500=v/500; v-=chip500*500;
  chip100=v/100; v-=chip100*100;
  chip50=v/50; v-=chip50*50;
  chip25=v/25; v-=chip25*25;
  chip10=v/10; v-=chip10*10;
  chip5=v/5; v-=chip5*5;
  chip1=v;
  x1=cx;
  for (i=0;i<chip1;i++) {
    rcs_drawPixmap(display,win,gc,x1,cy,chip1_xpm);
    x1+=4;
    }
  for (i=0;i<chip5;i++) {
    rcs_drawPixmap(display,win,gc,x1,cy,chip5_xpm);
    x1+=4;
    }
  for (i=0;i<chip10;i++) {
    rcs_drawPixmap(display,win,gc,x1,cy,chip10_xpm);
    x1+=4;
    }
  for (i=0;i<chip25;i++) {
    rcs_drawPixmap(display,win,gc,x1,cy,chip25_xpm);
    x1+=4;
    }
  for (i=0;i<chip50;i++) {
    rcs_drawPixmap(display,win,gc,x1,cy,chip50_xpm);
    x1+=4;
    }
  for (i=0;i<chip100;i++) {
    rcs_drawPixmap(display,win,gc,x1,cy,chip100_xpm);
    x1+=4;
    }
  for (i=0;i<chip500;i++) {
    rcs_drawPixmap(display,win,gc,x1,cy,chip500_xpm);
    x1+=4;
    }
  for (i=0;i<chip1000;i++) {
    rcs_drawPixmap(display,win,gc,x1,cy,chip1000_xpm);
    x1+=4;
    }
  for (i=0;i<chip5000;i++) {
    rcs_drawPixmap(display,win,gc,x1,cy,chip5000_xpm);
    x1+=4;
    }
  for (i=0;i<chip10000;i++) {
    rcs_drawPixmap(display,win,gc,x1,cy,chip10000_xpm);
    x1+=4;
    }
  }

