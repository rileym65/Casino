#include <stdlib.h>
#include <stdio.h>
#include "librcs.h"
#include "header.h"

Hand::Hand() {
  cards=(Card**)calloc(sizeof(Card*),10);
  numCards=0;
  }

Hand::Hand(int maxcards) {
  cards=(Card**)calloc(sizeof(Card*),maxcards);
  numCards=0;
  }


Hand::~Hand() {
  delete cards;
  }

void Hand::addCard(Card* c) {
  cards[numCards++]=c;
  }

void Hand::sort(int wild) {
  Card* card;
  int  i,j;
  char flag;
/*  int  last; */
/*  int  count; */
  int  strCount;
/*  int  strHigh;  */
/*  int  strLast; */
  int  wilds;
  flag='*';
  while (flag=='*') {
    flag=' ';
    for (i=0;i<numCards-1;i++)
      if (cards[i]->value()>cards[i+1]->value()) {
        flag='*';
        card=cards[i]; cards[i]=cards[i+1]; cards[i+1]=card;
        }
    }
  for (i=0;i<4;i++) suits[i]=0;
  for (i=0;i<15;i++) numbers[i]=0;
  for (i=0;i<8;i++) combinations[i]=0;
  wildCount=0;
  for (i=0;i<numCards;i++) {
    if (cards[i]->value() == wild || cards[i]->value()==0) wildCount++;
    else {
      numbers[cards[i]->value()]++;
      switch (cards[i]->getSuit()) {
        case 'H':suits[0]++; break;
        case 'D':suits[1]++; break;
        case 'C':suits[2]++; break;
        case 'S':suits[3]++; break;
        }
      }
    }
  for (i=0;i<15;i++) combinations[numbers[i]]++;
  straightCount=0;
  straightHigh=0;
  stFlushCount=0;
  stFlushHigh=0;
  for (i=2;i<11;i++) {
    j=i;
    strCount=0;
    wilds=wildCount;
    while (j>0 && j<15) {
      if (numbers[j]>0) { j++; strCount++; }
      else if (wilds>0) { j++; wilds--; strCount++; }
      else j=0;
      }
    if (strCount>=straightCount) {
      straightCount=strCount;
      straightHigh=i+strCount-1;
      }
    }
  if (numCards==5 && straightCount==5) {
    if (suits[0]+wildCount == 5 ||
        suits[1]+wildCount == 5 ||
        suits[2]+wildCount == 5 ||
        suits[3]+wildCount == 5) {
      stFlushCount=5;
      stFlushHigh=straightHigh;
      }
    }
  };

int Hand::bjValue() {
  int i;
  int v;
  int aces;
  int count;
  aces=0;
  count=0;
  for (i=0;i<numCards;i++) {
    v=cards[i]->value();
    if (v>10 && v<14) v=10;
    else if (v==14 || v==1) { v=11; aces++; }
    count+=v;
    }
  while (count>21 && aces>0) {
    count-=10;
    aces--;
    }
  if (aces>0) return -count;
  return count;
  };

int Hand::bjCmp(Hand* h) {
  int v1,v2;
  v1=abs(bjValue());
  v2=abs(h->bjValue());
  if (v1>v2) return 1;
  if (v1<v2) return -1;
  return 0;
  }

int Hand::baccValue() {
  int i;
  int v;
  int count;
  count=0;
  for (i=0;i<numCards;i++) {
    v=cards[i]->value();
    if (v>=10 && v<14) v=0;
    else if (v==14 || v==1) v=1;
    count+=v;
    }
  while (count>=10) count-=10;
  return count;
  };

int Hand::baccCmp(Hand* h) {
  int v1,v2;
  v1=abs(baccValue());
  v2=abs(h->baccValue());
  if (v1>v2) return 1;
  if (v1<v2) return -1;
  return 0;
  }

