#include <stdlib.h>
#include "header.h"
#include "bingo.h"

#ifdef GRAPHIC
#include "images/bingo.xpm"
#endif

Bingo::Bingo(Player* p) {
  player=p;
  nonPlayers=2000+rcs_random(3000);
  newSheet();
  if (progressives[PROG_BINGO]<1000) progressives[PROG_BINGO]=1000;
  progressives[PROG_BINGO] += (nonPlayers/6)*0.75;
  }

Bingo::~Bingo() {
  }

void Bingo::markBoard() {
  int x,y;
  for (x=0;x<5;x++)
    for (y=0;y<5;y++)
      if ((x==2 && y==2) || (called[board[x][y]]!=' ')) marks[x][y]='*';
        else marks[x][y]=' ';
  }

void Bingo::buildBoard(long boardNum) {
  double seed;
  int x,y;
  int i,n;
  int failCount;
  char selected[16];
  seed=boardNum;
  seed /= 65535.0;
  for (x=0;x<5;x++) {
    for (i=0;i<16;i++) selected[i]=' ';
    selected[15]='*';
    n=15;
    for (y=0;y<5;y++) {
      if (x==2 && y==2) board[x][y]=0;
        else {
        failCount=0;
        while (selected[n]=='*') {
          seed*=423.1966;
          seed-=int(seed);
          n=int(seed*15);
          if (++failCount==20) { 
            seed+=.3;
            seed-=int(seed);
            failCount=0;
            }
          }
        selected[n]='*';
        board[x][y]=n+15*x;
        }
      }
    }
  }

int Bingo::validate(long boardNum,int typ) {
  int i;
  int bingos; 
  int hards;
  int count1,count2;
  buildBoard(boardNum);
  markBoard();
  bingos=0;
  hards=0;
  if (typ==TYPE_X) {
    if (marks[0][0]=='*' && marks[1][1]=='*' &&
        marks[3][3]=='*' && marks[4][4]=='*' &&
        marks[0][4]=='*' && marks[1][3]=='*' &&
        marks[3][1]=='*' && marks[4][0]=='*') return -1;
    if (marks[2][0]=='*' && marks[2][1]=='*' &&
        marks[2][3]=='*' && marks[2][4]=='*' &&
        marks[0][2]=='*' && marks[1][2]=='*' &&
        marks[3][2]=='*' && marks[4][2]=='*') return -1;
    return 0;
    }
  if (typ==TYPE_T) {
    count1=0;
    count2=0;
    for (i=0;i<5;i++) {
      if (marks[0][i]=='*' && marks[i][2]=='*') count1++;
      if (marks[4][i]=='*' && marks[i][2]=='*') count2++;
      }
    if (count1>4 || count2>4) return -1;
    count1=0;
    count2=0;
    for (i=0;i<5;i++) {
      if (marks[i][0]=='*' && marks[2][i]=='*') count1++;
      if (marks[i][4]=='*' && marks[2][i]=='*') count2++;
      }
    return 0;
    }
  if (marks[0][0]=='*' && marks[0][1]=='*' && marks[0][2]=='*' &&
      marks[0][3]=='*' && marks[0][4]=='*') { bingos++; hards++; }
  if (marks[1][0]=='*' && marks[1][1]=='*' && marks[1][2]=='*' &&
      marks[1][3]=='*' && marks[1][4]=='*') { bingos++; hards++; }
  if (marks[2][0]=='*' && marks[2][1]=='*' && marks[2][2]=='*' &&
      marks[2][3]=='*' && marks[2][4]=='*') { bingos++; }
  if (marks[3][0]=='*' && marks[3][1]=='*' && marks[3][2]=='*' &&
      marks[3][3]=='*' && marks[3][4]=='*') { bingos++; hards++; }
  if (marks[4][0]=='*' && marks[4][1]=='*' && marks[4][2]=='*' &&
      marks[4][3]=='*' && marks[4][4]=='*') { bingos++; hards++; }

  if (marks[0][0]=='*' && marks[1][0]=='*' && marks[2][0]=='*' &&
      marks[3][0]=='*' && marks[4][0]=='*') { bingos++; hards++; }
  if (marks[0][1]=='*' && marks[1][1]=='*' && marks[2][1]=='*' &&
      marks[3][1]=='*' && marks[4][1]=='*') { bingos++; hards++; }
  if (marks[0][2]=='*' && marks[1][2]=='*' && marks[2][2]=='*' &&
      marks[3][2]=='*' && marks[4][2]=='*') { bingos++; }
  if (marks[0][3]=='*' && marks[1][3]=='*' && marks[2][3]=='*' &&
      marks[3][3]=='*' && marks[4][3]=='*') { bingos++; hards++; }
  if (marks[0][4]=='*' && marks[1][4]=='*' && marks[2][4]=='*' &&
      marks[3][4]=='*' && marks[4][4]=='*') { bingos++; hards++; }

  if (marks[0][0]=='*' && marks[1][1]=='*' && marks[2][2]=='*' &&
      marks[3][3]=='*' && marks[4][4]=='*') { bingos++; }
  if (marks[0][4]=='*' && marks[1][3]=='*' && marks[2][2]=='*' &&
      marks[3][1]=='*' && marks[4][0]=='*') { bingos++; }
  if (typ==TYPE_NORMAL && bingos>0) return -1;
  if (typ==TYPE_DOUBLE && bingos>1) return -1;
  if (typ==TYPE_TRIPLE && bingos>2) return -1;
  if (typ==TYPE_HARD && hards>0) return -1;
  if (typ==TYPE_DHARD && hards>1) return -1;
  if (typ==TYPE_COVERALL && bingos==12) return -1;
  return 0;
  }

