#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "poker.h"
#include "aruba.h"
#include "bacc.h"
#include "bahama.h"
#include "bingo.h"
#include "bj.h"
#include "bonus6.h"
#include "boston5.h"
#include "card7.h"
#include "carib.h"
#include "chuck.h"
#include "craps.h"
#include "dstud.h"
#include "faceup.h"
#include "flop.h"
#include "holdem.h"
#include "keno.h"
#include "lir.h"
#include "p357.h"
#include "paigow.h"
#include "paigowtiles.h"
#include "pkrmach.h"
#include "reddog.h"
#include "royal.h"
#include "roul.h"
#include "sicbo.h"
#include "spanish.h"
#include "superfun.h"
#include "texas.h"
#include "three.h"
#include "videokeno.h"
#include "wheel.h"
#include "war.h"
#include "wave.h"
#include "wildholdem.h"

#ifdef GRAPHIC
#include "images/main.xpm"
#endif

void getSaveFileName(char* envp[],const char* filename,char* dest) {
  int i;
  int j;
  j = -1;
  for (i=0; envp[i] != NULL; i++)
    if (strncasecmp(envp[i],"home=",5) == 0) j = i;
  if (j < 0) {
    strcpy(dest, filename);
    return;
    }
  i=0;
  while (envp[j][i] != '=') i++;
  i++;
  while (envp[j][i] == ' ') i++;
  strcpy(dest, envp[j]+i);
  if (dest[strlen(dest)] != '/') strcat(dest,"/");
  strcat(dest,filename);
  }

void getPlayerName(char* envp[],const char* defaultName,char* dest) {
  int i;
  int j;
  j = -1;
  for (i=0; envp[i] != NULL; i++)
    if (strncasecmp(envp[i],"user=",5) == 0) j = i;
  if (j < 0) {
    strcpy(dest, defaultName);
    return;
    }
  i=0;
  while (envp[j][i] != '=') i++;
  i++;
  while (envp[j][i] == ' ') i++;
  strcpy(dest, envp[j]+i);
  }

void pokerStats() {
  double ti,to;
  int i;
  int pos;
  int space;
  char buffer[255];
  rcs_GC gc;
  rcs_Font font;
  rcs_Event event;
  ti=0; to=0;
  for (i=0;i<SLOTS_BASE;i++) {
    ti+=player[0]->paidIn(i);
    to+=player[0]->paidOut(i);
    }
  if (ti==0) ti=.0001;
  gc=rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"darkgreen");
  rcs_drawFilledBox(display,mainScreen,gc,0,0,800,600);
  rcs_namedForeground(display,gc,"yellow");
  font=rcs_openFont(display,STAT_FONT);
  rcs_setFont(display,gc,font);
  pos=20;
  space=18;
  if (player[0]->paidIn(GAME_VPOKER)>0) {
    sprintf(buffer,"Video Poker (jacks)         %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_VPOKER),
      player[0]->paidOut(GAME_VPOKER),
      player[0]->average(GAME_VPOKER));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_VPOKER2)>0) {
    sprintf(buffer,"Video Poker (Tens)          %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_VPOKER2),
      player[0]->paidOut(GAME_VPOKER2),
      player[0]->average(GAME_VPOKER2));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_VPOKER3)>0) {
    sprintf(buffer,"Video Poker (Deuces)        %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_VPOKER3),
      player[0]->paidOut(GAME_VPOKER3),
      player[0]->average(GAME_VPOKER3));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_VPOKER4)>0) {
    sprintf(buffer,"Video Poker (Jokers)        %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_VPOKER4),
      player[0]->paidOut(GAME_VPOKER4),
      player[0]->average(GAME_VPOKER4));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_VPOKERP)>0) {
    sprintf(buffer,"Video Poker (Progressive)   %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_VPOKERP),
      player[0]->paidOut(GAME_VPOKERP),
      player[0]->average(GAME_VPOKERP));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_VPOKERDJ)>0) {
    sprintf(buffer,"Video Poker (Dbl Joker)     %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_VPOKERDJ),
      player[0]->paidOut(GAME_VPOKERDJ),
      player[0]->average(GAME_VPOKERDJ));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_VPOKERJ2)>0) {
    sprintf(buffer,"Video Poker (2's, Jokers)   %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_VPOKERJ2),
      player[0]->paidOut(GAME_VPOKERJ2),
      player[0]->average(GAME_VPOKERJ2));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_VPOKER8)>0) {
    sprintf(buffer,"Video Poker (8's and A's)   %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_VPOKER8),
      player[0]->paidOut(GAME_VPOKER8),
      player[0]->average(GAME_VPOKER8));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_VPOKERB)>0) {
    sprintf(buffer,"Bonus Poker                 %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_VPOKERB),
      player[0]->paidOut(GAME_VPOKERB),
      player[0]->average(GAME_VPOKERB));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_VPOKER2B)>0) {
    sprintf(buffer,"Double Bonus Poker          %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_VPOKER2B),
      player[0]->paidOut(GAME_VPOKER2B),
      player[0]->average(GAME_VPOKER2B));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_VPOKER3B)>0) {
    sprintf(buffer,"Triple Bonus Poker          %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_VPOKER3B),
      player[0]->paidOut(GAME_VPOKER3B),
      player[0]->average(GAME_VPOKER3B));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }

  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  displayScreen();
  getEvent(display);
  while (event.type != EVENT_BUTTON_PRESS) event=getEvent(display);
  }