unsigned long Hand::pokerValue(int maxcards,int wild) {
/*  int i,j,k; */
  unsigned long value;
/*  unsigned long temp; */
/*  int           shift; */
/*  int           wilds;  */
/*  int           nums[15]; */
  value=0;
  sort(wild);
  if (combinations[2]+wildCount>0) value=PK_PAIR;
  if (combinations[2]+wildCount>1) value=PK_2_PAIR;
  if (combinations[2]>2 && maxcards>5) value=PK_3_PAIR;
  if ((combinations[3]>0) ||
      (combinations[2]>0 && wildCount>0) ||
      (wildCount>1)) value=PK_THREE;
  if (straightCount>4) value=PK_STRAIGHT;
  if (suits[0]+wildCount>4 ||
      suits[1]+wildCount>4 ||
      suits[2]+wildCount>4 ||
      suits[3]+wildCount>4) value=PK_FLUSH;
  if ((combinations[2]>0 && combinations[3]>0) ||
      (combinations[3]>0 && wildCount>0) ||
      (combinations[2]>1 && wildCount>0) ||
      (combinations[2]>0 && wildCount>1) ||
      (wildCount>2)) value=PK_FULLHOUSE;
  if (combinations[3]>1 && maxcards>5) value=PK_3_THREE;
  if ((combinations[4]>0) ||
      (combinations[3]>0 && wildCount>0) ||
      (combinations[2]>0 && wildCount>1) ||
      (wildCount>2)) value=PK_FOUR;
  if ((combinations[5]>0) ||
      (combinations[4]>0 && wildCount>0) ||
      (combinations[3]>0 && wildCount>1) ||
      (combinations[2]>0 && wildCount>2) ||
      (wildCount>3)) value=PK_FIVE;
  if (stFlushCount>4) value=PK_STFLUSH;
  if (stFlushCount>4 && stFlushHigh==14 && wildCount>0) value=PK_ROYALWLD;
  if (wildCount>3) value=PK_FOURWLD;
  if (wildCount>4) value=PK_FIVEWLD;
  if (stFlushCount>4 && stFlushHigh==14 && wildCount==0) value=PK_ROYAL;

  value=computeHandValue(value);
  return value;
  }

unsigned long Hand::paigowValue() {
/*  int i,j,k; */
  unsigned long value;
/*   unsigned long temp; */
/*  int           shift; */
/*  int           wilds;  */
/*  int           nums[15]; */
  value=0;
  sort(0);
  if (combinations[2]+wildCount>0) value=PK_PAIR;
  if (combinations[2]+wildCount>1) value=PK_2_PAIR;
  if ((combinations[3]>0) ||
      (combinations[2]>0 && wildCount>0) ||
      (wildCount>1)) value=PK_THREE;
  if (straightCount>4) value=PK_STRAIGHT;
  if (suits[0]+wildCount>4 ||
      suits[1]+wildCount>4 ||
      suits[2]+wildCount>4 ||
      suits[3]+wildCount>4) value=PK_FLUSH;
  if ((combinations[2]>0 && combinations[3]>0) ||
      (combinations[3]>0 && wildCount>0) ||
      (combinations[2]>1 && wildCount>0) ||
      (combinations[2]>0 && wildCount>1) ||
      (wildCount>2)) value=PK_FULLHOUSE;
  if ((combinations[4]>0) ||
      (combinations[3]>0 && wildCount>0) ||
      (combinations[2]>0 && wildCount>1) ||
      (wildCount>2)) value=PK_FOUR;
  if ((combinations[5]>0) ||
      (combinations[4]>0 && wildCount>0) ||
      (combinations[3]>0 && wildCount>1) ||
      (combinations[2]>0 && wildCount>2) ||
      (wildCount>3)) value=PK_FIVE;
  if (stFlushCount>4) value=PK_STFLUSH;
  if (stFlushCount>4 && stFlushHigh==14 && wildCount>0) value=PK_ROYALWLD;
  if (stFlushCount>4 && stFlushHigh==14 && wildCount==0) value=PK_ROYAL;

  value=computePaigowValue(value);
  return value;
  }

unsigned long Hand::computePaigowValue(unsigned long value) {
  return computeHandValue(value);
  }