void Bingo::newSheet() {
  int i;
  for (i=0;i<6;i++) playerBoards[i]=rcs_random(65535);
  for (i=0;i<nonPlayers;i++) nonPlayerBoards[i]=rcs_random(65535);
  for (i=0;i<75;i++) called[i]=' ';
  numbersCalled=0;
  }

void Bingo::drawBoard(long boardNum,int ox,int oy) {
  rcs_GC gc;
  rcs_Font font;
  int x,y;
  char buffer[20];
  buildBoard(boardNum);
  gc=rcs_openGC(display,mainScreen);
  font=rcs_openFont(display,BINGO_FONT);
  rcs_setFont(display,gc,font);
  for (x=0;x<5;x++) {
    for (y=0;y<5;y++) {
      if (x!=2 || y!=2) {
        sprintf(buffer,"%2d",board[x][y]+1);
        rcs_drawString(display,mainScreen,gc,ox+x*29,oy+y*29,buffer);
        }
      }
    }
  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  }

void Bingo::play()
{
  int i;
  char flag;
  rcs_GC gc;
  rcs_Font font;
  rcs_Event event;
#ifdef GRAPHIC
  table=rcs_xpmToPixmap(display,mainWindow,bingo_xpm);
  gc=rcs_openGC(display,mainScreen);
  font=rcs_openFont(display,BINGO_FONT);
  rcs_setFont(display,gc,font);
  rcs_namedForeground(display,gc,"darkgreen");
  rcs_drawFilledBox(display,mainScreen,gc,0,0,800,600);
  rcs_namedForeground(display,gc,"gray80");
  rcs_drawFilledBox(display,mainScreen,gc,200,100,100,40);
  rcs_drawFilledBox(display,mainScreen,gc,200,150,100,40);
  rcs_drawFilledBox(display,mainScreen,gc,200,200,100,40);
  rcs_drawFilledBox(display,mainScreen,gc,200,250,100,40);
  rcs_drawFilledBox(display,mainScreen,gc,200,300,100,40);

  rcs_namedForeground(display,gc,"black");
  rcs_drawBox(display,mainScreen,gc,202,102,96,36);
  rcs_drawString(display,mainScreen,gc,210,125,"$4 Buyin");
  rcs_drawBox(display,mainScreen,gc,202,152,96,36);
  rcs_drawString(display,mainScreen,gc,210,175,"$7 Buyin");
  rcs_drawBox(display,mainScreen,gc,202,202,96,36);
  rcs_drawString(display,mainScreen,gc,210,225,"$10 Buyin");
  rcs_drawBox(display,mainScreen,gc,202,252,96,36);
  rcs_drawString(display,mainScreen,gc,210,275,"$13 Buyin");
  rcs_drawBox(display,mainScreen,gc,202,302,96,36);
  rcs_drawString(display,mainScreen,gc,210,325,"$16 Buyin");

  rcs_namedForeground(display,gc,"yellow");
  rcs_drawString(display,mainScreen,gc,350,125,"$50");
  rcs_drawString(display,mainScreen,gc,450,125,"$100");
  rcs_drawString(display,mainScreen,gc,550,125,"$150");
  rcs_drawString(display,mainScreen,gc,650,125,"$200");
  rcs_drawString(display,mainScreen,gc,350,175,"$100");
  rcs_drawString(display,mainScreen,gc,450,175,"$200");
  rcs_drawString(display,mainScreen,gc,550,175,"$300");
  rcs_drawString(display,mainScreen,gc,650,175,"$400");
  rcs_drawString(display,mainScreen,gc,350,225,"$150");
  rcs_drawString(display,mainScreen,gc,450,225,"$300");
  rcs_drawString(display,mainScreen,gc,550,225,"$450");
  rcs_drawString(display,mainScreen,gc,650,225,"$600");
  rcs_drawString(display,mainScreen,gc,350,275,"$200");
  rcs_drawString(display,mainScreen,gc,450,275,"$400");
  rcs_drawString(display,mainScreen,gc,550,275,"$600");
  rcs_drawString(display,mainScreen,gc,650,275,"$800");
  rcs_drawString(display,mainScreen,gc,350,325,"$250");
  rcs_drawString(display,mainScreen,gc,450,325,"$500");
  rcs_drawString(display,mainScreen,gc,550,325,"$750");
  rcs_drawString(display,mainScreen,gc,650,325,"$1000");

  for (i=0;i<6;i++)
    rcs_drawLine(display,mainScreen,gc,195,96+50*i,709,96+50*i);
  for (i=0;i<5;i++)
    rcs_drawLine(display,mainScreen,gc,310+i*100,96,310+i*100,346);
  rcs_drawLine(display,mainScreen,gc,195,96,195,346);
  rcs_drawLine(display,mainScreen,gc,310,46,310,96);
  rcs_drawLine(display,mainScreen,gc,710,46,710,96);
  rcs_drawLine(display,mainScreen,gc,310,46,710,46);

  rcs_drawString(display,mainScreen,gc,470,65,"Payouts");
  rcs_drawString(display,mainScreen,gc,330,85,"Single");
  rcs_drawString(display,mainScreen,gc,430,85,"Double");
  rcs_drawString(display,mainScreen,gc,530,85,"Triple");
  rcs_drawString(display,mainScreen,gc,630,85,"Cover all");

  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  displayScreen();
  flag=' ';
  while (flag==' ') {
    event=getEvent(display);
    if (event.type==EVENT_BUTTON_PRESS && event.d1==1) {
      if (event.d2>=201 && event.d2<=298) {
        if (event.d3>=102 && event.d3<=140) {
          player->placeBet(4,0,0,0);
          payoutLevel=1;
          flag='*';
          }
        if (event.d3>=152 && event.d3<=190) {
          player->placeBet(7,0,0,0);
          payoutLevel=2;
          flag='*';
          }
        if (event.d3>=202 && event.d3<=240) {
          player->placeBet(10,0,0,0);
          payoutLevel=3;
          flag='*';
          }
        if (event.d3>=252 && event.d3<=290) {
          player->placeBet(13,0,0,0);
          payoutLevel=4;
          flag='*';
          }
        if (event.d3>=302 && event.d3<=340) {
          player->placeBet(16,0,0,0);
          payoutLevel=5;
          flag='*';
          }
        }
      }
    }
#endif
  flag=' ';
  player->loseHandBets(0);
  player->clearAllBets();
  session();
#ifdef GRAPHIC
  rcs_closePixmap(display,table);
#endif

}

