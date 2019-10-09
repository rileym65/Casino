#include <stdio.h>
#include <string.h>
#ifdef UNIX
#include <unistd.h>
#endif
#ifdef WIN32
#include <windows.h>
#include <sys/timeb.h>
#include <io.h>
#endif

void Output(const char* Buffer)
{
  printf("%s",Buffer);
}

void Input(char* Buffer)
{
  int i;
  Buffer[0]='\0';
  fgets(Buffer,80,stdin);
  for (i=0;(unsigned)i<strlen(Buffer);i++)
    if (Buffer[i]=='\n') Buffer[i]=0;
/*
  fgets(Buffer,80,stdin);
  while (Buffer[strlen(Buffer)]<32 && Buffer[strlen(Buffer)]>0) 
    Buffer[strlen(Buffer)]=0;
*/
}

void ClrScr()
{
#ifndef GRAPHIC
  Output("\E[H\E[2J");
#endif
}

void Delay(int sec)
{
#ifdef WIN32
  Sleep(sec*1000);
#else
  sleep(sec);
#endif
}

void GotoXY(int x,int y)
{
#ifndef GRAPHIC
  char XBuffer[10];
  char YBuffer[10];
  char Buffer[20];
  sprintf(XBuffer,"%d",x);
  sprintf(YBuffer,"%d",y);
  strcpy(Buffer,"\E["); strcat(Buffer,YBuffer); strcat(Buffer,";");
  strcat(Buffer,XBuffer); strcat(Buffer,"H");
  Output(Buffer);
#endif
}


