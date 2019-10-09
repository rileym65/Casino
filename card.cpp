#include <librcs.h>

#include "images/cardBackRedLg.xpm"
#include "images/cardLg.xpm"
#include "images/cardSymLg.xpm"

rcs_Pixmap sym;
rcs_Pixmap cardBack;
rcs_Pixmap cardFront;

void cardInit(rcs_Display* display,rcs_Window win) {
  sym=rcs_xpmToPixmap(display,win,cardSymLg_xpm);
  cardBack=rcs_xpmToPixmap(display,win,cardBackRedLg_xpm);
  cardFront=rcs_xpmToPixmap(display,win,cardLg_xpm);
  }

void cardDone(rcs_Display* display) {
  rcs_closePixmap(display,sym);
  rcs_closePixmap(display,cardBack);
  rcs_closePixmap(display,cardFront);
  }

Card::Card(byte v,char s) {
  suit=s;
  val=v;
  side='B';
  x=0;
  y=0;
  }

int Card::getX() { return x; }
int Card::getY() { return y; }

char Card::getSuit() {
  return suit;
  }

byte Card::value() {
  if (val == 1) return 14;
  return val;
  }

byte Card::lValue() {
  if (val == 14) return 1;
  return val;
  }

char Card::getValue() {
  switch (val) {
    case  0:return '*';
    case  1:return 'A';
    case  2:return '2';
    case  3:return '3';
    case  4:return '4';
    case  5:return '5';
    case  6:return '6';
    case  7:return '7';
    case  8:return '8';
    case  9:return '9';
    case 10:return '0';
    case 11:return 'J';
    case 12:return 'Q';
    case 13:return 'K';
    case 14:return 'A';
    }
  return ' ';
  }

void Card::setSide(char s) { side=s; }

char Card::getSide() { return side; }

void Card::setPosition(int px,int py) {
  x=px;
  y=py;
  }

