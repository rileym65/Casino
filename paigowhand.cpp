#include <stdlib.h>
#include <librcs.h>

PaigowHand::PaigowHand() {
  tiles=NULL;
  numTiles=0;
  x=0;
  y=0;
  dir='V';
  }

PaigowHand::~PaigowHand() {
  if (tiles != NULL) free(tiles);
  }

PaigowTile* PaigowHand::getTile(int t) { return tiles[t]; }

int PaigowHand::getTileRank(int value) {
  if (value == 66) return 2;
  if (value == 22) return 3;
  if (value == 44) return 4;
  if (value == 13) return 5;
  if (value == 55) return 6;
  if (value == 33) return 7;
  if (value == 22) return 8;
  if (value == 56) return 9;
  if (value == 46) return 10;
  if (value == 16) return 11;
  if (value == 15) return 12;
  if (value == 36) return 13;
  if (value == 45) return 13;
  if (value == 26) return 14;
  if (value == 35) return 14;
  if (value == 34) return 15;
  if (value == 25) return 15;
  if (value == 23) return 16;
  if (value == 14) return 16;
  if (value == 12) return 17;
  if (value == 24) return 17;
  return 18;
  }

int PaigowHand::getRank() {
  int ret;
  if (tiles == NULL) return 0;
  ret=(tiles[0]->getPips() + tiles[1]->getPips()) % 10;
  if (tiles[0]->getValue()==11 && tiles[1]->getPips()==8) ret=10;
  if (tiles[1]->getValue()==11 && tiles[0]->getPips()==8) ret=10;
  if (tiles[0]->getValue()==66 && tiles[1]->getPips()==8) ret=11;
  if (tiles[1]->getValue()==66 && tiles[0]->getPips()==8) ret=11;
  if (tiles[0]->getValue()==11 && tiles[1]->getPips()==9) ret=12;
  if (tiles[1]->getValue()==11 && tiles[0]->getPips()==9) ret=12;
  if (tiles[0]->getValue()==66 && tiles[1]->getPips()==9) ret=13;
  if (tiles[1]->getValue()==66 && tiles[0]->getPips()==9) ret=13;
  if (tiles[0]->getValue()==23 && tiles[1]->getValue()==14) ret=14;
  if (tiles[1]->getValue()==23 && tiles[0]->getValue()==14) ret=14;
  if (tiles[0]->getValue()==34 && tiles[1]->getValue()==25) ret=15;
  if (tiles[1]->getValue()==34 && tiles[0]->getValue()==25) ret=15;
  if (tiles[0]->getValue()==26 && tiles[1]->getValue()==35) ret=16;
  if (tiles[1]->getValue()==26 && tiles[0]->getValue()==35) ret=16;
  if (tiles[0]->getValue()==45 && tiles[1]->getValue()==36) ret=17;
  if (tiles[1]->getValue()==45 && tiles[0]->getValue()==36) ret=17;
  if (tiles[0]->getValue()==15 && tiles[1]->getValue()==15) ret=18;
  if (tiles[0]->getValue()==16 && tiles[1]->getValue()==16) ret=19;
  if (tiles[0]->getValue()==46 && tiles[1]->getValue()==46) ret=20;
  if (tiles[0]->getValue()==56 && tiles[1]->getValue()==56) ret=21;
  if (tiles[0]->getValue()==22 && tiles[1]->getValue()==22) ret=22;
  if (tiles[0]->getValue()==33 && tiles[1]->getValue()==33) ret=23;
  if (tiles[0]->getValue()==55 && tiles[1]->getValue()==55) ret=24;
  if (tiles[0]->getValue()==13 && tiles[1]->getValue()==13) ret=25;
  if (tiles[0]->getValue()==44 && tiles[1]->getValue()==44) ret=26;
  if (tiles[0]->getValue()==11 && tiles[1]->getValue()==11) ret=27;
  if (tiles[0]->getValue()==66 && tiles[1]->getValue()==66) ret=28;
  if (tiles[0]->getValue()==12 && tiles[1]->getValue()==24) ret=29;
  if (tiles[1]->getValue()==12 && tiles[0]->getValue()==24) ret=29;
  return ret;
  }

int PaigowHand::compare(PaigowHand* h) {
  int v1,v2;
  int x1,x2;
  v1=getRank();
  v2=h->getRank();
  if (v1>v2) return 1;
  if (v1<v2) return -1;
  v1 = getTileRank(tiles[0]->getValue());
  v2 = getTileRank(tiles[1]->getValue());
  if (v2 < v1) v1 = v2;
  x1 = getTileRank(h->tiles[0]->getValue());
  x2 = getTileRank(h->tiles[1]->getValue());
  if (x2 < x1) x1 = x2;
  if (v1 < x1) return 1;
  if (v1 > x1) return -1;
  return 0;
  }

void PaigowHand::setDirection(char d) { dir=d; }

void PaigowHand::setPosition(int nx,int ny) {
  x=nx;
  y=ny;
  }

void PaigowHand::paint(rcs_Display* d,rcs_Window w,rcs_GC gc) {
  int i;
  for (i=0;i<numTiles;i++) {
    if (dir=='V') {
      tiles[i]->setPosition(x+i*28,y);
      tiles[i]->setDirection('V');
      } else {
      tiles[i]->setPosition(x,y+i*28);
      tiles[i]->setDirection('H');
      }
    tiles[i]->paint(d,w,gc);
    }
  }

PaigowTile* PaigowHand::removeTile(int p) {
  PaigowTile* ret;
  int         i;
  if (tiles==NULL || p<0 || p>=numTiles) return NULL;
  ret=tiles[p];
  for (i=p;i<numTiles-1;i++) tiles[i]=tiles[i+1];
  numTiles--;
  tiles=(PaigowTile**)realloc(tiles,sizeof(PaigowTile*)*numTiles);
  return ret;
  }

