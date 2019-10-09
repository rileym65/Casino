#include "header.h"
#include "cardgame.h"

CardGames::CardGames(int decks,int jokers,float minbet) {
  minBet=minbet;
  deck=new Deck(decks,jokers);
  numPlayers=0;
  dealerHand=new Hand(52);
  }

CardGames::~CardGames() {
  delete(deck);
  delete(dealerHand);
  }

void CardGames::addPlayer(Player* player)
{
  players[numPlayers++]=player;
  if (player!=NULL) player->resetStrategy();
}


