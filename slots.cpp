#include "header.h"

#define WHEEL_X 12
#define WHEEL_Y 12
#define PLAYER_X 12
#define PLAYER_Y 15

void SLOTS::New(int numwheels,int minbet,int maxbet,int paylines)
{
  int i,j;
  NumWheels=numwheels;
  MinBet=minbet;
  MaxBet=maxbet;
  PayLines=paylines;
  TestMode=0;
  NumPayoffs=0;
  NumOdds=0;
  PaidIn=0;
  PaidOut=0;
  for (i=0;i<4;i++)
    for (j=0;j<24;j++) strcpy(Wheels[i][j],"    ");
  for (i=0;i<15;i++) strcpy(Specials[i],"!@#$");
  for (i=0;i<15;i++) Actions[i]=0;
  for (i=0;i<24;i++) strcpy(OddsSymbol[i],"    ");
  for (i=0;i<24;i++) Odds[i]=0;
  for (i=0;i<4;i++)
    for (j=0;j<24;j++) strcpy(PaySymbol[i][j],"!@#$");
  for (i=0;i<24;i++) Pay[i]=0;
  for (i=0;i<24;i++) Hit[i]=0;
  for (i=0;i<4;i++); WheelPos[i]=Random(23);
}

void SLOTS::Add_Wheel(WHEEL wheel,int wheelnum)
{
  int i;
  for (i=0;i<24;i++) strcpy(Wheels[wheelnum][i],wheel.Entry[i]);
}

int SLOTS::Check_Symbol(char* Buf1,char* Buf2)
{
  int r;
  r=0;
  if (strcmp(Buf2,"ANYN")==0) r=1;
  else if (strcmp(Buf1," X2 ")==0) { r=1; Mult*=2; }
  else if (strcmp(Buf1," X3 ")==0) { r=1; Mult*=3; }
  else if (strcmp(Buf1,"WILD")==0) r=1;
  else if (strcmp(Buf2,"BLNK")==0 && strcmp(Buf1,"    ")==0) r=1;
  else if (strcmp(Buf2,"ANY ")==0 && strcmp(Buf1,"    ")!=0) r=1;
  else if (strcmp(Buf1,"-vv-")==0 && strcmp(Buf2,"----")==0) r=1;
  else if (strcmp(Buf1,"=vv=")==0 && strcmp(Buf2,"====")==0) r=1;
  else if (strcmp(Buf1,"-^^-")==0 && strcmp(Buf2,"----")==0) r=1;
  else if (strcmp(Buf1,"=^^=")==0 && strcmp(Buf2,"====")==0) r=1;
  else if (strcmp(Buf1,Buf2)==0) r=1;
  return r;
}

void SLOTS::Display_Wheels()
{
  int p1,p2,p3,p4;
  p1=WheelPos[0]-1; if (p1<0) p1=23;
  p2=WheelPos[1]-1; if (p2<0) p2=23;
  p3=WheelPos[2]-1; if (p3<0) p3=23;
  p4=WheelPos[3]-1; if (p4<0) p4=23;
  GotoXY(WHEEL_X,WHEEL_Y);
  if (NumWheels==3)
    sprintf(Buffer,"%4s %4s %4s",Wheels[0][p1],Wheels[1][p2],
      Wheels[2][p3]);
   else
    sprintf(Buffer,"%4s %4s %4s %4s",Wheels[0][p1],Wheels[1][p2],
      Wheels[2][p3],Wheels[2][p4]);
  Output(Buffer);
  p1=WheelPos[0];
  p2=WheelPos[1];
  p3=WheelPos[2];
  p4=WheelPos[3];
  GotoXY(WHEEL_X,WHEEL_Y+1);
  if (NumWheels==3)
    sprintf(Buffer,"%4s %4s %4s",Wheels[0][p1],Wheels[1][p2],
      Wheels[2][p3]);
   else
    sprintf(Buffer,"%4s %4s %4s %4s",Wheels[0][p1],Wheels[1][p2],
      Wheels[2][p3],Wheels[2][p4]);
  Output(Buffer);
  p1=WheelPos[0]+1; if (p1>23) p1=0;
  p2=WheelPos[1]+1; if (p2>23) p2=0;
  p3=WheelPos[2]+1; if (p3>23) p3=0;
  p4=WheelPos[3]+1; if (p4>23) p4=0;
  GotoXY(WHEEL_X,WHEEL_Y+2);
  if (NumWheels==3)
    sprintf(Buffer,"%4s %4s %4s",Wheels[0][p1],Wheels[1][p2],
      Wheels[2][p3]);
   else
    sprintf(Buffer,"%4s %4s %4s %4s",Wheels[0][p1],Wheels[1][p2],
      Wheels[2][p3],Wheels[2][p4]);
  Output(Buffer);
  Output("\n");
}

void SLOTS::Display_Machine(int credits)
{
  int i,j;
  if (credits) ;
  for (i=NumPayoffs-1;i>=0;i--) {
    GotoXY((NumPayoffs-i)/9*30+1,(NumPayoffs-i)%9+2);
    sprintf(Buffer,"%s %s %s %s %5d ",PaySymbol[0][i],PaySymbol[1][i],
      PaySymbol[2][i],PaySymbol[3][i],Pay[i]);
    Output(Buffer);
    for (j=2;j<=MaxBet;j++) {
      sprintf(Buffer,"%5d ",Pay[i]*j);
      Output(Buffer);
      }
    Output("\n");
    }
}

int SLOTS::Check_Odds(char* buffer)
{
  int i;
  int r;
  r=-1;
  for (i=0;i<NumOdds;i++) if (strcmp(buffer,OddsSymbol[i])==0) r=i;
  if (r!=-1) {
    if (Random(100)<Odds[r]) r=1; else r=0;
    }
  else r=0;
  return r;
}

int SLOTS::Get_MaxBet()
{
  return MaxBet;
}

