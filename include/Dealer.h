#pragma once

#include "globals.h"
#include "Player.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>         // for writing to the log 
#include <iostream>

using namespace std;

class Dealer : public pthreads_class {
  
  public:    
    Dealer(Deck &cards, Player &player_1, Player &player_2, Player &player_3);
    void run();
    void access_deck();
    void shuffle_deck();
    void deal_cards();

  private:
    Deck &card_deck;
    Player &player1, &player2, &player3;

};