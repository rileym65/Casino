#include <stdlib.h>
#include <time.h>
#define SUPPORT
#include "header.h"

#ifdef GRAPHIC
/*
void Output(const char* buffer) {
  }

void GotoXY(int x,int y) {
  }

void Delay(int i) {
  }

void ClrScr() {
  }

void Input(char* i) {
  }
*/

void button(rcs_GC gc,int x,int y,int w,int h) {
  rcs_namedForeground(display,gc,"white");
  rcs_drawFilledBox(display,mainScreen,gc,x,y,w,h);
  rcs_namedForeground(display,gc,"black");
  rcs_drawBox(display,mainScreen,gc,x+2,y+2,w-4,h-4);
  }

int msgBox(int x,int y,int w,int h,const char *msg) {
  rcs_GC gc;
  rcs_Font font;
  gc=rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"white");
  rcs_drawFilledBox(display,mainScreen,gc,x,y,w,h);
  rcs_namedForeground(display,gc,"black");
  rcs_drawBox(display,mainScreen,gc,x+2,y+2,w-4,h-4);
  font=rcs_openFont(display,ACTION_FONT);
  rcs_setFont(display,gc,font);
  rcs_drawString(display,mainScreen,gc,x+6,y+20,msg);
  rcs_closeFont(display,font);
  rcs_closeGC(display,gc);
  displayScreen();
  return 0;
  }

int actionBox(int x,int y,int w,int h,const char *msg,const char *b1,const char *b2) {
  int flag;
  rcs_GC gc;
  rcs_Font font;
  rcs_Event event;
      gc=rcs_openGC(display,mainScreen);
      rcs_namedForeground(display,gc,"white");
      rcs_drawFilledBox(display,mainScreen,gc,x,y,w,h);
      rcs_namedForeground(display,gc,"gray");
      rcs_drawFilledBox(display,mainScreen,gc,x+4,y+h-40,54,30);
      rcs_drawFilledBox(display,mainScreen,gc,x+62,y+h-40,54,30);
      rcs_namedForeground(display,gc,"black");
      rcs_drawBox(display,mainScreen,gc,x+2,y+2,w-4,h-4);
      font=rcs_openFont(display,ACTION_FONT);
      rcs_setFont(display,gc,font);
      rcs_drawString(display,mainScreen,gc,x+25,y+20,msg);
      rcs_drawBox(display,mainScreen,gc,x+6,y+h-38,50,26);
      rcs_drawBox(display,mainScreen,gc,x+64,y+h-38,50,26);
      rcs_drawString(display,mainScreen,gc,x+15,y+h-20,b1);
      rcs_drawString(display,mainScreen,gc,x+80,y+h-20,b2);
      rcs_closeFont(display,font);
      rcs_closeGC(display,gc);
      displayScreen();
      flag=99;
      while (flag==99) {
        event=getEvent(display);
        if (event.type==EVENT_BUTTON_PRESS) {
          if (event.d1==1 &&
              event.d2>=x+4 && event.d2<=x+58 &&
              event.d3>=y+h-40 && event.d3<=y+h-10) {
            flag=0;
            }
          if (event.d1==1 &&
              event.d2>=x+64 && event.d2<=x+104 &&
              event.d3>=y+h-40 && event.d3<=y+h-10) {
            flag=1;
            }

          }
        }
      gc=rcs_openGC(display,mainScreen);
      rcs_namedForeground(display,gc,"darkgreen");
      rcs_drawFilledBox(display,mainScreen,gc,x,y,w,h);
      rcs_closeGC(display,gc);
  return flag;
  }
#endif

#ifdef GRAPHIC
rcs_Event getEvent(rcs_Display* d) {
  rcs_Event event;
  rcs_GC    gc;
  event=rcs_getEvent(d);
  if (event.type == EVENT_BUTTON_PRESS && event.d1 == 2)
    printf("%d %d %d\n",event.d1,event.d2,event.d3);
  if (event.type == EVENT_EXPOSE) {
    if (event.d5 == 0) {
       gc=rcs_openGC(display,mainWindow);
       rcs_copyArea(display,mainScreen,mainWindow,gc,0,0,800,600,0,0);
       rcs_closeGC(display,gc);
      }
    event.type=0;
    }
  return event;
  }

rcs_Event pollEvent(rcs_Display* d) {
  rcs_Event event;
  rcs_GC    gc;
  event=rcs_pollEvent(d);
  if (event.type == EVENT_BUTTON_PRESS && event.d1 == 2)
    printf("%d %d %d\n",event.d1,event.d2,event.d3);
  if (event.type == EVENT_EXPOSE) {
    if (event.d5 == 0) {
       gc=rcs_openGC(display,mainWindow);
       rcs_copyArea(display,mainScreen,mainWindow,gc,0,0,800,600,0,0);
       rcs_closeGC(display,gc);
      }
    event.type=0;
    }
  return event;
  }

#endif