void Bingo::drawBingoScreen() {
  rcs_GC gc;
  gc=rcs_openGC(display,mainScreen);
  rcs_copyArea(display,table,mainScreen,gc,0,0,800,600,0,0);
  rcs_closeGC(display,gc);
  drawBoard(playerBoards[0],29,60);
  drawBoard(playerBoards[1],29,236);
  drawBoard(playerBoards[2],29,412);
  drawBoard(playerBoards[3],195,60);
  drawBoard(playerBoards[4],195,236);
  drawBoard(playerBoards[5],195,412);
  displayScreen();
  }

void Bingo::session() {
  gameNumber=1;
  drawBingoScreen();
  round(TYPE_T);      /* playing sheet 1 */
  Delay(5);

  newSheet();         /* playing sheet 2 */
  drawBingoScreen();
  gameNumber++;
  round(TYPE_NORMAL);
  Delay(5);
  gameNumber++;
  round(TYPE_DOUBLE);
  Delay(5);

  newSheet();         /* playing sheet 3 */
  drawBingoScreen();
  gameNumber++;
  round(TYPE_X);
  Delay(5);

  newSheet();         /* playing sheet 4 */
  drawBingoScreen();
  gameNumber++;
  round(TYPE_NORMAL);
  Delay(5);
  gameNumber++;
  round(TYPE_DOUBLE);
  Delay(5);

  newSheet();         /* playing sheet 5 */
  drawBingoScreen();
  gameNumber++;
  round(TYPE_DOUBLE);
  Delay(5);
  gameNumber++;
  round(TYPE_TRIPLE);
  Delay(5);

  newSheet();         /* playing sheet 6 */
  drawBingoScreen();
  gameNumber++;
  round(TYPE_HARD);
  Delay(5);
  gameNumber++;
  round(TYPE_DHARD);
  Delay(5);
  gameNumber++;
  round(TYPE_COVERALL);
  Delay(5);
  }

