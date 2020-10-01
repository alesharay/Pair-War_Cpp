#pragma once

#include "globals.h"
//#include "Deck.h"
#include "Player.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>         // for writing to the log 
#include <iostream>

using namespace std;

class Dealer {
  public:
    Dealer();

    Dealer(Player &player1, Player &player2, Player &player3);

    void dealCards(Deck &cards);

    void shuffleCards(Deck &cards);

  private:
    Player player1, player2, player3;
};