unsigned long Hand::computeHandValue(unsigned long value) {
  int i,j,k;
  unsigned long temp;
  int           shift;
  int           wilds;
  int           nums[15];
  shift=24;
  wilds=wildCount;
  for (i=0;i<15;i++) nums[i]=numbers[i];
  if (value == PK_PAIR) {
    i=14;
    while (i>0 && nums[i]+wilds<2) i--;
    if (i>0) {
      temp=i;
      value |= (temp<<shift);
      shift-=4;
      value |= (temp<<shift);
      shift-=4;
      for (j=0;j<2;j++) {
        if (nums[i]>0) nums[i]--; else wilds--;
        }
      }
    }
  if (value == PK_2_PAIR) {
    i=14;
    for (k=0;k<2;k++) {
      while (i>0 && nums[i]+wilds<2) i--;
      if (i>0) {
        temp=i;
        value |= (temp<<shift);
        shift-=4;
        value |= (temp<<shift);
        shift-=4;
        for (j=0;j<2;j++) {
          if (nums[i]>0) nums[i]--; else wilds--;
          }
        }
      }
    }
  if (value == PK_3_PAIR) {
    i=14;
    for (k=0;k<3;k++) {
      while (i>0 && nums[i]+wilds<2) i--;
      if (i>0) {
        temp=i;
        value |= (temp<<shift);
        shift-=4;
        value |= (temp<<shift);
        shift-=4;
        for (j=0;j<2;j++) {
          if (nums[i]>0) nums[i]--; else wilds--;
          }
        }
      }
    }
  if (value == PK_THREE) {
    i=14;
    while (i>0 && nums[i]+wilds<3) i--;
    if (i>0) {
      temp=i;
      for (j=0;j<3;j++) {
        value |= (temp<<shift);
        shift-=4;
        if (nums[i]>0) nums[i]--; else wilds--;
        }
      }
    }
  if (value == PK_STRAIGHT) {
    i=straightHigh;
    while (i>straightHigh-straightCount) {
      temp=i;
      if (nums[i]+wilds>0) {
        value |= (temp<<shift);
        shift-=4;
        if (nums[i]>0) nums[i]--; else wilds--;
        }
      i--;
      }
    }
  if (value == PK_FLUSH) {
    if (suits[0]>4) k='H';
    else if (suits[1]>4) k='D';
    else if (suits[2]>4) k='C';
    else if (suits[3]>4) k='S';
    i=14;
    while (i>0) {
      if (nums[i]==0 && wilds>0) {
        temp=i;
        value |= (temp<<shift);
        shift-=4;
        wilds--;
        } else {
        j=numCards-1;
        while (j>=0) {
          if (cards[j]->getSuit() == k &&
              cards[j]->value() == i) {
            temp=i;
            value |= (temp<<shift);
            shift-=4;
            nums[i]--;
            j=-99;
            } else j--;
          }
        if (j==-1 && wilds>0) {
          temp=i;
          value |= (temp<<shift);
          shift-=4;
          wilds--;
          }
        }
      i--;
      }
    }
  if (value == PK_FULLHOUSE) {
    i=14;
    while (i>0 && nums[i]+wilds<3) i--;
    if (i>0) {
      temp=i;
      for (j=0;j<3;j++) {
        value |= (temp<<shift);
        shift-=4;
        if (nums[i]>0) nums[i]--; else wilds--;
        }
      }
    i=14;
    while (i>0 && nums[i]+wilds<2) i--;
    if (i>0) {
      temp=i;
      for (j=0;j<2;j++) {
        value |= (temp<<shift);
        shift-=4;
        if (nums[i]>0) nums[i]--; else wilds--;
        }
      }
    }
  if (value == PK_3_THREE) {
    i=14;
    for (k=0;k<2;k++) {
      while (i>0 && nums[i]+wilds<3) i--;
      if (i>0) {
        temp=i;
        for (j=0;j<3;j++) {
          value |= (temp<<shift);
          shift-=4;
          if (nums[i]>0) nums[i]--; else wilds--;
          }
        }
      }
    }
  if (value == PK_FOUR) {
    i=14;
    while (i>0 && nums[i]+wilds<4) i--;
    if (i>0) {
      temp=i;
      for (j=0;j<4;j++) {
        value |= (temp<<shift);
        shift-=4;
        if (nums[i]>0) nums[i]--; else wilds--;
        }
      }
    }
  if (value == PK_FIVE) {
    i=14;
    while (i>0 && nums[i]+wilds<5) i--;
    if (i>0) {
      temp=i;
      for (j=0;j<5;j++) {
        value |= (temp<<shift);
        shift-=4;
        if (nums[i]>0) nums[i]--; else wilds--;
        }
      }
    }
  if (value == PK_STFLUSH ||
      value == PK_ROYALWLD ||
      value == PK_ROYAL) {
    if (suits[0]>4) k='H';
    else if (suits[1]>4) k='D';
    else if (suits[2]>4) k='C';
    else if (suits[3]>4) k='S';
    i=stFlushHigh;
    while (i>stFlushHigh-stFlushCount) {
      if (nums[i]==0 && wilds>0) {
        temp=i;
        value |= (temp<<shift);
        shift-=4;
        wilds--;
        } else {
        j=numCards-1;
        while (j>=0) {
          if (cards[j]->getSuit() == k &&
              cards[j]->value() == i) {
            temp=i;
            value |= (temp<<shift);
            shift-=4;
            nums[i]--;
            j=-99;
            } else j--;
          }
        if (j==-1 && wilds>0) {
          temp=i;
          value |= (temp<<shift);
          shift-=4;
          wilds--;
          }
        }
      i--;
      }
    }

  while (shift >= 0) {
    i=14;
    while (i>0 && nums[i]==0) i--;
    if (i>0) {
      temp=i;
      value |= (temp<<shift);
      shift-=4;
      nums[i]--;
      } else shift-=4;
    }
  return value;
  }


