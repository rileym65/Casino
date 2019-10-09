#include <librcs.h>

PaigowTile::PaigowTile(int h,int l) {
  top=h;
  bottom=l;
  x=0;
  y=0;
  dir='V';
  side='F';
  }

PaigowTile::~PaigowTile() {
  }

int PaigowTile::getPips() { return top+bottom; }

int PaigowTile::getValue() { return top*10 + bottom; }

void PaigowTile::setDirection(char d) { dir=d; }
void PaigowTile::setSide(char s) { side=s; }

void PaigowTile::setPosition(int nx,int ny) {
  x=nx;
  y=ny;
  }

void PaigowTile::hNumber(rcs_Display* d,rcs_Window w,rcs_GC gc,int x,int y,int n,int flag,int top) {
  switch(n) {
    case 1:rcs_namedForeground(d,gc,"red");
           if (top==0) {
             rcs_drawFilledBox(d,w,gc,x+2,y+10,4,4);
             } else {
             rcs_drawFilledBox(d,w,gc,x+18,y+10,4,4);
             }
           break;
    case 2:rcs_namedForeground(d,gc,"white");
           if (top==0) {
             rcs_drawFilledBox(d,w,gc,x+2,y+2,4,4);
             rcs_drawFilledBox(d,w,gc,x+2,y+18,4,4);
             } else {
             rcs_drawFilledBox(d,w,gc,x+18,y+2,4,4);
             rcs_drawFilledBox(d,w,gc,x+18,y+18,4,4);
             }
           break;
    case 3:rcs_namedForeground(d,gc,"white");
           rcs_drawFilledBox(d,w,gc,x+2,y+2,4,4);
           rcs_drawFilledBox(d,w,gc,x+10,y+10,4,4);
           rcs_drawFilledBox(d,w,gc,x+18,y+18,4,4);
           break;
    case 4:rcs_namedForeground(d,gc,"red");
           rcs_drawFilledBox(d,w,gc,x+2,y+2,4,4);
           rcs_drawFilledBox(d,w,gc,x+2,y+18,4,4);
           rcs_drawFilledBox(d,w,gc,x+18,y+2,4,4);
           rcs_drawFilledBox(d,w,gc,x+18,y+18,4,4);
           break;
    case 5:rcs_namedForeground(d,gc,"white");
           rcs_drawFilledBox(d,w,gc,x+2,y+2,4,4);
           rcs_drawFilledBox(d,w,gc,x+2,y+18,4,4);
           rcs_drawFilledBox(d,w,gc,x+10,y+10,4,4);
           rcs_drawFilledBox(d,w,gc,x+18,y+2,4,4);
           rcs_drawFilledBox(d,w,gc,x+18,y+18,4,4);
           break;
    case 6:rcs_namedForeground(d,gc,"white");
           if (flag==2) rcs_namedForeground(d,gc,"red");
           rcs_drawFilledBox(d,w,gc,x+2,y+18,4,4);
           rcs_drawFilledBox(d,w,gc,x+10,y+18,4,4);
           rcs_drawFilledBox(d,w,gc,x+18,y+18,4,4);
           if (flag==2) rcs_namedForeground(d,gc,"white");
           if (flag==1) rcs_namedForeground(d,gc,"red");
           rcs_drawFilledBox(d,w,gc,x+2,y+2,4,4);
           rcs_drawFilledBox(d,w,gc,x+10,y+2,4,4);
           rcs_drawFilledBox(d,w,gc,x+18,y+2,4,4);
           break;
    }
  }

