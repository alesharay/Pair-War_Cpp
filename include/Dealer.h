#pragma once

#include "globals.h"
#include "Deck.h"
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

    Dealer(Deck &cards, Player &player1, Player &player2, Player &player3);

    void dealCards();

    void shuffleCards();

  private:
    Deck cards;
    Player player1, player2, player3;
};