int SLOTS::Spin(int Coins)
{
  int i,j;
  int Count;
  int m;
  int Ret;
  int RMult;
  int p[4];
  GotoXY(WHEEL_X-5,WHEEL_Y+1); Output("--->\n");
  GotoXY(WHEEL_X+NumWheels*5,WHEEL_Y+1); Output("<---\n");
  if (PayLines>1 && Coins>1) {
    GotoXY(WHEEL_X-5,WHEEL_Y); Output("--->\n");
    GotoXY(WHEEL_X+NumWheels*5,WHEEL_Y); Output("<---\n");
    }
  else {
    GotoXY(WHEEL_X-5,WHEEL_Y); Output("    \n");
    GotoXY(WHEEL_X+NumWheels*5,WHEEL_Y); Output("    \n");
    }
  if (PayLines>1 && Coins>2) {
    GotoXY(WHEEL_X-5,WHEEL_Y+2); Output("--->\n");
    GotoXY(WHEEL_X+NumWheels*5,WHEEL_Y+2); Output("<---\n");
    }
  else {
    GotoXY(WHEEL_X-5,WHEEL_Y+2); Output("    \n");
    GotoXY(WHEEL_X+NumWheels*5,WHEEL_Y+2); Output("    \n");
    }
  if (PayLines>3 && Coins>3) {
    GotoXY(WHEEL_X-5,WHEEL_Y-1); Output("---\\\n");
    }
  else {
    GotoXY(WHEEL_X-5,WHEEL_Y-1); Output("    \n");
    }
  if (PayLines>3 && Coins>4) {
    GotoXY(WHEEL_X-5,WHEEL_Y+3); Output("---/\n");
    }
  else {
    GotoXY(WHEEL_X-5,WHEEL_Y+3); Output("    \n");
    }
  Ret=0;
  PaidIn+=Coins;
  Count=100+Random(200);
  while (Count-->0) {
    WheelPos[0]++; if (WheelPos[0]>23) WheelPos[0]=0;
    WheelPos[1]++; if (WheelPos[1]>23) WheelPos[1]=0;
    WheelPos[2]++; if (WheelPos[2]>23) WheelPos[2]=0;
    WheelPos[3]++; if (WheelPos[3]>23) WheelPos[3]=0;
    if (TestMode==0) Display_Wheels();
    if (Count==0 && Check_Odds(Wheels[0][WheelPos[0]])==1) Count++;
    }
  Count=10+Random(200);
  while (Count-->0) {
    WheelPos[1]++; if (WheelPos[1]>23) WheelPos[1]=0;
    WheelPos[2]++; if (WheelPos[2]>23) WheelPos[2]=0;
    WheelPos[3]++; if (WheelPos[3]>23) WheelPos[3]=0;
    if (TestMode==0) Display_Wheels();
    if (Count==0 && Check_Odds(Wheels[1][WheelPos[1]])==1) Count++;
    }
  Count=10+Random(200);
  while (Count-->0) {
    WheelPos[2]++; if (WheelPos[2]>23) WheelPos[2]=0;
    WheelPos[3]++; if (WheelPos[3]>23) WheelPos[3]=0;
    if (TestMode==0) Display_Wheels();
    if (Count==0 && Check_Odds(Wheels[2][WheelPos[2]])==1) Count++;
    }
  if (NumWheels==4) {
    Count=10+Random(200);
    while (Count-->0) {
      WheelPos[3]++; if (WheelPos[3]>23) WheelPos[3]=0;
      if (TestMode==0) Display_Wheels();
      if (Count==0 && Check_Odds(Wheels[3][WheelPos[3]])==1) Count++;
      }
    }
  for (i=0;i<NumWheels;i++) {
    p[i]=WheelPos[i]-1;
    if (p[i]<0) p[i]=23;
    if (strcmp(Wheels[i][p[i]],"-vv-")==0 || strcmp(Wheels[i][p[i]],"=vv=")==0) {
      if (TestMode==0) Delay(1);
      WheelPos[i]--;
      if (WheelPos[i]>23) WheelPos[i]=0;
      if (TestMode==0) Display_Wheels();
      }
    }
  for (i=0;i<NumWheels;i++) {
    p[i]=WheelPos[i]+1;
    if (p[i]>23) p[i]=0;
    if (strcmp(Wheels[i][p[i]],"-^^-")==0 || strcmp(Wheels[i][p[i]],"=^^=")==0) {
      if (TestMode==0) Delay(1);
      WheelPos[i]++;
      if (WheelPos[i]<0) WheelPos[i]=23;
      if (TestMode==0) Display_Wheels();
      }
    }
  if (NumWheels==3) {
    if (PayLines==1) {
      j=-1;
      for (i=0;i<NumPayoffs;i++) {
        Mult=1;
        if (Check_Symbol(Wheels[0][WheelPos[0]],PaySymbol[0][i])==1 &&
            Check_Symbol(Wheels[1][WheelPos[1]],PaySymbol[1][i])==1 &&
            Check_Symbol(Wheels[2][WheelPos[2]],PaySymbol[2][i])==1) {
          j=i;
          RMult=Mult;
          }
        }
      if (j!=-1) {
        Ret=Pay[j]*Coins*RMult;
        PaidOut+=(Ret*Coins*RMult);
        LastPayout=Ret*Coins*RMult;
        Hit[j]++;
        }
      }
    else if (PayLines>1) {
      j=-1;
      for (i=0;i<NumPayoffs;i++) {
        Mult=1;
        if (Check_Symbol(Wheels[0][WheelPos[0]],PaySymbol[0][i])==1 &&
            Check_Symbol(Wheels[1][WheelPos[1]],PaySymbol[1][i])==1 &&
            Check_Symbol(Wheels[2][WheelPos[2]],PaySymbol[2][i])==1) {
          j=i;
          RMult=Mult;
          }
        }
      if (j!=-1) {
        Ret=Pay[j]*RMult;
        PaidOut+=(Ret*RMult);
        LastPayout=Ret*RMult;
        Hit[j]++;
        }
      if (Coins>1) {
        j=-1;
        for (i=0;i<3;i++) {
          p[i]=WheelPos[i]-1;
          if (p[i]<0) p[i]=23;
          }
        for (i=0;i<NumPayoffs;i++) {
          Mult=1;
          if (Check_Symbol(Wheels[0][p[0]],PaySymbol[0][i])==1 &&
              Check_Symbol(Wheels[1][p[1]],PaySymbol[1][i])==1 &&
              Check_Symbol(Wheels[2][p[2]],PaySymbol[2][i])==1) {
            j=i;
            RMult=Mult;
            }
          }
        if (j!=-1) {
          Ret+=Pay[j]*RMult;
          PaidOut+=(Ret*RMult);
          LastPayout=Ret*RMult;
          Hit[j]++;
          }
        }
      if (Coins>2) {
        j=-1;
        for (i=0;i<3;i++) {
          p[i]=WheelPos[i]+1;
          if (p[i]>23) p[i]=0;
          }
        for (i=0;i<NumPayoffs;i++) {
          Mult=1;
          if (Check_Symbol(Wheels[0][p[0]],PaySymbol[0][i])==1 &&
              Check_Symbol(Wheels[1][p[1]],PaySymbol[1][i])==1 &&
              Check_Symbol(Wheels[2][p[2]],PaySymbol[2][i])==1) {
            j=i;
            RMult=Mult;
            }
          }
        if (j!=-1) {
          Ret+=Pay[j]*RMult;
          PaidOut+=(Ret*RMult);
          LastPayout=Ret*RMult;
          Hit[j]++;
          }
        }
      if (Coins>3 && PayLines>3) {
        j=-1;
        p[0]=WheelPos[0]-1; if (p[0]<0) p[0]=23;
        p[1]=WheelPos[1];
        p[2]=WheelPos[2]+1; if (p[2]>23) p[2]=0;
        for (i=0;i<NumPayoffs;i++) {
          Mult=1;
          if (Check_Symbol(Wheels[0][p[0]],PaySymbol[0][i])==1 &&
              Check_Symbol(Wheels[1][p[1]],PaySymbol[1][i])==1 &&
              Check_Symbol(Wheels[2][p[2]],PaySymbol[2][i])==1) {
            j=i;
            RMult=Mult;
            }
          }
        if (j!=-1) {
          Ret+=Pay[j]*RMult;
          PaidOut+=(Ret*RMult);
          LastPayout=Ret*RMult;
          Hit[j]++;
          }
        }
      if (Coins>4 && PayLines>3) {
        j=-1;
        p[0]=WheelPos[0]+1; if (p[0]>23) p[0]=0;
        p[1]=WheelPos[1];
        p[2]=WheelPos[2]-1; if (p[2]<0) p[2]=23;
        for (i=0;i<NumPayoffs;i++) {
          Mult=1;
          if (Check_Symbol(Wheels[0][p[0]],PaySymbol[0][i])==1 &&
              Check_Symbol(Wheels[1][p[1]],PaySymbol[1][i])==1 &&
              Check_Symbol(Wheels[2][p[2]],PaySymbol[2][i])==1) {
            j=i;
            RMult=Mult;
            }
          }
        if (j!=-1) {
          Ret+=Pay[j]*RMult;
          PaidOut+=(Ret*RMult);
          LastPayout=Ret*RMult;
          Hit[j]++;
          }
        }
      }
    else {
      }
    }
  else {
    if (PayLines==1) {
      }
    else {
      }
    }
  return Ret;
}

