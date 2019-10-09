#ifndef _CARDGAME_H
#define _CARDGAME_H

class CardGames {
  protected:
    Deck*         deck;
    float         minBet;
    Hand*         dealerHand;
    Player        *players[MAX_PLAYERS];
    int           numPlayers;
  public:
    CardGames(int decks,int jokers,float minbet);
    ~CardGames();
    void addPlayer(Player* player);
};

#endif