void PaigowHand::addTile(PaigowTile* t) {
  if (tiles == NULL) tiles=(PaigowTile**)malloc(sizeof(PaigowTile*));
    else  tiles=(PaigowTile**)realloc(tiles,sizeof(PaigowTile*)*(numTiles+1));
  tiles[numTiles++]=t;
  }

int PaigowHand::getNumTiles() { return numTiles; }

void PaigowHand::analyze() {
  int i;
  supreme=0;
  for (i=0;i<13;i++) counts[i]=0;
  for (i=0;i<numTiles;i++) {
    if (tiles[i]->getValue()!=12 && tiles[i]->getValue()!=24)
      counts[tiles[i]->getPips()]++;
    if (tiles[i]->getValue()==12) supreme++;
    if (tiles[i]->getValue()==24) supreme++;
    }
  if (supreme != 2) supreme=0;
  }

int PaigowHand::findTileValue(int v) {
  int i;
  i=0;
  while (i<numTiles) {
    if (tiles[i]->getValue()==v) return i;
    i++;
    }
  return -1;
  }

int PaigowHand::findTile(int pips) {
  int i;
  i=0;
  while (i<numTiles) {
    if (tiles[i]->getPips()==pips) return i;
    i++;
    }
  return -1;
  }

void PaigowHand::splitHand(PaigowHand* h) {
/*  int i; */
  PaigowHand *h1,*h2;
  int r1,r2,rt,high;
  int hr1,hr2;
  h1=new PaigowHand();
  h2=new PaigowHand();

  h1->addTile(getTile(0)); h1->addTile(getTile(1));
  h2->addTile(getTile(2)); h2->addTile(getTile(3));
  r1=h1->getRank(); r2=h2->getRank();
  if (r2>r1) { rt=r1; r1=r2; r2=rt; }
  hr1=r1; hr2=r2; high=0;
  h1->removeTile(0); h1->removeTile(0);
  h2->removeTile(0); h2->removeTile(0);

  h1->addTile(getTile(0)); h1->addTile(getTile(2));
  h2->addTile(getTile(1)); h2->addTile(getTile(3));
  r1=h1->getRank(); r2=h2->getRank();
  if (r2>r1) { rt=r1; r1=r2; r2=rt; }
  if ((r1>hr1 && r2>hr2) || (r1>9 && r1>hr1) || (r2>9 && r2>hr2))
    { hr1=r1; hr2=r2; high=1; }
  h1->removeTile(0); h1->removeTile(0);
  h2->removeTile(0); h2->removeTile(0);

  h1->addTile(getTile(0)); h1->addTile(getTile(3));
  h2->addTile(getTile(1)); h2->addTile(getTile(2));
  r1=h1->getRank(); r2=h2->getRank();
  if (r2>r1) { rt=r1; r1=r2; r2=rt; }
  if ((r1>hr1 && r2>hr2) || (r1>9 && r1>hr1) || (r2>9 && r2>hr2))
    { hr1=r1; hr2=r2; high=2; }
  h1->removeTile(0); h1->removeTile(0);
  h2->removeTile(0); h2->removeTile(0);

  h1->addTile(getTile(1)); h1->addTile(getTile(2));
  h2->addTile(getTile(0)); h2->addTile(getTile(3));
  r1=h1->getRank(); r2=h2->getRank();
  if (r2>r1) { rt=r1; r1=r2; r2=rt; }
  if ((r1>hr1 && r2>hr2) || (r1>9 && r1>hr1) || (r2>9 && r2>hr2))
    { hr1=r1; hr2=r2; high=3; }
  h1->removeTile(0); h1->removeTile(0);
  h2->removeTile(0); h2->removeTile(0);

  h1->addTile(getTile(1)); h1->addTile(getTile(3));
  h2->addTile(getTile(0)); h2->addTile(getTile(2));
  r1=h1->getRank(); r2=h2->getRank();
  if (r2>r1) { rt=r1; r1=r2; r2=rt; }
  if ((r1>hr1 && r2>hr2) || (r1>9 && r1>hr1) || (r2>9 && r2>hr2))
    { hr1=r1; hr2=r2; high=4; }
  h1->removeTile(0); h1->removeTile(0);
  h2->removeTile(0); h2->removeTile(0);

  h1->addTile(getTile(2)); h1->addTile(getTile(3));
  h2->addTile(getTile(0)); h2->addTile(getTile(1));
  r1=h1->getRank(); r2=h2->getRank();
  if (r2>r1) { rt=r1; r1=r2; r2=rt; }
  if ((r1>hr1 && r2>hr2) || (r1>9 && r1>hr1) || (r2>9 && r2>hr2))
    { hr1=r1; hr2=r2; high=5; }
  h1->removeTile(0); h1->removeTile(0);
  h2->removeTile(0); h2->removeTile(0);

  switch (high) {
    case 0:h->addTile(removeTile(1));
           h->addTile(removeTile(0));
           break;
    case 1:h->addTile(removeTile(2));
           h->addTile(removeTile(0));
           break;
    case 2:h->addTile(removeTile(3));
           h->addTile(removeTile(0));
           break;
    case 3:h->addTile(removeTile(2));
           h->addTile(removeTile(1));
           break;
    case 4:h->addTile(removeTile(3));
           h->addTile(removeTile(1));
           break;
    case 5:h->addTile(removeTile(3));
           h->addTile(removeTile(2));
           break;
    }
  delete(h1);
  delete(h2);
  }

void PaigowHand::setSide(char s) {
  int i;
  for (i=0;i<numTiles;i++)
    tiles[i]->setSide(s);
  }