void SLOTS::TestSpins(long int spins)
{
  float p1,p2;
  ClrScr(); printf("\n");
  TestMode=1;
  Doubles=0;
  while (spins-->0) Spin(MaxBet);
  GotoXY(1,1);
  p1=PaidIn; p2=PaidOut;
  printf("Paid in:%d  Paid out:%d  %5.2f\n",PaidIn,PaidOut,p2/p1);
  for (i=0;i<NumPayoffs;i++)
    printf("%s %s %s %s %8d %12d\n",PaySymbol[0][i],PaySymbol[1][i],
      PaySymbol[2][i],PaySymbol[3][i],Hit[i],MaxBet*Hit[i]*Pay[i]);
  printf(" X2  %8d\n",Doubles);
  TestMode=0;
  Input(Buffer);
  ClrScr();
}

void SLOTS::Add_Odds(char* buffer,int odds)
{
  strcpy(OddsSymbol[NumOdds],buffer);
  Odds[NumOdds++]=odds;
}

void SLOTS::Add_Payout(char* w1,char* w2,char* w3,char*w4,int payout)
{
  strcpy(PaySymbol[0][NumPayoffs],w1);
  strcpy(PaySymbol[1][NumPayoffs],w2);
  strcpy(PaySymbol[2][NumPayoffs],w3);
  strcpy(PaySymbol[3][NumPayoffs],w4);
  Pay[NumPayoffs++]=payout;
}

