#pragma once

#include "globals.h"
#include "Deck.h"
#include "pthreads_class.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>         // for writing to the log 
#include <iostream>



using namespace std;

class Player : public pthreads_class {
  
  public:
    Player(Deck &cards, int ID);
    void run();
    void access_deck();
    void draw_card();
    void discard_card( int card );
    void compare_cards();
    void set_hand(int card); 
    int get_hand();
    void set_ID(int ID);
    int get_ID();
    void reset_hand();

  private:
    int hand = -1;
    int newlyDrawnCard = -1;
    int id; 
    bool started = false; 
    Deck &card_deck;

};