void Card::paint(rcs_Display* display,rcs_Window win,rcs_GC gc) {
  int sx,sy;
  int clr;
  if (side=='B') 
    rcs_copyArea(display,cardBack,win,gc,0,0,64,96,x,y);
  else
    rcs_copyArea(display,cardFront,win,gc,0,0,64,96,x,y);
  if (side != 'B') {
    if (suit=='H' || suit=='D') clr=75; else clr=0;
    switch (suit) {
      case 'H':sy=72; sx=142;
               break;
      case 'D':sy=72; sx=132;
               break;
      case 'C':sy=72; sx=66;
               break;
      case 'S':sy=72; sx=56;
               break;
      }
    if (val != 0) {
      rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+5,y+25);
      rcs_copyArea(display,sym,win,gc,sx,sy+18,10,18,x+50,y+55);
      }
    switch (val) {
      case  0:rcs_copyArea(display,sym,win,gc,clr+26,18,9,17,x+5,y+5);
              rcs_copyArea(display,sym,win,gc,clr+26,36,9,17,x+50,y+75);
              rcs_copyArea(display,sym,win,gc,clr+26,18,10,18,x+17,y+25);
              rcs_copyArea(display,sym,win,gc,clr+26,18,10,18,x+17,y+55);
              rcs_copyArea(display,sym,win,gc,clr+26,18,10,18,x+37,y+25);
              rcs_copyArea(display,sym,win,gc,clr+26,18,10,18,x+37,y+55);
              break;
      case 1:
      case 14:rcs_copyArea(display,sym,win,gc,clr+56,18,9,17,x+5,y+5);
              rcs_copyArea(display,sym,win,gc,clr+56,36,9,17,x+50,y+75);
              switch (suit) {
                case 'H':rcs_copyArea(display,sym,win,gc,90,72,14,24,x+25,y+37);
                         break;
                case 'D':rcs_copyArea(display,sym,win,gc,76,72,14,24,x+25,y+37);
                         break;
                case 'C':rcs_copyArea(display,sym,win,gc,14,72,14,24,x+25,y+37);
                         break;
                case 'S':rcs_copyArea(display,sym,win,gc,0,72,14,24,x+25,y+37);
                         break;
                }
              break;
      case  2:rcs_copyArea(display,sym,win,gc,clr+4, 0,9,17,x+5,y+5);
              rcs_copyArea(display,sym,win,gc,clr+4,54,9,17,x+50,y+75);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+27,y+25);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+27,y+55);
              break;
      case  3:rcs_copyArea(display,sym,win,gc,clr+14, 0,9,17,x+5,y+5);
              rcs_copyArea(display,sym,win,gc,clr+14,54,9,17,x+50,y+75);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+27,y+15);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+27,y+40);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+27,y+65);
              break;
      case  4:rcs_copyArea(display,sym,win,gc,clr+24, 0,9,17,x+5,y+5);
              rcs_copyArea(display,sym,win,gc,clr+24,54,9,17,x+50,y+75);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+17,y+25);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+17,y+55);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+37,y+25);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+37,y+55);
              break;
      case  5:rcs_copyArea(display,sym,win,gc,clr+34, 0,9,17,x+5,y+5);
              rcs_copyArea(display,sym,win,gc,clr+34,54,9,17,x+50,y+75);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+17,y+15);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+17,y+65);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+37,y+15);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+37,y+65);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+27,y+40);
              break;
      case  6:rcs_copyArea(display,sym,win,gc,clr+44, 0,9,17,x+5,y+5);
              rcs_copyArea(display,sym,win,gc,clr+44,54,9,17,x+50,y+75);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+17,y+15);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+17,y+65);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+37,y+15);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+37,y+65);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+37,y+40);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+17,y+40);
              break;
      case  7:rcs_copyArea(display,sym,win,gc,clr+54, 0,9,17,x+5,y+5);
              rcs_copyArea(display,sym,win,gc,clr+54,54,9,17,x+50,y+75);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+17,y+15);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+17,y+65);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+37,y+15);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+37,y+65);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+37,y+40);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+17,y+40);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+27,y+27);
              break;
      case  8:rcs_copyArea(display,sym,win,gc,clr+64, 0,9,17,x+5,y+5);
              rcs_copyArea(display,sym,win,gc,clr+64,54,9,17,x+50,y+75);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+17,y+15);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+17,y+65);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+37,y+15);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+37,y+65);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+37,y+40);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+17,y+40);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+27,y+27);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+27,y+52);
              break;
      case  9:rcs_copyArea(display,sym,win,gc,clr+0,18,9,17,x+5,y+5);
              rcs_copyArea(display,sym,win,gc,clr+0,36,9,17,x+50,y+75);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+15,y+15);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+15,y+40);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+15,y+65);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+39,y+15);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+39,y+40);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+39,y+65);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+27,y+15);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+27,y+40);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+27,y+65);
              break;
      case 10:rcs_copyArea(display,sym,win,gc,clr+10,18,14,17,x+5,y+5);
              rcs_copyArea(display,sym,win,gc,clr+10,36,14,17,x+45,y+75);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+17,y+15);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+17,y+65);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+37,y+15);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+37,y+65);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+37,y+40);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+17,y+40);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+27,y+7);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+27,y+27);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+27,y+52);
              rcs_copyArea(display,sym,win,gc,sx,sy,10,18,x+27,y+72);
              break;
      case 11:rcs_copyArea(display,sym,win,gc,clr+26,18,9,17,x+5,y+5);
              rcs_copyArea(display,sym,win,gc,clr+26,36,9,17,x+50,y+75);
              break;
      case 12:rcs_copyArea(display,sym,win,gc,clr+36,18,9,17,x+5,y+5);
              rcs_copyArea(display,sym,win,gc,clr+36,36,9,17,x+50,y+75);
              break;
      case 13:rcs_copyArea(display,sym,win,gc,clr+46,18,9,17,x+5,y+5);
              rcs_copyArea(display,sym,win,gc,clr+46,36,9,17,x+50,y+75);
              break;
      
      }
    }
  }

