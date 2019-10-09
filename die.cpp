#include <librcs.h>

Die::Die(int s) {
  sides=s;
  number=1;
  x=0;
  y=0;
  size=10;
  }

Die::~Die() {
  }

void Die::putNumber(int n) { number=n; }

int  Die::getNumber() { return number; }

int  Die::roll() {
  number=rcs_random(sides)+1;
  return number;
  }

void Die::paint(rcs_Display* display,rcs_Window win,rcs_GC gc) {
  int sz;
  rcs_namedForeground(display,gc,"ivory");
  rcs_drawFilledBox(display,win,gc,x+1,y+1,size-1,size-1);
  rcs_namedForeground(display,gc,"black");
  rcs_drawBox(display,win,gc,x+0,y+0,size,size);
  sz=size/4;

  if (number==1 || number==3 || number==5)
    rcs_drawFilledCircle(display,win,gc,x+size/2-sz/2,y+size/2-sz/2,sz,sz);
  if (number>1)
    rcs_drawFilledCircle(display,win,gc,x+sz-sz/2,y+sz-sz/2,sz,sz);
  if (number>3)
    rcs_drawFilledCircle(display,win,gc,x+size-sz-sz/2,y+sz-sz/2,sz,sz);
  if (number>3)
    rcs_drawFilledCircle(display,win,gc,x+sz-sz/2,y+size-sz-sz/2,sz,sz);
  if (number>1)
    rcs_drawFilledCircle(display,win,gc,x+size-sz-sz/2,y+size-sz-sz/2,sz,sz);
  if (number==6) {
    rcs_drawFilledCircle(display,win,gc,x+sz-sz/2,y+size/2-sz/2,sz,sz);
    rcs_drawFilledCircle(display,win,gc,x+size-sz-sz/2,y+size/2-sz/2,sz,sz);
    }
  }

void Die::setPosition(int px,int py) {
  x=px;
  y=py;
  }

void Die::setSize(int s) { size=s; }