void Slot1(PLAYER* Player,int BetSize)
{
  SLOTS SlotM;
  WHEEL w;
  int Bet;
  int Amount;
  int r;
  int Credits;
  ClrScr();
  Credits=0;
  SlotM.New(3,1,3,1);
  strcpy(w.Entry[0],"    "); strcpy(w.Entry[1],"----");
  strcpy(w.Entry[2],"    "); strcpy(w.Entry[3],"$$$$");
  strcpy(w.Entry[4],"    "); strcpy(w.Entry[5],"----");
  strcpy(w.Entry[6],"    "); strcpy(w.Entry[7],"====");
  strcpy(w.Entry[8],"    "); strcpy(w.Entry[9],"----");
  strcpy(w.Entry[10],"    "); strcpy(w.Entry[11],"====");
  strcpy(w.Entry[12],"    "); strcpy(w.Entry[13],"----");
  strcpy(w.Entry[14],"    "); strcpy(w.Entry[15],"$$$$");
  strcpy(w.Entry[16],"    "); strcpy(w.Entry[17],"----");
  strcpy(w.Entry[18],"    "); strcpy(w.Entry[19],"====");
  strcpy(w.Entry[20],"    "); strcpy(w.Entry[21],"----");
  strcpy(w.Entry[22],"    "); strcpy(w.Entry[23],"====");
  SlotM.Add_Wheel(w,0);
  SlotM.Add_Wheel(w,1);
  strcpy(w.Entry[0],"    "); strcpy(w.Entry[1],"----");
  strcpy(w.Entry[2],"    "); strcpy(w.Entry[3],"----");
  strcpy(w.Entry[4],"    "); strcpy(w.Entry[5],"----");
  strcpy(w.Entry[6],"    "); strcpy(w.Entry[7],"====");
  strcpy(w.Entry[8],"    "); strcpy(w.Entry[9],"----");
  strcpy(w.Entry[10],"    "); strcpy(w.Entry[11],"----");
  strcpy(w.Entry[12],"    "); strcpy(w.Entry[13],"----");
  strcpy(w.Entry[14],"    "); strcpy(w.Entry[15],"$$$$");
  strcpy(w.Entry[16],"    "); strcpy(w.Entry[17],"----");
  strcpy(w.Entry[18],"    "); strcpy(w.Entry[19],"----");
  strcpy(w.Entry[20],"    "); strcpy(w.Entry[21],"----");
  strcpy(w.Entry[22],"    "); strcpy(w.Entry[23],"====");
  SlotM.Add_Wheel(w,2);
  SlotM.Add_Payout("BLNK","BLNK","BLNK","    ",1);
  SlotM.Add_Payout("ANY ","ANY ","ANY ","    ",3);
  SlotM.Add_Payout("----","----","----","    ",9);
  SlotM.Add_Payout("====","====","====","    ",100);
  SlotM.Add_Payout("$$$$","$$$$","$$$$","    ",500);
  SlotM.Add_Odds("====",5);
  SlotM.Display_Machine(0);
/*  SlotM.TestSpins(1000000); */
  Bet=1;
  while (Bet!=0) {
    GotoXY(PLAYER_X,PLAYER_Y+1);
    sprintf(Buffer,"Credits:%d    \n",Credits);
    Output(Buffer);
    GotoXY(PLAYER_X,PLAYER_Y+2);
    sprintf(Buffer,"Money $%12.2f   \n",Player->Money());
    Output(Buffer);
    GotoXY(PLAYER_X,PLAYER_Y+3);
    Output("Bet ?");
    Input(Buffer);
    sscanf(Buffer,"%d",&Bet);
    GotoXY(PLAYER_X,PLAYER_Y+3); Output("             \n");
    if (Bet>3) Bet=3;
    Amount=Bet;
    if (Amount>0) {
      while (Credits>0 && Amount>0) { Credits--; Amount--; }
      }
    else Amount=-Amount;
    if (Amount>0) {
      Player->Place_Bet(Amount*BetSize,0,1,1);
      Player->Clear_All_Bets();
      }
    if (Bet!=0) {
      r=SlotM.Spin(Bet);
      if (r>0) {
        sprintf(Buffer,"Won %d   \n",r);
        GotoXY(PLAYER_X,PLAYER_Y); Output(Buffer);
        Credits+=r;
        }
      else {
        GotoXY(PLAYER_X,PLAYER_Y); Output("             \n");
        }
      }
    }
  Player->Add_Chips(BetSize,Credits);
}

void Slot2(PLAYER* Player,int BetSize)
{
  SLOTS SlotM;
  WHEEL w;
  int Bet;
  int Amount;
  int r;
  int Credits;
  ClrScr();
  Credits=0;
  SlotM.New(3,1,3,1);
  strcpy(w.Entry[0],"    "); strcpy(w.Entry[1]," OO ");
  strcpy(w.Entry[2],"    "); strcpy(w.Entry[3]," OO ");
  strcpy(w.Entry[4],"    "); strcpy(w.Entry[5]," $$ ");
  strcpy(w.Entry[6],"    "); strcpy(w.Entry[7]," X2 ");
  strcpy(w.Entry[8],"    "); strcpy(w.Entry[9]," OO ");
  strcpy(w.Entry[10],"    "); strcpy(w.Entry[11]," $$ ");
  strcpy(w.Entry[12],"    "); strcpy(w.Entry[13]," OO ");
  strcpy(w.Entry[14],"    "); strcpy(w.Entry[15],"7777");
  strcpy(w.Entry[16],"    "); strcpy(w.Entry[17]," OO ");
  strcpy(w.Entry[18],"    "); strcpy(w.Entry[19]," $$ ");
  strcpy(w.Entry[20],"    "); strcpy(w.Entry[21]," OO ");
  strcpy(w.Entry[22],"    "); strcpy(w.Entry[23]," OO ");
  SlotM.Add_Wheel(w,0);
  SlotM.Add_Wheel(w,1);
  SlotM.Add_Wheel(w,2);
  SlotM.Add_Payout("ANYN","ANYN"," OO ","    ",1);
  SlotM.Add_Payout("ANYN"," OO "," OO ","    ",2);
  SlotM.Add_Payout("ANY ","ANY ","ANY ","    ",3);
  SlotM.Add_Payout(" OO "," OO "," OO ","    ",9);
  SlotM.Add_Payout(" $$ "," $$ "," $$ ","    ",100);
  SlotM.Add_Payout("7777","7777","7777","    ",1000);
  SlotM.Add_Odds(" OO ",25);
  SlotM.Add_Odds(" $$ ",30);
  SlotM.Add_Odds("7777",35);
  SlotM.Add_Odds(" X2 ",55);
/*  SlotM.TestSpins(1000000); */
  SlotM.Display_Machine(0);
  Bet=1;
  while (Bet!=0) {
    GotoXY(PLAYER_X,PLAYER_Y+1);
    sprintf(Buffer,"Credits:%d    \n",Credits);
    Output(Buffer);
    GotoXY(PLAYER_X,PLAYER_Y+2);
    sprintf(Buffer,"Money $%12.2f   \n",Player->Money());
    Output(Buffer);
    GotoXY(PLAYER_X,PLAYER_Y+3);
    Output("Bet ?");
    Input(Buffer);
    sscanf(Buffer,"%d",&Bet);
    GotoXY(PLAYER_X,PLAYER_Y+3); Output("             \n");
    if (Bet>3) Bet=3;
    Amount=Bet;
    if (Amount>0) {
      while (Credits>0 && Amount>0) { Credits--; Amount--; }
      }
    else Amount=-Amount;
    if (Amount>0) {
      Player->Place_Bet(Amount*BetSize,0,1,1);
      Player->Clear_All_Bets();
      }
    if (Bet!=0) {
      r=SlotM.Spin(Bet);
      if (r>0) {
        sprintf(Buffer,"Won %d   \n",r);
        GotoXY(PLAYER_X,PLAYER_Y); Output(Buffer);
        Credits+=r;
        }
      else {
        GotoXY(PLAYER_X,PLAYER_Y); Output("             \n");
        }
      }
    }
  Player->Add_Chips(BetSize,Credits);
}

