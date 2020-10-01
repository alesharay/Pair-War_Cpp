#pragma once

#include "globals.h"
#include "Deck.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>         // for writing to the log 
#include <iostream>

using namespace std;

class Player {
  public:
    Player();

    Player(Deck &cards, string name);

    void *run(void *playerId);

    void setHand(int card); 

    void accessDeck();

    void displayHand();

    void printHandToFile();

    void drawCard();

    void discard(int card);

    void compareCards();

  private:
    string name;
    Deck cards;
    int hand = -1;
    int newlyDrawnCard = -1;
    bool started = false; 

};