#pragma once

#include "globals.h"
#include "Deck.h"
#include "pthreads_Class.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>         // for writing to the log 
#include <iostream>



using namespace std;

class Player : public pthreads_Class {
  public:
    Player(Deck &cards);

    Player(Deck &cards, string player_name);

    void setHand(int card); 

    void accessDeck();

    void displayHand();

    void printHandToFile();

    void drawCard();

    void discard( int card );

    void compareCards();

    void resetHand();

    void run();

  private:
    string name;
    int hand = -1;
    int newlyDrawnCard = -1;
    bool started = false; 
    Deck &card_deck;
};