void Slot3(PLAYER* Player,int BetSize)
{
  SLOTS SlotM;
  WHEEL w;
  int Bet;
  int Amount;
  int r;
  int Credits;
  ClrScr();
  Credits=0;
  SlotM.New(3,1,3,1);
  strcpy(w.Entry[0],"    "); strcpy(w.Entry[1],"  7 ");
  strcpy(w.Entry[2],"    "); strcpy(w.Entry[3],"  7 ");
  strcpy(w.Entry[4],"    "); strcpy(w.Entry[5]," 77 ");
  strcpy(w.Entry[6],"    "); strcpy(w.Entry[7]," X3 ");
  strcpy(w.Entry[8],"    "); strcpy(w.Entry[9],"  7 ");
  strcpy(w.Entry[10],"    "); strcpy(w.Entry[11]," 77 ");
  strcpy(w.Entry[12],"    "); strcpy(w.Entry[13],"  7 ");
  strcpy(w.Entry[14],"    "); strcpy(w.Entry[15]," 777");
  strcpy(w.Entry[16],"    "); strcpy(w.Entry[17],"  7 ");
  strcpy(w.Entry[18],"    "); strcpy(w.Entry[19]," 77 ");
  strcpy(w.Entry[20],"    "); strcpy(w.Entry[21],"  7 ");
  strcpy(w.Entry[22],"    "); strcpy(w.Entry[23],"  7 ");
  SlotM.Add_Wheel(w,0);
  SlotM.Add_Wheel(w,1);
  SlotM.Add_Wheel(w,2);
  SlotM.Add_Payout("  7 ","  7 ","  7 ","    ",9);
  SlotM.Add_Payout(" 77 "," 77 "," 77 ","    ",27);
  SlotM.Add_Payout(" 777"," 777"," 777","    ",1000);
  SlotM.Add_Odds(" 77 ",5);
  SlotM.Add_Odds(" 777",35);
  SlotM.Add_Odds(" X3 ",60);
/*  SlotM.TestSpins(1000000); */
  SlotM.Display_Machine(0);
  Bet=1;
  while (Bet!=0) {
    GotoXY(PLAYER_X,PLAYER_Y+1);
    sprintf(Buffer,"Credits:%d    \n",Credits);
    Output(Buffer);
    GotoXY(PLAYER_X,PLAYER_Y+2);
    sprintf(Buffer,"Money $%12.2f   \n",Player->Money());
    Output(Buffer);
    GotoXY(PLAYER_X,PLAYER_Y+3);
    Output("Bet ?");
    Input(Buffer);
    sscanf(Buffer,"%d",&Bet);
    GotoXY(PLAYER_X,PLAYER_Y+3); Output("             \n");
    if (Bet>3) Bet=3;
    Amount=Bet;
    if (Amount>0) {
      while (Credits>0 && Amount>0) { Credits--; Amount--; }
      }
    else Amount=-Amount;
    if (Amount>0) {
      Player->Place_Bet(Amount*BetSize,0,1,1);
      Player->Clear_All_Bets();
      }
    if (Bet!=0) {
      r=SlotM.Spin(Bet);
      if (r>0) {
        sprintf(Buffer,"Won %d   \n",r);
        GotoXY(PLAYER_X,PLAYER_Y); Output(Buffer);
        Credits+=r;
        }
      else {
        GotoXY(PLAYER_X,PLAYER_Y); Output("             \n");
        }
      }
    }
  Player->Add_Chips(BetSize,Credits);
}

void Slot4(PLAYER* Player,int BetSize)
{
  SLOTS SlotM;
  WHEEL w;
  int Bet;
  int Amount;
  int r;
  int Credits;
  ClrScr();
  Credits=0;
  SlotM.New(3,1,3,1);
  strcpy(w.Entry[0],"    "); strcpy(w.Entry[1],"  1 ");
  strcpy(w.Entry[2],"    "); strcpy(w.Entry[3],"  2 ");
  strcpy(w.Entry[4],"    "); strcpy(w.Entry[5],"====");
  strcpy(w.Entry[6],"    "); strcpy(w.Entry[7],"WILD");
  strcpy(w.Entry[8],"    "); strcpy(w.Entry[9],"  1 ");
  strcpy(w.Entry[10],"    "); strcpy(w.Entry[11],"  3 ");
  strcpy(w.Entry[12],"    "); strcpy(w.Entry[13],"  2 ");
  strcpy(w.Entry[14],"    "); strcpy(w.Entry[15],"  W ");
  strcpy(w.Entry[16],"    "); strcpy(w.Entry[17],"  3 ");
  strcpy(w.Entry[18],"    "); strcpy(w.Entry[19],"====");
  strcpy(w.Entry[20],"    "); strcpy(w.Entry[21],"  7 ");
  strcpy(w.Entry[22],"    "); strcpy(w.Entry[23],"  1 ");
  SlotM.Add_Wheel(w,0);
  strcpy(w.Entry[0],"    "); strcpy(w.Entry[1],"  1 ");
  strcpy(w.Entry[2],"    "); strcpy(w.Entry[3],"  2 ");
  strcpy(w.Entry[4],"    "); strcpy(w.Entry[5],"====");
  strcpy(w.Entry[6],"    "); strcpy(w.Entry[7],"WILD");
  strcpy(w.Entry[8],"    "); strcpy(w.Entry[9],"  1 ");
  strcpy(w.Entry[10],"    "); strcpy(w.Entry[11],"  3 ");
  strcpy(w.Entry[12],"    "); strcpy(w.Entry[13],"  1 ");
  strcpy(w.Entry[14],"    "); strcpy(w.Entry[15],"  I ");
  strcpy(w.Entry[16],"    "); strcpy(w.Entry[17],"  2 ");
  strcpy(w.Entry[18],"    "); strcpy(w.Entry[19],"====");
  strcpy(w.Entry[20],"    "); strcpy(w.Entry[21],"  3 ");
  strcpy(w.Entry[22],"    "); strcpy(w.Entry[23],"  1 ");
  SlotM.Add_Wheel(w,1);
  strcpy(w.Entry[0],"    "); strcpy(w.Entry[1],"  1 ");
  strcpy(w.Entry[2],"    "); strcpy(w.Entry[3],"  2 ");
  strcpy(w.Entry[4],"    "); strcpy(w.Entry[5],"====");
  strcpy(w.Entry[6],"    "); strcpy(w.Entry[7],"WILD");
  strcpy(w.Entry[8],"    "); strcpy(w.Entry[9],"  1 ");
  strcpy(w.Entry[10],"    "); strcpy(w.Entry[11],"  3 ");
  strcpy(w.Entry[12],"    "); strcpy(w.Entry[13],"  2 ");
  strcpy(w.Entry[14],"    "); strcpy(w.Entry[15],"  N ");
  strcpy(w.Entry[16],"    "); strcpy(w.Entry[17],"  1 ");
  strcpy(w.Entry[18],"    "); strcpy(w.Entry[19],"====");
  strcpy(w.Entry[20],"    "); strcpy(w.Entry[21],"  3 ");
  strcpy(w.Entry[22],"    "); strcpy(w.Entry[23],"  1 ");
  SlotM.Add_Wheel(w,2);
  SlotM.Add_Payout("  1 ","  1 ","  1 ","    ",15);
  SlotM.Add_Payout("  1 ","  2 ","  3 ","    ",25);
  SlotM.Add_Payout("  3 ","  2 ","  1 ","    ",25);
  SlotM.Add_Payout("  2 ","  2 ","  2 ","    ",75);
  SlotM.Add_Payout("  3 ","  3 ","  3 ","    ",100);
  SlotM.Add_Payout("====","====","====","    ",500);
  SlotM.Add_Payout("  W ","  I ","  N ","    ",1000);
  SlotM.Add_Payout("WILD","WILD","WILD","    ",7500);
  SlotM.Add_Odds("  3 ",25);
  SlotM.Add_Odds("====",35);
  SlotM.Add_Odds("WILD",40);
/*  SlotM.TestSpins(1000000); */
  SlotM.Display_Machine(0);
  Bet=1;
  while (Bet!=0) {
    GotoXY(PLAYER_X,PLAYER_Y+1);
    sprintf(Buffer,"Credits:%d    \n",Credits);
    Output(Buffer);
    GotoXY(PLAYER_X,PLAYER_Y+2);
    sprintf(Buffer,"Money $%12.2f   \n",Player->Money());
    Output(Buffer);
    GotoXY(PLAYER_X,PLAYER_Y+3);
    Output("Bet ?");
    Input(Buffer);
    sscanf(Buffer,"%d",&Bet);
    GotoXY(PLAYER_X,PLAYER_Y+3); Output("             \n");
    if (Bet>3) Bet=3;
    Amount=Bet;
    if (Amount>0) {
      while (Credits>0 && Amount>0) { Credits--; Amount--; }
      }
    else Amount=-Amount;
    if (Amount>0) {
      Player->Place_Bet(Amount*BetSize,0,1,1);
      Player->Clear_All_Bets();
      }
    if (Bet!=0) {
      r=SlotM.Spin(Bet);
      if (r>0) {
        sprintf(Buffer,"Won %d   \n",r);
        GotoXY(PLAYER_X,PLAYER_Y); Output(Buffer);
        Credits+=r;
        }
      else {
        GotoXY(PLAYER_X,PLAYER_Y); Output("             \n");
        }
      }
    }
  Player->Add_Chips(BetSize,Credits);
}

