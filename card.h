#ifndef _CARD_H
#define _CARD_H

#ifndef _BYTE
#define _BYTE
typedef unsigned char byte;
#endif

class Card {
  protected:
    byte val;
    char suit;
  public:
    Card(byte v,char s);
    char getValue();
    char getSuit();
    byte value();
};

#endif