void PaigowTile::vNumber(rcs_Display* d,rcs_Window w,rcs_GC gc,int x,int y,int n,int flag,int top) {
  switch(n) {
    case 1:rcs_namedForeground(d,gc,"red");
           if (top==0) {
             rcs_drawFilledBox(d,w,gc,x+10,y+2,4,4);
             } else {
             rcs_drawFilledBox(d,w,gc,x+10,y+18,4,4);
             }
           break;
    case 2:rcs_namedForeground(d,gc,"white");
           if (top==0) {
             rcs_drawFilledBox(d,w,gc,x+2,y+2,4,4);
             rcs_drawFilledBox(d,w,gc,x+18,y+2,4,4);
             } else {
             rcs_drawFilledBox(d,w,gc,x+2,y+18,4,4);
             rcs_drawFilledBox(d,w,gc,x+18,y+18,4,4);
             }
           break;
    case 3:rcs_namedForeground(d,gc,"white");
           rcs_drawFilledBox(d,w,gc,x+2,y+18,4,4);
           rcs_drawFilledBox(d,w,gc,x+10,y+10,4,4);
           rcs_drawFilledBox(d,w,gc,x+18,y+2,4,4);
           break;
    case 4:rcs_namedForeground(d,gc,"red");
           rcs_drawFilledBox(d,w,gc,x+2,y+2,4,4);
           rcs_drawFilledBox(d,w,gc,x+2,y+18,4,4);
           rcs_drawFilledBox(d,w,gc,x+18,y+2,4,4);
           rcs_drawFilledBox(d,w,gc,x+18,y+18,4,4);
           break;
    case 5:rcs_namedForeground(d,gc,"white");
           rcs_drawFilledBox(d,w,gc,x+2,y+2,4,4);
           rcs_drawFilledBox(d,w,gc,x+2,y+18,4,4);
           rcs_drawFilledBox(d,w,gc,x+10,y+10,4,4);
           rcs_drawFilledBox(d,w,gc,x+18,y+2,4,4);
           rcs_drawFilledBox(d,w,gc,x+18,y+18,4,4);
           break;
    case 6:rcs_namedForeground(d,gc,"white");
           if (flag==2) rcs_namedForeground(d,gc,"red");
           rcs_drawFilledBox(d,w,gc,x+2,y+2,4,4);
           rcs_drawFilledBox(d,w,gc,x+2,y+10,4,4);
           rcs_drawFilledBox(d,w,gc,x+2,y+18,4,4);
           if (flag==2) rcs_namedForeground(d,gc,"white");
           if (flag==1) rcs_namedForeground(d,gc,"red");
           rcs_drawFilledBox(d,w,gc,x+18,y+2,4,4);
           rcs_drawFilledBox(d,w,gc,x+18,y+10,4,4);
           rcs_drawFilledBox(d,w,gc,x+18,y+18,4,4);
           break;
    }
  }

void PaigowTile::paint(rcs_Display* d,rcs_Window w,rcs_GC gc) {
  rcs_namedForeground(d,gc,"black");
  if (dir == 'V') {
    rcs_drawFilledBox(d,w,gc,x,y,25,50);
    rcs_namedForeground(d,gc,"gray40");
    rcs_drawLine(d,w,gc,x-1,y,x-1,y+49);
    rcs_drawLine(d,w,gc,x+25,y,x+25,y+49);
    rcs_drawLine(d,w,gc,x,y-1,x+24,y-1);
    rcs_drawLine(d,w,gc,x,y+50,x+24,y+50);
    if (side == 'F') {
      vNumber(d,w,gc,x,y,top,(getValue()==66 || getValue()==33)?1:0,0);
      vNumber(d,w,gc,x,y+25,bottom,(getValue()==66 || getValue()==33)?2:0,1);
      }
    } else {
    rcs_drawFilledBox(d,w,gc,x,y,50,25);
    rcs_namedForeground(d,gc,"gray40");
    rcs_drawLine(d,w,gc,x-1,y,x-1,y+24);
    rcs_drawLine(d,w,gc,x+50,y,x+50,y+24);
    rcs_drawLine(d,w,gc,x,y-1,x+49,y-1);
    rcs_drawLine(d,w,gc,x,y+25,x+49,y+25);
    if (side == 'F') {
      hNumber(d,w,gc,x,y,top,(getValue()==66 || getValue()==33)?1:0,0);
      hNumber(d,w,gc,x+25,y,bottom,(getValue()==66 || getValue()==33)?2:0,1);
      }
    }
  }