void Bingo::round(int gameType) {
  int winners;
  int x,y;
  rcs_Event event;
  rcs_Font  font;
  rcs_GC    gc;
  int       baseX,baseY;
  int       brd;
  char      letter;
  int       number;
  int       current;
  time_t    start;
  winners=0;
  current=0;
  gc=rcs_openGC(display,mainScreen);
  font=rcs_openFont(display,BINGO_FONT);
  rcs_setFont(display,gc,font);
  rcs_copyArea(display,table,mainScreen,gc,400,0,300,50,400,0);
  rcs_copyArea(display,table,mainScreen,gc,380,200,215,400,380,200);
  switch (gameType) {
    case TYPE_T:rcs_drawString(display,mainScreen,gc,440,40,"Crazy T"); break;
    case TYPE_NORMAL:rcs_drawString(display,mainScreen,gc,440,40,"Normal Bingo"); break;
    case TYPE_DOUBLE:rcs_drawString(display,mainScreen,gc,440,40,"Double Bingo"); break;
    case TYPE_TRIPLE:rcs_drawString(display,mainScreen,gc,440,40,"Triple Bingo"); break;
    case TYPE_HARD:rcs_drawString(display,mainScreen,gc,440,40,"Hardway Bingo"); break;
    case TYPE_DHARD:rcs_drawString(display,mainScreen,gc,440,40,"Double Hardway"); break;
    case TYPE_X:rcs_drawString(display,mainScreen,gc,440,40,"Cross X or +"); break;
    case TYPE_COVERALL:rcs_drawString(display,mainScreen,gc,440,40,"Cover All"); break;
    }
  sprintf(buffer,"Game #%d",gameNumber);
  rcs_drawString(display,mainScreen,gc,600,40,buffer);
  if (gameType == TYPE_COVERALL) {
    sprintf(buffer,"Progressive $%-14.2f",progressives[PROG_BINGO]);
    rcs_drawString(display,mainScreen,gc,440,70,buffer);
    }
  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  displayScreen();
  start=rcs_time();
  while (winners==0) {
    while (rcs_time()<start) {
      if (winners==0 && validate(nonPlayerBoards[current],gameType)) {
        msgBox(440,200,80,40,"Bingo");
        winners=1;
        } else current++;
      if (current>=nonPlayers) {
        current=0;
        }
      event=pollEvent(display);
      if (event.type==EVENT_BUTTON_PRESS && event.d1==1) {
        if (event.d2>=133 && event.d2<=222 &&
            event.d3>=556 && event.d3<=589) {
          if (playerWinners(gameType)>0) {
            msgBox(440,200,80,40,"Bingo");
            winners=1;
            }
          }
        if ((event.d2>=25 && event.d2<170 &&
             event.d3>=42 && event.d3<187) ||
            (event.d2>=25 && event.d2<170 &&
             event.d3>=216 && event.d3<361) ||
            (event.d2>=25 && event.d2<170 &&
             event.d3>=392 && event.d3<537) ||
            (event.d2>=189 && event.d2<334 &&
             event.d3>=42 && event.d3<187) ||
            (event.d2>=189 && event.d2<334 &&
             event.d3>=216 && event.d3<361) ||
            (event.d2>=189 && event.d2<334 &&
             event.d3>=392 && event.d3<537)
           ) {
          brd=0;
          if (event.d2>=25 && event.d2<=170) baseX=25;
            else { baseX=189; brd=3; }
          if (event.d3>=42 && event.d3<=187) baseY=42;
          if (event.d3>=216 && event.d3<=361) { baseY=216; brd++; }
          if (event.d3>=392 && event.d3<=537) { baseY=392; brd+=2; }
          buildBoard(playerBoards[brd]);
          x=(event.d2-baseX)/29;
          y=(event.d3-baseY)/29;
          gc=rcs_openGC(display,mainScreen);
          rcs_namedForeground(display,gc,"red");
          rcs_drawFilledCircle(display,mainScreen,gc,baseX+1+x*29,baseY+1+y*29,25,25);
          rcs_namedForeground(display,gc,"black");
          if (x!=2 || y!=2) {
            font=rcs_openFont(display,BINGO_FONT);
            rcs_setFont(display,gc,font);
            sprintf(buffer,"%2d",board[x][y]+1);
            rcs_drawString(display,mainScreen,gc,baseX+4+x*29,baseY+18+y*29,buffer);
            rcs_closeFont(display,font);
            }
          rcs_closeGC(display,gc);
          displayScreen();
          }
        }
      }
    if (winners==0) {
      number=rcs_random(75);
      while (called[number] != ' ') number=rcs_random(75);
      called[number]='*';
      number++;
      if (number>=1 && number<=15) letter='B';
      if (number>=16 && number<=30) letter='I';
      if (number>=31 && number<=45) letter='N';
      if (number>=46 && number<=60) letter='G';
      if (number>=61 && number<=75) letter='O';
      sprintf(buffer,"%c %-2d",letter,number);
      gc=rcs_openGC(display,mainScreen);
      font=rcs_openFont(display,BINGO_FONT);
      rcs_setFont(display,gc,font);
      rcs_copyArea(display,table,mainScreen,gc,440,80,100,100,440,80);
      rcs_namedForeground(display,gc,"black");
      rcs_drawString(display,mainScreen,gc,460,155,buffer);
      sprintf(buffer,"%2d",number);
      rcs_drawString(display,mainScreen,gc,632+((number-1)/15)*29,
                     112+((number-1)%15)*29,buffer);
      numbersCalled++;
      sprintf(buffer,"Called: %d",numbersCalled);
      rcs_drawString(display,mainScreen,gc,440,100,buffer);
      rcs_closeFont(display,font);
      rcs_closeGC(display,gc);
      displayScreen();
      printf("\a\n");
      start=rcs_time()+15000;
      }
    }
  figureWinners(gameType);
  }