void Slot5(PLAYER* Player,int BetSize)
{
  SLOTS SlotM;
  WHEEL w;
  int Bet;
  int Amount;
  int r;
  int Credits;
  ClrScr();
  Credits=0;
  SlotM.New(3,1,3,1);
  strcpy(w.Entry[0],"    "); strcpy(w.Entry[1],"----");
  strcpy(w.Entry[2],"    "); strcpy(w.Entry[3],"$$$$");
  strcpy(w.Entry[4],"    "); strcpy(w.Entry[5],"----");
  strcpy(w.Entry[6],"    "); strcpy(w.Entry[7],"====");
  strcpy(w.Entry[8],"    "); strcpy(w.Entry[9],"-vv-");
  strcpy(w.Entry[10],"    "); strcpy(w.Entry[11],"====");
  strcpy(w.Entry[12],"    "); strcpy(w.Entry[13],"-^^-");
  strcpy(w.Entry[14],"    "); strcpy(w.Entry[15],"$$$$");
  strcpy(w.Entry[16],"    "); strcpy(w.Entry[17],"----");
  strcpy(w.Entry[18],"    "); strcpy(w.Entry[19],"=vv=");
  strcpy(w.Entry[20],"    "); strcpy(w.Entry[21],"----");
  strcpy(w.Entry[22],"    "); strcpy(w.Entry[23],"=^^=");
  SlotM.Add_Wheel(w,0);
  SlotM.Add_Wheel(w,1);
  strcpy(w.Entry[0],"    "); strcpy(w.Entry[1],"----");
  strcpy(w.Entry[2],"    "); strcpy(w.Entry[3],"----");
  strcpy(w.Entry[4],"    "); strcpy(w.Entry[5],"-vv-");
  strcpy(w.Entry[6],"    "); strcpy(w.Entry[7],"====");
  strcpy(w.Entry[8],"    "); strcpy(w.Entry[9],"----");
  strcpy(w.Entry[10],"    "); strcpy(w.Entry[11],"----");
  strcpy(w.Entry[12],"    "); strcpy(w.Entry[13],"----");
  strcpy(w.Entry[14],"    "); strcpy(w.Entry[15],"$$$$");
  strcpy(w.Entry[16],"    "); strcpy(w.Entry[17],"----");
  strcpy(w.Entry[18],"    "); strcpy(w.Entry[19],"-^^-");
  strcpy(w.Entry[20],"    "); strcpy(w.Entry[21],"----");
  strcpy(w.Entry[22],"    "); strcpy(w.Entry[23],"====");
  SlotM.Add_Wheel(w,2);
  SlotM.Add_Payout("ANY ","ANY ","ANY ","    ",1);
  SlotM.Add_Payout("----","----","----","    ",5);
  SlotM.Add_Payout("====","====","====","    ",75);
  SlotM.Add_Payout("$$$$","$$$$","$$$$","    ",500);
  SlotM.Add_Odds("====",5);
  SlotM.Display_Machine(0);
/*  SlotM.TestSpins(1000000); */
  Bet=1;
  while (Bet!=0) {
    GotoXY(PLAYER_X,PLAYER_Y+1);
    sprintf(Buffer,"Credits:%d    \n",Credits);
    Output(Buffer);
    GotoXY(PLAYER_X,PLAYER_Y+2);
    sprintf(Buffer,"Money $%12.2f   \n",Player->Money());
    Output(Buffer);
    GotoXY(PLAYER_X,PLAYER_Y+3);
    Output("Bet ?");
    Input(Buffer);
    sscanf(Buffer,"%d",&Bet);
    GotoXY(PLAYER_X,PLAYER_Y+3); Output("             \n");
    if (Bet>3) Bet=3;
    Amount=Bet;
    if (Amount>0) {
      while (Credits>0 && Amount>0) { Credits--; Amount--; }
      }
    else Amount=-Amount;
    if (Amount>0) {
      Player->Place_Bet(Amount*BetSize,0,1,1);
      Player->Clear_All_Bets();
      }
    if (Bet!=0) {
      r=SlotM.Spin(Bet);
      if (r>0) {
        sprintf(Buffer,"Won %d  \n",r);
        GotoXY(PLAYER_X,PLAYER_Y); Output(Buffer);
        Credits+=r;
        }
      else {
        GotoXY(PLAYER_X,PLAYER_Y); Output("             \n");
        }
      }
    }
  Player->Add_Chips(BetSize,Credits);
}