int Hand::threePokerValue(int wild) {
/*  int i,j; */
  int value;
/*  int count; */
/*  int hiCount; */
/*  int last; */
/*  int wildCount; */
/*  int flushCount; */
/*  int suits[4]; */
  value=0;
  sort(wild);
  if (cards[0]->value()==cards[1]->value() ||
      cards[0]->value()==cards[2]->value() ||
      cards[1]->value()==cards[2]->value()) value=1;
  if (cards[0]->getSuit()==cards[1]->getSuit() && cards[1]->getSuit()==cards[2]->getSuit()) value=2;
  if (cards[0]->value()==cards[1]->value()-1 && cards[1]->value()==cards[2]->value()-1)
     value=3;
  if (cards[0]->value()==cards[1]->value() && cards[1]->value()==cards[2]->value()) value=4;
  if (cards[0]->getSuit()==cards[1]->getSuit() && cards[1]->getSuit()==cards[2]->getSuit() &&
      cards[0]->value()==cards[1]->value()-1 && cards[1]->value()==cards[2]->value()-1)
     value=5;
  return value;
  }

int Hand::threePokerCmp(Hand* h) {
  int pv,dv;
  int ph,pl,dh,dl;
  pv=threePokerValue(0);
  dv=h->threePokerValue(0);
  
  if (dv == 0 && h->cards[2]->value()<12) return 1;
  if (pv>dv) return 2;
  if (pv<dv) return -1;
  if (pv>2) {
    if (cards[2]->value()>h->cards[2]->value()) return 2;
    if (cards[2]->value()==h->cards[2]->value()) return 0;
    return -1;
    }
  if (pv==1) {
    if (cards[0]->value()==cards[1]->value()) {
      ph=cards[0]->value(); pl=cards[2]->value();
      } else if (cards[0]->value()==cards[2]->value()) {
      ph=cards[0]->value(); pl=cards[1]->value();
      } else {
      ph=cards[1]->value(); pl=cards[0]->value();
      }
    if (h->cards[0]->value()==h->cards[1]->value()) {
      dh=h->cards[0]->value(); dl=h->cards[2]->value();
      } else if (h->cards[0]->value()==h->cards[2]->value()) {
      dh=h->cards[0]->value(); dl=h->cards[1]->value();
      } else {
      dh=h->cards[1]->value(); dl=h->cards[0]->value();
      }
    if (ph>dh) return 2;
    if (ph<dh) return -1;
    if (pl>dl) return 2;
    if (pl<dl) return -1;
    return 0;
    }
  if (cards[2]->value()>h->cards[2]->value()) return 2;
  if (cards[2]->value()<h->cards[2]->value()) return -1;
  if (cards[1]->value()>h->cards[1]->value()) return 2;
  if (cards[1]->value()<h->cards[1]->value()) return -1;
  if (cards[0]->value()>h->cards[0]->value()) return 2;
  if (cards[0]->value()<h->cards[0]->value()) return -1;
  return 0;
  }