#ifdef GRAPHIC
void displayScreen() {
  rcs_GC    gc;
  gc=0;
  gc=rcs_openGC(display,mainWindow);
  rcs_copyArea(display,mainScreen,mainWindow,gc,0,0,800,600,0,0);
  rcs_closeGC(display,gc);
  rcs_flush(display);
  }
#endif

void clearScreen() {
  rcs_GC    gc;
#ifdef GRAPHIC
  gc=rcs_openGC(display,mainScreen);
  rcs_namedForeground(display,gc,"dark green");
  rcs_drawFilledBox(display,mainScreen,gc,0,0,800,600);
  rcs_closeGC(display,gc);
  displayScreen();
#endif
#ifdef CONSOLE
  ClrScr();
#endif
  }

float rand_seed;

/* 
int abs(int inp)
{
  if (inp<0) return -inp;
    else return inp;
}
*/

int Random(int size)
{
  float r;
  r=rand();
  r/=RAND_MAX;
  r-=int(r);
  r*=size;
  return int(r);
}
 
void Randomize()
{
  time_t t;
  t=time(&t);
  t&=0xfffff;
  srand(t);
}

char Upcase(char i)
{
  if (i>='a') i-=32;
  return i;
}

void makeName(char* buffer)
{
  buffer[0]='\0';
  switch(Random(41)) {
    case 0:strcpy(buffer,"Mike "); break;
    case 1:strcpy(buffer,"Susan "); break;
    case 2:strcpy(buffer,"John "); break;
    case 3:strcpy(buffer,"Terri "); break;
    case 4:strcpy(buffer,"Bill "); break;
    case 5:strcpy(buffer,"Donna "); break;
    case 6:strcpy(buffer,"Mark "); break;
    case 7:strcpy(buffer,"Constance "); break;
    case 8:strcpy(buffer,"Dave "); break;
    case 9:strcpy(buffer,"Dianne "); break;
    case 10:strcpy(buffer,"Chris "); break;
    case 11:strcpy(buffer,"Rachel "); break;
    case 12:strcpy(buffer,"Charles "); break;
    case 13:strcpy(buffer,"Kathy "); break;
    case 14:strcpy(buffer,"Martin "); break;
    case 15:strcpy(buffer,"Nancy "); break;
    case 16:strcpy(buffer,"Karin "); break;
    case 17:strcpy(buffer,"Janice "); break;
    case 18:strcpy(buffer,"Christoph "); break;
    case 19:strcpy(buffer,"Roland "); break;
    case 20:strcpy(buffer,"Jenny "); break;
    case 21:strcpy(buffer,"Liz "); break;
    case 22:strcpy(buffer,"Lars "); break;
    case 23:strcpy(buffer,"Beatrice "); break;
    case 24:strcpy(buffer,"Andreas "); break;
    case 25:strcpy(buffer,"Anne "); break;
    case 26:strcpy(buffer,"Tegan "); break;
    case 27:strcpy(buffer,"Robert "); break;
    case 28:strcpy(buffer,"Alan "); break;
    case 29:strcpy(buffer,"Dani "); break;
    case 30:strcpy(buffer,"Nicole "); break;
    case 31:strcpy(buffer,"Julie "); break;
    case 32:strcpy(buffer,"Gloria "); break;
    case 33:strcpy(buffer,"Ray "); break;
    case 34:strcpy(buffer,"Blythe  "); break;
    case 35:strcpy(buffer,"Dana "); break;
    case 36:strcpy(buffer,"Roxanne  "); break;
    case 37:strcpy(buffer,"Michelle "); break;
    case 38:strcpy(buffer,"Tara "); break;
    case 39:strcpy(buffer,"Pete "); break;
    case 40:strcpy(buffer,"Lisa "); break;
    }
  switch(Random(22)) {
    case 0:strcat(buffer,"Riley"); break;
    case 1:strcat(buffer,"Smith"); break;
    case 2:strcat(buffer,"Jones"); break;
    case 3:strcat(buffer,"Taylor"); break;
    case 4:strcat(buffer,"Brown"); break;
    case 5:strcat(buffer,"Franklin"); break;
    case 6:strcat(buffer,"Harding"); break;
    case 7:strcat(buffer,"Stevens"); break;
    case 8:strcat(buffer,"Farrell"); break;
    case 9:strcat(buffer,"Flemming"); break;
    case 10:strcat(buffer,"Miller"); break;
    case 11:strcat(buffer,"Rand"); break;
    case 12:strcat(buffer,"Langs"); break;
    case 13:strcat(buffer,"Harris"); break;
    case 14:strcat(buffer,"Jovenka"); break;
    case 15:strcat(buffer,"Braums"); break;
    case 16:strcat(buffer,"Peterson"); break;
    case 17:strcat(buffer,"Wild"); break;
    case 18:strcat(buffer,"Woods"); break;
    case 19:strcat(buffer,"Stanley"); break;
    case 20:strcat(buffer,"Stauber"); break;
    case 21:strcat(buffer,"Simpson"); break;
    }
}

