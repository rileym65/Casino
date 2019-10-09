#include <stdlib.h>
#include "header.h"
#include "player.h"

Player::Player(char* n,char o) {
  int i;
  for (i=0;i<MAX_BETS;i++) {
    bets[i]=new Bet(0);
    if (bets[i] == NULL) {
      printf("Could not create bet objects\n");
      exit(1);
      }
    }
  hand=(Hand**)calloc(MAX_HANDS,sizeof(Hand*));
  if (hand==NULL) {
    printf("Out of memory creating Player.Hand\n");
    exit(1);
    }
  for (i=0;i<MAX_HANDS;i++) hand[i]=new Hand();
  strcpy(name,n);
  game=0;
  owner=o;
  cash=1000;
  vip = 0;
  for (i=0;i<MAX_GAMES;i++) {
    moneyPaidIn[i]=0;
    moneyPaidOut[i]=0;
    }
  nextBet=1;
  strategy=Random(4);
  strcpy(kenoLast,"1,2,3,4,5,6,7,8,9,10");
  bluffer=Random(75);
  }

Player::~Player() {
  int i;
  for (i=0;i<MAX_HANDS;i++) delete hand[i];
  free(hand);
  for (i=0;i<MAX_BETS;i++) delete(bets[i]);
  }

void Player::resetStrategy() {
  nextBet=1;
  }

void Player::adjustStrategy() {
  switch (strategy) {
    case 1:nextBet*=2;
           if (nextBet>16) nextBet=1;
           break;
    case 2:nextBet=nextBet*2+1;
           if (nextBet>16) nextBet=1;
           break;
    case 3:nextBet++;
           if (nextBet>16) nextBet=1;
           break;
    }
  }

double Player::getBet() {
  return nextBet;
  }

void Player::addPaidIn(double a) { moneyPaidIn[subGame] += a; }

void Player::addPaidOut(double a) { moneyPaidOut[subGame] += a; }

void Player::setPaidIn(int game,double a) { moneyPaidIn[game] = a; }
void Player::setPaidOut(int game,double a) { moneyPaidOut[game] = a; }

double Player::paidIn(int g)
{
  return moneyPaidIn[g];
}

double Player::paidOut(int g)
{
  return moneyPaidOut[g];
}

double Player::average(int g)
{
  return(moneyPaidOut[g]/moneyPaidIn[g]*100);
}

void Player::addChips(int chipSize,int chipNum)
{
  moneyPaidOut[game]+=chipSize*chipNum;
  cash+=(chipSize*chipNum);
}

double Player::money()
{
  return cash;
}

void Player::clearAllBets()
{
  int i;
  for (i=0;i<MAX_BETS;i++) clearBet(i);
}

void Player::clearBet(int bet)
{
  if (bets[bet]!=NULL) {
    bets[bet]->clear();
    }
}

double Player::getHandBet(int hand)
{
  int   i;
  float amount;
  amount=0;
  for (i=0;i<MAX_BETS;i++)
    if (bets[i]!=NULL && bets[i]->getHand()==hand && bets[i]->getX()!=0)
      amount += bets[i]->getValue();
  return amount;
}

Hand* Player::getHand(int h)
{
  return hand[h];
}

char* Player::getName()
{
  return &name[0];
}

void Player::loseHandBets(int hand)
{
  int i;
  for (i=0;i<MAX_BETS;i++)
    if (bets[i] != NULL && bets[i]->getHand()==hand) clearBet(i);
}

void Player::newCard(Card* card,int h)
{
  Hand* hand;
  hand=getHand(h);
  hand->cards[hand->numCards++]=card;
}

void Player::newHand(int h)
{
  Hand* hand;
  hand=getHand(h);
  hand->numCards=0;
}

double Player::placeBet(double amount,int hand,int x,int y)
{
  int   i;
  int   slot;
  slot=-1;
  for (i=0;i<MAX_BETS;i++) {
    if ((bets[i]->getX()+bets[i]->getY()+bets[i]->getHand())==0) slot=i;
    }
  if (slot>-1) {
    clearBet(slot);
    bets[slot]->setPosition(x,y);
    bets[slot]->putHand(hand);
    bets[slot]->place(amount);
    moneyPaidIn[game]+=amount;
    cash-=long(amount);
    }
  if (slot==-1) return 0; else return amount;
}

void Player::setGame(int g)
{
  game=g;
}

void Player::setSubGame(int game) {
  subGame=game;
  }

void Player::moveHandBet(int hand,int newHand,int x,int y) {
  int i;
  for (i=0;i<MAX_BETS;i++)
    if (bets[i]->getHand()==hand) {
      bets[i]->putHand(newHand);
      bets[i]->setPosition(x,y);
      }
  }

void Player::clearWonBets() {
  int i;
  for (i=0;i<MAX_BETS;i++)
    if (bets[i]->getX()!=0) 
      bets[i]->clearWonBet();
  }

void Player::clearNonWinners() {
  int i;
  for (i=0;i<MAX_BETS;i++)
    if (bets[i]->getX()!=0) 
      bets[i]->clearNonWinner();
  }

void Player::showBets()
{
  int i;
  for (i=0;i<MAX_BETS;i++)
    if (bets[i]->getX()!=0) 
      bets[i]->display();
}

void Player::paintBets()
{
  int i;
  for (i=0;i<MAX_BETS;i++)
    if (bets[i]->getX()!=0) 
      bets[i]->paint(display,mainScreen);
}

char Player::playerType()
{
  return owner;
}