Hand* Hand::paigowSplit(int c1,int c2) {
  Hand* ret;
  int  c[2];
  int  count;
  int  i,j;
  int  p1,p2;
  int  split;
  int  numBack[15];
  int  check2;
  ret=new Hand();
  sort(0);
  count=0;
  char suit;

  if (c1==-1 || c2==-1) {

  if (straightCount>4 || suits[0]>4 || suits[1]>4 || suits[2]>4 ||
             suits[3]>4) check2=1; else check2=0;
  
  for (i=0;i<15;i++) if (numbers[i]==2) p1=i;
  for (i=0;i<15;i++) if (numbers[i]==2 && i!=p1) p2=i;

  if (p1>p2) { i=p1; p1=p2; p2=i; }
  /* check for 5 aces */
    if (numbers[14]==4 && wildCount>0) {
      if (numbers[13] == 2) {
        for (i=0;i<7;i++) if (cards[i]->value()==13 && count<2) c[count++]=i;
        } else {
        for (i=0;i<7;i++) if (cards[i]->value()==14 && count<2) c[count++]=i;
        }
      }
  
  /* Check for four of a kind */
    else if (combinations[4]==1) {
      p2=0;
      for (i=0;i<15;i++) if (numbers[i]==4) p1=i;
      for (i=0;i<15;i++) if (numbers[i]==3 || numbers[i]==2) p2=i;
      split=1;
      if (p1<7) split=0;
      if (p1>6 && p1<11) {
        if (numbers[14]>0 || combinations[2]>0 || combinations[3]>0 ||
            wildCount>0) split=0;
        }
      if (p1>10 && p1<14 && p2>9) split=0;
      if (p1==14 && p2>6) split=0;
      j=numCards-1; count=0;
      if (split==1) {
        while (j>=0 && count<2) {
          if (numbers[cards[j]->value()]==4) c[count++]=j;
          j--;
          }
        } else {
        if (p2>0) {
          while (j>=0 && count<2) {
            if (cards[j]->value()==p2) c[count++]=j;
            j--;
            }
          } else {
          while (j>=0 && count<2) {
            if (numbers[cards[j]->value()]!=4) c[count++]=j;
            j--;
            }
          }
        }
      }

  /* check for 2 pair over straights or flushes */
    else if (check2==1 && combinations[2]>1 &&
       ((numbers[14]==1 || wildCount==1) ||
             (p1>=11 && p2>=6) ||
             (p1==14))) {
  printf("-->");
      split=0;
      for (i=0;i<15;i++) if (numbers[i]==2) p1=i;
      for (i=0;i<15;i++) if (numbers[i]==2 && i!=p1) p2=i;
      if (p1>p2) { i=p1; p1=p2; p2=i; }
      if (numbers[14]==2) split=1;
      else if (p2>=11 && p1>=6 && numbers[14]==1) split=1;
      else if ((p1>=7 || p2>=7) && numbers[14]==0) split=1;
      count=0;
      j=numCards-1;
      if (split==0) {
        while (j>=0 && count<2) {
          if (numbers[cards[j]->value()]!=2) { c[count++]=j; }
          j--;
          }
        } else {
        while (j>=0 && count<2) {
          if (cards[j]->value()==p1) { c[count++]=j; }
          j--;
          }
        }
    }


  /* Check for flushes*/
    else if (suits[0]>4 || suits[1]>4 || suits[2]>4 || suits[3]>4) {
      for (i=0;i<4;i++) if (suits[i]>4) p1=i;
      p2=suits[p1];
      switch (p1) {
        case 0:suit='H'; break;
        case 1:suit='D'; break;
        case 2:suit='C'; break;
        case 3:suit='S'; break;
        }
      j=numCards-1; count=0;
      if (p2>5 && combinations[2]>0) {
        while (j>=0 && numbers[(int)(cards[j]->getValue())]<2) j--;
        p1=cards[j]->getValue();
        j=numCards-1; count=0;
        while (j>=0 && count<2) {
          if (cards[j]->value()==p1) c[count++]=j;
          j--;
          }
        }
      j=numCards-1;
      while (j>=0 && count<2) {
        if (p2>5 || cards[j]->getSuit()!=suit) {
          c[count++]=j;
          if (cards[j]->getSuit()==suit) p2--;
          }
        j--;
        }
      }

  /* Check for straights*/
    else if (straightCount>4) {
      j=numCards-1; count=0;
      if (straightCount==7) {
        c[count++]=j--;
        c[count++]=j--;
        }
      for (i=0;i<15;i++) numBack[i]=numbers[i];
      if (straightCount==6) {
        if (numbers[straightHigh-straightCount+1]>1) {
          while (j>=0 && count<2) {
            if (cards[j]->value()==straightHigh-straightCount+1) c[count++]=j;
            j--;
            }
          }
        else if (numbers[straightHigh]>1) {
          while (j>=0 && count<2) {
            if (cards[j]->value()==straightHigh) c[count++]=j;
            j--;
            }
          } else {
          while (j>=0 && count<2) {
            if (cards[j]->value()>=straightHigh) c[count++]=j;
            else if (cards[j]->value()<=straightHigh-straightCount) c[count++]=j;
            else if (numBack[cards[j]->value()]>1) {
              c[count++]=j;
              numBack[cards[j]->value()]--;
              }
            j--;
            }
          }
        }
      j=numCards-1;
      while (j>=0 && count<2) {
        if (cards[j]->value()>straightHigh) c[count++]=j;
        else if (cards[j]->value()<=straightHigh-straightCount) c[count++]=j;
        else if (numBack[cards[j]->value()]>1) {
          c[count++]=j;
          numBack[cards[j]->value()]--;
          }
        j--;
        }
      }
  
  
  
  /* Check for two trios */
    else if (combinations[3]==2) {
      j=numCards-1; count=0;
      while (j>=0 && count<2) {
        if (numbers[cards[j]->value()]==3) c[count++]=j;
        j--;
        }
      }
  
  /* Check for full house with 2 pairs*/
    else if (combinations[3]==1 && combinations[2]==2) {
      split=1;
      for (i=0;i<15;i++) if (numbers[i]==2) p1=i;
      count=0;
      j=numCards-1;
      while (j>=0 && count<2) {
        if (cards[j]->value()==p1) { c[count++]=j; }
        j--;
        }
      }
  
  /* Check for full house */
    else if (combinations[3]==1 && combinations[2]==1) {
      split=1;
      for (i=0;i<15;i++) if (numbers[i]==2) p1=i;
      if (numbers[2]==2 && numbers[13]==1 && numbers[14]==1) split=0;
      count=0;
      j=numCards-1;
      if (split==0) {
        while (j>=0 && count<2) {
          if (numbers[cards[j]->value()]<2) { c[count++]=j; }
          j--;
          }
        } else {
        while (j>=0 && count<2) {
          if (cards[j]->value()==p1) { c[count++]=j; }
          j--;
          }
        }
      }
  
  /* Check for 3 of a kind */
    else if (combinations[3]==1) {
      j=numCards-1; count=0;
      if (numbers[14]==3) {
        c[count++]=j;
        }
      while (j>=0 && count<2) {
        if (numbers[cards[j]->value()]!=3) { c[count++]=j; }
        j--;
        }
      }
  
  /* Check for three pair */
    else if (combinations[2]==3) {
      j=numCards-1; count=0;
      while (j>=0 && count<2) {
        if (numbers[cards[j]->value()]==2) c[count++]=j;
        j--;
        }
      }
  
  /* Check for two pair */
    else if (combinations[2]==2) {
      split=0;
      for (i=0;i<15;i++) if (numbers[i]==2) p1=i;
      for (i=0;i<15;i++) if (numbers[i]==2 && i!=p1) p2=i;
      if (p1>p2) { i=p1; p1=p2; p2=i; }
      if (numbers[14]==2) split=1;
      else if (p2>=11 && p1>=6 && numbers[14]==1) split=1;
      else if ((p1>=7 || p2>=7) && numbers[14]==0) split=1;
      count=0;
      j=numCards-1;
      if (split==0) {
        while (j>=0 && count<2) {
          if (numbers[cards[j]->value()]!=2) { c[count++]=j; }
          j--;
          }
        } else {
        while (j>=0 && count<2) {
          if (cards[j]->value()==p1) { c[count++]=j; }
          j--;
          }
        }
      }
  
  /* Check for single pair */
    else if (combinations[2]==1) {
      j=numCards-1; count=0;
      while (j>=0 && count<2) {
        if (numbers[cards[j]->value()]!=2) { c[count++]=j; }
        j--;
        }
      }
  
    else {
      c[0]=5; c[1]=4;
      }
    } else {
    c[0]=c1; c[1]=c2;
    }
  ret->cards[0]=cards[c[0]];
  ret->cards[1]=cards[c[1]];
  if (c[0]>c[1]) { i=c[0]; c[0]=c[1]; c[1]=i; }  
  for (i=c[1];i<6;i++) cards[i]=cards[i+1];
  for (i=c[0];i<6;i++) cards[i]=cards[i+1];
  numCards=5;
  ret->numCards=2;
  return ret;
  }