void Slot6(PLAYER* Player,int BetSize)
{
  SLOTS SlotM;
  WHEEL w;
  int Bet;
  int Amount;
  int r;
  int Credits;
  ClrScr();
  Credits=0;
  SlotM.New(3,1,3,3);
  strcpy(w.Entry[0],"    "); strcpy(w.Entry[1]," WI ");
  strcpy(w.Entry[2],"    "); strcpy(w.Entry[3]," MO ");
  strcpy(w.Entry[4],"    "); strcpy(w.Entry[5]," CA ");
  strcpy(w.Entry[6],"    "); strcpy(w.Entry[7]," BLA");
  strcpy(w.Entry[8],"    "); strcpy(w.Entry[9]," CA ");
  strcpy(w.Entry[10],"    "); strcpy(w.Entry[11]," MO ");
  strcpy(w.Entry[12],"    "); strcpy(w.Entry[13]," CA ");
  strcpy(w.Entry[14],"    "); strcpy(w.Entry[15]," MO ");
  strcpy(w.Entry[16],"    "); strcpy(w.Entry[17]," CA ");
  strcpy(w.Entry[18],"    "); strcpy(w.Entry[19]," MO ");
  strcpy(w.Entry[20],"    "); strcpy(w.Entry[21]," CA ");
  strcpy(w.Entry[22],"    "); strcpy(w.Entry[23]," BLA");
  SlotM.Add_Wheel(w,0);
  strcpy(w.Entry[0],"    "); strcpy(w.Entry[1]," NN ");
  strcpy(w.Entry[2],"    "); strcpy(w.Entry[3]," SI ");
  strcpy(w.Entry[4],"    "); strcpy(w.Entry[5]," CK ");
  strcpy(w.Entry[6],"    "); strcpy(w.Entry[7]," SI ");
  strcpy(w.Entry[8],"    "); strcpy(w.Entry[9],"  N ");
  strcpy(w.Entry[10],"    "); strcpy(w.Entry[11]," SI ");
  strcpy(w.Entry[12],"    "); strcpy(w.Entry[13],"  N ");
  strcpy(w.Entry[14],"    "); strcpy(w.Entry[15]," SI ");
  strcpy(w.Entry[16],"    "); strcpy(w.Entry[17],"  N ");
  strcpy(w.Entry[18],"    "); strcpy(w.Entry[19],"CK  ");
  strcpy(w.Entry[20],"    "); strcpy(w.Entry[21],"  N ");
  strcpy(w.Entry[22],"    "); strcpy(w.Entry[23]," SI ");
  SlotM.Add_Wheel(w,1);
  strcpy(w.Entry[0],"    "); strcpy(w.Entry[1]," ER ");
  strcpy(w.Entry[2],"    "); strcpy(w.Entry[3]," NO ");
  strcpy(w.Entry[4],"    "); strcpy(w.Entry[5]," EY ");
  strcpy(w.Entry[6],"    "); strcpy(w.Entry[7]," NO ");
  strcpy(w.Entry[8],"    "); strcpy(w.Entry[9],"JACK");
  strcpy(w.Entry[10],"    "); strcpy(w.Entry[11]," NO ");
  strcpy(w.Entry[12],"    "); strcpy(w.Entry[13]," EY ");
  strcpy(w.Entry[14],"    "); strcpy(w.Entry[15]," NO ");
  strcpy(w.Entry[16],"    "); strcpy(w.Entry[17]," EY ");
  strcpy(w.Entry[18],"    "); strcpy(w.Entry[19],"JACK");
  strcpy(w.Entry[20],"    "); strcpy(w.Entry[21]," EY ");
  strcpy(w.Entry[22],"    "); strcpy(w.Entry[23]," NO ");
  SlotM.Add_Wheel(w,2);
  SlotM.Add_Payout("BLNK","BLNK","BLNK","    ",1);
  SlotM.Add_Payout("ANY ","ANY "," NO ","    ",3);
  SlotM.Add_Payout(" CA "," SI "," NO ","    ",12);
  SlotM.Add_Payout(" MO ","  N "," EY ","    ",26);
  SlotM.Add_Payout(" BLA","CK  ","JACK","    ",100);
  SlotM.Add_Payout(" WI "," NN "," ER ","    ",500);
  SlotM.Add_Odds(" ER ",5);
  SlotM.Display_Machine(0);
/*  SlotM.TestSpins(1000000); */
  Bet=1;
  while (Bet!=0) {
    GotoXY(PLAYER_X,PLAYER_Y+1);
    sprintf(Buffer,"Credits:%d    \n",Credits);
    Output(Buffer);
    GotoXY(PLAYER_X,PLAYER_Y+2);
    sprintf(Buffer,"Money $%12.2f   \n",Player->Money());
    Output(Buffer);
    GotoXY(PLAYER_X,PLAYER_Y+3);
    Output("Bet ?");
    Input(Buffer);
    sscanf(Buffer,"%d",&Bet);
    GotoXY(PLAYER_X,PLAYER_Y+3); Output("             \n");
    if (Bet>3) Bet=3;
    Amount=Bet;
    if (Amount>0) {
      while (Credits>0 && Amount>0) { Credits--; Amount--; }
      }
    else Amount=-Amount;
    if (Amount>0) {
      Player->Place_Bet(Amount*BetSize,0,1,1);
      Player->Clear_All_Bets();
      }
    if (Bet!=0) {
      r=SlotM.Spin(Bet);
      if (r>0) {
        sprintf(Buffer,"Won %d  \n",r);
        GotoXY(PLAYER_X,PLAYER_Y); Output(Buffer);
        Credits+=r;
        }
      else {
        GotoXY(PLAYER_X,PLAYER_Y); Output("             \n");
        }
      }
    }
  Player->Add_Chips(BetSize,Credits);
}

