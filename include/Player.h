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

    Player(string name);

    void *run(void *playerId, Deck &cards);

    void setHand(int card); 

    void accessDeck(Deck &cards);

    void displayHand();

    void printHandToFile();

    void drawCard(Deck &cards);

    void discard(Deck &cards, int card);

    void compareCards(Deck &cards);

  private:
    string name;
    int hand = -1;
    int newlyDrawnCard = -1;
    bool started = false; 

};