void Hand::paint(rcs_Display* display,rcs_Window win,rcs_GC gc) {
  int i;
  for (i=0;i<numCards;i++) {
    cards[i]->paint(display,win,gc);
    }
  }


void Hand::paint(rcs_Display* display,rcs_Window win,rcs_GC gc,int hidden) {
  int i;
  for (i=0;i<numCards;i++) {
    if (hidden-->0) cards[i]->setSide('B');
      else cards[i]->setSide('F');
    cards[i]->paint(display,win,gc);
    }
  }

void Hand::display(int Hidden)
{
  int i;
  char buffer[80];
  for (i=0;i<numCards;i++) {
    if (Hidden>0) { Output("## "); Hidden--; }
      else {
        switch(cards[i]->getValue()) {
          case '*':Output("*"); break;
          case '2':Output("2"); break;
          case '3':Output("3"); break;
          case '4':Output("4"); break;
          case '5':Output("5"); break;
          case '6':Output("6"); break;
          case '7':Output("7"); break;
          case '8':Output("8"); break;
          case '9':Output("9"); break;
          case '0':Output("10"); break;
          case 'J':Output("J"); break;
          case 'Q':Output("Q"); break;
          case 'K':Output("K"); break;
          case 'A':Output("A"); break;
          }
        buffer[1]=' '; buffer[0]=cards[i]->getSuit();
        buffer[2]='\0';
        Output(buffer);
        }
    }
}