void statistics() {
  double pi,po;
  double si,so;
  double ti,to;
  int i;
  int pos;
  int space;
  char buffer[255];
#ifdef GRAPHIC
  rcs_GC gc;
  rcs_Font font;
  rcs_Event event;
#endif
  si = 0;
  so = 0;
  for (i=SLOTS_BASE;i<MAX_GAMES;i++) {
    si+=player[0]->paidIn(i);
    so+=player[0]->paidOut(i);
    }
  ti=si; to=so;
  for (i=0;i<SLOTS_BASE;i++) {
    ti+=player[0]->paidIn(i);
    to+=player[0]->paidOut(i);
    }
  if (ti==0) ti=.0001;
  pi = player[0]->paidIn(GAME_VPOKER) + player[0]->paidIn(GAME_VPOKER2) +
       player[0]->paidIn(GAME_VPOKER3) + player[0]->paidIn(GAME_VPOKER4) +
       player[0]->paidIn(GAME_VPOKERP) + player[0]->paidIn(GAME_VPOKERDJ) +
       player[0]->paidIn(GAME_VPOKERJ2) + player[0]->paidIn(GAME_VPOKER8) +
       player[0]->paidIn(GAME_VPOKERB) + player[0]->paidIn(GAME_VPOKER2B) +
       player[0]->paidIn(GAME_VPOKER3B);
  po = player[0]->paidOut(GAME_VPOKER) + player[0]->paidOut(GAME_VPOKER2) +
       player[0]->paidOut(GAME_VPOKER3) + player[0]->paidOut(GAME_VPOKER4) +
       player[0]->paidOut(GAME_VPOKERP) + player[0]->paidOut(GAME_VPOKERDJ) +
       player[0]->paidOut(GAME_VPOKERJ2) + player[0]->paidOut(GAME_VPOKER8) +
       player[0]->paidOut(GAME_VPOKERB) + player[0]->paidOut(GAME_VPOKER2B) +
       player[0]->paidOut(GAME_VPOKER3B);
#ifdef GRAPHIC
  gc=rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"darkgreen");
  rcs_drawFilledBox(display,mainScreen,gc,0,0,800,600);
  rcs_namedForeground(display,gc,"yellow");
  font=rcs_openFont(display,STAT_FONT);
  rcs_setFont(display,gc,font);
  pos=20;
  space=15;
  if (player[0]->paidIn(GAME_BJ)>0) {
    sprintf(buffer,"Blackjack                   %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_BJ),
      player[0]->paidOut(GAME_BJ),
      player[0]->average(GAME_BJ));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_FACEUP)>0) {
    sprintf(buffer,"  Faceup 21                 %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_FACEUP),
      player[0]->paidOut(GAME_FACEUP),
      player[0]->average(GAME_FACEUP));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_SPANISH)>0) {
    sprintf(buffer,"  Spanish 21                %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_SPANISH),
      player[0]->paidOut(GAME_SPANISH),
      player[0]->average(GAME_SPANISH));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_ROYAL)>0) {
    sprintf(buffer,"  Royal Match 21            %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_ROYAL),
      player[0]->paidOut(GAME_ROYAL),
      player[0]->average(GAME_ROYAL));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_SUPERFUN)>0) {
    sprintf(buffer,"  Super Fun 21              %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_SUPERFUN),
      player[0]->paidOut(GAME_SUPERFUN),
      player[0]->average(GAME_SUPERFUN));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_BACC)>0) {
    sprintf(buffer,"Baccarat                    %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_BACC),
      player[0]->paidOut(GAME_BACC),
      player[0]->average(GAME_BACC));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_LIR)>0) {
    sprintf(buffer,"Let it Ride                 %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_LIR),
      player[0]->paidOut(GAME_LIR),
      player[0]->average(GAME_LIR));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_WILD)>0) {
    sprintf(buffer,"Wild Hold'em Fold'em        %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_WILD),
      player[0]->paidOut(GAME_WILD),
      player[0]->average(GAME_WILD));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_CRAPS)>0) {
    sprintf(buffer,"Craps                       %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_CRAPS),
      player[0]->paidOut(GAME_CRAPS),
      player[0]->average(GAME_CRAPS));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_ROUL)>0) {
    sprintf(buffer,"Roulette                    %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_ROUL),
      player[0]->paidOut(GAME_ROUL),
      player[0]->average(GAME_ROUL));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_KENO)>0) {
    sprintf(buffer,"Keno                        %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_KENO),
      player[0]->paidOut(GAME_KENO),
      player[0]->average(GAME_KENO));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_CARIB)>0) {
    sprintf(buffer,"Caribbean Stud              %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_CARIB),
      player[0]->paidOut(GAME_CARIB),
      player[0]->average(GAME_CARIB));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_BAHAMA)>0) {
    sprintf(buffer,"  Bahama Bonus              %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_BAHAMA),
      player[0]->paidOut(GAME_BAHAMA),
      player[0]->average(GAME_BAHAMA));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_ARUBA)>0) {
    sprintf(buffer,"  Wild Aruba Stud           %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_ARUBA),
      player[0]->paidOut(GAME_ARUBA),
      player[0]->average(GAME_ARUBA));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_REDDOG)>0) {
    sprintf(buffer,"Red Dog                     %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_REDDOG),
      player[0]->paidOut(GAME_REDDOG),
      player[0]->average(GAME_REDDOG));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_CHUCK)>0) {
    sprintf(buffer,"Chuck a Luck                %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_CHUCK),
      player[0]->paidOut(GAME_CHUCK),
      player[0]->average(GAME_CHUCK));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_WHEEL)>0) {
    sprintf(buffer,"Money Wheel                 %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_WHEEL),
      player[0]->paidOut(GAME_WHEEL),
      player[0]->average(GAME_WHEEL));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_DSTUD)>0) {
    sprintf(buffer,"Double Down Stud            %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_DSTUD),
      player[0]->paidOut(GAME_DSTUD),
      player[0]->average(GAME_DSTUD));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_BONUS6)>0) {
    sprintf(buffer,"Bonus 6                     %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_BONUS6),
      player[0]->paidOut(GAME_BONUS6),
      player[0]->average(GAME_BONUS6));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_THREE)>0) {
    sprintf(buffer,"Three Card Poker            %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_THREE),
      player[0]->paidOut(GAME_THREE),
      player[0]->average(GAME_THREE));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_PAIGOWT)>0) {
    sprintf(buffer,"Pai Gow                     %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_PAIGOWT),
      player[0]->paidOut(GAME_PAIGOWT),
      player[0]->average(GAME_PAIGOWT));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_PAIGOW)>0) {
    sprintf(buffer,"  Pai Gow Poker             %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_PAIGOW),
      player[0]->paidOut(GAME_PAIGOW),
      player[0]->average(GAME_PAIGOW));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_SICBO)>0) {
    sprintf(buffer,"Sic Bo                      %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_SICBO),
      player[0]->paidOut(GAME_SICBO),
      player[0]->average(GAME_SICBO));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_WAR)>0) {
    sprintf(buffer,"Casino War                  %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_WAR),
      player[0]->paidOut(GAME_WAR),
      player[0]->average(GAME_WAR));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_WAVE)>0) {
    sprintf(buffer,"Catch a Wave                %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_WAVE),
      player[0]->paidOut(GAME_WAVE),
      player[0]->average(GAME_WAVE));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_HOLDEM)>0) {
    sprintf(buffer,"Casino Hold'em              %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_HOLDEM),
      player[0]->paidOut(GAME_HOLDEM),
      player[0]->average(GAME_HOLDEM));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_BOSTON5)>0) {
    sprintf(buffer,"Boston 5                    %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_BOSTON5),
      player[0]->paidOut(GAME_BOSTON5),
      player[0]->average(GAME_BOSTON5));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_FLOP)>0) {
    sprintf(buffer,"Flop Poker                  %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_FLOP),
      player[0]->paidOut(GAME_FLOP),
      player[0]->average(GAME_FLOP));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_357)>0) {
    sprintf(buffer,"3-5-7 Poker                 %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_357),
      player[0]->paidOut(GAME_357),
      player[0]->average(GAME_357));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_TEXAS)>0) {
    sprintf(buffer,"Texas Hold'em Poker         %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_TEXAS),
      player[0]->paidOut(GAME_TEXAS),
      player[0]->average(GAME_TEXAS));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_CARD7)>0) {
    sprintf(buffer,"Seven Card Stud Poker       %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_CARD7),
      player[0]->paidOut(GAME_CARD7),
      player[0]->average(GAME_CARD7));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (player[0]->paidIn(GAME_BINGO)>0) {
    sprintf(buffer,"Bingo                       %12.2f  %12.2f  %5.2f%%\n",
      player[0]->paidIn(GAME_BINGO),
      player[0]->paidOut(GAME_BINGO),
      player[0]->average(GAME_BINGO));
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (si>0) {
    sprintf(buffer,"Slots (All)                 %12.2f  %12.2f  %5.2f%%\n",
      si, so, so/si*100);
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  if (pi>0) {
    sprintf(buffer,"Video Poker (All)           %12.2f  %12.2f  %5.2f%%\n",
      pi,
      po,
      po/pi);
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  pi = 0; po = 0;
  for (i=KENO_BASE; i<KENO_BASE+10; i++) {
    pi += player[0]->paidIn(i);
    po += player[0]->paidOut(i);
    }
  if (pi>0) {
    sprintf(buffer,"Video Keno (All)            %12.2f  %12.2f  %5.2f%%\n",
      pi,
      po,
      po/pi*100);
    rcs_drawString(display,mainScreen,gc,20,pos,buffer);
    pos+=space;
    }
  sprintf(buffer,"Total                       %12.2f  %12.2f  %5.2f%%\n",ti,to,to/ti*100);
  sprintf(buffer,"Total                       %12.2f  %12.2f  %5.2f%%\n",ti,to,to/ti*100);
  rcs_drawString(display,mainScreen,gc,20,pos,buffer);
  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  displayScreen();
  getEvent(display);
  while (event.type != EVENT_BUTTON_PRESS) event=getEvent(display);
#endif
#ifdef CONSOLE
  if (player[0]->paidIn(GAME_BJ)>0)
    printf("Blackjack                 %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(GAME_BJ),
      player[0]->paidOut(GAME_BJ),
      player[0]->average(GAME_BJ));
  if (player[0]->paidIn(GAME_FACEUP)>0)
    printf("Faceup 21                 %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(GAME_FACEUP),
      player[0]->paidOut(GAME_FACEUP),
      player[0]->average(GAME_FACEUP));
  if (player[0]->paidIn(GAME_BACC)>0)
    printf("Baccarat                  %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(GAME_BACC),
      player[0]->paidOut(GAME_BACC),
      player[0]->average(GAME_BACC));
  if (player[0]->paidIn(GAME_LIR)>0)
    printf("Let it ride               %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(GAME_LIR),
      player[0]->paidOut(GAME_LIR),
      player[0]->average(GAME_LIR));
  if (player[0]->paidIn(GAME_CRAPS)>0)
    printf("Craps                     %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(GAME_CRAPS),
      player[0]->paidOut(GAME_CRAPS),
      player[0]->average(GAME_CRAPS));
  if (player[0]->paidIn(GAME_ROUL)>0)
    printf("Roulette                  %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(GAME_ROUL),
      player[0]->paidOut(GAME_ROUL),
      player[0]->average(GAME_ROUL));
  if (player[0]->paidIn(GAME_VPOKER)>0)
    printf("Video Poker (Jacks)       %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(GAME_VPOKER),
      player[0]->paidOut(GAME_VPOKER),
      player[0]->average(GAME_VPOKER));
  if (player[0]->paidIn(GAME_VPOKER2)>0)
    printf("Video Poker (10s)         %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(GAME_VPOKER2),
      player[0]->paidOut(GAME_VPOKER2),
      player[0]->average(GAME_VPOKER2));
  if (player[0]->paidIn(GAME_VPOKER3)>0)
    printf("Video Poker (Deuces)      %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(GAME_VPOKER3),
      player[0]->paidOut(GAME_VPOKER3),
      player[0]->average(GAME_VPOKER3));
  if (player[0]->paidIn(GAME_VPOKER4)>0)
    printf("Video Poker (Jokers)      %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(GAME_VPOKER4),
      player[0]->paidOut(GAME_VPOKER4),
      player[0]->average(GAME_VPOKER4));
  if (player[0]->paidIn(GAME_VPOKERDJ)>0)
    printf("Video Poker (Dbl Jokers)  %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(GAME_VPOKERDJ),
      player[0]->paidOut(GAME_VPOKERDJ),
      player[0]->average(GAME_VPOKERDJ));
  if (player[0]->paidIn(GAME_VPOKERJ2)>0)
    printf("Video Poker 2's jokers    %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(GAME_VPOKERJ2),
      player[0]->paidOut(GAME_VPOKERJ2),
      player[0]->average(GAME_VPOKERJ2));
  if (player[0]->paidIn(GAME_VPOKERP)>0)
    printf("Video Poker (Progressive) %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(GAME_VPOKERP),
      player[0]->paidOut(GAME_VPOKERP),
      player[0]->average(GAME_VPOKERP));
  if (player[0]->paidIn(GAME_SLOTS)>0)
    printf("Slots                     %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(GAME_SLOTS),
      player[0]->paidOut(GAME_SLOTS),
      player[0]->average(GAME_SLOTS));
  if (player[0]->paidIn(GAME_KENO)>0)
    printf("Keno                      %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(GAME_KENO),
      player[0]->paidOut(GAME_KENO),
      player[0]->average(GAME_KENO));
  if (player[0]->paidIn(GAME_CARIB)>0)
    printf("Carribean Stud Poker      %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(GAME_CARIB),
      player[0]->paidOut(GAME_CARIB),
      player[0]->average(GAME_CARIB));
  if (player[0]->paidIn(GAME_REDDOG)>0)
    printf("Red Dog                   %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(GAME_REDDOG),
      player[0]->paidOut(GAME_REDDOG),
      player[0]->average(GAME_REDDOG));
  if (player[0]->paidIn(GAME_CHUCK)>0)
    printf("Chuck-a-Luck              %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(GAME_CHUCK),
      player[0]->paidOut(GAME_CHUCK),
      player[0]->average(GAME_CHUCK));
  if (player[0]->paidIn(GAME_WHEEL)>0)
    printf("Money Wheel               %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(GAME_WHEEL),
      player[0]->paidOut(GAME_WHEEL),
      player[0]->average(GAME_WHEEL));
  if (player[0]->paidIn(GAME_DSTUD)>0)
    printf("Double Down Stud          %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(GAME_DSTUD),
      player[0]->paidOut(GAME_DSTUD),
      player[0]->average(GAME_DSTUD));
  if (player[0]->paidIn(GAME_THREE)>0)
    printf("Three Card Poker          %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(GAME_THREE),
      player[0]->paidOut(GAME_THREE),
      player[0]->average(GAME_THREE));
  if (player[0]->paidIn(GAME_PAIGOW)>0)
    printf("Pai Gow Poker             %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(GAME_PAIGOW),
      player[0]->paidOut(GAME_PAIGOW),
      player[0]->average(GAME_PAIGOW));
  if (player[0]->paidIn(GAME_TEXAS)>0)
    printf("Texas Hold'em Poker       %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(GAME_TEXAS),
      player[0]->paidOut(GAME_TEXAS),
      player[0]->average(GAME_TEXAS));
  if (player[0]->paidIn(GAME_CARD7)>0)
    printf("Seven Card Stud Poker     %12.2f   %12.2f   %5.2f%%\n",
      player[0]->paidIn(GAME_CARD7),
      player[0]->paidOut(GAME_CARD7),
      player[0]->average(GAME_CARD7));
  printf("Total                     %12.2f   %12.2f   %5.2f%%\n",
    ti,to,to/ti*100);
  printf("Press <enter> to continue\n");
  fgets(buffer,10,stdin);
#endif
}

int mainMenu() {
  int game;
#ifdef GRAPHIC
  rcs_Event event;
  rcs_GC    gc;
  clearScreen();
  gc=rcs_openGC(display,mainScreen);
  table=rcs_xpmToPixmap(display,mainWindow,main_xpm);
  rcs_copyArea(display,table,mainScreen,gc,0,0,800,600,0,0);
  rcs_closeGC(display,gc);

  displayScreen();

  game=-1;
  while (game==-1) {
    event=getEvent(display);
    switch (event.type) {
      case EVENT_BUTTON_PRESS: if (event.d1==1) {
             if (event.d2>=0 && event.d2<=61 && event.d3>=0 && event.d3<=25) game=99;
             if (event.d2>=457 && event.d2<=531 && event.d3>=33 && event.d3<=153) game=0;
             if (event.d2>=339 && event.d2<=439 && event.d3>=202 && event.d3<=297) game=1;
             if (event.d2>=64 && event.d2<=157 && event.d3>=314 && event.d3<=409) game=2;
             if (event.d2>=286 && event.d2<=426 && event.d3>=60 && event.d3<=178) game=3;
             if (event.d2>=692 && event.d2<=793 && event.d3>=442 && event.d3<=537) game=4;
             if (event.d2>=81 && event.d2<=266 && event.d3>=186 && event.d3<=298) game=5;
             if (event.d2>=554 && event.d2<=741 && event.d3>=192 && event.d3<=287) game=6;
             if (event.d2>=562 && event.d2<=706 && event.d3>=58 && event.d3<=174) game=7;
             if (event.d2>=134 && event.d2<=231 && event.d3>=18 && event.d3<=89) game=8;
             if (event.d2>=553 && event.d2<=656 && event.d3>=438 && event.d3<=534) game=9;
             if (event.d2>=17 && event.d2<=57 && event.d3>=47 && event.d3<=224) game=10;
             if (event.d2>=56 && event.d2<=154 && event.d3>=440 && event.d3<=534) game=11;
             if (event.d2>=350 && event.d2<=445 && event.d3>=312 && event.d3<=410) game=12;
             if (event.d2>=558 && event.d2<=656 && event.d3>=312 && event.d3<=410) game=13;
             if (event.d2>=701 && event.d2<=795 && event.d3>=303 && event.d3<=410) game=14;
             if (event.d2>=208 && event.d2<=301 && event.d3>=312 && event.d3<=406) game=15;
             if (event.d2>=198 && event.d2<=296 && event.d3>=440 && event.d3<=536) game=16;
             if (event.d2>=339 && event.d2<=440 && event.d3>=440 && event.d3<=538) game=17;
             if (event.d2>=738 && event.d2<=777 && event.d3>=46 && event.d3<=225) game=-2;
             }
           break;
      }
    }
  rcs_closePixmap(display,table);
  return game;
#endif
#ifdef CONSOLE
  ClrScr();
  Output("\n 1. Blackjack           6. Roulette\n");
    Output(" 2. Baccarat            7. Slots\n");
    Output(" 3. Video Poker         8. Keno\n");
    Output(" 4. Let it Ride         9. Carribian Stud Poker\n");
    Output(" 5. Craps              10. Texas Hold'em Poker\n");
    Output("13. Chuck-a-Luck       11. Faceup 21\n");
    Output("12. Red Dog            14. Money Wheel\n");
    Output("15. Double Down Stud   16. Three Card Poker\n");
    Output("17. Pai Gow Poker\n");
    Output("\n");
    Output("99. Statistics          0. Quit\n");
    Input(buffer);
    sscanf(buffer,"%d",&game);
  return game;
#endif
  }

void _pokerMenu() {
  rcs_GC gc;
  rcs_Font font;
      gc=rcs_openGC(display,mainScreen);
      font=rcs_openFont(display,MENU_FONT);
      rcs_setFont(display,gc,font);
      rcs_namedForeground(display,gc,"darkgreen");
      rcs_drawFilledBox(display,mainScreen,gc,0,0,800,600);
      rcs_namedForeground(display,gc,"yellow");
      rcs_drawString(display,mainScreen,gc,320,65,"Video Poker");
      rcs_drawString(display,mainScreen,gc,320,125,"Jacks or better");
      rcs_drawString(display,mainScreen,gc,320,165,"Tens or better");
      rcs_drawString(display,mainScreen,gc,320,205,"Deuces Wild");
      rcs_drawString(display,mainScreen,gc,320,245,"Jokers Wild");
      rcs_drawString(display,mainScreen,gc,320,285,"Jacks or better proressive");
      rcs_drawString(display,mainScreen,gc,320,325,"Double Joker");
      rcs_drawString(display,mainScreen,gc,320,365,"Deuces and Jokers wild");
      rcs_drawString(display,mainScreen,gc,320,405,"Aces and Eights");
      rcs_drawString(display,mainScreen,gc,320,445,"Bonus Poker");
      rcs_drawString(display,mainScreen,gc,320,485,"Double Bonus Poker");
      rcs_drawString(display,mainScreen,gc,320,525,"Triple Bonus Poker");
      rcs_drawString(display,mainScreen,gc,320,565,"Statistics");
      rcs_closeFont(display,font);
      rcs_closeGC(display,gc);
      displayScreen();
  }

int main(int argc,char** argv,char** envp)
{
  int gamePlayers[10];
  int i,j,r;
  int game;
  char *outputDisplay;
  Bacc* bacc;
  Bj* bjGame;
  Bingo* bingo;
  Bonus6* bonus6;
  Boston5* boston5;
  Carib* carib;
  Chuck* chuck;
  Craps* craps;
  DStud* dStud;
  Faceup* faceupGame;
  Holdem* holdem;
  Keno* keno;
  Lir* lirGame;
  MoneyWheel* moneyWheel;
  Paigow* paigow;
  PaigowTiles* paigowt;
  PkrMach* pkrMach;
  Royal* royal;
  Roul* roul;
  Reddog* reddog;
  Sicbo*  sicbo;
  Spanish* spanishGame;
  SuperFun* superFun;
  Texas* texas;
  VideoKeno*  videoKeno;
  War*        war;
  Wave*       wave;
  WildHoldem* wild;
  Bahama*     bahama;
  Aruba*      aruba;
  Card7*      card7;
  Three*      three;
  Flop*       flop;
  P357*       p357;
#ifdef GRAPHIC
  rcs_GC gc;
  rcs_Font font;
  rcs_Event event;
  char flag;
#endif
  getSaveFileName(envp, ".casino.rc", saveFileName);
  outputDisplay = getenv("DISPLAY");
  if (outputDisplay == NULL) strcpy(outputDisplay,":0.0");
  ClrScr();
//  rcs_getFullName(buffer);
  setbuf(stdout,NULL);
  Randomize();
  for (i=0;i<20;i++) progressives[i]=0;
  progressives[PROG_CARIB]=10000;
  progressives[PROG_VPOKER1]=3500;
  progressives[PROG_VPOKER5]=17500;
  progressives[PROG_VPOKER10]=35000;
  progressives[PROG_VPOKER25]=87500;
  progressives[PROG_VPOKER100]=350000;
#ifdef CONSOLE
  GotoXY(29,10);
  Output("Welcome to Club R.C.S.\n");
  Output("Enter your name: ");
  Input(buffer);
#endif
  getPlayerName(envp, "Player", buffer);
//  strcpy(buffer,argv[1]);
  player[0]=new Player(buffer,'H');
  player[0]->load();
  for (i=1;i<MAX_PLAYERS;i++) {
    makeName(buffer);
    player[i]=new Player(buffer,'C');
    }

#ifdef GRAPHIC
  display=rcs_openDisplay(outputDisplay);
  rootWindow=rcs_rootWindow(display);
  mainWindow=rcs_createWindow(display,rootWindow,10,10,800,600);
  rcs_setWindowName(display,mainWindow,(char*)"Club RCS");
  rcs_showWindow(display,mainWindow);
  mainScreen=rcs_createPixmap(display,mainWindow,800,600);
  cardInit(display,mainWindow);
#endif

  game=1;
  while (game != 0) {
    game=mainMenu();
    if (game==-2) {
#ifdef GRAPHIC
      gc=rcs_openGC(display,mainScreen);
      font=rcs_openFont(display,MENU_FONT);
      rcs_setFont(display,gc,font);
      rcs_namedForeground(display,gc,"darkgreen");
      rcs_drawFilledBox(display,mainScreen,gc,0,0,800,600);
      rcs_namedForeground(display,gc,"yellow");
      rcs_drawString(display,mainScreen,gc,120,45,"Other Games");
      rcs_drawString(display,mainScreen,gc,120,105,"Sic Bo");
      rcs_drawString(display,mainScreen,gc,120,145,"Spanish 21");
      rcs_drawString(display,mainScreen,gc,120,185,"Casino War");
      rcs_drawString(display,mainScreen,gc,120,225,"Wild Hold'em Fold'em");
      rcs_drawString(display,mainScreen,gc,120,265,"Bahama Bonus");
      rcs_drawString(display,mainScreen,gc,120,305,"Royal Match 21");
      rcs_drawString(display,mainScreen,gc,120,345,"Wild Aruba Stud");
      rcs_drawString(display,mainScreen,gc,120,385,"Pai Gow");
      rcs_drawString(display,mainScreen,gc,120,425,"Catch a Wave");
      rcs_drawString(display,mainScreen,gc,120,465,"Super Fun 21");
      rcs_drawString(display,mainScreen,gc,120,505,"Bonus 6");
      rcs_drawString(display,mainScreen,gc,120,545,"Bingo");
      rcs_drawString(display,mainScreen,gc,120,585,"Video Keno");
      rcs_drawString(display,mainScreen,gc,420,105,"Casino Hold'em");
      rcs_drawString(display,mainScreen,gc,420,145,"Boston 5");
      rcs_drawString(display,mainScreen,gc,420,185,"Flop Poker");
      rcs_drawString(display,mainScreen,gc,420,225,"3-5-7 Poker");
      rcs_closeFont(display,font);
      rcs_closeGC(display,gc);
      displayScreen();
      flag=' ';
      while (flag==' ') {
        event=getEvent(display);
        if (event.type==EVENT_BUTTON_PRESS && event.d1==1) {
          if (event.d2>=100 && event.d2<=400 &&
              event.d3>=80 && event.d3<=110) {
            game=18; flag='X';
            }
          if (event.d2>=100 && event.d2<=200 &&
              event.d3>=120 && event.d3<=150) {
            game=19; flag='X';
            }
          if (event.d2>=100 && event.d2<=200 &&
              event.d3>=160 && event.d3<=190) {
            game=20; flag='X';
            }
          if (event.d2>=100 && event.d2<=200 &&
              event.d3>=200 && event.d3<=230) {
            game=21; flag='X';
            }
          if (event.d2>=100 && event.d2<=200 &&
              event.d3>=240 && event.d3<=270) {
            game=22; flag='X';
            }
          if (event.d2>=100 && event.d2<=200 &&
              event.d3>=280 && event.d3<=310) {
            game=23; flag='X';
            }
          if (event.d2>=100 && event.d2<=200 &&
              event.d3>=320 && event.d3<=350) {
            game=24; flag='X';
            }
          if (event.d2>=100 && event.d2<=200 &&
              event.d3>=360 && event.d3<=390) {
            game=25; flag='X';
            }
          if (event.d2>=100 && event.d2<=200 &&
              event.d3>=400 && event.d3<=430) {
            game=26; flag='X';
            }
          if (event.d2>=100 && event.d2<=200 &&
              event.d3>=440 && event.d3<=470) {
            game=27; flag='X';
            }
          if (event.d2>=100 && event.d2<=200 &&
              event.d3>=480 && event.d3<=510) {
            game=28; flag='X';
            }
          if (event.d2>=100 && event.d2<=200 &&
              event.d3>=520 && event.d3<=550) {
            game=29; flag='X';
            }
          if (event.d2>=100 && event.d2<=200 &&
              event.d3>=560 && event.d3<=590) {
            game=30; flag='X';
            }
          if (event.d2>=420 && event.d2<=520 &&
              event.d3>=80 && event.d3<=110) {
            game=31; flag='X';
            }
          if (event.d2>=400 && event.d2<=520 &&
              event.d3>=120 && event.d3<=150) {
            game=32; flag='X';
            }
          if (event.d2>=400 && event.d2<=520 &&
              event.d3>=160 && event.d3<=190) {
            game=33; flag='X';
            }
          if (event.d2>=400 && event.d2<=520 &&
              event.d3>=200 && event.d3<=230) {
            game=34; flag='X';
            }
          }
        }
#endif
    }
    if (game==1) {
#ifdef GRAPHIC
      gc=rcs_openGC(display,mainScreen);
      font=rcs_openFont(display,MENU_FONT);
      rcs_setFont(display,gc,font);
      rcs_namedForeground(display,gc,"darkgreen");
      rcs_drawFilledBox(display,mainScreen,gc,0,0,800,600);
      rcs_namedForeground(display,gc,"yellow");
      rcs_drawString(display,mainScreen,gc,320,65,"Blackjack");
      rcs_drawString(display,mainScreen,gc,320,125,"1 Deck");
      rcs_drawString(display,mainScreen,gc,320,165,"2 Deck");
      rcs_drawString(display,mainScreen,gc,320,205,"4 Deck");
      rcs_drawString(display,mainScreen,gc,320,245,"6 Deck");
      rcs_closeFont(display,font);
      rcs_closeGC(display,gc);
      displayScreen();
      flag=' ';
      while (flag==' ') {
        event=getEvent(display);
        if (event.type==EVENT_BUTTON_PRESS && event.d1==1) {
          if (event.d2>=300 && event.d2<=400 &&
              event.d3>=100 && event.d3<=130) {
            i=1; flag='X';
            }
          if (event.d2>=300 && event.d2<=400 &&
              event.d3>=140 && event.d3<=170) {
            i=2; flag='X';
            }
          if (event.d2>=300 && event.d2<=400 &&
              event.d3>=180 && event.d3<=210) {
            i=4; flag='X';
            }
          if (event.d2>=300 && event.d2<=400 &&
              event.d3>=220 && event.d3<=250) {
            i=6; flag='X';
            }
          }
        }
#endif
#ifdef CONSOLE
      ClrScr();
      Output("1. 1 Deck\n");
      Output("2. 2 Decks\n");
      Output("4. 4 Decks\n");
      Output("6. 6 Decks\n");
      Input(buffer);
      sscanf(buffer,"%d",&i);
#endif
      if (i!=1 && i!=2 && i!=4 && i!=6) i=1;
      bjGame=new Bj(i,0,2);
      player[0]->setGame(GAME_BJ);
      for (i=0;i<5;i++) gamePlayers[i]=-1;
      gamePlayers[Random(5)]=99;
      for (i=0;i<5;i++) if (gamePlayers[i]==-1) {
        r=Random(MAX_PLAYERS-2)+1;
        for (j=0;j<5;j++) if (gamePlayers[j]==r) r=-1;
        gamePlayers[i]=r;
        }
      for (i=0;i<5;i++)
        if (gamePlayers[i]==99) bjGame->addPlayer(player[0]);
        else if (gamePlayers[i]==-1) bjGame->addPlayer(NULL);
        else bjGame->addPlayer(player[gamePlayers[i]]);
        bjGame->play();
      delete(bjGame);
      }
    if (game==19) {
      spanishGame=new Spanish(8,0,2);
      player[0]->setGame(GAME_SPANISH);
      for (i=0;i<5;i++) gamePlayers[i]=-1;
      gamePlayers[Random(5)]=99;
      for (i=0;i<5;i++) if (gamePlayers[i]==-1) {
        r=Random(MAX_PLAYERS-2)+1;
        for (j=0;j<5;j++) if (gamePlayers[j]==r) r=-1;
        gamePlayers[i]=r;
        }
      for (i=0;i<5;i++)
        if (gamePlayers[i]==99) spanishGame->addPlayer(player[0]);
        else if (gamePlayers[i]==-1) spanishGame->addPlayer(NULL);
        else spanishGame->addPlayer(player[gamePlayers[i]]);
        spanishGame->play();
      delete(spanishGame);
      }
    if (game==11) {
#ifdef GRAPHIC
      gc=rcs_openGC(display,mainScreen);
      font=rcs_openFont(display,MENU_FONT);
      rcs_setFont(display,gc,font);
      rcs_namedForeground(display,gc,"darkgreen");
      rcs_drawFilledBox(display,mainScreen,gc,0,0,800,600);
      rcs_namedForeground(display,gc,"yellow");
      rcs_drawString(display,mainScreen,gc,320,65,"Faceup 21");
      rcs_drawString(display,mainScreen,gc,320,125,"1 Deck");
      rcs_drawString(display,mainScreen,gc,320,165,"2 Deck");
      rcs_drawString(display,mainScreen,gc,320,205,"4 Deck");
      rcs_drawString(display,mainScreen,gc,320,245,"6 Deck");
      rcs_closeFont(display,font);
      rcs_closeGC(display,gc);
      displayScreen();
      flag=' ';
      while (flag==' ') {
        event=getEvent(display);
        if (event.type==EVENT_BUTTON_PRESS && event.d1==1) {
          if (event.d2>=300 && event.d2<=400 &&
              event.d3>=100 && event.d3<=130) {
            i=1; flag='X';
            }
          if (event.d2>=300 && event.d2<=400 &&
              event.d3>=140 && event.d3<=170) {
            i=2; flag='X';
            }
          if (event.d2>=300 && event.d2<=400 &&
              event.d3>=180 && event.d3<=210) {
            i=4; flag='X';
            }
          if (event.d2>=300 && event.d2<=400 &&
              event.d3>=220 && event.d3<=250) {
            i=6; flag='X';
            }
          }
        }
#endif
#ifdef CONSOLE
      ClrScr();
      Output("1. 1 Deck\n");
      Output("2. 2 Decks\n");
      Output("4. 4 Decks\n");
      Output("6. 6 Decks\n");
      Input(buffer);
      sscanf(buffer,"%d",&i);
#endif
      if (i!=1 && i!=2 && i!=4 && i!=6) i=1;
      faceupGame=new Faceup(i,0,5);
      player[0]->setGame(GAME_FACEUP);
      for (i=0;i<5;i++) gamePlayers[i]=-1;
      gamePlayers[Random(5)]=99;
      for (i=0;i<5;i++) if (gamePlayers[i]==-1) {
        r=Random(MAX_PLAYERS-2)+1;
        for (j=0;j<5;j++) if (gamePlayers[j]==r) r=-1;
        gamePlayers[i]=r;
        }
      for (i=0;i<5;i++)
        if (gamePlayers[i]==99) faceupGame->addPlayer(player[0]);
        else if (gamePlayers[i]==-1) faceupGame->addPlayer(NULL);
        else faceupGame->addPlayer(player[gamePlayers[i]]);
        faceupGame->play();
      delete(faceupGame);
      }
    if (game==2) {
      bacc=new Bacc(6,0,5);
      player[0]->setGame(GAME_BACC);
      for (i=0;i<PLAYERS_BACC;i++) gamePlayers[i]=-1;
      gamePlayers[Random(PLAYERS_BACC)]=99;
      for (i=0;i<PLAYERS_BACC;i++) if (gamePlayers[i]==-1) {
        r=Random(MAX_PLAYERS-2)+1;
        for (j=0;j<PLAYERS_BACC;j++) if (gamePlayers[j]==r) r=-1;
        gamePlayers[i]=r;
        }
      for (i=0;i<PLAYERS_BACC;i++)
        if (gamePlayers[i]==99) bacc->addPlayer(player[0]);
        else if (gamePlayers[i]==-1) bacc->addPlayer(NULL);
        else bacc->addPlayer(player[gamePlayers[i]]);
      bacc->play();
      delete(bacc);
      }
    if (game==12) {
      reddog=new Reddog(6,0,5);
      player[0]->setGame(GAME_REDDOG);
      for (i=0;i<PLAYERS_REDDOG;i++) gamePlayers[i]=-1;
      gamePlayers[Random(PLAYERS_REDDOG)]=99;
      for (i=0;i<PLAYERS_REDDOG;i++) if (gamePlayers[i]==-1) {
        r=Random(MAX_PLAYERS-2)+1;
        for (j=0;j<PLAYERS_REDDOG;j++) if (gamePlayers[j]==r) r=-1;
        gamePlayers[i]=r;
        }
      for (i=0;i<PLAYERS_REDDOG;i++)
        if (gamePlayers[i]==99) reddog->addPlayer(player[0]);
        else if (gamePlayers[i]==-1) reddog->addPlayer(NULL);
        else reddog->addPlayer(player[gamePlayers[i]]);
      reddog->play();
      delete(reddog);
      }
    if (game==3) {
#ifdef GRAPHIC
      i=1;
      _pokerMenu();
/*
      gc=rcs_openGC(display,mainScreen);
      font=rcs_openFont(display,MENU_FONT);
      rcs_setFont(display,gc,font);
      rcs_namedForeground(display,gc,"darkgreen");
      rcs_drawFilledBox(display,mainScreen,gc,0,0,800,600);
      rcs_namedForeground(display,gc,"yellow");
      rcs_drawString(display,mainScreen,gc,320,65,"Video Poker");
      rcs_drawString(display,mainScreen,gc,320,125,"Jacks or better");
      rcs_drawString(display,mainScreen,gc,320,165,"Tens or better");
      rcs_drawString(display,mainScreen,gc,320,205,"Deuces Wild");
      rcs_drawString(display,mainScreen,gc,320,245,"Jokers Wild");
      rcs_drawString(display,mainScreen,gc,320,285,"Jacks or better proressive");
      rcs_drawString(display,mainScreen,gc,320,325,"Double Joker");
      rcs_drawString(display,mainScreen,gc,320,365,"Deuces and Jokers wild");
      rcs_drawString(display,mainScreen,gc,320,405,"Aces and Eights");
      rcs_drawString(display,mainScreen,gc,320,445,"Bonus Poker");
      rcs_drawString(display,mainScreen,gc,320,485,"Double Bonus Poker");
      rcs_drawString(display,mainScreen,gc,320,525,"Triple Bonus Poker");
      rcs_drawString(display,mainScreen,gc,320,565,"Statistics");
      rcs_closeFont(display,font);
      rcs_closeGC(display,gc);
      displayScreen();
*/
      flag=' ';
      while (flag==' ') {
        event=getEvent(display);
        if (event.type==EVENT_BUTTON_PRESS && event.d1==1) {
          if (event.d2>=300 && event.d2<=400 &&
              event.d3>=100 && event.d3<=130) {
            j=1; flag='X';
            }
          if (event.d2>=300 && event.d2<=400 &&
              event.d3>=140 && event.d3<=170) {
            j=2; flag='X';
            }
          if (event.d2>=300 && event.d2<=400 &&
              event.d3>=180 && event.d3<=210) {
            j=3; flag='X';
            }
          if (event.d2>=300 && event.d2<=400 &&
              event.d3>=220 && event.d3<=250) {
            j=4; flag='X';
            }
          if (event.d2>=300 && event.d2<=400 &&
              event.d3>=260 && event.d3<=290) {
            j=5; flag='X';
            }
          if (event.d2>=300 && event.d2<=400 &&
              event.d3>=300 && event.d3<=330) {
            j=6; flag='X';
            }
          if (event.d2>=300 && event.d2<=400 &&
              event.d3>=340 && event.d3<=370) {
            j=7; flag='X';
            }
          if (event.d2>=300 && event.d2<=400 &&
              event.d3>=380 && event.d3<=410) {
            j=8; flag='X';
            }
          if (event.d2>=300 && event.d2<=400 &&
              event.d3>=420 && event.d3<=450) {
            j=9; flag='X';
            }
          if (event.d2>=300 && event.d2<=400 &&
              event.d3>=460 && event.d3<=490) {
            j=10; flag='X';
            }
          if (event.d2>=300 && event.d2<=400 &&
              event.d3>=500 && event.d3<=530) {
            j=11; flag='X';
            }
          if (event.d2>=300 && event.d2<=400 &&
              event.d3>=540 && event.d3<=570) {
            pokerStats();
            _pokerMenu();
            }
          }
        }
#endif
#ifdef CONSOLE
      ClrScr();
      Output("1. $1 Machine\n");
      Output("2. $5 Machine\n");
      Output("3. $10 Machine\n");
      Output("4. $25 Machine\n");
      Output("5. $100 Machine\n");
      Input(buffer);
      sscanf(buffer,"%d",&i);
      if (i==1) i=1;
      else if (i==2) i=5;
      else if (i==3) i=10;
      else if (i==4) i=25;
      else if (i==5) i=100;
      else i=1;
      Output("1. Jacks or Better\n");
      Output("2. 10's or Better\n");
      Output("3. Deuces Wild\n");
      Output("4. Jokers Wild\n");
      Output("5. Jacks or Better Progressive\n");
      Output("6. Double Joker Poker\n");
      Output("7. Deuces and Jokers Wild\n");
      Input(buffer);
      sscanf(buffer,"%d",&j);
#endif
      if (j<1) j=1;
/*
      if (j>7) j=7;
*/
      if (j==1) {
        pkrMach=new PkrMach(1,0,i);
        player[0]->setGame(GAME_VPOKER);
        pkrMach->addPayout("Royal Flush",     0xe0000000l,0xefffffff,800);
        pkrMach->addPayout("Straight Flush"  ,0xa0000000l,0xafffffff,50);
        pkrMach->addPayout("4 of a Kind",     0x90000000l,0x9fffffff,25);
        pkrMach->addPayout("Full House",      0x70000000l,0x7fffffff,8);
        pkrMach->addPayout("Flush",           0x60000000l,0x6fffffff,5);
        pkrMach->addPayout("Straight",        0x50000000l,0x5fffffff,4);
        pkrMach->addPayout("3 of a Kind",     0x40000000l,0x4fffffff,3);
        pkrMach->addPayout("2 Pair",          0x20000000l,0x2fffffff,2);
        pkrMach->addPayout("Jacks or better", 0x1bb00000l,0x1fffffff,1);
//        pkrMach->addPayout(PK_PAIR | (11l<<24),1);
        pkrMach->addPlayer(player[0]);
        pkrMach->play();
        }
      if (j==2) {
        player[0]->setGame(GAME_VPOKER2);
        pkrMach=new PkrMach(1,0,i);
        pkrMach->addPayout("Royal Flush",     0xe0000000l,0xefffffff,800);
        pkrMach->addPayout("Straight Flush"  ,0xa0000000l,0xafffffff,50);
        pkrMach->addPayout("4 of a Kind",     0x90000000l,0x9fffffff,20);
        pkrMach->addPayout("Full House",      0x70000000l,0x7fffffff,6);
        pkrMach->addPayout("Flush",           0x60000000l,0x6fffffff,5);
        pkrMach->addPayout("Straight",        0x50000000l,0x5fffffff,4);
        pkrMach->addPayout("3 of a Kind",     0x40000000l,0x4fffffff,3);
        pkrMach->addPayout("2 Pair",          0x20000000l,0x2fffffff,2);
        pkrMach->addPayout("Tens or better",  0x1aa00000l,0x1fffffff,1);
//        pkrMach->addPayout(PK_PAIR | (10l<<24),1);
        pkrMach->addPlayer(player[0]);
        pkrMach->play();
        }
      if (j==3) {
        player[0]->setGame(GAME_VPOKER3);
        pkrMach=new PkrMach(1,0,i);
        pkrMach->addPayout("Natural Royal",   0xe0000000l,0xefffffff,800);
        pkrMach->addPayout("Four Deuces",     0xd0000000l,0xdfffffff,200);
        pkrMach->addPayout("Wild Royal",      0xc0000000l,0xcfffffff,20);
        pkrMach->addPayout("5 of a Kind",     0xb0000000l,0xbfffffff,12);
        pkrMach->addPayout("Straight Flush",  0xa0000000l,0xafffffff,10);
        pkrMach->addPayout("4 of a Kind",     0x90000000l,0x9fffffff,4);
        pkrMach->addPayout("Full House",      0x70000000l,0x7fffffff,4);
        pkrMach->addPayout("Flush",           0x60000000l,0x6fffffff,3);
        pkrMach->addPayout("Straight",        0x50000000l,0x5fffffff,2);
        pkrMach->addPayout("3 of a Kind",     0x40000000l,0x4fffffff,1);
        pkrMach->addPlayer(player[0]);
        pkrMach->putWildCard(2);
        pkrMach->play();
        }
      if (j==4) {
        player[0]->setGame(GAME_VPOKER4);
        pkrMach=new PkrMach(1,1,i);
        pkrMach->addPayout("Natural Royal",   0xe0000000l,0xefffffff,1000);
        pkrMach->addPayout("5 of a Kind",     0xb0000000l,0xbfffffff,300);
        pkrMach->addPayout("Wild Royal",      0xc0000000l,0xcfffffff,150);
        pkrMach->addPayout("Straight Flush",  0xa0000000l,0xafffffff,50);
        pkrMach->addPayout("4 of a Kind",     0x90000000l,0x9fffffff,10);
        pkrMach->addPayout("Full House",      0x70000000l,0x7fffffff,7);
        pkrMach->addPayout("Flush",           0x60000000l,0x6fffffff,5);
        pkrMach->addPayout("Straight",        0x50000000l,0x5fffffff,3);
        pkrMach->addPayout("3 of a Kind",     0x40000000l,0x4fffffff,2);
        pkrMach->addPayout("2 Pair",          0x20000000l,0x2fffffff,1);
        pkrMach->addPayout("Kings or better", 0x1dd00000l,0x1fffffff,1);
//        pkrMach->addPayout((unsigned long)(PK_PAIR | (12l<<24)),1);
        pkrMach->addPlayer(player[0]);
        pkrMach->putWildCard(0);
        pkrMach->play();
        }
      if (j==5) {
        pkrMach=new PkrMach(1,0,i);
        player[0]->setGame(GAME_VPOKERP);
        pkrMach->addPayout("Royal Flush",     0xe0000000l,0xefffffff,250);
        pkrMach->addPayout("Straight Flush"  ,0xa0000000l,0xafffffff,50);
        pkrMach->addPayout("4 of a Kind",     0x90000000l,0x9fffffff,25);
        pkrMach->addPayout("Full House",      0x70000000l,0x7fffffff,8);
        pkrMach->addPayout("Flush",           0x60000000l,0x6fffffff,5);
        pkrMach->addPayout("Straight",        0x50000000l,0x5fffffff,4);
        pkrMach->addPayout("3 of a Kind",     0x40000000l,0x4fffffff,3);
        pkrMach->addPayout("2 Pair",          0x20000000l,0x2fffffff,2);
        pkrMach->addPayout("Jacks or better", 0x1bb00000l,0x1fffffff,1);
//        pkrMach->addPayout(PK_PAIR | (11l<<24),1);
        pkrMach->addPlayer(player[0]);
        switch (i) {
          case   1:pkrMach->putProgressive(progressives[PROG_VPOKER1]); break;
          case   5:pkrMach->putProgressive(progressives[PROG_VPOKER5]); break;
          case  10:pkrMach->putProgressive(progressives[PROG_VPOKER10]); break;
          case  25:pkrMach->putProgressive(progressives[PROG_VPOKER25]); break;
          case 100:pkrMach->putProgressive(progressives[PROG_VPOKER100]); break;
          }
        pkrMach->play();
        switch (i) {
          case   1:progressives[PROG_VPOKER1]=pkrMach->getProgressive(); break;
          case   5:progressives[PROG_VPOKER5]=pkrMach->getProgressive(); break;
          case  10:progressives[PROG_VPOKER10]=pkrMach->getProgressive(); break;
          case  25:progressives[PROG_VPOKER25]=pkrMach->getProgressive(); break;
          case 100:progressives[PROG_VPOKER100]=pkrMach->getProgressive(); break;
          }
        }
      if (j==6) {
        player[0]->setGame(GAME_VPOKERDJ);
        pkrMach=new PkrMach(1,2,i);
        pkrMach->addPayout("Natural Royal",   0xe0000000l,0xefffffff,800);
        pkrMach->addPayout("Wild Royal",      0xc0000000l,0xcfffffff,100);
        pkrMach->addPayout("5 of a Kind",     0xb0000000l,0xbfffffff,50);
        pkrMach->addPayout("Straight Flush",  0xa0000000l,0xafffffff,25);
        pkrMach->addPayout("4 of a Kind",     0x90000000l,0x9fffffff,8);
        pkrMach->addPayout("Full House",      0x70000000l,0x7fffffff,5);
        pkrMach->addPayout("Flush",           0x60000000l,0x6fffffff,4);
        pkrMach->addPayout("Straight",        0x50000000l,0x5fffffff,3);
        pkrMach->addPayout("3 of a Kind",     0x40000000l,0x4fffffff,2);
        pkrMach->addPayout("2 Pair",          0x20000000l,0x2fffffff,1);
        pkrMach->addPlayer(player[0]);
        pkrMach->putWildCard(0);
        pkrMach->play();
        }
      if (j==7) {
        player[0]->setGame(GAME_VPOKERJ2);
        pkrMach=new PkrMach(1,1,i);
        pkrMach->addPayout("Five Wilds",      0xf0000000l,0xffffffff,2000);
        pkrMach->addPayout("Natural Royal",   0xe0000000l,0xefffffff,250);
        pkrMach->addPayout("Four Deuces",     0xd0000000l,0xdfffffff,25);
        pkrMach->addPayout("Wild Royal",      0xc0000000l,0xcfffffff,12);
        pkrMach->addPayout("5 of a Kind",     0xb0000000l,0xbfffffff,9);
        pkrMach->addPayout("Straight Flush",  0xa0000000l,0xafffffff,6);
        pkrMach->addPayout("4 of a Kind",     0x90000000l,0x9fffffff,3);
        pkrMach->addPayout("Full House",      0x70000000l,0x7fffffff,3);
        pkrMach->addPayout("Flush",           0x60000000l,0x6fffffff,3);
        pkrMach->addPayout("Straight",        0x50000000l,0x5fffffff,2);
        pkrMach->addPayout("3 of a Kind",     0x40000000l,0x4fffffff,1);
        pkrMach->addPlayer(player[0]);
        pkrMach->putWildCard(2);
        pkrMach->play();
        }
      if (j==8) {
        player[0]->setGame(GAME_VPOKER8);
        pkrMach=new PkrMach(1,0,i);
        pkrMach->addPayout("Royal Flush",     0xe0000000l,0xefffffff,800);
        pkrMach->addPayout("Straight Flush"  ,0xa0000000l,0xafffffff,50);
        pkrMach->addPayout("4 Aces",          0x9dddd000l,0x9ddddfff,80);
        pkrMach->addPayout("4 Eights",        0x98888000l,0x98888fff,80);
        pkrMach->addPayout("4 Sevens",        0x97777000l,0x97777fff,50);
        pkrMach->addPayout("4 of a Kind",     0x90000000l,0x9fffffff,25);
        pkrMach->addPayout("Full House",      0x70000000l,0x7fffffff,8);
        pkrMach->addPayout("Flush",           0x60000000l,0x6fffffff,5);
        pkrMach->addPayout("Straight",        0x50000000l,0x5fffffff,4);
        pkrMach->addPayout("3 of a Kind",     0x40000000l,0x4fffffff,3);
        pkrMach->addPayout("2 Pair",          0x20000000l,0x2fffffff,2);
        pkrMach->addPayout("Jacks or better", 0x1bb00000l,0x1fffffff,1);
        pkrMach->addPlayer(player[0]);
        pkrMach->play();
        }
      if (j==9) {
        player[0]->setGame(GAME_VPOKERB);
        pkrMach=new PkrMach(1,0,i);
        pkrMach->addPayout("Royal Flush",     0xe0000000l,0xefffffff,800);
        pkrMach->addPayout("Straight Flush"  ,0xa0000000l,0xafffffff,50);
        pkrMach->addPayout("4 Aces",          0x9dddd000l,0x9ddddfff,80);
        pkrMach->addPayout("4 2s, 3s or 4s",  0x92222000l,0x94444fff,40);
        pkrMach->addPayout("4 5-K",           0x90000000l,0x9fffffff,25);
        pkrMach->addPayout("Full House",      0x70000000l,0x7fffffff,7);
        pkrMach->addPayout("Flush",           0x60000000l,0x6fffffff,5);
        pkrMach->addPayout("Straight",        0x50000000l,0x5fffffff,4);
        pkrMach->addPayout("3 of a Kind",     0x40000000l,0x4fffffff,3);
        pkrMach->addPayout("2 Pair",          0x20000000l,0x2fffffff,2);
        pkrMach->addPayout("Jacks or better", 0x1bb00000l,0x1fffffff,1);
        pkrMach->addPlayer(player[0]);
        pkrMach->play();
        }
      if (j==10) {
        player[0]->setGame(GAME_VPOKER2B);
        pkrMach=new PkrMach(1,0,i);
        pkrMach->addPayout("Royal Flush",     0xe0000000l,0xefffffff,800);
        pkrMach->addPayout("Straight Flush"  ,0xa0000000l,0xafffffff,50);
        pkrMach->addPayout("4 Aces",          0x9dddd000l,0x9ddddfff,160);
        pkrMach->addPayout("4 2s, 3s or 4s",  0x92222000l,0x94444fff,80);
        pkrMach->addPayout("4 5-K",           0x90000000l,0x9fffffff,50);
        pkrMach->addPayout("Full House",      0x70000000l,0x7fffffff,9);
        pkrMach->addPayout("Flush",           0x60000000l,0x6fffffff,6);
        pkrMach->addPayout("Straight",        0x50000000l,0x5fffffff,5);
        pkrMach->addPayout("3 of a Kind",     0x40000000l,0x4fffffff,3);
        pkrMach->addPayout("2 Pair",          0x20000000l,0x2fffffff,1);
        pkrMach->addPayout("Jacks or better", 0x1bb00000l,0x1fffffff,1);
        pkrMach->addPlayer(player[0]);
        pkrMach->play();
        }
      if (j==11) {
        player[0]->setGame(GAME_VPOKER3B);
        pkrMach=new PkrMach(1,0,i);
        pkrMach->addPayout("Royal Flush",     0xe0000000l,0xefffffff,800);
        pkrMach->addPayout("Straight Flush"  ,0xa0000000l,0xafffffff,80);
        pkrMach->addPayout("4 Aces",          0x9dddd000l,0x9ddddfff,240);
        pkrMach->addPayout("4 2s, 3s or 4s",  0x92222000l,0x94444fff,120);
        pkrMach->addPayout("4 5-K",           0x90000000l,0x9fffffff,50);
        pkrMach->addPayout("Full House",      0x70000000l,0x7fffffff,8);
        pkrMach->addPayout("Flush",           0x60000000l,0x6fffffff,5);
        pkrMach->addPayout("Straight",        0x50000000l,0x5fffffff,4);
        pkrMach->addPayout("3 of a Kind",     0x40000000l,0x4fffffff,3);
        pkrMach->addPayout("2 Pair",          0x20000000l,0x2fffffff,1);
        pkrMach->addPayout("Jacks or better", 0x1bb00000l,0x1fffffff,1);
        pkrMach->addPlayer(player[0]);
        pkrMach->play();
        }
      delete(pkrMach);
      }
    if (game==4) {
      lirGame=new Lir(1,0,5);
      player[0]->setGame(GAME_LIR);
      for (i=0;i<PLAYERS_LIR;i++) gamePlayers[i]=-1;
      gamePlayers[Random(PLAYERS_LIR)]=99;
      for (i=0;i<PLAYERS_LIR;i++) if (gamePlayers[i]==-1) {
        r=Random(MAX_PLAYERS-2)+1;
        for (j=0;j<PLAYERS_LIR;j++) if (gamePlayers[j]==r) r=-1;
        gamePlayers[i]=r;
        }
      for (i=0;i<PLAYERS_LIR;i++)
        if (gamePlayers[i]==99) lirGame->addPlayer(player[0]);
        else if (gamePlayers[i]==-1) lirGame->addPlayer(NULL);
        else lirGame->addPlayer(player[gamePlayers[i]]);
      lirGame->play();
      delete(lirGame);
      }
    if (game==5) {
      craps=new Craps(player[0],1);
      player[0]->setGame(GAME_CRAPS);
      craps->play();
      delete(craps);
      }
    if (game==14) {
      moneyWheel=new MoneyWheel(player[0]);
      player[0]->setGame(GAME_WHEEL);
      moneyWheel->play();
      delete(moneyWheel);
      }
    if (game==13) {
      chuck=new Chuck(player[0]);
      player[0]->setGame(GAME_CHUCK);
      chuck->play();
      delete(chuck);
      }
    if (game==18) {
      sicbo=new Sicbo(player[0]);
      player[0]->setGame(GAME_SICBO);
      sicbo->play();
      delete(sicbo);
      }
    if (game==6) {
      roul=new Roul(player[0],1);
      player[0]->setGame(GAME_ROUL);
      roul->play();
      delete(roul);
      }
    if (game==7) {
      player[0]->setGame(GAME_SLOTS);
      Slots(player[0]);
      }
    if (game==8) {
      keno=new Keno(player[0]);
      player[0]->setGame(GAME_KENO);
      keno->play();
      delete(keno);
      }
    if (game==9) {
      carib=new Carib(1,0,5);
      player[0]->setGame(GAME_CARIB);
      for (i=0;i<PLAYERS_CARIB;i++) gamePlayers[i]=-1;
      gamePlayers[Random(PLAYERS_CARIB)]=99;
      for (i=0;i<PLAYERS_CARIB;i++) if (gamePlayers[i]==-1) {
        r=Random(MAX_PLAYERS-2)+1;
        for (j=0;j<PLAYERS_CARIB;j++) if (gamePlayers[j]==r) r=-1;
        gamePlayers[i]=r;
        }
      for (i=0;i<PLAYERS_CARIB;i++)
        if (gamePlayers[i]==99) carib->addPlayer(player[0]);
        else if (gamePlayers[i]==-1) carib->addPlayer(NULL);
        else carib->addPlayer(player[gamePlayers[i]]);
      carib->play();
      delete(carib);
      }
    if (game==10) {
#ifdef GRAPHIC
      i=5;
      gc=rcs_openGC(display,mainScreen);
      font=rcs_openFont(display,MENU_FONT);
      rcs_setFont(display,gc,font);
      rcs_namedForeground(display,gc,"darkgreen");
      rcs_drawFilledBox(display,mainScreen,gc,0,0,800,600);
      rcs_namedForeground(display,gc,"yellow");
      rcs_drawString(display,mainScreen,gc,320,65,"Poker");
      rcs_drawString(display,mainScreen,gc,320,125,"Texas Hold'em");
      rcs_drawString(display,mainScreen,gc,320,165,"7 Card Stud");
      rcs_closeFont(display,font);
      rcs_closeGC(display,gc);
      displayScreen();
      flag=' ';
      while (flag==' ') {
        event=getEvent(display);
        if (event.type==EVENT_BUTTON_PRESS && event.d1==1) {
          if (event.d2>=300 && event.d2<=400 &&
              event.d3>=100 && event.d3<=130) {
            j=1; flag='X';
            }
          if (event.d2>=300 && event.d2<=400 &&
              event.d3>=140 && event.d3<=170) {
            j=2; flag='X';
            }
          }
        }
#endif
#ifdef CONSOLE
      ClrScr();
      Output("1. $5 to $10 Table\n");
      Output("2. $25 to $50 Table\n");
      Output("3. $100 to $200 Table\n");
      Output("4. $250 to $500 Table\n");
      Output("5. $1000 to $2000 Table\n");
      Input(buffer);
      sscanf(buffer,"%d",&i);
      if (i==1) i=5;
      else if (i==2) i=25;
      else if (i==3) i=100;
      else if (i==4) i=250;
      else if (i==5) i=1000;
      else i=5;
      Output("1. Texas Hold'em\n");
      Output("2. 7 Card Stud\n");
      Input(buffer);
      sscanf(buffer,"%d",&j);
#endif
      if (j==1) {
        texas=new Texas(1,0,1,i,i*2);
        player[0]->setGame(GAME_TEXAS);
        for (i=0;i<PLAYERS_TEXAS;i++) gamePlayers[i]=-1;
        gamePlayers[Random(PLAYERS_TEXAS)]=99;
        for (i=0;i<PLAYERS_TEXAS;i++) if (gamePlayers[i]==-1) {
          r=Random(MAX_PLAYERS-2)+1;
          for (j=0;j<PLAYERS_TEXAS;j++) if (gamePlayers[j]==r) r=-1;
          gamePlayers[i]=r;
          }
        for (i=0;i<PLAYERS_TEXAS;i++)
          if (gamePlayers[i]==99) texas->addPlayer(player[0]);
          else if (gamePlayers[i]==-1) texas->addPlayer(NULL);
          else texas->addPlayer(player[gamePlayers[i]]);
        texas->play();
        delete(texas);
        }
      if (j==2) {
        card7=new Card7(1,0,1,i,i*2);
        player[0]->setGame(GAME_CARD7);
        for (i=0;i<PLAYERS_CARD7;i++) gamePlayers[i]=-1;
        gamePlayers[Random(PLAYERS_CARD7)]=99;
        for (i=0;i<PLAYERS_CARD7;i++) if (gamePlayers[i]==-1) {
          r=Random(MAX_PLAYERS-2)+1;
          for (j=0;j<PLAYERS_TEXAS;j++) if (gamePlayers[j]==r) r=-1;
          gamePlayers[i]=r;
          }
        for (i=0;i<PLAYERS_CARD7;i++)
          if (gamePlayers[i]==99) card7->addPlayer(player[0]);
          else if (gamePlayers[i]==-1) card7->addPlayer(NULL);
          else card7->addPlayer(player[gamePlayers[i]]);
        card7->play();
        delete(card7);
        }
      }
    if (game==15) {
      dStud=new DStud(1,0,5);
      player[0]->setGame(GAME_DSTUD);
      for (i=0;i<PLAYERS_DSTUD;i++) gamePlayers[i]=-1;
      gamePlayers[Random(PLAYERS_DSTUD)]=99;
      for (i=0;i<PLAYERS_DSTUD;i++) if (gamePlayers[i]==-1) {
        r=Random(MAX_PLAYERS-2)+1;
        for (j=0;j<PLAYERS_DSTUD;j++) if (gamePlayers[j]==r) r=-1;
        gamePlayers[i]=r;
        }
      for (i=0;i<PLAYERS_DSTUD;i++)
        if (gamePlayers[i]==99) dStud->addPlayer(player[0]);
        else if (gamePlayers[i]==-1) dStud->addPlayer(NULL);
        else dStud->addPlayer(player[gamePlayers[i]]);
      dStud->play();
      delete(dStud);
      }
    if (game==16) {
      three=new Three(1,0,5);
      player[0]->setGame(GAME_THREE);
      for (i=0;i<PLAYERS_THREE;i++) gamePlayers[i]=-1;
      gamePlayers[Random(PLAYERS_THREE)]=99;
      for (i=0;i<PLAYERS_THREE;i++) if (gamePlayers[i]==-1) {
        r=Random(MAX_PLAYERS-2)+1;
        for (j=0;j<PLAYERS_THREE;j++) if (gamePlayers[j]==r) r=-1;
        gamePlayers[i]=r;
        }
      for (i=0;i<PLAYERS_THREE;i++)
        if (gamePlayers[i]==99) three->addPlayer(player[0]);
        else if (gamePlayers[i]==-1) three->addPlayer(NULL);
        else three->addPlayer(player[gamePlayers[i]]);
      three->play();
      delete(three);
      }
    if (game==17) {
      paigow=new Paigow(1,0,20);
      player[0]->setGame(GAME_PAIGOW);
      for (i=0;i<PLAYERS_PAIGOW;i++) gamePlayers[i]=-1;
      gamePlayers[Random(PLAYERS_PAIGOW)]=99;
      for (i=0;i<PLAYERS_PAIGOW;i++) if (gamePlayers[i]==-1) {
        r=Random(MAX_PLAYERS-2)+1;
        for (j=0;j<PLAYERS_PAIGOW;j++) if (gamePlayers[j]==r) r=-1;
        gamePlayers[i]=r;
        }
      for (i=0;i<PLAYERS_PAIGOW;i++)
        if (gamePlayers[i]==99) paigow->addPlayer(player[0]);
        else if (gamePlayers[i]==-1) paigow->addPlayer(NULL);
        else paigow->addPlayer(player[gamePlayers[i]]);
      paigow->play();
      delete(paigow);
      }
    if (game==20) {
      war=new War(6,0,6);
      player[0]->setGame(GAME_WAR);
      for (i=0;i<PLAYERS_WAR;i++) gamePlayers[i]=-1;
      gamePlayers[Random(PLAYERS_WAR)]=99;
      for (i=0;i<PLAYERS_WAR;i++) if (gamePlayers[i]==-1) {
        r=Random(MAX_PLAYERS-2)+1;
        for (j=0;j<PLAYERS_WAR;j++) if (gamePlayers[j]==r) r=-1;
        gamePlayers[i]=r;
        }
      for (i=0;i<PLAYERS_WAR;i++)
        if (gamePlayers[i]==99) war->addPlayer(player[0]);
        else if (gamePlayers[i]==-1) war->addPlayer(NULL);
        else war->addPlayer(player[gamePlayers[i]]);
      war->play();
      delete(war);
      }
    if (game==21) {
      wild=new WildHoldem(1,0,4);
      player[0]->setGame(GAME_WILD);
      for (i=0;i<PLAYERS_WILD;i++) gamePlayers[i]=-1;
      gamePlayers[Random(PLAYERS_WILD)]=99;
      for (i=0;i<PLAYERS_WILD;i++) if (gamePlayers[i]==-1) {
        r=Random(MAX_PLAYERS-2)+1;
        for (j=0;j<PLAYERS_WILD;j++) if (gamePlayers[j]==r) r=-1;
        gamePlayers[i]=r;
        }
      for (i=0;i<PLAYERS_WILD;i++)
        if (gamePlayers[i]==99) wild->addPlayer(player[0]);
        else if (gamePlayers[i]==-1) wild->addPlayer(NULL);
        else wild->addPlayer(player[gamePlayers[i]]);
      wild->play();
      delete(wild);
      }
    if (game==22) {
      bahama=new Bahama(1,0,5);
      player[0]->setGame(GAME_BAHAMA);
      for (i=0;i<PLAYERS_BAHAMA;i++) gamePlayers[i]=-1;
      gamePlayers[Random(PLAYERS_BAHAMA)]=99;
      for (i=0;i<PLAYERS_BAHAMA;i++) if (gamePlayers[i]==-1) {
        r=Random(MAX_PLAYERS-2)+1;
        for (j=0;j<PLAYERS_BAHAMA;j++) if (gamePlayers[j]==r) r=-1;
        gamePlayers[i]=r;
        }
      for (i=0;i<PLAYERS_BAHAMA;i++)
        if (gamePlayers[i]==99) bahama->addPlayer(player[0]);
        else if (gamePlayers[i]==-1) bahama->addPlayer(NULL);
        else bahama->addPlayer(player[gamePlayers[i]]);
      bahama->play();
      delete(bahama);
      }
    if (game==23) {
      royal=new Royal(6,0,2);
      player[0]->setGame(GAME_ROYAL);
      for (i=0;i<PLAYERS_ROYAL;i++) gamePlayers[i]=-1;
      gamePlayers[Random(PLAYERS_ROYAL)]=99;
      for (i=0;i<PLAYERS_ROYAL;i++) if (gamePlayers[i]==-1) {
        r=Random(MAX_PLAYERS-2)+1;
        for (j=0;j<PLAYERS_ROYAL;j++) if (gamePlayers[j]==r) r=-1;
        gamePlayers[i]=r;
        }
      for (i=0;i<PLAYERS_ROYAL;i++)
        if (gamePlayers[i]==99) royal->addPlayer(player[0]);
        else if (gamePlayers[i]==-1) royal->addPlayer(NULL);
        else royal->addPlayer(player[gamePlayers[i]]);
      royal->play();
      delete(royal);
      }
    if (game==24) {
      aruba=new Aruba(1,0,5);
      player[0]->setGame(GAME_ARUBA);
      for (i=0;i<PLAYERS_ARUBA;i++) gamePlayers[i]=-1;
      gamePlayers[Random(PLAYERS_ARUBA)]=99;
      for (i=0;i<PLAYERS_ARUBA;i++) if (gamePlayers[i]==-1) {
        r=Random(MAX_PLAYERS-2)+1;
        for (j=0;j<PLAYERS_ARUBA;j++) if (gamePlayers[j]==r) r=-1;
        gamePlayers[i]=r;
        }
      for (i=0;i<PLAYERS_ARUBA;i++)
        if (gamePlayers[i]==99) aruba->addPlayer(player[0]);
        else if (gamePlayers[i]==-1) aruba->addPlayer(NULL);
        else aruba->addPlayer(player[gamePlayers[i]]);
      aruba->play();
      delete(aruba);
      }
    if (game==25) {
      paigowt=new PaigowTiles(1,0,20);
      player[0]->setGame(GAME_PAIGOWT);
      for (i=0;i<PLAYERS_PAIGOWT;i++) gamePlayers[i]=-1;
      gamePlayers[Random(PLAYERS_PAIGOWT)]=99;
      for (i=0;i<PLAYERS_PAIGOWT;i++) if (gamePlayers[i]==-1) {
        r=Random(MAX_PLAYERS-2)+1;
        for (j=0;j<PLAYERS_PAIGOWT;j++) if (gamePlayers[j]==r) r=-1;
        gamePlayers[i]=r;
        }
      for (i=0;i<PLAYERS_PAIGOWT;i++)
        if (gamePlayers[i]==99) paigowt->addPlayer(player[0]);
        else if (gamePlayers[i]==-1) paigowt->addPlayer(NULL);
        else paigowt->addPlayer(player[gamePlayers[i]]);
      paigowt->play();
      delete(paigowt);
      }
    if (game==26) {
      wave=new Wave(8,0,5);
      player[0]->setGame(GAME_WAVE);
      for (i=0;i<PLAYERS_WAVE;i++) gamePlayers[i]=-1;
      gamePlayers[Random(PLAYERS_WAVE)]=99;
      for (i=0;i<PLAYERS_WAVE;i++) if (gamePlayers[i]==-1) {
        r=Random(MAX_PLAYERS-2)+1;
        for (j=0;j<PLAYERS_WAVE;j++) if (gamePlayers[j]==r) r=-1;
        gamePlayers[i]=r;
        }
      for (i=0;i<PLAYERS_WAVE;i++)
        if (gamePlayers[i]==99) wave->addPlayer(player[0]);
        else if (gamePlayers[i]==-1) wave->addPlayer(NULL);
        else wave->addPlayer(player[gamePlayers[i]]);
      wave->play();
      delete(wave);
      }
    if (game==27) {
      superFun=new SuperFun(1,0,2);
      player[0]->setGame(GAME_SUPERFUN);
      for (i=0;i<PLAYERS_ROYAL;i++) gamePlayers[i]=-1;
      gamePlayers[Random(PLAYERS_BJ)]=99;
      for (i=0;i<PLAYERS_ROYAL;i++) if (gamePlayers[i]==-1) {
        r=Random(MAX_PLAYERS-2)+1;
        for (j=0;j<PLAYERS_ROYAL;j++) if (gamePlayers[j]==r) r=-1;
        gamePlayers[i]=r;
        }
      for (i=0;i<PLAYERS_BJ;i++)
        if (gamePlayers[i]==99) superFun->addPlayer(player[0]);
        else if (gamePlayers[i]==-1) superFun->addPlayer(NULL);
        else superFun->addPlayer(player[gamePlayers[i]]);
      superFun->play();
      delete(superFun);
      }
    if (game==28) {
      bonus6=new Bonus6(1,0,2);
      player[0]->setGame(GAME_BONUS6);
      for (i=0;i<PLAYERS_BONUS6;i++) gamePlayers[i]=-1;
      gamePlayers[Random(PLAYERS_BONUS6)]=99;
      for (i=0;i<PLAYERS_BONUS6;i++) if (gamePlayers[i]==-1) {
        r=Random(MAX_PLAYERS-2)+1;
        for (j=0;j<PLAYERS_BONUS6;j++) if (gamePlayers[j]==r) r=-1;
        gamePlayers[i]=r;
        }
      for (i=0;i<PLAYERS_BONUS6;i++)
        if (gamePlayers[i]==99) bonus6->addPlayer(player[0]);
        else if (gamePlayers[i]==-1) bonus6->addPlayer(NULL);
        else bonus6->addPlayer(player[gamePlayers[i]]);
      bonus6->play();
      delete(bonus6);
      }
    if (game==29) {
      bingo=new Bingo(player[0]);
      player[0]->setGame(GAME_BINGO);
      bingo->play();
      delete(bingo);
      }
    if (game==30) {
      videoKeno=new VideoKeno(player[0]);
      videoKeno->setGame(1);
      videoKeno->setDenomination(1.00);
      videoKeno->play();
      videoKeno->cashOut();
      delete(videoKeno);
      }
    if (game==31) {
      holdem=new Holdem(1,0,5);
      player[0]->setGame(GAME_HOLDEM);
      for (i=0;i<PLAYERS_HOLDEM;i++) gamePlayers[i]=-1;
      gamePlayers[Random(PLAYERS_HOLDEM)]=99;
      for (i=0;i<PLAYERS_CARIB;i++) if (gamePlayers[i]==-1) {
        r=Random(MAX_PLAYERS-2)+1;
        for (j=0;j<PLAYERS_CARIB;j++) if (gamePlayers[j]==r) r=-1;
        gamePlayers[i]=r;
        }
      for (i=0;i<PLAYERS_HOLDEM;i++)
        if (gamePlayers[i]==99) holdem->addPlayer(player[0]);
        else if (gamePlayers[i]==-1) holdem->addPlayer(NULL);
        else holdem->addPlayer(player[gamePlayers[i]]);
      holdem->play();
      delete(holdem);
      }
    if (game==32) {
      boston5=new Boston5(1,0,5);
      player[0]->setGame(GAME_BOSTON5);
      for (i=0;i<PLAYERS_BOSTON5;i++) gamePlayers[i]=-1;
      gamePlayers[Random(PLAYERS_BOSTON5)]=99;
      for (i=0;i<PLAYERS_CARIB;i++) if (gamePlayers[i]==-1) {
        r=Random(MAX_PLAYERS-2)+1;
        for (j=0;j<PLAYERS_CARIB;j++) if (gamePlayers[j]==r) r=-1;
        gamePlayers[i]=r;
        }
      for (i=0;i<PLAYERS_BOSTON5;i++)
        if (gamePlayers[i]==99) boston5->addPlayer(player[0]);
        else if (gamePlayers[i]==-1) boston5->addPlayer(NULL);
        else boston5->addPlayer(player[gamePlayers[i]]);
      boston5->play();
      delete(boston5);
      }
    if (game==33) {
      flop=new Flop(1,0,5);
      player[0]->setGame(GAME_FLOP);
      for (i=0;i<PLAYERS_FLOP;i++) gamePlayers[i]=-1;
      gamePlayers[Random(PLAYERS_FLOP)]=99;
      for (i=0;i<PLAYERS_FLOP;i++) if (gamePlayers[i]==-1) {
        r=Random(MAX_PLAYERS-2)+1;
        for (j=0;j<PLAYERS_FLOP;j++) if (gamePlayers[j]==r) r=-1;
        gamePlayers[i]=r;
        }
      for (i=0;i<PLAYERS_FLOP;i++)
        if (gamePlayers[i]==99) flop->addPlayer(player[0]);
        else if (gamePlayers[i]==-1) flop->addPlayer(NULL);
        else flop->addPlayer(player[gamePlayers[i]]);
      flop->play();
      delete(flop);
      }
    if (game==34) {
      p357=new P357(1,0,5);
      player[0]->setGame(GAME_357);
      for (i=0;i<PLAYERS_357;i++) gamePlayers[i]=-1;
      gamePlayers[Random(PLAYERS_357)]=99;
      for (i=0;i<PLAYERS_357;i++) if (gamePlayers[i]==-1) {
        r=Random(MAX_PLAYERS-2)+1;
        for (j=0;j<PLAYERS_357;j++) if (gamePlayers[j]==r) r=-1;
        gamePlayers[i]=r;
        }
      for (i=0;i<PLAYERS_357;i++)
        if (gamePlayers[i]==99) p357->addPlayer(player[0]);
        else if (gamePlayers[i]==-1) p357->addPlayer(NULL);
        else p357->addPlayer(player[gamePlayers[i]]);
      p357->play();
      delete(p357);
      }
    ClrScr();
    if (game==99) statistics();
    }
#ifdef CONSOLE
  ClrScr();
  statistics();
#endif
  player[0]->save();
#ifdef GRAPHIC
  rcs_closePixmap(display,mainScreen);
  rcs_closeWindow(display,mainWindow);
  rcs_closeDisplay(display);
#endif
  return 0;
}

#ifdef WIN32
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow) {
  rcs_initWin32(hInstance);
  main();
  return 0;
    }
#endif