void Player::winHandBets(int hand,double mult)
{
  int i;
  if (mult>0) {
    if (strategy!=3) nextBet=1;
      else if (nextBet>1) nextBet--;
    }
  float amount;
  amount=0;
  for (i=0;i<MAX_BETS;i++)
    amount+=bets[i]->winHandBet(hand,mult);
  winMoney(amount);
}

void Player::loseXYBets(int x1,int y1,int x2,int y2) {
  int i;
  for (i=0;i<MAX_BETS;i++)
    bets[i]->loseXYBet(x1,y1,x2,y2);
  }

void Player::winXYBets(int x1,int y1,int x2,int y2,double mult)
{
  int i;
  double amount;
  amount=0;
  for (i=0;i<MAX_BETS;i++)
    amount+=bets[i]->winXYBet(x1,y1,x2,y2,mult);
  winMoney(amount);
}

void  Player::winOdds(double a,double bet,double payoff)
{
  double amount;
  amount=0;
  if (bet<payoff) {
    while (a>=bet) {
      amount+=payoff;
      a-=bet;
      }
    amount+=a;
    }
  else {
    while (a>=bet) {
      amount+=payoff;
      a-=bet;
      }
    }
  winMoney(amount);
}

void Player::winMoney(double amount)
{
  moneyPaidOut[game]+=amount;
  cash+=long(amount);
}

void Player::putKenoLast(char* l) { strcpy(kenoLast,l); }

char* Player::getKenoLast() { return kenoLast; }

int Player::getBluffer() { return bluffer; }

void Player::save()
{
  FILE *OutFile;
  int i;
//  strcpy(buffer,name);
//  strcat(buffer,".sav");
//  OutFile=fopen(buffer,"w");
  OutFile=fopen(saveFileName,"w");
  fprintf(OutFile,"%s\n",name);
  fprintf(OutFile,"%c\n",owner);
  fprintf(OutFile,"%d\n",chips1);
  fprintf(OutFile,"%d\n",chips5);
  fprintf(OutFile,"%d\n",chips25);
  fprintf(OutFile,"%d\n",chips100);
  fprintf(OutFile,"%d\n",chips500);
  fprintf(OutFile,"%d\n",chips1000);
  fprintf(OutFile,"%d\n",pennies);
  fprintf(OutFile,"%d\n",nickles);
  fprintf(OutFile,"%d\n",dimes);
  fprintf(OutFile,"%d\n",quarters);
  fprintf(OutFile,"%d\n",halfdollars);
  fprintf(OutFile,"%d\n",dollars);
  fprintf(OutFile,"%d\n",bills1);
  fprintf(OutFile,"%d\n",bills5);
  fprintf(OutFile,"%d\n",bills10);
  fprintf(OutFile,"%d\n",bills20);
  fprintf(OutFile,"%d\n",bills50);
  fprintf(OutFile,"%d\n",bills100);
  fprintf(OutFile,"%f\n",cash);
  for (i=0;i<MAX_GAMES;i++) {
    fprintf(OutFile,"%f\n",moneyPaidIn[i]);
    fprintf(OutFile,"%f\n",moneyPaidOut[i]);
    }
  for (i=0;i<MAX_PROG;i++) {
    fprintf(OutFile,"%f\n",progressives[i]);
    }
  fprintf(OutFile,"%s\n",kenoLast);
  fclose(OutFile);
}

void Player::load()
{
  FILE *InFile;
  int i;
//  strcpy(buffer,name);
//  strcat(buffer,".sav");
//  if ((InFile=fopen(buffer,"r"))!=NULL) {
  if ((InFile=fopen(saveFileName,"r"))!=NULL) {
    fgets(name,80,InFile);
    rcs_trimLineEndings(name);
    fscanf(InFile,"%c\n",&owner);
    fscanf(InFile,"%d\n",&chips1);
    fscanf(InFile,"%d\n",&chips5);
    fscanf(InFile,"%d\n",&chips25);
    fscanf(InFile,"%d\n",&chips100);
    fscanf(InFile,"%d\n",&chips500);
    fscanf(InFile,"%d\n",&chips1000);
    fscanf(InFile,"%d\n",&pennies);
    fscanf(InFile,"%d\n",&nickles);
    fscanf(InFile,"%d\n",&dimes);
    fscanf(InFile,"%d\n",&quarters);
    fscanf(InFile,"%d\n",&halfdollars);
    fscanf(InFile,"%d\n",&dollars);
    fscanf(InFile,"%d\n",&bills1);
    fscanf(InFile,"%d\n",&bills5);
    fscanf(InFile,"%d\n",&bills10);
    fscanf(InFile,"%d\n",&bills20);
    fscanf(InFile,"%d\n",&bills50);
    fscanf(InFile,"%d\n",&bills100);
    fscanf(InFile,"%lf\n",&cash);
    for (i=0;i<MAX_GAMES;i++) {
      fscanf(InFile,"%lf\n",&moneyPaidIn[i]);
      fscanf(InFile,"%lf\n",&moneyPaidOut[i]);
      }
    for (i=0;i<MAX_PROG;i++) {
      fscanf(InFile,"%lf\n",&progressives[i]);
      }
    fscanf(InFile,"%s\n",kenoLast);
    fclose(InFile);
  }
}

long Player::getPaidIn() { return (long)moneyPaidIn[game]; }

long Player::getPaidOut() { return (long)moneyPaidOut[game]; }

void Player::addVip(long v) { vip += v; }

long Player::getVip() { return vip; }

void Player::addMoney(double m) { cash += m; }

void Player::subMoney(double m) { cash -= m; }

double Player::getMoney() { return cash; }