void Slot7(PLAYER* Player,int BetSize)
{
  SLOTS SlotM;
  WHEEL w;
  int Bet;
  int Amount;
  int r;
  int Credits;
  ClrScr();
  Credits=0;
  SlotM.New(3,1,3,5);
  strcpy(w.Entry[0],"    "); strcpy(w.Entry[1],"  O ");
  strcpy(w.Entry[2],"    "); strcpy(w.Entry[3],"  * ");
  strcpy(w.Entry[4],"    "); strcpy(w.Entry[5],"  O ");
  strcpy(w.Entry[6],"    "); strcpy(w.Entry[7],"----");
  strcpy(w.Entry[8],"    "); strcpy(w.Entry[9],"  O ");
  strcpy(w.Entry[10],"    "); strcpy(w.Entry[11]," $$ ");
  strcpy(w.Entry[12],"    "); strcpy(w.Entry[13],"  O ");
  strcpy(w.Entry[14],"    "); strcpy(w.Entry[15],"  * ");
  strcpy(w.Entry[16],"    "); strcpy(w.Entry[17],"  O ");
  strcpy(w.Entry[18],"    "); strcpy(w.Entry[19],"----");
  strcpy(w.Entry[20],"    "); strcpy(w.Entry[21],"  O ");
  strcpy(w.Entry[22],"    "); strcpy(w.Entry[23],"  * ");
  SlotM.Add_Wheel(w,0);
  strcpy(w.Entry[0],"    "); strcpy(w.Entry[1],"  O ");
  strcpy(w.Entry[2],"    "); strcpy(w.Entry[3],"  * ");
  strcpy(w.Entry[4],"    "); strcpy(w.Entry[5],"----");
  strcpy(w.Entry[6],"    "); strcpy(w.Entry[7],"  O ");
  strcpy(w.Entry[8],"    "); strcpy(w.Entry[9],"  * ");
  strcpy(w.Entry[10],"    "); strcpy(w.Entry[11]," $$ ");
  strcpy(w.Entry[12],"    "); strcpy(w.Entry[13],"  O ");
  strcpy(w.Entry[14],"    "); strcpy(w.Entry[15],"  * ");
  strcpy(w.Entry[16],"    "); strcpy(w.Entry[17],"----");
  strcpy(w.Entry[18],"    "); strcpy(w.Entry[19],"  O ");
  strcpy(w.Entry[20],"    "); strcpy(w.Entry[21],"WILD");
  strcpy(w.Entry[22],"    "); strcpy(w.Entry[23],"  * ");
  SlotM.Add_Wheel(w,1);
  SlotM.Add_Wheel(w,2);
  SlotM.Add_Payout("    ","    ","  O ","    ",1);
  SlotM.Add_Payout("    ","  O ","    ","    ",1);
  SlotM.Add_Payout("  O ","    ","    ","    ",1);
  SlotM.Add_Payout("  O ","  O ","  O ","    ",9);
  SlotM.Add_Payout("  * ","  * ","  * ","    ",50);
  SlotM.Add_Payout("----","----","----","    ",200);
  SlotM.Add_Payout(" $$ "," $$ "," $$ ","    ",300);
  SlotM.Add_Odds(" ER ",5);
  SlotM.Display_Machine(0);
/*  SlotM.TestSpins(1000000); */
  Bet=1;
  while (Bet!=0) {
    GotoXY(PLAYER_X,PLAYER_Y+1);
    sprintf(Buffer,"Credits:%d    \n",Credits);
    Output(Buffer);
    GotoXY(PLAYER_X,PLAYER_Y+2);
    sprintf(Buffer,"Money $%12.2f   \n",Player->Money());
    Output(Buffer);
    GotoXY(PLAYER_X,PLAYER_Y+3);
    Output("Bet ?");
    Input(Buffer);
    sscanf(Buffer,"%d",&Bet);
    GotoXY(PLAYER_X,PLAYER_Y+3); Output("             \n");
    if (Bet>5) Bet=5;
    Amount=Bet;
    if (Amount>0) {
      while (Credits>0 && Amount>0) { Credits--; Amount--; }
      }
    else Amount=-Amount;
    if (Amount>0) {
      Player->Place_Bet(Amount*BetSize,0,1,1);
      Player->Clear_All_Bets();
      }
    if (Bet!=0) {
      r=SlotM.Spin(Bet);
      if (r>0) {
        sprintf(Buffer,"Won %d  \n",r);
        GotoXY(PLAYER_X,PLAYER_Y); Output(Buffer);
        Credits+=r;
        }
      else {
        GotoXY(PLAYER_X,PLAYER_Y); Output("             \n");
        }
      }
    }
  Player->Add_Chips(BetSize,Credits);
}


void Slots(PLAYER* Player)
{
  int i;
  int Machine;
  int BetSize;
  ClrScr();
  Output("1. Bar\n");
  Output("2. Double Fortune\n");
  Output("3. Tripple Pay\n");
  Output("4. Wild Win\n");
  Output("5. Stepper\n");
  Output("6. Alphabet Soup\n");
  Input(Buffer);
  sscanf(Buffer,"%d",&Machine);
  if (Machine!=0) {
    Output("1. $1\n2. $5\n3. $25\n4. $100\n5. $500\n6. $1000\n");
    Input(Buffer);
    sscanf(Buffer,"%d",&i);
    switch (i) {
      case 1:BetSize=1; break;
      case 2:BetSize=5; break;
      case 3:BetSize=25; break;
      case 4:BetSize=100; break;
      case 5:BetSize=500; break;
      case 6:BetSize=1000; break;
      default:BetSize=1;
      }
    switch(Machine) {
      case 1:Slot1(Player,BetSize); break;
      case 2:Slot2(Player,BetSize); break;
      case 3:Slot3(Player,BetSize); break;
      case 4:Slot4(Player,BetSize); break;
      case 5:Slot5(Player,BetSize); break;
      case 6:Slot6(Player,BetSize); break;
      case 7:Slot7(Player,BetSize); break;
      }
    }
}