int Bingo::playerWinners(int gameType) {
  int i;
  int bingos;
  bingos=0;
  for (i=0;i<6;i++)
    if (validate(playerBoards[i],gameType)) bingos++;
  return bingos;
  }

int Bingo::numberOfWinners(int gameType) {
  int i,j;
  int bingos;
  rcs_Font font;
  rcs_GC   gc;
  bingos=0;
  gc=rcs_openGC(display,mainScreen);
  font=rcs_openFont(display,BINGO_FONT);
  rcs_setFont(display,gc,font);
  for (i=0;i<nonPlayers;i++)
    if (validate(nonPlayerBoards[i],gameType)) {
      bingos++;
      rcs_namedForeground(display,gc,"white");
      rcs_drawFilledBox(display,mainScreen,gc,390,250,158,158);
      rcs_namedForeground(display,gc,"black");
      for (j=0;j<6;j++) {
        rcs_drawLine(display,mainScreen,gc,395,252+29*j,540,252+29*j);
        rcs_drawLine(display,mainScreen,gc,395,253+29*j,540,253+29*j);
        rcs_drawLine(display,mainScreen,gc,395+29*j,252,395+29*j,397);
        rcs_drawLine(display,mainScreen,gc,396+29*j,252,396+29*j,397);
        }
      drawBoard(nonPlayerBoards[i],400,270);
      markBoard();
      showWinner(gameType);
      sprintf(buffer,"%d Winners",bingos);
      msgBox(420,430,100,30,buffer);
      displayScreen();
      Delay(5);
      }
  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  return bingos;
  }

