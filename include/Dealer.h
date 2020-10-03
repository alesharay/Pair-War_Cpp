#pragma once

#include "globals.h"
#include "Player.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>         // for writing to the log 
#include <iostream>

using namespace std;

class Dealer : public pthreads_Class {
  public:
    
    Dealer(Deck &cards, Player &player_1, Player &player_2, Player &player_3);
    // void getNewCards(Deck &cards);

    void dealCards();

    void shuffleCards();

    void accessDeck();

    void run();

  private:
    Deck &card_deck;
    Player &player1, player2, player3;
};