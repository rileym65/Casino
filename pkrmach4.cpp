#include "header.h"

void PKRMACHJW::Play()
{
  char *Bptr;
  int Bet;
  int i;
  int high,hv;
  int Keep[5];
  int Top;
  float Amount;
  CARD Card;
  HAND Hand;
  Add_Jokers(1);
  ClrScr();
  sprintf(Buffer,"Royal Flush (no wilds) $ %6d %6d %6d %6d %6d\n",250*(int)MinBet,
    250*(int)MinBet*2,250*(int)MinBet*3,250*(int)MinBet*4,800*(int)MinBet*5);
  Output(Buffer);
  sprintf(Buffer,"5 of a Kind            $ %6d %6d %6d %6d %6d\n",200*(int)MinBet,
    200*(int)MinBet*2,200*(int)MinBet*3,200*(int)MinBet*4,200*(int)MinBet*5);
  Output(Buffer);
  sprintf(Buffer,"Royal with wilds       $ %6d %6d %6d %6d %6d\n",100*(int)MinBet,
    100*(int)MinBet*2,100*(int)MinBet*3,100*(int)MinBet*4,100*(int)MinBet*5);
  Output(Buffer);
  sprintf(Buffer,"Straight Flush         $ %6d %6d %6d %6d %6d\n",50*(int)MinBet,
    50*(int)MinBet*2,50*(int)MinBet*3,50*(int)MinBet*4,50*(int)MinBet*5);
  Output(Buffer);
  sprintf(Buffer,"4 of a Kind            $ %6d %6d %6d %6d %6d\n",20*(int)MinBet,
    20*(int)MinBet*2,20*(int)MinBet*3,20*(int)MinBet*4,20*(int)MinBet*5);
  Output(Buffer);
  sprintf(Buffer,"Full House             $ %6d %6d %6d %6d %6d\n",7*(int)MinBet,
    7*(int)MinBet*2,7*(int)MinBet*3,7*(int)MinBet*4,7*(int)MinBet*5);
  Output(Buffer);
  sprintf(Buffer,"Flush                  $ %6d %6d %6d %6d %6d\n",5*(int)MinBet,
    5*(int)MinBet*2,5*(int)MinBet*3,5*(int)MinBet*4,5*(int)MinBet*5);
  Output(Buffer);
  sprintf(Buffer,"Straight               $ %6d %6d %6d %6d %6d\n",3*(int)MinBet,
    3*(int)MinBet*2,3*(int)MinBet*3,3*(int)MinBet*4,3*(int)MinBet*5);
  Output(Buffer);
  sprintf(Buffer,"3 of a Kind            $ %6d %6d %6d %6d %6d\n",2*(int)MinBet,
    2*(int)MinBet*2,2*(int)MinBet*3,2*(int)MinBet*4,2*(int)MinBet*5);
  Output(Buffer);
  sprintf(Buffer,"2 Pair                 $ %6d %6d %6d %6d %6d\n",1*(int)MinBet,
    1*(int)MinBet*2,1*(int)MinBet*3,1*(int)MinBet*4,1*(int)MinBet*5);
  Output(Buffer);
  sprintf(Buffer,"Pair (Kings)           $ %6d %6d %6d %6d %6d\n",1*(int)MinBet,
    1*(int)MinBet*2,1*(int)MinBet*3,1*(int)MinBet*4,1*(int)MinBet*5);
  Output(Buffer);
  Bet=1;
  while (Bet!=0) {
    GotoXY(1,22);
    Shuffle();
    GotoXY(1,18);
    Players[0]->Clear_All_Bets();
    sprintf(Buffer,"Money $%12.2f",Players[0]->Money());
    Output(Buffer);
    GotoXY(1,19); Output("Bet ?");
    Input(Buffer);
    sscanf(Buffer,"%d",&Bet);
    if (Bet!=0) {
      if (Bet>5) Bet=5;
      if (Bet==5) Top=800; else Top=250;
      Bet=Bet*(int)MinBet;
      Amount=Players[0]->Place_Bet(Bet,0,1,1);
      if (Amount) ;
      GotoXY(1,19); Output("                 ");
      GotoXY(1,13); Output("                                   ");
      GotoXY(1,15); Output("                 ");
      GotoXY(1,18);
      sprintf(Buffer,"Money $%12.2f",Players[0]->Money());
      Output(Buffer);
      Hand.NumCards=0;
      GotoXY(1,15); printf("### ### ### ### ###");
      GotoXY(1,16); printf(" 1   2   3   4   5 ");
      GotoXY(1,15);
      for (i=0;i<5;i++) {
        GotoXY(1+(i*4),15);
        Card=Deal_Card();
        Hand.Cards[Hand.NumCards++]=Card;
        switch(Hand.Cards[i].Value) {
          case 0:Output("*J*"); break;
          case 1:Output(" A"); break;
          case 2:Output(" 2"); break;
          case 3:Output(" 3"); break;
          case 4:Output(" 4"); break;
          case 5:Output(" 5"); break;
          case 6:Output(" 6"); break;
          case 7:Output(" 7"); break;
          case 8:Output(" 8"); break;
          case 9:Output(" 9"); break;
          case 10:Output("10"); break;
          case 11:Output(" J"); break;
          case 12:Output(" Q"); break;
          case 13:Output(" K"); break;
          }
        Buffer[1]=' '; Buffer[0]=Hand.Cards[i].Suit;
        Buffer[2]='\0';
        if (Hand.Cards[i].Value != 0) Output(Buffer);
        Delay(1);
        }
      GotoXY(1,19); Output("Holds ?");
      Input(Buffer);
      Bptr=Buffer;
      GotoXY(1,19); Output("                 ");
      for (i=0;i<5;i++) Keep[i]=0;
      while (*Bptr!='\0') {
        switch (*Bptr) {
          case '1':Keep[0]=1; break;
          case '2':Keep[1]=1; break;
          case '3':Keep[2]=1; break;
          case '4':Keep[3]=1; break;
          case '5':Keep[4]=1; break;
          }
        Bptr++;
        }
      for (i=0;i<5;i++) if (Keep[i]==0) {
        Hand.Cards[i]=Deal_Card();
        GotoXY(1+i*4,15); printf("###");
        }
      Delay(1);
      for (i=0;i<5;i++) if (Keep[i]==0) {
        GotoXY(1+(i*4),15);
        switch(Hand.Cards[i].Value) {
          case 0:Output("*J*"); break;
          case 1:Output(" A"); break;
          case 2:Output(" 2"); break;
          case 3:Output(" 3"); break;
          case 4:Output(" 4"); break;
          case 5:Output(" 5"); break;
          case 6:Output(" 6"); break;
          case 7:Output(" 7"); break;
          case 8:Output(" 8"); break;
          case 9:Output(" 9"); break;
          case 10:Output("10"); break;
          case 11:Output(" J"); break;
          case 12:Output(" Q"); break;
          case 13:Output(" K"); break;
          }
        Buffer[1]=' '; Buffer[0]=Hand.Cards[i].Suit;
        Buffer[2]='\0';
        if (Hand.Cards[i].Value != 0) Output(Buffer);
        Delay(1);
        }
      high=Check_Hand_Wild(Hand,&hv,0);
      GotoXY(1,13);
      if (high==PK_PAIR && hv>12) {
        sprintf(Buffer,"Pair $%d",Bet*1);
        Output(Buffer);
        Players[0]->Win_Hand_Bets(0,1);
        }
      else if (high==PK_2_PAIR) {
        sprintf(Buffer,"2 Pair $%d",Bet*1);
        Output(Buffer);
        Players[0]->Win_Hand_Bets(0,1);
        }
      else if (high==PK_THREE) {
        sprintf(Buffer,"3 of a kind $%d",Bet*2);
        Output(Buffer);
        Players[0]->Win_Hand_Bets(0,2);
        }
      else if (high==PK_STRAIGHT) {
        sprintf(Buffer,"Straight $%d",Bet*3);
        Output(Buffer);
        Players[0]->Win_Hand_Bets(0,3);
        }
      else if (high==PK_FLUSH) {
        sprintf(Buffer,"Flush $%d",Bet*5);
        Output(Buffer);
        Players[0]->Win_Hand_Bets(0,5);
        }
      else if (high==PK_FULLHOUSE) {
        sprintf(Buffer,"Full House $%d",Bet*7);
        Output(Buffer);
        Players[0]->Win_Hand_Bets(0,7);
        }
      else if (high==PK_FOUR) {
        sprintf(Buffer,"4 of a kind $%d",Bet*20);
        Output(Buffer);
        Players[0]->Win_Hand_Bets(0,20);
        }
      else if (high==PK_STFLUSH) {
        sprintf(Buffer,"Straight Flush $%d",Bet*50);
        Output(Buffer);
        Players[0]->Win_Hand_Bets(0,50);
        }
      else if (high==PK_FIVE) {
        sprintf(Buffer,"5 of a kind $%d",Bet*200);
        Output(Buffer);
        Players[0]->Win_Hand_Bets(0,200);
        }
      else if (high==PK_ROYALWLD) {
        sprintf(Buffer,"Royal Flush (with wilds) $%d",Bet*100);
        Output(Buffer);
        Players[0]->Win_Hand_Bets(0,100);
        }
      else if (high==PK_ROYAL) {
        sprintf(Buffer,"Royal Flush (no wilds) $%d",Bet*Top);
        Output(Buffer);
        Players[0]->Win_Hand_Bets(0,Top);
        }
      else {
        Output("Game Over");
        }
      Players[0]->Lose_Hand_Bets(0);
      }
    }
}

