#include <stdlib.h>
#include <librcs.h>

PaigowDeck::PaigowDeck() {
  numTiles=32;
  tiles=(PaigowTile**)malloc(sizeof(PaigowTile*)*numTiles);
  newDeck();
  }

PaigowDeck::~PaigowDeck() {
  free(tiles);
  }

void PaigowDeck::shuffle() {
  int  i;
/*  int  value; */
  int  p1,p2;
  PaigowTile* tcard;
  rcs_randomize();
  p1=0;
  for (i=0;i<numTiles*5;i++) {
    p2=rcs_random(numTiles);
    tcard=tiles[p1];
    tiles[p1]=tiles[p2];
    tiles[p2]=tcard;
    p1++;
    if (p1==numTiles) p1=0;
    }
  tilePos=numTiles-1;
  }

PaigowTile* PaigowDeck::dealTile() {
  if (tilePos == 0) return NULL;
  return tiles[tilePos--];
  }

int PaigowDeck::tilesLeft() {
  return tilePos;
  }

void PaigowDeck::newDeck() {
  tiles[0]=new PaigowTile(6,6);
  tiles[1]=new PaigowTile(6,6);
  tiles[2]=new PaigowTile(5,6);
  tiles[3]=new PaigowTile(5,6);
  tiles[4]=new PaigowTile(4,6);
  tiles[5]=new PaigowTile(4,6);
  tiles[6]=new PaigowTile(3,6);
  tiles[7]=new PaigowTile(2,6);
  tiles[8]=new PaigowTile(1,6);
  tiles[9]=new PaigowTile(1,6);
  tiles[10]=new PaigowTile(5,5);
  tiles[11]=new PaigowTile(5,5);
  tiles[12]=new PaigowTile(4,5);
  tiles[13]=new PaigowTile(3,5);
  tiles[14]=new PaigowTile(2,5);
  tiles[15]=new PaigowTile(1,5);
  tiles[16]=new PaigowTile(1,5);
  tiles[17]=new PaigowTile(4,4);
  tiles[18]=new PaigowTile(4,4);
  tiles[19]=new PaigowTile(3,4);
  tiles[20]=new PaigowTile(2,4);
  tiles[21]=new PaigowTile(1,4);
  tiles[22]=new PaigowTile(3,3);
  tiles[23]=new PaigowTile(3,3);
  tiles[24]=new PaigowTile(2,3);
  tiles[25]=new PaigowTile(1,3);
  tiles[26]=new PaigowTile(1,3);
  tiles[27]=new PaigowTile(2,2);
  tiles[28]=new PaigowTile(2,2);
  tiles[29]=new PaigowTile(1,2);
  tiles[30]=new PaigowTile(1,1);
  tiles[31]=new PaigowTile(1,1);
  }