void Bingo::figureWinners(int gameType) {
  int players;
  int nonPlayers;
  double value;
  players=playerWinners(gameType);
  nonPlayers=numberOfWinners(gameType);
  value=50;
  if (gameType == TYPE_DOUBLE) value=100;
  if (gameType == TYPE_TRIPLE) value=150;
  if (gameType == TYPE_DHARD) value=100;
  if (gameType == TYPE_X) value=100;
  if (gameType == TYPE_T) value=100;
  if (gameType == TYPE_COVERALL) value=200;
  if (gameType == TYPE_COVERALL && numbersCalled<45) {
    value=progressives[PROG_BINGO];
    progressives[PROG_BINGO]=0;
    }
  value/=(players+nonPlayers);
  value*=players*payoutLevel;
  if (value>0) {
     player->winMoney(value);
     sprintf(buffer,"Won $%-8.2f",value);
     msgBox(420,470,130,30,buffer);
     }
  }

void Bingo::showWinner(int gameType) {
  int x,y;
  int count;
  int ox,oy;
  rcs_GC gc;
  rcs_Font font;
  ox=397; oy=254;
  gc=rcs_openGC(display,mainScreen);
  font=rcs_openFont(display,BINGO_FONT);
  rcs_setFont(display,gc,font);
  if (gameType==TYPE_T) {
/* check for normal T */
    count=0;
    for (x=0;x<5;x++) {
      if (marks[x][0]=='*') count++;
      if (marks[2][x]=='*') count++;
      }
    if (count==10) {
      for (x=0;x<5;x++) {
        rcs_namedForeground(display,gc,"red");
        rcs_drawFilledCircle(display,mainScreen,gc,ox+1+x*29,oy+1+0*29,25,25);
        rcs_drawFilledCircle(display,mainScreen,gc,ox+1+2*29,oy+1+x*29,25,25);
        rcs_namedForeground(display,gc,"black");
        sprintf(buffer,"%2d",board[x][0]+1);
        rcs_drawString(display,mainScreen,gc,ox+4+x*29,oy+18+0*29,buffer);
        if (x != 2) {
          sprintf(buffer,"%2d",board[2][x]+1);
          rcs_drawString(display,mainScreen,gc,ox+4+2*29,oy+18+x*29,buffer);
          }
        }
      }
/* Check for upside down T */
    count=0;
    for (x=0;x<5;x++) {
      if (marks[x][4]=='*') count++;
      if (marks[2][x]=='*') count++;
      }
    if (count==10) {
      for (x=0;x<5;x++) {
        rcs_namedForeground(display,gc,"red");
        rcs_drawFilledCircle(display,mainScreen,gc,ox+1+x*29,oy+1+4*29,25,25);
        rcs_drawFilledCircle(display,mainScreen,gc,ox+1+2*29,oy+1+x*29,25,25);
        rcs_namedForeground(display,gc,"black");
        sprintf(buffer,"%2d",board[x][4]+1);
        rcs_drawString(display,mainScreen,gc,ox+4+x*29,oy+18+4*29,buffer);
        if (x != 2) {
          sprintf(buffer,"%2d",board[2][x]+1);
          rcs_drawString(display,mainScreen,gc,ox+4+2*29,oy+18+x*29,buffer);
          }
        }
      }
/* check for left T */
    count=0;
    for (x=0;x<5;x++) {
      if (marks[0][x]=='*') count++;
      if (marks[x][2]=='*') count++;
      }
    if (count==10) {
      for (x=0;x<5;x++) {
        rcs_namedForeground(display,gc,"red");
        rcs_drawFilledCircle(display,mainScreen,gc,ox+1+0*29,oy+1+x*29,25,25);
        rcs_drawFilledCircle(display,mainScreen,gc,ox+1+x*29,oy+1+2*29,25,25);
        rcs_namedForeground(display,gc,"black");
        sprintf(buffer,"%2d",board[0][x]+1);
        rcs_drawString(display,mainScreen,gc,ox+4+0*29,oy+18+x*29,buffer);
        if (x != 2) {
          sprintf(buffer,"%2d",board[x][2]+1);
          rcs_drawString(display,mainScreen,gc,ox+4+x*29,oy+18+2*29,buffer);
          }
        }
      }
/* check for right T */
    count=0;
    for (x=0;x<5;x++) {
      if (marks[4][x]=='*') count++;
      if (marks[x][2]=='*') count++;
      }
    if (count==10) {
      for (x=0;x<5;x++) {
        rcs_namedForeground(display,gc,"red");
        rcs_drawFilledCircle(display,mainScreen,gc,ox+1+4*29,oy+1+x*29,25,25);
        rcs_drawFilledCircle(display,mainScreen,gc,ox+1+x*29,oy+1+2*29,25,25);
        rcs_namedForeground(display,gc,"black");
        sprintf(buffer,"%2d",board[4][x]+1);
        rcs_drawString(display,mainScreen,gc,ox+4+4*29,oy+18+x*29,buffer);
        if (x != 2) {
          sprintf(buffer,"%2d",board[x][2]+1);
          rcs_drawString(display,mainScreen,gc,ox+4+x*29,oy+18+2*29,buffer);
          }
        }
      }

    }
  if (gameType==TYPE_COVERALL) {
    for (x=0;x<5;x++)
      for (y=0;y<5;y++) {
        rcs_namedForeground(display,gc,"red");
        rcs_drawFilledCircle(display,mainScreen,gc,ox+1+x*29,oy+1+y*29,25,25);
        if (x != 2 || y != 2) {
          rcs_namedForeground(display,gc,"black");
          sprintf(buffer,"%2d",board[x][y]+1);
          rcs_drawString(display,mainScreen,gc,ox+4+x*29,oy+18+y*29,buffer);
          }
        }
    }
  if (gameType==TYPE_X) {
    count=0;
    for (x=0;x<5;x++) if (marks[x][2]=='*' && marks[2][x]=='*') count++;
    if (count==5) {
      for (x=0;x<5;x++) {
        rcs_namedForeground(display,gc,"red");
        rcs_drawFilledCircle(display,mainScreen,gc,ox+1+x*29,oy+1+2*29,25,25);
        rcs_drawFilledCircle(display,mainScreen,gc,ox+1+2*29,oy+1+x*29,25,25);
        if (x != 2) {
          rcs_namedForeground(display,gc,"black");
          sprintf(buffer,"%2d",board[x][2]+1);
          rcs_drawString(display,mainScreen,gc,ox+4+x*29,oy+18+2*29,buffer);
          sprintf(buffer,"%2d",board[2][x]+1);
          rcs_drawString(display,mainScreen,gc,ox+4+2*29,oy+18+x*29,buffer);
          }
        }
      } else {
      for (x=0;x<5;x++) {
        rcs_namedForeground(display,gc,"red");
        rcs_drawFilledCircle(display,mainScreen,gc,ox+1+x*29,oy+1+x*29,25,25);
        rcs_drawFilledCircle(display,mainScreen,gc,ox+1+x*29,oy+1+(4-x)*29,25,25);
        if (x != 2) {
          rcs_namedForeground(display,gc,"black");
          sprintf(buffer,"%2d",board[x][x]+1);
          rcs_drawString(display,mainScreen,gc,ox+4+x*29,oy+18+x*29,buffer);
          sprintf(buffer,"%2d",board[x][4-x]+1);
          rcs_drawString(display,mainScreen,gc,ox+4+x*29,oy+18+(4-x)*29,buffer);
          }
        }
      }
    }
  if (gameType==TYPE_NORMAL || gameType==TYPE_DOUBLE ||
      gameType==TYPE_TRIPLE ||
      gameType==TYPE_HARD || gameType==TYPE_DHARD) {
    count=0;
    if (gameType != TYPE_HARD && gameType != TYPE_DHARD) {
      for (x=0;x<5;x++) if (marks[x][x]=='*') count++;
      if (count==5) {
        for (x=0;x<5;x++) {
          rcs_namedForeground(display,gc,"red");
          rcs_drawFilledCircle(display,mainScreen,gc,ox+1+x*29,oy+1+x*29,25,25);
          sprintf(buffer,"%2d",board[x][x]+1);
          rcs_namedForeground(display,gc,"black");
          rcs_drawString(display,mainScreen,gc,ox+4+x*29,oy+18+x*29,buffer);
          }
        }
      count=0;
      for (x=0;x<5;x++) if (marks[x][4-x]=='*') count++;
      if (count==5) {
        for (x=0;x<5;x++) {
          rcs_namedForeground(display,gc,"red");
          rcs_drawFilledCircle(display,mainScreen,gc,ox+1+x*29,oy+1+(4-x)*29,25,25);
          sprintf(buffer,"%2d",board[x][4-x]+1);
          rcs_namedForeground(display,gc,"black");
          rcs_drawString(display,mainScreen,gc,ox+4+x*29,oy+18+(4-x)*29,buffer);
          }
        }
      }
    for (x=0;x<5;x++) {
      if (x!=2 || (gameType != TYPE_HARD && gameType != TYPE_DHARD)) {
        count=0;
        for (y=0;y<5;y++) if (marks[x][y]=='*') count++;
        if (count==5) {
          for (y=0;y<5;y++) {
            rcs_namedForeground(display,gc,"red");
            rcs_drawFilledCircle(display,mainScreen,gc,ox+1+x*29,oy+1+y*29,25,25);
            sprintf(buffer,"%2d",board[x][y]+1);
            rcs_namedForeground(display,gc,"black");
            rcs_drawString(display,mainScreen,gc,ox+4+x*29,oy+18+y*29,buffer);
            }
          }
        count=0;
        for (y=0;y<5;y++) if (marks[y][x]=='*') count++;
        if (count==5) {
          for (y=0;y<5;y++) {
            rcs_namedForeground(display,gc,"red");
            rcs_drawFilledCircle(display,mainScreen,gc,ox+1+y*29,oy+1+x*29,25,25);
            sprintf(buffer,"%2d",board[y][x]+1);
            rcs_namedForeground(display,gc,"black");
            rcs_drawString(display,mainScreen,gc,ox+4+y*29,oy+18+x*29,buffer);
            }
          }
        }
      }
    }
  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  }