int Hand::pokerCmp(Hand* dHand,int wild) {
  unsigned long pValue;
  unsigned long dValue;
  pValue=pokerValue(5,wild);
  dValue=dHand->pokerValue(5,wild);
  if (pValue>dValue) return 1;
  if (pValue<dValue) return -1;
  return 0;
  }

int Hand::cribbageValue() {
  int ret;
  int i,j,k,l;
  int count;
  int mult;
  int counts[15];
  int values[5];
  ret=0;
/* check for nobs and heels */
  if (numCards == 5) {
    if (cards[4]->value() == 11) ret+=2;
    for (i=0;i<4;i++)
      if (cards[i]->value()==11 && cards[i]->getSuit()==cards[4]->getSuit()) {
        ret+=1;
        }
    }
/* check flushes */
  if (numCards > 3) {
    if (cards[0]->getSuit() == cards[1]->getSuit() &&
        cards[0]->getSuit() == cards[2]->getSuit() &&
        cards[0]->getSuit() == cards[3]->getSuit()) {
      ret+=4;
      if (numCards==5 && cards[0]->getSuit() == cards[4]->getSuit()) ret++;
      }
    }
/* check for pairs */
  for (i=0;i<numCards;i++)
    for (j=i+1;j<numCards;j++)
      if (cards[i]->value()==cards[j]->value()) ret+=2;
/* get values of cards */
  for (i=0;i<numCards;i++) {
    values[i]=cards[i]->value();
    if (values[i]==14) values[i]=1;
    if (values[i]>10) values[i]=10;
    }
/* check for 2 card 15s */
  for (i=0;i<numCards;i++)
    for (j=i+1;j<numCards;j++)
      if (values[i]+values[j]==15) ret+=2;
/* check for 3 card 15s */
  for (i=0;i<numCards;i++)
    for (j=i+1;j<numCards;j++)
      for (k=j+1;k<numCards;k++)
        if (values[i]+values[j]+values[k]==15) ret+=2;
/* check for 4 card 15s */
  for (i=0;i<numCards;i++)
    for (j=i+1;j<numCards;j++)
      for (k=j+1;k<numCards;k++)
        for (l=k+1;l<numCards;l++)
          if (values[i]+values[j]+values[k]+values[l]==15) ret+=2;
/* check for 5 card 15s */
  if (numCards==5 && values[0]+values[1]+values[2]+values[3]+values[4]==15)
    ret+=2;
/* prepare to check for straights */
  for (i=0;i<15;i++) counts[i]=0;
  for (i=0;i<numCards;i++) {
    counts[cards[i]->value()]++;
    }
/* check for straights */
  i=0;
  while (i<15) {
    count=0;
    mult=1;
    while (i+count<15 && counts[i+count]>0) {
      mult *= counts[i+count];
      count++;
      } 
    if (count>2) {
      ret += (count*mult);
      if (count>3) i+=(count-3);
      }
    i++;
    }
  return ret;
  }

void Hand::deleteHand(Hand* h) {
  delete(h);
  }

